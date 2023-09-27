#include "Gimbal_Task.h"

#include "main.h"

#include "led.h"
#include "INS_Task.h"
#include "pid.h"
#include "delay.h"
#include "arm_math.h"
#include "CAN_Receive.h"
#include "INS_Task.h"
#include "user_lib.h"
#include "shoot.h"
#include "servo.h"
#include "gray.h"
#include "User_Task.h"


#include "FreeRTOSConfig.h"
#include "FreeRTOS.h"
#include "task.h"

//�������ֵ���� 0��8191
#define ECD_Format(ecd)         \
    {                           \
        if ((ecd) > ecd_range)  \
            (ecd) -= ecd_range; \
        else if ((ecd) < 0)     \
            (ecd) += ecd_range; \
    }
		

#if INCLUDE_uxTaskGetStackHighWaterMark
uint32_t gimbal_high_water;
#endif

//���̳�ʼ������Ҫ��pid��ʼ��
static void chassis_init(chassis_move_t *chassis_move_init);
//��������
static void chassis_feedback_update(chassis_move_t *chassis_move_update);
//�����ƶ�
static void chassis_move_angle_1(void);
//�����ƶ�
static void chassis_move_angle_2(void);

		
		static void chassis_staight_gray_556(int ff);
void sevor_on2_red(int v,int g);

		
		
//ǰ��Ѳ��ģʽ 1
static void chassis_staight_gray(int ff);
//ǰ��Ѳ��ģʽ 2
static void chassis_staight_gray_2(int ff);
//ǰ��Ѳ��ģʽ 3
static void chassis_staight_gray_3(int ff);
void staight_556(int v,int g);//v  ����ı�ʶ   g��һ����ʶ

static void chassis_staight_gray_4(int ff);
void staight_55(int v,int g);//v  ����ı�ʶ   g��һ����ʶ
void sevor_on2_bule(int v,int g);

static void chassis_staight_gray_5(int ff);
static void chassis_staight_gray_6(int ff);
static void chassis_staight_gray_pu(int ff);
static void chassis_staight_gray_55(int ff);
void sevor_on2_b(int v,int g);

static void chassis_staight_gray_33(int ff);

void staight_33(int v,int g);
void sevor_on2_bb(int v,int g);


//����Ѳ��ģʽ	
static void chassis_back_gray(int ff);
static void chassis_back_gray_long(int ff);
//��ת׼��ģʽ
int chassis_turn_ready(int dd);	
	void sevor_on_120(int v,int g);
	void sevor_on_1(int v,int g);
		void sevor_on2_120(int v,int g);
	void sevor_on2_1(int v,int g);
int chassis_turn_go(int dd,int ff,int ci);
void chassis_turn(int xiang,int ci,int v);
		
void jiu_zheng(int v);

void jiu_zheng_2(int v);
void jiu_zheng_y(int v);
void stop(int v,int g);



void colur_find(int ff,int yan);
void start_staight(int dd);
void turn(int v,int g,int xiang,int ci);
void staight_2(int v,int g);
void find_colur(int v,int g,int se);
void back_short(int v,int g);
void back_long(int v,int g);
void xingzoufangshi(int v,int g,int hh);
void staight_4(int v,int g);//v  ����ı�ʶ   g��һ����ʶ
void staight_5(int v,int g);//v  ����ı�ʶ   g��һ����ʶ
void staight_pi(int v,int g);//v  ����ı�ʶ   g��һ����ʶ
void staight_6(int v,int g);
void staight_3(int v,int g);
void avv_jiu(int v,int g);
void avv_jiu_2(int v,int g);
void avv_jiu_y(int v,int g);

void sevor_on2_w(int v,int g);

void turn_2(int v,int g,int xiang,int ci);

void chassis_turn_2(int xiang,int ci,int v);  //��ת90
void staight_5566(int v,int g);//v  ����ı�ʶ   g��һ����ʶ

void sevor_init();
void sevor_on2_g(int v,int g);

void sevor_init2();

//PID����
static void chassis_control_loop_1(chassis_move_t *chassis_move_control_loop);
//��ȡ�Ҷ�
void chassis_gary_loop();
static void chassis_staight_gray_5566(int ff);




//�����˶�����
chassis_move_t chassis_move;
int16_t qj3=0;
int16_t count;
int16_t c=0;
int16_t falg1 = 0,falg2 = 0,falg3 = 0,falg4 = 0;
int16_t key[20];
int16_t w = 1;
int16_t biao[255]={0};
int16_t colur;
int16_t weizhi=1;
int16_t se[5]={green,white,red,black,blue};
int16_t zhi[5]={1,2,3,4,5};
int16_t zhuan=0,yan=10,zhuan_count=0,zhuan_xiang=0;
uint16_t cs = 0,cs1=0;
int16_t tese[2]={red,blue};
int16_t tesebiao[2]={0,0};
int16_t cun[3]={0};
int16_t jici[20]={0};
int16_t wan[10]={0};
int16_t wn=0;
// ������
void GIMBAL_task(void *pvParameters)
{
	  //�ȴ������������������������
    vTaskDelay(GIMBAL_TASK_INIT_TIME);
	  chassis_init(&chassis_move);
	  sevor_init();
	sevor_init2();
	  while (1)
    {
    led_green_on();		
		//�������ݸ���
    chassis_feedback_update(&chassis_move);
  	 //�Ҷȷ��غ���
    chassis_gary_loop();
    //���̿��ƺ���
			  //colur = clour_disguish();

chassis_control_loop_1(&chassis_move);
			
		vTaskDelay(GIMBAL_CONTROL_TIME);
#if INCLUDE_uxTaskGetStackHighWaterMark
        gimbal_high_water = uxTaskGetStackHighWaterMark(NULL);
#endif		
		}
}
static void chassis_init(chassis_move_t *chassis_move_init)
{
	  if (chassis_move_init == NULL)
    {
        return;
    }	
	  //�����ٶȻ�pidֵ
    const static fp32 motor_speed_pid[3] = {M2006_MOTOR_SPEED_PID_KP, M2006_MOTOR_SPEED_PID_KI, M2006_MOTOR_SPEED_PID_KD};
		uint8_t i;			
	  //��ʼ��PID �˶�
    for (i = 0; i < 4; i++)
    {
        chassis_move_init->motor_chassis[i].chassis_motor_measure = get_Chassis_Motor_Measure_Point(i);
        PID_Init(&chassis_move_init->motor_speed_pid[i], PID_POSITION, motor_speed_pid, M2006_MOTOR_SPEED_MAX_OUT, M2006_MOTOR_SPEED_MAX_IOUT);
    }
		chassis_feedback_update(chassis_move_init);
		
		uint8_t d = 0;
		for (d = 0; d < 4; d++)
		{
    chassis_move.ecd_count[d] = 0;
    chassis_move.angle[d] = chassis_move_init->motor_chassis[d].chassis_motor_measure->ecd * Motor_ECD_TO_ANGLE;
    chassis_move.given_current[d] = 0;
    chassis_move.move_flag = 0;
    chassis_move.set_angle[d] = chassis_move.angle[d];
    chassis_move.speed[d] = 0.0f;
    chassis_move.speed_set[d] = 0.0f;
		}			
}

static void chassis_feedback_update(chassis_move_t *chassis_move_update)
{
	  uint8_t i = 0;
		for (i = 0; i < 4; i++)
		{
				
     //���µ���ٶȣ����ٶ����ٶȵ�PID΢��
     chassis_move_update->motor_chassis[i].speed = chassis_move_update->motor_chassis[i].chassis_motor_measure->speed_rpm * Motor_RMP_TO_SPEED;
		
		
    //���Ȧ�����ã� ��Ϊ�������תһȦ�� �������ת 36Ȧ������������ݴ������������ݣ����ڿ��������Ƕ�
    if (chassis_move_update->motor_chassis[i].chassis_motor_measure->ecd - chassis_move_update->motor_chassis[i].chassis_motor_measure->last_ecd > Half_ecd_range)
    {
        chassis_move.ecd_count[i]--;
    }
    else if (chassis_move_update->motor_chassis[i].chassis_motor_measure->ecd - chassis_move_update->motor_chassis[i].chassis_motor_measure->last_ecd < -Half_ecd_range)
    {
        chassis_move.ecd_count[i]++;
    }			

    if (chassis_move.ecd_count[i] == FULL_COUNT)
    {
        chassis_move.ecd_count[i] = -(FULL_COUNT - 1);
    }
    else if (chassis_move.ecd_count[i] == -FULL_COUNT)
    {
        chassis_move.ecd_count[i] = FULL_COUNT - 1;
    }

    //���������Ƕ�
    chassis_move.angle[i] = (chassis_move.ecd_count[i] * ecd_range + chassis_move_update->motor_chassis[i].chassis_motor_measure->ecd) * Motor_ECD_TO_ANGLE;		
		}	
		
}

