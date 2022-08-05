# 超音波センサーを使ってみよう！

## （未定）


### このレッスンで身につける力

- [ ] ブレッドボードに超音波センサーを使った回路を作ることができる
- [ ] 超音波センサの仕組みを大まかに理解する
- [ ] サンプルコードを実行できる
- [ ] サンプルコードを改造して人感センサを作ることができる

---

### ミッションの準備

- [ ] Osoyoo UNO Board x1
- [ ] 超音波センサーHC-SR04 x1
- [ ] ブレッドボード x1
- [ ] ジャンパー線
- [ ] USBケーブル x1
- [ ] パソコン x1

---
## ミッションチャレンジ

### 超音波センサをArduinoにつなごう！

配線図：
<img src="image/lesson15_1_WiringDiagram.png" width="100%">

- [ ] 回路が作れたらチェック！

---

### 超音波センサで測った距離をシリアルモニタに表示しよう！

ArduinoIDEを開き，ファイル→名前を付けて保存をクリックして，「name_lesson_15_1」という名前で保存しましょう．

スケッチに以下のコードをコピー＆ペーストして，スケッチを実行してみよう．


``` C++
#define echoPin 3
#define trigPin 2

void setup() {
  Serial.begin (9600);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
}

void loop() {
  float duration, distance;
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);

  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  duration = pulseIn(echoPin, HIGH);
  distance = (duration / 2) * 0.0344;

  if (distance >= 400 || distance <= 2) {
    Serial.print("Distance = ");
    Serial.println("Out of range");
  }
  else {
    Serial.print("Distance = ");
    Serial.print(distance);
    Serial.println(" cm");
  }
  delay(10);
}
```

上のプログラムをコピーして実行し，シリアルモニタを開こう！

<img src="image/lesson15_1_serialmonitor_result.png" width="70%">

- [ ] シリアルモニタに上の画像のような表示が出たらチェック！


---

### 超音波センサとは？

ここで，超音波センサの仕組みについて簡単に説明するよ．








---

### 超音波センサとLEDを組み合わせて人感センサを作ろう！

先ほどの回路を改造して，10cm以内に障害物があることを検知したらLEDが点灯する人感センサを作ろう！


配線図：
<img src="image/lesson15_2_WiringDiagram.png" width="100%">

- [ ] 回路が作れたらチェック！

ArduinoIDEを開き，ファイル→名前を付けて保存をクリックして，「name_lesson_15_2」という名前で保存しましょう．

スケッチに以下のコードをコピー＆ペーストして，スケッチを実行してみよう．

``` C++
#define echoPin 3
#define trigPin 2
#define LEDPin 8

void setup() {
  Serial.begin (9600);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(LEDPin, OUTPUT);

}

void loop() {
  float duration, distance;
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);

  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  duration = pulseIn(echoPin, HIGH);
  distance = (duration / 2) * 0.0344;

  Serial.print("Distance = ");
  Serial.print(distance);
  Serial.println(" cm");

  if (distance < 10) {
    digitalWrite(LEDPin, HIGH);
  }
  else {
    digitalWrite(LEDPin, LOW);
  }
  delay(10);
}
```

- [ ] 超音波センサで測定した距離に応じてLEDが光ったらチェック！


---
### 超音波センサで測定した距離に応じてLEDの明るさを変えよう！

ArduinoIDEを開き，ファイル→名前を付けて保存をクリックして，「name_lesson_15_3」という名前で保存しましょう．

スケッチに以下のコードをコピー＆ペーストして，スケッチを実行してみよう．

``` C++







```


**他の（プロジェクターやテレビ等の）リモコンでも試してみよう！**

- [ ] 数字ボタンでサーボモーターが動いたらチェック！
- [ ] 左右の矢印でサーボモーターの位置を細かく変更出来たらチェック！

---
### まとめ

- 


---

#### 出来たことをチェックしよう
- [ ] ブレッドボードに超音波センサーを使った回路を作ることができる
- [ ] 超音波センサの仕組みを大まかに理解する
- [ ] サンプルコードを実行できる
- [ ] サンプルコードを改造して人感センサを作ることができる