#define LED1 7  // 1つ目のLED → D7
#define LED2 8  // 2つ目のLED → D8

void setup() {
  pinMode(LED1, OUTPUT);
  pinMode(LED2, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  // ミッション1：LED1を5回点滅（for文）
  for (int i = 0; i < 5; i++) {
    digitalWrite(LED1, HIGH);
    delay(200);
    digitalWrite(LED1, LOW);
    delay(200);
  }
  delay(500);

  // ミッション2：カウントアップ（点灯時間がだんだん長くなる）
  for (int i = 0; i < 10; i++) {
    digitalWrite(LED1, HIGH);
    delay(i * 50 + 100);
    digitalWrite(LED1, LOW);
    delay(100);
  }
  delay(500);

  // ミッション3：ネストしたfor文（LED1とLED2を交互に）
  for (int round = 0; round < 3; round++) {
    for (int i = 0; i < 5; i++) {
      digitalWrite(LED1, HIGH);
      delay(100);
      digitalWrite(LED1, LOW);
      delay(100);
    }
    for (int i = 0; i < 5; i++) {
      digitalWrite(LED2, HIGH);
      delay(100);
      digitalWrite(LED2, LOW);
      delay(100);
    }
  }
  delay(500);

  // ミッション4：while文でシリアル入力待ち
  Serial.println("何かキーを入力してEnterを押してね");
  while (Serial.available() == 0) {
    digitalWrite(LED2, HIGH);
    delay(300);
    digitalWrite(LED2, LOW);
    delay(300);
  }
  while (Serial.available() > 0) { Serial.read(); }
  Serial.println("入力されました！");
  delay(1000);
}
