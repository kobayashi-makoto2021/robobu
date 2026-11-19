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

// ---- レスポンス（返事）として、操作画面のHTMLを送る ----
void sendPage(WiFiEspClient &client)
{
  // 1. ヘッダー：「うまくいったよ（200 OK）。中身はHTMLだよ」
  client.print(F(
    "HTTP/1.1 200 OK\r\n"
    "Content-Type: text/html; charset=UTF-8\r\n"
    "Connection: close\r\n"
    "\r\n"));
  // 2. 本体：操作画面のHTML
  client.print(F(
    "<!DOCTYPE html>"
    "<html lang=\"ja\">"
    "<head><meta charset=\"UTF-8\"><title>Robot Controller</title></head>"
    "<body>"
    "<h1>ロボット操作パネル</h1>"
    "<p><a href=\"/forward\">▲ 前進</a></p>"
    "<p><a href=\"/left\">◀ 左</a> "
    "<a href=\"/stop\">■ 停止</a> "
    "<a href=\"/right\">▶ 右</a></p>"
    "<p><a href=\"/back\">▼ 後退</a></p>"
    "</body></html>"));
}

// ---- リクエストの1行目から、パス（/forward など）を取り出す ----
// 例：「GET /forward HTTP/1.1」→「/forward」
String getPath(String request)
{
  int space1 = request.indexOf(' ');               // 1つ目のスペース
  int space2 = request.indexOf(' ', space1 + 1);   // 2つ目のスペース
  return request.substring(space1 + 1, space2);    // そのあいだがパス
}

// ---- パスに合わせて、ロボットを動かす ----
// モーターの動かし方は motor.h の関数を呼ぶだけ。ここでは作り直さない。
void doCommand(String path)
{
  if      (path == "/forward") go_Advance();
  else if (path == "/back")    go_Back();
  else if (path == "/left")    go_Left();
  else if (path == "/right")   go_Right();
  else if (path == "/stop")    stop_Stop();
}

// ---- ブラウザからリクエストが来ていたら受け取って、返事をする（loop() で毎回呼ぶ）----
void do_Http_Tick()
{
  WiFiEspClient client = server.available();  // ブラウザが来ているか見る
  if (!client) return;                         // 来ていなければ何もしない

  String request = "";      // リクエストの1行目（例：GET /forward HTTP/1.1）
  bool firstLine = true;    // 今、1行目を読んでいるか
  bool lineIsBlank = true;  // 今の行が、まだ空っぽか

  while (client.connected()) {
    if (client.available()) {
      char c = client.read();

      // 1行目だけを request にためる
      if (firstLine && c != '\r' && c != '\n' && request.length() < 40) {
        request += c;
      }

      // 空っぽの行が来たら、リクエストはおしまい → 命令を実行して返事をする
      if (c == '\n' && lineIsBlank) {
        Serial.println(request);
        doCommand(getPath(request));
        sendPage(client);
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
  client.stop();   // 通信を終わる
}
