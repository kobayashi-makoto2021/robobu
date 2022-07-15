# 追いかけロボットを作ろう

## 障害物センサーを使って物体追従を行う

### このレッスンで身につける力

- [ ] トラッキングセンサーを正しく取り付けられる
- [ ] ジャンパーワイヤーを正しく接続出来る
- [ ] トラッキングセンサーの感度を調整できる
- [ ] サンプルコードを実行できる
- [ ] 条件式(and or)の書き方を理解してコードを修正できる
- [ ] コースを走破するためにサンプルコードを修正できる

---
### ミッションの準備
- [ ] Osoyoo UNO Board x 1
- [ ] 赤外線コントローラー
- [ ] トラッキングセンサーモジュール
- [ ] アクティブブザーモジュールx 1
- [ ] F/Mジャンパー
- [ ] USBケーブルx 1
- [ ] パソコン x 1


---
### ミッションチャレンジ

#### トラッキングセンサーを正しく取り付けられる

<!-- テキストテキストテキストテキストテキストテキスト
テキストテキストテキストテキストテキストテキスト
テキストテキストテキストテキストテキストテキスト -->

- [ ] トラッキングセンサーを正しく取り付けられる

---
#### ジャンパーワイヤーを正しく接続出来る

<!-- テキストテキストテキストテキストテキストテキスト
テキストテキストテキストテキストテキストテキスト
テキストテキストテキストテキストテキストテキスト -->

- [ ] ジャンパーワイヤーを正しく接続出来る

---
#### サンプルコードを実行できる
スケッチに以下のコードをコピー＆ペーストして、スケッチを実行してみよう。

