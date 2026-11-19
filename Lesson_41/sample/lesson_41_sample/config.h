// =============================================
//  config.h  ピン番号・定数
//  設定を変えたいときは、このファイルだけを見ればOK
// =============================================
#pragma once

#define RECV_PIN   10  // 赤外線受信器 → D10
#define BUZZ_PIN   13  // ブザー → D13
#define LED_PIN     2  // LED → D2

#define dir1PinRight   12  // 右モーターの向き1 → MODEL-X IN1
#define dir2PinRight   11  // 右モーターの向き2 → MODEL-X IN2
#define speedPinRight   9  // 右モーターのスピード → MODEL-X ENA
#define speedPinLeft    6  // 左モーターのスピード → MODEL-X ENB
#define dir1PinLeft     7  // 左モーターの向き1 → MODEL-X IN3
#define dir2PinLeft     8  // 左モーターの向き2 → MODEL-X IN4

#define SPEED       150  // 前進・後進のスピード
#define TURNSPEED   200  // 曲がるときのスピード
#define MAX_PACKETSIZE 32  // Bluetooth受信バッファの大きさ

// チームの設定（レッスン21と同じ切りかえ方）
#define IR_BULLET      0xAAA       //Aの時はこちらを使う。Bの時はコメントアウト
#define MY_BULLET      0xBBB       //Aの時はこちらを使う。Bの時はコメントアウト
// #define IR_BULLET      0xBBB       //Bの時はこちらを使う。Aの時はコメントアウト
// #define MY_BULLET      0xAAA       //Bの時はこちらを使う。Aの時はコメントアウト
