# Arduinoでタイマーをつくってみよう！

## **シリアルモニターから入力を拾ってオンオフするタイマーを作成する**

### このレッスンで身につける力

- [ ] 足す、引く、掛ける、割るの計算が出来る
- [ ] 計算の順序に合わせて( )を使える
- [ ] delay()と変数、整数型（int）を使ってタイマーを作れる
- [ ] 浮動小数点型(float)を使ってタイマーを改良できる

---

### ミッションの準備

#### 0.ハードウェアを用意しよう

- [ ] Osoyoo UNO Board（ Arduino UNO rev.3と完全互換）x 1
- [ ] USBケーブルx 1
- [ ] パソコン x 1

#### 0.ArduinoIDEを起動しよう

デスクトップにあるAruduinoのアイコンをダブルクリックしてArduinoIDEを起動しよう

![ArduinoIDE_icon]()

#### 1.スケッチを保存しよう

(Arduinoでは，プログラムのことを「スケッチ」といいます．)

ファイル→保存をクリック（Ctrl+SでもOK）して，デスクトップに「lesson_02_1」という名前で保存しよう．

![ArduinoIDE_save]()

#### 2.Arduinoとパソコンを接続しよう

Arduino UNOボードとパソコンをUSBケーブルでつなごう．

![Arduino_USBcable]()

【注意】USBを抜き差しするときは向きを確認して，ていねいにあつかうこと．

USBを差したら，ArduinoIDEでポートを指定しよう．

ツール→シリアルポートをクリックして，「COM～（Arduino UNO）」となっているものをクリックしよう．（COM～の数字は毎回変わります．）

![ArduinoIDE_port_setting]()



---

### 【前回の復習】電卓を作ってみよう
#### このセクションで身につける力
- [ ] 足す、引く、掛ける、割るの計算が出来る
- [ ] 計算の順序に合わせて( )を使える

---

#### プログラムでの四則演算

足し算，引き算，掛け算，割り算のことを「四則演算（しそくえんざん）」と言います．

算数の時間だけでなく，プログラムを書くときもこの四則演算を使うことが多いです．

しかし，プログラム内での四則演算は少し変わった書き方をします．まずは書き方を覚えましょう．

| 種類 | 算数 | プログラム |
| ---- | ---- | ---- |
|  足し算  | + | + |
|  引き算  | - | - |
|  掛け算  | × | * （アスタリスク） |
|  割り算  | ÷ | / （スラッシュ）|

プログラムで書く四則演算の例）
- 1 + 1
- 2 - 1
- 2 * 3  
- 4 / 2


---


#### シリアルモニタからの入力を読み取ろう

電卓を作るには，入力された数字を読み取る必要があります．

さっそく，シリアルモニタからの入力をそのまま表示するプログラムを作ってみましょう．

**＜プログラム＞**

``` C++
long val;

void setup() {
  Serial.begin(9600); //ボーレートの指定
}

void loop() {

  //受信データがある場合if内を処理
  if (Serial.available() > 0) {
    val = Serial.parseInt();    //文字列データを数値に変換
    Serial.println(val);          //一つ目の数字をシリアルモニタに表示
  }

}
```


**＜実行の準備＞**

ツール→シリアルモニタをクリックしましょう．

シリアルモニタが表示されたら，ボーレートを9600に，と改行の設定を「改行無し」にしましょう．

シリアルモニタに数字を入力してみましょう．

![lesson02_1_serialmonitor_setting]()



**＜実行結果＞**

![lesson02_1_serialmonitor_result]()


---

#### 電卓を完成させよう

上で作ったプログラムを改造して，電卓に改造しよう．

ファイル→名前を付けて保存をクリックして，「lesson_02_1」という名前で保存しよう．

以下をすべてコピー＆ペーストしよう．

**＜プログラム＞**

``` C++
long val1,val2,result;

void setup() {
  Serial.begin(9600); //ボーレートを指定
}

void loop() {

  //受信データがある場合if内を処理
  if (Serial.available() > 0){
    
    val1 = Serial.parseInt();    //文字列データを数値に変換
    Serial.print(val1);          //一つ目の数字をシリアルモニタに表示
    
    char aop = Serial.read();    //四則演算用の文字の読み込み
    Serial.print(aop);           //四則演算の文字をシリアルモニタに表示
 
    val2 = Serial.parseInt();    //文字列データを数値に変換
    Serial.print(val2);          //2つ目の数字をシリアルモニタに表示
    Serial.println("=");         //"="表示後改行
    
    switch (aop){
      case '+' :
          result = val1 + val2;
          Serial.println(result ,DEC);   //加算と改行
          Serial.println("");            //改行
          break;
      
      case '-' :
          result = val1 - val2;
          Serial.println(result ,DEC);   //減算と改行
          Serial.println("");            //改行
          break;

      case '*' :
          result = val1 * val2;
          Serial.println(result ,DEC);   //乗算と改行
          Serial.println("");            //改行
          break;

      case '/' :
          result = val1 / val2;
          Serial.println(result ,DEC);   //除算と改行
          Serial.println("");            //改行
          break;
      }
      
  }
  
}
```

