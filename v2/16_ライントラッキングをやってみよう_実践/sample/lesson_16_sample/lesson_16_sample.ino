#include "motor_driver.h"

//**********5チャンネルIRセンサー接続**********//
#define ir1 A0   // 左端
#define ir2 A1   // 左
#define ir3 A2   // 中央
#define ir4 A3   // 右
#define ir5 A4   // 右端

#define SPEED      120   // まっすぐ進むときの速さ
#define TURN_SPEED 150   // 曲がるときの速さ

void setup() {
  init_GPIO();

  pinMode(ir1, INPUT);
  pinMode(ir2, INPUT);
  pinMode(ir3, INPUT);
  pinMode(ir4, INPUT);
  pinMode(ir5, INPUT);

  Serial.begin(9600);
  beep(1, 200);          // 準備できたよの合図
}

void loop() {
  //センサー値の読み取り（黒い線の上なら 0）
  int s1 = digitalRead(ir1);  //左端のセンサ
  int s2 = digitalRead(ir2);  //左センサー
  int s3 = digitalRead(ir3);  //中央センサ
  int s4 = digitalRead(ir4);  //右センサー
  int s5 = digitalRead(ir5);  //右端のセンサ

  // シリアルモニターで見えるように表示（黒が1に見えるよう反転）
  Serial.print(!s1);
  Serial.print(!s2);
  Serial.print(!s3);
  Serial.print(!s4);
  Serial.println(!s5);

  if (s3 == 0) {
    // 中央が線の上 → まっすぐ進む
    go_Advance(SPEED, 0);
  }
  else if (s2 == 0) {
    // 少し左にずれた → 進みながら、左をおそくしてゆるく左へ
    go_Advance(SPEED, 0);
    set_Motorspeed(80, TURN_SPEED);
  }
  else if (s1 == 0) {
    // かなり左にずれた → 大きく左へ
    go_Left(TURN_SPEED, 0);
  }
  else if (s4 == 0) {
    // 少し右にずれた → 進みながら、右をおそくしてゆるく右へ
    go_Advance(SPEED, 0);
    set_Motorspeed(TURN_SPEED, 80);
  }
  else if (s5 == 0) {
    // かなり右にずれた → 大きく右へ
    go_Right(TURN_SPEED, 0);
  }
  else {
    // どのセンサーも線を見ていない → コースから外れた
    stop_Stop();
    beep(3, 80);       // 「外れたよ」の合図
  }
}
