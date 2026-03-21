#include <IRremote.hpp>  // IRRemote.hpp をインクルード ここでライブラリが使えるようになる
#define IR_PIN 2  // 受信モジュールのSIGはpin2

void setup(){
  Serial.begin(9600);    // シリアルを初期化し、ボーレートは9600に設定する
  IrReceiver.begin(IR_PIN, ENABLE_LED_FEEDBACK);  // 赤外線受信機モジュールを有効にする
  Serial.print("赤外線モジュールサンプルプログラムスタート\n");
}

void loop(){
  if (IrReceiver.decode()){  // 赤外線受信機モジュールの受信データ
    Serial.print("IRコード: ");
    Serial.print(IrReceiver.decodedIRData.decodedRawData, HEX);  // シリアルに値を出力する
    Serial.print(",　ビット: ");
    Serial.println(IrReceiver.decodedIRData.numberOfBits);        // ビット数を出力する
    IrReceiver.resume();  // 次の値を受取る
  }
  delay(600);  // 600ミリ秒待機
}
