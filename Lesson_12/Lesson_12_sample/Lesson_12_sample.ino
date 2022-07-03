#define speedPinR 9          //PWM右ピン接続
#define RightDirectPin1  12  //右モーター方向ピン1
#define RightDirectPin2  11  //右モーター方向ピン2
#define speedPinL 6          //PWM右ピン接続
#define LeftDirectPin1  7    //左モーター方向ピン
#define LeftDirectPin2  8    //左モーター方向ピン


/*左からD 3、A 1-A 3、D 10に接続します*/
#define RightObstacleSensor 2  //右障害物センサーからD2
#define LeftObstacleSensor 3   //左障害物センサーからD3

#define SPEED   180 //モータ速度
void go_Advance(void)  //前進
{
  digitalWrite(RightDirectPin1, HIGH);
  digitalWrite(RightDirectPin2,LOW);
  digitalWrite(LeftDirectPin1,HIGH);
  digitalWrite(LeftDirectPin2,LOW);
    set_Motorspeed(SPEED,SPEED);
}
void back_Right(void)  //左折
{
  digitalWrite(RightDirectPin1, HIGH);
  digitalWrite(RightDirectPin2,LOW);
  digitalWrite(LeftDirectPin1,LOW);
  digitalWrite(LeftDirectPin2,HIGH);
    set_Motorspeed(SPEED,0);
}
void back_Left(void)  //右折
{
  digitalWrite(RightDirectPin1, LOW);
  digitalWrite(RightDirectPin2,HIGH);
  digitalWrite(LeftDirectPin1,HIGH);
  digitalWrite(LeftDirectPin2,LOW);
    set_Motorspeed(0,SPEED);
}
void go_Back(void)  //後進
{
  digitalWrite(RightDirectPin1, LOW);
  digitalWrite(RightDirectPin2,HIGH);
  digitalWrite(LeftDirectPin1,LOW);
  digitalWrite(LeftDirectPin2,HIGH);
    set_Motorspeed(SPEED,SPEED);
}
void stop_Stop()    //止まる
{
  digitalWrite(RightDirectPin1, LOW);
  digitalWrite(RightDirectPin2,LOW);
  digitalWrite(LeftDirectPin1,LOW);
  digitalWrite(LeftDirectPin2,LOW);
}
/*モーター速度を設定*/
void set_Motorspeed(int speed_L,int speed_R)
{
  analogWrite(speedPinL,speed_L); 
  analogWrite(speedPinR,speed_R);   
}

void setup()
{
 pinMode(speedPinL,OUTPUT); //左モーターPWMピン
 pinMode(speedPinR,OUTPUT); //右モーターPWMピン
 pinMode(RightDirectPin1,OUTPUT); //左モーター方向ピン1
 pinMode(RightDirectPin2,OUTPUT); //左モーター方向ピン2
 pinMode(LeftDirectPin1,OUTPUT);  //右モーター方向ピン1
 pinMode(LeftDirectPin2,OUTPUT);  //右モーター方向ピン2

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
