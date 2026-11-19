# レッスン41　プログラムを整理しよう！

## モジュール化とリファクタリングに挑戦しよう

## これからロボットをゲームコントローラーで動かそう！

これまで、ロボットはタブレットのアプリを使って操作してきました。これからは、**ゲームのコントローラーを使ってロボットを動かせるように改造**していきます！

そのためには、今まで作ってきたプログラムを大きく整理する必要があります。プログラムの動作を変えずに、中身の構造を整理して、読みやすく改造しやすくする作業を**リファクタリング**といいます。

プログラムを大きく改造するときは、コードを役割ごとのまとまりに分け、**そのまま使う部分**と**これから改造する部分**を区別しておくと便利です。このように、機能ごとのまとまりに整理することを**モジュール化**といいます。

今回は、みんなが今使っている対戦ロボットのプログラム（レッスン21・22で作ったもの）を使って、まずこの整理に挑戦します。モーターの操作、Bluetooth通信、赤外線の攻撃や被弾判定などを機能ごとに分け、**ロボットの動きを変えずに、次の改造に備える**ことが目標です。

ゲームコントローラーへの切り替えは、次のレッスン以降で進めます。

### このレッスンで身につける力

- [ ] モジュール化とリファクタリングの意味を説明できる
- [ ] Arduino IDEで新しいタブ（ファイル）を作れる
- [ ] `.ino` と `.h` の役割の違いを説明できる
- [ ] 共通の設定をヘッダーファイルにまとめられる
- [ ] 機能別にプログラムを分けても、元どおり動かせる

---

## ミッションの準備

- [ ] レッスン21で使用した対戦ロボット
- [ ] Arduino Uno互換ボードとUSBケーブル
- [ ] パソコンとArduino IDE
- [ ] 今使っている自分の対戦プログラム（レッスン21・22で作ったもの）

**大切！** 今回はWi-Fi通信への変更は行いません。Bluetoothでの走行と赤外線対戦が、整理後も動くことを確かめます。

---

## ミッション1　プログラムの役割を見つけよう

### モジュール化って何だろう？

長いプログラムを、役割ごとに分けて整理することを**モジュール化**といいます。

また、ロボットの動作など外から見た働きを変えずに、プログラムの構造を改善することを**リファクタリング**といいます。

自分のプログラムから、次の処理を探してみましょう。

| 機能 | 元のプログラムにある関数や処理 |
|---|---|
| モーター | `go_Advance()`、`go_Left()`、`go_Right()`、`go_Back()`、`back_Left()`、`back_Right()`、`stop_Stop()`、`set_Motorspeed()` |
| ブザー | `buzz_ON()`、`buzz_OFF()`、`alarm()` |
| Bluetooth通信 | `do_Uart_Tick()` |
| 赤外線攻撃 | `shoot()` |
| 被弾時の処理 | `deadAlarm()` |
| 全体の実行 | `setup()`、`loop()` |

レッスン22などで自分で追加した関数（必殺技など）があれば、それも探しておきましょう。

- [ ] それぞれの関数を見つけられたらチェック！

---

## ミッション2　今のプログラムを新しい名前で保存しよう

1. Arduino IDEで、今使っている自分の対戦プログラムを開きます。
2. **ファイル → 名前を付けて保存**を選びます。
3. いつもと同じように、**日付4桁＋名前（英語）** で名前を付けます。例えば、11月19日にたろうさんが保存するなら `1119taro` です。
4. 元のプログラムはそのまま残るので、うまくいかなくなってもいつでも戻せます。

このテキストでは、例として `1119taro` という名前で説明します。`1119taro` と書いてあるところは、**自分のファイル名に読みかえて**ください。また、`1119taro` のタブのことを**メインのタブ**と呼びます。

- [ ] 新しい名前で保存できたらチェック！

---

## ミッション3　完成形の構成を確認しよう

ファイルを作り始める前に、最後にどんな形になるのかを確認しておきましょう。

完成すると、`1119taro` フォルダの中は次のようになります。

