float count = 0;

void setup() {
  Serial.begin(9600);
  Serial.println("Yを押してタイマースタート");
}
void loop() {
  if (Serial.available()) {
    char ch = Serial.read();
    if (ch == 'y' ||  ch == 'Y') {
      Serial.println("タイマーON");
      Serial.println("タイマーを止めるにはNを押してください");
      count = 0;
    }
    if (ch == 'n' ||  ch == 'N') {
      Serial.println("タイマーOFF");
      Serial.print(count/10);
      Serial.println(" 秒");
      Serial.println("Yを押してタイマースタート");
      count = 0;
    }
  }
  delay(100);
  count += 1;
}
