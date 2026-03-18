#include <SoftwareSerial.h>
#include <IRremote.h>
#include "motor_driver.h"  // 標準モーター制御ライブラリ（ENA=D3, ENB=D6 など）

SoftwareSerial BTSerial(4, 5);  // Bluetooth RX=D4, TX=D5

#define RECV_PIN    10  // 赤外線受信モジュール → D10
IRrecv irrecv(RECV_PIN);
IRsend irsend;
decode_results results;
int buttonState;

#define BUZZ_PIN    13   // ブザー → D13
#define LED_PIN      2   // LED → D2
#define IR_BULLET    0xAAA  // 受け取る弾のコード（チームBから飛んでくる）
#define MY_BULLET    0xBBB  // 自分が撃つ弾のコード

#define SPEED      90   // 通常走行速度
#define TURNSPEED  170  // 旋回速度

#define MAX_PACKETSIZE 32
char buffUART[MAX_PACKETSIZE];
unsigned int buffUARTIndex = 0;
unsigned long preUARTTick = 0;

// 斜め移動（back_Left / back_Right）
void back_Left()  { go_Right(); set_Motorspeed(0, TURNSPEED); }
void back_Right() { go_Left();  set_Motorspeed(TURNSPEED, 0); }

// Bluetoothシリアルを読み取って走行コマンドを実行する
void do_Uart_Tick()
{
  char Uart_Date = 0;
  if (BTSerial.available())
  {
    size_t len = BTSerial.available();
    uint8_t sbuf[len + 1];
    sbuf[len] = 0x00;
    BTSerial.readBytes(sbuf, len);
    memcpy(buffUART + buffUARTIndex, sbuf, len);
    buffUARTIndex += len;
    preUARTTick = millis();
    if (buffUARTIndex >= MAX_PACKETSIZE - 1)
    {
      buffUARTIndex = MAX_PACKETSIZE - 2;
      preUARTTick = preUARTTick - 200;
    }
  }
  if (buffUARTIndex > 0 && (millis() - preUARTTick >= 100))
  {
    buffUART[buffUARTIndex] = 0x00;
    Uart_Date = buffUART[0];
    buffUARTIndex = 0;
  }

  switch (Uart_Date)
  {
    case 'M': go_Advance(); set_Motorspeed(SPEED, SPEED); break;
    case 'L': go_Left();    set_Motorspeed(0, TURNSPEED); break;
    case 'R': go_Right();   set_Motorspeed(TURNSPEED, 0); break;
    case 'B': go_Back();    set_Motorspeed(SPEED, SPEED); break;
    case 'X': back_Left();  break;
    case 'Y': back_Right(); break;
    case 'F': buttonState = 1; shoot(); break;
    case 'E': stop_Stop(); buzz_OFF(); break;
    case 'J': stop_Stop(); break;
    default:  break;
  }
}

// ブザーを鳴らす
void buzz_ON()
{
  for (int i = 0; i < 100; i++)
  {
    digitalWrite(BUZZ_PIN, LOW);
    delay(2);
    digitalWrite(BUZZ_PIN, HIGH);
    delay(2);
  }
}

// ブザーを止める
void buzz_OFF()
{
  digitalWrite(BUZZ_PIN, HIGH);
}

// 弾を発射する（赤外線送信）
void shoot()
{
  Serial.print("shooting bullet :");
  Serial.println(MY_BULLET, HEX);
  for (int i = 0; i < 3; i++)
  {
    irsend.sendSony(MY_BULLET, 12);
    delay(40);
  }
}

// 被弾したときの動作
void deadAlarm()
{
  BTSerial.println("DEAD!");
  Serial.println("DEAD!");
  stop_Stop();
  while (1)
  {
    for (int i = 0; i < 80; i++)
    {
      digitalWrite(BUZZ_PIN, LOW);
      delay(1);
      digitalWrite(BUZZ_PIN, HIGH);
      delay(1);
    }
    for (int i = 0; i < 100; i++)
    {
      digitalWrite(LED_PIN, LOW);
      delay(2);
      digitalWrite(LED_PIN, HIGH);
      delay(2);
    }
  }
}

void setup()
{
  init_GPIO();  // モーターピンを初期化

  irrecv.enableIRIn();

  pinMode(LED_PIN, OUTPUT);
  pinMode(BUZZ_PIN, OUTPUT);
  buzz_OFF();

  Serial.begin(9600);
  BTSerial.begin(9600);
}

int lastButtonState = 0;
void loop()
{
  if (buttonState) {
    buttonState = 0;
    irrecv.enableIRIn();
    irrecv.resume();
  }
  else if (irrecv.decode(&results)) {
    int data = results.value;
    Serial.print("ir code:");
    Serial.println(data);
    if (data == IR_BULLET) {
      deadAlarm();
    }
    irrecv.resume();
  }
  lastButtonState = buttonState;
  do_Uart_Tick();
}
