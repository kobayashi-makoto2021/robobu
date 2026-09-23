#include <IRremote.h>  // IRRemote.hをインクルード
const int irReceiverPin = 2;  ///受信モジュールを２番ピンに繋げる
IRrecv irrecv(irReceiverPin); //IRrecvタイプの変数を作成します
decode_results results;    // 結果

void setup(){
  Serial.begin(9600);    //シリアルを初期化し、ボーレートは9600に設定する
  pinMode(3,OUTPUT);     //LEDを３番ピンに繋げる
  irrecv.enableIRIn();   // 赤外線受信機モジュールを有効にする
  Serial.print("赤外線モジュールチャレンジプログラムスタート\n");
}

void loop(){
  if (irrecv.decode(&results)){ //赤外線受信機モジュールの受信データ
    Serial.print("IRコード: ");
    Serial.print(results.value,HEX); //シリアルに値を出力する
    Serial.print(",　ビット: ");  //bitsを送信する         
    Serial.println(results.bits); //bitsを結果に出力する
    
    if(results.value==0xFF38C7){
      digitalWrite(3, HIGH);
      Serial.print("HIGH\n");
      }
    if(results.value==0xFFB04F){
      digitalWrite(3, LOW);
      Serial.print("LOW\n");
    }
    irrecv.resume();// 次の値を受取る
  }
  delay(600); //600ミリ秒待機
}