static void chassis_control_loop_1(chassis_move_t *chassis_move_control_loop)
{
	  uint8_t i = 0;
	
	  for (i = 0; i < 4; i++)
    {
			 chassis_move_control_loop->motor_speed_pid[i].max_out = TRIGGER_BULLET_PID_MAX_OUT;
			 chassis_move_control_loop->motor_speed_pid[i].max_iout = TRIGGER_BULLET_PID_MAX_IOUT;
		}

//		
//////		//��ɫ
	  start_staight(1);   //ֱ��
    avv_jiu (2,1);
    avv_jiu_2(3,2);	
		turn_2(4,3,zuo,3);  //��ת90
		staight_2(5,4);		  //ǰ���м�
		sevor_on_120(6,5);  //ץ
   	back_short(7,6);		//����
    turn_2(8,7,you,8);//��ת45
    staight_3(9,8);		//ǰ�����
		sevor_on_1(10,9);
  	back_short(11,10);		//����
		
		//��ɫ
	  turn_2(12,11,you,8);//ת�䵽��Ӧ
		staight_2(13,12);		//ǰ���м�
		sevor_on_120(14,13);
  	back_short(15,14);		//����
	  turn_2(16,15,you,8);//ת�䵽��Ӧ
    staight_4(17,16);		//ǰ���м�
		sevor_on_1(18,17);
    back_short(19,18);		//����

    //��ɫ
	  turn_2(20,19,you,8);//ת�䵽��Ӧ
    staight_2(21,20);		//ǰ���м�
		sevor_on_120(22,21);   //ץ
    back_short(23,22);		//����
	  turn_2(24,23,you,8);//ת�䵽��Ӧ
	  turn_2(25,24,you,8);//ת�䵽��Ӧ
	  turn_2(26,25,you,8);//ת�䵽��Ӧ
	  turn_2(27,26,you,8);//ת�䵽��Ӧ
    staight_4(28,27);		//ǰ���м�
		sevor_on_1(29,28);
    back_short(30,29);		//����
		//��ɫ

  	turn_2(31,30,zuo,2);  //��ת90
    staight_55(32,31);
	  sevor_on2_120(33,32);
		sevor_on_120(34,33);   //ץ
	  sevor_on2_1(35,34);
    back_short(36,35);		//����
	  turn_2(37,36,you,8);//ת�䵽��Ӧ
	  turn_2(38,37,you,8);//ת�䵽��Ӧ
		turn_2(39,38,you,8);//ת�䵽��Ӧ
    staight_4(40,39);		//ǰ�����
		sevor_on_1(41,40);

   back_short(42,41);		//���� 
		//��ɫ
	  turn_2(43,42,you,8);//ת�䵽��Ӧ
	  turn_2(44,43,you,8);//ת�䵽��Ӧ
	  turn_2(45,44,you,8);//ת�䵽��Ӧ

    staight_55(46,45);
		sevor_on2_red(47,46);
		sevor_on_120(48,47);   //ץ
		sevor_on2_1(49,48);
    back_short(50,49);		//����
	 //��ɫ
	  turn_2(51,50,you,8);//ת�䵽��Ӧ
	  turn_2(52,51,you,8);//ת�䵽��Ӧ
	  turn_2(53,52,you,8);//ת�䵽��Ӧ
	  turn_2(54,53,you,8);//ת�䵽��Ӧ
    staight_3(55,54);		//ǰ�����
    sevor_on_1(56,55);  //̧����	

// // biao[56]  =  1;
     back_short(57,56);		//����

//  biao[59] = 1;
		turn_2(58,57,zuo,3);  //��ת90
    staight_55(59,58);
	  sevor_on2_w(60,59);
		sevor_on_120(61,60);   //ץ
	  sevor_on2_1(62,61);
    back_short(63,62);		//����
	  turn_2(64,63,you,8);//ת�䵽��Ӧ
	  turn_2(65,64,you,8);//ת�䵽��Ӧ
    staight_3(66,65);		//ǰ�����
    sevor_on_1(67,66);  //̧����	
    back_short(68,67);		//����
	  turn_2(69,68,you,8);//ת�䵽��Ӧ
	  turn_2(70,69,you,8);//ת�䵽��Ӧ
	  turn_2(71,70,you,8);//ת�䵽��Ӧ
	  turn_2(72,71,you,8);//ת�䵽��Ӧ

//biao[72] = 1;
    staight_55(73,72);
	  sevor_on2_w(74,73);
		sevor_on_120(75,74);   //ץ
	  sevor_on2_1(76,75);
    back_short(77,76);		//����

	  turn_2(78,77,you,8);//ת�䵽��Ӧ
	  turn_2(79,78,you,8);//ת�䵽��Ӧ
	  turn_2(80,79,you,8);//ת�䵽��Ӧ
	  turn_2(81,80,you,8);//ת�䵽��Ӧ
	  turn_2(82,81,you,4);//ת�䵽��Ӧ
    staight_4(83,82);		//ǰ�����

    sevor_on_1(84,83);  //̧����	


    back_short(85,84);		//����
	  turn_2(86,85,you,8);//ת�䵽��Ӧ
	  turn_2(87,86,you,8);//ת�䵽��Ӧ
	  turn_2(88,87,you,8);//ת�䵽��Ӧ
staight_556(89,88);
	  sevor_on2_b(90,89);
		sevor_on_120(91,90);   //ץ
     back_short(92,91);		//����
		    sevor_on2_1(93,92);

   turn_2(94,93,zuo,2);//ת�䵽��Ӧ
   staight_4(95,94);		//ǰ�����
   sevor_on_1(96,95);  //̧����	

    back_short(97,96);		//����
	  turn_2(98,97,you,8);//ת�䵽��Ӧ
	  turn_2(99,98,you,8);//ת�䵽��Ӧ






 

		    staight_556(100,99);		//����

		

				for (i = 0; i < 4; i++)
    {   
			  chassis_move_control_loop->motor_chassis[i].speed_set = chassis_move.speed_set[i];
        PID_Calc(&chassis_move_control_loop->motor_speed_pid[i], chassis_move_control_loop->motor_chassis[i].speed, chassis_move_control_loop->motor_chassis[i].speed_set);
    }		
     //��ֵ����ֵ
    for (i = 0; i < 4; i++)
    {
        chassis_move_control_loop->motor_chassis[i].give_current = (int16_t)(chassis_move_control_loop->motor_speed_pid[i].out);
    }
		
		   CAN_CMD_CHASSIS(chassis_move.motor_chassis[0].give_current,chassis_move.motor_chassis[1].give_current,
                              chassis_move.motor_chassis[2].give_current, chassis_move.motor_chassis[3].give_current);	
 
}

void jiu_zheng(int v)
{

	
  if(key[2] ==1&&key[3]==1)
	{	
			  biao[v]=1;
     		chassis_move.speed_set[0] = 0;
				chassis_move.speed_set[1] = 0;	
				chassis_move.speed_set[2] = 0;
				chassis_move.speed_set[3] = 0;		
	}
	
	
	  if(key[2] == 0)
	{	
		if(key[9] == 0)
		{
			   chassis_move.speed_set[0] = -left_goback_slow;
				 chassis_move.speed_set[1] = -left_goback_slow;	
				 chassis_move.speed_set[2] = 0;
				 chassis_move.speed_set[3] = 0;	
		}
		
		
				if(key[8] == 0)
		{
			   chassis_move.speed_set[0] = left_goback_slow;
				 chassis_move.speed_set[1] = left_goback_slow;	
				 chassis_move.speed_set[2] = 0;
				 chassis_move.speed_set[3] = 0;	
		}
	
	
	}
	 if(key[3] == 0)
	{	
		if(key[12] == 0)
		{
			   chassis_move.speed_set[0] = 0;
				 chassis_move.speed_set[1] = 0;	
				 chassis_move.speed_set[2] = -left_goback_slow;
				 chassis_move.speed_set[3] = -left_goback_slow;	
		}
		
		
				if(key[13] == 0)
		{
			   chassis_move.speed_set[0] = 0;
				 chassis_move.speed_set[1] = 0;	
				 chassis_move.speed_set[2] = left_goback_slow;
				 chassis_move.speed_set[3] = left_goback_slow;	
		}
	
	
	}
}


void jiu_zheng_2(int v)
{

			chassis_move.speed_set[0] = -left_go;
			chassis_move.speed_set[1] = -left_go;	
			chassis_move.speed_set[2] = -right_go;
			chassis_move.speed_set[3] = -right_go;
	
  if(key[8] ==1&&key[12]==1)
	{	
			  biao[v]=1;
     		chassis_move.speed_set[0] = 0;
				chassis_move.speed_set[1] = 0;	
				chassis_move.speed_set[2] = 0;
				chassis_move.speed_set[3] = 0;		
	}
	 //ͣ������
}



void jiu_zheng_y(int v)
{

	
  if( key[14] ==1)
	{	
			  biao[v]=1;
     		chassis_move.speed_set[0] = 0;
				chassis_move.speed_set[1] = 0;	
				chassis_move.speed_set[2] = 0;
				chassis_move.speed_set[3] = 0;		
	}
	
	
// if(key[7] == 0)
//	{	
//		if(key[6] == 0)
//		{
//			   chassis_move.speed_set[0] = -left_go;
//				 chassis_move.speed_set[1] = -left_go;	
//				 chassis_move.speed_set[2] = right_go;
//				 chassis_move.speed_set[3] = right_go;	
//		}
//		
//		
//				if(key[15] == 0)
//		{
//			   chassis_move.speed_set[0] = left_go;
//				 chassis_move.speed_set[1] = left_go;	
//				 chassis_move.speed_set[2] = -right_go;
//				 chassis_move.speed_set[3] = -right_go;	
//		}
//	
//	
//	}
	
	 if(key[14] == 0)
	{	
		if(key[9] == 0)
		{
//			   chassis_move.speed_set[0] = left_go;
//				 chassis_move.speed_set[1] = left_go;	
//				 chassis_move.speed_set[2] = 0;
//				 chassis_move.speed_set[3] = 0;	
			
						   chassis_move.speed_set[0] = 0;
				 chassis_move.speed_set[1] = 0;	
				 chassis_move.speed_set[2] = -right_go;
				 chassis_move.speed_set[3] = -right_go;	
		}
		
		
				if(key[12] == 0)
		{
			   chassis_move.speed_set[0] = 0;
				 chassis_move.speed_set[1] = 0;	
				 chassis_move.speed_set[2] = right_go;
				 chassis_move.speed_set[3] = right_go;	
		}
	
	
	}
	
	
	
	
	

}






