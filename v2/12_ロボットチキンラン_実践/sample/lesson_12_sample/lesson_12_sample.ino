#include "motor_driver.h"

void setup()
{
  init_GPIO();
  beep(1, 200);      // スタートの合図

  //ここから下にプログラムを書く

  // ゴールの線ギリギリまで進む
  // 速さと時間は、レッスン11で作った「速さと距離の表」から予想して書きかえよう
  go_Advance(100, 1000);
  stop_Stop();

  beep(1, 100);      // 止まったよの合図

  delay(2000);       // 2秒待つ

  // スタートの線ギリギリまで戻る
  go_Back(100, 1000);
  stop_Stop();

  beep(2, 100);      // 戻ったよの合図
}

void loop() {
}
