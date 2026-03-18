#include <Servo.h>
#include "motor_driver.h"  // 標準モーター制御ライブラリ（ENA=D3, ENB=D6 など）

#define SERVO_PIN  9   // サーボモーターをD9に接続（ENA=D3の代わりにD9を確保）
#define Echo_PIN   2   // 超音波センサー ECHOピン → D2
#define Trig_PIN   10  // 超音波センサー TRIGピン → D10
#define BUZZ_PIN   13  // ブザー → D13

#define LPT           2    // 障害物チェックを行うまでのループ回数
#define FAST_SPEED    250  // 速いモーター速度
#define SPEED         120  // 通常モーター速度
#define TURN_SPEED    200  // 曲がるときのモーター速度
#define BACK_SPEED1   255  // 後退時のモーター速度1
#define BACK_SPEED2   90   // 後退時のモーター速度2

int leftscanval, centerscanval, rightscanval, ldiagonalscanval, rdiagonalscanval;
const int distancelimit     = 30;  // 前方障害物の距離制限（cm）
const int sidedistancelimit = 30;  // 左右障害物の距離制限（cm）
int distance;
int numcycles = 0;
const int turntime = 250;  // 曲がりに費やす時間（ミリ秒）
const int backtime = 300;  // 後退に費やす時間（ミリ秒）
int thereis;

Servo head;

// ブザーを鳴らす
void buzz_ON()
{
  for (int i = 0; i < 100; i++)
  {
    digitalWrite(BUZZ_PIN, LOW);
    delay(2);
    digitalWrite(BUZZ_PIN, HIGH);
    delay(2);
  }
}

// ブザーを止める
void buzz_OFF()
{
  digitalWrite(BUZZ_PIN, HIGH);
}

// 注意音（3回鳴らす）
void atention()
{
  for (int i = 0; i < 3; i++)
  {
    digitalWrite(BUZZ_PIN, LOW);
    delay(200);
    digitalWrite(BUZZ_PIN, HIGH);
    delay(200);
  }
}

void alarm()
{
  buzz_ON();
  buzz_OFF();
}

// 超音波センサーで前方距離を取得する（cm）
int watch()
{
  long echo_distance;
  digitalWrite(Trig_PIN, LOW);
  delayMicroseconds(5);
  digitalWrite(Trig_PIN, HIGH);
  delayMicroseconds(15);
  digitalWrite(Trig_PIN, LOW);
  echo_distance = pulseIn(Echo_PIN, HIGH);
  echo_distance = echo_distance * 0.01657;
  return round(echo_distance);
}

// 5方向をスキャンして障害物の有無を2進数の文字列で返す
String watchsurrounding()
{
  int obstacle_status = B100000;

  centerscanval = watch();
  if (centerscanval < distancelimit) { stop_Stop(); alarm(); obstacle_status = obstacle_status | B100; }

  head.write(120); delay(100);
  ldiagonalscanval = watch();
  if (ldiagonalscanval < distancelimit) { stop_Stop(); alarm(); obstacle_status = obstacle_status | B1000; }

  head.write(170); delay(300);
  leftscanval = watch();
  if (leftscanval < sidedistancelimit) { stop_Stop(); alarm(); obstacle_status = obstacle_status | B10000; }

  head.write(90); delay(100);
  centerscanval = watch();
  if (centerscanval < distancelimit) { stop_Stop(); alarm(); obstacle_status = obstacle_status | B100; }

  head.write(40); delay(100);
  rdiagonalscanval = watch();
  if (rdiagonalscanval < distancelimit) { stop_Stop(); alarm(); obstacle_status = obstacle_status | B10; }

  head.write(0); delay(100);
  rightscanval = watch();
  if (rightscanval < sidedistancelimit) { stop_Stop(); alarm(); obstacle_status = obstacle_status | 1; }

  head.write(90); delay(300);

  String obstacle_str = String(obstacle_status, BIN);
  obstacle_str = obstacle_str.substring(1, 6);
  return obstacle_str;
}

// 障害物を感知して回避する
void auto_avoidance()
{
  ++numcycles;
  if (numcycles >= LPT)
  {
    stop_Stop();
    String obstacle_sign = watchsurrounding();
    Serial.print("begin str=");
    Serial.println(obstacle_sign);

    if (obstacle_sign == "10000") {
      Serial.println("SLIT right");
      set_Motorspeed(SPEED, FAST_SPEED);
      go_Advance();
      delay(turntime);
      stop_Stop();
    }
    else if (obstacle_sign == "00001") {
      Serial.println("SLIT LEFT");
      set_Motorspeed(FAST_SPEED, SPEED);
      go_Advance();
      delay(turntime);
      stop_Stop();
    }
    else if (obstacle_sign == "11100" || obstacle_sign == "01000" || obstacle_sign == "11000" ||
             obstacle_sign == "10100" || obstacle_sign == "01100" || obstacle_sign == "00100") {
      Serial.println("hand right");
      go_Right();
      set_Motorspeed(TURN_SPEED, TURN_SPEED);
      delay(turntime);
      stop_Stop();
    }
    else if (obstacle_sign == "00010" || obstacle_sign == "00111" || obstacle_sign == "00011" ||
             obstacle_sign == "00101" || obstacle_sign == "00110" || obstacle_sign == "01010") {
      Serial.println("hand left");
      go_Left();
      set_Motorspeed(TURN_SPEED, TURN_SPEED);
      delay(turntime);
      stop_Stop();
    }
    else if (obstacle_sign == "01111" || obstacle_sign == "10111" || obstacle_sign == "11111") {
      Serial.println("hand back right");
      go_Left();
      set_Motorspeed(FAST_SPEED, SPEED);
      delay(backtime);
      stop_Stop();
    }
    else if (obstacle_sign == "11011" || obstacle_sign == "11101" ||
             obstacle_sign == "11110" || obstacle_sign == "01110") {
      Serial.println("hand back left");
      go_Right();
      set_Motorspeed(SPEED, FAST_SPEED);
      delay(backtime);
      stop_Stop();
    }
    else Serial.println("no handle");

    numcycles = 0;
  }
  else
  {
    set_Motorspeed(SPEED, SPEED);
    go_Advance();
    delay(backtime);
    stop_Stop();
  }

  distance = watch();
  if (distance < distancelimit) {
    Serial.println("final go back");
    go_Right();
    set_Motorspeed(SPEED, FAST_SPEED);
    delay(backtime * 3 / 2);
    ++thereis;
  }
  if (distance > distancelimit) { thereis = 0; }
  if (thereis > 25) {
    Serial.println("final stop");
    stop_Stop();
    thereis = 0;
  }
}

void setup()
{
  init_GPIO();  // モーターピンを初期化

  // 超音波センサーの初期化
  pinMode(Trig_PIN, OUTPUT);
  pinMode(Echo_PIN, INPUT);

  // ブザーの初期化
  pinMode(BUZZ_PIN, OUTPUT);
  buzz_OFF();

  delay(1000);
  atention();

  digitalWrite(Trig_PIN, LOW);

  // サーボの初期化
  head.attach(SERVO_PIN);
  head.write(90);

  // 正面を向いて3秒待機（調整用）
  delay(3000);
  atention();

  Serial.begin(9600);
}

void loop()
{
  auto_avoidance();
}
