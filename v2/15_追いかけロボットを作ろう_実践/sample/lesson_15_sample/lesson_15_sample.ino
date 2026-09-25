#include "motor_driver.h"

#define RightObstacleSensor 2   // 右の障害物センサーは D2
#define LeftObstacleSensor  4   // 左の障害物センサーは D4

#define SPEED 180               // モーターの速さ

void auto_following()
{
  int IRvalueLeft  = digitalRead(LeftObstacleSensor);
  int IRvalueRight = digitalRead(RightObstacleSensor);

  if (IRvalueLeft == LOW && IRvalueRight == LOW) {
    // 両方のセンサーが見つけた → まうしろにある。下がって近づく
    go_Back(SPEED, 0);
  }
  else if (IRvalueLeft == LOW && IRvalueRight == HIGH) {
    // 左だけが見つけた → 左に向きを変える
    go_Left(SPEED, 0);
  }
  else if (IRvalueLeft == HIGH && IRvalueRight == LOW) {
    // 右だけが見つけた → 右に向きを変える
    go_Right(SPEED, 0);
  }
  else {
    // どちらも見つけていない → 止まる
    stop_Stop();
  }
}

void setup()
{
  init_GPIO();
  pinMode(RightObstacleSensor, INPUT);
  pinMode(LeftObstacleSensor, INPUT);
  Serial.begin(9600);
  beep(1, 200);          // 準備できたよの合図
}

void loop()
{
  auto_following();
}
