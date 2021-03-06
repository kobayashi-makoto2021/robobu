int LEDPin = 13;  //LEDピンを13番に設定　（Arduino本体のLED）
int isObstaclePin = 2;  // 2番ピンを赤外線センサーに接続
int isObstacle = HIGH;  // 障害物が無い場合

void setup() {
  pinMode(isObstaclePin, INPUT);
  pinMode(LEDPin, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  isObstacle = digitalRead(isObstaclePin);
  if (isObstacle == LOW)  //障害物がある場合
  {
    Serial.println("物体を検知しました！！　LEDをオン"); 
    digitalWrite(LEDPin, HIGH); //LEDをON
  }
  else  //障害物がない場合
  {
    Serial.println("物体はありません　LEDオフ");
    digitalWrite(LEDPin, LOW); //LEDをOFF
  }
  delay(200);
}
