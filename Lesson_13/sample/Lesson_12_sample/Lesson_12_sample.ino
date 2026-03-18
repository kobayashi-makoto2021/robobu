#include "motor_driver.h"  // 標準モーター制御ライブラリ（ENA=D3, ENB=D6 など）

// 障害物センサーの接続ピン
// 注意：D3はENA（右モーターPWM）に使用するため、左センサーはA5に接続してください
#define RightObstacleSensor  2   // 右障害物センサー → D2
#define LeftObstacleSensor   A5  // 左障害物センサー → A5（D3はモーター制御用）

#define SPEED  180  // モーター速度（0〜255）

// 追従ロジック：センサー値に応じてロボットを動かす
void auto_following()
{
  int rightSensor = digitalRead(RightObstacleSensor);  // LOW=物体あり
  int leftSensor  = digitalRead(LeftObstacleSensor);   // LOW=物体あり

  if (rightSensor == LOW && leftSensor == LOW)
  {
    // 両センサーが物体を検出 → 近づきすぎているので後退
    go_Back(SPEED);
  }
  else if (rightSensor == HIGH && leftSensor == HIGH)
  {
    // 両センサーとも未検出 → 停止して待機
    stop_Stop();
  }
  else if (rightSensor == LOW && leftSensor == HIGH)
  {
    // 右センサーのみ検出 → 右に向けて追いかける
    go_Right(SPEED);
  }
  else if (rightSensor == HIGH && leftSensor == LOW)
  {
    // 左センサーのみ検出 → 左に向けて追いかける
    go_Left(SPEED);
  }
}

void setup()
{
  init_GPIO();  // モーターピンを初期化

  // 障害物センサーの初期設定
  pinMode(RightObstacleSensor, INPUT);
  pinMode(LeftObstacleSensor, INPUT);

  Serial.begin(9600);
}

void loop()
{
  auto_following();
}
