#include<Servo.h>
Servo ZUO1;
Servo ZUO2;
Servo ZUO3;
Servo ZUO4;
Servo YOU1;
Servo YOU2;
Servo YOU3;
Servo YOU4;
Servo YUANTONGKAIBI;
Servo YUANTONGSHANGXIA;
const int zuo1_InitPos = 150;
const int zuo2_InitPos = 145;
const int zuo3_InitPos = 90;
const int zuo4_InitPos = 20;
const int you1_InitPos = 50;
const int you2_InitPos = 20;
const int you3_InitPos = 156;
const int you4_InitPos = 150;
const int yuantongkaibi_InitPos = 58;
const int yuantongshangxia_InitPos = 100;
const int zuo1_properPos = 110;
const int zuo2_properPos = 70;
const int zuo3_properPos = 160;
const int zuo4_properPos = 120;//
const int you1_properPos = 105;
const int you2_properPos = 80;
const int you3_properPos = 105;
const int you4_properPos = 50;
const int yuantongkaibi_properPos1 = 140;
const int yuantongkaibi_properPos2 = 115;
const int yuantongshangxia_properPos1 = 20;
const int yuantongshangxia_properPos2 = 60;//64
const int taotongzhong = 46;//48
const int bao2houtui_pulse = 185;
#define zuoyi   42
#define zuoer   31
#define youyi   44
#define youer   7
#define zuosan  2
#define zuosi   12
#define yousan  4
#define yousi   6
#define yuantongkaibi 43
#define yuantongshangxia 30

#define MotorApin1 10
#define MotorApin2 8
#define MotorApwm  9
#define MotorAcountA 34 
#define MotorAcountB 35

#define MotorBpin1 24
#define MotorBpin2 25
#define MotorBpwm  11
#define MotorBcountA 36
#define MotorBcountB 37

#define onecircle   775    //775������תһȦ
int MotorAPos = 0;
int MotorBPos = 0;
int old_posA = 0;
int old_posB = 0;
float omgaA = 0;
float omgaB = 0;
int   flag = 0;
unsigned long old_time = 0;
unsigned long now_time = 0;

#define Qvalue4 A4
#define Qvalue5 A5
#define Hvalue4 A6
#define Hvalue5 A9

///////////////////////////////////////////��ɫ������
#define OUT     48
#define LED     45
#define S2      47
#define S3      49

#define black 0
#define white 1
#define red   2
#define green 3
#define blue  4

int colorA = 0;
int colorB = 0;
int colorC = 0;
int colorD = 0;
int colorE = 0;

///////////////////////////////////////////���⴫����
#define Llaser1 50
#define Llaser2 51
#define Rlaser1 53
#define Rlaser2 40
////////////////////////////////////////ѭ���궨��
#define QvalueMax4  2800 
#define QvalueMin4  400
#define QvalueMax5  2000 
#define QvalueMin5  300 
#define HvalueMax4  1700
#define HvalueMin4  3000
#define HvalueMax5  3100
#define HvalueMin5  370
#define stopyanshi  200
const int average1 = (QvalueMax4 + QvalueMin4) / 2;
const int average2 = (QvalueMax5 + QvalueMin5) / 2;
const int average3 = (HvalueMax4 + HvalueMin4) / 2;
const int average4 = (HvalueMax5 + HvalueMin5) / 2;
const int speed1 = 88;//����  82
const int speed2 = 91;//����  85
const int speed3 = 53;//����  50
const int speed4 = 58;//����  55
const int speed5 = 70;//      64
const int speed6 = 76;//      70
const int change = 35;
const float Kp1 = 13, Ki1 = 0.25, Kd1 = 1.5;                    //pidǰ���������� 
const float Kp2 = 11, Ki2 = 0.2, Kd2 = 4.5;                    //pid���˲������� 
float error = 0, P = 0, I = 0, D = 0, PID_value = 0;  //pidֱ������ 
float previous_error = 0, previous_I = 0;
///////////////////////////////////////////ת��΢��
const int leftbeforeweitiao = 150;
const int rightbeforeweitiao = 150;
const int leftafterweitiao45 = 120;
const int rightafterweitiao45 = 100;
const int leftafterweitiao90 = 40;
const int rightafterweitiao90 = 90;
const int leftafterweitiao135 = 110;
const int rightafterweitiao135 = 110;
/////////////////////////////////////////�Ҷȴ�����
int val4 = 0;
int val5 = 0;
int val6 = 0;
int val7 = 0;

int ljg1 = 0;
int ljg2 = 0;
int rjg1 = 0;
int rjg2 = 0;
void getABCD()
{ //��ȡ4��5��6��7�ŵ�ֵ

  val4 = 0;
  val5 = 0;
  val6 = 0;
  val7 = 0;
  char i;
  for (i = 0; i < 4; i++) {
    val4 += analogRead(Qvalue4);
    val5 += analogRead(Qvalue5);
    val6 += analogRead(Hvalue4);
    val7 += analogRead(Hvalue5);
  }
  val4 = val4 / 4;
  val5 = val5 / 4;
  val6 = val6 / 4;
  val7 = val7 / 4;
  if (flag == 1) {//ǰ��
    if (val4 < 800 && val5 < 600)//�ں���
      error = 0;
    else if (val4 < 800 && val5 > 600)//ƫ��
      error = 3;
    else if (val4 > 800&& val5 < 600)//ƫ��
      error = 3;
    else
      error = 0;
  }
  else {//����
    if (val6 < 600 && val7 <1000)//�ں���
      error = 0;
    else if (val6 < 600 && val7 > 1000)//ƫ��
      error = 3;
    else if (val6 > 600 && val7 < 1000)//ƫ��
      error = 3;
    else
      error = 0;
  }
}

///////////////////////////////////////////////////��ɫ������/////////////////////////////////////////////////////

int   g_count = 0;    // count the frequecy������������Ϊ��ɫ�������ı�������
int   g_array[4];     // store the RGB value
// save the RGB Scale factor
float g_SF[3] = { 0.32, 0.37, 0.32 };//0.32 0.35 0.29     0.82  0.82  0.82��������һ��
void TSC_Init()//��ɫ�������ĺ���
{
  pinMode(LED, OUTPUT);
  pinMode(S2, OUTPUT);
  pinMode(S3, OUTPUT);
  pinMode(OUT, INPUT);
}
void TSC_Count()//��ɫ�������ĺ���
{
  g_count++;
}

//////////////////////////////////////////////ֱ�߲�ѭ��
void doMotorA()
{
  if (digitalRead(MotorAcountA) == HIGH)
  {
    if (digitalRead(MotorAcountB) == HIGH)
    {
      MotorAPos = MotorAPos + 1;
    }
    else
    {
      MotorAPos = MotorAPos - 1;
    }
  }
  else
  {
    if (digitalRead(MotorAcountB) == LOW)
    {
      MotorAPos = MotorAPos + 1;
    }
    else
    {
      MotorAPos = MotorAPos - 1;
    }
  }
}

void doMotorB()
{
  if (digitalRead(MotorBcountA) == HIGH)
  {
    if (digitalRead(MotorBcountB) == LOW)
    {
      MotorBPos = MotorBPos + 1;
    }
    else
    {
      MotorBPos = MotorBPos - 1;
    }
  }
  else
  {
    if (digitalRead(MotorBcountB) == HIGH)
    {
      MotorBPos = MotorBPos + 1;
    }
    else
    {
      MotorBPos = MotorBPos - 1;
    }
  }
}

void move_compute(int* speeda, int* speedb)
{
  now_time = old_time + 50;
  while (millis() < now_time);
  attachInterrupt(digitalPinToInterrupt(MotorAcountA),doMotorA,CHANGE);
  attachInterrupt(digitalPinToInterrupt(MotorBcountA),doMotorB,CHANGE);
  //detachInterrupt(digitalPinToInterrupt(MotorAcountA));
  //detachInterrupt(digitalPinToInterrupt(MotorBcountA));
  omgaA = abs((float)(MotorAPos - old_posA) * 20 / onecircle);//��������ת��
  omgaB = abs((float)(MotorBPos - old_posB) * 20 / onecircle);//��������ת��
//  Serial.print("omgaA=");
//  Serial.print(omgaA);
//  Serial.print("r\\s omgaB=");
//  Serial.print(omgaB);
//  Serial.print("r\\s");
//  Serial.println("");
  float t1 = (float)(*(speeda));
  float t2 = (float)(*(speedb));
  if(omgaA>omgaB && (omgaA - omgaB)>0.1) 
  {
    *(speedb) += 3; //= (float)(t2 - 100*(omgaA - omgaB));
    *(speeda) -= 2; //= (float)(t1 + 100*(omgaA - omgaB));
  }
  else if(omgaA< omgaB && (omgaB - omgaA)>0.1)
  {
    *(speedb) -= 2;// (float)(t2 + 80*(omgaB - omgaA));
    *(speeda) += 3;// (float)(t1 - 80*(omgaB - omgaA));
  }
  if (*(speedb) > t2 * 1.2 || *(speedb) < t2 * 0.1)  *(speedb) = t2;
  if (*(speeda) > t1 * 1.2 || *(speeda) < t1 * 0.1) *(speeda) = t1;//��ֹ�����������ٶ�̫��
  //ʵ�ʹ����п��ٲ�������һ�����ӣ���һ�������ٶ����������־��޷���Ϊԭ��
  old_time = millis();
  old_posA = MotorAPos;
  old_posB = MotorBPos;
//  attachInterrupt(digitalPinToInterrupt(MotorAcountA),doMotorA,CHANGE);
//  attachInterrupt(digitalPinToInterrupt(MotorBcountA),doMotorB,CHANGE);
}

void goStraight(int speeda, int speedb) {//BΪ���֣�AΪ����
  digitalWrite(MotorApin1, LOW);
  digitalWrite(MotorApin2, HIGH);
  analogWrite(MotorApwm, speeda);

  digitalWrite(MotorBpin1, HIGH);
  digitalWrite(MotorBpin2, LOW);
  analogWrite(MotorBpwm, speedb);
}

void gostraight(int speeda, int speedb)
{
  move_compute(&speeda, &speedb);
  goStraight(speeda, speedb);
}

void retreat(int speeda, int speedb) {
  digitalWrite(MotorApin1, HIGH);
  digitalWrite(MotorApin2, LOW);
  analogWrite(MotorApwm, speeda);

  digitalWrite(MotorBpin1, LOW);
  digitalWrite(MotorBpin2, HIGH);
  analogWrite(MotorBpwm, speedb);
}

void retreat1(int speeda, int speedb)
{
  move_compute(&speeda, &speedb);
  retreat(speeda, speedb);
}

void zhongduanhoutuiweitiao1(int pulse_weitiao, int speeda, int speedb)
{
	int temp = 1;
  MotorAPos = 0;
  MotorBPos = 0;
  attachInterrupt(digitalPinToInterrupt(MotorAcountA), doMotorA, CHANGE);
  attachInterrupt(digitalPinToInterrupt(MotorBcountA), doMotorB, CHANGE);
  while (MotorAPos > -pulse_weitiao && MotorBPos > -pulse_weitiao)yanxiantui(speeda, speedb);
  if(temp)
  {
	  while(MotorAPos < -pulse_weitiao || MotorBPos < -pulse_weitiao)
	  {
		   yanxianzou(speed3,speed4);
	  }
	  temp = 0;
  }
  detachInterrupt(digitalPinToInterrupt(MotorAcountA));
  detachInterrupt(digitalPinToInterrupt(MotorBcountA));
  MotorAPos = 0;
  MotorBPos = 0;
}

void zhongduanhoutuiweitiao2(int pulse_weitiao, int speeda, int speedb)
{
  MotorAPos = 0;
  MotorBPos = 0;
  attachInterrupt(digitalPinToInterrupt(MotorAcountA), doMotorA, CHANGE);
  attachInterrupt(digitalPinToInterrupt(MotorBcountA), doMotorB, CHANGE);
  while (MotorAPos > -pulse_weitiao && MotorBPos > -pulse_weitiao)retreat1(speeda, speedb);
  detachInterrupt(digitalPinToInterrupt(MotorAcountA));
  detachInterrupt(digitalPinToInterrupt(MotorBcountA));
  MotorAPos = 0;
  MotorBPos = 0;
}

void zhongduanhoutuiweitiao(int pulse_weitiao, int speeda, int speedb)
{
  MotorAPos = 0;
  MotorBPos = 0;
  attachInterrupt(digitalPinToInterrupt(MotorAcountA), doMotorA, CHANGE);
  attachInterrupt(digitalPinToInterrupt(MotorBcountA), doMotorB, CHANGE);
  while (MotorAPos > -pulse_weitiao && MotorBPos > -pulse_weitiao)yanxiantui(speeda, speedb);
  detachInterrupt(digitalPinToInterrupt(MotorAcountA));
  detachInterrupt(digitalPinToInterrupt(MotorBcountA));
  MotorAPos = 0;
  MotorBPos = 0;
}

void zhongduanzhixingweitiao1(int pulse_weitiao, int speeda, int speedb)
{
  int temp = 1;
  MotorAPos = 0;
  MotorBPos = 0;
  attachInterrupt(digitalPinToInterrupt(MotorAcountA), doMotorA, CHANGE);
  attachInterrupt(digitalPinToInterrupt(MotorBcountA), doMotorB, CHANGE);
  while (MotorAPos < pulse_weitiao && MotorBPos < pulse_weitiao)yanxianzou(speeda, speedb);
  if(temp)
  {
	  while(MotorAPos > pulse_weitiao || MotorBPos > pulse_weitiao)
	  {
		  yanxiantui(speed3,speed4);
	  }	
	  temp = 0;  
  }
  detachInterrupt(digitalPinToInterrupt(MotorAcountA));
  detachInterrupt(digitalPinToInterrupt(MotorBcountA));
  MotorAPos = 0;
  MotorBPos = 0;
}

