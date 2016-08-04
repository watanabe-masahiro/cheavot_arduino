const int button1 = 14;
const int button2 = 16;
const int button3 = 18;
//表示する数字
int num1 = 0;
int num2 = 0;
int num3 = 0;
//本当の数字
int renum1 = 0;
int renum2 = 0;
int renum3 = 0;
//数字の入れ替えで使用
int numch = 0;
int chch = 0;
//数字と投票先の関係を記憶(文字にしたほうが混乱ないかも)
int a = 1;
int b = 2;
int c = 3;
//LEDのダイナミック点灯フラグ
boolean _flg = false;
//チャタリング防止
int cnt = 0;

void setup() {
  Serial.begin(9600); 
//LED用の出力ピン定義
  for (int i = 4; i <= 12; i++) {
    pinMode(i, OUTPUT);
  }
  for (int i = 30; i <= 38; i++) {
    pinMode(i, OUTPUT);
  }
   for (int i = 58; i <= 66; i++) {
    pinMode(i, OUTPUT);
  }
  pinMode(button1, INPUT);
  pinMode(button2, INPUT);
  pinMode(button3, INPUT);
  pinMode(15, OUTPUT);
  pinMode(17, OUTPUT);
  pinMode(19, OUTPUT);
  //スイッチへの電源供給
}
//LEDレイアウトを定義
boolean Num_Array[10][7] = {
  {0, 0, 1, 0, 0, 0, 0}, //0
  {1, 1, 1, 1, 1, 0, 0}, //1
  {0, 0, 0, 1, 0, 0, 1}, //2
  {1, 0, 0, 1, 0, 0, 0}, //3
  {1, 1, 0, 0, 1, 0, 0}, //4
  {1, 0, 0, 0, 0, 1, 0}, //5
  {0, 0, 0, 0, 0, 1, 0}, //6
  {1, 1, 1, 0, 0, 0, 0}, //7
  {0, 0, 0, 0, 0, 0, 0}, //8
  {1, 0, 0, 0, 0, 0, 0} //9
};

