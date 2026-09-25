#include <Servo.h>
#include "motor_driver.h"

/* モーターとブザーのピン・関数は motor_driver.h の中にある */

#define LPT 2            // 何回進んだら周りを見わたすか

#define SERVO_PIN    9   // サーボをD9に接続
#define Echo_PIN     2   // 超音波センサーのEchoをD2に接続
#define Trig_PIN    10   // 超音波センサーのTrigをD10に接続

/* ===== ここの数字を調整しよう ===== */
#define FAST_SPEED  250  // 速いほうのモーター速度
#define SPEED       120  // ふつうのモーター速度
#define TURN_SPEED  200  // 曲がるときのモーター速度

const int distancelimit     = 30;  // 前方の壁を「近い」と判断する距離(cm)
const int sidedistancelimit = 30;  // 横の壁を「近い」と判断する距離(cm)
const int turntime = 250;          // 曲がるのにかける時間(ミリ秒)
const int backtime = 300;          // 下がるのにかける時間(ミリ秒)
/* ================================= */

int leftscanval, centerscanval, rightscanval, ldiagonalscanval, rdiagonalscanval;
int distance;
int numcycles = 0;
int thereis;
Servo head;

/*超音波距離の検出*/
int watch()
{
  long echo_distance;
  digitalWrite(Trig_PIN, LOW);
  delayMicroseconds(5);
  digitalWrite(Trig_PIN, HIGH);
  delayMicroseconds(15);
  digitalWrite(Trig_PIN, LOW);
  echo_distance = pulseIn(Echo_PIN, HIGH);
  echo_distance = echo_distance * 0.01657; //物体までの距離は何cmか？
  return round(echo_distance);
}

//右、左、前、左ななめ、右ななめの5方向の距離を測る。
//近いところがあれば、その向きのけたを1にした5けたの文字列を返す。
String watchsurrounding()
{
  int obstacle_status = B100000;

  centerscanval = watch();
  if (centerscanval < distancelimit) {
    stop_Stop();
    beep(1, 100);
    obstacle_status = obstacle_status | B100;
  }
  head.write(120);
  delay(100);
  ldiagonalscanval = watch();
  if (ldiagonalscanval < distancelimit) {
    stop_Stop();
    beep(1, 100);
    obstacle_status = obstacle_status | B1000;
  }
  head.write(170); //注：サーボはこの角度を取ることができないため、180度を使用しませんでした
  delay(300);
  leftscanval = watch();
  if (leftscanval < sidedistancelimit) {
    stop_Stop();
    beep(1, 100);
    obstacle_status = obstacle_status | B10000;
  }

  head.write(90); //サーボを180度全体に動かす場合は、90度を使用します。
  delay(100);
  centerscanval = watch();
  if (centerscanval < distancelimit) {
    stop_Stop();
    beep(1, 100);
    obstacle_status = obstacle_status | B100;
  }
  head.write(40);
  delay(100);
  rdiagonalscanval = watch();
  if (rdiagonalscanval < distancelimit) {
    stop_Stop();
    beep(1, 100);
    obstacle_status = obstacle_status | B10;
  }
  head.write(0);
  delay(100);
  rightscanval = watch();
  if (rightscanval < sidedistancelimit) {
    stop_Stop();
    beep(1, 100);
    obstacle_status = obstacle_status | 1;
  }
  head.write(90); //見回し終える(また前を向く)
  delay(300);

  String obstacle_str = String(obstacle_status, BIN);
  obstacle_str = obstacle_str.substring(1, 6);

  return obstacle_str;
}

void auto_avoidance()   //障害物を感知して回避する
{
  ++numcycles;
  if (numcycles >= LPT) { //LPT回進むごとに、周りに何かあるか確認する
    stop_Stop();
    String obstacle_sign = watchsurrounding(); //5けたの値が、5方向の障害物のようすを表す
    Serial.print("begin str=");
    Serial.println(obstacle_sign);

    if (obstacle_sign == "10000") {
      Serial.println("SLIT right");
      go_Advance(SPEED, 0);
      set_Motorspeed(FAST_SPEED, SPEED);
      delay(turntime);
      stop_Stop();
    }
    else if (obstacle_sign == "00001") {
      Serial.println("SLIT LEFT");
      go_Advance(SPEED, 0);
      set_Motorspeed(SPEED, FAST_SPEED);
      delay(turntime);
      stop_Stop();
    }
    else if (obstacle_sign == "11100" || obstacle_sign == "01000" || obstacle_sign == "11000" || obstacle_sign == "10100" || obstacle_sign == "01100" || obstacle_sign == "00100") {
      Serial.println("hand right");
      go_Right(TURN_SPEED, turntime);
      stop_Stop();
    }
    else if (obstacle_sign == "00010" || obstacle_sign == "00111" || obstacle_sign == "00011" || obstacle_sign == "00101" || obstacle_sign == "00110" || obstacle_sign == "01010") {
      Serial.println("hand left");
      go_Left(TURN_SPEED, turntime);   //左に曲がる
      stop_Stop();
    }
    else if (obstacle_sign == "01111" || obstacle_sign == "10111" || obstacle_sign == "11111") {
      Serial.println("hand back right");
      go_Left(SPEED, 0);
      set_Motorspeed(FAST_SPEED, SPEED);
      delay(backtime);
      stop_Stop();
    }
    else if (obstacle_sign == "11011" || obstacle_sign == "11101" || obstacle_sign == "11110" || obstacle_sign == "01110") {
      Serial.println("hand back left");
      go_Right(SPEED, 0);
      set_Motorspeed(SPEED, FAST_SPEED);
      delay(backtime);
      stop_Stop();
    }
    else Serial.println("no handle");

    numcycles = 0; //数えなおし
  }
  else {
    // 何も問題がなければ先に進む
    go_Advance(SPEED, backtime);
    stop_Stop();
  }

  // 前に何かあるか確認する
  distance = watch();
  if (distance < distancelimit) {
    //前方に障害物があると確信できるまで数える（超音波センサーの誤信号を無視するため）
    Serial.println("final go back");
    go_Right(SPEED, 0);
    set_Motorspeed(SPEED, FAST_SPEED);
    delay(backtime * 3 / 2);
    ++thereis;
  }
  if (distance > distancelimit) {
    thereis = 0;   //数えなおし
  }
  if (thereis > 25) {
    Serial.println("final stop");
    stop_Stop();   //何かが先にあるので、動きを止める
    thereis = 0;
  }
}

void setup()
{
  init_GPIO();       // モーターとブザーの準備

  /*HC-SR04の初期化*/
  pinMode(Trig_PIN, OUTPUT);
  pinMode(Echo_PIN, INPUT);
  digitalWrite(Trig_PIN, LOW);

  delay(1000);
  beep(3, 200);      // ピピピッ

  /*サーボの初期化*/
  head.attach(SERVO_PIN);
  head.write(90);

  /*正面を向いて3秒待機（ホルダーの位置合わせ用）*/
  delay(3000);
  beep(3, 200);      // ピピピッ（合わせ終わりの合図）

  Serial.begin(9600);
}

void loop()
{
  auto_avoidance();
}
