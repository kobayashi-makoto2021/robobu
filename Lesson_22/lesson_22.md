# レッスン22 switch文と関数を使いこなそう
## 「場合分け」と「自分だけの命令」を作ろう

### このレッスンで身につける力

- [ ] **switch文**の書き方を理解できる（if文との違いを説明できる）
- [ ] **自作関数**の作り方がわかる（`void 関数名() {}`）
- [ ] シリアルモニターから入力した文字に応じて動作を変えられる
- [ ] レッスン29（対戦）で必殺技を作るための準備ができる

---

### ミッションの準備

#### 0. 必要なハードウェア

- [ ] Osoyoo UNO Board x1
- [ ] ブレッドボード x1
- [ ] アクティブブザー x1
- [ ] LED x1（任意）
- [ ] 抵抗 330Ω x1
- [ ] ジャンパー線
- [ ] USBケーブル x1
- [ ] パソコン x1

#### 1. 回路を作ろう

| 部品 | 接続先 |
|---|---|
| ブザー SIG | D13 |
| ブザー GND | GND |
| LED（アノード＋） | D7（抵抗経由） |
| LED（カソード－） | GND |

---

### switch文とif文の違い

`if`文は条件が「真か偽か」で分岐するよ。でも「1のとき・2のとき・3のとき…」とたくさん分けたいときは**switch文**が読みやすくて便利！

```C++
// if文で書いた場合（長くなりやすい）
if (mode == 1) {
  // 処理A
} else if (mode == 2) {
  // 処理B
} else if (mode == 3) {
  // 処理C
}

// switch文で書いた場合（すっきり！）
switch (mode) {
  case 1: // 処理A; break;
  case 2: // 処理B; break;
  case 3: // 処理C; break;
  default: // どれでもないとき; break;
}
```

**`break`** を忘れずに！忘れると次の `case` に流れ込んでしまうよ。

---

### 自作関数とは？

よく使う処理に名前をつけて、まとめておくことができる。これを**関数**というよ。

```C++
// 関数の定義（書き方）
void 関数名() {
  // ここに処理を書く
}

// 関数の呼び出し（使い方）
関数名();
```

---

### ミッションチャレンジ

#### サンプルコードを動かそう

シリアルモニターで `1`・`2`・`3` を入力すると、それぞれ違う音が鳴るよ。

```C++
#define BUZZ_PIN 13
#define LED_PIN  7

// ---- 自作関数（音パターン） ----

void pattern_one() {
  // パターン1：ピッ（短く1回）
  digitalWrite(BUZZ_PIN, LOW);  delay(150);
  digitalWrite(BUZZ_PIN, HIGH);
}

void pattern_two() {
  // パターン2：ピピッ（2回）
  for (int i = 0; i < 2; i++) {
    digitalWrite(BUZZ_PIN, LOW);  delay(100);
    digitalWrite(BUZZ_PIN, HIGH); delay(100);
  }
}

void pattern_three() {
  // パターン3：ピピピーッ（3回＋長め）
  for (int i = 0; i < 3; i++) {
    digitalWrite(BUZZ_PIN, LOW);  delay(80);
    digitalWrite(BUZZ_PIN, HIGH); delay(80);
  }
  digitalWrite(BUZZ_PIN, LOW);  delay(400);
  digitalWrite(BUZZ_PIN, HIGH);
}

void led_flash(int times) {
  // LED を指定回数点滅する自作関数
  for (int i = 0; i < times; i++) {
    digitalWrite(LED_PIN, HIGH); delay(100);
    digitalWrite(LED_PIN, LOW);  delay(100);
  }
}

// ---- setup / loop ----

void setup() {
  pinMode(BUZZ_PIN, OUTPUT);
  pinMode(LED_PIN, OUTPUT);
  digitalWrite(BUZZ_PIN, HIGH);

  Serial.begin(9600);
  Serial.println("1・2・3を入力してEnterを押してみよう！");
}

void loop() {
  if (Serial.available() > 0) {
    char input = Serial.read();

    switch (input) {
      case '1':
        Serial.println("パターン1！");
        pattern_one();
        led_flash(1);
        break;
      case '2':
        Serial.println("パターン2！");
        pattern_two();
        led_flash(2);
        break;
      case '3':
        Serial.println("パターン3！");
        pattern_three();
        led_flash(3);
        break;
      default:
        Serial.println("1・2・3のどれかを入力してね");
        break;
    }
  }
}
```

- [ ] 1・2・3 の入力でそれぞれ違う音が鳴ったらチェック！
- [ ] `break` を一か所消してみて、何が起きるか確かめたらチェック！

---

#### オリジナルパターンを追加しよう

`case '4':` を追加して、自分だけのオリジナル音パターン関数を作ってみよう。

- [ ] 自分のオリジナルパターン関数が作れたらチェック！

---

### まとめ

- **switch文** ：値によって処理を分岐する。`case 値: 処理; break;` の形
- **`break`** ：switch文の各ケースを終わらせるために必須
- **`default`** ：どのcaseにも当てはまらないときに実行される
- **自作関数** ：`void 関数名() { }` で定義。`関数名();` で呼び出す
- 関数を使うとコードが読みやすく、同じ処理を何度でも使い回せる

### 出来たことをチェックしよう

- [ ] **switch文**の書き方を理解できる（if文との違いを説明できる）
- [ ] **自作関数**の作り方がわかる（`void 関数名() {}`）
- [ ] シリアルモニターから入力した文字に応じて動作を変えられる
- [ ] レッスン29（対戦）で必殺技を作るための準備ができる
