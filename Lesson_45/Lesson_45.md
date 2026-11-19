# レッスン45　アナログスティックでロボットを自在に動かそう！

## 今回の目的：スティックの傾きをモーターの速さに変える

レッスン44では、十字キーの上下左右をHTTP命令に変えてロボットを動かしました。十字キーは「押している／押していない」の二択でしたね。

今回は**アナログスティック**を使います。少し倒せばゆっくり、大きく倒せば速く動かせるようにしましょう。

> **今日のゴール：** アナログスティックで前後進・旋回・カーブを操作し、左右のモーターの速さがどう決まるか説明できる。**戦車方式**と**アーケード方式**の2つを試して、くらべてみよう。

### このレッスンで身につける力

- [ ] デジタル（押す・押さない）とアナログ（倒した大きさ）の入力のちがいを説明できる
- [ ] アナログスティックの値を読み取って、画面に表示できる
- [ ] デッドゾーンの役割を説明できる
- [ ] 戦車方式とアーケード方式で、左右のモーターの速さがどう決まるか説明できる
- [ ] ロボット側に、左右のモーターの速さを別々に決める命令（`/D`）を追加できる
- [ ] 2つの方式で走らせて、操作のしやすさをくらべられる

---

## ミッション1　デジタルとアナログの違いを考えよう

| 入力 | 読み取れる値 | ロボットの動かし方 |
|---|---|---|
| 十字キー | 押した／離した | 決められた方向へ動く |
| アナログスティック | おおむね -1.0 ～ +1.0 | 倒した向きと大きさに応じて動く |

十字キーのように「押した・押していない」の2つしかない入力を**デジタル**、スティックのように「どのくらい倒したか」を細かい数で表す入力を**アナログ**といいます。

ゲームパッドのスティックの値は、`pad.axes[番号]` で読み取れます（`axes` は「軸」という意味）。F310では、ふつう次のようになっています。

| 番号 | スティック | 値の向き |
|---|---|---|
| `axes[0]` | 左スティックの左右 | 左がマイナス、右がプラス |
| `axes[1]` | 左スティックの上下 | **上がマイナス**、下がプラス |
| `axes[2]` | 右スティックの左右 | 左がマイナス、右がプラス |
| `axes[3]` | 右スティックの上下 | **上がマイナス**、下がプラス |

ただし、**番号や向きは、ミッション3で作るページで実際に確かめます。**

**考えてみよう：** スティックを半分だけ倒したとき、モーターを半分の速さにできたら何が便利でしょうか？

---

## ミッション2　ロボット側に「左右の速さ」の命令を追加しよう

レッスン42〜44のロボットは、`/M`（前進）や `/L`（左）のように、**方向だけ**を受け取っていました。スピードは `config.h` の `SPEED` と `TURNSPEED` で決まっていて、変えられません。

スティックでなめらかに動かすには、**左のモーターと右のモーターの速さを、別々に送る**必要があります。そこで、新しい命令 `/D` を追加します（Dは Drive〈運転する〉の頭文字です）。

```http
GET /D?l=204&r=102 HTTP/1.1
```

- `?` のうしろは、命令に付ける**数のメモ**です。`&` で区切って、いくつも書けます。
- `l` は左（left）モーター、`r` は右（right）モーターの速さです。
- 数は `-255` ～ `255` です。**プラスは前進、マイナスは後退、0は停止**です。`255` は、Arduinoのモーターのいちばん速い値です。

例えば、`/D?l=0&r=0` は停止、`/D?l=255&r=-255` はその場で右に回る、という意味になります。

#### 手順1　今のプログラムを新しい名前で保存する

1. Arduino IDEで、レッスン42で作ったロボットのプログラムを開きます。
2. **ファイル → 名前を付けて保存** で、いつもと同じように **日付4桁＋名前（英語）**（例：`1210taro`）で保存します。

#### 手順2　`motor.h` に `drive()` を追加する

`motor.h` のタブを開いて、**いちばん下**（`stop_Stop()` の最後の `}` の下）に、次のプログラムを貼り付けます。