**＜実行の準備＞**

ツール→シリアルモニタをクリックしよう．

シリアルモニタが表示されたら，ボーレートを9600に，と改行の設定を「改行無し」にしよう．

シリアルモニタに「1+1」「2*3」のような式を入力して，Enterを押しましょう．

![lesson02_2_serialmonitor_setting]()



**＜実行結果＞**

![lesson02_2_serialmonitor_result]()



---

### タイマーを作ってみよう
#### このセクションで身につける力
- [ ] delay()と変数、整数型（int）を使ってタイマーを作れる
- [ ] 浮動小数点型(float)を使ってタイマーを改良できる

---

#### 変数とは？

変数は，数字や文字を入れておく入れ物のことです．MindStormsではカバンになっていましたね．

Arduinoでは，変数を使う前に宣言する（用意する）必要があります．

例えば，こんな風に宣言します．

``` C++
int a;
```
これは，「整数型で，aという変数を宣言した」ということになります．

「int」が「整数型」を表します．整数とは，「1」「100」「-5」などの小数や分数以外の数字です．整数型には整数しか入りません．「3.14（小数）」「b（文字）」などは入りません．

この部分を変えると型の種類を変更できます．型の種類は他にもたくさんありますが，ここではintのみの紹介とします．

---


#### 1秒ごとにカウントアップするタイマーを作ろう

ファイル→名前を付けて保存をクリックして，「lesson_02_3」という名前で保存しよう．

以下をすべてコピー＆ペーストしよう．

**＜プログラム＞**

``` C++
int redLedPin = 2;
int count = 0;


void setup() {
  Serial.begin(9600);
  Serial.println("Enter Y to start timer");
}
void loop() {
  if (Serial.available()) {
    char ch = Serial.read();
    if (ch == 'y' ||  ch == 'Y') {
      Serial.println("Timer ON");
      Serial.println("If you want to switch it off, simply enter N or n!");
      count = 0;
    }
    if (ch == 'n' ||  ch == 'N') {
      Serial.println("Timer OFF");
      Serial.print(count);
      Serial.println(" seconds");
      Serial.println("If you want to switch it on, simply enter Y or y!");
      count = 0;
    }
  }
  delay(1000);
  count += 1;
}

```

**＜実行の準備＞**

ツール→シリアルモニタをクリックしよう．

シリアルモニタが表示されたら，ボーレートを9600に，と改行の設定を「改行無し」にしよう．

シリアルモニタに「y」を入力して，Enterを押しましょう．タイマーが起動します．

数秒後，シリアルモニタに「n」を入力して，またEnterを押しましょう．タイマーが停止して，経過した時間が表示されます．

![lesson02_3_serialmonitor_setting]()



**＜実行結果＞**

![lesson02_3_serialmonitor_result]()





---

#### 0.1秒ごとにカウントアップするタイマーを作ろう

50m走をするときに使うストップウォッチなどは，1秒の100分の1や1000分の1の細かい時間まで測ることができます．

今回は，上で作ったプログラムを改造して，1秒の10分の1の時間まで測ることができる（＝10倍の精度の）タイマーを作ろう．

**＜プログラム＞**

ループを遅らせる時間を1000ms（1秒）から100ms（0.1秒）に変えて，精度をアップしよう

``` C++
delay(100);
```

ループを早めた分，countの数字が10倍速く大きくなってしまうので，表示する数字を10分の1にして調節しましょう．

``` C++
Serial.print(count/10);
```

**＜実行の準備＞**

さきほどと同じように実行しよう．


**＜実行結果＞**

![lesson02_4_serialmonitor_result]()

**精度が10倍になっているはずなのに1秒単位でしか表示されないのは何故でしょうか？**


---

#### float型を使ってタイマーを正しく動作させよう

あああ


---

### まとめ

あああ

#### 出来たことをチェックしよう

- [ ] 足す、引く、掛ける、割るの計算が出来る
- [ ] 計算の順序に合わせて( )を使える
- [ ] delay()と変数、整数型（int）を使ってタイマーを作れる
- [ ] 浮動小数点型(float)を使ってタイマーを改良できる