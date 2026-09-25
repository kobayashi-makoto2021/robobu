#define USE_IR_ROBOT       // 赤外線を使うので、右モーターのPWMはD9

#include <SoftwareSerial.h>
SoftwareSerial BTSerial(4, 5);  //RX,TX

#define DECODE_NEC         // 弾は「NEC」という決まりごとで送る
#include <IRremote.hpp>
#include "motor_driver.h"

#define RECV_PIN   10 // IR receiver pin connect to D10
#define SEND_PIN    3 // IR transmitter pin connect to D3

// #define IR_BULLET      0xAA       //Aの時はこちらを使う。Bの時はコメントアウト
// #define MY_BULLET      0xBB       //Aの時はこちらを使う。Bの時はコメントアウト
#define IR_BULLET      0xBB       //Bの時はこちらを使う。Aの時はコメントアウト
#define MY_BULLET      0xAA       //Bの時はこちらを使う。Aの時はコメントアウト
#define LED_PIN 2

#define SPEED      150  //ふつうの速さ
#define TURNSPEED  200  //曲がるときの速さ

#define MAX_PACKETSIZE 32    //Serial receive buffer
char buffUART[MAX_PACKETSIZE];
unsigned int buffUARTIndex = 0;
unsigned long preUARTTick = 0;

void shoot();
void deadAlarm();

//Bluetooth through the serial control
void do_Uart_Tick()
{

  char Uart_Date=0;
  if(BTSerial.available())
  {
    size_t len = BTSerial.available();
    uint8_t sbuf[len + 1];
    sbuf[len] = 0x00;
    BTSerial.readBytes(sbuf, len);
    memcpy(buffUART + buffUARTIndex, sbuf, len);//ensure that the serial port can read the entire frame of data
    buffUARTIndex += len;
    preUARTTick = millis();
    if(buffUARTIndex >= MAX_PACKETSIZE - 1)
    {
      buffUARTIndex = MAX_PACKETSIZE - 2;
      preUARTTick = preUARTTick - 200;
    }
  }
  if(buffUARTIndex > 0 && (millis() - preUARTTick >= 100))//APP send flag to modify the obstacle avoidance parameters
  { //data ready
    buffUART[buffUARTIndex] = 0x00;
    Uart_Date=buffUART[0];
    buffUARTIndex = 0;
  }

  switch (Uart_Date)    //serial control instructions
  {
    case 'M': go_Advance(SPEED, 0); break;
    case 'L': go_Left(TURNSPEED, 0); break;
    case 'R': go_Right(TURNSPEED, 0); break;
    case 'B': go_Back(SPEED, 0); break;
    case 'X': back_Left(TURNSPEED, 0); break;
    case 'Y': back_Right(TURNSPEED, 0); break;
    case 'F': shoot();break;
    case 'E': stop_Stop() ;buzz_Off();break;
    case 'J': stop_Stop() ;break;
    default:break;
  }
}

void setup()
{
  init_GPIO();          // モーターとブザーの準備

  // ブザーと同じD13を光らせないように、LEDの合図はオフにする
  IrReceiver.begin(RECV_PIN, DISABLE_LED_FEEDBACK); // 弾を受け取る準備
  IrSender.begin(SEND_PIN);                         // 弾を撃つ準備
  pinMode(LED_PIN, OUTPUT);

  Serial.begin(9600);//In order to fit the Bluetooth module's default baud rate, only 9600
  BTSerial.begin(9600);
  beep(1, 200);         // 準備できたよの合図
}

void loop()
{
  if (IrReceiver.decode()) {

    //If got shoot by enemy, dead freeze and alarm
    Serial.print("ir code: 0x");
    Serial.println(IrReceiver.decodedIRData.command, HEX);

    if(IrReceiver.decodedIRData.command == IR_BULLET)
    {
      deadAlarm();
    }

    IrReceiver.resume(); // resume receiver
  }
  do_Uart_Tick();
}

void shoot(){
 Serial.print("shooting bullet : 0x");
 Serial.println(MY_BULLET,HEX);
 IrSender.sendNEC(0x00, MY_BULLET, 2);  // 弾を3回送る
 IrReceiver.restartAfterSend();         // 撃ち終わったら、また受け取れるようにする
}

void deadAlarm(){
  BTSerial.println("DEAD!");
  Serial.println("DEAD!");
    stop_Stop();
 while(1)
 {
 //output an frequency
  for(int i=0;i<80;i++)
  {
    digitalWrite(BUZZ_PIN,LOW);
    delay(1);//wait for 1ms
    digitalWrite(BUZZ_PIN,HIGH);
    delay(1);//wait for 1ms
  }
  //output another frequency
  for(int i=0;i<100;i++)
  {
    digitalWrite(LED_PIN,LOW);
    delay(2);//wait for 2ms
    digitalWrite(LED_PIN,HIGH);
    delay(2);//wait for 2ms
  }
 }
}
