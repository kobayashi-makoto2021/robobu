# レッスン23 BluetoothでサーボモーターをBluetooth操作しよう
## スマホから角度を送ってサーボを動かそう

### このレッスンで身につける力

- [ ] Bluetoothモジュール（HC-06）をArduinoに接続できる
- [ ] SoftwareSerialでBluetoothのデータを受信できる
- [ ] 受信したデータを使ってservo.write()でサーボを動かせる
- [ ] レッスン24（Bluetoothロボット）の接続方法に慣れられる

---

### ミッションの準備

#### 0. 必要なハードウェア

- [ ] Osoyoo UNO Board x1
- [ ] Bluetoothモジュール（HC-06）x1
- [ ] SG90サーボモーター x1
- [ ] ブレッドボード x1
- [ ] ジャンパー線
- [ ] USBケーブル x1
- [ ] パソコン x1
- [ ] タブレットまたはスマホ（Bluetooth送信アプリをインストール済み）

---

### 部品を接続しよう

#### Bluetoothモジュール（HC-06）の配線

| HC-06のピン | Arduinoのピン |
|---|---|
| VCC | 5V |
| GND | GND |
| TXD | D4（SoftwareSerial RX） |
| RXD | D5（SoftwareSerial TX） |

> **注意**：HC-06のTXDはArduinoのRXに、HC-06のRXDはArduinoのTXにつなぐよ。

#### サーボモーター（SG90）の配線

| サーボのピン | 色 | 接続先 |
|---|---|---|
| 電源 | 赤 | 5V |
| GND | 茶（黒） | GND |
| 信号 | 橙（黄） | D9 |

---

### Bluetoothアプリの準備

タブレットまたはスマホに **Serial Bluetooth Terminal** などのアプリをインストールしよう。

1. Bluetoothをオンにする
2. アプリを開いてデバイスを検索
3. `HC-06` または `BT_OSOYOO` という名前のデバイスに接続
   （ペアリングPINは `1234` または `0000`）
4. 送信欄に数字を入力して送信するとサーボが動くよ

---

### ミッションチャレンジ

#### サンプルコードを動かそう

```C++
#include <SoftwareSerial.h>
#include <Servo.h>

SoftwareSerial BTSerial(4, 5);  // Bluetooth RX=D4, TX=D5
Servo myServo;

#define SERVO_PIN 9  // サーボ → D9

int angle = 90;  // 現在の角度（初期値90°）

void setup() {
  Serial.begin(9600);
  BTSerial.begin(9600);
  myServo.attach(SERVO_PIN);
  myServo.write(angle);  // 起動時は90°（正面向き）

  Serial.println("Bluetooth待受中...");
  Serial.println("0〜180の数字を送信するとサーボが動くよ");
}

void loop() {
  if (BTSerial.available() > 0) {
    String data = BTSerial.readStringUntil('\n');  // 改行まで読み取る
    data.trim();                                    // 前後の空白・改行を除去

    int newAngle = data.toInt();  // 文字列を整数に変換

    // 0〜180の範囲に制限する
    newAngle = constrain(newAngle, 0, 180);

    angle = newAngle;
    myServo.write(angle);

    Serial.print("受信: ");
    Serial.print(data);
    Serial.print(" → サーボ角度: ");
    Serial.println(angle);
  }
}
```

- [ ] アプリから `90` を送信してサーボが正面を向いたらチェック！
- [ ] `0` ・ `90` ・ `180` を送って、サーボが動いたらチェック！

---

#### ボタンで特定の角度に動かしてみよう

アプリのボタンに文字（例：`L`、`C`、`R`）を設定して、switch文で角度を変えよう。

```C++
void loop() {
  if (BTSerial.available() > 0) {
    char cmd = BTSerial.read();

    switch (cmd) {
      case 'L':
        myServo.write(0);    // 左いっぱい
        Serial.println("左へ");
        break;
      case 'C':
        myServo.write(90);   // 正面
        Serial.println("正面");
        break;
      case 'R':
        myServo.write(180);  // 右いっぱい
        Serial.println("右へ");
        break;
      default:
        break;
    }
  }
}
```

- [ ] L・C・Rで3つの方向にサーボが動いたらチェック！

---

### まとめ

- **SoftwareSerial** ：D4・D5を使った追加のシリアル通信（Bluetooth通信に使う）
- `BTSerial.available()` ：受信データがあれば1以上の値を返す
- `BTSerial.readStringUntil('\n')` ：改行まで文字列を読み取る
- `data.toInt()` ：文字列を整数に変換
- `constrain(値, 最小, 最大)` ：値を指定した範囲に収める
- `myServo.write(角度)` ：0〜180でサーボの角度を指定

### 出来たことをチェックしよう

- [ ] Bluetoothモジュール（HC-06）をArduinoに接続できる
- [ ] SoftwareSerialでBluetoothのデータを受信できる
- [ ] 受信したデータを使ってservo.write()でサーボを動かせる
- [ ] レッスン24（Bluetoothロボット）の接続方法に慣れられる