void colur_find(int ff,int yanse)
{
	int aa=0;
 // colur = clour_disguish();
	colur=yanse ;
	if(yan!=colur)
	{
		for (aa=0;aa<5;aa++)
		{
			 if(colur==se[aa])
			{
	
			zhuan=(weizhi-zhi[aa])*45;//˳ʱ��С��0	
			if(weizhi-zhi[aa]<0)//˳ʱ��
				{
			zhuan_count= zhi[aa]-weizhi;
			zhuan_xiang=you ;}
			if(weizhi-zhi[aa]>0)//��ʱ��
			{
			zhuan_count= weizhi-zhi[aa];
			zhuan_xiang=zuo;}
				
			weizhi=zhi[aa];
			yan=colur;
			biao[ff]=1;
			}
		}		
	}
}


// ǰ��Ѳ��ģʽ
static void chassis_staight_gray(int ff)
{
	
		  chassis_move.speed_set[0] = left_go;
			chassis_move.speed_set[1] = left_go;	
			chassis_move.speed_set[2] = right_go;
			chassis_move.speed_set[3] = right_go;
	 
//			if(key[1] == 1 && key[0] == 0)
//			{		
//			   chassis_move.speed_set[0] = left_go_cha;
//				 chassis_move.speed_set[1] = left_go_cha;	
//				 chassis_move.speed_set[2] = right_go;
//				 chassis_move.speed_set[3] = right_go;		
//			}
//			if(key[15] == 1 && key[14] == 0)
//			{		
//			   chassis_move.speed_set[0] = 6.0;
//				 chassis_move.speed_set[1] = 6.0;	
//				 chassis_move.speed_set[2] = right_go;
//				 chassis_move.speed_set[3] = right_go;		
//			}			
			
			
			
			if(key[5] == 1 && key[14] == 0)
			{			
			   chassis_move.speed_set[0] = left_go;
				 chassis_move.speed_set[1] = left_go;	
				 chassis_move.speed_set[2] = right_go_cha;
  			 chassis_move.speed_set[3] = right_go_cha;
			}
			if(key[14] == 1 && key[5] == 0)
			{			
			   chassis_move.speed_set[0] = left_go_cha;
				 chassis_move.speed_set[1] = left_go_cha;	
				 chassis_move.speed_set[2] = right_go;
  			 chassis_move.speed_set[3] = right_go;
			}
			
			if( (key[12] == 1 && key[0] == 1 ) || (key[3] == 1 && key[0] == 1 ) || (key[13] == 1 && key[0] == 1 ))				
			{
 biao[ff]=1;
				 chassis_move.speed_set[0] = 0.0f;
				 chassis_move.speed_set[1] = 0.0f;	
				 chassis_move.speed_set[2] = 0.0f;
  			 chassis_move.speed_set[3] = 0.0f;	

			}			
			
			

			
}
// ǰ��Ѳ��ģʽ3
static void chassis_staight_gray_3(int ff)
{
	if(qj3==0){
	chassis_move.speed_set[0] = 8.0;  //2
			chassis_move.speed_set[1] = 8.0;	
			chassis_move.speed_set[2] = -8.0;
			chassis_move.speed_set[3] = -8.0;
	 
			if(key[5] == 1 && key[14] == 0)
			{			
			   chassis_move.speed_set[0] = 10.0;  //4
				 chassis_move.speed_set[1] = 10.0;	
				 chassis_move.speed_set[2] = 0;
  			 chassis_move.speed_set[3] = 0;
			}
			if(key[14] == 1 && key[5] == 0)
			{			
			   chassis_move.speed_set[0] = 0;
				 chassis_move.speed_set[1] = 0;	
				 chassis_move.speed_set[2] = -10.0;
  			 chassis_move.speed_set[3] = -10.0;
			}			
			if(  key[11] == 1)				
			{ 

				 chassis_move.speed_set[0] = 0.0f;
				 chassis_move.speed_set[1] = 0.0f;	
				 chassis_move.speed_set[2] = 0.0f;
  			 chassis_move.speed_set[3] = 0.0f;	
				
qj3=1;
			}
	}
	
		if(qj3==2){
		  chassis_move.speed_set[0] = 8.0;  //2
			chassis_move.speed_set[1] = 8.0;	
			chassis_move.speed_set[2] = -8.0;
			chassis_move.speed_set[3] = -8.0;
	 
			if(key[5] == 1 && key[14] == 0)
			{			
			   chassis_move.speed_set[0] = 10.0;  //4
				 chassis_move.speed_set[1] = 10.0;	
				 chassis_move.speed_set[2] = 0;
  			 chassis_move.speed_set[3] = 0;
			}
			if(key[14] == 1 && key[5] == 0)
			{			
			   chassis_move.speed_set[0] = 0;
				 chassis_move.speed_set[1] = 0;	
				 chassis_move.speed_set[2] = -10.0;
  			 chassis_move.speed_set[3] = -10.0;
			}			
			if(  key[10] == 1)				
			{ 

				 chassis_move.speed_set[0] = 0.0f;
				 chassis_move.speed_set[1] = 0.0f;	
				 chassis_move.speed_set[2] = 0.0f;
  			 chassis_move.speed_set[3] = 0.0f;	
				biao[ff]=1;
qj3=0;
			}

		}

if(qj3==1){
chassis_move.speed_set[0] = 12.0;  //2
			chassis_move.speed_set[1] = 12.0;	
			chassis_move.speed_set[2] = -12.0;
			chassis_move.speed_set[3] = -12.0;
	 
			if(key[5] == 1 && key[14] == 0)
			{			
			   chassis_move.speed_set[0] = 10.0;  //4
				 chassis_move.speed_set[1] = 10.0;	
				 chassis_move.speed_set[2] = 0;
  			 chassis_move.speed_set[3] = 0;
			}
			if(key[14] == 1 && key[5] == 0)
			{			
			   chassis_move.speed_set[0] = 0;
				 chassis_move.speed_set[1] = 0;	
				 chassis_move.speed_set[2] = -10.0;
  			 chassis_move.speed_set[3] = -10.0;
			}
			
					if(key[2]==1 && key[3]==1)				
			{ 

 
				
				 chassis_move.speed_set[0] = 0.0f;
				 chassis_move.speed_set[1] = 0.0f;	
				 chassis_move.speed_set[2] = 0.0f;
  			 chassis_move.speed_set[3] = 0.0f;	
				 
								   qj3=2;

				
			}
			




}
	  
}

// ǰ��Ѳ��ģʽ3
static void chassis_staight_gray_33(int ff)
{
		  chassis_move.speed_set[0] = 8.0;  //2
			chassis_move.speed_set[1] = 8.0;	
			chassis_move.speed_set[2] = -8.0;
			chassis_move.speed_set[3] = -8.0;
	 
			if(key[5] == 1 && key[14] == 0)
			{			
			   chassis_move.speed_set[0] = 10.0;  //4
				 chassis_move.speed_set[1] = 10.0;	
				 chassis_move.speed_set[2] = 0;
  			 chassis_move.speed_set[3] = 0;
			}
			if(key[14] == 1 && key[5] == 0)
			{			
			   chassis_move.speed_set[0] = 0;
				 chassis_move.speed_set[1] = 0;	
				 chassis_move.speed_set[2] = -10.0;
  			 chassis_move.speed_set[3] = -10.0;
			}
			
			if(  key[10] == 1)				
			{ 

 
				cs1=1;
				if(cs==2){
				 chassis_move.speed_set[0] = 0.0f;
				 chassis_move.speed_set[1] = 0.0f;	
				 chassis_move.speed_set[2] = 0.0f;
  			 chassis_move.speed_set[3] = 0.0f;	
				 cs=0;
				 cs1=0;
								   biao[ff]=1;

				
			}
			}
			else if(  key[10] == 0)				
			{ 
				if(cs1==1)
			  {
				   cs=cs+1;
					cs1=0;
				}
			}




	  
}




// ǰ��Ѳ��ģʽ3

static void chassis_staight_gray_5(int ff)
{
		  chassis_move.speed_set[0] = 4.5;  //2
			chassis_move.speed_set[1] = 4.5;	
			chassis_move.speed_set[2] = -4.5;
			chassis_move.speed_set[3] = -4.5;
	 
			if(key[5] == 1 && key[14] == 0)
			{			
			   chassis_move.speed_set[0] = 10.0;  //4
				 chassis_move.speed_set[1] = 10.0;	
				 chassis_move.speed_set[2] = 0;
  			 chassis_move.speed_set[3] = 0;
			}
			if(key[14] == 1 && key[5] == 0)
			{			
			   chassis_move.speed_set[0] = 0;
				 chassis_move.speed_set[1] = 0;	
				 chassis_move.speed_set[2] = -10.0;
  			 chassis_move.speed_set[3] = -10.0;
			}
			
//			if(  key[14] == 1 && key[5] == 1 && key[10] == 1)				
//			{ 

// 


//				 chassis_move.speed_set[0] = 0.0f;
//				 chassis_move.speed_set[1] = 0.0f;	
//				 chassis_move.speed_set[2] = 0.0f;
//  			 chassis_move.speed_set[3] = 0.0f;	

//								   biao[ff]=1;

//				
//			}
					if(  key[6] == 1)				
			{ 

 
				cs1=1;
				if(cs==2){
				 chassis_move.speed_set[0] = 0.0f;
				 chassis_move.speed_set[1] = 0.0f;	
				 chassis_move.speed_set[2] = 0.0f;
  			 chassis_move.speed_set[3] = 0.0f;	
				 cs=0;
				 cs1=0;
								   biao[ff]=1;

				
			}
			}
			else if(  key[6] == 0)				
			{ 
				if(cs1==1)
			  {
				   cs=cs+1;
					cs1=0;
				}
			}

	  
}

