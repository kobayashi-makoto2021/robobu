#define speedPinR 9          //PWM右ピン接続
#define RightMotorDirPin1  12  //右モーター方向ピン1
#define RightMotorDirPin2  11  //右モーター方向ピン2
#define speedPinL 6          //PWM右ピン接続
#define LeftMotorDirPin1  7    //左モーター方向ピン
#define LeftMotorDirPin2  8    //左モーター方向ピン


/*左からD 3、A 1-A 3、D 10に接続します*/
#define RightObstacleSensor 2  //右障害物センサーからD2
#define LeftObstacleSensor 3   //左障害物センサーからD3

#define SPEED   180 //モータ速度
/***************モーター制御***************/
void stop_Stop(int time = 1000)    //ストップ
{
  digitalWrite(RightMotorDirPin1, LOW);
  digitalWrite(RightMotorDirPin2, LOW);
  digitalWrite(LeftMotorDirPin1, LOW);
  digitalWrite(LeftMotorDirPin2, LOW);
  delay(time);
}

void go_Advance(int speed = 200, int time = 0)  //前に進む関数
{
  digitalWrite(RightMotorDirPin1, HIGH);
  digitalWrite(RightMotorDirPin2, LOW);
  digitalWrite(LeftMotorDirPin1, HIGH);
  digitalWrite(LeftMotorDirPin2, LOW);
  analogWrite(speedPinL, speed);
  analogWrite(speedPinR, speed);
  if (time == 0) {
    ;
  } else {
    delay(time);
    stop_Stop();
  }
}
void go_Left(int speed = 200, int time = 0) //左に旋回する関数
{
  digitalWrite(RightMotorDirPin1, HIGH);
  digitalWrite(RightMotorDirPin2, LOW);
  digitalWrite(LeftMotorDirPin1, LOW);
  digitalWrite(LeftMotorDirPin2, HIGH);
  analogWrite(speedPinL, speed);
  analogWrite(speedPinR, speed);
  if (time == 0) {
    ;
  } else {
    delay(time);
    stop_Stop();
  }
}
void go_Right(int speed = 200, int time = 0) //右に旋回する関数
{
  digitalWrite(RightMotorDirPin1, LOW);
  digitalWrite(RightMotorDirPin2, HIGH);
  digitalWrite(LeftMotorDirPin1, HIGH);
  digitalWrite(LeftMotorDirPin2, LOW);
  analogWrite(speedPinL, speed);
  analogWrite(speedPinR, speed);
  if (time == 0) {
    ;
  } else {
    delay(time);
    stop_Stop();
  }
}
void go_Back(int speed = 200, int time = 0) //後ろに下がる関数
{
  digitalWrite(RightMotorDirPin1, LOW);
  digitalWrite(RightMotorDirPin2, HIGH);
  digitalWrite(LeftMotorDirPin1, LOW);
  digitalWrite(LeftMotorDirPin2, HIGH);
  analogWrite(speedPinL, speed);
  analogWrite(speedPinR, speed);
  if (time == 0) {
    ;
  } else {
    delay(time);
    stop_Stop();
  }
}


void back_Right(int speed = 200, int time = 0)  //左折
{
  digitalWrite(RightMotorDirPin1, HIGH);
  digitalWrite(RightMotorDirPin2,LOW);
  digitalWrite(LeftMotorDirPin1,LOW);
  digitalWrite(LeftMotorDirPin2,HIGH);
  analogWrite(speedPinL, speed);
  analogWrite(speedPinR, speed);
  if (time == 0) {
    ;
  } else {
    delay(time);
    stop_Stop();
  }
}
void back_Left(int speed = 200, int time = 0)  //右折
{
  digitalWrite(RightMotorDirPin1, LOW);
  digitalWrite(RightMotorDirPin2,HIGH);
  digitalWrite(LeftMotorDirPin1,HIGH);
  digitalWrite(LeftMotorDirPin1,LOW);
  analogWrite(speedPinL, speed);
  analogWrite(speedPinR, speed);
  if (time == 0) {
    ;
  } else {
    delay(time);
    stop_Stop();
  }
}

//モーター速度の設定
void set_Motorspeed(int speed_L, int speed_R)
{
  analogWrite(speedPinL, speed_L);
  analogWrite(speedPinR, speed_R);
}


void setup()
{
 pinMode(speedPinL,OUTPUT); //左モーターPWMピン
 pinMode(speedPinR,OUTPUT); //右モーターPWMピン
 pinMode(RightMotorDirPin1,OUTPUT); //左モーター方向ピン1
 pinMode(RightMotorDirPin2,OUTPUT); //左モーター方向ピン2
 pinMode(LeftMotorDirPin1,OUTPUT);  //右モーター方向ピン1
 pinMode(LeftMotorDirPin2,OUTPUT);  //右モーター方向ピン2

  /*障害物センサ初期設定 */
 pinMode(RightObstacleSensor,INPUT); 
 pinMode(LeftObstacleSensor,INPUT); 
 Serial.begin(9600);
}

void auto_following(){
 int IRvalueLeft= digitalRead(RightObstacleSensor);
 int IRvalueRight=digitalRead(LeftObstacleSensor);
 if (IRvalueLeft==LOW && IRvalueRight==LOW)
 { 
  //両方のセンサーが障害物を検出しました。先に進みます。
      go_Back();  //Turn left
 }
 else  if (IRvalueLeft==HIGH && IRvalueRight==HIGH)
 {
     stop_Stop();   //ストップ
     set_Motorspeed(0,0);
    }
 else if (IRvalueLeft==LOW && IRvalueRight==HIGH)
 { 
  //左センサのみが障害物を検知
      back_Left();  //左折
 }
  else if (IRvalueLeft==HIGH && IRvalueRight==LOW)
 { 
   //右側センサのみが障害物を検知する
      back_Right();  //右折
  
 }
}

void loop(){
 
auto_following();
}