```C++
#define m1 7  //右モーターMA1
#define m2 8  //右モーターMA2
#define m3 12  //左モーターMB1
#define m4 11  //左モーターMB2
#define e1 9  //右モーター使用可能ピンEA
#define e2 6 //左モーター使用可能ピンEB      

//**********5チャンネルIRセンサー接続**********//
#define ir1 A0
#define ir2 A1
#define ir3 A2
#define ir4 A3
#define ir5 A4
//*************************************************//

void setup() {
  pinMode(m1, OUTPUT);
  pinMode(m2, OUTPUT);
  pinMode(m3, OUTPUT);
  pinMode(m4, OUTPUT);
  pinMode(e1, OUTPUT);
  pinMode(e2, OUTPUT);
  pinMode(ir1, INPUT);
  pinMode(ir2, INPUT);
  pinMode(ir3, INPUT);
  pinMode(ir4, INPUT);
  pinMode(ir5, INPUT);
  Serial.begin(9600);
}

void loop() {
  //センサー値の読み取り
  int s1 = digitalRead(ir1);  //左端のセンサ
  int s2 = digitalRead(ir2);  //左センサー
  int s3 = digitalRead(ir3);  //中央センサ
  int s4 = digitalRead(ir4);  //右センサー
  int s5 = digitalRead(ir5);  //右端のセンサ
 
 Serial.print(!s1);
  Serial.print(!s2);
  Serial.print(!s3);
  Serial.print(!s4);
  Serial.println(!s5);
 
  //中央のセンサの黒い線のみの場合
  if((s1 == 1) && (s2 == 1) && (s3 == 0) && (s4 == 1) && (s5 == 1))
  {
    //全速力で前進する 
    analogWrite(e1, 120); //モーターの速度を0~255の範囲で調整できます
    analogWrite(e2, 120); //モーターの速度を0~255の範囲で調整できます
    digitalWrite(m1, HIGH);
    digitalWrite(m2, LOW);
    digitalWrite(m3, HIGH);
    digitalWrite(m4, LOW);
  }
  
  //左センサーの黒線のみの場合
  if((s1 == 1) && (s2 == 0) && (s3 == 1) && (s4 == 1) && (s5 == 1))
  {
    //左に移動
    analogWrite(e1, 150); //モーターの速度を0~255の範囲で調整できます
    analogWrite(e2, 150); //モーターの速度を0~255の範囲で調整できます
    digitalWrite(m1, LOW);
    digitalWrite(m2, LOW);
    digitalWrite(m3, HIGH);
    digitalWrite(m4, LOW);
    

  }
  
  //センサの黒い線が一番左にある場合
  if((s1 == 0) && (s2 == 1) && (s3 == 1) && (s4 == 1) && (s5 == 1))
  {
    //全速力で左へ
    analogWrite(e1, 180); //モーターの速度を0~255の範囲で調整できます
    analogWrite(e2, 180); //モーターの速度を0~255の範囲で調整できます
    digitalWrite(m1, LOW);
    digitalWrite(m2, HIGH);
    digitalWrite(m3, HIGH);
    digitalWrite(m4, LOW);
    

  }

  //右側のセンサの黒い線のみの場合
  if((s1 == 1) && (s2 == 1) && (s3 == 1) && (s4 == 0) && (s5 == 1))
  {
    //going right
    analogWrite(e1, 150); //モーターの速度を0~255の範囲で調整できます
    analogWrite(e2, 150); //モーターの速度を0~255の範囲で調整できます
    digitalWrite(m1, HIGH);
    digitalWrite(m2, LOW);
    digitalWrite(m3, LOW);
    digitalWrite(m4, LOW);
  }

  //右端のセンサーのみが黒線を検出した場合
  if((s1 == 1) && (s2 == 1) && (s3 == 1) && (s4 == 1) && (s5 == 0))
  {
    //going right with full speed 
    analogWrite(e1, 180); //モーターの速度を0~255の範囲で調整できます
    analogWrite(e2, 180); //モーターの速度を0~255の範囲で調整できます
    digitalWrite(m1, HIGH);
    digitalWrite(m2, LOW);
    digitalWrite(m3, LOW);
    digitalWrite(m4, HIGH);
  }

  //中央と右のセンサーが黒線を検出した場合
  if((s1 == 1) && (s2 == 1) && (s3 == 0) && (s4 == 0) && (s5 == 1))
  {
    //going right
    analogWrite(e1, 150); //モーターの速度を0~255の範囲で調整できます
    analogWrite(e2, 150); //モーターの速度を0~255の範囲で調整できます
    digitalWrite(m1, HIGH);
    digitalWrite(m2, LOW);
    digitalWrite(m3, LOW);
    digitalWrite(m4, LOW);
  }

  //中央と左のセンサが黒線を検出した場合
  if((s1 == 1) && (s2 == 0) && (s3 == 0) && (s4 == 1) && (s5 == 1))
  {
    //going left
    analogWrite(e1, 150); //モーターの速度を0~255の範囲で調整できます
    analogWrite(e2, 150); //モーターの速度を0~255の範囲で調整できます
    digitalWrite(m1, LOW);
    digitalWrite(m2, LOW);
    digitalWrite(m3, HIGH);
    digitalWrite(m4, LOW);
  }

  //中央、左、左のほとんどのセンサが黒い線を検出した場合
  if((s1 == 0) && (s2 == 0) && (s3 == 0) && (s4 == 1) && (s5 == 1))
  {
    //going left
    analogWrite(e1, 150); //モーターの速度を0~255の範囲で調整できます
    analogWrite(e2, 150); //モーターの速度を0~255の範囲で調整できます
    digitalWrite(m1, LOW);
    digitalWrite(m2, LOW);
    digitalWrite(m3, HIGH);
    digitalWrite(m4, LOW);
  }

  //中央、右、一番右のセンサーが黒い線を検出した場合
  if((s1 == 1) && (s2 == 1) && (s3 == 0) && (s4 == 0) && (s5 == 0))
  {
    //going right
    analogWrite(e1, 150); //モーターの速度を0~255の範囲で調整できます
    analogWrite(e2, 150); //モーターの速度を0~255の範囲で調整できます
    digitalWrite(m1, HIGH);
    digitalWrite(m2, LOW);
    digitalWrite(m3, LOW);
    digitalWrite(m4, LOW);
  }

  //すべてのセンサーが黒い線上にある場合
  if((s1 == 0) && (s2 == 0) && (s3 == 0) && (s4 == 0) && (s5 == 0))
  {
    //stop
    digitalWrite(m1, LOW);
    digitalWrite(m2, LOW);
    digitalWrite(m3, LOW);
    digitalWrite(m4, LOW);
  }
}
```


- [ ] サンプルコードを実行できる

---
#### トラッキングセンサーの感度を調整できる


<!-- テキストテキストテキストテキストテキストテキスト
テキストテキストテキストテキストテキストテキスト
テキストテキストテキストテキストテキストテキスト -->


- [ ] トラッキングセンサーの感度を調整できる


---
#### 条件式(and or)の書き方を理解してコードを修正できる

<!-- テキストテキストテキストテキストテキストテキスト
テキストテキストテキストテキストテキストテキスト
テキストテキストテキストテキストテキストテキスト -->

- [ ] 条件式(and or)の書き方を理解してコードを修正できる


---
#### コースを走破するためにサンプルコードを修正できる

<!-- テキストテキストテキストテキストテキストテキスト
テキストテキストテキストテキストテキストテキスト
テキストテキストテキストテキストテキストテキスト -->

- [ ] コースを走破するためにサンプルコードを修正できる

---
### まとめ

<!-- テキストテキストテキストテキストテキストテキスト
テキストテキストテキストテキストテキストテキスト
テキストテキストテキストテキストテキストテキスト -->



---
#### 出来たことをチェックしよう

- [ ] トラッキングセンサーを正しく取り付けられる
- [ ] ジャンパーワイヤーを正しく接続出来る
- [ ] トラッキングセンサーの感度を調整できる
- [ ] サンプルコードを実行できる
- [ ] 条件式(and or)の書き方を理解してコードを修正できる
- [ ] コースを走破するためにサンプルコードを修正できる