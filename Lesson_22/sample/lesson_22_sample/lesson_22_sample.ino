#define BUZZ_PIN 13
#define LED_PIN   7

// ---- 自作関数（音パターン） ----

void pattern_one() {
  // パターン1：ピッ（短く1回）
  digitalWrite(BUZZ_PIN, LOW);  delay(150);
  digitalWrite(BUZZ_PIN, HIGH);
}

void pattern_two() {
  // パターン2：ピピッ（2回）
  for (int i = 0; i < 2; i++) {
    digitalWrite(BUZZ_PIN, LOW);  delay(100);
    digitalWrite(BUZZ_PIN, HIGH); delay(100);
  }
}

void pattern_three() {
  // パターン3：ピピピーッ（3回＋長め）
  for (int i = 0; i < 3; i++) {
    digitalWrite(BUZZ_PIN, LOW);  delay(80);
    digitalWrite(BUZZ_PIN, HIGH); delay(80);
  }
  digitalWrite(BUZZ_PIN, LOW);  delay(400);
  digitalWrite(BUZZ_PIN, HIGH);
}

void led_flash(int times) {
  for (int i = 0; i < times; i++) {
    digitalWrite(LED_PIN, HIGH); delay(100);
    digitalWrite(LED_PIN, LOW);  delay(100);
  }
}

// ---- 初期化 / メインループ ----

void setup() {
  pinMode(BUZZ_PIN, OUTPUT);
  pinMode(LED_PIN, OUTPUT);
  digitalWrite(BUZZ_PIN, HIGH);

  Serial.begin(9600);
  Serial.println("1・2・3を入力してEnterを押してみよう！");
}

void loop() {
  if (Serial.available() > 0) {
    char input = Serial.read();

    switch (input) {
      case '1':
        Serial.println("パターン1！");
        pattern_one();
        led_flash(1);
        break;
      case '2':
        Serial.println("パターン2！");
        pattern_two();
        led_flash(2);
        break;
      case '3':
        Serial.println("パターン3！");
        pattern_three();
        led_flash(3);
        break;
      default:
        Serial.println("1・2・3のどれかを入力してね");
        break;
    }
  }
}
