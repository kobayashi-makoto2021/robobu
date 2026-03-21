#include <IRremote.hpp>  // IRRemote.hpp の関数を使用する
#define IR_PIN 3  // 受信モジュールのSIGはpin3

void setup()
{
  Serial.begin(9600);    // シリアルを初期化し、ボーレートは9600に設定する
  IrReceiver.begin(IR_PIN, ENABLE_LED_FEEDBACK);  // 赤外線受信機モジュールを有効にする
}

void loop()
{
  if (IrReceiver.decode())  // 赤外線受信機モジュールの受信データ
  {
    Serial.print("irCode: ");
    Serial.print(IrReceiver.decodedIRData.decodedRawData, HEX);  // シリアルに値を出力する
    Serial.print(",  bits: ");
    Serial.println(IrReceiver.decodedIRData.numberOfBits);        // ビット数を出力する
    IrReceiver.resume();    // 次の値を受取る
  }
  delay(600);  // 600ミリ秒待機
}