void zhongduanzhixingweitiao2(int pulse_weitiao, int speeda, int speedb)
{
  int temp = 1;
  MotorAPos = 0;
  MotorBPos = 0;
  attachInterrupt(digitalPinToInterrupt(MotorAcountA), doMotorA, CHANGE);
  attachInterrupt(digitalPinToInterrupt(MotorBcountA), doMotorB, CHANGE);
  while (MotorAPos < pulse_weitiao && MotorBPos < pulse_weitiao)gostraight(speeda, speedb);
  detachInterrupt(digitalPinToInterrupt(MotorAcountA));
  detachInterrupt(digitalPinToInterrupt(MotorBcountA));
  MotorAPos = 0;
  MotorBPos = 0;
}

void zhongduanzhixingweitiao(int pulse_weitiao, int speeda, int speedb)
{
  MotorAPos = 0;
  MotorBPos = 0;
  attachInterrupt(digitalPinToInterrupt(MotorAcountA), doMotorA, CHANGE);
  attachInterrupt(digitalPinToInterrupt(MotorBcountA), doMotorB, CHANGE);
  while (MotorAPos < pulse_weitiao && MotorBPos < pulse_weitiao)yanxianzou(speeda, speedb);
  detachInterrupt(digitalPinToInterrupt(MotorAcountA));
  detachInterrupt(digitalPinToInterrupt(MotorBcountA));
  MotorAPos = 0;
  MotorBPos = 0;
}


////////////////////////////////////////////////////////ֹͣ
void stop(int n)
{
  digitalWrite(MotorApin1, LOW);
  digitalWrite(MotorApin2, LOW);
  analogWrite(MotorApwm, 0);

  digitalWrite(MotorBpin1, LOW);
  digitalWrite(MotorBpin2, LOW);
  analogWrite(MotorBpwm, 0);
  delay(n);
}


/////////////////////////////////////////////////////////ѭ��
void calc_pid() {
  P = error;
  I = I + error;
  D = error - previous_error;
  
  if(flag == 1)
  {
	  if (I > 30) I = 10;
	  PID_value = (Kp1 * P) + (Ki1 * I) + (Kd1* D);
  }
  else 
  {
      if (I > 25) I = 15;
	  PID_value = (Kp2 * P) + (Ki2 * I) + (Kd2* D);
  }
  previous_error = error;
}
void yanxianzou(int a, int b) {
  flag = 1;
  getABCD();
  calc_pid();
  if (val4 < 1000 && val5 < 900)//�ں���
    goStraight(a, b);
  else if (val4 < 1000 && val5 > 900)//ƫ��
    goStraight(a + PID_value, b - PID_value);
  else if (val4 > 1000&& val5 < 900)//ƫ��
    goStraight(a - PID_value, b + PID_value);
  else
    goStraight(a, b);
}

void yanxiantui(int a, int b) {
  flag = 0;
  getABCD();
  calc_pid();
  if (val6 < 800 && val7 <1400)//�ں���
    retreat(a, b);
  else if (val6 >  800  && val7 < 1400)//ƫ��
    retreat(a - PID_value, b +PID_value);
  else if (val6 <  800  && val7 > 1400)//ƫ��
    retreat(a+PID_value , b - PID_value);
  else
    retreat(a, b);
}
///////////////////////////////////////////////////////////////////��ǰ��������
void R2after1(int n, int speeda, int speedn)//ֱ���ҵ�2����
{ //���ٹ�n����(�Ҳ��2���)
  int count = 0;
  unsigned long times;
  rjg2 = 0;
  int flag;

  while (count < n)
  {
    zhixingweitiao(250,speeda,speedn);
    flag = 0;
    while (flag == 0)
    {
      yanxianzou(speeda, speedn);
      rjg2 = digitalRead(Rlaser2);
      times = millis();
      while (rjg2)
      { //�ں�ɫ����
        yanxianzou(speeda, speedn);
        rjg2 = digitalRead(Rlaser2);
      }
      if (millis() - times > 25)//30 25 30
      { //Խ����ɫ������
        count++;
        flag = 1;
      }
    }
  }
}

void L2after1(int n, int speeda, int speedn)//ֱ�����2����
{ //���ٹ�n����(����2���)
  int count = 0;
  unsigned long times;
  ljg2 = 0;
  int flag;
  while (count < n)
  {
    zhixingweitiao(250,speeda,speedn);
    flag = 0;
    while (flag == 0)
    {
      yanxianzou(speeda, speedn);
      ljg2 = digitalRead(Llaser2);
      times = millis();
      while (ljg2)
      { //�ں�ɫ����
        yanxianzou(speeda, speedn);
        ljg2 = digitalRead(Llaser2);
      }
      if (millis() - times > 25)//30 25 30 10
      { //Խ����ɫ������
        count++;
        flag = 1;
      }
    }
  }
}

void R1after1(int n, int speeda, int speedn)//ֱ���ҵ�1����
{ //���ٹ�n����(�Ҳ��1���)
  int count = 0;
  unsigned long times;
  rjg1 = 0;
  int flag;
  zhixingweitiao(150,speeda,speedn);
    flag = 0;
    while (flag == 0)
    {
      yanxianzou(speeda, speedn);
      rjg1 = digitalRead(Rlaser1);
      times = millis();
      while (rjg1)
      { //�ں�ɫ����
        yanxianzou(speeda, speedn);
        rjg1 = digitalRead(Rlaser1);
      }
      if (millis() - times > 25)//30 25 30
      { //Խ����ɫ������
        count++;
        flag = 1;
      }
    }
  }

void L1after1(int n, int speeda, int speedb)//ֱ�����1����
{ //���ٹ�n����(����1���)
  int count = 0;
  unsigned long times;
  ljg1 = 0;
  int flag;
  while (count < n)
  {
    zhixingweitiao(150, speeda, speedb);
    flag = 0;
    while (flag == 0)
    {
      yanxianzou(speeda, speedb);
      ljg1 = digitalRead(Llaser1);
      times = millis();
      while (ljg1)
      { //�ں�ɫ����
        yanxianzou(speeda, speedb);
        ljg1 = digitalRead(Llaser1);
      }
      if (millis() - times > 25)//30 25 30 10
      { //Խ����ɫ������
        count++;
        flag = 1;
      }
    }
  }
}

void R2after2(int n, int speeda, int speedb)//ֱ���ҵ�2����
{ //���ٹ�n����(�Ҳ��2���)
  int count = 0;
  unsigned long times;
  rjg2 = 0;
  int flag;
  while (count < n)
  {
    houtuiweitiao(150, speeda, speedb);
    flag = 0;
    while (flag == 0)
    {
      yanxiantui(speeda, speedb);
      rjg2 = digitalRead(Rlaser2);
      times = millis();
      while (rjg2)
      { //�ں�ɫ����
        yanxiantui(speeda, speedb);
        rjg2 = digitalRead(Rlaser2);
      }
      if (millis() - times > 25)//30 25 30
      { //Խ����ɫ������
        count++;
        flag = 1;
      }
    }
  }
}

void L2after2(int n, int speeda, int speedb)//ֱ�����2����
{ //���ٹ�n����(����2���)
  int count = 0;
  unsigned long times;
  ljg2 = 0;
  int flag;

  while (count < n)
  {
    houtuiweitiao(150, speeda, speedb);
    flag = 0;
    while (flag == 0)
    {
      yanxiantui(speeda, speedb);
      ljg2 = digitalRead(Llaser2);
      times = millis();
      while (ljg2)
      { //�ں�ɫ����
        yanxiantui(speeda, speedb);
        ljg2 = digitalRead(Llaser2);
      }
      if (millis() - times > 25)//30 25 30 10
      { //Խ����ɫ������
        count++;
        flag = 1;
      }
    }

    //  stop(1000);
  }
}

void R1after2(int n, int speeda, int speedn)//ֱ���ҵ�1����
{ //���ٹ�n����(�Ҳ��1���)
  int count = 0;
  unsigned long times;
  rjg1 = 0;
  int flag;

  while (count < n)
  {
    houtuiweitiao(150, speeda, speedn);
    flag = 0;
    while (flag == 0)
    {
      yanxiantui(speeda, speedn);
      rjg1 = digitalRead(Rlaser1);
      times = millis();
      while (rjg1)
      { //�ں�ɫ����
        yanxiantui(speeda, speedn);
        rjg1 = digitalRead(Rlaser1);
      }
      if (millis() - times > 25)//30 25 30
      { //Խ����ɫ������
        count++;
        flag = 1;
      }
    }
  }
}

void L1after2(int n, int speeda, int speedn)//ֱ�����1����
{ //���ٹ�n����(����1���)
  int count = 0;
  unsigned long times;
  ljg1 = 0;
  int flag;

  while (count < n)
  {
    houtuiweitiao(150, speeda, speedn);
    flag = 0;
    while (flag == 0)
    {
      yanxiantui(speeda, speedn);
      ljg1 = digitalRead(Llaser1);
      times = millis();
      while (ljg1)
      { //�ں�ɫ����
        yanxiantui(speeda, speedn);
        ljg1 = digitalRead(Llaser1);
      }
      if (millis() - times > 25)//30 25 30 10
      { //Խ����ɫ������
        count++;
        flag = 1;
      }
    }
  }
}

void zhixingweitiao(int weitiao, int speeda, int speedb)
{//ǰ�� weitiao ����Ĳ���
  for (unsigned times = millis(); millis() - times < weitiao;)
    yanxianzou(speeda, speedb);
}

void houtuiweitiao(int weitiao, int speeda, int speedb)
{//���� weitiao ����Ĳ���
  for (unsigned times = millis(); millis() - times < weitiao;)
    yanxiantui(speeda, speedb);

}

void R2Arrive1(int speeda, int speedb)
{ //�Ҽ����2�������ֹͣ
  unsigned long times;
  int count = 0;
  zhixingweitiao(150, speeda, speedb);
  while (count < 1)
  {
    yanxianzou(speeda, speedb);
    rjg2 = digitalRead(Rlaser2);
    times = millis();
    while (rjg2 && count < 1)
    {
      yanxianzou(speeda, speedb);
      rjg2 = digitalRead(Rlaser2);
      if (millis() - times > 20)   //40  45  35  45  55  60 45
      {
        count++;
      }
    }
  }
  retreat(200,200);
  delay(20);
  stop(100);
}
void L1Arrive1(int speeda, int speedb)
{ //�Ҽ����2�������ֹͣ
  unsigned long times;
  int count = 0;
  zhongduanzhixingweitiao(100, speeda, speedb);
  while (count < 1)
  {
    yanxianzou(speeda, speedb);
    ljg1 = digitalRead(Llaser1);
    times = millis();
    while (ljg1 && count < 1)
    {
      yanxianzou(speeda, speedb);
      ljg1 = digitalRead(Llaser1);
      if (millis() - times > 25)   //40  45  35  45  55  60 45
      {
        count++;
      }
    }
  }
  retreat(200,200);
  delay(20);
  stop(100);
}
void L2Arrive1(int speeda, int speedb)
{ //�Ҽ����2�������ֹͣ
  unsigned long times;
  int count = 0;
  zhixingweitiao(150, speeda, speedb);
  while (count < 1)
  {
    yanxianzou(speeda, speedb);
    ljg2 = digitalRead(Llaser2);
    times = millis();
    while (ljg2 && count < 1)
    {
      yanxianzou(speeda, speedb);
      rjg2 = digitalRead(Llaser2);
      if (millis() - times > 20)   //40  45  35  45  55  60 45
      {
        count++;
      }
    }
  }
  retreat(200,200);
  delay(20);
  stop(100);
}

void R1Arrive1(int speeda, int speedb)
{ //�Ҽ����1�������ֹͣ
  unsigned long times;
  int count = 0;
  zhixingweitiao(150, speeda, speedb);
  while (count < 1)
  {
    yanxianzou(speeda, speedb);
    rjg1 = digitalRead(Rlaser1);
    times = millis();
    while (rjg1 && count < 1)
    {
      yanxianzou(speeda, speedb);
      rjg1 = digitalRead(Rlaser1);
      if (millis() - times > 5)   //40  45  35  45  55  60 45
      {
        count++;
      }
    }
  }
  retreat(200,200);
  delay(20);
  stop(100);
}

void R2Arrive2(int speeda, int speedb)
{ //�Ҽ����2�������ֹͣ
  unsigned long times;
  int count = 0;
  houtuiweitiao(150, speeda, speedb);
  while (count < 1)
  {
    yanxiantui(speeda, speedb);
    rjg2 = digitalRead(Rlaser2);
    times = millis();
    while (rjg2 && count < 1)
    {
      yanxiantui(speeda, speedb);
      rjg2 = digitalRead(Rlaser2);
      if (millis() - times > 15)   //40  45  35  45  55  60 45
      {
        count++;
      }
    }
  }
  goStraight(200,200);
  delay(20);
  stop(100);
}

void L2Arrive2(int speeda, int speedb)
{ //�Ҽ����2�������ֹͣ
  unsigned long times;
  int count = 0;
  houtuiweitiao(100, speeda, speedb);
  while (count < 1)
  {
    yanxiantui(speeda, speedb);
    ljg2 = digitalRead(Llaser2);
    times = millis();
    while (ljg2 && count < 1)
    {
      yanxiantui(speeda, speedb);
      rjg2 = digitalRead(Llaser2);
      if (millis() - times > 20)   //40  45  35  45  55  60 45
      {
        count++;
      }
    }
  }
  goStraight(200,200);
  delay(20);
  stop(100);
}

void R1Arrive2(int speeda, int speedb)
{ //�Ҽ����1�������ֹͣ
  unsigned long times;
  int count = 0;
  houtuiweitiao(270, speeda, speedb);
  while (count < 1)
  {
    yanxiantui(speeda, speedb);
    rjg1 = digitalRead(Rlaser1);
    times = millis();
    while (rjg1 && count < 1)
    {
      yanxiantui(speeda, speedb);
      rjg1 = digitalRead(Rlaser1);
      if (millis() - times > 20)   //40  45  35  45  55  60 45
      {
        count++;
      }
    }
  }
  goStraight(200,200);
  delay(20);
  stop(100);
}


//////////////////////////////////////////////////////////ת�亯��
void zuozhuan1(int speeda, int speedb) {//BΪ���֣�AΪ����      ���õ���
  digitalWrite(MotorApin1, LOW);
  digitalWrite(MotorApin2, HIGH);
  analogWrite(MotorApwm, speeda);

  digitalWrite(MotorBpin1, LOW);
  digitalWrite(MotorBpin2, HIGH);
  analogWrite(MotorBpwm, speedb);
}

