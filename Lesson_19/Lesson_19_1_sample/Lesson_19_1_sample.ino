#include <SoftwareSerial.h>// シリアルライブラリをインポートする

SoftwareSerial mySerial(10, 11); // RX, TX
int ledpin = 13; //D13に接続されているLEDの点滅はオン/オフを表示します
int BluetoothData; //コンピューターから与えられたデータ

void setup()
{
  Serial.begin(9600);
  Serial.println("Type AT commands!");
  // put your setup code here, to run once:
  mySerial.begin(9600);
  Serial.println("Bluetooth On please press 1 or 0 blink LED ..");
  pinMode(ledpin, OUTPUT);
}

void loop()
{
  // ここにセットアップコードを入れて、1回実行します:
  if (mySerial.available())
  {
    BluetoothData = mySerial.read();
    if (BluetoothData == '1')
    {
      // if number 1 pressed ....
      digitalWrite(ledpin, 1);
      Serial.println("LED  On D13 ON ! ");
    }
    if (BluetoothData == '0')
    {
      // if number 0 pressed ....
      digitalWrite(ledpin, 0);
      Serial.println("LED  On D13 Off ! ");
    }
  }
  delay(100);// prepare for next data ...
}