// ǰ��Ѳ��ģʽ3

static void chassis_staight_gray_556(int ff)
{
		if(qj3==0){
	     chassis_move.speed_set[0] = 8.0;  //2
			 chassis_move.speed_set[1] = 8.0;	
			 chassis_move.speed_set[2] = -8.0;
		   chassis_move.speed_set[3] = -8.0;
	 
			if(key[5] == 1 && key[14] == 0)
			{			
			   chassis_move.speed_set[0] = 10.0;  //4
				 chassis_move.speed_set[1] = 10.0;	
				 chassis_move.speed_set[2] = 0;
  			 chassis_move.speed_set[3] = 0;
			}
			if(key[14] == 1 && key[5] == 0)
			{			
			   chassis_move.speed_set[0] = 0;
				 chassis_move.speed_set[1] = 0;	
				 chassis_move.speed_set[2] = -10.0;
  			 chassis_move.speed_set[3] = -10.0;
			}			
			if(  key[11] == 1)				
			{ 

				 chassis_move.speed_set[0] = 0.0f;
				 chassis_move.speed_set[1] = 0.0f;	
				 chassis_move.speed_set[2] = 0.0f;
  			 chassis_move.speed_set[3] = 0.0f;	
				
        qj3=1;
			}
	    }
	
		if(qj3==2){
		  chassis_move.speed_set[0] = 8.0;  //2
			chassis_move.speed_set[1] = 8.0;	
			chassis_move.speed_set[2] = -8.0;
			chassis_move.speed_set[3] = -8.0;
	 
			if(key[5] == 1 && key[14] == 0)
			{			
			   chassis_move.speed_set[0] = 10.0;  //4
				 chassis_move.speed_set[1] = 10.0;	
				 chassis_move.speed_set[2] = 0;
  			 chassis_move.speed_set[3] = 0;
			}
			if(key[14] == 1 && key[5] == 0)
			{			
			   chassis_move.speed_set[0] = 0;
				 chassis_move.speed_set[1] = 0;	
				 chassis_move.speed_set[2] = -10.0;
  			 chassis_move.speed_set[3] = -10.0;
			}			
			if(  key[6] == 1)				
			{ 

				 chassis_move.speed_set[0] = 0.0f;
				 chassis_move.speed_set[1] = 0.0f;	
				 chassis_move.speed_set[2] = 0.0f;
  			 chassis_move.speed_set[3] = 0.0f;	
         qj3=3;
			}

		}

		
				if(qj3==3){
		  chassis_move.speed_set[0] = 3.0;  //2
			chassis_move.speed_set[1] = 3.0;	
			chassis_move.speed_set[2] = -3.0;
			chassis_move.speed_set[3] = -3.0;
	 
			if(key[5] == 1 && key[14] == 0)
			{			
			   chassis_move.speed_set[0] = 10.0;  //4
				 chassis_move.speed_set[1] = 10.0;	
				 chassis_move.speed_set[2] = 0;
  			 chassis_move.speed_set[3] = 0;
			}
			if(key[14] == 1 && key[5] == 0)
			{			
			   chassis_move.speed_set[0] = 0;
				 chassis_move.speed_set[1] = 0;	
				 chassis_move.speed_set[2] = -10.0;
  			 chassis_move.speed_set[3] = -10.0;
			}			
			if(  key[2] == 1&&key[3]==1)				
			{ 

				 chassis_move.speed_set[0] = 0.0f;
				 chassis_move.speed_set[1] = 0.0f;	
				 chassis_move.speed_set[2] = 0.0f;
  			 chassis_move.speed_set[3] = 0.0f;	
				biao[ff]=1;
         qj3=0;
			}

		}
				
		
     if(qj3==1){
       chassis_move.speed_set[0] = 6.0;  //2
			 chassis_move.speed_set[1] = 6.0;	
			 chassis_move.speed_set[2] = -6.0;
			 chassis_move.speed_set[3] = -6.0;
	 
			if(key[5] == 1 && key[14] == 0)
			{			
			   chassis_move.speed_set[0] = 10.0;  //4
				 chassis_move.speed_set[1] = 10.0;	
				 chassis_move.speed_set[2] = 0;
  			 chassis_move.speed_set[3] = 0;
			}
			if(key[14] == 1 && key[5] == 0)
			{			
			   chassis_move.speed_set[0] = 0;
				 chassis_move.speed_set[1] = 0;	
				 chassis_move.speed_set[2] = -10.0;
  			 chassis_move.speed_set[3] = -10.0;
			}
			
		  if(key[2]==1 && key[3]==1)				
			{ 

 
				
				 chassis_move.speed_set[0] = 0.0f;
				 chassis_move.speed_set[1] = 0.0f;	
				 chassis_move.speed_set[2] = 0.0f;
  			 chassis_move.speed_set[3] = 0.0f;	
				 
								   qj3=2;

				
			}
			




}
	  
	  
}




static void chassis_staight_gray_5566(int ff)
{
		if(qj3==0){
	     chassis_move.speed_set[0] = 8.0;  //2
			 chassis_move.speed_set[1] = 8.0;	
			 chassis_move.speed_set[2] = -8.0;
		   chassis_move.speed_set[3] = -8.0;
	 
			if(key[5] == 1 && key[14] == 0)
			{			
			   chassis_move.speed_set[0] = 10.0;  //4
				 chassis_move.speed_set[1] = 10.0;	
				 chassis_move.speed_set[2] = 0;
  			 chassis_move.speed_set[3] = 0;
			}
			if(key[14] == 1 && key[5] == 0)
			{			
			   chassis_move.speed_set[0] = 0;
				 chassis_move.speed_set[1] = 0;	
				 chassis_move.speed_set[2] = -10.0;
  			 chassis_move.speed_set[3] = -10.0;
			}			
			if(  key[11] == 1)				
			{ 

				 chassis_move.speed_set[0] = 0.0f;
				 chassis_move.speed_set[1] = 0.0f;	
				 chassis_move.speed_set[2] = 0.0f;
  			 chassis_move.speed_set[3] = 0.0f;	
				
        qj3=1;
			}
	    }
	
		if(qj3==2){
		  chassis_move.speed_set[0] = 8.0;  //2
			chassis_move.speed_set[1] = 8.0;	
			chassis_move.speed_set[2] = -8.0;
			chassis_move.speed_set[3] = -8.0;
	 
			if(key[5] == 1 && key[14] == 0)
			{			
			   chassis_move.speed_set[0] = 10.0;  //4
				 chassis_move.speed_set[1] = 10.0;	
				 chassis_move.speed_set[2] = 0;
  			 chassis_move.speed_set[3] = 0;
			}
			if(key[14] == 1 && key[5] == 0)
			{			
			   chassis_move.speed_set[0] = 0;
				 chassis_move.speed_set[1] = 0;	
				 chassis_move.speed_set[2] = -10.0;
  			 chassis_move.speed_set[3] = -10.0;
			}			
			if(  key[6] == 1)				
			{ 

				 chassis_move.speed_set[0] = 0.0f;
				 chassis_move.speed_set[1] = 0.0f;	
				 chassis_move.speed_set[2] = 0.0f;
  			 chassis_move.speed_set[3] = 0.0f;	
         qj3=3;
			}

		}

		
				if(qj3==3){
		  chassis_move.speed_set[0] = 3.0;  //2
			chassis_move.speed_set[1] = 3.0;	
			chassis_move.speed_set[2] = -3.0;
			chassis_move.speed_set[3] = -3.0;
	 
			if(key[5] == 1 && key[14] == 0)
			{			
			   chassis_move.speed_set[0] = 10.0;  //4
				 chassis_move.speed_set[1] = 10.0;	
				 chassis_move.speed_set[2] = 0;
  			 chassis_move.speed_set[3] = 0;
			}
			if(key[14] == 1 && key[5] == 0)
			{			
			   chassis_move.speed_set[0] = 0;
				 chassis_move.speed_set[1] = 0;	
				 chassis_move.speed_set[2] = -10.0;
  			 chassis_move.speed_set[3] = -10.0;
			}			
			if(  key[9] == 1&&key[13]==1)				
			{ 

				 chassis_move.speed_set[0] = 0.0f;
				 chassis_move.speed_set[1] = 0.0f;	
				 chassis_move.speed_set[2] = 0.0f;
  			 chassis_move.speed_set[3] = 0.0f;	
				biao[ff]=1;
         qj3=0;
			}

		}
				
		
     if(qj3==1){
       chassis_move.speed_set[0] = 6.0;  //2
			 chassis_move.speed_set[1] = 6.0;	
			 chassis_move.speed_set[2] = -6.0;
			 chassis_move.speed_set[3] = -6.0;
	 
			if(key[5] == 1 && key[14] == 0)
			{			
			   chassis_move.speed_set[0] = 10.0;  //4
				 chassis_move.speed_set[1] = 10.0;	
				 chassis_move.speed_set[2] = 0;
  			 chassis_move.speed_set[3] = 0;
			}
			if(key[14] == 1 && key[5] == 0)
			{			
			   chassis_move.speed_set[0] = 0;
				 chassis_move.speed_set[1] = 0;	
				 chassis_move.speed_set[2] = -10.0;
  			 chassis_move.speed_set[3] = -10.0;
			}
			
		  if(key[2]==1 && key[3]==1)				
			{ 

 
				
				 chassis_move.speed_set[0] = 0.0f;
				 chassis_move.speed_set[1] = 0.0f;	
				 chassis_move.speed_set[2] = 0.0f;
  			 chassis_move.speed_set[3] = 0.0f;	
				 
								   qj3=2;

				
			}
			




}
	  
	  
}