```text
1119taro/
├── 1119taro.ino    ← メインのファイル。共有する変数、#include、setup()、loop()
├── config.h        ← ピン番号・定数・チームの設定
├── motor.h         ← モーターの動作
├── sound.h         ← ブザー
├── battle.h        ← 赤外線攻撃・被弾時の処理
├── hissatsu.h      ← 必殺技（レッスン22で作った人だけ）
└── bluetooth.h     ← Bluetooth通信
```

それぞれのファイルに入れるものは、次のとおりです。

| ファイル | 入れるもの | 作るミッション |
|---|---|---|
| `config.h` | `#define` で始まる行（ピン番号・スピード・チームの設定） | ミッション4 |
| `motor.h` | `set_Motorspeed()`、`go_Advance()`、`go_Left()`、`go_Right()`、`go_Back()`、`back_Left()`、`back_Right()`、`stop_Stop()` | ミッション5 |
| `sound.h` | `buzz_ON()`、`buzz_OFF()`、`alarm()` | ミッション6 |
| `battle.h` | `shoot()`、`deadAlarm()` | ミッション6 |
| `hissatsu.h` | レッスン22で作った `hissatsu()` などの必殺技 | ミッション6 |
| `bluetooth.h` | `do_Uart_Tick()` | ミッション6 |
| `1119taro.ino` | ライブラリの読み込み、共有するオブジェクト・変数、`#include`、`setup()`、`loop()` | 残ったもの |

全部できあがると、`1119taro.ino` は次のような形になります（`...` は中身を省略しています）。

```cpp
#include <SoftwareSerial.h>
SoftwareSerial BTSerial(4, 5);  //RX,TX
#include <IRremote.h>
#include "config.h"          // ← ミッション4で追加

IRrecv irrecv(RECV_PIN);
IRsend irsend;
decode_results results;
int buttonState;

char buffUART[MAX_PACKETSIZE];
unsigned int buffUARTIndex = 0;
unsigned long preUARTTick = 0;
#include "motor.h"           // ← ミッション5で追加
#include "sound.h"           // ← ミッション6で追加
#include "battle.h"          // ← ミッション6で追加
#include "hissatsu.h"        // ← ミッション6で追加（必殺技を作った人だけ）
#include "bluetooth.h"       // ← ミッション6で追加

void setup()
{
  ...
}
int lastButtonState=0;
void loop()
{
  ...
}
```

### `#include` の順番にはルールがある

`.h` ファイルは、`#include` を書いた**上から順番に**読み込まれます。そして `.h` ファイルの中では、**使う関数や変数が、それより先に読み込まれている**必要があります。

| 順番 | ファイル | この順番になる理由 |
|---|---|---|
| 1 | `config.h` | ピン番号などは、ほかの全部のファイルが使うので最初 |
| 2 | `motor.h` | ほかのファイルの関数を使わない |
| 3 | `sound.h` | ほかのファイルの関数を使わない |
| 4 | `battle.h` | `deadAlarm()` が `motor.h` の `stop_Stop()` を使う |
| 5 | `hissatsu.h` | 必殺技は、走る・撃つ・鳴らす関数を使う |
| 6 | `bluetooth.h` | `do_Uart_Tick()` が、アプリのボタンに合わせて全部の関数を呼ぶので最後 |

共有する変数（`BTSerial` や `buttonState` など）も `.h` ファイルの中で使われるので、`#include "motor.h"` より上に書いておきます。

**`#include` の順番は「読み込む順番」です。ロボットが動く順番ではありません。** 動く順番を決めるのは、これまでどおり `setup()` と `loop()` です。

- [ ] 完成形の構成と、`#include` の順番のルールを確認できたらチェック！

---

## ミッション4　最初の `.h` ファイル `config.h` を作ろう

まずは、いちばん簡単な `config.h` から作ります。ここで `.h` ファイルの作り方を覚えましょう。

#### 手順1　新しいタブを作る

1. Arduino IDEのタブが並んでいる行の右はしにある **「…」ボタン**をクリックします。
2. **新規タブ**を選びます（`Ctrl` + `Shift` + `N` でもできます）。
3. ファイル名を聞かれるので、`config.h` と入力して **OK** を押します。**`.h` まで入力**しましょう。`.h` を書き忘れると `.ino` のファイルになってしまいます。
4. `config.h` というタブが増えたら成功です。

