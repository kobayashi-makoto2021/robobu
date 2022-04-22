long val1,val2,result;

void setup() {
  Serial.begin(9600); //ボーレートを指定
}

void loop() {

  //受信データがある場合if内を処理
  if (Serial.available() > 0){
    
    val1 = Serial.parseInt();    //文字列データを数値に変換
    Serial.print(val1);          //一つ目の数字をシリアルモニタに表示
    
    char aop = Serial.read();    //四則演算用の文字の読み込み
    Serial.print(aop);           //四則演算の文字をシリアルモニタに表示
 
    val2 = Serial.parseInt();    //文字列データを数値に変換
    Serial.print(val2);          //2つ目の数字をシリアルモニタに表示
    Serial.println("=");         //"="表示後改行
    
    switch (aop){
      case '+' :
          result = val1 + val2;
          Serial.println(result ,DEC);   //加算と改行
          Serial.println("");            //改行
          break;
      
      case '-' :
          result = val1 - val2;
          Serial.println(result ,DEC);   //減算と改行
          Serial.println("");            //改行
          break;

      case '*' :
          result = val1 * val2;
          Serial.println(result ,DEC);   //乗算と改行
          Serial.println("");            //改行
          break;

      case '/' :
          result = val1 / val2;
          Serial.println(result ,DEC);   //除算と改行
          Serial.println("");            //改行
          break;
      }
      
  }
  
}
