# レッスン19 for文とwhile文でLEDを制御しよう
## 繰り返し処理でLEDをピカピカさせよう

### このレッスンで身につける力

- [ ] **for文**の書き方を理解できる（カウントアップ・カウントダウン）
- [ ] **while文**の書き方を理解できる
- [ ] delay()と組み合わせてLEDの点滅パターンを作れる
- [ ] ネストしたfor文で複数のLEDを順番に光らせられる

---

### ミッションの準備

#### 0. 必要なハードウェア

- [ ] Osoyoo UNO Board x1
- [ ] ブレッドボード x1
- [ ] LED x2（緑・赤など）
- [ ] 抵抗 330Ω x2
- [ ] ジャンパー線
- [ ] USBケーブル x1
- [ ] パソコン x1

#### 1. 回路を作ろう

| 部品 | 接続先 |
|---|---|
| LED1（アノード＋） | D7（抵抗経由） |
| LED2（アノード＋） | D8（抵抗経由） |
| LED カソード（−） | GND |

レッスン3のLED回路と同じ構成だよ。2つのLEDをD7とD8に接続しよう。

---

### for文とは？

**同じ処理を決まった回数くり返す**ときに使う文だよ。

```C++
for (最初の設定; 続ける条件; 毎回の変化) {
  // くり返す処理
}
```

例：10回LEDを点滅させる
```C++
for (int i = 0; i < 10; i++) {
  digitalWrite(7, HIGH);  // LED ON
  delay(200);
  digitalWrite(7, LOW);   // LED OFF
  delay(200);
}
```

- `int i = 0`：カウンター変数 `i` を0から始める
- `i < 10`：i が10より小さい間、くり返す
- `i++`：くり返しのたびに i を1増やす

---

### while文とは？

**条件が満たされている間ずっとくり返す**ときに使う文だよ。

```C++
while (続ける条件) {
  // くり返す処理
}
```

例：シリアルモニターに数字を入力するまでLEDを点滅し続ける
```C++
while (Serial.available() == 0) {
  digitalWrite(7, HIGH);
  delay(300);
  digitalWrite(7, LOW);
  delay(300);
}
```

---

### ミッションチャレンジ

#### ミッション1：for文でLEDを5回点滅させよう

```C++
#define LED1 7
#define LED2 8

void setup() {
  pinMode(LED1, OUTPUT);
  pinMode(LED2, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  // ミッション1：LED1を5回点滅
  for (int i = 0; i < 5; i++) {
    digitalWrite(LED1, HIGH);
    delay(200);
    digitalWrite(LED1, LOW);
    delay(200);
  }
  delay(1000);  // 1秒待ってから繰り返す
}
```

- [ ] LED1が5回点滅したらチェック！

---

#### ミッション2：カウントアップ・カウントダウンを試そう

```C++
void loop() {
  // カウントアップ（0→9）：回数が増えるごとに点灯時間も増やす
  for (int i = 0; i < 10; i++) {
    digitalWrite(LED1, HIGH);
    delay(i * 50 + 100);  // i が増えるほど長く光る
    digitalWrite(LED1, LOW);
    delay(100);
  }

  // カウントダウン（9→0）：だんだん短くなる
  for (int i = 9; i >= 0; i--) {
    digitalWrite(LED1, HIGH);
    delay(i * 50 + 100);
    digitalWrite(LED1, LOW);
    delay(100);
  }
}
```

- [ ] 点灯時間がだんだん長く、またはだんだん短くなったらチェック！

---

#### ミッション3：ネストしたfor文で2つのLEDを交互に光らせよう

```C++
void loop() {
  // 外側のfor：全体を3回繰り返す
  for (int round = 0; round < 3; round++) {

    // 内側のfor：LED1を5回点滅
    for (int i = 0; i < 5; i++) {
      digitalWrite(LED1, HIGH);
      delay(100);
      digitalWrite(LED1, LOW);
      delay(100);
    }

    // 内側のfor：LED2を5回点滅
    for (int i = 0; i < 5; i++) {
      digitalWrite(LED2, HIGH);
      delay(100);
      digitalWrite(LED2, LOW);
      delay(100);
    }
  }
  delay(1000);
}
```

- [ ] 2つのLEDが交互に光ったらチェック！

---

#### ミッション4：while文でシリアル入力待ちを作ろう

```C++
void loop() {
  Serial.println("シリアルモニターで何かキーを入力してEnterを押してね");

  // 入力があるまでLED2を点滅し続ける
  while (Serial.available() == 0) {
    digitalWrite(LED2, HIGH);
    delay(300);
    digitalWrite(LED2, LOW);
    delay(300);
  }

  // 入力されたデータを読み捨てる
  while (Serial.available() > 0) {
    Serial.read();
  }

  Serial.println("入力されました！");
  delay(1000);
}
```

- [ ] シリアルで入力するまでLEDが点滅し続けたらチェック！

---

### まとめ

- **for文** ：決まった回数くり返す。`for (int i = 0; i < N; i++)` の形
- **while文** ：条件が満たされている間くり返す。`while (条件) { }` の形
- **ネスト** ：for文の中にfor文を書くこと。外側×内側の回数だけくり返す
- `i++` ：iを1増やす（カウントアップ）
- `i--` ：iを1減らす（カウントダウン）

### 出来たことをチェックしよう

- [ ] **for文**の書き方を理解できる（カウントアップ・カウントダウン）
- [ ] **while文**の書き方を理解できる
- [ ] delay()と組み合わせてLEDの点滅パターンを作れる
- [ ] ネストしたfor文で複数のLEDを順番に光らせられる
