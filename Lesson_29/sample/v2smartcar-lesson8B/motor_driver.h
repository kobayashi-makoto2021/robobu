// motor_driver.h
// ロボット部 標準モーター制御ライブラリ
// 全ロボットレッスンで共通使用する
//
// 【ピン配置】
//   D3  : ENA  右モーターPWM（D9はサーボ用に確保）
//   D6  : ENB  左モーターPWM
//   D7  : IN3  左モーター方向1
//   D8  : IN4  左モーター方向2
//   D11 : IN2  右モーター方向2
//   D12 : IN1  右モーター方向1

#ifndef MOTOR_DRIVER_H
#define MOTOR_DRIVER_H

// ピン番号定義
#define ENA 3   // 右モーターPWM ← 最初からD3に固定（D9はサーボ用に確保）
#define IN1 12  // 右モーター方向ピン1
#define IN2 11  // 右モーター方向ピン2
#define ENB 6   // 左モーターPWM
#define IN3 7   // 左モーター方向ピン1
#define IN4 8   // 左モーター方向ピン2

// ピンの初期化（setup()の中で呼び出す）
void init_GPIO()
{
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(ENA, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
  pinMode(ENB, OUTPUT);
  // 起動時は停止状態にする
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
  analogWrite(ENA, 0);
  analogWrite(ENB, 0);
}

// 停止
// time: 停止後に待機するミリ秒（0なら待機なし）
void stop_Stop(int time = 0)
{
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
  analogWrite(ENA, 0);
  analogWrite(ENB, 0);
  if (time > 0) delay(time);
}

// 前進
// speed: モーター速度（0〜255）
// time:  走行時間（ミリ秒）。0なら走り続ける
void go_Advance(int speed = 200, int time = 0)
{
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
  analogWrite(ENA, speed);
  analogWrite(ENB, speed);
  if (time > 0) {
    delay(time);
    stop_Stop();
  }
}

// 後退
// speed: モーター速度（0〜255）
// time:  走行時間（ミリ秒）。0なら走り続ける
void go_Back(int speed = 200, int time = 0)
{
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
  analogWrite(ENA, speed);
  analogWrite(ENB, speed);
  if (time > 0) {
    delay(time);
    stop_Stop();
  }
}

// 左旋回（右モーター前進・左モーター後退）
// speed: モーター速度（0〜255）
// time:  走行時間（ミリ秒）。0なら走り続ける
void go_Left(int speed = 200, int time = 0)
{
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
  analogWrite(ENA, speed);
  analogWrite(ENB, speed);
  if (time > 0) {
    delay(time);
    stop_Stop();
  }
}

// 右旋回（右モーター後退・左モーター前進）
// speed: モーター速度（0〜255）
// time:  走行時間（ミリ秒）。0なら走り続ける
void go_Right(int speed = 200, int time = 0)
{
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
  analogWrite(ENA, speed);
  analogWrite(ENB, speed);
  if (time > 0) {
    delay(time);
    stop_Stop();
  }
}

// 左右のモーター速度を個別に設定する
// speed_L: 左モーター速度（0〜255）
// speed_R: 右モーター速度（0〜255）
void set_Motorspeed(int speed_L, int speed_R)
{
  analogWrite(ENB, speed_L);
  analogWrite(ENA, speed_R);
}

#endif // MOTOR_DRIVER_H
