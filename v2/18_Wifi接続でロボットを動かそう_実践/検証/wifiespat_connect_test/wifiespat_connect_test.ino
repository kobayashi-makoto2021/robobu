/*
 * 検証3 WiFiEspAT（後継ライブラリ 1.4.x）でつながるか
 *
 * WiFiEspAT は ATファームウェア 1.7 以降でないと動かない。
 * 検証1で調べたバージョンが 1.7 より古ければ、この検証は失敗して当然。
 * その場合、乗り換えには全シールドのファームウェア書き換えが必要になる。
 *
 * 準備：
 *   1. ライブラリマネージャで「WiFiEspAT」を検索してインストール
 *      （WiFiEsp とは別のライブラリ。両方入れておいても競合しない）
 *   2. WiFiEspAT は「ESP側に保存された接続設定」を使う作りなので、
 *      付属のスケッチ例 File > 例 > WiFiEspAT > Tools > SetupWiFiConnection を
 *      先に一度実行して、SSIDとパスワードをESPに覚えさせる
 *
 * 見るところ：
 *   シリアルモニタに IP Address: が出れば成功。
 */
#include <WiFiEspAT.h>
#include <SoftwareSerial.h>

#define SOFT_RX 4
#define SOFT_TX 5

SoftwareSerial espSerial(SOFT_RX, SOFT_TX);

void setup()
{
  Serial.begin(9600);
  while (!Serial);

  espSerial.begin(9600);
  WiFi.init(espSerial);

  if (WiFi.status() == WL_NO_MODULE) {
    Serial.println("ESPモジュールと通信できません");
    Serial.println("→ ボーレート（9600）と配線 D4/D5 を確認");
    while (true);
  }

  Serial.println("ESPモジュールを見つけました");

  // SetupWiFiConnection で覚えさせた設定で自動的につながるのを待つ
  int status = WiFi.waitForConnectResult();

  if (status == WL_CONNECTED) {
    Serial.println("You're connected to the network");
    Serial.print("IP Address: ");
    Serial.println(WiFi.localIP());
  } else {
    Serial.print("接続できませんでした status=");
    Serial.println(status);
    Serial.println("→ SetupWiFiConnection を実行したか確認");
    Serial.println("→ ATファームウェアが 1.7 より古い可能性");
  }
}

void loop()
{
}
