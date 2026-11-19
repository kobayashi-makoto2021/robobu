// =============================================
//  bluetooth.h  Bluetooth通信
//  アプリから届いた文字を読んで、動きを決める。
//  ほかの .h の関数を全部呼ぶので、いちばん最後に読み込む。
// =============================================
#pragma once

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
    case 'R':  go_Right(); break;
    case 'B':  go_Back(); break;
    case 'X':  back_Left(); break;
    case 'Y':  back_Right(); break;
    case 'F':  buttonState=1;shoot();break;
    case 'E': stop_Stop() ;buzz_OFF();break;
    case 'J': stop_Stop() ;break;
    default:break;
  }
}
