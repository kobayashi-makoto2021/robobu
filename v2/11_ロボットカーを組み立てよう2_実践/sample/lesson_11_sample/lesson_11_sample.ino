#include "motor_driver.h"   // 共通のモーター制御を読みこむ

void setup()
{
  init_GPIO();       // ピンの準備。必ず最初に呼ぶ

  beep(1, 200);      // 「ピッ」と鳴ってスタートの合図

  go_Advance(200, 2000);   // 前に進む（速さ200で2秒）
  stop_Stop(500);          // 止まる（0.5秒）

  go_Back(200, 2000);      // 後ろに下がる
  stop_Stop(500);

  go_Left(200, 1000);      // 左に旋回する
  stop_Stop(500);

  go_Right(200, 1000);     // 右に旋回する
  stop_Stop();

  beep(2, 200);      // 「ピピッ」と鳴って終わりの合図
}

void loop() {
}
