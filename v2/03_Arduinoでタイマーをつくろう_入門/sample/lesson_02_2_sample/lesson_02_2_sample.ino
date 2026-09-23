int count = 0;
//整数型の変数countを定義

void setup() {
  Serial.begin(9600);
  Serial.println("Yを押してタイマースタート");
}
void loop() {
  if (Serial.available()) {
  //シリアル信号を受信した場合
    char ch = Serial.read();
    //受信した値を変数に代入
    if (ch == 'y' ||  ch == 'Y') {
    //yまたはYだった場合
      Serial.println("タイマーON");
      Serial.println("タイマーを止めるにはNを押してください");
      count = 0;
      //countに0を代入
    }
    if (ch == 'n' ||  ch == 'N') {
    //nまたはNだった場合
      Serial.println("タイマーOFF");
      Serial.print(count);
      Serial.println(" 秒");
      Serial.println("Yを押してタイマースタート");
      count = 0;
      //countに0を代入
    }
  }
  delay(1000);
  //1秒待機
  count += 1;
  //countに1を足す
  
}
