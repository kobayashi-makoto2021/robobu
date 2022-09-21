#include <SoftwareSerial.h>
SoftwareSerial BTSerial(4, 5);  //RX,TX
#include <IRremote.h>
 #define RECV_PIN   10 // IR receiver pin connect to D10
IRrecv irrecv(RECV_PIN);
IRsend irsend;
decode_results results;
int buttonState;

#define BUZZ_PIN     13  //buzzer connect to D13
#define IR_BULLET      0xBBB       //code my bullet shoot from IR LED 
//#define IR_BULLET      0x38C7       //test my bullet shoot from IR remoter 

#define MY_BULLET       0xAAA       //code my bullet shoot to enemy 
 

/*Declare L298N Dual H-Bridge Motor Controller directly since there is not a library to load.*/
//Define L298N Dual H-Bridge Motor Controller Pins
#define dir1PinRight   12  // Right Motor direction pin 1 to MODEL-X IN1 
#define dir2PinRight  11   // Right Motor direction pin 2 to MODEL-X IN2
#define speedPinRight 9   //RIGHT PWM pin connect MODEL-X ENA
#define speedPinLeft 6    // Left PWM pin connect MODEL-X ENB
#define dir1PinLeft  7    //Left Motor direction pin 1 to MODEL-X IN3 
#define dir2PinLeft  8    //Left Motor direction pin 2 to MODEL-X IN4 

 
#define SPEED   90  //avoidance motor speed
#define TURNSPEED  170     //back speed
 
#define MAX_PACKETSIZE 32    //Serial receive buffer
char buffUART[MAX_PACKETSIZE];
unsigned int buffUARTIndex = 0;
unsigned long preUARTTick = 0;

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

/*set motor speed */
void set_Motorspeed(int speed_L,int speed_R)
{
  analogWrite(speedPinRight,speed_R); 
  analogWrite(speedPinLeft,speed_L);   
}
void buzz_ON()   //open buzzer
{
	  for(int i=0;i<100;i++)
  {
   digitalWrite(BUZZ_PIN,LOW);
   delay(2);//wait for 1ms
   digitalWrite(BUZZ_PIN,HIGH);
   delay(2);//wait for 1ms
  }

}
void buzz_OFF()  //close buzzer
{
  digitalWrite(BUZZ_PIN, HIGH);
}

void alarm(){
   buzz_ON();
   buzz_OFF();
}

//WiFi / Bluetooth through the serial control
void do_Uart_Tick()
{

  char Uart_Date=0;
  if(BTSerial.available()) 
  {
    size_t len = BTSerial.available();
    uint8_t sbuf[len + 1];
    sbuf[len] = 0x00;
    BTSerial.readBytes(sbuf, len);
    //parseUartPackage((char*)sbuf);
    memcpy(buffUART + buffUARTIndex, sbuf, len);//ensure that the serial port can read the entire frame of data
    buffUARTIndex += len;
    preUARTTick = millis();
    if(buffUARTIndex >= MAX_PACKETSIZE - 1) 
    {
      buffUARTIndex = MAX_PACKETSIZE - 2;
      preUARTTick = preUARTTick - 200;
    }
  }
  if(buffUARTIndex > 0 && (millis() - preUARTTick >= 100))//APP send flag to modify the obstacle avoidance parameters
  { //data ready
    buffUART[buffUARTIndex] = 0x00;
    Uart_Date=buffUART[0];
    buffUARTIndex = 0;
  }

  switch (Uart_Date)    //serial control instructions
  {
    case 'M':  go_Advance(); break;
    case 'L':  go_Left(); break;
    case 'R': go_Right(); break;
    case 'B':  go_Back(); break;
    case 'X':  back_Left(); break;
    case 'Y':  back_Right(); break;
    case 'F':  buttonState=1;shoot();break;
    case 'E': stop_Stop() ;buzz_OFF();break;
    case 'J': stop_Stop() ;break;
    default:break;
  }
}

//car motor control


void setup()
{
  irrecv.enableIRIn(); // Start the receiver
  pinMode(dir1PinRight, OUTPUT); 
  pinMode(dir2PinRight, OUTPUT); 
  pinMode(speedPinRight, OUTPUT);  
  pinMode(dir1PinLeft, OUTPUT);
  pinMode(dir2PinLeft, OUTPUT); 
  pinMode(speedPinLeft, OUTPUT); 
  stop_Stop();
  pinMode(BUZZ_PIN, OUTPUT);
  buzz_OFF();  
  Serial.begin(9600);//In order to fit the Bluetooth module's default baud rate, only 9600
  BTSerial.begin(9600);
  /*
  go_Advance();
  delay(1000);
    go_Back();
  delay(1000);
  stop_Stop();
  */
}
int lastButtonState=0;
void loop()
{  
  if (buttonState) {
     buttonState=0;
       irrecv.enableIRIn(); // Start the receiver
        irrecv.resume();
  } 
  else  if (irrecv.decode(&results)) {
 

  //If got shoot by enemy, dead freeze and alarm
  int data=results.value;
    Serial.print("ir code:");
   Serial.println(data);
    
    if(data==IR_BULLET)
    {
        deadAlarm();
    }
    irrecv.resume(); // resume receiver
  }
  lastButtonState = buttonState;

  
  do_Uart_Tick();
 
}

void shoot(){
  Serial.print("shooting bullet :");
  Serial.println(MY_BULLET,HEX);  
 for (int i = 0; i < 3; i++) {
      irsend.sendSony(MY_BULLET, 12); // Sony TV power code
      delay(40);
    }
  
}
void deadAlarm(){
  BTSerial.println("DEAD!");
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
    digitalWrite(BUZZ_PIN,LOW);
    delay(2);//wait for 2ms
    digitalWrite(BUZZ_PIN,HIGH);
    delay(2);//wait for 2ms
  }
    
 }
}
