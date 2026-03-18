#include <SoftwareSerial.h>
#include <Servo.h>

SoftwareSerial BTSerial(4, 5);  // Bluetooth RX=D4, TX=D5
Servo myServo;

#define SERVO_PIN 9  // サーボ → D9

int angle = 90;  // 現在の角度（初期値90°）

void setup() {
  Serial.begin(9600);
  BTSerial.begin(9600);
  myServo.attach(SERVO_PIN);
  myServo.write(angle);  // 起動時は90°（正面向き）

  Serial.println("Bluetooth待受中...");
  Serial.println("0〜180の数字を送信するとサーボが動くよ");
}

void loop() {
  if (BTSerial.available() > 0) {
    String data = BTSerial.readStringUntil('\n');
    data.trim();

    int newAngle = data.toInt();
    newAngle = constrain(newAngle, 0, 180);

    angle = newAngle;
    myServo.write(angle);

    Serial.print("受信: ");
    Serial.print(data);
    Serial.print(" → サーボ角度: ");
    Serial.println(angle);
  }
}
