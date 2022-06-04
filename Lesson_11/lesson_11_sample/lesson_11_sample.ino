int buzzerPin = 3;  //3番ピンをブザーに接続
int isObstaclePin = 2;  // 2番ピンを赤外線センサーに接続
int isObstacle = HIGH;  // 障害物が無い場合

void setup() {
  pinMode(buzzerPin, OUTPUT);
  pinMode(isObstaclePin, INPUT);
  digitalWrite(buzzerPin, HIGH);
  Serial.begin(9600);
}

void loop() {
  isObstacle = digitalRead(isObstaclePin);
  if (isObstacle == LOW)  //障害物がある場合
  {
    Serial.println("OBSTACLE!!, OBSTACLE!!"); //Obstacleは「障害物」の意味
    digitalWrite(buzzerPin, LOW);
  }
  else  //障害物がない場合
  {
    Serial.println("clear");
    digitalWrite(buzzerPin, HIGH); //stop beep

  }
  delay(200);
}
