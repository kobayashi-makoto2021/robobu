/*  ___   ___  ___  _   _  ___   ___   ____ ___  ____
   / _ \ /___)/ _ \| | | |/ _ \ / _ \ / ___) _ \|    \
  | |_| |___ | |_| | |_| | |_| | |_| ( (__| |_| | | | |
   \___/(___/ \___/ \__  |\___/ \___(_)____)___/|_|_|_|
                    (____/
   Arduino Smart Car Tutorial Lesson 1
   Tutorial URL http://osoyoo.com/2018/12/07/new-arduino-smart-car-lesson1/
   CopyRight www.osoyoo.com

   After running the code, smart car will go forward 2 seconds, then go backward 2
   seconds, then left turn for 2 seconds then right turn for 2 seconds then stop.

*/
#define speedPinR 9    //  RIGHT PWM pin connect MODEL-X ENA
#define RightMotorDirPin1  12    //Right Motor direction pin 1 to MODEL-X IN1 
#define RightMotorDirPin2  11    //Right Motor direction pin 2 to MODEL-X IN2
#define speedPinL 6    // Left PWM pin connect MODEL-X ENB
#define LeftMotorDirPin1  7    //Left Motor direction pin 1 to MODEL-X IN3 
#define LeftMotorDirPin2  8   //Left Motor direction pin 1 to MODEL-X IN4 


/*motor control*/
void go_Advance(int speed = 200, int time = 0)  //Forward
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
  }
}
void go_Left(int speed = 200, int time = 0) //Turn left
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
  }
}
void go_Right(int speed = 200, int time = 0) //Turn right
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
  }
}
void go_Back(int speed = 200, int time = 0) //Reverse
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
  }
}
void stop_Stop(int time = 1000)    //Stop
{
  digitalWrite(RightMotorDirPin1, LOW);
  digitalWrite(RightMotorDirPin2, LOW);
  digitalWrite(LeftMotorDirPin1, LOW);
  digitalWrite(LeftMotorDirPin2, LOW);
  delay(time);
}
/*set motor speed */
void set_Motorspeed(int speed_L, int speed_R)
{
  analogWrite(speedPinL, speed_L);
  analogWrite(speedPinR, speed_R);
}

//Pins initialize
void init_GPIO()
{
  pinMode(RightMotorDirPin1, OUTPUT);
  pinMode(RightMotorDirPin2, OUTPUT);
  pinMode(speedPinL, OUTPUT);

  pinMode(LeftMotorDirPin1, OUTPUT);
  pinMode(LeftMotorDirPin2, OUTPUT);
  pinMode(speedPinR, OUTPUT);
  stop_Stop();
}

void setup()
{
  init_GPIO();
  // go_Advance(250, 1000);//Forward

  // go_Back(10, 1000);//Reverse

  //   go_Left(150, 600);//Turn left
  digitalWrite(RightMotorDirPin1, HIGH);
  digitalWrite(RightMotorDirPin2, LOW);
  analogWrite(speedPinR, 200);
  delay(1000);
  // go_Right(100, 1000);//Turn right

  stop_Stop();//Stop

}

void loop() {
//   go_Advance(100);//Forward
//   delay(1000);
//   stop_Stop();
//   delay(1000);
}

/* 2022.03.06
 *  開発記録　小林
 *  Arduino Cloudはフリー版は１日のコンパイル時間がトータル200sしかないので、実用に耐えない。Chromebookでは唯一の選択肢なので辛い。
 *  go_Advance, go_Left, go_Rightを改良し、speed、timeを追加
 *  speedは250が上限
 *  timeは0のときは無期限で回転する。
 *  EV3のステアリング、タンクに相当する関数があるとよいと思った。
 *  関数名の命名規則がキャメル式でもスネーク式でもないのが気持ち悪い。
 *  
 */
 
