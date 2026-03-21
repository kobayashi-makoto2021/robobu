#include <IRremote.hpp>
#include <Servo.h>
#define plus  0xFF18E7  // 時計回りのボタン
#define minus 0xFF4AB5  // 反時計回りのボタン

const int RECV_PIN = 3;  // 赤外線受信機のピン
Servo servo;
int val;                 // 回転角度
bool cwRotation, ccwRotation;  // 回転の状態

void setup()
{
  Serial.begin(9600);
  IrReceiver.begin(RECV_PIN, ENABLE_LED_FEEDBACK);  // 受信機を起動する
  servo.attach(9);  // サーボピン
}

void loop()
{
  if (IrReceiver.decode()) {
    uint32_t code = IrReceiver.decodedIRData.decodedRawData;  // コードを保存してから resume
    Serial.println(code, HEX);
    IrReceiver.resume();  // 次のデータを受信する

    if (code == plus)
    {
      cwRotation = !cwRotation;   // 回転角度の値を切り替えます
      ccwRotation = false;        // これ以上回転しません
    }

    if (code == minus)
    {
      ccwRotation = !ccwRotation;
      cwRotation = false;         // 回転角度の値を切り替えます
    }
  }
  if (cwRotation && (val != 175)) {
    val++;  // 連動ボタン用
  }
  if (ccwRotation && (val != 0)) {
    val--;  // カウンター連動ボタン用
  }
  servo.write(val);
  delay(20);  // 回転速度
}
