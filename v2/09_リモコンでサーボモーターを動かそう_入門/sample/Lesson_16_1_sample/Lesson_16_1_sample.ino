#include <IRremote.hpp>  // IRremoteライブラリの関数を使用する

const int irReceiverPin = 3;  //受信モジュールのSIGはpin3

void setup()
{
  Serial.begin(9600);    //シリアルを初期化し、ボーレートは9600に設定する
  IrReceiver.begin(irReceiverPin, ENABLE_LED_FEEDBACK); // 赤外線受信機モジュールを有効にする
}

void loop()
{
  if (IrReceiver.decode()) //赤外線を受け取ったら
  {
    Serial.print("IRコード: 0x");
    Serial.println(IrReceiver.decodedIRData.command, HEX); //ボタンの番号を出力する
    IrReceiver.resume();    // 次の値を受取る
  }
  delay(600); //600ミリ秒待機
}
