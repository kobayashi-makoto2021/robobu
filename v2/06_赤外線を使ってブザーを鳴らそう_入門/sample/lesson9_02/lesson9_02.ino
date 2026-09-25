#include <IRremote.hpp>

const int irReceiverPin = 3;  //受信モジュールのSIGはpin3
const int buzzerPin = 13;     //13ピンをブザーに接続します

#define IR_OK 0x38            //「OK」ボタンのIRコード

int lastCommand = 0;          //さいごに押されたボタンをおぼえておく

void setup()
{
  pinMode(buzzerPin,OUTPUT);//ブザーピンを出力として設定します
  digitalWrite(buzzerPin,HIGH);
  Serial.begin(9600);
  //ブザーと同じ13ピンを光らせないように、LEDの合図はオフにする
  IrReceiver.begin(irReceiverPin, DISABLE_LED_FEEDBACK); // ir受信機モジュールを有効にする
}

void loop()
{
  if (IrReceiver.decode()) //赤外線を受け取ったら
  {
    lastCommand = IrReceiver.decodedIRData.command; //押されたボタンをおぼえる
    Serial.print("IRコード: 0x");
    Serial.println(lastCommand, HEX); //値を16進数で出力します
    IrReceiver.resume(); // Receive the next value
  }

  if(lastCommand == IR_OK)//「OK」ボタンを押すと、受信モジュールは0x38を受信します
  {
    digitalWrite(buzzerPin,LOW);//ブザーのビープ音（低音）
  }
  else
  {
    digitalWrite(buzzerPin,HIGH);//stop beep
  }
    delay(400); //delay 400ms
}
