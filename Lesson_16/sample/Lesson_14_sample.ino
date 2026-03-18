#include "motor_driver.h"  // 標準モーター制御ライブラリ（ENA=D3, ENB=D6 など）

// 5チャンネルラインセンサーの接続ピン（A0〜A4）
#define ir1 A0  // 左端センサー
#define ir2 A1  // 左センサー
#define ir3 A2  // 中央センサー
#define ir4 A3  // 右センサー
#define ir5 A4  // 右端センサー

void setup()
{
  init_GPIO();  // モーターピンを初期化

  // ラインセンサーの初期設定
  pinMode(ir1, INPUT);
  pinMode(ir2, INPUT);
  pinMode(ir3, INPUT);
  pinMode(ir4, INPUT);
  pinMode(ir5, INPUT);

  Serial.begin(9600);
}

void loop()
{
  // 各センサーの値を読み取る（0=黒線あり、1=黒線なし）
  int s1 = digitalRead(ir1);  // 左端
  int s2 = digitalRead(ir2);  // 左
  int s3 = digitalRead(ir3);  // 中央
  int s4 = digitalRead(ir4);  // 右
  int s5 = digitalRead(ir5);  // 右端

  // シリアルモニターに表示（!で黒=1、白=0 と読みやすく反転）
  Serial.print(!s1);
  Serial.print(!s2);
  Serial.print(!s3);
  Serial.print(!s4);
  Serial.println(!s5);

  // 中央センサーだけが黒線を検出 → 直進
  if ((s1 == 1) && (s2 == 1) && (s3 == 0) && (s4 == 1) && (s5 == 1))
  {
    go_Advance(120);
  }

  // 左センサーだけが黒線を検出 → 左に曲がる
  else if ((s1 == 1) && (s2 == 0) && (s3 == 1) && (s4 == 1) && (s5 == 1))
  {
    set_Motorspeed(150, 0);  // 左モーター走行・右モーター停止
    go_Left();
  }

  // 左端センサーだけが黒線を検出 → 大きく左に曲がる
  else if ((s1 == 0) && (s2 == 1) && (s3 == 1) && (s4 == 1) && (s5 == 1))
  {
    set_Motorspeed(180, 0);
    go_Left();
  }

  // 右センサーだけが黒線を検出 → 右に曲がる
  else if ((s1 == 1) && (s2 == 1) && (s3 == 1) && (s4 == 0) && (s5 == 1))
  {
    set_Motorspeed(0, 150);  // 左モーター停止・右モーター走行
    go_Right();
  }

  // 右端センサーだけが黒線を検出 → 大きく右に曲がる
  else if ((s1 == 1) && (s2 == 1) && (s3 == 1) && (s4 == 1) && (s5 == 0))
  {
    set_Motorspeed(0, 180);
    go_Right();
  }

  // 中央＋右センサーが黒線を検出 → 右に曲がる
  else if ((s1 == 1) && (s2 == 1) && (s3 == 0) && (s4 == 0) && (s5 == 1))
  {
    set_Motorspeed(0, 150);
    go_Right();
  }

  // 中央＋左センサーが黒線を検出 → 左に曲がる
  else if ((s1 == 1) && (s2 == 0) && (s3 == 0) && (s4 == 1) && (s5 == 1))
  {
    set_Motorspeed(150, 0);
    go_Left();
  }

  // 左3つのセンサーが黒線を検出 → 左に曲がる
  else if ((s1 == 0) && (s2 == 0) && (s3 == 0) && (s4 == 1) && (s5 == 1))
  {
    set_Motorspeed(150, 0);
    go_Left();
  }

  // 右3つのセンサーが黒線を検出 → 右に曲がる
  else if ((s1 == 1) && (s2 == 1) && (s3 == 0) && (s4 == 0) && (s5 == 0))
  {
    set_Motorspeed(0, 150);
    go_Right();
  }

  // すべてのセンサーが黒線上 → 停止
  else if ((s1 == 0) && (s2 == 0) && (s3 == 0) && (s4 == 0) && (s5 == 0))
  {
    stop_Stop();
  }
}
