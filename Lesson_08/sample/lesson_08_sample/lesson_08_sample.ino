#include "motor_driver.h"  // 標準モーター制御ライブラリ

#define BUZZ_PIN 13  // ブザー → D13

// ---- ブザー音パターン ----

// 短く1回（前進合図）
void buzz_short() {
  digitalWrite(BUZZ_PIN, LOW);
  delay(100);
  digitalWrite(BUZZ_PIN, HIGH);
}

// 長く1回（後退合図）
void buzz_long() {
  digitalWrite(BUZZ_PIN, LOW);
  delay(400);
  digitalWrite(BUZZ_PIN, HIGH);
}

// 2回（右折合図）
void buzz_twice() {
  buzz_short(); delay(100);
  buzz_short();
}

// 3回（左折合図）
void buzz_triple() {
  buzz_short(); delay(100);
  buzz_short(); delay(100);
  buzz_short();
}

// ---- 音付き移動関数 ----

void move_forward(int speed = 200, int time = 0) {
  buzz_short();          // 前進：短く1回
  go_Advance(speed, time);
}

void move_back(int speed = 200, int time = 0) {
  buzz_long();           // 後退：長く1回
  go_Back(speed, time);
}

void turn_right(int speed = 200, int time = 0) {
  buzz_twice();          // 右折：2回
  go_Right(speed, time);
}

void turn_left(int speed = 200, int time = 0) {
  buzz_triple();         // 左折：3回
  go_Left(speed, time);
}

// ---- 初期化 / メインループ ----

void setup() {
  init_GPIO();
  pinMode(BUZZ_PIN, OUTPUT);
  digitalWrite(BUZZ_PIN, HIGH);  // 起動時はブザーOFF

  // 動作テスト：各方向に動きながら音で確認しよう
  move_forward(200, 1000);   // 前進 1秒
  move_back(200, 1000);      // 後退 1秒
  turn_right(200, 500);      // 右旋回 0.5秒
  turn_left(200, 500);       // 左旋回 0.5秒
  stop_Stop();
}

void loop() {
}
