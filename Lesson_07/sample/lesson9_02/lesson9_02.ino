#include <IRremote.hpp>
#define IR_PIN 3
const int buzzerPin = 13;  // 13ピンをブザーに接続します

uint32_t irCode = 0;  // 受信したコードを保存する

void setup()
{
  pinMode(buzzerPin, OUTPUT);  // ブザーピンを出力として設定します
  digitalWrite(buzzerPin, HIGH);
  Serial.begin(9600);
  IrReceiver.begin(IR_PIN, ENABLE_LED_FEEDBACK);  // 赤外線受信機を有効にする
}

void loop()
{
  if (IrReceiver.decode())  // 赤外線受信モジュールの受信データ
  {
    Serial.print("irCode: ");
    Serial.print(IrReceiver.decodedIRData.decodedRawData, HEX);  // 値を16進数で出力します
    Serial.print(", bits: ");
    Serial.println(IrReceiver.decodedIRData.numberOfBits);        // ビット数を出力する
    irCode = IrReceiver.decodedIRData.decodedRawData;
    IrReceiver.resume();  // 次のデータを受信する
  }

  if (irCode == 0xFF38C7)  // 「OK」ボタンを押すと0xFF38C7を受信します
  {
    digitalWrite(buzzerPin, LOW);   // ブザーのビーブ音（低音）
  }
  else
  {
    digitalWrite(buzzerPin, HIGH);  // ブザーを止める
  }
  delay(400);  // 400ms待機
}