void zuozhuan(int speeda, int speedb)
{
  move_compute(&speeda, &speedb);
  zuozhuan1(speeda, speedb);
}
unsigned long timee = 0;
void turn_compute(int* speeda, int* speedb)
{
	attachInterrupt(digitalPinToInterrupt(MotorAcountA),doMotorA,CHANGE);
    attachInterrupt(digitalPinToInterrupt(MotorBcountA),doMotorB,CHANGE);
	if(millis() - timee > 20)
	{
  omgaA = abs((float)MotorAPos * 50 / onecircle);//��������ת��
  omgaB = abs((float)MotorBPos * 50 / onecircle);//��������ת��
  float t1 = (float)(*(speeda));
  float t2 = (float)(*(speedb));
  if(omgaA>omgaB && (omgaA - omgaB)>0.1) 
  {
    *(speedb) += 3; //= (float)(t2 - 100*(omgaA - omgaB));
    *(speeda) -= 2; //= (float)(t1 + 100*(omgaA - omgaB));
  }
  else if(omgaA< omgaB && (omgaB - omgaA)>0.1)
  {
    *(speedb) -= 2;// (float)(t2 + 80*(omgaB - omgaA));
    *(speeda) += 3;// (float)(t1 - 80*(omgaB - omgaA));
  }
  if (*(speedb) > t2 * 1.2 || *(speedb) < t2 * 0.1)  *(speedb) = t2;
  if (*(speeda) > t1 * 1.2 || *(speeda) < t1 * 0.1) *(speeda) = t1;//��ֹ�����������ٶ�̫��
  //ʵ�ʹ����п��ٲ�������һ�����ӣ���һ�������ٶ����������־��޷���Ϊԭ��
  timee = millis();
	}
    detachInterrupt(digitalPinToInterrupt(MotorAcountA));
    detachInterrupt(digitalPinToInterrupt(MotorBcountA));
  
}

void laoshiyouzhuan(int speeda,int speedb)
{
	turn_compute(&speeda,&speedb);
	youzhuan1(speeda,speedb);
}

void laoshizuozhuan(int speeda,int speedb)
{
	unsigned long timee = millis();
	if(millis() - timee > 20)
	{
		omgaA = abs((float)MotorAPos * 50 / onecircle);//��������ת��
        omgaB = abs((float)MotorBPos * 50 / onecircle);//��������ת��
        float t1 = (float)speeda;
        float t2 = (float)speedb;
		if(omgaA>omgaB && (omgaA - omgaB)>0.1) 
        {
           speedb += 3; //= (float)(t2 - 100*(omgaA - omgaB));
           speeda -= 2; //= (float)(t1 + 100*(omgaA - omgaB));
        }
        else if(omgaA< omgaB && (omgaB - omgaA)>0.1)
        {
           speedb -= 2;// (float)(t2 + 80*(omgaB - omgaA));
           speeda += 3;// (float)(t1 - 80*(omgaB - omgaA));
		}
        if (speedb > t2 * 1.2 || speedb < t2 * 0.1)  speedb = t2;
        if (speeda > t1 * 1.2 || speeda < t1 * 0.1) speeda = t1;//��ֹ�����������ٶ�̫��
         //ʵ�ʹ����п��ٲ�������һ�����ӣ���һ�������ٶ����������־��޷���Ϊԭ��
        timee = millis();
	}
	zuozhuan1(speeda, speedb);
}

//void laoshiyouzhuan(int speeda,int speedb)
//{
//	unsigned long time = millis();
//	if(millis() - time > 40)
//	{
//		omgaA = abs((float)MotorAPos * 25 / onecircle);//��������ת��
//        omgaB = abs((float)MotorBPos * 25 / onecircle);//��������ת��
//        float t1 = (float)speeda;
//        float t2 = (float)speedb;
//		if(omgaA > omgaB && (omgaA - omgaB)>0.1) 
//        {
//           speedb += 5; //= (float)(t2 - 100*(omgaA - omgaB));
//           speeda -= 5; //= (float)(t1 + 100*(omgaA - omgaB));
//        }
//        else if(omgaA< omgaB && (omgaB - omgaA)>0.1)
//        {
//           speedb-= 5; // (float)(t2 + 80*(omgaB - omgaA));
//           speeda+= 5; // (float)(t1 - 80*(omgaB - omgaA));
//		}
//        if (speedb > t2 * 1.2 || speedb < t2 * 0.1)  speedb = t2;
//        if (speeda > t1 * 1.2 || speeda < t1 * 0.1) speeda = t1;//��ֹ�����������ٶ�̫��
//         //ʵ�ʹ����п��ٲ�������һ�����ӣ���һ�������ٶ����������־��޷���Ϊԭ��
//	}
//	youzhuan1(speeda, speedb);
//}

void youzhuan1(int speeda, int speedb) {//BΪ���֣�AΪ����     ���õ���
  digitalWrite(MotorApin1, HIGH);
  digitalWrite(MotorApin2, LOW);
  analogWrite(MotorApwm, speeda);

  digitalWrite(MotorBpin1, HIGH);
  digitalWrite(MotorBpin2, LOW);
  analogWrite(MotorBpwm, speedb);
}

void youzhuan(int speeda, int speedb)
{
  move_compute(&speeda, &speedb);
  youzhuan1(speeda, speedb);
}

void lbeforeweitiao(int leftbeforeweitiao, int speeda, int speedb)
{// ���õ���
  unsigned long times = millis();
  while (millis() - times < leftbeforeweitiao)
  {
    zuozhuan(speeda, speedb);
  }
}

void rbeforeweitiao(int rightbeforeweitiao, int speeda, int speedb)
{// ���õ���
  unsigned long times = millis();
  while (millis() - times < rightbeforeweitiao)
  {
    youzhuan(speeda, speedb);
  }
}


void turnRightArrive(int sa,int sb){//A������ת�Ҽ���Ƶ�����ߣ�û�з�װͣ��
  unsigned long times;
  int flag = 0;
  int rj=0;
  while (flag < 1){
    laoshiyouzhuan(sa,sb);
	rj= digitalRead(Llaser1);
    times = millis();
    while (rj && flag < 1){
      laoshiyouzhuan(sa,sb);
      //times++;
      if (millis() - times >10 ){//35
        flag++;
      }
      rj = digitalRead(Llaser1);
    }
  }
}
void turnRightArrive2(int sa,int sb){//A������ת�Ҽ���Ƶ�����ߣ�û�з�װͣ��
  unsigned long times;
  int flag = 0;
  int rj=0;
  while (flag < 1){
    laoshiyouzhuan(sa,sb);
	rj= digitalRead(Rlaser2);
    times = millis();
    while (rj && flag < 1){
      laoshiyouzhuan(sa,sb);
      //times++;
      if (millis() - times >10 ){//35
        flag++;
      }
      rj = digitalRead(Rlaser2);
    }
  }
}
void turnLeftArrive(int sa,int sb){//A����ת��༤��Ƶ�����ߣ�û�з�װͣ��
	unsigned long times;
	int flag=0;
	int lj=0;
	while(flag<1){
		laoshizuozhuan(sa,sb);
		lj=digitalRead(Llaser1);
		times=millis();
		while(lj && flag<1){
			laoshizuozhuan(sa,sb);
			if(millis()-times >10 ){
				flag++;
			}
			lj = digitalRead(Llaser1);
		}
	}
}
void turnLeftArrive2(int sa,int sb){//A����ת��༤��Ƶ�����ߣ�û�з�װͣ��
	unsigned long times;
	int flag=0;
	int lj=0;
	while(flag<1){
		laoshizuozhuan(sa,sb);
		lj=digitalRead(Llaser2);
		times=millis();
		while(lj && flag<1){
			laoshizuozhuan(sa,sb);
			if(millis()-times >10 ){
				flag++;
			}
			lj = digitalRead(Llaser2);
		}
	}
}

#define pulse_45L 226
void turnleft45(int speeda, int speedb) {
    MotorAPos = 0;
    MotorBPos = 0;
    attachInterrupt(digitalPinToInterrupt(MotorAcountA), doMotorA, CHANGE);
    attachInterrupt(digitalPinToInterrupt(MotorBcountA), doMotorB, CHANGE);
    while (MotorAPos > -180 && MotorBPos < 180) {
    laoshizuozhuan(speeda,speedb);
  }
  turnLeftArrive(speed1,speed2);
  turnRightArrive(speed5,speed6);
	  if(MotorBPos < pulse_45L+50)
	  {
		stop(1);
	  }
  detachInterrupt(digitalPinToInterrupt(MotorAcountA));
  detachInterrupt(digitalPinToInterrupt(MotorBcountA));
  MotorAPos = 0;
  MotorBPos = 0;
}
#define pulse_45R 250
void turnright45(int speeda, int speedb) {
	MotorAPos = 0;
    MotorBPos = 0;
  attachInterrupt(digitalPinToInterrupt(MotorAcountA), doMotorA, CHANGE);
  attachInterrupt(digitalPinToInterrupt(MotorBcountA), doMotorB, CHANGE);
  while(MotorAPos < pulse_45R -50 && MotorBPos > -pulse_45R + 50) {
    laoshiyouzhuan(speeda,speedb);
  }
  turnRightArrive(speeda,speedb);
  turnLeftArrive(speed5,speed6);
	if(MotorAPos < pulse_45R + 50 )
	  {
		stop(1);  
	  }
  detachInterrupt(digitalPinToInterrupt(MotorAcountA));
  detachInterrupt(digitalPinToInterrupt(MotorBcountA));
  MotorAPos = 0;
  MotorBPos = 0;
}
#define pulse_90L 480
void turnleft90(int speeda, int speedb) {
  MotorAPos = 0;
  MotorBPos = 0;
  attachInterrupt(digitalPinToInterrupt(MotorAcountA), doMotorA, CHANGE);
  attachInterrupt(digitalPinToInterrupt(MotorBcountA), doMotorB, CHANGE);
  while (MotorAPos > -pulse_90L + 50 && MotorBPos < pulse_90L - 50) {
    laoshizuozhuan(speeda, speedb);
  }
  turnLeftArrive(speeda,speedb);
  turnRightArrive(speeda,speedb);
	  if(MotorAPos > -pulse_90L+50)
	  {
		stop(1);  
	  }
  detachInterrupt(digitalPinToInterrupt(MotorAcountA));
  detachInterrupt(digitalPinToInterrupt(MotorBcountA));
  MotorAPos = 0;
  MotorBPos = 0;
}
#define pulse_90R 465
void turnright90(int speeda, int speedb) {
  MotorAPos = 0;
  MotorBPos = 0;
  attachInterrupt(digitalPinToInterrupt(MotorAcountA), doMotorA, CHANGE);
  attachInterrupt(digitalPinToInterrupt(MotorBcountA), doMotorB, CHANGE);
  while (MotorAPos < pulse_90R - 50 && MotorBPos > -pulse_90R + 50) {
    laoshiyouzhuan(speeda, speedb);
  }
  turnRightArrive2(speeda,speedb);
  lbeforeweitiao(160,speed5,speed6);
  //turnLeftArrive2(speeda,speedb);
	  if(MotorAPos > pulse_90R + 50)
	  {
		stop(1); 
	  }
  detachInterrupt(digitalPinToInterrupt(MotorAcountA));
  detachInterrupt(digitalPinToInterrupt(MotorBcountA));
  MotorAPos = 0;
  MotorBPos = 0;
}
#define pulse_135L 780
void turnleft135(int speeda, int speedb) {
  stop(200);
  MotorAPos = 0;
  MotorBPos = 0;
  attachInterrupt(digitalPinToInterrupt(MotorAcountA), doMotorA, CHANGE);
  attachInterrupt(digitalPinToInterrupt(MotorBcountA), doMotorB, CHANGE);
  while (MotorAPos > -pulse_135L + 40 && MotorBPos < pulse_135L - 40) {
    laoshizuozhuan(speeda,speedb);
  }
  turnLeftArrive(speeda,speedb);
  youzhuan(speed5,speed6);
  delay(130);
  stop(1);
  if( MotorBPos > pulse_135L +50)
	  {
		stop(1);
	  }
  detachInterrupt(digitalPinToInterrupt(MotorAcountA));
  detachInterrupt(digitalPinToInterrupt(MotorBcountA));
  MotorAPos = 0;
  MotorBPos = 0;
}
#define pulse_135R 780
void turnright135(int speeda, int speedb) {
  stop(200);
  MotorAPos = 0;
  MotorBPos = 0;
  attachInterrupt(digitalPinToInterrupt(MotorAcountA), doMotorA, CHANGE);
  attachInterrupt(digitalPinToInterrupt(MotorBcountA), doMotorB, CHANGE);
  while (MotorAPos < pulse_135R - 40 && MotorBPos > -pulse_135R + 40) {
    laoshiyouzhuan(speeda, speedb+10);
  }
  turnRightArrive(speeda,speedb);
  zuozhuan(speed5,speed6);
  delay(200);
  stop(1);
  if(MotorAPos > pulse_135R + 50 )
	  {
		stop(1);  
	  }
  detachInterrupt(digitalPinToInterrupt(MotorAcountA));
  detachInterrupt(digitalPinToInterrupt(MotorBcountA));
  MotorAPos = 0;
  MotorBPos = 0;
}

void turn180()
{
  houtuiweitiao(700, speed5, speed6);
  stop(300);
  turn180_butui();
}
#define turn180_pulse 1035//1080
void turn180_butui()
{
  stop(200);
  MotorAPos = 0;
  MotorBPos = 0;
	int temp = 1;
  attachInterrupt(digitalPinToInterrupt(MotorAcountA), doMotorA, CHANGE);
  attachInterrupt(digitalPinToInterrupt(MotorBcountA), doMotorB, CHANGE);
  while (MotorAPos < turn180_pulse && MotorBPos > -turn180_pulse) {
    laoshiyouzhuan(speed1, speed2+15);
  }
  zuozhuan(150,150);
  delay(20);
  stop(1);
  detachInterrupt(digitalPinToInterrupt(MotorAcountA));
  detachInterrupt(digitalPinToInterrupt(MotorBcountA));
  MotorAPos = 0;
  MotorBPos = 0;
  stop(300);
  zhixingweitiao(500,speed3 - 4,speed4 - 4);
}

