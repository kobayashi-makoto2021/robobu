#include <IRremote.h>  // IRRemote.hをインクルード
const int irReceiverPin = 3;  ///受信モジュールのSIGはpin2
IRrecv irrecv(irReceiverPin); //IRrecvタイプの変数を作成します
decode_results results;    // 結果

void setup(){
  Serial.begin(9600);    //シリアルを初期化し、ボーレートは9600に設定する
  pinMode(3,OUTPUT);
  irrecv.enableIRIn();   // 赤外線受信機モジュールを有効にする
  Serial.print("赤外線モジュールサンプルプログラムスタート\n");
}

void loop(){
  if (irrecv.decode(&results)){ //赤外線受信機モジュールの受信データ
    if(results.value==0x16726215){
      digitalWrite(3, HIGH);
      Serial.print("HIGH\n");
      }
    if(results.value==0x16756815){
      digitalWrite(3, LOW);
      Serial.print("LOW\n");
    }
  }
  delay(600); //600ミリ秒待機
}
