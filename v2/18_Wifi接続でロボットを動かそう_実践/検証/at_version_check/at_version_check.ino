/*
 * ATファームウェアのバージョンを調べる
 *
 * WiFiシールドのESP8266が、どのバージョンのATファームウェアで動いているかを見る。
 *
 * キットは生徒が購入した持ち物なので、買った時期によって
 * バージョンがちがう可能性がある。教室の実機を控えておくと、
 * 「つながらない」相談が来たときの手がかりになる。
 *
 * WiFiにつながらないときの切り分けにも使える。
 * AT に OK が返れば、シールドとは話せている＝原因はその先にある。
 *
 * 使い方：
 *   1. 書き込む
 *   2. シリアルモニタを開き、右下の改行設定を「CRおよびLF」にする
 *   3. 入力らんに AT と打って Enter → OK が返れば通信できている
 *   4. AT+GMR と打って Enter → バージョンが表示される
 */
#include <SoftwareSerial.h>

#define SOFT_RX 4    // Softserial RX port
#define SOFT_TX 5    // Softserial TX port

SoftwareSerial esp(SOFT_RX, SOFT_TX);

// ESP8266側のボーレート。OKが返らないときは 115200 に変えて試す
#define ESP_BAUD 9600

void setup()
{
  Serial.begin(9600);
  esp.begin(ESP_BAUD);

  Serial.println(F("--- ATコマンド確認 ---"));
  Serial.print(F("ESP側のボーレート: "));
  Serial.println(ESP_BAUD);
  Serial.println(F("シリアルモニタの改行を「CRおよびLF」にしてください"));
  Serial.println();
  Serial.println(F("  AT       と入力 → OK が返れば通信できている"));
  Serial.println(F("  AT+GMR   と入力 → ATファームウェアのバージョン"));
  Serial.println(F("  AT+CWMODE_CUR?  と入力 → 応答があれば AT 1.7 以降の可能性"));
  Serial.println();
  Serial.println(F("何も返ってこない/文字化けするときは ESP_BAUD を 115200 にして書き直す"));
  Serial.println(F("----------------------"));
}

void loop()
{
  // ESP → パソコン
  while (esp.available()) {
    Serial.write(esp.read());
  }
  // パソコン → ESP
  while (Serial.available()) {
    esp.write(Serial.read());
  }
}
