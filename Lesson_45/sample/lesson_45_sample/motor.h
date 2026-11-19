// =============================================
//  motor.h  モーターの動作
//  .h では、使う関数を先に書いておく必要がある。
//  そのため set_Motorspeed() をいちばん上に置いている。
// =============================================
#pragma once

/*set motor speed */
void set_Motorspeed(int speed_L,int speed_R)
{
  analogWrite(speedPinRight,speed_R); 
  analogWrite(speedPinLeft,speed_L);   
}

/*motor control*/
void go_Advance(void)  //Forward
{
  digitalWrite(dir1PinRight, HIGH);
  digitalWrite(dir2PinRight,LOW);
  digitalWrite(dir1PinLeft,HIGH);
  digitalWrite(dir2PinLeft,LOW);
  set_Motorspeed(SPEED,SPEED) ;
}
void go_Left()  //Turn left
{
  digitalWrite(dir1PinRight, HIGH);
  digitalWrite(dir2PinRight,LOW);
  digitalWrite(dir1PinLeft,LOW);
  digitalWrite(dir2PinLeft,HIGH);
   set_Motorspeed(0,TURNSPEED) ;
}
void go_Right()  //Turn right
{
  digitalWrite(dir1PinRight, LOW);
  digitalWrite(dir2PinRight,HIGH);
  digitalWrite(dir1PinLeft,HIGH);
  digitalWrite(dir2PinLeft,LOW);
   set_Motorspeed(TURNSPEED,0) ;
}
void go_Back()  //Reverse
{
  digitalWrite(dir1PinRight, LOW);
  digitalWrite(dir2PinRight,HIGH);
  digitalWrite(dir1PinLeft,LOW);
  digitalWrite(dir2PinLeft,HIGH);
   set_Motorspeed(SPEED,SPEED) ;
}
void back_Left()  //Reverse
{
  digitalWrite(dir1PinRight, LOW);
  digitalWrite(dir2PinRight,HIGH);
  digitalWrite(dir1PinLeft,HIGH);
  digitalWrite(dir2PinLeft,LOW);
   set_Motorspeed(0,TURNSPEED) ;
}
void back_Right()  //Reverse
{
  digitalWrite(dir1PinRight, HIGH);
  digitalWrite(dir2PinRight,LOW);
  digitalWrite(dir1PinLeft,LOW);
  digitalWrite(dir2PinLeft,HIGH);
   set_Motorspeed(TURNSPEED,0) ;
}
void stop_Stop()    //Stop
{
  digitalWrite(dir1PinRight, LOW);
  digitalWrite(dir2PinRight,LOW);
  digitalWrite(dir1PinLeft,LOW);
  digitalWrite(dir2PinLeft,LOW);
  set_Motorspeed(0,0);
}

// ---- レッスン45で追加：左右のモーターの速さを、別々に決める ----
// left・right は -255〜255。プラスは前進、マイナスは後退、0は停止。
void drive(int left, int right)
{
  left  = constrain(left,  -255, 255);   // -255〜255 の外に出ないようにする
  right = constrain(right, -255, 255);

  // 右モーターの向き（go_Advance() と同じ向きが前進）
  if (right >= 0) {
    digitalWrite(dir1PinRight, HIGH);
    digitalWrite(dir2PinRight, LOW);
  } else {
    digitalWrite(dir1PinRight, LOW);
    digitalWrite(dir2PinRight, HIGH);
  }

  // 左モーターの向き
  if (left >= 0) {
    digitalWrite(dir1PinLeft, HIGH);
    digitalWrite(dir2PinLeft, LOW);
  } else {
    digitalWrite(dir1PinLeft, LOW);
    digitalWrite(dir2PinLeft, HIGH);
  }

  // 速さは、マイナスを取った大きさ（abs）で決める
  set_Motorspeed(abs(left), abs(right));
}
