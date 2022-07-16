#include <IRremote.h>      //IRremoteライブラリをアルドゥイーノライブラリにコピーする必要があります
#include <Servo.h>
#define plus 0xFF18E7   //時計回りのボタン
#define minus 0xFF4AB5  //反時計回りのボタン

int RECV_PIN = 3;       //赤外線受信機のピン
Servo servo;
int val;                //回転角度
bool cwRotation, ccwRotation;  //回転の状態

IRrecv irrecv(RECV_PIN);

decode_results results;

void setup()
{
  Serial.begin(9600);
  irrecv.enableIRIn(); // 受信機を起動する
  servo.attach(9);     //サーボピン
}

void loop() 
{
  if (irrecv.decode(&results)) {
    Serial.println(results.value, HEX);
    irrecv.resume(); // Receive the next value

    if (results.value == plus)
    {
      cwRotation = !cwRotation;      //回転角度の値を切り替えます
      ccwRotation = false;         //これ以上回転しません
    }

    if (results.value == minus)
    {
      ccwRotation = !ccwRotation;   
      cwRotation = false;            //回転角度の値を切り替えます
    }
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
