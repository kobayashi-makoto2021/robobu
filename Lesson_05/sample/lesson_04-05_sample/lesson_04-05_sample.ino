#include "motor_driver.h"  // 標準モーター制御ライブラリ（ENA=D3, ENB=D6 など）

void setup()
{
  init_GPIO();        // モーターピンを初期化して停止状態にする

  go_Advance();       // 前進
  delay(2000);

  go_Back();          // 後退
  delay(2000);

  go_Left();          // 左旋回
  delay(2000);

  go_Right();         // 右旋回
  delay(2000);

  stop_Stop();        // 停止
}

void loop() {
}
