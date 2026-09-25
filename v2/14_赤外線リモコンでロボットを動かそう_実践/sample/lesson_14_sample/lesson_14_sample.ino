#define USE_IR_ROBOT       // 赤外線を使うので、右モーターのPWMはD9

#define DECODE_NEC         // 付属のリモコンは「NEC」という決まりごとで送っている
#include <IRremote.hpp>
#include "motor_driver.h"

#define IR_PIN 10          // 赤外線レシーバの信号ピンは D10

// リモコンのボタンとIRコードの対応（自分の記録表の値に書きかえよう）
#define IR_ADVANCE  0x18   // 「▲」前進
#define IR_BACK     0x4A   // 「▼」後進
#define IR_RIGHT    0x5A   // 「▶」右折
#define IR_LEFT     0x10   // 「◀」左折
#define IR_STOP     0x38   // 「OK」ストップ

void setup()
{
  init_GPIO();                 // モーターとブザーの準備

  // ブザーと同じD13を光らせないように、LEDの合図はオフにする
  IrReceiver.begin(IR_PIN, DISABLE_LED_FEEDBACK);   // 赤外線受信機モジュールを有効にする

  Serial.begin(9600);
  Serial.println("--プログラムスタート！--");
  beep(1, 200);                // 準備できたよの合図
}

void loop()
{
  if (IrReceiver.decode()) {
    Serial.print("IRコード: 0x");
    Serial.println(IrReceiver.decodedIRData.command, HEX);   // 受け取ったコードを表示

    switch (IrReceiver.decodedIRData.command) {
      case IR_ADVANCE:  go_Advance(200, 300);  break;   // 少し前進
      case IR_BACK:     go_Back(200, 300);     break;   // 少し後進
      case IR_LEFT:     go_Left(200, 200);     break;   // 少し左折
      case IR_RIGHT:    go_Right(200, 200);    break;   // 少し右折
      case IR_STOP:     stop_Stop();           break;   // 止まる
      default:                                 break;
    }
    stop_Stop();              // 一回動いたら止まる
    IrReceiver.resume();      // 次の信号を受け取る
  }
}
