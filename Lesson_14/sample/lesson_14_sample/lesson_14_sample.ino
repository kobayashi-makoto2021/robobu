#include "motor_driver.h"  // 標準モーター制御ライブラリ

#define BUZZ_PIN             13  // ブザー → D13
#define RightObstacleSensor   2  // 右障害物センサー → D2
#define LeftObstacleSensor   A5  // 左障害物センサー → A5

#define SPEED  180  // モーター速度（0〜255）

// 回避ロジック：センサー値に応じて障害物から逃げる
void auto_avoidance() {
  int rightSensor = digitalRead(RightObstacleSensor);  // LOW=物体あり
  int leftSensor  = digitalRead(LeftObstacleSensor);   // LOW=物体あり

  if (rightSensor == LOW && leftSensor == LOW) {
    // 両センサーが検出 → 前方に障害物！後退して回避
    digitalWrite(BUZZ_PIN, LOW);  delay(200);  // 警告音
    digitalWrite(BUZZ_PIN, HIGH);
    go_Back(SPEED, 300);
  }
  else if (rightSensor == HIGH && leftSensor == HIGH) {
    // 何もない → 前進してどんどん進む
    go_Advance(SPEED);
  }
  else if (rightSensor == LOW && leftSensor == HIGH) {
    // 右に障害物 → 左に回避
    go_Left(SPEED);
  }
  else if (rightSensor == HIGH && leftSensor == LOW) {
    // 左に障害物 → 右に回避
    go_Right(SPEED);
  }
}

void setup() {
  init_GPIO();
  pinMode(BUZZ_PIN, OUTPUT);
  digitalWrite(BUZZ_PIN, HIGH);

  pinMode(RightObstacleSensor, INPUT);
  pinMode(LeftObstacleSensor, INPUT);

  Serial.begin(9600);
}

void loop() {
  auto_avoidance();
}