#### 手順2　1行目に `#pragma once` と書く

`config.h` のタブを開いて、1行目に次のように書きます。

```cpp
#pragma once
```

`#pragma once` は、「このファイルは1回だけ読み込んでね」という命令です。これから作る `.h` ファイルには、全部この1行を最初に書きます。

#### 手順3　`#define` の行を切り取って貼り付ける

1. メインのタブに戻ります。
2. `#define` で始まる行を探して、**切り取り**（`Ctrl` + `X`）ます。チームの設定の、`// #define` で始まる行（コメントアウトしてある行）もいっしょに切り取ります。
3. `config.h` のタブを開いて、`#pragma once` の下に**貼り付け**（`Ctrl` + `V`）ます。
4. これを、メインのタブに `#define` が1つもなくなるまでくり返します。

レッスン21のサンプルから変えていなければ、切り取る `#define` は次の16行です。自分で `#define` を追加した人は、それもいっしょに移しましょう。

- `RECV_PIN`、`BUZZ_PIN`、`LED_PIN`（センサー・ブザー・LEDのピン）
- `IR_BULLET`、`MY_BULLET`（チームの設定。コメントアウトしてある行も入れて4行）
- `dir1PinRight` 〜 `dir2PinLeft`（モーターのピン、6行）
- `SPEED`、`TURNSPEED`（スピード）
- `MAX_PACKETSIZE`（Bluetoothの受信バッファの大きさ）

貼り付けが終わると、`config.h` はこのようになります（並び順はちがっていてもOKです。スピードなどの数字を変えている人は、自分の数字のままでOKです）。

```cpp
#pragma once

#define RECV_PIN   10 // IR receiver pin connect to D10
#define BUZZ_PIN     13  //buzzer connect to D13
#define IR_BULLET      0xAAA       //Aの時はこちらを使う。Bの時はコメントアウト
#define MY_BULLET      0xBBB       //Aの時はこちらを使う。Bの時はコメントアウト
// #define IR_BULLET      0xBBB       //Bの時はこちらを使う。Aの時はコメントアウト
// #define MY_BULLET      0xAAA       //Bの時はこちらを使う。Aの時はコメントアウト
#define LED_PIN 2
#define dir1PinRight   12  // Right Motor direction pin 1 to MODEL-X IN1
#define dir2PinRight  11   // Right Motor direction pin 2 to MODEL-X IN2
#define speedPinRight 9   //RIGHT PWM pin connect MODEL-X ENA
#define speedPinLeft 6    // Left PWM pin connect MODEL-X ENB
#define dir1PinLeft  7    //Left Motor direction pin 1 to MODEL-X IN3
#define dir2PinLeft  8    //Left Motor direction pin 2 to MODEL-X IN4
#define SPEED   150  //avoidance motor speed
#define TURNSPEED  200     //back speed
#define MAX_PACKETSIZE 32    //Serial receive buffer
```

**注意：** 同じ `#define` を、メインのタブと `config.h` の二か所に書かないようにしましょう。Bチームの人は、Bチームの設定が有効になっていること（`0xBBB` の `IR_BULLET` が `//` なしになっていること）を確認します。

#### 手順4　`1119taro.ino` に `#include "config.h"` を書く

メインのタブに戻り、`#include <IRremote.h>` の**すぐ下**に1行追加します。

```cpp
#include <SoftwareSerial.h>
SoftwareSerial BTSerial(4, 5);  //RX,TX
#include <IRremote.h>
#include "config.h"          // ← この行を追加する

IRrecv irrecv(RECV_PIN);
```

`#include "config.h"` は、コンパイルする前に、`config.h` の中身をこの場所に展開する（はりつける）命令です。ロボットが動いている最中に読み込むわけではありません。

`IRrecv irrecv(RECV_PIN);` の行では `RECV_PIN` を使っているので、`#include "config.h"` はそれより上に書く必要があります。

#### 手順5　検証してみる

Arduino IDEの**検証（チェックマーク）**を押します。エラーが出なければ成功です。

`'RECV_PIN' was not declared in this scope` のようなエラーが出たときは、`#include "config.h"` を書いた場所を確認しましょう。

