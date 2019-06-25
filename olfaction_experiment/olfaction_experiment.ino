const int buttonPin = A4; // 连接按键的引脚
int buttonState = 1;
int a = 0;
int b = 0;
int odor;
int RNDsec;

int num1[24] = {6, 6, 3, 8, 3, 7, 1, 6, 8, 5, 5, 3, 7, 1, 7, 2, 4, 2, 8, 5, 1, 4, 2, 4};
int num2[24] = {8, 8, 2, 3, 6, 5, 1, 6, 2, 4, 1, 7, 6, 8, 5, 1, 5, 7, 3, 2, 3, 4, 4, 7};
int num3[24] = {7, 4, 5, 6, 4, 8, 6, 6, 3, 2, 8, 7, 3, 3, 5, 4, 8, 1, 5, 2, 7, 1, 2, 1};
int num4[24] = {4, 3, 8, 5, 2, 6, 6, 4, 1, 1, 8, 5, 4, 2, 3, 7, 8, 7, 6, 1, 2, 5, 3, 7};
int num5[24] = {3, 7, 8, 3, 5, 1, 1, 3, 7, 4, 8, 7, 2, 8, 5, 1, 2, 4, 5, 6, 6, 4, 2, 6};
int num6[24] = {3, 7, 1, 8, 4, 7, 5, 1, 6, 7, 8, 3, 8, 3, 2, 6, 4, 2, 5, 5, 6, 1, 4, 2};
int num7[24] = {8, 2, 5, 8, 4, 6, 5, 3, 6, 3, 5, 7, 2, 1, 4, 7, 4, 3, 1, 6, 1, 7, 2, 8};
int num8[24] = {6, 7, 2, 6, 8, 2, 8, 3, 6, 4, 3, 4, 5, 1, 4, 3, 1, 1, 2, 7, 8, 5, 5, 7};
int num9[24] = {8, 3, 6, 4, 4, 5, 2, 2, 3, 5, 1, 5, 6, 4, 8, 2, 1, 1, 8, 3, 7, 7, 7, 6};
int num10[24] = {4, 4, 2, 8, 3, 1, 3, 5, 8, 5, 5, 6, 6, 7, 7, 4, 3, 8, 7, 1, 2, 1, 6, 2};
int num11[24] = {4, 5, 1, 6, 1, 2, 3, 2, 2, 7, 7, 5, 4, 8, 8, 1, 6, 8, 3, 6, 7, 5, 3, 4};
int num12[24] = {1, 1, 7, 5, 8, 2, 6, 3, 4, 1, 3, 6, 7, 8, 4, 7, 3, 6, 2, 2, 8, 5, 4, 5};
int num13[24] = {6, 7, 5, 8, 2, 6, 8, 3, 4, 4, 7, 3, 8, 1, 2, 7, 6, 2, 5, 1, 4, 3, 5, 1};
int num14[24] = {5, 5, 7, 8, 8, 7, 1, 3, 2, 6, 8, 4, 5, 4, 7, 2, 2, 1, 3, 4, 6, 3, 1, 6};
int num15[24] = {7, 6, 8, 5, 2, 1, 7, 4, 1, 5, 2, 3, 2, 3, 1, 4, 3, 8, 8, 6, 4, 5, 6, 7};
int num16[24] = {1, 8, 1, 5, 5, 2, 5, 8, 6, 6, 4, 3, 6, 7, 7, 2, 4, 1, 7, 3, 4, 2, 3, 8};
int num17[24] = {4, 8, 2, 6, 7, 8, 2, 6, 4, 1, 5, 4, 5, 3, 3, 7, 5, 6, 3, 1, 1, 8, 7, 2};
int num18[24] = {1, 7, 3, 1, 8, 2, 2, 2, 5, 6, 3, 5, 7, 4, 3, 1, 4, 4, 7, 5, 6, 6, 8, 8};
int num19[24] = {4, 8, 8, 2, 3, 1, 5, 5, 2, 6, 7, 5, 1, 1, 3, 6, 7, 4, 7, 8, 6, 4, 3, 2};
int num20[24] = {4, 3, 8, 5, 1, 3, 5, 7, 2, 1, 1, 7, 3, 7, 6, 4, 2, 8, 5, 6, 4, 8, 2, 6};
int num21[15] = {3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3};
int num22[15] = {7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7};
int num23[15] = {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1};
int num24[15] = {5,5,5,5,5,5,5,5,5,5,5,5,5,5,5};
int num25[24] = {2,2,3,4,3,3,1,2,4,1,1,3,3,1,3,2,4,2,4,1,1,4,2,4};

 void Valve_ON(int valve) {
    digitalWrite(valve + 21 + 8, HIGH);
    if (valve == 3) {
      digitalWrite(6 + 21 + 8, HIGH);
      digitalWrite(6 + 21, HIGH);
    }
    if (valve > 1) {
      delay(1000);
    }
    digitalWrite(valve + 21, HIGH);
    if (valve == 4) {
      digitalWrite(38, HIGH);
    }
  }

  void Valve_OFF(int valve) {
    digitalWrite(valve + 21 + 8, LOW);
    digitalWrite(6 + 21 + 8, LOW);
    if (valve > 1) {
      delay(50);
    }
    digitalWrite(valve + 21, LOW);
    digitalWrite(6 + 21, LOW);
    //digitalWrite(38,LOW);
  }