```cpp
// ---- レッスン45で追加：左右のモーターの速さを、別々に決める ----
// left・right は -255〜255。プラスは前進、マイナスは後退、0は停止。
void drive(int left, int right)
{
  left  = constrain(left,  -255, 255);   // -255〜255 の外に出ないようにする
  right = constrain(right, -255, 255);

  // 右モーターの向き（go_Advance() と同じ向きが前進）
  if (right >= 0) {
    digitalWrite(dir1PinRight, HIGH);
    digitalWrite(dir2PinRight, LOW);
  } else {
    digitalWrite(dir1PinRight, LOW);
    digitalWrite(dir2PinRight, HIGH);
  }

  // 左モーターの向き
  if (left >= 0) {
    digitalWrite(dir1PinLeft, HIGH);
    digitalWrite(dir2PinLeft, LOW);
  } else {
    digitalWrite(dir1PinLeft, LOW);
    digitalWrite(dir2PinLeft, HIGH);
  }

  // 速さは、マイナスを取った大きさ（abs）で決める
  set_Motorspeed(abs(left), abs(right));
}
```

- `drive(左の速さ, 右の速さ)` で、左右のモーターを別々に動かせます。
- 速さがプラスなら、`go_Advance()` と同じ向き（前進）にモーターを回します。マイナスなら、反対の向き（後退）に回します。
- `abs()` は、マイナスを取った大きさにする命令です（例：`abs(-102)` は `102`）。モーターの速さ（PWM）はマイナスにできないので、向きと大きさを分けて決めています。
- `constrain(値, 下, 上)` は、値が `下`〜`上` の外に出ないようにする命令です。

#### 手順3　`http.h` に `/D` を受け取る処理を追加する

`http.h` のタブを開いて、2か所を追加します。

**① `setDrive()` 関数を追加する**

`setMoveTime()` 関数の最後の `}` の下（`// ---- 命令の1文字に合わせて、ロボットを動かす ----` の上）に、次のプログラムを貼り付けます。

```cpp
// ---- レッスン45で追加：スティックから届いた左右の速さで、ロボットを動かす ----
// 例：「GET /D?l=204&r=-102 HTTP/1.1」→ 左 204、右 -102
void setDrive(String request)
{
  int l = request.indexOf("l=");   // 「l=」の場所
  int r = request.indexOf("r=");   // 「r=」の場所
  if (l < 0 || r < 0) return;      // 見つからなければ何もしない

  int left  = request.substring(l + 2).toInt();  // 「l=」のうしろの数字
  int right = request.substring(r + 2).toInt();  // 「r=」のうしろの数字
  drive(left, right);              // motor.h の drive() で、左右べつべつに動かす

  moving = true;          // 時計をスタート（moveTime たったら止まる）
  moveStart = millis();
  Serial.print("左: ");
  Serial.print(left);
  Serial.print("  右: ");
  Serial.println(right);
}
```

- `request.indexOf("l=")` で、リクエストの中の `l=` の場所をさがします。
- `request.substring(l + 2).toInt()` で、`l=` のうしろの数字を読み取ります（`-` が付いていれば、マイナスの数として読めます）。
- 読み取った2つの数を、手順2で作った `drive()` にわたします。
- `/M` などと同じように、`moveTime` の時計もスタートさせます。命令が届かなくなったら、`moveTime` がたったところで止まります。

**② `do_Http_Tick()` に、`D` のときの1行を足す**

`do_Http_Tick()` の中の、`cmd == 'T'` の行のすぐ下に1行足します。

```cpp
        if (cmd == 'T') setMoveTime(request);   // スライダーの時間
        else if (cmd == 'D') setDrive(request); // ← この行を足す
        else if (isQuick(cmd)) doCommand(cmd);  // モーターの命令は、すぐ実行
```

#### 手順4　検証して、書き込む

**検証（チェックマーク）**を押して、エラーが出なければ、ロボットに書き込みます。**車輪は浮かせておきましょう。**

`/M` などの今までの命令も、そのまま使えます。レッスン42の操作画面や、レッスン44の `controller.html` でも、今までどおり動かせます。

