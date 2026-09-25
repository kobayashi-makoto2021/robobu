/*  ___   ___  ___  _   _  ___   ___   ____ ___  ____
   / _ \ /___)/ _ \| | | |/ _ \ / _ \ / ___) _ \|    \
  | |_| |___ | |_| | |_| | |_| | |_| ( (__| |_| | | | |
   \___/(___/ \___/ \__  |\___/ \___(_)____)___/|_|_|_|
                    (____/
   Arduino Smart Car Tutorial Lesson 7
   Tutorial URL http://osoyoo.com/2019/02/26/osoyoo-v2-robot-car-lesson-7-imitation-driving-with-bluetooth-app/
   CopyRight www.osoyoo.com

   タブレットのアプリから送られてくる文字で、ロボットを操縦する。
*/

#include <SoftwareSerial.h>
SoftwareSerial BLTSerial(4, 5);  //RX,TX

#include "motor_driver.h"

#define MAX_PACKETSIZE 32    //Serial receive buffer

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

car_status get_status( char buffUART[]);

//Bluetooth through the serial control
void do_Uart_Tick()
{

  char Uart_Date = 0;
  if (BLTSerial.available())
  {
    size_t len = BLTSerial.available();
    uint8_t sbuf[len + 1];
    sbuf[len] = 0x00;
    BLTSerial.readBytes(sbuf, len);
    memcpy(buffUART + buffUARTIndex, sbuf, len);//ensure that the serial port can read the entire frame of data
    buffUARTIndex += len;
    preUARTTick = millis();
    if (buffUARTIndex >= MAX_PACKETSIZE - 1)
    {
      buffUARTIndex = MAX_PACKETSIZE - 2;
      preUARTTick = preUARTTick - 200;
    }
  }
  car_status cs = {0, 0, 0};
  if (buffUARTIndex > 0 && (millis() - preUARTTick >= 100)) //APP send flag to modify the obstacle avoidance parameters
  { //data ready
    buffUART[buffUARTIndex] = 0x00;
    Uart_Date = buffUART[0];
    cs = get_status(buffUART);
    buffUARTIndex = 0;
  }
  Speed = cs.speed + 50;
  TURNSPEED = Speed * 3 / 2;
  if (Speed > 250) Speed = 250;
  if (TURNSPEED > 250) TURNSPEED = 250;
  switch (Uart_Date)    //serial control instructions
  {
    case 'M':
      go_Advance(Speed, 0);
      break;
    case 'L':
      go_Left(TURNSPEED, 0);
      if (cs.angle == 1) {
        set_Motorspeed(0, 50) ;
      }
      if (cs.angle == 2) {
        set_Motorspeed(50, 200) ;
      }
      break;
    case 'R':
      go_Right(TURNSPEED, 0);
      if (cs.angle == -1) {
        set_Motorspeed(50, 0) ;
      }
      if (cs.angle == -2) {
        set_Motorspeed(200, 50) ;
      }
      break;
    case 'B':
      go_Back(Speed, 0);
      break;
    case 'X':
      back_Left(TURNSPEED, 0);
      if (cs.angle == 1) {
        set_Motorspeed(0, 50) ;
      }
      if (cs.angle == 2) {
        set_Motorspeed(50, 200) ;
      }
      break;
    case 'Y':
      back_Right(TURNSPEED, 0);
      if (cs.angle == -1) {
        set_Motorspeed(50, 0) ;
      }
      if (cs.angle == -2) {
        set_Motorspeed(200, 50) ;
      }
      break;

    case 'E': stop_Stop() ; break;
    case 'J': stop_Stop() ; break;
    default: break;
  }
}

void setup()
{
  init_GPIO();   // モーターとブザーの準備

  Serial.begin(9600);//In order to fit the Bluetooth module's default baud rate, only 9600
  BLTSerial.begin(9600);
  beep(1, 200);  // 準備できたよの合図
}

void loop()
{
  do_Uart_Tick();

}

car_status get_status( char buffUART[])
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