- [ ] `config.h` に `#define` を移して、エラーなく検証できたらチェック！

---

## ミッション5　`motor.h` を作ろう

次は、モーターの関数を `motor.h` に移します。関数を移すときは、`void 関数名()` の行から、その関数の最後の `}` までを**まとめて**切り取ります。

#### 手順1　新しいタブ `motor.h` を作る

ミッション4と同じように、**「…」ボタン → 新規タブ**で、`motor.h` という名前のタブを作ります。

#### 手順2　1行目に `#pragma once` と書く

```cpp
#pragma once
```

#### 手順3　`set_Motorspeed()` を切り取って貼り付ける

メインのタブで、次の部分を探します（`stop_Stop()` のすぐ下にあります）。

```cpp
/*set motor speed */
void set_Motorspeed(int speed_L,int speed_R)
{
  analogWrite(speedPinRight,speed_R); 
  analogWrite(speedPinLeft,speed_L);   
}
```

`/*set motor speed */` の行から最後の `}` までを選んで**切り取り**、`motor.h` の `#pragma once` の下に**貼り付け**ます。

#### 手順4　`go_Advance()` 〜 `stop_Stop()` を切り取って貼り付ける

メインのタブで、`/*motor control*/` の行を探します。そこから、`stop_Stop()` の最後の `}` までを選んで**切り取り**ます。

```cpp
/*motor control*/                 ← ここから
void go_Advance(void)  //Forward
{
  ...
}
void go_Left()  //Turn left
  ...
void stop_Stop()    //Stop
{
  digitalWrite(dir1PinRight, LOW);
  digitalWrite(dir2PinRight,LOW);
  digitalWrite(dir1PinLeft,LOW);
  digitalWrite(dir2PinLeft,LOW);
  set_Motorspeed(0,0);
}                                 ← ここまで
```

`motor.h` のタブを開いて、手順3で貼り付けた `set_Motorspeed()` の**下**に貼り付けます。

貼り付けが終わると、`motor.h` はこのような形になります。

```cpp
#pragma once

/*set motor speed */
void set_Motorspeed(int speed_L,int speed_R)
{
  ...
}
/*motor control*/
void go_Advance(void)  //Forward
{
  ...
}
void go_Left()  //Turn left
  ...
void stop_Stop()    //Stop
{
  ...
}
```

**大切！ どうして `set_Motorspeed()` をいちばん上にするの？**
`go_Advance()` などの関数は、中で `set_Motorspeed()` を使っています。`.ino` ファイルの中なら、Arduino IDEが関数の順番を気にしなくても動くようにしてくれます。でも `.h` ファイルの中ではそうしてくれないので、**使う関数を先に書いておく**必要があるのです。

#### 手順5　`1119taro.ino` に `#include "motor.h"` を書く

メインのタブに戻り、`unsigned long preUARTTick = 0;` の行の**すぐ下**に1行追加します。

```cpp
char buffUART[MAX_PACKETSIZE];
unsigned int buffUARTIndex = 0;
unsigned long preUARTTick = 0;
#include "motor.h"           // ← この行を追加する
```

メインのタブに、モーターの関数（`go_Advance()` 〜 `stop_Stop()`、`set_Motorspeed()`）が残っていないことも確認しましょう。

#### 手順6　検証してみる

**検証（チェックマーク）**を押して、エラーが出なければ成功です。

- [ ] `motor.h` にモーターの関数を移せたらチェック！
- [ ] エラーなく検証できたらチェック！

---

## ミッション6　残りのファイルも作ろう

残りのファイルも、ミッション5と同じ手順で作ります。

1. **「…」ボタン → 新規タブ**で、`.h` ファイルを作る
2. 1行目に `#pragma once` と書く
3. メインのタブから関数を**切り取り**、新しいタブに**貼り付け**る
4. メインのタブの、前に書いた `#include` の**すぐ下**に、新しい `#include` を1行追加する
5. **検証**して、エラーが出ないことを確かめる

ひとつ作るごとに検証しましょう。エラーが出たときに、どこでまちがえたのかがすぐに分かります。

次の表の**上から順番に**作ります。

