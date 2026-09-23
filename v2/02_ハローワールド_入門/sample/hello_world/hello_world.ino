void setup() {
  // put your setup code here, to run once:
  // (日本語訳)最初に一度だけ動かすプログラムはここに書く
  Serial.begin(9600); // シリアルポートを使うための準備
}
void loop() {
  // put your main code here, to run repeatedly:
  // (日本語訳)繰り返して動かすプログラムはここに書く
  Serial.println("Hello World!");
  //シリアルは「Hello World！」という文字列を出力します
  delay(5000);
  // 5秒待機させます（この数値を変更して時間を設定することができます）
}
