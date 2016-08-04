#include <MsTimer2.h>

int button_pins[3] = {14, 16, 18};
int display_votes[3] = {0, 0, 0};
int real_display_map[3] = {0, 1, 2}; // 「実際の投票数」が「表示している投票数」のどれに当たるかを示すindexのマップ。real_display_map[0]の値がこだわりのindexでdisplay_votes[real_display_map[0]] がその投票数

boolean led_dynamic_flag = false;
int chattering_counter = 0;
boolean running_timer;

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
  for (int i = 0; i <= 3; i++) {
    pinMode(button_pins[i], INPUT);
  }
  pinMode(15, OUTPUT);
  pinMode(17, OUTPUT);
  pinMode(19, OUTPUT);
  //スイッチへの電源供給
   MsTimer2::set(30000, start_timer); // 3s period
}

void start_timer() {
  int max_index = 0;
  int max_votes = 0;
  for(int i=0; i<3; i++) {
    if (display_votes[i] > max_votes) {
       max_index = i;
       max_votes = display_votes[i];
    }
  }
  int fanantial_index = real_display_map[0];
  if (fanantial_index == max_index) {
     return;
  }
  int tmp = display_votes[max_index];
  display_votes[max_index] = display_votes[fanantial_index];
  display_votes[fanantial_index] = tmp;
  tmp = real_display_map[max_index];
  real_display_map[max_index] = real_display_map[fanantial_index]; 
  real_display_map[fanantial_index] = tmp;
  stop_timer();
  debug_print_to_serial();
}
//void start_timer() {
//  if (running_timer) {
//    stop_timer();
//  }
//  running_timer = true;
//  MsTimer2::start();
//}

void stop_timer() {
  MsTimer2::stop();
  running_timer = false;
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

void NumPrint(int index, int Number) {
    int offset[] = {58, 30, 4};
    for (int w = 0; w < 7; w++) {
      digitalWrite(w + offset[index], -Num_Array[Number][w]);
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

void debug_print_to_serial() {
    String message[3] = { "kodawari:", "hanrei1:", "hanrei2:" };
    for(int i=0; i<3; i++) {
      Serial.println(message[i]);
      Serial.println(display_votes[real_display_map[i]]);
    }
}



void loop() {
  digitalWrite(15, HIGH); // → setup()に持っていっても良い?
  digitalWrite(17, HIGH);
  digitalWrite(19, HIGH);
  //スイッチへの電源供給

  //led_dynamic_flag変数をtrue / falseを切り替えることで11番13番ピンの出力を交互に切り替える
  if (led_dynamic_flag) {
    digitalWrite(11, LOW);
    digitalWrite(12, HIGH);
    digitalWrite(37, LOW);
    digitalWrite(38, HIGH);
    digitalWrite(65, LOW);
    digitalWrite(66, HIGH);
    for(int i=0; i<3; i++) {
      NumPrint(i, NumParse(display_votes[i], 1)); //1桁目の表示
    }
  } else {
    digitalWrite(11, HIGH);
    digitalWrite(12, LOW);
    digitalWrite(37, HIGH);
    digitalWrite(38, LOW);
    digitalWrite(65, HIGH);
    digitalWrite(66, LOW);
    for(int i=0; i<3; i++) {
      NumPrint(i, NumParse(display_votes[i], 2)); //2桁目の表示
    }
  }
  led_dynamic_flag = !led_dynamic_flag;
  chattering_counter++;
  if (chattering_counter == 40) {//ボタンのチャタリング防止
    for (int i=0; i<3; i++) {
      //ボタン i
      if (digitalRead(button_pins[i]) == HIGH) {
        display_votes[i]++;
        start_timer();
        //debug_print_to_serial();
      }
    }
    chattering_counter = 0;
  }
  delay(5);
}
