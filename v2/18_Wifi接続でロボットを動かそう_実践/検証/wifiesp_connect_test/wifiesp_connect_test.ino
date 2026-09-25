/*
 * 検証2 WiFiEsp（ライブラリマネージャ版 2.2.2）でつながるか
 *
 * いまのレッスン18は osoyoo が配っている zip の WiFiEsp を使っている。
 * それをライブラリマネージャの WiFiEsp 2.2.2 に置きかえても、
 * 同じようにつながるかどうかを確かめる。
 *
 * 準備：
 *   ライブラリマネージャで「WiFiEsp」を検索してインストール
 *   （osoyoo の zip 版を先に入れている場合は、そちらを削除しておくこと）
 *
 * 見るところ：
 *   シリアルモニタに IP Address: が出れば成功。
 */
#include <WiFiEsp.h>
#include <SoftwareSerial.h>

#define SOFT_RX 4
#define SOFT_TX 5

SoftwareSerial Serial1(SOFT_RX, SOFT_TX);

char ssid[] = "YOUR_ROUTER_SSID";           // 教室のWiFiの名前
char pass[] = "YOUR_ROUTER_WIFI_PASSWORD";  // そのパスワード

int status = WL_IDLE_STATUS;

void setup()
{
  Serial.begin(9600);

  // レッスン18の本編と同じ手順でESPを初期化する
  Serial1.begin(115200);
  Serial1.print("AT+CIOBAUD=9600\r\n");
  Serial1.write("AT+RST\r\n");
  Serial1.begin(9600);

  WiFi.init(&Serial1);

  if (WiFi.status() == WL_NO_SHIELD) {
    Serial.println("WiFi shield not present");
    while (true);
  }

  while (status != WL_CONNECTED) {
    Serial.print("Attempting to connect to WPA SSID: ");
    Serial.println(ssid);
    status = WiFi.begin(ssid, pass);
  }

  Serial.println("You're connected to the network");
  Serial.print("IP Address: ");
  Serial.println(WiFi.localIP());
}

void loop()
{
}
