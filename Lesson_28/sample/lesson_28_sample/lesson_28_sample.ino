#include "motor_driver.h"

#define BUZZ_PIN 13
#define RightObstacleSensor 2
#define LeftObstacleSensor  A5

// ---- 音デバッグ関数 ----
void buzz_short() {
  digitalWrite(BUZZ_PIN, LOW);
  delay(100);
  digitalWrite(BUZZ_PIN, HIGH);
  delay(50);
}

void buzz_twice() {
  buzz_short();
  delay(100);
  buzz_short();
}

// ---- 起動時の確認音 ----
void boot_sound() {
  digitalWrite(BUZZ_PIN, LOW);
  delay(200);
  digitalWrite(BUZZ_PIN, HIGH);
  delay(100);
  digitalWrite(BUZZ_PIN, LOW);
  delay(100);
  digitalWrite(BUZZ_PIN, HIGH);
}

void setup() {
  init_GPIO();
  pinMode(BUZZ_PIN, OUTPUT);
  digitalWrite(BUZZ_PIN, HIGH);  // ブザーOFF（Active LOW）

  pinMode(RightObstacleSensor, INPUT);
  pinMode(LeftObstacleSensor,  INPUT);

  Serial.begin(9600);
  boot_sound();  // 起動音
  Serial.println("ロボット起動！");
}

void loop() {
  int right = digitalRead(RightObstacleSensor);
  int left  = digitalRead(LeftObstacleSensor);

  Serial.print("右センサー: "); Serial.print(right);
  Serial.print(" / 左センサー: "); Serial.println(left);

  if (right == LOW && left == LOW) {
    // 両方に障害物 → 後退して左折
    buzz_twice();
    go_Back(180, 500);
    go_Left(180, 400);

  } else if (right == LOW) {
    // 右に障害物 → 左折
    buzz_short();
    go_Left(180, 400);

  } else if (left == LOW) {
    // 左に障害物 → 右折
    buzz_short();
    go_Right(180, 400);

  } else {
    // 障害物なし → 前進
    go_Advance(200, 0);
  }

  delay(100);
}
