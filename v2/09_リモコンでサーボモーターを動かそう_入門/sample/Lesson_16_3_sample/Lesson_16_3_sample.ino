#include <IRremote.hpp>
#include <Servo.h>

#define RIGHT_ARROW   0x5A //時計回りに回転する（▶）
#define LEFT_ARROW    0x10 //反時計回りに回転する（◀）
#define SELECT_BUTTON 0x38 //サーボの回転位置が中心（OK）
#define BUTTON_0 0x98  //ボタン0〜9を押すと、決まった位置に移動します
#define BUTTON_1 0xA2  // 20度ずつ回転
#define BUTTON_2 0x62
#define BUTTON_3 0xE2
#define BUTTON_4 0x22
#define BUTTON_5 0x02
#define BUTTON_6 0xC2
#define BUTTON_7 0xE0
#define BUTTON_8 0xA8
#define BUTTON_9 0x90

int RECV_PIN = 3;       //赤外線受信機のピン
int16_t pos;         // サーボ位置を保存する変数を設定する
Servo servo;

void setup()
{
  Serial.begin(9600);
  IrReceiver.begin(RECV_PIN, ENABLE_LED_FEEDBACK); // 受信機を起動する
  servo.attach(9);     //サーボピン
  pos = 90;               // 中間点90度から開始
  servo.write(pos);     // 初期位置を設定
}

void loop()
{
  if (IrReceiver.decode()) {
    switch (IrReceiver.decodedIRData.command) {  //ボタンに応じてサーボを動かす
      case LEFT_ARROW:    pos = min(180, pos + 5); break;
      case RIGHT_ARROW:   pos = max(0, pos - 5); break;
      case SELECT_BUTTON: pos = 90; break;
      case BUTTON_0:      pos = 0 * 20; break;
      case BUTTON_1:      pos = 1 * 20; break;
      case BUTTON_2:      pos = 2 * 20; break;
      case BUTTON_3:      pos = 3 * 20; break;
      case BUTTON_4:      pos = 4 * 20; break;
      case BUTTON_5:      pos = 5 * 20; break;
      case BUTTON_6:      pos = 6 * 20; break;
      case BUTTON_7:      pos = 7 * 20; break;
      case BUTTON_8:      pos = 8 * 20; break;
      case BUTTON_9:      pos = 9 * 20; break;
    }
    servo.write(pos);
    IrReceiver.resume();
  }
}
