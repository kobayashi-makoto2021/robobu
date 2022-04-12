long val;

void setup() {
  Serial.begin(9600); //データ転送レートを指定
}

void loop() {

  //受信データがある場合if内を処理
  if (Serial.available() > 0) {
    val = Serial.parseInt();    //文字列データを数値に変換
    Serial.println(val);          //一つ目の数字をシリアルモニタに表示
  }

}