void zuoerqucese()
{//����һ���Ӵӳ�ʼλ��������ɫ
  int i = 0;
  ZUO2.write(zuo2_properPos +8);
  for (i = zuo4_InitPos; i < zuo4_properPos; i++) {
    ZUO4.write(i);
    delay(3);
  }
  for (i = zuo2_properPos+8; i > zuo2_properPos - 20; i--) {
    ZUO2.write(i);
    delay(5);
  }
}

void zuoercun()
{//����ɫŲ�����
  int i = 0;
  for (i = zuo2_properPos - 20; i < zuo2_InitPos; i++) {
    ZUO2.write(i);
    delay(6);
  }
  for (i = zuo4_properPos; i < zuo4_properPos + 10; i++) {
    ZUO4.write(i);
    delay(1);
  }
}

void zuoerfang()
{//zuoercun()�ķ���鶯��
  int i = 0;
  ZUO4.write(zuo4_properPos);
  for (i = zuo2_InitPos; i > zuo2_properPos - 20; i--) {
    ZUO2.write(i);
    delay(5);
  }
  delay(150);
  for (i = zuo2_properPos - 20; i < zuo2_properPos; i++) {
    ZUO2.write(i);
    delay(5);
  }
  for (i = zuo4_properPos; i > zuo4_InitPos; i--) {
    ZUO4.write(i);
    delay(1);
  }
  ZUO2.write(zuo2_InitPos);
}

void youerqucese()
{//����һ���ҹ��Ӵӳ�ʼλ��������ɫ
  int i = 0;
  YOU2.write(you2_properPos);
  for (i = you4_InitPos; i > you4_properPos; i--) {
    YOU4.write(i);
    delay(3);
  }
  for (i = you2_properPos; i < you2_properPos + 40; i++) {
    YOU2.write(i);
    delay(5);
  }
}

void youercun()
{//����ɫŲ���ұ�
	YOU4.write(you4_properPos - 15);
  for (int i = you2_properPos + 40; i > you2_InitPos - 10; i--) {
    YOU2.write(i);
    delay(6);
  }
}

void youerfang()
{//youercun()�ķ���鶯��
  int i = 0;
  YOU4.write(you4_properPos);
  for (i = you2_InitPos; i < you2_properPos + 40; i++) {
    YOU2.write(i);
    delay(6);
  }
  for (i = you2_properPos + 40; i > you2_properPos - 10; i--) {
    YOU2.write(i);
    delay(4);
  }
  YOU4.write(you4_properPos + 10);
  delay(100);
  YOU4.write(you4_InitPos);
  delay(100);
  YOU2.write(you2_InitPos);
}

void guomizi1()
{
  zhongduanzhixingweitiao(385, speed3+8, speed4+8);
}

void guomizi3()
{
	retreat(100,100);
    delay(18);
    zhongduanzhixingweitiao(70, speed3+8, speed4+8);
	R2Arrive1(speed3,speed4);
} 

void guomizi2()
{
  zhongduanhoutuiweitiao(405, speed3, speed4);
}
void guomizi4()
{
    goStraight(100,100);
	delay(18);
	zhongduanhoutuiweitiao(70, speed3, speed4);
	R2Arrive2(speed3,speed4);
}


void qucese()
{
	zhixingweitiao(400, speed3-5,speed4-5);
	guomizi1();
	zhongduanzhixingweitiao(155,speed5+6,speed6+6);
	digitalWrite(LED,HIGH);
    L1after1(1,speed3, speed4);
	digitalWrite(LED,LOW);
	stop(100);
}

void cewanhuizhongxin()
{
  houtuiweitiao(200, speed3+8,speed4+8);
  R2after2(1, speed1, speed2);
  guomizi4();
  stop(300);
}

void qufang()
{
  zhixingweitiao(350, speed3 - 5,speed4 - 5);
  guomizi1();
//	zhixingweitiao(100, speed5,speed6);
//  L1after1(1, speed1, speed2);
  zhongduanzhixingweitiao(2*onecircle, speed1, speed2);
	retreat(200,200);
	delay(20);
	digitalWrite(LED,HIGH);
  L1Arrive1(speed3, speed4);
	digitalWrite(LED,LOW);
	zhongduanhoutuiweitiao1(15, speed5, speed6);
	stop(10);
}

void half_qufang()
{
	zhixingweitiao(150, speed5,speed6);
	zhongduanzhixingweitiao(onecircle+80, speed1, speed2);
	retreat(100,100);
	delay(20);
	L1Arrive1(speed3,speed4);
	zhongduanhoutuiweitiao1(15, speed5, speed6);
	stop(10);
}

void fangwanhuizhongxin()
{
  houtuiweitiao(300, speed3+8,speed4+8);
  R2after2(1, speed1, speed2);
  R2after2(1, speed5, speed6);
  guomizi4();
  stop(350);
}

void qumission2() {
  zhixingweitiao(200,speed3,speed4);
  zhongduanzhixingweitiao(2*onecircle - 100, speed5, speed6);
  R1Arrive1(speed3, speed4);
}

