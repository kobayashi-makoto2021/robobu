// =============================================
//  battle.h  赤外線攻撃・被弾時の処理
//  motor.h（stop_Stop）を使う
//  レッスン42：Bluetooth を使っていた BTSerial.println("DEAD!"); の行を消した
// =============================================
#pragma once

void shoot(){
 Serial.print("shooting bullet :");
 Serial.println(MY_BULLET,HEX);  
 for (int i = 0; i < 3; i++) {
      irsend.sendSony(MY_BULLET, 12); // Sony TV power code
      delay(40);
    }
  
}
void deadAlarm(){
  Serial.println("DEAD!");
    stop_Stop();
 while(1)
 {
 //output an frequency
  for(int i=0;i<80;i++)
  {
    digitalWrite(BUZZ_PIN,LOW);
    delay(1);//wait for 1ms
    digitalWrite(BUZZ_PIN,HIGH);
    delay(1);//wait for 1ms
  }
  //output another frequency
  for(int i=0;i<100;i++)
  {
    digitalWrite(LED_PIN,LOW);
    delay(2);//wait for 2ms
    digitalWrite(LED_PIN,HIGH);
    delay(2);//wait for 2ms
  }
 }
}
