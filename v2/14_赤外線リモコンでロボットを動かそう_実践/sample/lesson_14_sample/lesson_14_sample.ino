#define USE_IR_ROBOT       // 赤外線を使うので、右モーターのPWMはD9

#include <IRremote.h>
#include "motor_driver.h"

#define IR_PIN 10          // 赤外線レシーバの信号ピンは D10
IRrecv IR(IR_PIN);
decode_results IRresults;

// リモコンのボタンとIRコードの対応（自分の記録表の値に書きかえよう）
#define IR_ADVANCE  0x00FF18E7   // 「▲」前進
#define IR_BACK     0x00FF4AB5   // 「▼」後進
#define IR_RIGHT    0x00FF5AA5   // 「▶」右折
#define IR_LEFT     0x00FF10EF   // 「◀」左折
#define IR_STOP     0x00FF38C7   // 「OK」ストップ

void setup()
{
  init_GPIO();                 // モーターとブザーの準備

  pinMode(IR_PIN, INPUT);
  IR.enableIRIn();             // 赤外線受信機モジュールを有効にする

  Serial.begin(9600);
  Serial.println("--プログラムスタート！--");
  beep(1, 200);                // 準備できたよの合図
}

void loop()
{
  if (IR.decode(&IRresults)) {
    Serial.println(IRresults.value, HEX);   // 受け取ったコードを表示

    switch (IRresults.value) {
      case IR_ADVANCE:  go_Advance(200, 300);  break;   // 少し前進
      case IR_BACK:     go_Back(200, 300);     break;   // 少し後進
      case IR_LEFT:     go_Left(200, 200);     break;   // 少し左折
      case IR_RIGHT:    go_Right(200, 200);    break;   // 少し右折
      case IR_STOP:     stop_Stop();           break;   // 止まる
      default:                                 break;
    }
    stop_Stop();          // 一回動いたら止まる
    IR.resume();          // 次の信号を受け取る
  }
}