void black_to_mission2() {
  turn180();
  R2after1(2, speed1 + 10, speed2 + 10);
  guomizi1();
	qumission2();
	//qufang();
}
void mission1() {
  zhongduanzhixingweitiao(onecircle + 300,speed1,speed2);
  R2after1(1, speed1, speed2);
  R2after1(1, speed1, speed2);
  guomizi3();
  stop(300);
  turnleft90(speed1, speed2);
  qucese();
  zuoerqucese();
  colorA = GetColor();
  zuoercun();
  if (colorA == green) {     //OK
    half_qufang();
    zuoerfang();
    fangwanhuizhongxin();
    turnright90(speed1, speed2);
    qucese();
    youerqucese();
    colorC = GetColor();
    youercun();
    if (colorC == white) {
      cewanhuizhongxin();
      turnleft45(speed1, speed2);
      qufang();
      youerfang();
      fangwanhuizhongxin();
      turnright135(speed1, speed2);
      qucese();
      zuoerqucese();
      colorE = GetColor();
      zuoercun();
      if (colorE == red) {  //�̰׺�      OK
        cewanhuizhongxin();
        turnleft90(speed1, speed2);
        qufang();
        zuoerfang();
        fangwanhuizhongxin();
        turnleft135(speed1, speed2);
        qumission2();
      }
      else if (colorE == black) {   //�̰׺�   OK
        cewanhuizhongxin();
        turnleft45(speed1, speed2);
        qufang();
        zuoerfang();
        black_to_mission2();
      }
      else if (colorE == blue) {    //�̰���    OK
        half_qufang();
        zuoerfang();
        fangwanhuizhongxin();
        turnright135(speed1, speed2);
        qumission2();
      }
    }
    else if (colorC == red) {
      half_qufang();
      youerfang();
      fangwanhuizhongxin();
      turnright90(speed1, speed2);
      qucese();
      zuoerqucese();
      colorE = GetColor();
      zuoercun();
      if (colorE == white) {    //�̺��      OK
        cewanhuizhongxin();
        turnleft135(speed1, speed2);
        qufang();
        zuoerfang();
        fangwanhuizhongxin();
        turnleft90(speed1, speed2);
        qumission2();
      }
      else if (colorE == black) {   //�̺��   OK
        cewanhuizhongxin();
        turnleft45(speed1, speed2);
        qufang();
        zuoerfang();
        black_to_mission2();
      }
      else if (colorE == blue) {    //�̺���    OK
        half_qufang();
        zuoerfang();
        fangwanhuizhongxin();
        turnright135(speed1, speed2);
        qumission2();
      }
    }
    else if (colorC == black) {
      cewanhuizhongxin();
      turnright45(speed1, speed2);
      qufang();
      youerfang();
      fangwanhuizhongxin();
      turnright45(speed1, speed2);
      qucese();
      zuoerqucese();
      colorE = GetColor();
      zuoercun();
      if (colorE == white) {  //�̺ڰ�       OK
        cewanhuizhongxin();
        turnleft135(speed1, speed2);
        qufang();
        zuoerfang();
        fangwanhuizhongxin();
        turnleft90(speed1, speed2);
        qumission2();
      }
      else if (colorE == red) { //�̺ں�   OK
        cewanhuizhongxin();
        turnleft90(speed1, speed2);
        qufang();
        zuoerfang();
        fangwanhuizhongxin();
        turnleft135(speed1, speed2);
        qumission2();
      }
      else if (colorE == blue) {    //�̺���     OK
        half_qufang();
        zuoerfang();
        fangwanhuizhongxin();
        turnright135(speed1, speed2);
        qumission2();
      }
    }
    else if (colorC == blue) {
      cewanhuizhongxin();
      turnright90(speed1, speed2);
      qucese();
      zuoerqucese();
      colorE = GetColor();
      zuoercun();
      half_qufang();
      youerfang();
      if (colorE == white) {  //������     OK
        fangwanhuizhongxin();
        turnleft135(speed1, speed2);
        qufang();
        zuoerfang();
        fangwanhuizhongxin();
        turnleft90(speed1, speed2);
        qumission2();
      }
      else if (colorE == red) { //������      OK
        fangwanhuizhongxin();
        turnleft90(speed1, speed2);
        qufang();
        zuoerfang();
        fangwanhuizhongxin();
        turnleft135(speed1, speed2);
        qumission2();
      }
      else if (colorE == black) { //������     OK
        fangwanhuizhongxin();
        turnleft45(speed1, speed2);
        qufang();
        zuoerfang();
        black_to_mission2();
      }
    }
  }
  else if (colorA == white) {        //OK
    cewanhuizhongxin();
    turnright45(speed1, speed2);
    qufang();
    zuoerfang();
    fangwanhuizhongxin();
    turnright45(speed1, speed2);
    qucese();
    youerqucese();
    colorC = GetColor();
    youercun();
    if (colorC == green) {
      cewanhuizhongxin();
      turnleft90(speed1, speed2);
      qufang();
      youerfang();
      ///////////////////////
      turn180();
      R2after1(2, speed1, speed2);
      guomizi1();
      qucese();
      zuoerqucese();
      colorE = GetColor();
      zuoercun();
      if (colorE == red) {  //���̺�              OK
        cewanhuizhongxin();
        turnleft90(speed1, speed2);
        qufang();
        zuoerfang();
        fangwanhuizhongxin();
        turnleft135(speed1, speed2);
        qumission2();
      }
      else if (colorE == black) {   //���̺�       OK
        cewanhuizhongxin();
        turnleft45(speed1, speed2);
        qufang();
        zuoerfang();
        black_to_mission2();
      }
      else if (colorE == blue) {    //������           OK
        half_qufang();
        zuoerfang();
        fangwanhuizhongxin();
        turnright135(speed1, speed2);
        qumission2();
      }
    }
    else if (colorC == red) {
      half_qufang();
      youerfang();
      fangwanhuizhongxin();
      turnright90(speed1, speed2);
      qucese();
      zuoerqucese();
      colorE = GetColor();
      zuoercun();
      if (colorE == green) {    //�׺���     OK
        turn180_butui();
		  zhongduanzhixingweitiao(50,speed5,speed6);
        R2after1(1, speed1, speed2);
		guomizi1();
        qufang();
        zuoerfang();
        fangwanhuizhongxin();
        turnleft45(speed1, speed2);
        qumission2();
      }
      else if (colorE == black) {   //�׺��     OK
        cewanhuizhongxin();
        turnleft45(speed1, speed2);
        qufang();
        zuoerfang();
        black_to_mission2();
      }
      else if (colorE == blue) {      //�׺���          OK
        half_qufang();
        zuoerfang();
        fangwanhuizhongxin();
        turnright135(speed1, speed2);
        qumission2();
      }
    }
    else if (colorC == black) {
      cewanhuizhongxin();
      turnright45(speed1, speed2);
      qufang();
      youerfang();
      fangwanhuizhongxin();
      turnright45(speed1, speed2);
      qucese();
      youerqucese();
      colorE = GetColor();
      youercun();
      if (colorE == red) {  //�׺ں�        OK
        cewanhuizhongxin();
        turnleft90(speed1, speed2);
        qufang();
        youerfang();
        fangwanhuizhongxin();
        turnleft135(speed1, speed2);
        qumission2();
      }
      else if (colorE == green) { //�׺���     OK
		  turn180_butui();
        zhixingweitiao(100, speed1, speed2);
        R2after1(1, speed1 - 10, speed2 - 10);
        guomizi1();
        qufang();
        youerfang();
		  fangwanhuizhongxin();
        turnleft45(speed1, speed2);
        qumission2();
      }
      else if (colorE == blue) {  //�׺���      OK
        half_qufang();
        youerfang();
        fangwanhuizhongxin();
        turnright135(speed1, speed2);
        qumission2();
      }
    }
    else if (colorC == blue) {
      cewanhuizhongxin();
      turnright90(speed1, speed2);
      qucese();
      zuoerqucese();
      colorE = GetColor();
      zuoercun();
      half_qufang();
      youerfang();
      if (colorE == red) {  //������             OK
        fangwanhuizhongxin();
        turnleft90(speed1, speed2);
        qufang();
        zuoerfang();
        fangwanhuizhongxin();
        turnleft135(speed1, speed2);
        qumission2();
      }
      else if (colorE == black) { //������     OK
        fangwanhuizhongxin();
        turnleft45(speed1, speed2);
        qufang();
        zuoerfang();
        black_to_mission2();
      }
      else if (colorE == green) { //������          OK
        turn180();
        R1after1(2, speed1, speed2);
        guomizi1();
        qufang();
        zuoerfang();
        fangwanhuizhongxin();
        turnleft45(speed1, speed2);
        qumission2();
      }
    }
  }
  else if (colorA == red) {          //OK
    cewanhuizhongxin();
    turnright90(speed1, speed2);
    qucese();
    youerqucese();
    colorC = GetColor();
    youercun();
	half_qufang();
    zuoerfang();
    fangwanhuizhongxin();
    if (colorC == white) {
      turnleft45(speed1, speed2);
      qufang();
      youerfang();
      fangwanhuizhongxin();
      turnright135(speed1, speed2);
      qucese();
      zuoerqucese();
      colorE = GetColor();
      zuoercun();
      if (colorE == green) {  //�����                  OK
        turn180_butui();
        R2after1(1, speed1, speed2);
        guomizi1();
        qufang();
        zuoerfang();
        fangwanhuizhongxin();
        turnleft45(speed1, speed2);
        qumission2();
      }
      else if (colorE == black) { //��׺�      OK         
        cewanhuizhongxin();
        turnleft45(speed1, speed2);
        qufang();
        zuoerfang();
        black_to_mission2();
      }
      else if (colorE == blue) {  //�����                OK
        half_qufang();
        zuoerfang();
        fangwanhuizhongxin();
        turnright135(speed1, speed2);
        qumission2();
      }
    }
    else if (colorC == green) {
      turnleft90(speed1, speed2);
      qufang();
      youerfang();
      turn180();
      /////////////////////////////////////////////////////
      R2after1(2, speed1, speed2);
      guomizi1();
      qucese();
      zuoerqucese();
      colorE = GetColor();
      zuoercun();
      if (colorE == white) {    //���̰�               OK
        cewanhuizhongxin();
        turnleft135(speed1, speed2);
        qufang();
        zuoerfang();
        fangwanhuizhongxin();
        turnleft90(speed1, speed2);
        qumission2();
      }
      else if (colorE == black) { //���̺�             OK
        cewanhuizhongxin();
        turnleft45(speed1, speed2);
        qufang();
        zuoerfang();
        black_to_mission2();
      }
      else if (colorE == blue) {  //������              OK
        half_qufang();
        zuoerfang();
        fangwanhuizhongxin();
        turnright135(speed1, speed2);
        qumission2();
      }
    }
    else if (colorC == black) {
      turnright45(speed1, speed2);
      qufang();
      youerfang();
      fangwanhuizhongxin();
      turnright45(speed1, speed2);
      qucese();
      zuoerqucese();
      colorE = GetColor();
      zuoercun();
      if (colorE == green) {  //�����               OK
        turn180_butui();
        R2after1(1, speed1, speed2);
        guomizi1();
        qufang();
        zuoerfang();
        fangwanhuizhongxin();
        turnleft45(speed1, speed2);
        qumission2();
      }
      else if (colorE == white) { //��ڰ�           OK
        cewanhuizhongxin();
        turnleft135(speed1, speed2);
        qufang();
        zuoerfang();
        fangwanhuizhongxin();
        turnleft90(speed1, speed2);
        qumission2();
      }
      else if (colorE == blue) {  //�����           OK
        half_qufang();
        zuoerfang();
        fangwanhuizhongxin();
        turnright135(speed1, speed2);
        qumission2();
      }
    }
    else if (colorC == blue) {
      turnright90(speed1, speed2);
      qucese();
      zuoerqucese();
      colorE = GetColor();
      zuoercun();
      half_qufang();
      youerfang();
      if (colorE == green) {  //������               OK
        turn180_butui();
        R2after1(1, speed1, speed2);
        guomizi1();
        qufang();
        zuoerfang();
        fangwanhuizhongxin();
        turnleft45(speed1, speed2);
        qumission2();
      }
      else if (colorE == black) { //������             OK
        fangwanhuizhongxin();
        turnleft45(speed1, speed2);
        qufang();
        zuoerfang();
        black_to_mission2();
      }
      else if (colorE == white) { //������            OK      
        fangwanhuizhongxin();
        turnleft135(speed1, speed2);
        qufang();
        zuoerfang();
        fangwanhuizhongxin();
        turnleft90(speed1, speed2);
        qumission2();
      }
    }
  }/////////////////////////////////////////////////////////////////////
  else if (colorA == black) {        //OK
    cewanhuizhongxin();
    turnright135(speed1, speed2);
    qufang();
    zuoerfang();
    fangwanhuizhongxin();
    turnleft45(speed1, speed2);
    qucese();
    youerqucese();
    colorC = GetColor();
    youercun();
    if (colorC == white) {
      cewanhuizhongxin();
      turnleft45(speed1, speed2);
      qufang();
      youerfang();
      fangwanhuizhongxin();
      turnright135(speed1, speed2);
      qucese();
      zuoerqucese();
      colorE = GetColor();
      zuoercun();
      if (colorE == green) {  //�ڰ���                  OK
        turn180_butui();
        zhongduanzhixingweitiao(100,speed5,speed6);
        R2after1(1, speed1, speed2);
        guomizi1();
        qufang();
        zuoerfang();
        fangwanhuizhongxin();
        turnleft45(speed1, speed2);
        qumission2();
      }
      else if (colorE == red) { //�ڰ׺�                 OK
        cewanhuizhongxin();
        turnleft90(speed1, speed2);
        qufang();
        zuoerfang();
        fangwanhuizhongxin();
        turnleft135(speed1, speed2);
        qumission2();
      }
      else if (colorE == blue) {  //�ڰ���           OK
        half_qufang();
        zuoerfang();
        fangwanhuizhongxin();
        turnright135(speed1, speed2);
        qumission2();
      }
    }
    else if (colorC == red) {
      half_qufang();
      youerfang();
      fangwanhuizhongxin();
      turnright90(speed1, speed2);
      qucese();
      zuoerqucese();
      colorE = GetColor();
      zuoercun();
      if (colorE == green) {  //�ں���            OK
        turn180_butui();
        zhongduanzhixingweitiao(100,speed5,speed6);
        R2after1(1, speed1, speed2);
        guomizi1();
        qufang();
        zuoerfang();
        fangwanhuizhongxin();
        turnleft45(speed1, speed2);
        qumission2();
      }
      else if (colorE == white) {   //�ں��          OK  
        cewanhuizhongxin();
        turnleft135(speed1, speed2);
        qufang();
        zuoerfang();
        fangwanhuizhongxin();
        turnleft90(speed1, speed2);
        qumission2();
      }
      else if (colorE == blue) {    //�ں���             OK
        half_qufang();
        zuoerfang();
        fangwanhuizhongxin();
        turnright135(speed1, speed2);
        qumission2();
      }
    }
    else if (colorC == green) {
      cewanhuizhongxin();
      turnleft90(speed1, speed2);
      qufang();
      youerfang();
      turn180();
      R2after1(2, speed1, speed2);
      guomizi1();
      qucese();
      zuoerqucese();
      colorE = GetColor();
      zuoercun();
      if (colorE == red) {    //���̺�                  OK
        cewanhuizhongxin();
        turnleft90(speed1, speed2);
        qufang();
        zuoerfang();
        fangwanhuizhongxin();
        turnleft135(speed1, speed2);
        qumission2();
      }
      else if (colorE == white) {   //���̰�               OK
        cewanhuizhongxin();
        turnleft135(speed1, speed2);
        qufang();
        zuoerfang();
        fangwanhuizhongxin();
        turnleft90(speed1, speed2);
        qumission2();
      }
      else if (colorE == blue) {    //������                 OK
        half_qufang();
        zuoerfang();
        fangwanhuizhongxin();
        turnright135(speed1, speed2);
        qumission2();
      }
    }
    else if (colorC == blue) {
      cewanhuizhongxin();
      turnright90(speed1, speed2);
      qucese();
      zuoerqucese();
      colorE = GetColor();
      zuoercun();
      half_qufang();
      youerfang();
      if (colorE == green) {    //������               OK
        turn180();
        R2after1(2, speed1, speed2);
        guomizi1();
        qufang();
        zuoerfang();
        fangwanhuizhongxin();
        turnleft45(speed1, speed2);
        qumission2();
      }
      else if (colorE == red) { //������                  OK
        fangwanhuizhongxin();
        turnleft90(speed1, speed2);
        qufang();
        zuoerfang();
        fangwanhuizhongxin();
        turnleft135(speed1, speed2);
        qumission2();
      }
      else if (colorE == white) {   //������             OK
        fangwanhuizhongxin();
        turnleft135(speed1, speed2);
        qufang();
        zuoerfang();
        fangwanhuizhongxin();
        turnleft90(speed1, speed2);
        qumission2();
      }
    }
  }
  else {     //if(colorA==blue)    ֻ����������£�A=zuoer��C=zuoer��E=youer
    turn180_butui();
    zhixingweitiao(100, speed1, speed2);
    R2after1(1, speed1 - 10, speed2 - 10);
    guomizi1();
    qucese();
    youerqucese();
    colorE = GetColor();
    youercun();
    half_qufang();
    zuoerfang();
    if (colorE == green) {   
      turn180();
      R2after1(2, speed1, speed2);
      guomizi1();
      qufang();
      youerfang();
      fangwanhuizhongxin();
      turnright90(speed1, speed2);
      qucese();
      zuoerqucese();
      colorC = GetColor();
      zuoercun();
      if (colorC == white) {    //������
        cewanhuizhongxin();
        turnleft45(speed1, speed2);
        qufang();
        zuoerfang();
        fangwanhuizhongxin();
        turnleft90(speed1, speed2);
        qumission2();
      }
      else if (colorC == red) { //������                OK
        half_qufang();
        zuoerfang();
        fangwanhuizhongxin();
        turnleft135(speed1, speed2);
        qumission2();
      }
      else if (colorC == black) {   //������
        cewanhuizhongxin();
        turnright45(speed1, speed2);
        qufang();
        zuoerfang();
        black_to_mission2();
      }
    }
    else if (colorE == white) {
      fangwanhuizhongxin();
      turnleft90(speed1, speed2);
      qucese();
      zuoerqucese();
      colorC = GetColor();
      zuoercun();
      if (colorC == red) {//�����               OK
        half_qufang();
        zuoerfang();
        fangwanhuizhongxin();
        turnleft45(speed1, speed2);
        qufang();
        youerfang();
        fangwanhuizhongxin();
        turnleft90(speed1, speed2);
        qumission2();
      }
      else if (colorC == green) {//���̰�                    OK
        cewanhuizhongxin();
        turnleft45(speed1, speed2);
        qufang();
        youerfang();
        fangwanhuizhongxin();
        turnleft45(speed1, speed2);
        qufang();
        zuoerfang();
        fangwanhuizhongxin();
        turnleft45(speed1, speed2);
        qumission2();
      }
      else //colorC == black    ���ڰ�
      {
        cewanhuizhongxin();
        turnleft45(speed1, speed2);
        qufang();
        youerfang();
        fangwanhuizhongxin();
        turnright90(speed1, speed2);
        qufang();
        zuoerfang();
        black_to_mission2();
      }
    }
    else if (colorE == red) {
      fangwanhuizhongxin();
      turnleft90(speed1, speed2);
      qucese();
      zuoerqucese();
      colorC = GetColor();
      zuoercun();
      R1Arrive1(speed5, speed6);
      youerfang();
      if (colorC == white) {  //���׺�
        fangwanhuizhongxin();
        turnleft45(speed1, speed2);
        qufang();
        zuoerfang();
        fangwanhuizhongxin();
        turnleft90(speed1, speed2);
        qumission2();
      }
      else if (colorC == green) {   //���̺�             OK  ת������ʱ������
        fangwanhuizhongxin();
        turnleft90(speed1, speed2);
        qufang();
        zuoerfang();
        fangwanhuizhongxin();
        turnleft45(speed1, speed2);
        qumission2();
      }
      else if (colorC == black) {   //���ں�           OK
        fangwanhuizhongxin();
        turnright45(speed1, speed2);
        qufang();
        zuoerfang();
        black_to_mission2();
      }
    }
    else if (colorE == black) {
      fangwanhuizhongxin();
      turnleft45(speed1, speed2);
      qufang();
      youerfang();
      fangwanhuizhongxin();
      turnleft45(speed1, speed2);
      qucese();
      zuoerqucese();
      colorC = GetColor();
      zuoercun();
      if (colorC == white) {    //���׺�                OK
        cewanhuizhongxin();
        turnleft45(speed1, speed2);
        qufang();
        zuoerfang();
        fangwanhuizhongxin();
        turnleft90(speed1, speed2);
        qumission2();
      }
      else if (colorC == red) { //�����                 OK
        half_qufang();
        zuoerfang();
        fangwanhuizhongxin();
        turnleft135(speed1, speed2);
        qumission2();
      }
      else if (colorC == green) { //���̺�                OK
        cewanhuizhongxin();
        turnleft90(speed1, speed2);
        qufang();
        zuoerfang();
        fangwanhuizhongxin();
        turnleft45(speed1, speed2);
        qumission2();
      }
    }
  }
}
//////////////////////////////////////////////////�������Ҫ�ĺ���

void zuoyicun()                                            //���OK
{
  int i = 0;
  ZUO4.write(zuo4_InitPos);
  ZUO2.write(zuo2_InitPos);
  delay(150);
  ZUO3.write(zuo3_InitPos);
  delay(300);
  ZUO1.write(zuo1_properPos - 25);
  delay(200);
  for (i = zuo3_InitPos; i < zuo3_properPos + 25; i++) {
    ZUO3.write(i);
    delay(5);
  }
  for (i = zuo1_properPos; i < zuo1_InitPos + 20; i++) {
    ZUO1.write(i);
    delay(6);
  }
  ZUO3.write(zuo3_properPos + 11);
  ZUO4.write(zuo4_InitPos);
  ZUO2.write(zuo2_InitPos);
}
void zuoyifang()                                        //���OK
{
  int i = 0;
  ZUO4.write(zuo4_InitPos);
  ZUO2.write(zuo2_InitPos);
  for (i = zuo1_InitPos+ 20; i > zuo1_properPos - 60; i--) {
    ZUO1.write(i);
    delay(5);
  }
  delay(200);
  ZUO1.write(zuo1_properPos - 50);
  delay(30);
  ZUO3.write(zuo3_properPos - 8);
  delay(30);
  ZUO1.write(zuo1_properPos - 40);
  delay(30);
  ZUO3.write(zuo3_properPos - 8);
  delay(30);
  ZUO1.write(zuo1_properPos - 30);
  delay(30);
  ZUO3.write(zuo3_properPos - 4);
  delay(30);
  for (i = zuo3_properPos - 20; i > zuo3_InitPos; i--) {
    ZUO3.write(i);
    delay(5);
  }
  ZUO1.write(zuo1_InitPos);
  ZUO4.write(zuo4_InitPos);
  ZUO2.write(zuo2_InitPos);
}
void zuoerna()                             //���OK
{
  int i = 0;
  ZUO2.write(zuo2_InitPos);
  delay(150);
  for (i = zuo4_InitPos; i < zuo4_properPos + 5; i++) {
    ZUO4.write(i);
    delay(2);
  }
}
void youyicun(int n)                             //���OK
{
  if (n == 0)
  {
    YOU4.write(180);
    YOU2.write(0);
    delay(150);
  }
  int i = 0;
  for (i = you1_InitPos; i < you1_properPos +3; i++) {
    YOU1.write(i);
    delay(5);
  }
  delay(150);
  for (i = you3_InitPos; i > you3_properPos ; i--) {
    YOU3.write(i);
    delay(2);
  }
  delay(150);
  for (i = you1_properPos +3 ; i > you1_InitPos - 25; i--) {
    YOU1.write(i);
    delay(5);
  }
   YOU3.write(you3_properPos - 15);
  delay(100);
  YOU4.write(you4_InitPos);
  YOU2.write(you2_InitPos);
}

