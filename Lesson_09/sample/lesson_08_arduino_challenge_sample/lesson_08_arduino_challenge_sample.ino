#include <IRremote.hpp>  // IRRemote.hpp をインクルード
#define IR_PIN 2  // 受信モジュールを２番ピンに繋げる

void setup(){
  Serial.begin(9600);    // シリアルを初期化し、ボーレートは9600に設定する
  pinMode(3, OUTPUT);    // LEDを３番ピンに繋げる
  IrReceiver.begin(IR_PIN, ENABLE_LED_FEEDBACK);  // 赤外線受信機モジュールを有効にする
  Serial.print("赤外線モジュールチャレンジプログラムスタート\n");
}

void loop(){
  if (IrReceiver.decode()){  // 赤外線受信機モジュールの受信データ
    Serial.print("IRコード: ");
    Serial.print(IrReceiver.decodedIRData.decodedRawData, HEX);  // シリアルに値を出力する
    Serial.print(",　ビット: ");
    Serial.println(IrReceiver.decodedIRData.numberOfBits);        // ビット数を出力する

    if (IrReceiver.decodedIRData.decodedRawData == 0xFF38C7) {
      digitalWrite(3, HIGH);
      Serial.print("HIGH\n");
    }
    if (IrReceiver.decodedIRData.decodedRawData == 0xFFB04F) {
      digitalWrite(3, LOW);
      Serial.print("LOW\n");
    }
    IrReceiver.resume();  // 次の値を受取る
  }
  delay(600);  // 600ミリ秒待機
}