void setup() {
  // put your setup code here, to run once:


  pinMode(A4, INPUT);
  pinMode(22, OUTPUT); // water
  pinMode(23, OUTPUT); // odor1
  pinMode(24, OUTPUT); // odor2
  pinMode(25, OUTPUT); //
  pinMode(26, OUTPUT); // odor3
  pinMode(27, OUTPUT); // odor4
  pinMode(28, OUTPUT); // odor5
  pinMode(29, OUTPUT); // odor6
  pinMode(30, OUTPUT); //
  pinMode(31, OUTPUT); // odor1
  pinMode(32, OUTPUT); // odor2
  pinMode(33, OUTPUT); //
  pinMode(34, OUTPUT); // odor3
  pinMode(35, OUTPUT); // odor4
  pinMode(36, OUTPUT); // odor5
  pinMode(37, OUTPUT); // odor6


  pinMode(38, OUTPUT);
  pinMode(39, OUTPUT);
  pinMode(40, OUTPUT);
  pinMode(41, OUTPUT);
  pinMode(42, OUTPUT);
  pinMode(43, OUTPUT);
  pinMode(44, OUTPUT);
  pinMode(45, OUTPUT);
  pinMode(46, OUTPUT);
  pinMode(47, OUTPUT);
  pinMode(48, OUTPUT);
  pinMode(49, OUTPUT);

  pinMode(52, OUTPUT);
  pinMode(53, OUTPUT);

  digitalWrite(50, HIGH);
  digitalWrite(52, LOW);
  digitalWrite(53, LOW);
  digitalWrite(39, LOW);



}

void loop() {
  // put your main code here, to run repeatedly:
  // put your main code here, to run repeatedly:
  buttonState = digitalRead(buttonPin);// 读取按键状态并存储在变量中
  // 检查按键是否被下 如果按键下，buttonState应该为低电平
  if (buttonState == LOW) {
    buttonState = 1;
    a++;
    delay(500);
  }
  //else {
  //digitalWrite(ledPin, LOW);// 熄灭 LED
  //}

  if (a == 3) {
    if (b == 0) {
      //digitalWrite(ledPin, LOW);
      delay(14000); //cause valve_On will take 1 second
      b++;
    }
    for (int c = 0; c < 24; c++) {
      switch (num25[c]) {
        case 1:
          odor = 2;
          RNDsec = 1000;
          break;

        case 2:
          odor = 2;
          RNDsec = 2000;
          break;

        case 3:
          odor = 2;
          RNDsec = 4000;
          break;

        case 4:
          odor = 2;
          RNDsec = 8000;
          break;

        case 5:
          odor = 5;
          RNDsec = 1000;
          break;

        case 6:
          odor = 5;
          RNDsec = 2000;
          break;

        case 7:
          odor = 5;
          RNDsec = 4000;
          break;

        case 8:
          odor = 5;
          RNDsec = 8000;
          break;
      }

      // valve2 is odor A , valve5 is odor C.


      Valve_ON(odor);
      delay(RNDsec);
      Valve_OFF(odor);
      delay(19000);
    }
  }
}
