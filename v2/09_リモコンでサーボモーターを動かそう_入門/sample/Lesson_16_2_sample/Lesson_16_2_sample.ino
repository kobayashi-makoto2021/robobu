#include <IRremote.hpp>
#include <Servo.h>

#define plus   0x18   //時計回りのボタン（▲）
#define minus  0x4A   //反時計回りのボタン（▼）

int RECV_PIN = 3;       //赤外線受信機のピン
Servo servo;
int val;                //回転角度
bool cwRotation, ccwRotation;  //回転の状態

void setup()
{
  Serial.begin(9600);
  IrReceiver.begin(RECV_PIN, ENABLE_LED_FEEDBACK); // 受信機を起動する
  servo.attach(9);     //サーボピン
}

void loop()
{
  if (IrReceiver.decode()) {
    Serial.println(IrReceiver.decodedIRData.command, HEX);

    if (IrReceiver.decodedIRData.command == plus)
    {
      cwRotation = !cwRotation;      //回転角度の値を切り替えます
      ccwRotation = false;         //これ以上回転しません
    }

    if (IrReceiver.decodedIRData.command == minus)
    {
      ccwRotation = !ccwRotation;
      cwRotation = false;            //回転角度の値を切り替えます
    }
    IrReceiver.resume(); // Receive the next value
  }
  if (cwRotation && (val != 175))  {
    val++;                         //連動ボタン用
  }
  if (ccwRotation && (val != 0))  {
    val--;                         //カウンター連動ボタン用
  }
  servo.write(val);
  delay(20);          //回転速度
}
