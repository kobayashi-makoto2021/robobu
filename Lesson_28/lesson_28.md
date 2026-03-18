# レッスン28 オリジナルロボットを作ろう(4)〜調整と完成
## コードを移植して動かそう

### このレッスンで身につける力

- [ ] motor_driver.hを使って自分のロボットを動かせる
- [ ] センサーのピン番号を自分の配線に合わせて変更できる
- [ ] 音デバッグ（ブザー）でロボットの動作を確認できる
- [ ] テスト→修正のサイクルでロボットを完成させられる

---

### ミッションの準備

#### 0. 必要なもの

- [ ] 組み立て済みのオリジナルロボット（L27で完成したもの）
- [ ] パソコン + Arduino IDE
- [ ] USBケーブル
- [ ] 作りたい動作のイメージ（L25で考えたコンセプト）

---

### コード移植の手順

L08〜L24で学んだコードを自分のロボットに移植しよう。

#### ステップ1：motor_driver.h をスケッチフォルダにコピー

```
lesson_28_sample/
├── lesson_28_sample.ino
└── motor_driver.h     ← Lesson_commonからコピー
```

#### ステップ2：使いたいレッスンのコードをベースにする

| やりたいこと | ベースにするレッスン |
|---|---|
| 障害物を自動で避ける | L14（障害物回避） |
| ラインを自動でトレース | L16（ライントラッキング） |
| スマホで操作する | L24（Bluetooth操作） |
| WiFiで操作する | L21（WiFi操作） |
| 超音波センサーで距離を測る | L18（迷路ロボット） |

#### ステップ3：ピン番号を自分の配線に合わせる

自分の配線と、コードのピン番号が一致しているか確認しよう。

```cpp
// ピン番号の確認ポイント
#define RightObstacleSensor 2    // ← 自分の配線に合わせて変更
#define LeftObstacleSensor  A5   // ← 自分の配線に合わせて変更
#define BUZZ_PIN 13              // ← ブザーをつないだピン
```

---

### ミッションチャレンジ

#### ミッション1：最小限のコードで動作確認しよう

まず**前進・停止だけ**確認してから、センサー処理を追加しよう。

```cpp
#include "motor_driver.h"
#define BUZZ_PIN 13

void setup() {
  init_GPIO();
  pinMode(BUZZ_PIN, OUTPUT);
  digitalWrite(BUZZ_PIN, HIGH);  // ブザーOFF（起動時）

  // 起動音
  digitalWrite(BUZZ_PIN, LOW);
  delay(200);
  digitalWrite(BUZZ_PIN, HIGH);
  delay(100);
}

void loop() {
  go_Advance(200, 1000);  // 1秒前進
  stop_Stop();
  delay(2000);
}
```

- [ ] ロボットが前進・停止できたらチェック！

---

#### ミッション2：音デバッグでセンサーを確認しよう

L08で学んだ音デバッグを使って、センサーが正しく反応しているか確認しよう。

```cpp
#include "motor_driver.h"
#define BUZZ_PIN 13
#define RightObstacleSensor 2
#define LeftObstacleSensor A5

void buzz_short() {
  digitalWrite(BUZZ_PIN, LOW);
  delay(100);
  digitalWrite(BUZZ_PIN, HIGH);
  delay(50);
}

void setup() {
  init_GPIO();
  pinMode(BUZZ_PIN, OUTPUT);
  digitalWrite(BUZZ_PIN, HIGH);
  pinMode(RightObstacleSensor, INPUT);
  pinMode(LeftObstacleSensor, INPUT);
  Serial.begin(9600);
}

void loop() {
  int right = digitalRead(RightObstacleSensor);
  int left  = digitalRead(LeftObstacleSensor);

  // センサー値をシリアルモニタに表示
  Serial.print("右: "); Serial.print(right);
  Serial.print(" 左: "); Serial.println(left);

  // 障害物を検知したら音を鳴らす
  if (right == LOW || left == LOW) {
    buzz_short();
  }
  delay(100);
}
```

- [ ] 障害物をかざすとブザーが鳴ったらチェック！
- [ ] シリアルモニタで 0/1 の変化が確認できたらチェック！

---

#### ミッション3：完成コードを組み合わせよう

センサーが正しく動いたら、ベースのコードと組み合わせて完成させよう。

**テスト → 修正 のサイクル**：

1. 書き込む → 動かす
2. 思った通りに動かない部分を見つける
3. コードを修正する
4. また書き込む → 動かす

> ロボットが意図しない方向に動いたときは、モーターの配線の向き（プラスとマイナス）を確認しよう。`go_Advance()` で後退する場合は、モータードライバーへの接続線を2本入れ替えると直ることが多い。

- [ ] 自分のロボットが狙い通りに動いたらチェック！

---

### まとめ

- **移植の手順**：motor_driver.h コピー → ベースコード選択 → ピン番号調整
- **音デバッグ**：センサーの動作確認に有効
- **テスト→修正**：一度に全部作らず、少しずつ確認しながら進める

### 出来たことをチェックしよう

- [ ] motor_driver.hを使って自分のロボットを動かせる
- [ ] センサーのピン番号を自分の配線に合わせて変更できる
- [ ] 音デバッグ（ブザー）でロボットの動作を確認できる
- [ ] テスト→修正のサイクルでロボットを完成させられる
