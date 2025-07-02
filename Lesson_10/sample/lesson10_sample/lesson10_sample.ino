#include <IRremote.h>  
#define IR_PIN    10 //赤外線レシーバ信号ピンはArduinoピンD 10に接続 
 IRrecv IR(IR_PIN);  //  IRrecvオブジェクトIRリモコンからコードを取得する
 decode_results IRresults;   

#define speedPinR 9    //  右側のPWM信号を送信するピンの設定
#define RightMotorDirPin1  12    //右のモーターの信号ピン1の設定 
#define RightMotorDirPin2  11    //右のモーターの信号ピン2の設定
#define speedPinL 6    // 左のPWM信号を送信するピンの設定
#define LeftMotorDirPin1  7    //左のモーターの信号ピン1の設定
#define LeftMotorDirPin2  8   //左のモーターの信号ピン2の設定

 #define IR_ADVANCE       0x00FF18E7       //IRコントローラー 「▲」 ボタンのコード
 #define IR_BACK          0x00FF4AB5       //IRコントローラー 「▼」 ボタンのコード
 #define IR_RIGHT         0x00FF5AA5       //IRコントローラー 「>」 ボタンのコード
 #define IR_LEFT          0x00FF10EF       //IRコントローラー 「<」 ボタンのコード
 #define IR_STOP          0x00FF38C7       //IRコントローラー 「OK」 ボタンのコード
 #define IR_turnsmallleft 0x00FFB04F       //IRコントローラー 「#」 ボタンのコード

enum DN
{ 
  GO_ADVANCE, //前進する
  GO_LEFT, //左折
  GO_RIGHT,//右折
  GO_BACK,//後進する
  STOP_STOP, 
  DEF
}Drive_Num=DEF;

bool stopFlag = true;//停止フラグを設定する
bool JogFlag = false;
uint16_t JogTimeCnt = 0;
uint32_t JogTime=0;
uint8_t motor_update_flag = 0;
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

//モーター速度の設定
void set_Motorspeed(int speed_L, int speed_R)
{
  analogWrite(speedPinL, speed_L);
  analogWrite(speedPinR, speed_R);
}

/**************赤外線コードを検出する***************/
void do_IR_Tick()
{
  if(IR.decode(&IRresults))
  {
    Serial.print(IRresults.value,HEX); //シリアルに値を出力する
    if(IRresults.value==IR_ADVANCE)
    {
      Drive_Num=GO_ADVANCE;
      Serial.print(" >> GO_ADVANCE");
    }
    else if(IRresults.value==IR_RIGHT)
    {
       Drive_Num=GO_RIGHT;
       Serial.print(" >> GO_RIGHT");
    }
    else if(IRresults.value==IR_LEFT)
    {
       Drive_Num=GO_LEFT;
       Serial.print(" >> GO_LEFT");
    }
    else if(IRresults.value==IR_BACK)
    {
        Drive_Num=GO_BACK;
        Serial.print(" >> GO_BACK");
    }
    else if(IRresults.value==IR_STOP)
    {
        Drive_Num=STOP_STOP;
        Serial.print(" >> STOP_STOP");
    }
    Serial.println("");
    IRresults.value = 0;
    IR.resume();
  }
}

/**************車制御**************/
void do_Drive_Tick()
{
    switch (Drive_Num) 
    {
      case GO_ADVANCE://GO_ADVANCEコードが検出された場合、前に進みます。
        go_Advance(200, 1000); //ここのパラメータを調整しよう
        JogFlag = true;
        JogTimeCnt = 1;
        JogTime=millis();
        break;
      case GO_LEFT: //GO_LEFTコードが検出された場合は、左に曲がります。
        go_Left(200, 1000);//ここのパラメータを調整しよう
        JogFlag = true;
        JogTimeCnt = 1;
        JogTime=millis();
        break;
      case GO_RIGHT://GO_RIGHTコードが検出された場合は右に曲がる
        go_Right(200, 1000);//ここのパラメータを調整しよう
        JogFlag = true;
        JogTimeCnt = 1;
        JogTime=millis();
        break;
      case GO_BACK://GO_BACKコードが検出された場合、バックします
        go_Back(200, 1000);//ここのパラメータを調整しよう
        JogFlag = true;
        JogTimeCnt = 1;
        JogTime=millis();
        break;
      case STOP_STOP://STOP_STOPコードが検出された場合、ストップします。
        stop_Stop();
        JogTime = 0;
        break;
      default:break;
    }
    Drive_Num=DEF;
    if(millis()-JogTime>=200)
    {
      JogTime=millis();
      if(JogFlag == true) 
      {
        stopFlag = false;
        if(JogTimeCnt <= 0) 
        {
          JogFlag = false; stopFlag = true;
        }
        JogTimeCnt--;
      }
      if(stopFlag == true) 
      {
        JogTimeCnt=0;
        stop_Stop();
      }
    }
}

void setup()
{
  //モーターのPinの設定を行う
  pinMode(RightMotorDirPin1, OUTPUT);
  pinMode(RightMotorDirPin2, OUTPUT);
  pinMode(speedPinL, OUTPUT);

  pinMode(LeftMotorDirPin1, OUTPUT);
  pinMode(LeftMotorDirPin2, OUTPUT);
  pinMode(speedPinR, OUTPUT);
  stop_Stop();
  
  //赤外線受信機モジュールを有効にする
  pinMode(IR_PIN, INPUT); 
  digitalWrite(IR_PIN, HIGH);  
  IR.enableIRIn();

  //シリアルを初期化し、ボーレートは9600に設定する       
  Serial.begin(9600);
  Serial.println("--プログラムスタート！--");
}


void loop()
{
  do_IR_Tick();
  do_Drive_Tick();
}