void youyifang()     ///                    ���OK
{
  int i = 0;
  YOU4.write(180);
  YOU2.write(0);
  YOU3.write(you3_properPos - 20);
  for (i = you1_InitPos - 25; i < you1_properPos + 30; i++) {
    YOU1.write(i);
    delay(5);
  }
  YOU1.write(you1_properPos + 5);
  YOU3.write(you3_InitPos);
  delay(300);
  YOU1.write(you1_InitPos);
  YOU4.write(you4_InitPos);
  YOU2.write(you2_InitPos);
}

void youerna()                         //���OK
{
  int i = 0;
  YOU2.write(you2_InitPos + 10);
  for (i = you4_InitPos; i > you4_properPos - 20; i--)
  {
    YOU4.write(i);
    delay(2);
  }
  YOU2.write(you2_InitPos);
}

void yuantongbao1()     //OK
{
  stop(1);
  YUANTONGSHANGXIA.write(yuantongshangxia_properPos1);
	for (int i = yuantongshangxia_properPos1 ; i > yuantongshangxia_properPos1; i--) {
    YUANTONGSHANGXIA.write(i);
    delay(8);
  }
  YUANTONGKAIBI.write(yuantongkaibi_properPos1);
  delay(200);
  zhongduanzhixingweitiao(450, speed3, speed4);
  stop(100);
  for (int i = yuantongkaibi_properPos1; i > yuantongkaibi_InitPos; i--) {
    YUANTONGKAIBI.write(i);
    delay(3);
  }
  YUANTONGSHANGXIA.write(yuantongshangxia_InitPos);
  delay(100);
  stop(1);
}

void yuantongbao2()
{
	  int i = 0;
	  stop(50);
	  YUANTONGSHANGXIA.write(yuantongshangxia_properPos2);
	  delay(200);
	  
//	  for (i = yuantongkaibi_InitPos; i < 77; i++) {//76
//		YUANTONGKAIBI.write(i);
//		delay(20);
//	  }
//	  delay(200);
	  
	for (i = yuantongshangxia_properPos2; i > taotongzhong; i--) {
		YUANTONGSHANGXIA.write(i);
		delay(15);
	  }
	  delay(200);
	  YOU1.write(10);
//	  zhongduanzhixingweitiao1(350,speed3+10,speed4+10);
	  stop(1);
	   for (i = yuantongkaibi_InitPos; i < 76; i++) {//76
		YUANTONGKAIBI.write(i);
		delay(15);
	  }
	  delay(100);
	  zhongduanhoutuiweitiao(15,speed3,speed4);
	  stop(1);
	  for (i = 76; i < yuantongkaibi_properPos2 + 10; i++) {//76
		YUANTONGKAIBI.write(i);
		delay(15);
	  }
	  delay(100);
	  for (i = taotongzhong; i > yuantongshangxia_properPos1; i--) {
		YUANTONGSHANGXIA.write(i);
		delay(15);
	  }
	  delay(100);
	  YUANTONGKAIBI.write(yuantongkaibi_InitPos);
	  YOU1.write(you1_InitPos - 25);
	  delay(300);
	  YUANTONGSHANGXIA.write(yuantongshangxia_InitPos);
	  delay(100);
	  stop(1);
}

void yuantongfang1()//    �ȵ��ף�ȫ�������ˣ���Ͳ�ָ���ʼ״̬            ����û��飬��Ͳ����Ҳû�У�һ���������������������ڷ�D  
{
  int i = 0;
	zhongduanhoutuiweitiao1(135,speed3,speed4);
	stop(100);
  YUANTONGSHANGXIA.write(yuantongshangxia_properPos1 - 10);//����
  delay(200);
  YOU1.write(10);
	stop(100);
  retreat(100,0);
  delay(130);
  stop(100);
  for (i = yuantongkaibi_InitPos; i < yuantongkaibi_properPos2; i++) {
    YUANTONGKAIBI.write(i);
    delay(25);
  }
  
  for (i = yuantongkaibi_properPos2; i < yuantongkaibi_properPos1; i++) {//������ȫ��
    YUANTONGKAIBI.write(i);
    delay(5);
  }
  delay(200);
  retreat(speed3,speed4);
  delay(150);
  zhongduanhoutuiweitiao(onecircle - 450, speed5, speed6);//����
  YUANTONGSHANGXIA.write(yuantongshangxia_InitPos);
  YUANTONGKAIBI.write(yuantongkaibi_InitPos);
  YOU1.write(you1_InitPos);
  stop(1);
}

void yuantongfang2()//�ȵ��ף��뿪�����ϵ�һ�룬�ٹ�����Ͳ��̧�ߵ�ͷ�����ˣ���Ͳ�ָ���ʼ��     ����û��飬��Ͳ���У���������飬�����ڷ�B
{
  stop(1);
	zhongduanhoutuiweitiao1(105,speed3,speed4);
	stop(100);
	delay(250);
  int i = 0;
  YUANTONGSHANGXIA.write(yuantongshangxia_properPos1 - 10);//����
	stop(100);
  retreat(100,0);
  delay(120);
  stop(500);
  for (i = yuantongkaibi_InitPos; i < yuantongkaibi_properPos2 - 20 ; i++) {//�뿪
    YUANTONGKAIBI.write(i);
    delay(30);
  }
  delay(200);
  zhongduanhoutuiweitiao1(10,speed3,speed4);
  stop(1);
  for (i = yuantongshangxia_properPos1- 10; i < yuantongshangxia_InitPos - 13; i++) {//���ϵ�ͷ
    YUANTONGSHANGXIA.write(i);
    delay(20);
  }
  for (i = yuantongkaibi_properPos2 - 20; i > yuantongkaibi_InitPos; i--) {//������Ͳ
    YUANTONGKAIBI.write(i);
    delay(20);
  }
  for (i = yuantongshangxia_InitPos-13; i < yuantongshangxia_InitPos; i++) {//���ϵ�ͷ
    YUANTONGSHANGXIA.write(i);
    delay(10);
  }
  zhongduanhoutuiweitiao(onecircle - 200, speed5, speed6);//����
  YUANTONGSHANGXIA.write(yuantongshangxia_InitPos);
  YUANTONGKAIBI.write(yuantongkaibi_InitPos);
  stop(1);
}

void yuantongfang3()//�½���һ�룬��Ͳ�뿪�����½����ף���Ͳ��£�̶���飬������ȫ�򿪣�����             ������һ����飬��Ͳ����û�У�һ���������������ڷ�A,��C,��E
{
  stop(100);
  int i = 0;
	zhongduanzhixingweitiao2(350,speed3,speed4);
	zhongduanhoutuiweitiao2(118,speed3,speed4);//125
	stop(10);
	  YUANTONGSHANGXIA.write(yuantongshangxia_properPos2);
	  delay(200);
	for (i = yuantongshangxia_properPos2; i > taotongzhong; i--) {
		YUANTONGSHANGXIA.write(i);
		delay(15);
	  }
	  delay(200);
	  YOU1.write(10);
	  stop(1);
	   for (i = yuantongkaibi_InitPos; i < 76; i++) {//76
		YUANTONGKAIBI.write(i);
		delay(15);
	  }
	  delay(100);
	  zhongduanhoutuiweitiao2(15,speed3,speed4);
	  stop(1);
	  for (i = 76; i < yuantongkaibi_properPos2 + 10; i++) {//76
		YUANTONGKAIBI.write(i);
		delay(15);
	  }
	  delay(100);
	  zhongduanzhixingweitiao2(10,speed3,speed4);
	  stop(200);
	  for (i = taotongzhong; i > yuantongshangxia_properPos1; i--) {
		YUANTONGSHANGXIA.write(i);
		delay(15);
	  }
	  delay(100);
	  YUANTONGKAIBI.write(yuantongkaibi_InitPos);
	  R1Arrive2(speed3,speed4);
	  zhongduanhoutuiweitiao1(10,speed3,speed4);
	  delay(300);
	  retreat(100,0);
	  delay(120);
	  stop(300);
	  YOU1.write(10);
	  for (i = yuantongkaibi_InitPos; i < yuantongkaibi_properPos1- 20; i++) {//��Ͳȫ��
    YUANTONGKAIBI.write(i);
    delay(10);
  }
  YUANTONGKAIBI.write(yuantongkaibi_properPos1+20);
  for(unsigned long time = millis(); millis() - time < 150;)retreat1(speed3,speed4);
    zhongduanhoutuiweitiao(150,speed3,speed4);
    YUANTONGSHANGXIA.write(yuantongshangxia_InitPos);
    ZUO1.write(zuo1_InitPos);
  stop(1);
}

void yuantongfanghei()//�½���һ�룬��Ͳ�뿪�����½����ף���Ͳ��£�̶���飬������ȫ�򿪣�����             ������һ����飬��Ͳ����û�У�һ���������������ڷ�A,��C,��E
{
  stop(100);
  int i = 0;
	zhongduanzhixingweitiao2(350,speed3,speed4);
	zhongduanhoutuiweitiao2(130,speed3,speed4);
	stop(10);
	  YUANTONGSHANGXIA.write(yuantongshangxia_properPos2);
	  delay(200);
	
	stop(300);
	for (i = yuantongshangxia_properPos2; i > taotongzhong +2; i--) {
		YUANTONGSHANGXIA.write(i);
		delay(15);
	  }
	  zhongduanzhixingweitiao2(300,speed3,speed4);
	  stop(1);
	  delay(200);
	  YOU1.write(10);
	  stop(1);
	   for (i = yuantongkaibi_InitPos; i < 76; i++) {//76
		YUANTONGKAIBI.write(i);
		delay(15);
	  }
	  delay(100);
	  zhongduanhoutuiweitiao2(12,speed3,speed4);
	  stop(1);
	  for (i = 76; i < yuantongkaibi_properPos2 + 10; i++) {//76
		YUANTONGKAIBI.write(i);
		delay(15);
	  }
	  delay(100);
	  for (i = taotongzhong; i > yuantongshangxia_properPos1; i--) {
		YUANTONGSHANGXIA.write(i);
		delay(10);
	  }
	  delay(100);
	  YUANTONGKAIBI.write(yuantongkaibi_InitPos);
	  R1Arrive2(speed3,speed4);
	  zhongduanhoutuiweitiao1(10,speed3,speed4);
	  delay(300);
	  retreat(100,0);
	  delay(120);
	  stop(300);
	  YOU1.write(10);
	  for (i = yuantongkaibi_InitPos; i < yuantongkaibi_properPos1- 20; i++) {//��Ͳȫ��
    YUANTONGKAIBI.write(i);
    delay(10);
  }
  YUANTONGKAIBI.write(yuantongkaibi_properPos1+20);
  for(unsigned long time = millis(); millis() - time < 150;)retreat1(speed3,speed4);
    zhongduanhoutuiweitiao(150,speed3,speed4);
    YUANTONGSHANGXIA.write(yuantongshangxia_InitPos);
    ZUO1.write(zuo1_InitPos);
  stop(1);
}

void baoE()//����AB��E������Ͳ��
{
  zuoyifang();
  zuoerna();
  youyifang();
  youerna();
  youerfang();
  zhongduanhoutuiweitiao(420, speed3, speed4);
  YOU1.write(5);
  yuantongbao1();
  zuoerfang();
  zhongduanhoutuiweitiao(bao2houtui_pulse, speed3, speed4);
  yuantongbao2();
  zhongduanhoutuiweitiao(300,speed5,speed6);
  R2after2(1,speed5,speed6);
  guomizi4();
  stop(100);
}

void naAB_houtui()
{
  int i = 0;
  ZUO2.write(zuo2_InitPos - 40);
  YOU2.write(you2_InitPos + 40);
  for (i = zuo4_InitPos; i < zuo4_properPos; i++) {
    ZUO4.write(i);
    delay(5);
  }
  for (i = you4_InitPos; i > you4_properPos - 15; i--) {
    YOU4.write(i);
    delay(5);
  }
  zhongduanhoutuiweitiao(50, speed3, speed4);
  stop(1);
  for (i = zuo2_InitPos - 40; i < zuo2_InitPos + 15; i++)
  {
    ZUO2.write(i);
    delay(6);
  }
  for (i = zuo4_properPos; i < zuo4_properPos + 10; i++) {
    ZUO4.write(i);
    delay(1);
  }
  for (i = you2_InitPos + 40; i > you2_InitPos - 15; i--)
  {
    YOU2.write(i);
    delay(6);
  }
  YOU4.write(you4_properPos - 15);
  zhongduanhoutuiweitiao(250, speed3, speed4);
  stop(1);
  delay(100);
}

