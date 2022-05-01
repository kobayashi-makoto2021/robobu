# ロボットカーを組み立てよう！

## **ロボットカーを組み立てる**

### このレッスンで身につける力

- [ ] 部品があるかチェックが出来る
- [ ] モーターを取り付けられる
- [ ] モータードライバーと電圧計を取り付けられる
- [ ] Arduinoボードと電池ボックス、WIFIシールドを取り付けられる
- [ ] ジャンパーワイヤーを正しく取り付けられる
- [ ] シャーシ・タイヤを取り付けられる
- [ ] サンプルコードを動かすことが出来る

---

### ミッションの準備

#### ハードウェアを用意しよう

- [ ] Osoyoo ROBOT CAR KIT x1
- [ ] 六角ドライバー x1
- [ ] ラジオペンチ x1


---
### 部品があるかチェックしよう

このレッスンで使う部品一覧

| 写真                                         | 名前                              | 個数 | 
| -------------------------------------------- | :-------------------------------- | :--: | 
| <img src="image/ArduinoUNO.jpg" width="10%"> | Arduino UNO                       | 1    | 
| <img src="image/UART WIFI module.jpg" width="10%"> | UART WiFiシールド                 | 1    | 
| <img src="image/Motordriver.jpg" width="10%"> | モータードライバー                | 1    | 
| <img src="image/Voltage_meter.jpg" width="10%"> | 電圧計                            | 1    | 
| <img src="image/Gear_motor.jpg" width="10%"> | ギヤモーター                      | 4    | 
| <img src="image/motor_holder.jpg" width="10%"> | モーター用ホルダー（ネジ付き）    | 4    | 
| <img src="image/Wheel.jpg" width="10%"> | ホイール                          | 4    | 
| <img src="image/chassis_upside.jpg" width="10%"> | 上部カーシャーシ                  | 1    | 
| <img src="image/chassis_under.jpg" width="10%"> | 下部カーシャーシ                  | 1    | 
| <img src="image/3pin_Female_Female.jpg" width="10%"> | 3ピン メスーメス ジャンパーワイヤ | 1    | 
| <img src="image/6pin_male-male.jpg" width="10%"> | 6ピン オスーメス ジャンパーワイヤ | 1    | 
| <img src="image/2pin_pnp.jpg" width="10%"> | 2ピン PnP ケーブル                | 1    | 
| <img src="image/plusdriver.jpg" width="10%"> | プラスドライバー                  | 1    | 
| <img src="image/Hex_Screwdriver.jpg" width="10%"> | 六角ドライバー                    | 1    | 
| <img src="image/BatteryBox_9V.jpg" width="10%"> | バッテリーボックス（９V電池用）   | 1    | 
| <img src="image/M3x10 hex.jpg" width="10%"> | M3 x 10 六角ネジ	                 | 10   | 
| <img src="image/M3x10 plus.jpg" width="10%"> | M3 x 10 プラスネジ	               | 4    | 
| <img src="image/M3 nut.jpg" width="10%"> | M3 ナット                         | 4    | 
| <img src="image/spacer brass.jpg" width="10%"> | スペーサー（黄銅）                | 5    | 
| <img src="image/screw for wheel.jpg" width="10%"> | ホイール用ネジ                    | 4    | 
| <img src="image/M3 plastic screw.jpg" width="10%"> | M3 プラスチックネジ               | 9    | 
| <img src="image/M3 plastic spacer.jpg" width="10%"> | M3 プラスチックスペーサー         | 10   | 
| <img src="image/M3 plastic nut.jpg" width="10%"> | M3 プラスチックナット             | 10   | 


---



#### 【ステップ2】0.1秒ごとにカウントアップするタイマーを作ろう



**＜実行の準備＞**

コピー＆ペーストができたら左上の矢印を押して（またはCtrl＋U），プログラムを書き込みましょう．

さきほどと同じように実行しましょう．


**＜実行結果＞**

<img src="image/lesson02_2_ver.2_serialmonitor_result.png" width="70%">



---

### まとめ

- プログラムでの四則演算は「+」「-」「*」「/」
- シリアルモニタでデータの入力・表示ができる
- ループを遅らせるための関数はdelay();
- 変数は，数字や文字を入れておく箱
- int型は「整数型」，float型は「浮動小数点型」


#### 出来たことをチェックしよう

- [ ] 足す、引く、掛ける、割るの計算が出来る
- [ ] 計算の順序に合わせて( )を使える
- [ ] delay()と変数、整数型（int）を使ってタイマーを作れる
- [ ] 浮動小数点型(float)を使ってタイマーを改良できる