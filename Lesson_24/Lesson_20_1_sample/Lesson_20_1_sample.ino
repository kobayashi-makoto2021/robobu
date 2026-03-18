#include <SoftwareSerial.h>
#include "motor_driver.h"  // 標準モーター制御ライブラリ（ENA=D3, ENB=D6 など）

SoftwareSerial BLTSerial(4, 5);  // Bluetooth RX=D4, TX=D5

#define MAX_PACKETSIZE 32  // シリアル受信バッファサイズ

struct car_status {
  int speed;
  int angle;
  int direct;
};

char buffUART[MAX_PACKETSIZE];
unsigned int buffUARTIndex = 0;
unsigned long preUARTTick = 0;
int Speed = 150;
int TURNSPEED = 50;

// 斜め移動（後退しながら右折）
void back_Left()
{
  go_Right();
}

// 斜め移動（後退しながら左折）
void back_Right()
{
  go_Left();
}

// Bluetoothからのデータを解析して走行状態を更新する
car_status get_status(char buffUART[])
{
  car_status cstatus;
  int index = 2;
  if (buffUART[index] == '-') {
    cstatus.angle = -buffUART[index + 1] + '0';
    index = index + 3;
  } else {
    cstatus.angle = buffUART[index] - '0';
    index = index + 2;
  }
  int currentvalue;
  int spd = 0;
  while (buffUART[index] != ',')
  {
    currentvalue = buffUART[index] - '0';
    spd = spd * 10 + currentvalue;
    index++;
  }
  cstatus.speed = spd;
  index++;
  cstatus.direct = buffUART[index] - '0';
  return cstatus;
}

// Bluetoothシリアルを読み取って走行コマンドを実行する
void do_Uart_Tick()
{
  char Uart_Date = 0;
  if (BLTSerial.available())
  {
    size_t len = BLTSerial.available();
    uint8_t sbuf[len + 1];
    sbuf[len] = 0x00;
    BLTSerial.readBytes(sbuf, len);
    memcpy(buffUART + buffUARTIndex, sbuf, len);
    buffUARTIndex += len;
    preUARTTick = millis();
    if (buffUARTIndex >= MAX_PACKETSIZE - 1)
    {
      buffUARTIndex = MAX_PACKETSIZE - 2;
      preUARTTick = preUARTTick - 200;
    }
  }

  car_status cs;
  if (buffUARTIndex > 0 && (millis() - preUARTTick >= 100))
  {
    buffUART[buffUARTIndex] = 0x00;
    Uart_Date = buffUART[0];
    cs = get_status(buffUART);
    buffUARTIndex = 0;
  }

  Speed = cs.speed + 50;
  TURNSPEED = Speed * 3 / 2;
  if (Speed > 250)     Speed = 250;
  if (TURNSPEED > 250) TURNSPEED = 250;

  switch (Uart_Date)
  {
    case 'M':
      go_Advance();
      set_Motorspeed(Speed, Speed);
      break;
    case 'L':
      go_Left();
      if (cs.angle == 1)  { set_Motorspeed(0, 50); }
      if (cs.angle == 2)  { set_Motorspeed(50, 200); }
      break;
    case 'R':
      go_Right();
      if (cs.angle == -1) { set_Motorspeed(50, 0); }
      if (cs.angle == -2) { set_Motorspeed(200, 50); }
      break;
    case 'B':
      go_Back();
      set_Motorspeed(Speed, Speed);
      break;
    case 'X':
      back_Left();
      if (cs.angle == 1)  { set_Motorspeed(0, 50); }
      if (cs.angle == 2)  { set_Motorspeed(50, 200); }
      break;
    case 'Y':
      back_Right();
      if (cs.angle == -1) { set_Motorspeed(50, 0); }
      if (cs.angle == -2) { set_Motorspeed(200, 50); }
      break;
    case 'E': stop_Stop(); break;
    case 'J': stop_Stop(); break;
    default:  break;
  }
}

void setup()
{
  init_GPIO();  // モーターピンを初期化

  Serial.begin(9600);
  BLTSerial.begin(9600);
}

void loop()
{
  do_Uart_Tick();
}
