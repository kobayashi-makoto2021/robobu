// =============================================
//  http.h  Wi-Fi・HTTP通信
//  ブラウザから届いた命令（リクエスト）を読んで、ロボットを動かす。
//  ほかの .h の関数を全部呼ぶので、いちばん最後に読み込む。
// =============================================
#pragma once

WiFiEspServer server(80);  // 80番の入口で、ブラウザからのリクエストを待つ

// ---- Wi-Fiにつないで、Webサーバーを始める（setup() で1回だけ呼ぶ）----
void http_init()
{
  // Wi-Fiシールドとの通信の準備（レッスン18と同じ）
  espSerial.begin(115200);
  espSerial.print("AT+CIOBAUD=9600\r\n");
  espSerial.write("AT+RST\r\n");
  espSerial.begin(9600);
  WiFi.init(&espSerial);

  if (WiFi.status() == WL_NO_SHIELD) {
    Serial.println("Wi-Fiシールドが見つかりません");
    while (true);  // ここで止まる
  }

  // 教室のWi-Fiにつながるまで、くり返す
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print("Wi-Fiに接続中: ");
    Serial.println(WIFI_SSID);
    WiFi.begin(WIFI_SSID, WIFI_PASS);
  }

  server.begin();  // Webサーバーを始める
  Serial.print("ブラウザで開くアドレス → http://");
  Serial.println(WiFi.localIP());
}

// ---- 安全のため：命令を受け取ってから moveTime ミリ秒たったら止まる ----
unsigned int moveTime = 500;        // 1回に動く時間（ミリ秒）。はじめは500＝0.5秒。画面のスライダーで変わる
bool moving = false;                // 今、動いているか
unsigned long moveStart = 0;        // 命令を受け取った時刻（ミリ秒）

void checkTimer()
{
  if (moving && millis() - moveStart >= moveTime) {
    stop_Stop();
    moving = false;
    Serial.print("止めました: ");
    Serial.print(millis() - moveStart);   // 実際に動いた時間
    Serial.println(" ミリ秒動いた");
  }
}

// ---- 操作画面のHTMLを送る（「/」を開いたときだけ）----
// HTMLの中身は page.h に書いてある
void sendPage(WiFiEspClient &client)
{
  // 1. ヘッダー：「うまくいったよ（200 OK）。中身はHTMLだよ」
  client.print(F(
    "HTTP/1.1 200 OK\r\n"
    "Content-Type: text/html; charset=UTF-8\r\n"
    "Connection: close\r\n"
    "\r\n"));
  // 2. 本体：page.h のHTML（前半 → 今の moveTime → 後半 の順に送る）
  client.print((const __FlashStringHelper*)PAGE_TOP);
  client.print(moveTime);
  client.print((const __FlashStringHelper*)PAGE_BOTTOM);
}

// ---- 命令を受け取ったときの返事を送る ----
// 204 No Content：「受け取ったよ。送る中身はないよ」→ ブラウザは今の画面のまま
void sendOK(WiFiEspClient &client)
{
  client.print(F(
    "HTTP/1.1 204 No Content\r\n"
    "Connection: close\r\n"
    "\r\n"));
}

// ---- リクエストの1行目から、命令の1文字を取り出す ----
// 例：「GET /M HTTP/1.1」→ 'M'（/ のすぐ後ろの1文字）
//     「GET / HTTP/1.1」→ 0（命令なし。操作画面を開いただけ）
char getCommand(String request)
{
  int slash = request.indexOf('/');   // 1つ目の / の場所
  char cmd = request.charAt(slash + 1);
  if (cmd == ' ') return 0;           // / のすぐ後ろが空白なら、命令なし
  return cmd;
}

// ---- スライダーから届いた時間を読んで、moveTime を変える ----
// 例：「GET /T800 HTTP/1.1」→ 800
void setMoveTime(String request)
{
  int slash = request.indexOf('/');
  int space = request.indexOf(' ', slash);
  int value = request.substring(slash + 2, space).toInt();  // T のうしろの数字
  if (value >= 100 && value <= 2000) {
    moveTime = value;
    Serial.print("動く時間を変えました: ");
    Serial.println(moveTime);
  }
}

// ---- 命令の1文字に合わせて、ロボットを動かす ----
// bluetooth.h の switch 文と同じ。アプリと同じ文字を使っている。
// モーターの動かし方は motor.h の関数を呼ぶだけ。ここでは作り直さない。
void doCommand(char cmd)
{
  switch (cmd)
  {
    case 'M':  go_Advance(); break;
    case 'L':  go_Left(); break;
    case 'R':  go_Right(); break;
    case 'B':  go_Back(); break;
    case 'X':  back_Left(); break;
    case 'Y':  back_Right(); break;
    case 'F':  buttonState=1;shoot();break;
    case 'E': stop_Stop() ;buzz_OFF();break;
    case 'J': stop_Stop() ;break;
    default:break;
  }
  moving = true;          // 時計をスタート
  moveStart = millis();
  Serial.print("動き始めました: ");
  Serial.print(moveTime);
  Serial.println(" ミリ秒たったら止めます");
}

// ---- ブラウザからリクエストが来ていたら受け取って、返事をする（loop() で毎回呼ぶ）----
void do_Http_Tick()
{
  checkTimer();  // 時間が来ていたら止める

  WiFiEspClient client = server.available();  // ブラウザが来ているか見る
  if (!client) return;                         // 来ていなければ何もしない

  String request = "";      // リクエストの1行目（例：GET /M HTTP/1.1）
  bool firstLine = true;    // 今、1行目を読んでいるか
  bool lineIsBlank = true;  // 今の行が、まだ空っぽか

  while (client.connected()) {
    checkTimer();  // リクエストを読んでいる間も、時間が来ていたら止める
    if (client.available()) {
      char c = client.read();

      // 1行目だけを request にためる
      if (firstLine && c != '\r' && c != '\n' && request.length() < 40) {
        request += c;
      }

      // 1行目を読み終わったら、すぐに命令を実行する（残りの行を読み終わるのを待たない）
      if (c == '\n' && firstLine) {
        Serial.println(request);
        char cmd = getCommand(request);
        if (cmd == 'T') setMoveTime(request);  // スライダーの時間
        else if (cmd != 0) doCommand(cmd);     // ロボットへの命令
      }

      // 空っぽの行が来たら、リクエストはおしまい → 返事をする
      if (c == '\n' && lineIsBlank) {
        if (getCommand(request) == 0) {
          sendPage(client);   // 「/」を開いたときだけ、操作画面のHTMLを送る
        } else {
          sendOK(client);     // 命令のときは、短い返事だけ送る
        }
        break;
      }

      if (c == '\n') {
        firstLine = false;   // 2行目からは読み飛ばす
        lineIsBlank = true;
      } else if (c != '\r') {
        lineIsBlank = false;
      }
    }
  }
  delay(10);       // ブラウザが受け取るのを少し待つ
  checkTimer();    // 返事を送っている間に時間が来ていたら止める
  client.stop();   // 通信を終わる
}
