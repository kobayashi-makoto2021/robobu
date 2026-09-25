#include "motor_driver.h"

void setup()
{
  init_GPIO();
  beep(1, 200);      // スタートの合図

  //ここから下にプログラムを書く

  // 区間ごとに beep を入れておくと、
  // どこまで進んだところでずれたのかが音で分かる。

  beep(1, 100);            // 区間1 開始
  go_Advance(150, 1000);
  stop_Stop(300);

  beep(2, 100);            // 区間2 開始
  go_Right(150, 600);      // ←90度になる時間を自分でさがそう
  stop_Stop(300);

  beep(3, 100);            // 区間3 開始
  go_Advance(150, 1000);
  stop_Stop(300);

  // ここから先は自分で書き足していこう
}

void loop() {
}
