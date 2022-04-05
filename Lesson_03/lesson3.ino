void setup() {
  pinMode(2, OUTPUT);//LEDピンを出力へ
  Serial.begin(9600); //シリアルを9600バンドに設定する
  while (! Serial); // シリアルの初期化を許可する
  Serial.println("Enter Y to turn on the LED:");
}
void loop() {
  if (Serial.available()) {
    char ch = Serial.read();
    if (ch == 'y' || ch == 'Y') { //キーボードのyもしくはYを押すとLEDが光る
      digitalWrite(2, HIGH);
      Serial.println("You have turned on the LED!!");
      Serial.println("If you want to switch it off, simply enter N or n!");
    }
    if (ch == 'n' || ch == 'N')  { //キーボードのnもしくはNを押すとLEDが光る
      digitalWrite(2, LOW);
      digitalWrite(4, LOW);
      Serial.println("You have turned off the LED!!");
      Serial.println("If you want to switch it on, simply enter Y or y!");
    }
  }
  delay(1000);
}