static void chassis_staight_gray_6(int ff)
{
		  chassis_move.speed_set[0] = 12.0;  //2
			chassis_move.speed_set[1] = 12.0;	
			chassis_move.speed_set[2] = -12.0;
			chassis_move.speed_set[3] = -12.0;
	 
			if(key[5] == 1 && key[14] == 0)
			{			
			   chassis_move.speed_set[0] = 10.0;  //4
				 chassis_move.speed_set[1] = 10.0;	
				 chassis_move.speed_set[2] = 0;
  			 chassis_move.speed_set[3] = 0;
			}
			if(key[14] == 1 && key[5] == 0)
			{			
			   chassis_move.speed_set[0] = 0;
				 chassis_move.speed_set[1] = 0;	
				 chassis_move.speed_set[2] = -10.0;
  			 chassis_move.speed_set[3] = -10.0;
			}
			
					if(  key[8] == 1&&key[12]==1)				
			{ 

 
				
				 chassis_move.speed_set[0] = 0.0f;
				 chassis_move.speed_set[1] = 0.0f;	
				 chassis_move.speed_set[2] = 0.0f;
  			 chassis_move.speed_set[3] = 0.0f;	
				 
								   biao[ff]=1;

				
			}
			
			

	  
}


static void chassis_staight_gray_55(int ff)
{
		if(qj3==0){
	     chassis_move.speed_set[0] = 8.0;  //2
			 chassis_move.speed_set[1] = 8.0;	
			 chassis_move.speed_set[2] = -8.0;
		   chassis_move.speed_set[3] = -8.0;
	 
			if(key[5] == 1 && key[14] == 0)
			{			
			   chassis_move.speed_set[0] = 10.0;  //4
				 chassis_move.speed_set[1] = 10.0;	
				 chassis_move.speed_set[2] = 0;
  			 chassis_move.speed_set[3] = 0;
			}
			if(key[14] == 1 && key[5] == 0)
			{			
			   chassis_move.speed_set[0] = 0;
				 chassis_move.speed_set[1] = 0;	
				 chassis_move.speed_set[2] = -10.0;
  			 chassis_move.speed_set[3] = -10.0;
			}			
			if(  key[11] == 1)				
			{ 

				 chassis_move.speed_set[0] = 0.0f;
				 chassis_move.speed_set[1] = 0.0f;	
				 chassis_move.speed_set[2] = 0.0f;
  			 chassis_move.speed_set[3] = 0.0f;	
				
        qj3=1;
			}
	    }
	
		if(qj3==2){
		  chassis_move.speed_set[0] = 3.0;  //2
			chassis_move.speed_set[1] = 3.0;	
			chassis_move.speed_set[2] = -3.0;
			chassis_move.speed_set[3] = -3.0;
	 
			if(key[5] == 1 && key[14] == 0)
			{			
			   chassis_move.speed_set[0] = 10.0;  //4
				 chassis_move.speed_set[1] = 10.0;	
				 chassis_move.speed_set[2] = 0;
  			 chassis_move.speed_set[3] = 0;
			}
			if(key[14] == 1 && key[5] == 0)
			{			
			   chassis_move.speed_set[0] = 0;
				 chassis_move.speed_set[1] = 0;	
				 chassis_move.speed_set[2] = -10.0;
  			 chassis_move.speed_set[3] = -10.0;
			}			
			if(  key[6] == 1)				
			{ 

				 chassis_move.speed_set[0] = 0.0f;
				 chassis_move.speed_set[1] = 0.0f;	
				 chassis_move.speed_set[2] = 0.0f;
  			 chassis_move.speed_set[3] = 0.0f;	
				biao[ff]=1;
         qj3=0;
			}

		}

		

				
		
     if(qj3==1){
       chassis_move.speed_set[0] = 8.0;  //2
			 chassis_move.speed_set[1] = 8.0;	
			 chassis_move.speed_set[2] = -8.0;
			 chassis_move.speed_set[3] = -8.0;
	 
			if(key[5] == 1 && key[14] == 0)
			{			
			   chassis_move.speed_set[0] = 10.0;  //4
				 chassis_move.speed_set[1] = 10.0;	
				 chassis_move.speed_set[2] = 0;
  			 chassis_move.speed_set[3] = 0;
			}
			if(key[14] == 1 && key[5] == 0)
			{			
			   chassis_move.speed_set[0] = 0;
				 chassis_move.speed_set[1] = 0;	
				 chassis_move.speed_set[2] = -10.0;
  			 chassis_move.speed_set[3] = -10.0;
			}
			
		  if(key[2]==1 && key[3]==1)				
			{ 

 
				
				 chassis_move.speed_set[0] = 0.0f;
				 chassis_move.speed_set[1] = 0.0f;	
				 chassis_move.speed_set[2] = 0.0f;
  			 chassis_move.speed_set[3] = 0.0f;	
				 
								   qj3=2;

				
			}
			




}
			

	  
}


static void chassis_staight_gray_pu(int ff)
{
		  chassis_move.speed_set[0] = 12.0;  //2
			chassis_move.speed_set[1] = 12.0;	
			chassis_move.speed_set[2] = -12.0;
			chassis_move.speed_set[3] = -12.0;
	 
			if(key[5] == 1 && key[14] == 0)
			{			
			   chassis_move.speed_set[0] = 10.0;  //4
				 chassis_move.speed_set[1] = 10.0;	
				 chassis_move.speed_set[2] = 0;
  			 chassis_move.speed_set[3] = 0;
			}
			if(key[14] == 1 && key[5] == 0)
			{			
			   chassis_move.speed_set[0] = 0;
				 chassis_move.speed_set[1] = 0;	
				 chassis_move.speed_set[2] = -10.0;
  			 chassis_move.speed_set[3] = -10.0;
			}
			
					if(key[2]==1 && key[3]==1)				
			{ 

 
				
				 chassis_move.speed_set[0] = 0.0f;
				 chassis_move.speed_set[1] = 0.0f;	
				 chassis_move.speed_set[2] = 0.0f;
  			 chassis_move.speed_set[3] = 0.0f;	
				 
								   biao[ff]=1;

				
			}
			
	 
			

	
	
	
}



// ǰ��Ѳ��ģʽ4

//static void chassis_staight_gray_4init(chassis_move_t *chassis_move_init)
//{
//	
//		uint8_t d = 0;
//		for (d = 0; d < 4; d++)
//		{
//    chassis_move.ecd_count[d] = 0;
//    chassis_move.angle[d] = chassis_move_init->motor_chassis[d].chassis_motor_measure->ecd * Motor_ECD_TO_ANGLE;
//    chassis_move.given_current[d] = 0;
//    chassis_move.move_flag = 0;
//    chassis_move.set_angle[d] = chassis_move.angle[d];
//    chassis_move.speed[d] = 0.0f;
//    chassis_move.speed_set[d] = 0.0f;
//		}	


//}


static void chassis_staight_gray_4(int ff)
{
		  chassis_move.speed_set[0] = 8.0;  //2
			chassis_move.speed_set[1] = 8.0;	
			chassis_move.speed_set[2] = -8.0;
			chassis_move.speed_set[3] = -8.0;
	 
			if(key[5] == 1 && key[14] == 0)
			{			
			   chassis_move.speed_set[0] = 10.0;  //4
				 chassis_move.speed_set[1] = 10.0;	
				 chassis_move.speed_set[2] = 0;
  			 chassis_move.speed_set[3] = 0;
			}
			if(key[14] == 1 && key[5] == 0)
			{			
			   chassis_move.speed_set[0] = 0;
				 chassis_move.speed_set[1] = 0;	
				 chassis_move.speed_set[2] = -10.0;
  			 chassis_move.speed_set[3] = -10.0;
			}
			
			if(  key[14] == 1 && key[5] == 1)				
			{ 

				 chassis_move.speed_set[0] = 0.0f;
				 chassis_move.speed_set[1] = 0.0f;	
				 chassis_move.speed_set[2] = 0.0f;
  			 chassis_move.speed_set[3] = 0.0f;	

								   biao[ff]=1;

				
			}
			
			
//			if(  key[10] == 1)				
//			{ 

// 
//				cs1=1;
//				if(cs==4){
//				 chassis_move.speed_set[0] = 0.0f;
//				 chassis_move.speed_set[1] = 0.0f;	
//				 chassis_move.speed_set[2] = 0.0f;
//  			 chassis_move.speed_set[3] = 0.0f;	
//				 cs=0;
//				 cs1=0;
//								   biao[ff]=1;

//				
//			}
//			}
//			else if(  key[10] == 0)				
//			{ 
//				if(cs1==1)
//			  {
//				   cs=cs+1;
//					cs1=0;
//				}

//chassis_move.angle[0] = 0;

//			}
//	 chassis_move.set_angle[0] = rad_format(PI_All);
//	
//		if(rad_format(chassis_move.set_angle[0] - chassis_move.angle[0]) > 0.05f )
//		{
//		        chassis_move.speed_set[0] = 12.0;
//					  chassis_move.speed_set[1] = 12.0;
//					  chassis_move.speed_set[2] = -12.0;
//					  chassis_move.speed_set[3] = -12.0;

//						if(key[5] == 1 && key[14] == 0)
//			{			
//			   chassis_move.speed_set[0] = 10.0;  //4
//				 chassis_move.speed_set[1] = 10.0;	
//				 chassis_move.speed_set[2] = 0;
//  			 chassis_move.speed_set[3] = 0;
//			}
//			if(key[14] == 1 && key[5] == 0)
//			{			
//			   chassis_move.speed_set[0] = 0;
//				 chassis_move.speed_set[1] = 0;	
//				 chassis_move.speed_set[2] = -10.0;
//  			 chassis_move.speed_set[3] = -10.0;
//			}
//			
//		}
//		else
//		{
//		        chassis_move.speed_set[0] = 0;
//					  chassis_move.speed_set[1] = 0;
//					  chassis_move.speed_set[2] = 0;
//					  chassis_move.speed_set[3] = 0;		
//		biao[ff]=1;
//		}
		
		
	  
}