**うまくいかないときは：** 完成例をダウンロードして、見くらべましょう。書き込む前に、`config.h` のWi-Fiの名前とパスワードを書きかえます。

[ここをクリックしてロボットカー側のプログラム（完成例）をダウンロード](https://github.com/kobayashi-makoto2021/robobu/raw/main/Lesson_45/sample/lesson_45_sample.zip)

- [ ] `motor.h` に `drive()` を追加できたらチェック！
- [ ] `http.h` に `/D` を受け取る処理を追加して、書き込めたらチェック！

---

## ミッション3　スティックで操作するページを作ろう

#### 手順1　`stick_controller.html` を作る

レッスン44の `controller.html` と同じフォルダーに、`stick_controller.html` というファイルを作ります。作り方は、レッスン43のミッション3の手順3と同じです（メモ帳なら、ファイルの種類を **すべてのファイル (\*.\*)**、エンコードを **UTF-8** にして保存します）。

下の灰色のわくの右上にある**コピーボタン**で、わくの中を全部コピーして貼り付けます。1行目が `<!DOCTYPE html>` になっているか確かめましょう。

```html
<!DOCTYPE html>
<html lang="ja">
<head>
  <meta charset="UTF-8">
  <title>レッスン45 スティック操作</title>
</head>
<body>
  <h1>アナログスティックでロボットを動かそう！</h1>

  <p>ロボットのIPアドレス：
    <input id="ip" type="text" placeholder="192.168.〇.〇">
  </p>

  <p>1回に動く時間：<b id="t">1000</b> ミリ秒</p>
  <input id="time" type="range" min="100" max="2000" step="100" value="1000">

  <p>操作のしかた：
    <label><input type="radio" name="mode" value="arcade" checked> アーケード方式（左スティック1本）</label>
    <label><input type="radio" name="mode" value="tank"> 戦車方式（左右のスティック）</label>
  </p>

  <p id="axes">スティックの値：</p>
  <p id="state">ゲームパッドのボタンを1回押してください</p>
  <p id="error"></p>

  <script>
    // ★ レッスン43・45で調べたスティックの番号に書きかえる（以下は例）
    const LEFT_X = 0;    // 左スティックの 左右
    const LEFT_Y = 1;    // 左スティックの 上下
    const RIGHT_Y = 3;   // 右スティックの 上下（戦車方式で使う）

    const ipBox = document.getElementById("ip");         // IPアドレスの入力らん
    const timeSlider = document.getElementById("time");  // 動く時間のスライダー

    let sending = false;                  // 今、ロボットに送っているところか
    let timeToSend = timeSlider.value;    // まだ送っていない「動く時間」（はじめに1回送る）
    let lastSent = "0,0";                 // さっき送った左右の速さ

    // 前に入れたIPアドレスを、ブラウザに覚えておいてもらう
    ipBox.value = localStorage.getItem("robotIP") || "";
    ipBox.addEventListener("change", () => {
      localStorage.setItem("robotIP", ipBox.value);
      timeToSend = timeSlider.value;
    });

    // スライダーを動かすと数字が変わり、手をはなすと動く時間を送る
    timeSlider.addEventListener("input", () => {
      document.getElementById("t").textContent = timeSlider.value;
    });
    timeSlider.addEventListener("change", () => {
      timeToSend = timeSlider.value;
    });

    // 入力されたIPアドレスから、ロボットのアドレスを作る
    function robotURL() {
      let ip = ipBox.value.trim();
      ip = ip.replace(/^https?:\/\//, "");   // http:// を入れていたら取る
      ip = ip.replace(/\/+$/, "");           // 最後の / を取る
      return "http://" + ip;
    }

    // スティックの小さなゆれを 0 にする（デッドゾーン）
    function deadZone(value) {
      return Math.abs(value) < 0.12 ? 0 : value;
    }

    // -1.0〜1.0 の値を、-255〜255 のモーターの速さに直す
    function toSpeed(value) {
      return Math.round(value * 255);
    }

    // アーケード方式：左スティック1本で、前後の速さと曲がる強さを決める
    function arcadeMix(x, y) {
      const forward = -deadZone(y);   // 上がマイナスなので、- を付けて「上＝前進」にする
      const turn = deadZone(x);       // 右がプラス
      let left = forward + turn;
      let right = forward - turn;
      // 1 をこえたら、左右の比率をそのままにして小さくする
      const scale = Math.max(1, Math.abs(left), Math.abs(right));
      return { left: toSpeed(left / scale), right: toSpeed(right / scale) };
    }

    // 戦車方式：左スティックの上下で左モーター、右スティックの上下で右モーター
    function tankMix(leftY, rightY) {
      return { left: toSpeed(-deadZone(leftY)), right: toSpeed(-deadZone(rightY)) };
    }

    // ロボットに命令を送る（返事が来るまで待つ。そのあいだは次を送らない）
    async function send(path) {
      sending = true;
      try {
        await fetch(robotURL() + path, {
          mode: "no-cors",
          cache: "no-store",
          signal: AbortSignal.timeout(2000)   // 2秒たっても返事がなければ、あきらめる
        });
        document.getElementById("error").textContent = "";
      } catch (e) {
        document.getElementById("error").textContent =
          "ロボットにつながりません。IPアドレスを確かめましょう";
      }
      sending = false;
    }

    function update() {
      const pad = Array.from(navigator.getGamepads()).find(p => p !== null);
      let speed = { left: 0, right: 0 };

      if (pad) {
        // スティックの値を画面に表示する
        document.getElementById("axes").textContent =
          "スティックの値：" +
          pad.axes.map((v, n) => n + "番=" + v.toFixed(2)).join("　");

        // えらんだ方式で、左右の速さを計算する
        const mode = document.querySelector('input[name="mode"]:checked').value;
        if (mode === "arcade") {
          speed = arcadeMix(pad.axes[LEFT_X], pad.axes[LEFT_Y]);
        } else {
          speed = tankMix(pad.axes[LEFT_Y], pad.axes[RIGHT_Y]);
        }
      }

      document.getElementById("state").textContent =
        "左モーター：" + speed.left + "　右モーター：" + speed.right;

      const now = speed.left + "," + speed.right;
      if (ipBox.value.trim() === "") {
        document.getElementById("error").textContent =
          "ロボットのIPアドレスを入れてください";
      } else if (!sending) {
        if (timeToSend !== null) {
          send("/T" + timeToSend);          // 動く時間が変わっていたら、先にそれを送る
          timeToSend = null;
        } else if (now !== "0,0" || lastSent !== "0,0") {
          // ・スティックを倒しているあいだは、くり返し送る
          // ・はなしたときは、0,0（停止）を1回だけ送る
          send("/D?l=" + speed.left + "&r=" + speed.right);
          lastSent = now;
        }
      }
      requestAnimationFrame(update);
    }

    update();
  </script>
</body>
</html>
```

#### 手順2　ページを開いて、スティックの値を確かめる

1. レッスン43・44と同じように、フォルダーで Webサーバーを起動します（`python -m http.server 8000`）。
2. Chromeで `http://localhost:8000/stick_controller.html` を開きます。
3. 「ロボットのIPアドレス」に、ロボットのIPアドレスを入れて `Enter` を押します（レッスン44で入れていれば、もう入っています）。
4. ゲームパッドのボタンを**一度押して**、ゲームパッドを見つけてもらいます。
5. 「スティックの値：」のところに、`0番=0.00　1番=0.00　…` のように、スティックの値が表示されます。スティックを動かして、どの番号の値が変わるか確かめましょう。

調べた番号と向きを、**ノートに表を書いて記録**しましょう。

| スティックの動き | 値が変わった番号 | 値（プラス・マイナス） |
|---|---|---|
| 左スティックを右へ | | |
| 左スティックを上へ | | |
| 右スティックを上へ | | |

番号がミッション1の表とちがっていたら、`stick_controller.html` の `★` のところ（`LEFT_X`・`LEFT_Y`・`RIGHT_Y`）を、ノートの番号に書きかえて保存し、`F5` で読みこみ直します。

- [ ] 左に倒すと、左右の値がマイナスになった
- [ ] 上に倒すと、上下の値がマイナスになった
- [ ] 少し倒した場合と大きく倒した場合で、数値がちがった

#### 手順3　デッドゾーンを知ろう

スティックから手を離しても、値がぴったり `0.00` にならず、`0.02` や `-0.04` のようになることがあります。このままだと、手を離してもロボットが少しずつ動いてしまいます。

そこで、`0` に近い小さなゆれは `0` と考えることにします。この「無視する範囲」を**デッドゾーン**といいます。

```javascript
function deadZone(value) {
  return Math.abs(value) < 0.12 ? 0 : value;
}
```

- `Math.abs(value)` は、マイナスを取った大きさです（Arduinoの `abs()` と同じ）。
- 大きさが `0.12` より小さければ `0`、そうでなければそのままの値を返します（`? :` はレッスン43で出てきた、短い `if` 文です）。

---

## ミッション4　左右のモーターに分けて考えよう

ロボットには、左と右の2つのモーターがあります。スティックの値から、2つのモーターの速さを決める方法を2つ考えます。ページの「操作のしかた」で、どちらの方式か選べます。

### 方法A　左右独立の「戦車方式」

**左スティックの上下で左モーター、右スティックの上下で右モーター**を操作します。戦車やショベルカーのような動かし方です。

```javascript
function tankMix(leftY, rightY) {
  return { left: toSpeed(-deadZone(leftY)), right: toSpeed(-deadZone(rightY)) };
}
```

- スティックは**上がマイナス**なので、`-` を付けて「上に倒す＝プラス＝前進」にしています。
- `toSpeed()` は、`-1.0`〜`1.0` の値に `255` をかけて、`-255`〜`255` のモーターの速さに直す関数です。

左右の速さを別々に決められるので、細かい動きができます。でも、2本のスティックを同時に動かす必要があります。

### 方法B　1本の「アーケード方式」

**左スティック1本**で、上下を**前後の速さ**、左右を**曲がる強さ**として使います。

```text
前後の速さ = -スティックの上下の値
曲がる強さ =  スティックの左右の値

左モーター = 前後の速さ + 曲がる強さ
右モーター = 前後の速さ - 曲がる強さ
```

例えば、前後の速さが `0.6`、曲がる強さが `0.2` なら、左モーターは `0.8`、右モーターは `0.4` です。左が速いので右へ曲がります。

計算した結果が `1` をこえることがあります（例：前後 `1.0`、曲がる強さ `0.5` → 左 `1.5`）。そのときは、左右の比率をそのままにして、大きいほうが `1` になるように小さくします。

```javascript
function arcadeMix(x, y) {
  const forward = -deadZone(y);   // 上がマイナスなので、- を付けて「上＝前進」にする
  const turn = deadZone(x);       // 右がプラス
  let left = forward + turn;
  let right = forward - turn;
  // 1 をこえたら、左右の比率をそのままにして小さくする
  const scale = Math.max(1, Math.abs(left), Math.abs(right));
  return { left: toSpeed(left / scale), right: toSpeed(right / scale) };
}
```

- `Math.max(1, A, B)` は、`1`・`A`・`B` の中でいちばん大きい数です。左右どちらも `1` 以下なら `scale` は `1` なので、そのままの値になります。

**計算してみよう：** ノートに計算して、ページの「左モーター・右モーター」の表示と、答え合わせをしましょう。

1. `x=0`、`y=-0.5`（上に半分）のとき、左右のモーターの速さは？
2. `x=1`、`y=0`（右にいっぱい）のとき、左右のモーターの速さは？
3. `x=0.2`、`y=-0.6`（上＋少し右）のとき、左右のモーターの速さは？

### 送るところは、レッスン44と同じしくみ

```javascript
} else if (now !== "0,0" || lastSent !== "0,0") {
  send("/D?l=" + speed.left + "&r=" + speed.right);
  lastSent = now;
}
```

レッスン44で十字キーを押している間 `/M` を送り続けたのと同じように、**スティックを倒している間は `/D?l=...&r=...` を送り続け**、離したら `/D?l=0&r=0`（停止）を1回だけ送ります。

---

## ミッション5　動きを試してみよう

**最初は必ず車輪を浮かせて試します。** 次の操作を試して、結果を**ノートに表を書いて記録**しましょう。

| スティック操作（アーケード方式） | 左モーター | 右モーター | 予想する動き | 実際の動き |
|---|---|---|---|---|
| 上に半分 | 前進・中速 | 前進・中速 | ゆっくり前進 | |
| 上にいっぱい | 前進・高速 | 前進・高速 | 速く前進 | |
| 右にいっぱい | 前進 | 後退 | その場で右旋回 | |
| 上＋少し右 | 速め | 遅め | 右カーブ | |
| 手を離す | 停止 | 停止 | 停止 | |

できたら、**戦車方式**にも切りかえて、同じように試してみましょう。

**くらべてみよう：** 戦車方式とアーケード方式、どちらが操作しやすかったでしょうか？ まっすぐ進む、カーブする、その場で回る、それぞれのやりやすさをノートに書きましょう。

**発展実験①：** スティックを少しだけ倒すと、画面ではモーターの速さが `50` などになっているのに、ロボットが動かないことがあります。なぜでしょう？（ヒント：モーターは、ある程度の強さがないと回り始めません）

**発展実験②：** `deadZone()` の `0.12` を `0.05` や `0.25` に変えると、操作感はどう変わるでしょうか？

---

## まとめ

十字キーでは「どの方向に動くか」を選びました。アナログスティックでは、**どの方向へ、どのくらいの速さで動くか**を数値で指定できます。入力の数値を計算して出力に変えることが、ロボット制御の大切な考え方です。

- **デジタル**：「押した・押していない」のように、2つの状態しかない入力
- **アナログ**：「どのくらい倒したか」のように、細かい数で表す入力
- **`pad.axes[番号]`**：スティックの値（`-1.0`〜`1.0`）
- **デッドゾーン**：`0` に近い小さなゆれを、`0` と考える範囲
- **戦車方式**：左右のスティックで、左右のモーターを別々に動かす
- **アーケード方式**：1本のスティックで、前後の速さと曲がる強さを決める
- **`/D?l=〇&r=〇`**：左右のモーターの速さを送る命令（`?` のうしろは数のメモ）

### 出来たことをチェックしよう

- [ ] デジタル（押す・押さない）とアナログ（倒した大きさ）の入力のちがいを説明できる
- [ ] アナログスティックの値を読み取って、画面に表示できる
- [ ] デッドゾーンの役割を説明できる
- [ ] 戦車方式とアーケード方式で、左右のモーターの速さがどう決まるか説明できる
- [ ] ロボット側に、左右のモーターの速さを別々に決める命令（`/D`）を追加できる
- [ ] 2つの方式で走らせて、操作のしやすさをくらべられる

### 次回：レッスン46「各ボタンに動きを割り当てよう！」

ゲームパッドのA・B・X・Yなどに、自分で考えたロボットの動きを割り当てます。

---

*講師向けメモ：原稿段階ではPCの中継サーバー（`relay.py`）と `/drive?l=&r=` を使う案でしたが、レッスン42〜44と同じく中継なし（`fetch` の `no-cors`）とし、命令はこれまでの「`/` の次の1文字」に合わせて `/D?l=〇&r=〇` にしています。ロボット側は、`motor.h` に `drive()`（左右のPWMと向きを別々に設定）、`http.h` に `setDrive()` と `do_Http_Tick()` の1行を追加します（完成例 `sample/lesson_45_sample`、Arduino Uno でフラッシュ78%・RAM55%）。`/D` も `moveTime` の時計をスタートさせるので、通信が途絶えても `moveTime`（ページを開いたときに1000ミリ秒を送る）で停止します。9600bps のため、スティックの動きがロボットに伝わるまで0.5秒前後おくれることがあります。モーターは小さいPWM値では回らない（不感帯）ため、低速側は実機で確認してください。F310をXモードにしたときの標準的な軸番号は 左スティック 左右=0・上下=1、右スティック 左右=2・上下=3（上がマイナス）です。**この構成は実機での確認がまだです。***
