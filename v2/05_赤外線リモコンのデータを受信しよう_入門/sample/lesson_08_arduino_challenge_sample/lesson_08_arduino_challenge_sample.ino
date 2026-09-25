#include <IRremote.hpp>  // IRremoteライブラリ

const int irReceiverPin = 2;  //受信モジュールを２番ピンに繋げる

#define IR_OK     0x38   //「OK」ボタン
#define IR_SHARP  0xB0   //「#」ボタン

void setup(){
  Serial.begin(9600);    //シリアルを初期化し、ボーレートは9600に設定する
  pinMode(3,OUTPUT);     //LEDを３番ピンに繋げる
  IrReceiver.begin(irReceiverPin, ENABLE_LED_FEEDBACK); //赤外線受信機モジュールを有効にする
  Serial.println("赤外線モジュールチャレンジプログラムスタート");
}

void loop(){
  if (IrReceiver.decode()){  //赤外線を受け取ったら
    Serial.print("IRコード: 0x");
    Serial.println(IrReceiver.decodedIRData.command, HEX); //ボタンの番号を出力する

    //「OK」ボタンが押されたら、LEDが光る
    if(IrReceiver.decodedIRData.command == IR_OK){
      digitalWrite(3, HIGH);
      Serial.println("HIGH");
    }
    //「#」ボタンが押されたら、LEDが消える
    if(IrReceiver.decodedIRData.command == IR_SHARP){
      digitalWrite(3, LOW);
      Serial.println("LOW");
    }
    IrReceiver.resume();// 次の値を受取る
  }
  delay(600); //600ミリ秒待機
}
