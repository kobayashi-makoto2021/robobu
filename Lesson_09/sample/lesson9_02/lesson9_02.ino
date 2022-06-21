#include <IRremote.h>
const int irReceiverPin =3; //受信モジュールのSIGはpin3
const int buzzerPin = 13;//13ピンをブザーに接続します
IRrecv irrecv(irReceiverPin); //IRrecv タイプの変数を作成します
decode_results results;
void setup()
{
  pinMode(buzzerPin,OUTPUT);//ブザーピンを出力として設定します
  digitalWrite(buzzerPin,HIGH);
  Serial.begin(9600);//irrecvを初期化します。
  irrecv.enableIRIn(); // ir受信機モジュールを有効にする
}
void loop() 
{
  if (irrecv.decode(&results)) //赤外線受信モジュールの受信データ
  { 
    Serial.print("irCode: "); //"irCode: "を送信する出力
    Serial.print(results.value, HEX); //値を16進数で出力します
    Serial.print(", bits: "); //" , bits: " を送信する
    Serial.println(results.bits); //bitsを結果に出力する
    irrecv.resume(); // Receive the next value 
  } 

  if(results.value == 0xFF38C7)//「OK」ボタンを押すと、受信モジュールは0xFF38C7を受信します
  {
    digitalWrite(buzzerPin,LOW);//ブザーのビーブ音（低音）
  }
  else
  {
    digitalWrite(buzzerPin,HIGH);//stop beep
  }
    delay(400); //delay 400ms
}
