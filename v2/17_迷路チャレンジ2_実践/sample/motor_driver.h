/*
 * motor_driver.h  ロボ部 共通モーター制御ライブラリ
 *
 * 実践10・11（ロボットカーを組み立てよう）で導入し、
 * 以降すべてのロボットレッスンで #include して使う。
 *
 * 使い方：
 *   スケッチと同じフォルダに motor_driver.h を置いて、先頭に次の1行を書く。
 *     #include "motor_driver.h"
 *   setup() の最初で init_GPIO(); を呼ぶ。
 *
 * ------------------------------------------------------------------
 * ⚠ ピン配置について（重要）
 *
 *   右モーターのPWM（ENA）は D3 を使う。
 *   旧教材では D9 だったが、D9 はサーボモーター用に空けておく。
 *   （実践17の迷路チャレンジ2でサーボを使うため）
 *
 *   配線するときは ENA を D3 につなぐこと。
 * ------------------------------------------------------------------
 */

#ifndef MOTOR_DRIVER_H
#define MOTOR_DRIVER_H

// ===== ピンの設定 =====
#define speedPinR          3   // 右モーターのPWM（ENA）※D9から変更
#define RightMotorDirPin1  12  // 右モーターの信号ピン1（IN1）
#define RightMotorDirPin2  11  // 右モーターの信号ピン2（IN2）
#define speedPinL          6   // 左モーターのPWM（ENB）
#define LeftMotorDirPin1   7   // 左モーターの信号ピン1（IN3）
#define LeftMotorDirPin2   8   // 左モーターの信号ピン2（IN4）
#define BUZZ_PIN           13  // ブザー

// 空けてあるピン： D9（サーボ用）、D2・D4・D5・D10（センサー用）


// ===== モーターの制御 =====

// 前に進む   speed:0〜255   time:0ならそのまま進み続ける
void go_Advance(int speed = 200, int time = 0)
{
  digitalWrite(RightMotorDirPin1, HIGH);
  digitalWrite(RightMotorDirPin2, LOW);
  digitalWrite(LeftMotorDirPin1, HIGH);
  digitalWrite(LeftMotorDirPin2, LOW);
  analogWrite(speedPinL, speed);
  analogWrite(speedPinR, speed);
  if (time != 0) {
    delay(time);
  }
}

// 後ろに下がる
void go_Back(int speed = 200, int time = 0)
{
  digitalWrite(RightMotorDirPin1, LOW);
  digitalWrite(RightMotorDirPin2, HIGH);
  digitalWrite(LeftMotorDirPin1, LOW);
  digitalWrite(LeftMotorDirPin2, HIGH);
  analogWrite(speedPinL, speed);
  analogWrite(speedPinR, speed);
  if (time != 0) {
    delay(time);
  }
}

// 左に旋回する
void go_Left(int speed = 200, int time = 0)
{
  digitalWrite(RightMotorDirPin1, HIGH);
  digitalWrite(RightMotorDirPin2, LOW);
  digitalWrite(LeftMotorDirPin1, LOW);
  digitalWrite(LeftMotorDirPin2, HIGH);
  analogWrite(speedPinL, speed);
  analogWrite(speedPinR, speed);
  if (time != 0) {
    delay(time);
  }
}

// 右に旋回する
void go_Right(int speed = 200, int time = 0)
{
  digitalWrite(RightMotorDirPin1, LOW);
  digitalWrite(RightMotorDirPin2, HIGH);
  digitalWrite(LeftMotorDirPin1, HIGH);
  digitalWrite(LeftMotorDirPin2, LOW);
  analogWrite(speedPinL, speed);
  analogWrite(speedPinR, speed);
  if (time != 0) {
    delay(time);
  }
}

// 止まる
void stop_Stop(int time = 0)
{
  digitalWrite(RightMotorDirPin1, LOW);
  digitalWrite(RightMotorDirPin2, LOW);
  digitalWrite(LeftMotorDirPin1, LOW);
  digitalWrite(LeftMotorDirPin2, LOW);
  if (time != 0) {
    delay(time);
  }
}

// 左右のモーターの速さを別々に設定する（カーブしたいときに使う）
void set_Motorspeed(int speed_L, int speed_R)
{
  analogWrite(speedPinL, speed_L);
  analogWrite(speedPinR, speed_R);
}


// ===== ブザーの制御 =====
// ロボットが「いまどの処理をしているか」を音で知らせる。
// うまく動かないときの原因さがしに使う。

// ブザーを鳴らす
void buzz_On()
{
  digitalWrite(BUZZ_PIN, LOW);   // このブザーは LOW で鳴る
}

// ブザーを止める
void buzz_Off()
{
  digitalWrite(BUZZ_PIN, HIGH);
}

// times回だけ「ピッ」と鳴らす   ms:1回の長さ
void beep(int times = 1, int ms = 100)
{
  for (int i = 0; i < times; i++) {
    buzz_On();
    delay(ms);
    buzz_Off();
    delay(ms);
  }
}


// ===== 初期化 =====
// setup() の最初に必ず呼ぶこと
void init_GPIO()
{
  pinMode(RightMotorDirPin1, OUTPUT);
  pinMode(RightMotorDirPin2, OUTPUT);
  pinMode(speedPinR, OUTPUT);

  pinMode(LeftMotorDirPin1, OUTPUT);
  pinMode(LeftMotorDirPin2, OUTPUT);
  pinMode(speedPinL, OUTPUT);

  pinMode(BUZZ_PIN, OUTPUT);
  buzz_Off();

  stop_Stop();
}

#endif