// ǰ��Ѳ��ģʽ2
static void chassis_staight_gray_2(int ff)
 {
		  chassis_move.speed_set[0] = left_go_slow;
			chassis_move.speed_set[1] = left_go_slow;	
			chassis_move.speed_set[2] = right_go_slow;
			chassis_move.speed_set[3] = right_go_slow;
	 
//			if(key[1] == 1 && key[0] == 0)
//			{		
//			   chassis_move.speed_set[0] = left_go_cha_slow;
//				 chassis_move.speed_set[1] = left_go_cha_slow;	
//				 chassis_move.speed_set[2] = right_go_slow;
//				 chassis_move.speed_set[3] = right_go_slow;		
//			}
//			if(key[0] == 1 && key[1] == 0)
//			{			
//			   chassis_move.speed_set[0] = left_go_slow;
//				 chassis_move.speed_set[1] = left_go_slow;	
//				 chassis_move.speed_set[2] = right_go_cha_slow;
//  			 chassis_move.speed_set[3] = right_go_cha_slow;
//			}
//			
			
			if(key[5] == 1 && key[14] == 0)
			{			
			   chassis_move.speed_set[0] = left_go_slow;
				 chassis_move.speed_set[1] = left_go_slow;	
				 chassis_move.speed_set[2] = 0;
  			 chassis_move.speed_set[3] = 0;
			}
			if(key[14] == 1 && key[5] == 0)
			{			
			   chassis_move.speed_set[0] = 0;
				 chassis_move.speed_set[1] = 0;	
				 chassis_move.speed_set[2] = right_go_slow;
  			 chassis_move.speed_set[3] = right_go_slow;
			}
//			if( (key[6] == 1 && key[7] == 1) || (key[6] == 1 && key[10] == 1) || (key[7] == 1 && key[11] == 1) ||(key[10] == 1 && key[11] == 1))				
//			{
//				 chassis_move.speed_set[0] = 0.0f;
//				 chassis_move.speed_set[1] = 0.0f;	
//				 chassis_move.speed_set[2] = 0.0f;
//  			 chassis_move.speed_set[3] = 0.0f;	
//			  biao[ff]=1;
//			}
			
			
			
			if( key[11] == 1 )				
			{

				 chassis_move.speed_set[0] = 0.0f;
				 chassis_move.speed_set[1] = 0.0f;	
				 chassis_move.speed_set[2] = 0.0f;
  			 chassis_move.speed_set[3] = 0.0f;	
			  biao[ff]=1;
			}			

		}


// ����Ѳ��ģʽ
static void chassis_back_gray(int ff)
{
	
		  chassis_move.speed_set[0] = left_goback_slow;
			chassis_move.speed_set[1] = left_goback_slow;	
			chassis_move.speed_set[2] = right_goback_slow;
			chassis_move.speed_set[3] = right_goback_slow;
	 
			if(key[4] == 1 && key[1] == 0)
			{	
			   chassis_move.speed_set[0] = 0;
				 chassis_move.speed_set[1] = 0;	
				 chassis_move.speed_set[2] = right_goback_slow;
				 chassis_move.speed_set[3] = right_goback_slow;	
			}
			if(key[1] == 1 && key[4] == 0)
			{			
			   chassis_move.speed_set[0] = left_goback_slow;
				 chassis_move.speed_set[1] = left_goback_slow;	
				 chassis_move.speed_set[2] = 0;
				 chassis_move.speed_set[3] = 0;
			}
	
			
			if( key[12] == 1 && key[10] == 1 )				
			{
 biao[ff]=1;
				 chassis_move.speed_set[0] = 0.0f;
				 chassis_move.speed_set[1] = 0.0f;	
				 chassis_move.speed_set[2] = 0.0f;
  			 chassis_move.speed_set[3] = 0.0f;	

			}		
			
			
			
	  }

static void chassis_back_gray_long(int ff)
{
	
		  chassis_move.speed_set[0] = left_goback_slow;
			chassis_move.speed_set[1] = left_goback_slow;	
			chassis_move.speed_set[2] = right_goback_slow;
			chassis_move.speed_set[3] = right_goback_slow;
	 
			if(key[0] == 1 && key[1] == 0)
			{		
			   chassis_move.speed_set[0] = left_goback_slow;
				 chassis_move.speed_set[1] = left_goback_slow;	
				 chassis_move.speed_set[2] = left_goback_cha_slow;
				 chassis_move.speed_set[3] = left_goback_cha_slow;	
			}
			if(key[1] == 1 && key[0] == 0)
			{			
			   chassis_move.speed_set[0] = right_goback_cha_slow;
				 chassis_move.speed_set[1] = right_goback_cha_slow;	
				 chassis_move.speed_set[2] = right_goback_slow;
				 chassis_move.speed_set[3] = right_goback_slow;
			}
	
			
			if(  key[5] == 1 )				
			{
				cs1=1;
				if(cs==3){
				 chassis_move.speed_set[0] = 0.0f;
				 chassis_move.speed_set[1] = 0.0f;	
				 chassis_move.speed_set[2] = 0.0f;
  			 chassis_move.speed_set[3] = 0.0f;	
			   biao[ff]=1;
				 cs=0;
				 cs1=0;
				}
			}
			if( key[5] == 0 )				
			{ 
				if(cs1==1)
			  {
				   cs=cs+1;
					cs1=0;
					//cs1=2;
				}			}
	  }



void start_staight(int dd)
{
		if(biao[dd]==0)
		{
		//chassis_move_right_90(dd);
		chassis_staight_gray(dd);
		}
}

void turn(int v,int g,int xiang,int ci)//v  ����ı�ʶ   g��һ����ʶ
{
  if(biao[v]==0&&biao[g]==1)
	{
	chassis_turn(xiang,ci,v);  //��ת90
	}
}
void staight_2(int v,int g)//v  ����ı�ʶ   g��һ����ʶ
{
  if(biao[v]==0&&biao[g]==1)//3 2
	{
    //	chassis_turn(you,2,v);
		chassis_staight_gray_2(v); //ֱ��
	}
}
void turn_2(int v,int g,int xiang,int ci)
{
if(biao[v]==0&&biao[g]==1)
	{
	chassis_turn_2(xiang,ci,v);  //��ת90
	}
}

