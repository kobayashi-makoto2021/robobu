# IRremote ライブラリ API 更新仕様書

旧API（v2以前）→ 新API（v3/v4）への書き換え手順。
本リポジトリの対象13ファイルに共通して適用する。

---

## 1. 受信（IRrecv）の変更

### 1-1. API 対応表

| 項目 | 旧API（v2以前） | 新API（v3/v4） |
|---|---|---|
| 変数宣言 | `IRrecv irrecv(pin);` | 不要（グローバル `IrReceiver` を使う） |
| 結果変数 | `decode_results results;` | 不要 |
| 初期化 | `irrecv.enableIRIn()` | `IrReceiver.begin(pin, ENABLE_LED_FEEDBACK)` |
| デコード確認 | `irrecv.decode(&results)` | `IrReceiver.decode()` |
| 受信値の取得 | `results.value` | `IrReceiver.decodedIRData.decodedRawData` |
| ビット数の取得 | `results.bits` | `IrReceiver.decodedIRData.numberOfBits` |
| 次の受信へ | `irrecv.resume()` | `IrReceiver.resume()` ← 変更なし |

### 1-2. 変換例（最小構成：コード読み取り）

**旧API**
```cpp
#include <IRremote.h>
const int irReceiverPin = 2;
IRrecv irrecv(irReceiverPin);
decode_results results;

void setup() {
  Serial.begin(9600);
  irrecv.enableIRIn();
}

void loop() {
  if (irrecv.decode(&results)) {
    Serial.print("IRコード: ");
    Serial.println(results.value, HEX);
    irrecv.resume();
  }
}
```

**新API**
```cpp
#include <IRremote.hpp>   // ← 拡張子が .h → .hpp に変わる
#define IR_PIN 2

void setup() {
  Serial.begin(9600);
  IrReceiver.begin(IR_PIN, ENABLE_LED_FEEDBACK);
}

void loop() {
  if (IrReceiver.decode()) {
    Serial.print("IRコード: ");
    Serial.println(IrReceiver.decodedIRData.decodedRawData, HEX);
    IrReceiver.resume();
  }
}
```

### 1-3. 変換例（ビット数も表示する場合）

```cpp
// 旧
Serial.print(results.value, HEX);
Serial.println(results.bits);

// 新
Serial.print(IrReceiver.decodedIRData.decodedRawData, HEX);
Serial.println(IrReceiver.decodedIRData.numberOfBits);
```

---

## 2. 送信（IRsend）の変更

Lesson_29 の 8A/8B と Lesson_17 の Lesson_16_2_sample / Lesson_16_3_sample には `IRsend` による送信処理がある。

### 2-1. API 対応表

| 項目 | 旧API（v2以前） | 新API（v3/v4） |
|---|---|---|
| 変数宣言 | `IRsend irsend;` | 不要（グローバル `IrSender` を使う） |
| 初期化 | 不要 | `IrSender.begin(DISABLE_LED_FEEDBACK)` ※setup内 |
| Sony送信 | `irsend.sendSony(code, bits)` | `IrSender.sendSony(code, bits, 3)` ※第3引数が追加 |

> **第3引数（repeat）について：**
> v3/v4 では送信関数の第3引数に繰り返し回数を指定する。
> Sonyプロトコルは仕様上3回送信が推奨されているため `3` を指定する。
> 旧コードがすでに `for (i = 0; i < 3; i++) { irsend.sendSony(...); delay(40); }` と3回ループしている場合は、
> ループを削除して `IrSender.sendSony(code, bits, 3)` の1行に置き換える。

### 2-2. 変換例（shoot関数）

**旧API**
```cpp
IRsend irsend;

void shoot() {
  for (int i = 0; i < 3; i++) {
    irsend.sendSony(MY_BULLET, 12);
    delay(40);
  }
}
```

**新API**
```cpp
// グローバル変数の IRsend irsend; 宣言は削除

void setup() {
  IrSender.begin(DISABLE_LED_FEEDBACK);  // 追加
  // ...
}

void shoot() {
  IrSender.sendSony(MY_BULLET, 12, 3);  // ループ不要、1行に集約
}
```

---

## 3. インクルードの変更

```cpp
// 旧
#include <IRremote.h>

// 新
#include <IRremote.hpp>
```

v3.0 以降は拡張子が `.hpp` に変わった。`.h` でも動作するバージョンもあるが、`.hpp` を使うのが正式。

---

## 4. NEC プロトコルのコード値に関する注意

