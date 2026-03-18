# レッスン20 WiFi通信の基礎を学ぼう
## ArduinoをWiFiでつないでみよう

### このレッスンで身につける力

- [ ] WiFiシールドをArduinoに取り付けられる
- [ ] SSIDとパスワードを設定してWiFiに接続できる
- [ ] UDP通信でデータを送受信できる
- [ ] シリアルモニターで通信データを確認できる

---

### ミッションの準備

#### 0. 必要なハードウェア

- [ ] Osoyoo ロボットカーから **WiFiシールドを取り外した状態**のArduino x1
  （またはWiFiシールドを単独でArduinoに取り付けて使用）
- [ ] USBケーブル x1
- [ ] パソコン x1
- [ ] WiFiが使える環境（ルーターなど）またはタブレット/スマホのアクセスポイント

---

### WiFiってどんなしくみ？

WiFiは**目に見えない電波**を使って、コンピューター同士がデータをやりとりする技術だよ。

- **SSID**（エスエスアイディー）：WiFiネットワークの名前。家のルーターについてるアレ
- **パスワード**：そのネットワークに接続するための合言葉
- **IPアドレス**：ネットワーク内でのロボットの住所（例：192.168.1.XX）
- **UDP**（ユーディーピー）：データを素早く送受信するためのルール

---

### WiFiライブラリをインストールしよう

ArduinoでWiFiを使うには **WiFiEsp** ライブラリが必要だよ。

1. 下のリンクをクリックしてダウンロードしよう
   [WiFiEsp Library](https://osoyoo.com/driver/WiFiEsp-master.zip)

2. Arduino IDE を開いて、**スケッチ → ライブラリをインクルード → .ZIPライブラリを追加** をクリック

3. ダウンロードした ZIP ファイルを選んで追加しよう

---

### ミッションチャレンジ

#### ミッション1：WiFiに接続してIPアドレスを確認しよう

```C++
#include <WiFiEsp.h>
#include <SoftwareSerial.h>

SoftwareSerial Serial1(4, 5);  // WiFiシールド RX=D4, TX=D5

// ★ここを自分のWiFi環境に書き換えよう
char ssid[] = "YOUR_SSID";      // WiFiのネットワーク名
char pass[] = "YOUR_PASSWORD";  // WiFiのパスワード

int status = WL_IDLE_STATUS;

void setup() {
  Serial.begin(9600);    // パソコンとの通信
  Serial1.begin(9600);   // WiFiシールドとの通信
  WiFi.init(&Serial1);

  Serial.println("WiFiに接続しています...");

  // WiFiに接続するまでくり返す
  while (status != WL_CONNECTED) {
    status = WiFi.begin(ssid, pass);
    delay(1000);
  }

  Serial.println("接続成功！");
  Serial.print("IPアドレス: ");
  Serial.println(WiFi.localIP());
}

void loop() {
}
```

- [ ] シリアルモニターに「接続成功！」と表示されたらチェック！
- [ ] IPアドレスが表示されたらチェック！

---

#### ミッション2：UDP でデータを受信してシリアルモニターに表示しよう

```C++
#include <WiFiEsp.h>
#include <WiFiEspUdp.h>
#include <SoftwareSerial.h>

SoftwareSerial Serial1(4, 5);

char ssid[] = "YOUR_SSID";
char pass[] = "YOUR_PASSWORD";

WiFiEspUDP Udp;
unsigned int localPort = 8888;  // 受信するポート番号
char packetBuffer[255];

int status = WL_IDLE_STATUS;

void setup() {
  Serial.begin(9600);
  Serial1.begin(9600);
  WiFi.init(&Serial1);

  while (status != WL_CONNECTED) {
    status = WiFi.begin(ssid, pass);
    delay(1000);
  }

  Serial.print("接続完了！IPアドレス: ");
  Serial.println(WiFi.localIP());

  Udp.begin(localPort);
  Serial.println("UDP待受開始...");
}

void loop() {
  int packetSize = Udp.parsePacket();
  if (packetSize) {
    Serial.print("受信データ（");
    Serial.print(packetSize);
    Serial.print("バイト）: ");

    int len = Udp.read(packetBuffer, 255);
    if (len > 0) {
      packetBuffer[len] = 0;  // 文字列の末尾に終端文字を追加
    }
    Serial.println(packetBuffer);
  }
}
```

> **試してみよう**：タブレットやスマホのUDP送信アプリ（例：UDP Sender/Receiver）を使って、
> Arduinoに文字を送ってみよう。シリアルモニターに表示されるはず！

- [ ] UDPでデータを受信してシリアルモニターに表示できたらチェック！

---

### まとめ

- **WiFiEsp** ：ArduinoでWiFiを使うためのライブラリ
- **SSID / パスワード** ：WiFiネットワークへの接続情報
- **UDP** ：素早くデータをやりとりするための通信方式
- `WiFi.begin(ssid, pass)` ：WiFiに接続する
- `WiFi.localIP()` ：ArduinoのIPアドレスを取得する
- `Udp.parsePacket()` ：受信したパケットのサイズを返す（0なら受信なし）

### 出来たことをチェックしよう

- [ ] WiFiシールドをArduinoに取り付けられる
- [ ] SSIDとパスワードを設定してWiFiに接続できる
- [ ] UDP通信でデータを送受信できる
- [ ] シリアルモニターで通信データを確認できる
