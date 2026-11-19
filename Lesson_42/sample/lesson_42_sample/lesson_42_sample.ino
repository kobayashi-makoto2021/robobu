// =============================================
//  lesson_42_sample.ino  メインのファイル
//  レッスン41のプログラムから、通信の部分だけを
//  Bluetooth（bluetooth.h）→ Wi-Fi・HTTP（http.h）に取りかえたもの
//
//  .h ファイルは、#include を書いた順番に読み込まれる。
//  使う関数が先に読み込まれているように、順番に気をつける。
// =============================================
#include <SoftwareSerial.h>
#include <IRremote.h>
#include <WiFiEsp.h>     // ← レッスン42で追加：Wi-Fiシールドを使うライブラリ
#include "config.h"      // ピン番号・定数・チームの設定・Wi-Fiの設定

// ---- 共有するオブジェクト・変数（定義はここ一か所だけ）----
// 下の .h ファイルが使うので、#include より先に書く
SoftwareSerial espSerial(4, 5);  // ← レッスン42で変更：Wi-Fiシールド（ESP8266）とつなぐ RX,TX
IRrecv irrecv(RECV_PIN);
IRsend irsend;
decode_results results;
int buttonState;
int lastButtonState = 0;

// ---- 機能ごとのファイル（この順番が大切）----
#include "motor.h"      // モーターの動作
#include "sound.h"      // ブザー
#include "battle.h"     // 赤外線攻撃・被弾時の処理（motor.h を使う）
#include "hissatsu.h"   // 必殺技（motor.h・sound.h・battle.h を使う）
#include "http.h"       // ← レッスン42で変更：Wi-Fi・HTTP通信（上の全部を使うので最後）

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
  Serial.begin(9600);
  http_init();    // ← レッスン42で変更：Wi-Fiにつないで、Webサーバーを始める

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
  do_Http_Tick();   // ← レッスン42で変更：ブラウザからの命令を見る
}