本リポジトリで使うリモコンは NEC プロトコル。
v3/v4 では NEC のデコード結果が **LSB ファースト**（ビット順が逆）で返される場合があり、
`decodedRawData` の値が v2 の `results.value` と一致しないケースがある。

| v2の results.value | v3/v4 の decodedRawData | 一致するか |
|---|---|---|
| `0xFF38C7` | `0xFF38C7` | 要実機確認 |
| `0x00FF18E7` | `0x00FF18E7` | 要実機確認 |

**対処方針：**
書き換え後に実機でシリアルモニターを開き、ボタンを押して出力されるコードを確認する。
値がズレていた場合は `#define` のコード定数を新しい値に書き換える。

---

## 5. ファイル別の変更箇所まとめ

### グループA：受信のみ（シンプル構成）

以下のファイルは `IRrecv` + `decode_results` を使った基本的な受信処理のみ。

| ファイル | 変更点 |
|---|---|
| [Lesson_09/sample/lesson_08_arduino_sample/lesson_08_arduino_sample.ino](Lesson_09/sample/lesson_08_arduino_sample/lesson_08_arduino_sample.ino) | セクション1の変換を適用 |
| [Lesson_09/sample/lesson_08_arduino_challenge_sample/lesson_08_arduino_challenge_sample.ino](Lesson_09/sample/lesson_08_arduino_challenge_sample/lesson_08_arduino_challenge_sample.ino) | セクション1の変換を適用 |
| [Lesson_17/sample/Lesson_16_1_sample/Lesson_16_1_sample.ino](Lesson_17/sample/Lesson_16_1_sample/Lesson_16_1_sample.ino) | セクション1の変換を適用 |
| [Lesson_17/sample/Lesson_16_2_sample/Lesson_16_2_sample.ino](Lesson_17/sample/Lesson_16_2_sample/Lesson_16_2_sample.ino) | セクション1の変換を適用 |
| [Lesson_17/sample/Lesson_16_3_sample/Lesson_16_3_sample.ino](Lesson_17/sample/Lesson_16_3_sample/Lesson_16_3_sample.ino) | セクション1の変換を適用 |

### グループB：受信のみ（ブザー制御あり）

| ファイル | 変更点 |
|---|---|
| [Lesson_07/sample/lesson9_02/lesson9_02.ino](Lesson_07/sample/lesson9_02/lesson9_02.ino) | セクション1の変換を適用（受信値の `if` 文のコード定数も要確認） |

### グループC：受信＋コード判定でロボット制御

| ファイル | 変更点 |
|---|---|
| [Lesson_10/sample/lesson10_sample/lesson10_sample.ino](Lesson_10/sample/lesson10_sample/lesson10_sample.ino) | `IRrecv IR(IR_PIN)` → `IrReceiver.begin`、`IRresults.value` → `IrReceiver.decodedIRData.decodedRawData` |

### グループD：受信＋送信（対戦ゲーム）

受信（IRrecv）と送信（IRsend）の両方を使う。セクション1＋2の両方を適用する。

| ファイル | 変更点 |
|---|---|
| [Lesson_29/sample/v2smartcar-lesson8A/v2smartcar-lesson8A.ino](Lesson_29/sample/v2smartcar-lesson8A/v2smartcar-lesson8A.ino) | セクション1＋2の変換を適用、`shoot()`内のループを1行に集約 |
| [Lesson_29/sample/v2smartcar-lesson8B/v2smartcar-lesson8B.ino](Lesson_29/sample/v2smartcar-lesson8B/v2smartcar-lesson8B.ino) | セクション1＋2の変換を適用、`shoot()`内のループを1行に集約 |

### グループE：Markdownファイル（説明文中のサンプルコード）

| ファイル | 変更点 |
|---|---|
| [Lesson_07/lesson_07.md](Lesson_07/lesson_07.md) | 説明文中のコードスニペットを新APIに書き換え |
| [Lesson_09/lesson_09.md](Lesson_09/lesson_09.md) | 説明文中のコードスニペットを新APIに書き換え |
| [Lesson_10/Lesson_10.md](Lesson_10/Lesson_10.md) | 説明文中のコードスニペットを新APIに書き換え |
| [Lesson_17/lesson_17.md](Lesson_17/lesson_17.md) | 説明文中のコードスニペットを新APIに書き換え |

---

## 6. 作業手順（推奨順）

1. グループA（シンプル受信）から始めて変換パターンを確認する
2. グループB・C と続けて受信処理の変換に慣れる
3. グループD（送信あり）を最後に対応する（`shoot()` のループ削除に注意）
4. 実機でシリアルモニターを開いてコード値を確認する（セクション4参照）
5. グループE のMarkdownファイルを更新する
