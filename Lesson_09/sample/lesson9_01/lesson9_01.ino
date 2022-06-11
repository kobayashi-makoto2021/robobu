const int buzzerPin = 13;//13ピンをブザーに割り当て

void setup() {
    pinMode(buzzerPin,OUTPUT);//ブザーのピン番号を出力に設定
}

void loop() {
    digitalWrite(buzzerPin,LOW);//ブザーのビーブ音（低音）
    delay(1000);                 //200ms待機
    digitalWrite(buzzerPin,HIGH);//ブザーを停止
    delay(1000);                 //200ms待機
}
