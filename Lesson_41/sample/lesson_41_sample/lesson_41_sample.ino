// =============================================
//  lesson_41_sample.ino  メインのファイル
//  共通の読み込み、共有する変数、setup()、loop() だけを置く
//
//  .h ファイルは、#include を書いた順番に読み込まれる。
//  使う関数が先に読み込まれているように、順番に気をつける。
// =============================================
#include <SoftwareSerial.h>
#include <IRremote.h>
#include "config.h"      // ピン番号・定数・チームの設定

// ---- 共有するオブジェクト・変数（定義はここ一か所だけ）----
// 下の .h ファイルが使うので、#include より先に書く
SoftwareSerial BTSerial(4, 5);  //RX,TX
IRrecv irrecv(RECV_PIN);
IRsend irsend;
decode_results results;
int buttonState;

char buffUART[MAX_PACKETSIZE];
unsigned int buffUARTIndex = 0;
unsigned long preUARTTick = 0;
int lastButtonState = 0;

// ---- 機能ごとのファイル（この順番が大切）----
#include "motor.h"      // モーターの動作
#include "sound.h"      // ブザー
#include "battle.h"     // 赤外線攻撃・被弾時の処理（motor.h を使う）
#include "hissatsu.h"   // 必殺技（motor.h・sound.h・battle.h を使う）
#include "bluetooth.h"  // Bluetooth通信（上の全部を使うので最後）

void setup()
{
  irrecv.enableIRIn(); // Start the receiver
  pinMode(LED_PIN, OUTPUT);
  pinMode(dir1PinRight, OUTPUT);
  pinMode(dir2PinRight, OUTPUT);
  pinMode(speedPinRight, OUTPUT);
  pinMode(dir1PinLeft, OUTPUT);
  pinMode(dir2PinLeft, OUTPUT);
  pinMode(speedPinLeft, OUTPUT);
  stop_Stop();
  pinMode(BUZZ_PIN, OUTPUT);
  buzz_OFF();
  Serial.begin(9600);//In order to fit the Bluetooth module's default baud rate, only 9600
  BTSerial.begin(9600);

}

void loop()
{
  if (buttonState) {
    buttonState=0;
      irrecv.enableIRIn(); // Start the receiver
      irrecv.resume();
  }
  else  if (irrecv.decode(&results)) {


  //If got shoot by enemy, dead freeze and alarm
  int data=results.value;
    Serial.print("ir code:");
    Serial.println(data);

    if(data==IR_BULLET)
    {
      deadAlarm();
    }


    irrecv.resume(); // resume receiver
  }
  lastButtonState = buttonState;
  do_Uart_Tick();
}