void chassis_turn_2(int xiang,int ci,int v)  //��ת90
{
	
if(key[14]==0&&key[5]==0&&jici[5]==0){
jici[5]=1;
}
if(key[14]==1&&key[5]==0&&jici[5]==0){
	chassis_move.speed_set[0] = -5.0;  //��ת
		  chassis_move.speed_set[1] = -5.0;	
	   	chassis_move.speed_set[2] = -5.0;  
		  chassis_move.speed_set[3] = -5.0;
	
if(key[14]==0&&key[5]==0&&jici[5]==0){
	  chassis_move.speed_set[0] = 0.0f;  //��ת
		  chassis_move.speed_set[1] = 0.0f;	
	   	chassis_move.speed_set[2] = 0.0f;  
		  chassis_move.speed_set[3] = 0.0f;	
jici[5]=1;
}
}
if(key[14]==0&&key[5]==1&&jici[5]==0){
	chassis_move.speed_set[0] = 5.0;  //��ת
		  chassis_move.speed_set[1] = 5.0;	
	   	chassis_move.speed_set[2] = 5.0;  
		  chassis_move.speed_set[3] = 5.0;
	
if(key[14]==0&&key[5]==0&&jici[5]==0){
	  chassis_move.speed_set[0] = 0.0f;  //��ת
		  chassis_move.speed_set[1] = 0.0f;	
	   	chassis_move.speed_set[2] = 0.0f;  
		  chassis_move.speed_set[3] = 0.0f;	
jici[5]=1;
}
	
}
if(jici[5]==1){
if(xiang==zuo)
				 {
					if(jici[4]==0){
      chassis_move.speed_set[0] = -5.0;  //��ת
		  chassis_move.speed_set[1] = -5.0;	
	   	chassis_move.speed_set[2] = -5.0;  
		  chassis_move.speed_set[3] = -5.0;
					}
					if((key[14]==0&&key[5]==1)&&jici[0]==ci)
					{			
						
      chassis_move.speed_set[0] = 0.0f;  //��ת
		  chassis_move.speed_set[1] = 0.0f;	
	   	chassis_move.speed_set[2] = 0.0f;  
		  chassis_move.speed_set[3] = 0.0f;	
		jici[1]=0;
		jici[2]=0;
		jici[3]=0;
		jici[4]=0;
		jici[5]=0;
		jici[6]=0;
		jici[7]=0;
		jici[0]=0;
			
         biao[v]=1;		
					}					
					if((key[14]==0&&key[5]==1)&& (jici[0]<ci&&jici[2]==0))
					{
			
						jici[0]=jici[0]+1;
						jici[1]=1;
						jici[2]=1;
						
      }
					if((key[14]!=1&&key[5]==0)&&jici[1]==1)
					{
			jici[2]=0;
						jici[1]=0;
				}
			}
				 
			
}


//if(xiang==zuo)
//				 {
//					 if(key[14]==1&&jici[4]==0){
//jici[5]=1;
//jici[4]=1;						 
//}
//					 
//if(jici[5]==1){

//	chassis_move.speed_set[0] = right_go;  //��ת
//		  chassis_move.speed_set[1] = right_go;	
//	   	chassis_move.speed_set[2] = right_go;  
//		  chassis_move.speed_set[3] = right_go;
//					
//	if (key[14]==0){
//		//ֹͣ
//		chassis_move.speed_set[0] = 0.0f;  //��ת
//		  chassis_move.speed_set[1] = 0.0f;	
//	   	chassis_move.speed_set[2] = 0.0f;  
//		  chassis_move.speed_set[3] = 0.0f;	
//		
//	  jici[5]=2;
//		
//	}
//}


//					  if(key[14]==0&&jici[4]==0){
//jici[5]=2;
//							jici[4]=1;
//							
//}
//					 
//			if(jici[5]==2){
//if(jici[7]==0){

//	chassis_move.speed_set[0] = right_go;  //��ת
//		  chassis_move.speed_set[1] = right_go;	
//	   	chassis_move.speed_set[2] = right_go;  
//		  chassis_move.speed_set[3] = right_go;
//					
//	if (key[14]==1){
//		//ֹͣ
//		chassis_move.speed_set[0] = 0.0f;  //��ת
//		  chassis_move.speed_set[1] = 0.0f;	
//	   	chassis_move.speed_set[2] = 0.0f;  
//		  chassis_move.speed_set[3] = 0.0f;	
//		
//	  jici[7]=2;
//		
//	}
//}
//		
//}
//			if(jici[7]==2){
//if(jici[6]==0){

//	chassis_move.speed_set[0] = right_go;  //��ת
//		  chassis_move.speed_set[1] = right_go;	
//	   	chassis_move.speed_set[2] = right_go;  
//		  chassis_move.speed_set[3] = right_go;
//					
//	if (key[14]==0){
//		//ֹͣ
//		chassis_move.speed_set[0] = 0.0f;  //��ת
//		  chassis_move.speed_set[1] = 0.0f;	
//	   	chassis_move.speed_set[2] = 0.0f;  
//		  chassis_move.speed_set[3] = 0.0f;	
//		
//	  biao[v]=1;
//		jici[1]=0;
//		jici[2]=0;
//		jici[3]=0;
//		jici[4]=0;
//		jici[5]=0;
//		jici[6]=0;
//		jici[7]=0;
//		jici[0]=0;
//		
//		
//	}
//}
//		
//}

//}


if(xiang==you)
				 {
					 if(key[5]==1&&jici[4]==0){
jici[5]=1;
jici[4]=1;						 
}
					 
if(jici[5]==1){

	chassis_move.speed_set[0] = 5.0;  //��ת
		  chassis_move.speed_set[1] = 5.0;	
	   	chassis_move.speed_set[2] = 5.0;  
		  chassis_move.speed_set[3] = 5.0;
					
	if (key[5]==0){
		//ֹͣ
		chassis_move.speed_set[0] = 0.0f;  //��ת
		  chassis_move.speed_set[1] = 0.0f;	
	   	chassis_move.speed_set[2] = 0.0f;  
		  chassis_move.speed_set[3] = 0.0f;	
		
	  jici[5]=2;
		
	}
}


					  if(key[5]==0&&jici[4]==0){
jici[5]=2;
							jici[4]=1;
							
}
					 
			if(jici[5]==2){
if(jici[7]==0){

	chassis_move.speed_set[0] = left_go;  //��ת
		  chassis_move.speed_set[1] = left_go;	
	   	chassis_move.speed_set[2] = left_go;  
		  chassis_move.speed_set[3] = left_go;
					
	if (key[5]==1){
		//ֹͣ
		chassis_move.speed_set[0] = 0.0f;  //��ת
		  chassis_move.speed_set[1] = 0.0f;	
	   	chassis_move.speed_set[2] = 0.0f;  
		  chassis_move.speed_set[3] = 0.0f;	
		
	  jici[7]=2;
		
	}
}
		
}
			if(jici[7]==2){
if(jici[6]==0){

	chassis_move.speed_set[0] = left_go;  //��ת
		  chassis_move.speed_set[1] = left_go;	
	   	chassis_move.speed_set[2] = left_go;  
		  chassis_move.speed_set[3] = left_go;
					
	if (key[5]==0){
		//ֹͣ
		chassis_move.speed_set[0] = 0.0f;  //��ת
		  chassis_move.speed_set[1] = 0.0f;	
	   	chassis_move.speed_set[2] = 0.0f;  
		  chassis_move.speed_set[3] = 0.0f;	
		
	  biao[v]=1;
		jici[1]=0;
		jici[2]=0;
		jici[3]=0;
		jici[4]=0;
		jici[5]=0;
		jici[6]=0;
		jici[7]=0;
		jici[0]=0;
		
		
	}
}
		
}

}
		
	} 


void find_colur(int v,int g,int se)//v  ����ı�ʶ   g��һ����ʶ
{
  if(biao[v]==0&&biao[g]==1)//3 2
	{
		colur_find(v,se);
	}
}

void back_short(int v,int g)//v  ����ı�ʶ   g��һ����ʶ
{
  if(biao[v]==0&&biao[g]==1)
	{
	chassis_back_gray(v);
	}
}

void back_long(int v,int g)//v  ����ı�ʶ   g��һ����ʶ
{
  if(biao[v]==0&&biao[g]==1)
	{
	chassis_back_gray_long(v);
	}
}


void xingzoufangshi(int v,int g,int hh)//v  ����ı�ʶ   g��һ����ʶ
{
  if(biao[v]==0&&biao[g]==1)//3 2
	{

    ////	chassis_turn(you,2,v);
		//�for (wn=0;wn<2;wn++){
	if(colur==tese[0] && tesebiao[0]==0) 
		{
    //tesebiao[wn]=1;
	    wan[hh]=2;
			tesebiao[0]=1;
			biao[v]=1;
			
	  }	
		if(colur==tese[1] && tesebiao[1]==0) 
		{
			tesebiao[1]=1;
    //tesebiao[wn]=1;
	    wan[hh]=2;
			biao[v]=1;
	  }	
		if(colur==black | colur==white | colur==green )	
		{  wan[hh]=3;
    //if(b==0)
			biao[v]=1;
		}
		
		
		
	}
}

void staight_3(int v,int g)//v  ����ı�ʶ   g��һ����ʶ
{
  if(biao[v]==0&&biao[g]==1)
	{
	chassis_staight_gray_3(v);
	}
}
void staight_33(int v,int g)//v  ����ı�ʶ   g��һ����ʶ
{
  if(biao[v]==0&&biao[g]==1)
	{
	chassis_staight_gray_33(v);
	}
}


void staight_4(int v,int g)//v  ����ı�ʶ   g��һ����ʶ
{
  if(biao[v]==0&&biao[g]==1)
	{
	chassis_staight_gray_4(v);
	}
}

void staight_5(int v,int g)//v  ����ı�ʶ   g��һ����ʶ
{
  if(biao[v]==0&&biao[g]==1)
	{
	chassis_staight_gray_5(v);
	}
}
void staight_55(int v,int g)//v  ����ı�ʶ   g��һ����ʶ
{
  if(biao[v]==0&&biao[g]==1)
	{
	chassis_staight_gray_55(v);
	}
}


void staight_556(int v,int g)//v  ����ı�ʶ   g��һ����ʶ
{
  if(biao[v]==0&&biao[g]==1)
	{
	chassis_staight_gray_556(v);
	}
}

void staight_5566(int v,int g)//v  ����ı�ʶ   g��һ����ʶ
{
  if(biao[v]==0&&biao[g]==1)
	{
	chassis_staight_gray_5566(v);
	}
}


void staight_6(int v,int g)//v  ����ı�ʶ   g��һ����ʶ
{
  if(biao[v]==0&&biao[g]==1)
	{
	chassis_staight_gray_6(v);
	}
}

void staight_pi(int v,int g)//v  ����ı�ʶ   g��һ����ʶ
{
  if(biao[v]==0&&biao[g]==1)
	{
	chassis_staight_gray_pu(v);
	}
}

void avv_jiu(int v,int g)
{
  if(biao[v]==0&&biao[g]==1)
	{
 jiu_zheng(v);
	}
}

void avv_jiu_2(int v,int g)
{
  if(biao[v]==0&&biao[g]==1)
	{
 jiu_zheng_2(v);
	}
}




