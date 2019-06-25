     
// 细分1 ,       一步1.8度, 一圈 360 / 1.8 = 200步
// 细分2/A 2/B   一步1.8 / 2 = 0.9度, 一圈 360 / 0.9 = 400步
// 1Hz delay(5);  ms
// 2Hz delayMicroseconds(2500); us
// 4Hz delayMicroseconds(1250); us


const int buttonPin = 2; // 连接按键的引脚 
int PUL=7; //define Pulse pin
int DIR=6; //define Direction pin
int ENA=5; //define Enable Pin

int a = 0;
int b = 0;
int c = 0;
int buttonState = 1; // 存储按键状态的变量  

//int num[5] = {10,20,30,40,50};
float steptime = 100000/60;

int num1[]={20,40,20,10,5,40,20,40,10,5,10,10,40,20,5,5,10,5,40,20};
int num2[]={10,10,40,40,10,5,40,40,20,20,5,10,10,5,20,20,40,5,20,5};
int num3[]={40,5,20,10,20,40,10,5,40,10,20,5,10,10,5,20,40,20,40,5};
int num4[]={40,40,5,10,5,10,10,20,40,20,10,20,5,20,40,5,20,10,5,40};
int num5[]={40,40,5,10,40,20,5,10,10,40,10,40,5,20,20,5,20,5,20,10};
int num6[]={40,10,10,40,40,10,20,5,40,20,10,20,20,20,5,40,10,5,5,5};
int num7[]={40,20,5,5,10,20,20,10,10,5,40,40,10,20,40,5,10,20,40,5};
int num8[]={40,5,20,5,5,20,10,40,10,5,10,20,40,40,10,10,5,40,20,20};
int num9[]={10,5,10,20,20,40,40,5,20,40,10,10,5,20,5,40,10,40,5,20};
int num10[]={5,20,5,10,20,10,40,40,40,5,20,20,10,10,5,10,40,20,40,5};
int num11[]={40,20,20,5,20,10,10,10,5,5,10,40,10,20,5,20,40,40,5,40};
int num12[]={40,40,40,40,20,10,20,10,10,10,40,20,5,20,10,20,5,5,5,5};
int num13[]={20,20,20,5,10,40,5,20,40,20,40,10,10,5,10,5,5,40,40,10};
int num14[]={20,20,10,20,5,40,10,20,40,20,5,10,5,40,5,40,10,10,40,5};
int num15[]={5,40,5,20,40,20,10,5,20,10,40,10,5,5,40,20,10,40,10,20};
int num16[]={40,10,20,5,5,40,10,5,10,40,20,10,20,40,5,20,20,10,40,5};
int num17[]={10,20,40,5,40,10,5,20,5,40,40,20,40,10,5,10,20,5,10,20};
int num18[]={40,5,5,20,10,5,10,20,40,5,40,10,40,40,20,10,20,20,10,5};
int num19[]={40,10,5,20,5,20,5,40,20,20,5,40,10,10,5,40,20,10,40,10};
int num20[]={20,20,5,20,40,40,40,10,20,5,10,5,10,20,10,5,10,40,5,40};

int num21[]={100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100};

void setup() {
  pinMode (PUL, OUTPUT);  //PULSE为脉冲管脚，驱动器每收到一个脉冲，电机就走一步
  pinMode (DIR, OUTPUT);  //Direction为方向引脚，低电平正转；高电平反转
  pinMode (ENA, OUTPUT); //Enable是脱机引脚，当管脚置高时（或者不接时），电机正常使用；
                         //当管脚置低时，电机可任意转动
  pinMode(buttonPin, INPUT);// 初始化按键引脚为输入状态
}

void loop(){

buttonState = digitalRead(buttonPin);// 读取按键状态并存储在变量中  
// 检查按键是否被下 如果按键下，buttonState应该为低电平 
  if (buttonState == LOW) {
  buttonState=1;
  a++;
  delay(500);
}
//else {
//digitalWrite(ledPin, LOW);// 熄灭 LED
//}

if (a==3) {
  if(b==0){
  //digitalWrite(ledPin, LOW);
  delay(10000);
  b++;
  }
  else{
    for(int k = 0; k<16; k++){
    while(c<num21[k]){                //前进后退次数: 20次
    
    
  for (int i=0; i<30; i++)    //Forward 400 steps 一圈, 细分2/A 2/B
  {
    digitalWrite(DIR,LOW);     //步进电机转
    digitalWrite(ENA,HIGH);    
    digitalWrite(PUL,HIGH);
    delayMicroseconds(steptime);
    //delay(5);
    digitalWrite(PUL,LOW);
    delayMicroseconds(steptime);
    //delay(5);
  }
  for (int i=0; i<30; i++)   //Backward 400 steps 一圈, 细分2/A 2/B
  {
    digitalWrite(DIR,HIGH);   //步进电机正转
    digitalWrite(ENA,HIGH);
    digitalWrite(PUL,HIGH);
    delayMicroseconds(steptime);
    //delay(5);
    digitalWrite(PUL,LOW);
    delayMicroseconds(steptime);
    //delay(5);
    }
   
    c++;
   
    }
     c=0;
     delay(20000);
    }
    
    

}
}
}