| 順番 | ファイル名 | 切り取る部分 | 追加する `#include` |
|---|---|---|---|
| 1 | `sound.h` | `void buzz_ON()` の行から、`alarm()` の最後の `}` まで | `#include "sound.h"` |
| 2 | `battle.h` | `void shoot()` の行から、`deadAlarm()` の最後の `}` まで（`loop()` よりも下にあります） | `#include "battle.h"` |
| 3 | `hissatsu.h` | レッスン22で作った `hissatsu()` などの必殺技の関数。自分で追加したほかの関数も、ここに入れます。**作っていない人はとばしてOK** | `#include "hissatsu.h"` |
| 4 | `bluetooth.h` | `//WiFi / Bluetooth through the serial control` の行から、`do_Uart_Tick()` の最後の `}` まで | `#include "bluetooth.h"` |

全部終わると、`#include` は次のように並びます。

```cpp
unsigned long preUARTTick = 0;
#include "motor.h"
#include "sound.h"
#include "battle.h"
#include "hissatsu.h"    // 必殺技を作った人だけ
#include "bluetooth.h"
```

**注意：**

- 関数の中身は、この段階では変更しません。`deadAlarm()` にある停止後の無限ループも、元の対戦ルールの一部としてそのまま残します。
- 必殺技をボタンに割り当てている `case 'G': hissatsu();break;` などの行は、`do_Uart_Tick()` の switch 文の中にあります。`bluetooth.h` にそのまま移しましょう。
- `battle.h` の `shoot()` と `deadAlarm()` は、元のプログラムでは `loop()` より下にありました。でも `#include "battle.h"` は、`loop()` の下ではなく、`#include "sound.h"` の下に書きます。

最後にメインのタブを見て、残っているのが次のものだけになっているか確認しましょう。

- ライブラリの読み込み（`#include <SoftwareSerial.h>` など）と `#include "〇〇.h"` の行
- 共有するオブジェクト・変数（`BTSerial`、`irrecv`、`irsend`、`results`、`buttonState`、`buffUART`、`buffUARTIndex`、`preUARTTick`、`lastButtonState`）
  - 自分で追加した変数があれば、それも残します。`.h` ファイルの中で使う変数は、`#include "motor.h"` より上に移しておきましょう。
- `setup()` と `loop()`

使われなくなった `//car motor control` のようなコメントは消してもかまいません。

- [ ] `sound.h` を作れたらチェック！
- [ ] `battle.h` を作れたらチェック！
- [ ] `hissatsu.h` を作れたらチェック！（必殺技を作った人だけ）
- [ ] `bluetooth.h` を作れたらチェック！
- [ ] メインのタブに、`setup()` と `loop()` 以外の関数が残っていないことを確認できたらチェック！

---

## ミッション7　コンパイルして確かめよう

最後にもう一度、**検証（チェックマーク）**を押して、全体がコンパイルできるか確かめましょう。

エラーが出たら、次の点を確認します。

1. `#include "config.h"` などのファイル名が正しく書かれているか
2. **`〜 was not declared in this scope` と出たら、読み込む順番を確認する。** 「〜」の関数や変数が、それを使うファイルよりも**後**で読み込まれていないか見てみましょう。
3. 関数や変数を、二か所に書いていないか（切り取らずにコピーしてしまっていないか）
4. 関数を移すときに `{` や `}` を消していないか、多く切り取っていないか
5. それぞれの `.h` ファイルの1行目に `#pragma once` があるか
6. タブの名前が `.h` になっているか（`.ino` になっていないか）
7. `1119taro.ino` がフォルダ名と同じ名前になっているか

例えば `#include "motor.h"` を `#include "bluetooth.h"` の下に書いてしまうと、次のようなエラーになります。

```text
battle.h:〇:〇: error: 'stop_Stop' was not declared in this scope
```

「`battle.h` の中で `stop_Stop` を使おうとしたけれど、まだ読み込まれていないよ」という意味です。

**発展：** 今回は `.h` の中に関数の中身まで書いて、`1119taro.ino` にまとめて読み込んでいます。本格的なプログラムでは、`.h` には関数の名前（宣言）だけを書き、中身は `.cpp` ファイルに書いて別々にコンパイルします。そうすると、読み込む順番を気にしなくてよくなります。