void ceBcunB_zhunbeifangA()
{
  int i = 0;
	ZUO4.write(zuo4_properPos);
  for (i = zuo2_InitPos; i > zuo2_properPos - 30; i--) {
    ZUO2.write(i);
    delay(5);
  }
  colorB = GetColor();
  for (i = zuo2_properPos - 30; i < zuo2_InitPos; i++)
  {
    ZUO2.write(i);
    delay(5);
  }
  for (i = zuo4_properPos; i < zuo4_properPos + 10; i++) {
    ZUO4.write(i);
    delay(1);
  }
  delay(200);
  zuoyicun();
  youerfang();
}

void baowuqianzhunbei()
{
	YOU1.write(10);
  YOU4.write(you4_InitPos);
  delay(250);
  YOU2.write(you2_InitPos);
  ZUO4.write(zuo4_InitPos);
  delay(250);
  ZUO2.write(zuo2_InitPos);
  stop(200);
}

void cunC_cunE()
{
  zuoerna();
  YOU2.write(you2_properPos);
  delay(100);
  YOU4.write(you4_properPos);
  delay(300);
  YOU2.write(you2_properPos + 55);
  delay(200);
  youyicun(1);
  YOU4.write(you4_properPos);
  youercun();
}

void CDrenglubian()
{
  int i = 0;
  zhongduanhoutuiweitiao(2 * onecircle - 400, speed5, speed6);
  R2Arrive2(speed3, speed4);
  for (i = zuo4_properPos; i > zuo4_InitPos; i--) {
    ZUO4.write(i);
    delay(5);
  }
  for (i = you4_properPos; i < you4_InitPos; i++) {
    YOU4.write(i);
    delay(5);
  } 
  ZUO2.write(zuo2_InitPos );
  YOU2.write(you2_InitPos);
}

void mission2_step1()
//��һ�׶ν�ABCDEλ��ȫ���ƶ����˺���������A����Ͳ���1��B���ҹ�1��E��C��D����·��
//������������2��4����2��4�Ź�ȫ���ع��ʼλ�ã�����1��3�Ź���Ϊ������飬���ڵ�λ��
{
  zhongduanzhixingweitiao1(380, speed3, speed4);//380
  stop(100);
  naAB_houtui();
  ////////////////////////////��B������1�ݴ�
  ceBcunB_zhunbeifangA();
  baowuqianzhunbei();
  zhongduanhoutuiweitiao1(400, speed3, speed4);
  yuantongbao1();
	for(long time = millis();millis() - time < 2000;)goStraight(speed3,speed4);
  //zhixingweitiao(2500, speed3, speed4);
  stop(1);
  cunC_cunE(); 
  CDrenglubian();
  //////////////////////////////////////������
	houtuiweitiao(400,speed3,speed4);
  R2after2(1, speed5, speed6);
  guomizi4();
  stop(300);
}

void baoA_baoB()
{
  zuoerfang();
  zuoyifang();
  zuoerna();
  zhongduanhoutuiweitiao1(bao2houtui_pulse, speed3, speed4);
  yuantongbao2();
  zuoerfang();
  zhongduanhoutuiweitiao1(bao2houtui_pulse, speed3, speed4);
  yuantongbao2();
  youerfang();
	zhongduanzhixingweitiao1(200,speed3,speed4);
	stop(1);
  zhongduanhoutuiweitiao1(bao2houtui_pulse, speed3, speed4);
  yuantongbao2();
  zhongduanzhixingweitiao1(100, speed5, speed6);
}

void cunC_cunE_step2()
{
	youerna();
  zuoyicun();
  zuoerqucese();
  zuoercun();
  //zuoerna();
}

void baoC()
{
  stop(1);
  youerfang();
  zhongduanhoutuiweitiao1(350, speed3, speed4);
	YOU1.write(5);
  yuantongbao1();
  zuoerfang();
	zhongduanhoutuiweitiao1(bao2houtui_pulse,speed3,speed4);
	stop(1);
  yuantongbao2();
  zhongduanhoutuiweitiao1(200, speed3, speed4);
  R2after2(1,speed1,speed2);
  guomizi4();
  stop(100);
}

void mission2_step2()//�������BΪ�ף�����ת180����������ǰת
{
  guomizi1();
  zhongduanzhixingweitiao(2*onecircle - 100,speed1,speed2);
	digitalWrite(LED,HIGH);
  L1Arrive1(speed5, speed6);
	digitalWrite(LED,LOW);
  zhongduanzhixingweitiao1(350, speed5, speed6);
  stop(50);
  naAB_houtui();
	//zhongduanhoutuiweitiao(200,speed5,speed6);
	stop(50);
  baoA_baoB();
  for(long time = millis();millis() - time < 1300;)goStraight(speed5,speed6);
  stop(1);
  cunC_cunE_step2();
  CDrenglubian();
  //////////////////////////////////////������
  houtuiweitiao(300, speed5, speed6);
  R2after2(1, speed5, speed6);
  guomizi4();
  stop(300);
}

void baoD_step1()//�ȷ�D,�����C���ұ���D
{
  //zhongduanzhixingweitiao(onecircle, speed5 - 10, speed6 - 10);
  youerna();
  zuoyicun();
  youerfang();
  YOU1.write(5);
  zhongduanhoutuiweitiao(350, speed3, speed4);
  yuantongbao1();
  YOU1.write(you1_InitPos - 25);
  R2after2(2, speed5, speed6);
  guomizi4();
  stop(150);
}

void baoD_step2()//�ȷ�D,�����D���ұ���C
{
  //zhongduanzhixingweitiao(onecircle + 80, speed5 - 10, speed6 - 10);
  stop(100);
  youerna();
  zuoerna();
  zuoerfang();
  YOU1.write(10);
  zhongduanhoutuiweitiao(bao2houtui_pulse, speed3, speed4);
  yuantongbao2();
  zuoyifang();
  zuoerna();
  R2after2(2, speed1, speed2);
  guomizi4();
  stop(100);
}//����Dȫ����Ͳ��Cȫ�����Ҷ��Ź�

void fangwanhuizhongxin1()
{
  R2after2(1, speed1, speed2);
  R2after2(1, speed5, speed6);
  guomizi4();
  stop(350);
}

void fangA()
{
	if(colorA == red || colorC == red || colorE == red )
	{
		zhixingweitiao(300,speed3,speed4);
		guomizi1();
		zhongduanzhixingweitiao(3*onecircle - 400,speed5,speed6);
		digitalWrite(LED,HIGH);
		L1Arrive1(speed3,speed4);
		digitalWrite(LED,LOW);
	}
    else
	{
		qufang();
	}
	stop(400);
	
		yuantongfang3();
  R2Arrive2(speed5, speed6);
}

void fangB()
{
  if(colorB == red )
	{
		zhixingweitiao(300,speed3,speed4);
		guomizi1();
		zhongduanzhixingweitiao(3*onecircle - 400,speed5,speed6);
		digitalWrite(LED,HIGH);
		L1Arrive1(speed3,speed4);
		digitalWrite(LED,LOW);
	}
    else
	{
		qufang();
	}
	stop(400);

		yuantongfang2();

  fangwanhuizhongxin1();
}

void fangC()
{
  fangA();
}

void fangD()
{
  if(colorD == red)
	{
		zhixingweitiao(300,speed3,speed4);
		guomizi1();
		zhongduanzhixingweitiao(3*onecircle - 400,speed5,speed6);
		digitalWrite(LED,HIGH);
		L1Arrive1(speed3,speed4);
		digitalWrite(LED,LOW);
	}
    else
	{
		qufang();
	}
	stop(400);

		yuantongfang1();
  R2Arrive2(speed1 - 10, speed2 - 10);
}

void fangE()
{
  if(colorA == red || colorC == red || colorE == red )
	{
		zhixingweitiao(300,speed3,speed4);
		guomizi1();
		zhongduanzhixingweitiao(3*onecircle - 400,speed5,speed6);
		digitalWrite(LED,HIGH);
		L1Arrive1(speed3,speed4);
		digitalWrite(LED,LOW);
	}
    else
	{
		qufang();
	}
	stop(400);
		yuantongfang3();
  R2after2(1,speed5, speed6);
  cewanhuizhongxin();
}

void fangE_black()
{ 
  fangA();
  turn180_butui();
	zhongduanzhixingweitiao(200,speed1,speed2);
  R2after1(1, speed1, speed2);
  guomizi3();
	stop(100);
}

void blue_huijia()
{
	fangC();
	YUANTONGSHANGXIA.write(yuantongshangxia_InitPos);
	YUANTONGKAIBI.write(yuantongkaibi_InitPos);
	MotorAPos = 0 ;
	MotorBPos = 0 ;
	attachInterrupt(digitalPinToInterrupt(MotorAcountA), doMotorA, CHANGE);
    attachInterrupt(digitalPinToInterrupt(MotorBcountA), doMotorB, CHANGE);
	while(MotorAPos > -pulse_90L + 55&& MotorBPos < pulse_90L - 55)
	{
		laoshizuozhuan(speed1,speed2);
	}
	youzhuan(150,150);
	delay(20);
    zhongduanhoutuiweitiao2( 4*onecircle,150,150);
	goStraight(255,255);
	delay(50);
	stop(1);
}

void green_huijia()
{
	fangC();
	YUANTONGSHANGXIA.write(yuantongshangxia_InitPos);
	YUANTONGKAIBI.write(yuantongkaibi_InitPos);
	MotorAPos = 0 ;
	MotorBPos = 0 ;
	attachInterrupt(digitalPinToInterrupt(MotorAcountA), doMotorA, CHANGE);
    attachInterrupt(digitalPinToInterrupt(MotorBcountA), doMotorB, CHANGE);
	while(MotorAPos < pulse_45R + 115&& MotorBPos > -pulse_45R - 115)
	{
		youzhuan(speed1,speed2);
	}
	zuozhuan(150,150);
	delay(20);
    zhongduanhoutuiweitiao2( 4*onecircle,150,150);
	goStraight(255,255);
	delay(50);
	stop(1);
}

void black_huijia()
{
	fangC();
	YUANTONGSHANGXIA.write(yuantongshangxia_InitPos);
	YUANTONGKAIBI.write(yuantongkaibi_InitPos);
	MotorAPos = 0 ;
	MotorBPos = 0 ;
	attachInterrupt(digitalPinToInterrupt(MotorAcountA), doMotorA, CHANGE);
    attachInterrupt(digitalPinToInterrupt(MotorBcountA), doMotorB, CHANGE);
	while(MotorAPos > -pulse_45L +40&& MotorBPos < pulse_45L - 40)
	{
		laoshizuozhuan(speed1,speed2);
	}
	youzhuan(150,150);
	delay(20);
	stop(200);
	zhongduanhoutuiweitiao2( onecircle,speed1,speed2);
    zhongduanhoutuiweitiao2( 4*onecircle - 110,150,150);
	goStraight(255,255);
	delay(50);
	stop(1);
}

void white_huijia()
{
	fangC();
	YUANTONGSHANGXIA.write(yuantongshangxia_InitPos);
	YUANTONGKAIBI.write(yuantongkaibi_InitPos);
	MotorAPos = 0 ;
	MotorBPos = 0 ;
	attachInterrupt(digitalPinToInterrupt(MotorAcountA), doMotorA, CHANGE);
    attachInterrupt(digitalPinToInterrupt(MotorBcountA), doMotorB, CHANGE);
	while(MotorAPos < pulse_45R - 100&& MotorBPos > -pulse_45R + 100)
	{
		laoshiyouzhuan(speed1,speed2);
	}
	zuozhuan(150,150);
	delay(20);
	stop(200);
	zhongduanhoutuiweitiao2( onecircle,speed1,speed2);
    zhongduanhoutuiweitiao2( 4*onecircle - 110,150,150);
	goStraight(255,255);
	delay(50);
	stop(1);
}

void red_huijia()
{
	fangC();
	zhongduanhoutuiweitiao(300,speed5,speed6);
	zhongduanhoutuiweitiao(5*onecircle,150,150);
	goStraight(200,200);
	delay(20);
	stop(1);
}