//LED表示関数を定義
void NumPrint1(int Number) {
  for (int w = 0; w <= 6; w++) {
    digitalWrite(w + 58, -Num_Array[Number][w]);
  }
}
void NumPrint2(int Number) {
  for (int w = 0; w <= 6; w++) {
    digitalWrite(w + 30, -Num_Array[Number][w]);
  }
}
void NumPrint3(int Number) {
  for (int w = 0; w <= 6; w++) {
    digitalWrite(w + 4, -Num_Array[Number][w]);
  }
}
//2桁をそれぞれの桁で分解する関数
int NumParse(int Number, int s) {
  if (s == 1) {
    return Number / 10; //10で割ったあまり = 一桁目の値
  }
  else if (s == 2) {
    return Number % 10; //10で割った値を整数にする = 二桁目の値
  }
  return 0;
}
void loop() {
  if (cnt == 41) {
    cnt = 0;

  }
  digitalWrite(15, HIGH);
  digitalWrite(17, HIGH);
  digitalWrite(19, HIGH);
  //スイッチへの電源供給

  //flg変数をtrue / falseを切り替えることで11番13番ピンの出力を交互に切り替える
  if (_flg) {
    digitalWrite(11, LOW);
    digitalWrite(12, HIGH);
    digitalWrite(37, LOW);
    digitalWrite(38, HIGH);
    digitalWrite(65, LOW);
    digitalWrite(66, HIGH);
    _flg = false;
    NumPrint1(NumParse(num1, 1)); //1桁目の表示
    NumPrint2(NumParse(num2, 1)); //1桁目の表示
    NumPrint3(NumParse(num3, 1)); //1桁目の表示
  }
  else {
    digitalWrite(12, LOW);
    digitalWrite(11, HIGH);
    digitalWrite(38, LOW);
    digitalWrite(37, HIGH);
    digitalWrite(66, LOW);
    digitalWrite(65, HIGH);
    _flg = true;
    NumPrint1(NumParse(num1, 2)); //1桁目の表示
    NumPrint2(NumParse(num2, 2)); //1桁目の表示
    NumPrint3(NumParse(num3, 2)); //1桁目の表示
  }
  //ここからボタンの読み取りについて
  //
  //
  cnt++;
  if (cnt == 40) {//ボタンのチャタリング防止
    
    //ここからボタン1
    if (digitalRead (button1) == HIGH) {
      num1++;
      if (a == 1) {
        renum1++;
      }
      if (a == 2) {
        renum2++;
        if (b == 1) {
          if (num1 > num2) {
            numch = num1;
            num1 = num2;
            num2 = numch;
            chch = a;
            a = b;
            b = chch;
            

          }//numは数字abcはnumと投票先の関係を記憶
          if (c == 1) {
            if (num1 > num3) {
              numch = num1;
              num1 = num3;
              num3 = numch;
              chch = a;
              a = c;
              c = chch;
            }
          }
        }
      }
      if (a == 3) {
        renum3++;
        if (b == 1) {
          if (num1 > num2) {
            numch = num1;
            num1 = num2;
            num2 = numch;
            chch = a;
            a = b;
            b = chch;
          }
        }
        if (c == 1) {
          if (num1 > num3) {
            numch = num1;
            num1 = num3;
            num3 = numch;
            chch = a;
            a = c;
            c = chch;
          }
        }

      }

      Serial.print("こだわりは");
      Serial.println(renum1);
      Serial.print("凡例１は");
      Serial.println(renum2);
      Serial.print("凡例2は");
      Serial.println(renum3);
    }

    //ここからボタン2
    if (digitalRead(button2) == HIGH) {
      num2++;
      if (b == 1) {
        renum1++;
      }
      if (b == 2) {
        renum2++;
        if (a == 1) {
          if (num2 > num1) {
            numch = num2;
            num2 = num1;
            num1 = numch;
            chch = b;
            b = a;
            a = chch;
          }
          if (c == 1) {
            if (num2 > num3) {
              numch = num2;
              num2 = num3;
              num3 = numch;
              chch = b;
              b = c;
              c = chch;
            }
          }
        }
      }
      if (b == 3) {
        renum3++;
        if (a == 1) {
          if (num2 > num1) {
            numch = num2;
            num2 = num1;
            num1 = numch;
            chch = b;
            b = a;
            a = chch;
          }
        }
        if (c == 1) {
          if (num2 > num3) {
            numch = num2;
            num2 = num3;
            num3 = numch;
            chch = b;
            b = c;
            c = chch;
          }
        }

      }
      Serial.print("こだわりは");
      Serial.println(renum1);

      Serial.print("凡例１は");
      Serial.println(renum2);

      Serial.print("凡例2は");
      Serial.println(renum3);
    }


    //ここからボタン3
    if (digitalRead(button3) == HIGH) {
      num3++;
      if (c == 1) {
        renum1++;
      }
      if (c == 2) {
        renum2++;
        if (a == 1) {
          if (num3 > num1) {
            numch = num3;
            num3 = num1;
            num1 = numch;
            chch = c;
            c = a;
            a = chch;
          }
          if (c == 1) {
            if (num3 > num2) {
              numch = num3;
              num3 = num2;
              num2 = numch;
              chch = c;
              c = b;
              b = chch;
            }
          }
        }
      }
      if (c == 3) {
        renum3++;
        if (a == 1) {
          if (num3 > num1) {
            numch = num3;
            num3 = num1;
            num1 = numch;
            chch = c;
            c = a;
            a = chch;
          }
        }
        if (b == 1) {
          if (num3 > num2) {
            numch = num3;
            num3 = num2;
            num2 = numch;
            chch = c;
            c = b;
            b = chch;
          }
        }

      }

      Serial.print("こだわりは");
      Serial.println(renum1);

      Serial.print("凡例１は");
      Serial.println(renum2);

      Serial.print("凡例2は");
      Serial.println(renum3);

    }
    cnt = 0;
  }
  delay(5);
}