- [ ] エラーなくコンパイルできたらチェック！

### どうしてもうまくいかないときは

完成例のサンプルコードと見比べてみましょう。

[ここをクリックして完成例をダウンロード](https://github.com/kobayashi-makoto2021/robobu/raw/main/Lesson_41/sample/lesson_41_sample.zip)

ダウンロードしたZIPファイルを展開して、`lesson_41_sample.ino` を開きます。完成例はメインのファイル名が `lesson_41_sample.ino` になっていますが、中身の分け方は上の構成と同じです。完成例はレッスン21のサンプルを分けたものなので、自分で追加した必殺技などは入っていません。分け方を見比べるのに使いましょう。Bチームの人は、`config.h` のチーム設定を切りかえてから書き込みます。

---

## ミッション8　ロボットの動作を確認しよう

コンパイルに成功したら、Arduinoに書き込んで動作を確かめます。

- [ ] Bluetoothで接続できる
- [ ] 前進・後退できる
- [ ] 左右に旋回できる
- [ ] 停止できる
- [ ] 赤外線を発射できる
- [ ] 相手の弾を受信すると停止し、ブザー・LEDが動作する

**成功条件：ファイルを分ける前と同じように動くこと！**

---

## ミッションチャレンジ　整理すると何が便利になる？

次の質問を考えてみましょう。

1. モーターの速度を変更したいとき、どのファイルを開けばよいでしょうか？
2. Bluetooth通信を別の通信方式に変更するとき、どの部分を変更すればよいでしょうか？
3. `config.h` にピン番号をまとめておくと、どんな利点があるでしょうか？
4. ファイルを分けても、なぜロボットの動作は変わらないのでしょうか？

**次の発展課題：** 今回整理したプログラムのBluetooth通信部分を、レッスン18で学んだWi-Fi通信を使う仕組みに改造しよう。その後、PCにつないだゲームコントローラーからロボットを操作できるようにしていこう！

---

## まとめ

- **モジュール化**：プログラムを役割ごとに分けること
- **リファクタリング**：外から見た動作を変えずに、コードを改善すること
- **`.ino`**：スケッチのメインファイル。`setup()` と `loop()` を書き、ほかのファイルを `#include` で読み込む
- **`.h`**：`#include` で読み込むヘッダーファイル。設定や機能ごとの関数をまとめておく
- **`#include` の順番**：使う関数・変数が先に読み込まれるように並べる（ロボットが動く順番ではない）
- **`#pragma once`**：同じ `.h` を2回読み込まないようにする命令
- **`setup()` と `loop()`**：処理の流れを決める入口

### 出来たことをチェックしよう

- [ ] モジュール化とリファクタリングの意味を説明できる
- [ ] Arduino IDEで新しいタブ（ファイル）を作れる
- [ ] `.ino` と `.h` の役割の違いを説明できる
- [ ] 共通の設定をヘッダーファイルにまとめられる
- [ ] 機能別にプログラムを分けても、元どおり動かせる

---

*講師向けメモ：このレッスンは、生徒が今使っている対戦プログラム（`lesson_21_sampleA` / `B` をもとに、レッスン22で必殺技などを追加したもの）を分割する課題です。生徒ごとに追加した関数・変数や数値が異なるため、追加分は `hissatsu.h` にまとめる、`.h` で使う変数は `#include` より上に置く、の2点を中心に支援してください。保存名は教室のルール（日付4桁＋英語の名前）に合わせています。サンプルには旧版のIRremote APIが使われています。授業では元の動作環境・ライブラリ版（レッスン08で配布しているIRremote 2.2.3）を維持して実施してください。完成例 `sample/lesson_41_sample` は、Arduino Unoでコンパイルした結果（.hex）が、Aチーム設定で `lesson_21_sampleA`、Bチーム設定で `lesson_21_sampleB` と完全に一致することを確認済みです。また、元コードのBluetooth受信バッファ処理には境界チェック上の問題があるため、別途安全性の改善を行う場合は「動作を変えないリファクタリング」と切り分けて扱ってください。*