void mission2()
{
  mission2_step1();
  turnleft90(speed1, speed2);
  mission2_step2();
  if (colorB == white)
  {
    turn180_butui();
    fangB();
    if (colorA == green)
    {
      turnleft45(speed1, speed2);
      fangA();
      baoE();
      if (colorE == red)
      {
        turnright90(speed1, speed2);
        fangE();
        turnleft135(speed1, speed2);
      }
      else if (colorE == black)
      {
        turnright135(speed1, speed2);
        fangE_black();
      }
      else if (colorE == blue)
      {
        turn180_butui();
        fangE();
        turnright135(speed1,speed2);
      }
    }
    else if (colorA == red)
    {
      turnright45(speed1, speed2);
      fangA();
      baoE();
      if (colorE == green)
      {
        turnleft90(speed1, speed2); 
        fangE();
        turnleft45(speed1, speed2);
      }
      else if (colorE == black)
      {
        turnright45(speed1, speed2);
        fangE_black();
      }
      else if (colorE == blue)
      {
        turnright90(speed1, speed2);
        fangE();
        turnright135(speed1, speed2);
      }
    }
    else if (colorA == black)
    {
      turnright90(speed1,speed2);
		fangA();
		baoE();
		if(colorE == red)
		{
			turnleft45(speed1,speed2);
			fangE();
			turnleft135(speed1,speed2);
		}
		else if(colorE == green)
		{
			turnleft135(speed1,speed2);
			fangE();
			turnleft45(speed1,speed2);
		}
		else if(colorE == blue)
		{
			turnright45(speed1,speed2);
			fangE();
			turnright135(speed1,speed2);
		}
    }
	else if(colorA == blue)
	{
		turnright135(speed1,speed2);
		fangA();
		baoE();
		if(colorE == green)
		{
			turn180_butui();
			fangE();
			turnleft45(speed1,speed2);
		}
		else if(colorE == red)
		{
			turnleft90(speed1,speed2);
			fangE();
			turnleft135(speed1,speed2);
		}
		else if(colorE == black)
		{
			turnleft45(speed1,speed2);
			fangE_black();
		}
	}
  }
  else if (colorB == blue)
  {
    turnleft45(speed1, speed2);
    fangB();
    if (colorA == black)
    {
      turnleft45(speed1, speed2);
		fangA();
      baoE();
      if (colorE == red)
      {
        turnleft45(speed1, speed2);
		  fangE();
        turnleft135(speed1, speed2);
      }
	  else if (colorE == white)
	  {
		  turnleft90(speed1,speed2);
		  fangE();
		  turnleft90(speed1,speed2);
	  }
	  else if (colorE == green)
	  {
		  turnleft135(speed1,speed2);
		  fangE();
		  turnleft45(speed1,speed2);
	  }
    }
	else if(colorA == white)
	{
		turnleft135(speed1,speed2);
		fangA();
		baoE();
		if(colorE == black)
		{
			turnright90(speed1,speed2);
			fangE_black();
		}
		else if(colorE == red)
		{
			turnright45(speed1,speed2);
			fangE();
			turnleft135(speed1,speed2);
		}
		else if(colorE == green)
		{
			turnleft45(speed1,speed2);
			fangE();
			turnleft45(speed1,speed2);
		}
	}
	else if(colorA == red)
	{
		turnleft90(speed1,speed2);
		fangA();
		baoE();
		if(colorE == white)
		{
			turnleft45(speed1,speed2);
			fangE();
			turnleft90(speed1,speed2);
		}
		else if(colorE == green)
		{
			turnleft90(speed1,speed2);
			fangE();
			turnleft45(speed1,speed2);
		}
		else if(colorE == black)
		{
			turnright45(speed1,speed2);
			fangE_black();
		}
	}
	else if(colorA == green)
	{
		turn180_butui();
		fangA();
		baoE();
		if(colorE == white)
		{
			turnright45(speed1,speed2);
			fangE();
			turnleft90(speed1,speed2);
		}
		if(colorE == red)
		{
			turnright90(speed1,speed2);
			fangE();
			turnleft135(speed1,speed2);
		}
		if(colorE == black)
		{
			turnright135(speed1,speed2);
			fangE_black();
		}
	}
  }
  else if(colorB == red)
  {
	  turnleft135(speed1,speed2);
	  fangB();
	  if(colorA == white)
	  {
		  turnleft45(speed1,speed2);
		  fangA();
		  baoE();
		  if(colorE== blue)
		  {
			  turnright135(speed1,speed2);
			  fangE();
			  turnright135(speed1,speed2);
		  }
		  else if(colorE== green)
		  {
			  turnleft45(speed1,speed2);
			  fangE();
			  turnleft45(speed1,speed2);
		  }
		  else if(colorE== black)
		  {
			  turnright90(speed1,speed2);
			  fangE_black();
		  }
	  }
	  else if(colorA == black)
	  {
		  turnright45(speed1,speed2);
		  fangA();
		  baoE();
		  if(colorE == white)
		  {
			  turnleft90(speed1,speed2);
			  fangE();
			  turnleft90(speed1,speed2);
		  }
		  else if(colorE == green )
		  {
			  turnleft135(speed1,speed2);
			  fangE();
			  turnleft45(speed1,speed2);
		  }
		  else if(colorE == blue )
		  {
			  turnright45(speed1,speed2);
			  fangE();
			  turnright135(speed1,speed2);
		  }
	  }
	  else if(colorA == blue)
	  {
		  turnright90(speed1,speed2);
		  fangA();
		  baoE();
		  if(colorE == white)
		  {
			  turnleft135(speed1,speed2);
			  fangE();
			  turnleft90(speed1,speed2);
		  }
		  else if(colorE == green)
		  {
			  turn180_butui();
			  fangE();
			  turnleft45(speed1,speed2);
		  }
		  else if(colorE == black)
		  {
			  turnleft45(speed1,speed2);
			  fangE_black();
		  }
	  }
	  else if(colorA == green)
	  {
		  turnleft90(speed1,speed2);
		  fangA();
		  baoE();
		  if(colorE == white)
		  {
			  turnright45(speed1,speed2);
			  fangE();
			  turnleft90(speed1,speed2);
		  }
		  else if(colorE == blue)
		  {
			  turn180_butui();
			  fangE_black();
			  turnleft45(speed1,speed2);
		  }
		  else if(colorE == black)
		  {
			  turnright135(speed1,speed2);
			  fangE_black();
		  }
	  }
  }
  else if(colorB == green)
  {
	  turnright135(speed1,speed2);
	  fangB();
	  if(colorA == white)
	  {
		  turnright45(speed1,speed2);
		  fangA();
		  baoE();
		  if(colorE == red)
		  {
			  turnright45(speed1,speed2);
			  fangE();
			  turnleft135(speed1,speed2);
		  }
		  else if(colorE == black)
		  {
			  turnright90(speed1,speed2);
			  fangE_black();
		  }
		  if(colorE == blue)
		  {
			  turnright135(speed1,speed2);
			  fangE();
			  turnright135(speed1,speed2);
		  }
	  }
	  else if(colorA == red)
	  {
		  turnright90(speed1,speed2);
		  fangA();
		  baoE();
		  if(colorE == white)
		  {
			  turnleft45(speed1,speed2);
			  fangE();
			  turnleft90(speed1,speed2);
		  }
		  else if(colorE == black)
		  {
			  turnright45(speed1,speed2);
			  fangE();
			  turn180_butui();
		  }
		  if(colorE == blue)
		  {
			  turnright90(speed1,speed2);
			  fangE_black();
			  turnleft45(speed1,speed2);
		  }
	  }
	  else if(colorA == blue)
	  {
		  turn180_butui();
		  fangA();
		  baoE();
		  if(colorE == black)
		  {
			  turnleft45(speed1,speed2);
			  fangE_black();
		  }
		  else if(colorE == red)
		  {
			  turnleft90(speed1,speed2);
			  fangE();
			  turnleft135(speed1,speed2);
		  }
		  if(colorE == white)
		  {
			  turnleft135(speed1,speed2);
			  fangE();
			  turnleft90(speed1,speed2);
		  }
	  }
	  else if(colorA == black)
	  {
		  turnright135(speed1,speed2);
		  fangA();
		  baoE();
		  if(colorE == white)
		  {
			  turnleft90(speed1,speed2);
			  fangE();
			  turnleft90(speed1,speed2);
		  }
		  else if(colorE == blue)
		  {
			  turnright45(speed1,speed2);
			  fangE();
			  turnright135(speed1,speed2);
		  }
		  if(colorE == red)
		  {
			  turnleft45(speed1,speed2);
			  fangE();
			  turnleft135(speed1,speed2);
		  }
	  }
  }
  else if(colorB == black)
  {
	  turnleft90(speed1,speed2);
	  fangB();
	  if(colorA == white)
	  {
		  turnleft90(speed1,speed2);
		  fangA();
		  baoE();
		  if(colorE == red)
		  {
			  turnright45(speed1,speed2);
			  fangE();
			  turnleft135(speed1,speed2);
		  }
		  else if(colorE == blue)
		  {
			  turnright135(speed1,speed2);
			  fangE();
			  turnright135(speed1,speed2);
		  }
		  else if(colorE == green)
		  {
			  turnleft45(speed1,speed2);
			  fangE();
			  turnleft45(speed1,speed2);
		  }
	  }
	  else if(colorA == red)
	  {
		  turnleft45(speed1,speed2);
		  fangA();
		  baoE();
		  if(colorE == white)
		  {
			  turnleft45(speed1,speed2);
			  fangE();
			  turnleft90(speed1,speed2);
		  }
		  else if(colorE == blue)
		  {
			  turnright90(speed1,speed2);
			  fangE();
			  turnright135(speed1,speed2);
		  }
		  else if(colorE == green)
		  {
			  turnleft90(speed1,speed2);
			  fangE();
			  turnleft45(speed1,speed2);
		  }
	  }
	  else if(colorA == green)
	  {
		  turnleft135(speed1,speed2);
		  fangA();
		  baoE();
		  if(colorE == red)
		  {
			  turnright90(speed1,speed2);
			  fangE();
			  turnleft135(speed1,speed2);
		  }
		  else if(colorE == white)
		  {
			  turnright45(speed1,speed2);
			  fangE();
			  turnleft90(speed1,speed2);
		  }
		  else if(colorE == blue)
		  {
			  turn180_butui();
			  fangE();
			  turnright135(speed1,speed2);
		  }
	  }
	  else if(colorA == blue)
	  {
		  turnright45(speed1,speed2);
		  fangA();
		  baoE();
		  if(colorE == green)
		  {
			  turn180_butui();
			  fangE();
			  turnleft45(speed1,speed2);
		  }
		  else if(colorE == red)
		  {
			  turnleft90(speed1,speed2);
			  fangE();
			  turnleft135(speed1,speed2);
		  }
		  else if(colorE == white)
		  {
			  turnleft135(speed1,speed2);
			  fangE();
			  turnleft90(speed1,speed2);
		  }
	  }
  }
  colorD = 10 - colorA - colorB - colorC - colorE;
  qumission2();
  baoD_step1();
  turnleft90(speed1, speed2);
  qumission2();
  baoD_step2();
  stop(300);
  if (colorD == white)
  {
    turn180_butui();
    fangD();
    baoC();
    if (colorC == green)
    {
      turnleft45(speed1, speed2);
      green_huijia();
    }
	else if(colorC == black)
	{
		turnright90(speed1,speed2);
		black_huijia();
	}
	else if(colorC == red)
	{
		turnright45(speed1,speed2);
		red_huijia();
	}
	else if(colorC == blue)
	{
		turnright135(speed1,speed2);
		blue_huijia();
	}
  }
  else if(colorD == black)
  {
	  turnleft90(speed1,speed2);
      fangD();
      baoC();
	  if(colorC == white)
	  {
		  turnleft90(speed1,speed2);
		  white_huijia();
	  }
	  else if(colorC == green)
	  {
		  turnleft135(speed1,speed2);
		  green_huijia();
	  }
	  else if(colorC == blue)
	  {
		  turnright45(speed1,speed2);
		  blue_huijia();
	  }
	  else if(colorC == red)
	  {
		  turnleft45(speed1,speed2);
		  red_huijia();
	  }
  }
  else if(colorD == red)
  {
	  turnleft135(speed1,speed2);
	  fangD();
	  baoC();
	  if(colorC == white)
	  {
		  turnleft45(speed1,speed2);
		  white_huijia();
	  }
	  else if(colorC == black)
	  {
		  turnright45(speed1,speed2);
		  black_huijia();
	  }
	  else if(colorC == green)
	  {
		  turnleft90(speed1,speed2);
		  green_huijia();
	  }
	  else if(colorC == blue)
	  {
		  turnright90(speed1,speed2);
		  blue_huijia();
	  }
  }
  else if(colorD == green)
  {
	  turnright135(speed1,speed2);
	  fangD();
	  baoC();
	  if(colorC == blue)
	  {
		  turn180_butui();
		  blue_huijia();
	  }
	  else if(colorC == white)
	  {
		  turnright45(speed1,speed2);
		  white_huijia();
	  }
	  else if(colorC == red)
	  {
		  turnright90(speed1,speed2);
		  red_huijia();
	  }
	  else if(colorC == black)
	  {
		  turnright135(speed1,speed2);
		  black_huijia();
	  }
  }
  else if(colorD == blue)
  {
	  turnleft45(speed1,speed2);
	  fangD();
	  baoC();
	  if(colorC == black)
	  {
		  turnleft45(speed1,speed2);
		  blue_huijia();
	  }
	  else if(colorC == white)
	  {
		  turnleft135(speed1,speed2);
		  white_huijia();
	  }
	  else if(colorC == red)
	  {
		  turnleft90(speed1,speed2);
		  red_huijia();
	  }
	  else if(colorC == green)
	  {
		  turn180_butui();
		  green_huijia();
	  }
  }
}

void huijia()
{
  guomizi1();
  zhixingweitiao(200, speed1, speed2);
  R2after1(2, speed1, speed2);
  R2Arrive1(speed3, speed4);

}
// the setup routine runs once when you press reset:
void setup() {
  // put your setup code here, to run once:
  TSC_Init();//��ɫ������
  pinMode(MotorApin1, OUTPUT);//���
  pinMode(MotorApin2, OUTPUT);
  pinMode(MotorApwm, OUTPUT);
  pinMode(MotorBpin1, OUTPUT);
  pinMode(MotorBpin2, OUTPUT);
  pinMode(MotorBpwm, OUTPUT);
  pinMode(MotorAcountA, INPUT_PULLUP);
  pinMode(MotorAcountB, INPUT_PULLUP);
  pinMode(MotorBcountA, INPUT_PULLUP);
  pinMode(MotorBcountB, INPUT_PULLUP);
  pinMode(Qvalue4, INPUT);//�Ҷȴ�����
  pinMode(Qvalue5, INPUT);
  pinMode(Hvalue4, INPUT);
  pinMode(Hvalue5, INPUT);
  pinMode(Llaser1, INPUT);//���⴫����
  pinMode(Llaser2, INPUT);
  pinMode(Rlaser1, INPUT);
  pinMode(Rlaser2, INPUT);
  ZUO1.attach(zuoyi);//�����ʼ��
  ZUO2.attach(zuoer);
  YOU1.attach(youyi);
  YOU2.attach(youer);
  ZUO3.attach(zuosan);
  ZUO4.attach(zuosi);
  YOU3.attach(yousan);
  YOU4.attach(yousi);
  YUANTONGKAIBI.attach(yuantongkaibi);
  YUANTONGSHANGXIA.attach(yuantongshangxia);
  ZUO1.write(zuo1_InitPos);//
  ZUO2.write(zuo2_InitPos);//
  YOU1.write(you1_InitPos);//
  YOU2.write(you2_InitPos);//
  ZUO3.write(zuo3_InitPos);//
  ZUO4.write(zuo4_InitPos);
  YOU3.write(you3_InitPos);//
  YOU4.write(you4_InitPos);//
  YUANTONGKAIBI.write(yuantongkaibi_InitPos+20);
  YUANTONGSHANGXIA.write(yuantongshangxia_InitPos);
  attachInterrupt(digitalPinToInterrupt(MotorAcountA), doMotorA, CHANGE);
  attachInterrupt(digitalPinToInterrupt(MotorBcountA), doMotorB, CHANGE);
  Serial.begin(9600);
}


// the loop routine runs over and over again forever:
void loop() {// put your main code here, to run repeatedly:
	delay(1000);
stop(1);
while (1);
}
