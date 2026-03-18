#include <WiFiEsp.h>
#include <WiFiEspUdp.h>
#include <SoftwareSerial.h>

SoftwareSerial Serial1(4, 5);  // WiFiシールド RX=D4, TX=D5

// ★ここを自分のWiFi環境に書き換えよう
char ssid[] = "YOUR_SSID";      // WiFiのネットワーク名
char pass[] = "YOUR_PASSWORD";  // WiFiのパスワード

WiFiEspUDP Udp;
unsigned int localPort = 8888;  // 受信するポート番号
char packetBuffer[255];

int status = WL_IDLE_STATUS;

void setup() {
  Serial.begin(9600);
  Serial1.begin(9600);
  WiFi.init(&Serial1);

  Serial.println("WiFiに接続しています...");

  while (status != WL_CONNECTED) {
    status = WiFi.begin(ssid, pass);
    delay(1000);
  }

  Serial.print("接続完了！IPアドレス: ");
  Serial.println(WiFi.localIP());

  Udp.begin(localPort);
  Serial.println("UDP待受開始（ポート8888）...");
}

void loop() {
  int packetSize = Udp.parsePacket();
  if (packetSize) {
    Serial.print("受信データ（");
    Serial.print(packetSize);
    Serial.print("バイト）: ");

    int len = Udp.read(packetBuffer, 255);
    if (len > 0) {
      packetBuffer[len] = 0;
    }
    Serial.println(packetBuffer);
  }
}
