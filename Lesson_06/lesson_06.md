# レッスン6 ロボット・チキンラン！<br>～ロボットで線ギリギリまで進むプログラムを書こう！～

#### このレッスンで身につける力

- [ ] レッスン04・05のサンプルコードを使ってロボットを**まっすぐ進める**ことができる。
- [ ] ロボットを**後ろに下がらせる**ことができる。
- [ ] ロボットの**速度を調整する**ことができる。
- [ ] 設定した速度と前進する時間からおおよその**進む距離が予想**できる。
- [ ] **ラインギリギリで止まる**ことができる。
---

### ミッションの準備
#### 0. 必要なハードウェア

- [ ] Osoyoo ROBOT CAR STARTER KIT ×1
- [ ] USBケーブル ×1
- [ ] ArduinoIDEがインストールされたパソコン ×1
- [ ] コース

![](image/course.png)

#### 1. ArduinoIDEを起動して白紙のスケッチを作ろう<br>
最初にArduinoIDEを起動しよう。次に起動したらスケッチに名前を付けてデスクトップに保存してみよう。やり方が分からなかったらレッスン1のテキストを見て復習しよう！
#### 2. サンプルコードをコピー&ペーストしよう<br>
サンプルコードを1で作ったスケッチにコピー&ペーストしよう
```C++
#define speedPinR 9    //  右側のPWM信号を送信するピンの設定
#define RightMotorDirPin1  12    //右後ろのモーターの信号ピンの設定 
#define RightMotorDirPin2  11    //右前のモーターの信号ピンの設定
#define speedPinL 6    // 左のPWM信号を送信するピンの設定
#define LeftMotorDirPin1  7    //左後ろのモーターの信号ピンの設定 
#define LeftMotorDirPin2  8   //左前のモーターの信号ピンの設定  


//モーターの制御
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

//ピンの初期化
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

//ここから下にプログラムを書く

}

void loop() {
} 
```
---

### ミッションチャレンジ
#### ロボットをまっすぐ進ませよう
ロボットをまっすぐ進ませるには**go_Advance関数**を使うよ。
```C++
go_Advance(スピード, 止まるまでの時間);
```
のように書くと指定された時間が経つまで前に進み続けるよ。
試しにプログラムの`//ここから下にプログラムを書く`と書いてある下に
```C++
go_Advance(100, 1000);
```
と書いて動かしてみよう。プログラムを実行するとロボットが1秒間(1000ミリ秒間)進むよ。

これができたら、速度と距離を変えて、コースのゴールの線ギリギリまで進んでみよう！

**出来たらチェック！**
 - [ ] ロボットの前進が出来たらチェック！
 - [ ] 速度を調節できたらチェック！
 - [ ] ラインギリギリで止まれたらチェック！

#### ロボットを後ろに下がらせよう
ゴールの線ギリギリに止まったロボットを今度はスタート地点まで戻してみよう。

ロボットを後ろに下がらせるためには**go_Back関数**を使うよ。go_Back関数もgo_Advance関数と同じように
```C++
go_Back(スピード, 止まるまでの時間);
```
のように書くと指定された時間が経つまで後ろに下がるよ。試しに

```C++
go_Back(100, 1000);
```
と書いて動かしてみよう。これができたら、速度と距離を変えて、コースのスタートの線ギリギリまで戻ってみよう！

**出来たらチェック！**

 - [ ] ロボットの後進が出来たらチェック！
 - [ ] 速度を調節できたらチェック！
 - [ ] ラインギリギリで止まれたらチェック！


#### 設定した前進する時間と距離から速度を計算しよう
速度は

`速度 = 進んだ距離 ÷ 時間`

で計算できるよ。

試しにスピードが100で1秒間進んだ時にどのくらい移動するか測ってみよう。
測った距離から速度をノートに計算してみよう。

同じようにスピードが200に設定したとき、300に設定したときで速度がどのように変わるか、距離を測って、ノートに記録しよう。

速度から距離を求める計算も覚えておこう

`進む距離 = 速さ × 時間` 


---
## まとめ
- **go_Advance関数** :ロボットを前に進めるための関数
- **go_Back関数** :ロボットを後ろに下がらせるための関数
- ```C++ 
  go_Advance(スピード, 止まるまでの時間);
  ```
  →ロボットが前に進むプログラム
- ```C++ 
  go_Back(スピード, 止まるまでの時間);
  ```
  →ロボットが後ろに下がるプログラム
- `進む距離 = 速さ × 時間` :ロボットが進む距離の計算式


### 出来たことをチェックしよう
- [ ] レッスン04・05のサンプルコードを使ってロボットをまっすぐ進めることができる。
- [ ] ロボットを後ろに下がらせることができる。
- [ ] ロボットの速度を調整することができる。
- [ ] 設定した速度と前進する時間からおおよその進む距離が予想できる。
- [ ] ラインギリギリで止まることができる。