void avv_jiu_y(int v,int g)
{
  if(biao[v]==0&&biao[g]==1)
	{
 jiu_zheng_y(v);
	}
}



int chassis_turn_ready(dd)
{
	falg2 = 0;
  //| key[2] ==1 && key[5] == 1
  if(key[10] ==1)
	{	
  if(dd==1)//��
	{
		chassis_move.speed_set[0] = left_go;
		chassis_move.speed_set[1] = left_go;	
		chassis_move.speed_set[2] = left_go;
		chassis_move.speed_set[3] = left_go;
   }
  if(dd==0)//��
   {
    chassis_move.speed_set[0] = right_go;
		chassis_move.speed_set[1] = right_go;	
		chassis_move.speed_set[2] = right_go;
		chassis_move.speed_set[3] = right_go;
   }
	}
	//| (key[2] ==0 && key[5] == 0)
	if(key[10] ==0)
	 {	
    falg1 = 1;
		falg2 = 0;
		return 0;
	 }
	  return 2;
}

int chassis_turn_go(int dd,int ff,int ci)
{
	if(dd==1)//��
	{
		chassis_move.speed_set[0] = left_go;
		chassis_move.speed_set[1] = left_go;	
		chassis_move.speed_set[2] = left_go;
		chassis_move.speed_set[3] = left_go;
  }
	if(dd==0)//��
	{
    chassis_move.speed_set[0] = right_go;
		chassis_move.speed_set[1] = right_go;	
		chassis_move.speed_set[2] = right_go;
		chassis_move.speed_set[3] = right_go;
  }
	//| (key[2] ==1 && key[5] == 1)
  if( key[10] ==1    )
	{	
	
		chassis_move.speed_set[0] = 0.0f;
		chassis_move.speed_set[1] = 0.0f;	
		chassis_move.speed_set[2] = 0.0f;
		chassis_move.speed_set[3] = 0.0f;
		falg1 = 0;
	  falg2 = 1;
		c++;
		if(c==ci)
		{
			c=0;
			biao[ff]=1;
		}
	
 	}
	
	
   return 0;
}


void chassis_turn (int xiang,int ci,int v)
{
		if(falg1 == 0 &&c<ci)
		{
		chassis_turn_ready(xiang);
		}		
		if(falg1 == 1 && falg2 == 0&&c<ci)
		{	
		chassis_turn_go(xiang,v,ci);
		}
		 if(ci==0)
		 biao[v]=1;
}


//�Ҷȼ��
void chassis_gary_loop()
{
    key[0]=GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_0);   //PA0
    key[1]=GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_1);   //PA1
    key[2]=GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_2);   //PA2
    key[3]=GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_3);   //PA3
    key[4]=GPIO_ReadInputDataBit(GPIOI,GPIO_Pin_5);   //PI5
    key[5]=GPIO_ReadInputDataBit(GPIOI,GPIO_Pin_6);   //PI6
    key[6]=GPIO_ReadInputDataBit(GPIOI,GPIO_Pin_7);   //PI7
    key[14]=GPIO_ReadInputDataBit(GPIOI,GPIO_Pin_2);   //PI12
	  key[8]=GPIO_ReadInputDataBit(GPIOH,GPIO_Pin_12);   //PH12
	  key[9]=GPIO_ReadInputDataBit(GPIOI,GPIO_Pin_0);   //PI0
	  key[10]=GPIO_ReadInputDataBit(GPIOH,GPIO_Pin_10);   //PI0
	  key[11]=GPIO_ReadInputDataBit(GPIOH,GPIO_Pin_11);   //PI0
	  key[12]=GPIO_ReadInputDataBit(GPIOD,GPIO_Pin_14);   //PI0
	  key[13]=GPIO_ReadInputDataBit(GPIOD,GPIO_Pin_15);   //PI0
	  //key[14]=GPIO_ReadInputDataBit(GPIOD,GPIO_Pin_12);   //PI0
	//  key[14]=GPIO_ReadInputDataBit(GPIOD,GPIO_Pin_13);   //PI0
	

}



void sevor_init()
{
	  servo_on(1);
}


void sevor_init2()
{
	  servo_on_1(15);
}

void sevor_on_1(int v,int g)
{
	if(biao[v]==0&&biao[g]==1)
	{
		chassis_move.speed_set[0] = 0.0f;
		chassis_move.speed_set[1] = 0.0f;	
		chassis_move.speed_set[2] = 0.0f;
		chassis_move.speed_set[3] = 0.0f;
		servo_on(1);
		//delay_ms(100);
	biao[v]=1;
	
	}
}
void sevor_on2_1(int v,int g)
{
	if(biao[v]==0&&biao[g]==1)
	{
		chassis_move.speed_set[0] = 0.0f;
		chassis_move.speed_set[1] = 0.0f;	
		chassis_move.speed_set[2] = 0.0f;
		chassis_move.speed_set[3] = 0.0f;
		servo_on_1(1);
		delay_ms(100);
	biao[v]=1;
	
	}
}

void stop(int v,int g)
{

		chassis_move.speed_set[0] = 0.0f;
		chassis_move.speed_set[1] = 0.0f;	
		chassis_move.speed_set[2] = 0.0f;
		chassis_move.speed_set[3] = 0.0f;
	
			//	delay_ms(150);//200

		
	   biao[v]=1;
	
	
}


void sevor_on_120(int v,int g)
{
	if(biao[v]==0&&biao[g]==1)
	{
		chassis_move.speed_set[0] = 0.0f;
		chassis_move.speed_set[1] = 0.0f;	
		chassis_move.speed_set[2] = 0.0f;
		chassis_move.speed_set[3] = 0.0f;
		 servo_on(150);
				delay_ms(120);//200
//		int16_t a,b,c,d;
//		for(a=0;a<1000;a++)
//		for(b=0;b<1000;b++)
//		for(c=0;c<1000;c++)
//		for(d=0;d<1000;d++)
		
	biao[v]=1;
	
	}
}
void sevor_on2_120(int v,int g)
{
	if(biao[v]==0&&biao[g]==1)
	{
		chassis_move.speed_set[0] = 0.0f;
		chassis_move.speed_set[1] = 0.0f;	
		chassis_move.speed_set[2] = 0.0f;
		chassis_move.speed_set[3] = 0.0f;
		 servo_on_1(60);
				delay_ms(150);//200
//		int16_t a,b,c,d;
//		for(a=0;a<1000;a++)
//		for(b=0;b<1000;b++)
//		for(c=0;c<1000;c++)
//		for(d=0;d<1000;d++)
		
	biao[v]=1;
	
	}
}

void sevor_on2_w(int v,int g)
{
	if(biao[v]==0&&biao[g]==1)
	{
		chassis_move.speed_set[0] = 0.0f;
		chassis_move.speed_set[1] = 0.0f;	
		chassis_move.speed_set[2] = 0.0f;
		chassis_move.speed_set[3] = 0.0f;
		 servo_on_1(120);
				delay_ms(150);//200
//		int16_t a,b,c,d;
//		for(a=0;a<1000;a++)
//		for(b=0;b<1000;b++)
//		for(c=0;c<1000;c++)
//		for(d=0;d<1000;d++)
		
	biao[v]=1;
	
	}
}

void sevor_on2_b(int v,int g)
{
	if(biao[v]==0&&biao[g]==1)
	{
		chassis_move.speed_set[0] = 0.0f;
		chassis_move.speed_set[1] = 0.0f;	
		chassis_move.speed_set[2] = 0.0f;
		chassis_move.speed_set[3] = 0.0f;
		 servo_on_1(55);
				delay_ms(150);//200
//		int16_t a,b,c,d;
//		for(a=0;a<1000;a++)
//		for(b=0;b<1000;b++)
//		for(c=0;c<1000;c++)
//		for(d=0;d<1000;d++)
		
	biao[v]=1;
	
	}
}



void sevor_on2_bule(int v,int g)
{
	if(biao[v]==0&&biao[g]==1)
	{
		chassis_move.speed_set[0] = 0.0f;
		chassis_move.speed_set[1] = 0.0f;	
		chassis_move.speed_set[2] = 0.0f;
		chassis_move.speed_set[3] = 0.0f;
		 servo_on_1(55);
				delay_ms(150);//200

		
	biao[v]=1;
	
	}
}

void sevor_on2_red(int v,int g)
{
	if(biao[v]==0&&biao[g]==1)
	{
		chassis_move.speed_set[0] = 0.0f;
		chassis_move.speed_set[1] = 0.0f;	
		chassis_move.speed_set[2] = 0.0f;
		chassis_move.speed_set[3] = 0.0f;
		 servo_on_1(65);
				delay_ms(150);//200

		
	biao[v]=1;
	
	}
}

void sevor_on2_g(int v,int g)
{
	if(biao[v]==0&&biao[g]==1)
	{
		chassis_move.speed_set[0] = 0.0f;
		chassis_move.speed_set[1] = 0.0f;	
		chassis_move.speed_set[2] = 0.0f;
		chassis_move.speed_set[3] = 0.0f;
		 servo_on_1(110);
				delay_ms(100);//200

		
	biao[v]=1;
	
	}
}


void sevor_on2_bb(int v,int g)
{
	if(biao[v]==0&&biao[g]==1)
	{
		chassis_move.speed_set[0] = 0.0f;
		chassis_move.speed_set[1] = 0.0f;	
		chassis_move.speed_set[2] = 0.0f;
		chassis_move.speed_set[3] = 0.0f;
		 servo_on_1(65);
				delay_ms(110);//200

		
	biao[v]=1;
	
	}
}


