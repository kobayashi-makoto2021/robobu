# トラッキングセンサーを使ってみよう！

## トラッキングセンサーの使い方を学ぼう

### このレッスンで身につける力

- [ ] ブレッドボードにトラッキングセンサーを使った回路を作ることができる
- [ ] トラッキングセンサーの感度を調整できる
- [ ] サンプルコードが実行できる
- [ ] 特定の反応の時にPCに〇を表示できる

### ミッションの準備
- [ ] Osoyoo UNO Board x 1
- [ ] トラッキングセンサー
- [ ] F/Mジャンパー
- [ ] USBケーブルx 1
- [ ] パソコン x 1

## ミッションチャレンジ
### ブレッドボードにトラッキングセンサーを使った回路を作ろう
図のようにトラッキングセンサーとOsoyoo UNO Boardを接続しよう！5VとGNDを間違えないようにしよう。
<image src="image/Arduino-5-tracking.jpg" >

- [ ] 接続できたらチェック！

### トラッキングセンサーの感度を調整しよう
トラッキングセンサーのつまみを回すとトラッキングセンサーの感度が調整できるよ。線に当ててみて上手く反応しなかったら調整してみよう！

- [ ] 感度が調整できたらチェック！

### サンプルコードを実行しよう
ArduinoIDEを開き，ファイル→名前を付けて保存をクリックして，「lesson_13」という名前で保存しよう。
スケッチに以下のコードをコピー＆ペーストして，スケッチを実行してみよう。
``` C++
int IR[] = {A0,A1,A2,A3,A4}

int get_IR(int id){
    int state = digitalRead(IR[id]);
    return state;
}

void setup(){
    Serial.begin(9600);
    pinMode(IR0,INPUT);
    pinMode(IR1,INPUT);
    pinMode(IR2,INPUT);
    pinMode(IR3,INPUT);
    pinMode(IR4,INPUT);
}

void loop(){
    int State0 = get_IR(0);
    int State1 = get_IR(1);
    int State2 = get_IR(2);
    int State3 = get_IR(3);
    int State4 = get_IR(4);
    Serial.print(State0);
    Serial.print(State1);
    Serial.print(State2);
    Serial.print(State3);
    Serial.print(State4);
    Serial.print("\n");
    delay(100);
}
```
- [ ] サンプルコードが実行できたらチェック！

### 特定の反応の時にPCに〇を表示しよう！
``` C++
    Serial.print(State0);
    Serial.print(State1);
    Serial.print(State2);
    Serial.print(State3);
    Serial.print(State4);
```
の部分をコメントアウトして**00110**の時にPCに〇を表示するプログラムを書いてみよう！できたら先生に見せよう！

### まとめ
- [ ] トラッキングセンサーはdigital.Readで読むことができる
- [ ] ドライバーでねじを回すことで感度を調整できる
- [ ] if文でセンサーが特定の反応をしたときに別な処理をすることができる

### できたことをチェックしよう！
- [ ] ブレッドボードにトラッキングセンサーを使った回路を作ることができる
- [ ] トラッキングセンサーの感度を調整できる
- [ ] サンプルコードが実行できる
- [ ] 特定の反応の時にPCに〇を表示できる