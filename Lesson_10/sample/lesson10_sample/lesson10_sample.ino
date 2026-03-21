#include <IRremote.hpp>
#include "motor_driver.h"  // 標準モーター制御ライブラリ（ENA=D3, ENB=D6 など）

#define IR_PIN    10  // 赤外線受信モジュールをD10に接続

// リモコンのボタンコード
#define IR_ADVANCE       0x00FF18E7  // 「▲」ボタン
#define IR_BACK          0x00FF4AB5  // 「▼」ボタン
#define IR_RIGHT         0x00FF5AA5  // 「>」ボタン
#define IR_LEFT          0x00FF10EF  // 「<」ボタン
#define IR_STOP          0x00FF38C7  // 「OK」ボタン

// 走行状態を表すenum
enum DN
{
  GO_ADVANCE,  // 前進
  GO_LEFT,     // 左折
  GO_RIGHT,    // 右折
  GO_BACK,     // 後退
  STOP_STOP,
  DEF
} Drive_Num = DEF;

bool stopFlag = true;
bool JogFlag = false;
uint16_t JogTimeCnt = 0;
uint32_t JogTime = 0;

// 赤外線コードを受信して走行状態を更新する
void do_IR_Tick()
{
  if (IrReceiver.decode())
  {
    uint32_t code = IrReceiver.decodedIRData.decodedRawData;
    Serial.print(code, HEX);
    if (code == IR_ADVANCE)
    {
      Drive_Num = GO_ADVANCE;
      Serial.print(" >> GO_ADVANCE");
    }
    else if (code == IR_RIGHT)
    {
      Drive_Num = GO_RIGHT;
      Serial.print(" >> GO_RIGHT");
    }
    else if (code == IR_LEFT)
    {
      Drive_Num = GO_LEFT;
      Serial.print(" >> GO_LEFT");
    }
    else if (code == IR_BACK)
    {
      Drive_Num = GO_BACK;
      Serial.print(" >> GO_BACK");
    }
    else if (code == IR_STOP)
    {
      Drive_Num = STOP_STOP;
      Serial.print(" >> STOP_STOP");
    }
    Serial.println("");
    IrReceiver.resume();
  }
}

// 走行状態に応じてモーターを動かす
void do_Drive_Tick()
{
  switch (Drive_Num)
  {
    case GO_ADVANCE:
      go_Advance(200, 1000);  // ここのパラメータを調整しよう
      JogFlag = true;
      JogTimeCnt = 1;
      JogTime = millis();
      break;
    case GO_LEFT:
      go_Left(200, 1000);  // ここのパラメータを調整しよう
      JogFlag = true;
      JogTimeCnt = 1;
      JogTime = millis();
      break;
    case GO_RIGHT:
      go_Right(200, 1000);  // ここのパラメータを調整しよう
      JogFlag = true;
      JogTimeCnt = 1;
      JogTime = millis();
      break;
    case GO_BACK:
      go_Back(200, 1000);  // ここのパラメータを調整しよう
      JogFlag = true;
      JogTimeCnt = 1;
      JogTime = millis();
      break;
    case STOP_STOP:
      stop_Stop();
      JogTime = 0;
      break;
    default:
      break;
  }
  Drive_Num = DEF;
  if (millis() - JogTime >= 200)
  {
    JogTime = millis();
    if (JogFlag == true)
    {
      stopFlag = false;
      if (JogTimeCnt <= 0)
      {
        JogFlag = false;
        stopFlag = true;
      }
      JogTimeCnt--;
    }
    if (stopFlag == true)
    {
      JogTimeCnt = 0;
      stop_Stop();
    }
  }
}

void setup()
{
  init_GPIO();  // モーターピンを初期化

  // 赤外線受信モジュールを有効にする
  IrReceiver.begin(IR_PIN, ENABLE_LED_FEEDBACK);

  Serial.begin(9600);
  Serial.println("--プログラムスタート！--");
}

void loop()
{
  do_IR_Tick();
  do_Drive_Tick();
}
