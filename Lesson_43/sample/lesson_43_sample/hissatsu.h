// =============================================
//  hissatsu.h  必殺技
//  レッスン22で作った必殺技は、このファイルに入れる。
//  motor.h・sound.h・battle.h の関数を使えるように、それらの後に読み込む。
//  bluetooth.h から呼び出せるように、bluetooth.h より前に読み込む。
// =============================================
#pragma once

// ---- 必殺技の例（レッスン22）----
// 使うときは、下の行の先頭の // を外す。
// ボタンへの割り当て（case 'G': hissatsu(); break; など）は bluetooth.h の switch 文に書く。
//
// void hissatsu(){
//   go_Advance();            // 前に進む
//   delay(1000);             // 1秒=1000ミリ秒待つ
//   stop_Stop();             // 止まる
//   buttonState=1;shoot();   // 赤外線で撃つ
// }
