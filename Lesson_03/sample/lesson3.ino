void setup() {
  pinMode(2, OUTPUT);//LEDピンを出力へ
  Serial.begin(9600); //シリアルを9600バンドに設定する
  while (! Serial); // シリアルの初期化を許可する
  Serial.println("Yもしくはyを入力するとLEDが光るよ！");
}
void loop() {
  if (Serial.available()){
    char ch = Serial.read();
    if(ch=='y'||ch=='Y'){
      digitalWrite(2, HIGH);
      Serial.println("LEDが光りました!!");
      Serial.println("スイッチをオフにする場合はNまたはnを入力するとLEDが消えるよ!");
      }
    if(ch=='n'||ch=='N'){
      digitalWrite(2, LOW);
      Serial.println("LEDが消えました!!");
      Serial.println("スイッチをオンにする場合はYもしくはyを入力するとLEDが光るよ");
    }
  }
  delay(1000);
}