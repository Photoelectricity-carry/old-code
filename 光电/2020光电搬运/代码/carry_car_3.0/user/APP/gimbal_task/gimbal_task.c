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

//电机编码值规整 0—8191
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

//底盘初始化，主要是pid初始化
static void chassis_init(chassis_move_t *chassis_move_init);
//更新数据
static void chassis_feedback_update(chassis_move_t *chassis_move_update);
//定向移动
static void chassis_move_angle_1(void);
//定向移动
static void chassis_move_angle_2(void);
		
//前进巡线模式 1
static void chassis_staight_gray(int ff);
//前进巡线模式 2
static void chassis_staight_gray_2(int ff);
//前进巡线模式 3
static void chassis_staight_gray_3(int ff);

//后退巡线模式	
static void chassis_back_gray(int ff);
static void chassis_back_gray_long(int ff);
//左转准备模式
int chassis_turn_ready(int dd);	
	
int chassis_turn_go(int dd,int ff,int ci);
void chassis_turn(int xiang,int ci,int v);
		
void jiu_zheng(int v);

void jiu_zheng_2(int v);
void jiu_zheng_y(int v);



void colur_find(int ff,int yan);
void start_staight(int dd);
void turn(int v,int g,int xiang,int ci);
void staight_2(int v,int g);
void find_colur(int v,int g,int se);
void back_short(int v,int g);
void back_long(int v,int g);
void xingzoufangshi(int v,int g,int hh);

void staight_3(int v,int g);
void avv_jiu(int v,int g);
void avv_jiu_2(int v,int g);
void avv_jiu_y(int v,int g);



//PID计算
static void chassis_control_loop_1(chassis_move_t *chassis_move_control_loop);
//读取灰度
void chassis_gary_loop();




//底盘运动数据
chassis_move_t chassis_move;

int16_t count;
int16_t c=0;
int16_t falg1 = 0,falg2 = 0,falg3 = 0,falg4 = 0;
int16_t key[20];
int16_t w = 1;
int16_t biao[100]={0};
int16_t colur;
int16_t weizhi=1;
int16_t se[5]={green,white,red,black,blue};
int16_t zhi[5]={1,2,3,4,5};
int16_t zhuan=0,yan=10,zhuan_count=0,zhuan_xiang=0;
uint16_t cs = 0,cs1=0;
int16_t tese[2]={red,blue};
int16_t tesebiao[2]={0,0};
int16_t cun[3]={0};
int16_t wan[10]={0};
int16_t wn=0;
// 主任务
void GIMBAL_task(void *pvParameters)
{
	  //等待陀螺仪任务更新陀螺仪数据
    vTaskDelay(GIMBAL_TASK_INIT_TIME);
	  chassis_init(&chassis_move);
	  while (1)
    {
    led_green_on();		
		//底盘数据更新
    chassis_feedback_update(&chassis_move);
  	 //灰度返回函数
    chassis_gary_loop();
    //底盘控制函数
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
	  //底盘速度环pid值
    const static fp32 motor_speed_pid[3] = {M2006_MOTOR_SPEED_PID_KP, M2006_MOTOR_SPEED_PID_KI, M2006_MOTOR_SPEED_PID_KD};
		uint8_t i;			
	  //初始化PID 运动
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
				
     //更新电机速度，加速度是速度的PID微分
     chassis_move_update->motor_chassis[i].speed = chassis_move_update->motor_chassis[i].chassis_motor_measure->speed_rpm * Motor_RMP_TO_SPEED;
		
		
    //电机圈数重置， 因为输出轴旋转一圈， 电机轴旋转 36圈，将电机轴数据处理成输出轴数据，用于控制输出轴角度
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

    //计算输出轴角度
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
    //计算pid
//zhuan_xiang,zhuan_count
	  start_staight(1);//直走
    avv_jiu (2,1);
 //  avv_jiu_2(3,2);	
//		//biao[7]=1;
  turn(3,2,zuo,2);//转弯90	
  	avv_jiu (4,3);
		staight_2(5,4);		//前进中间
//		find_colur(6,5,blue );//抓取  颜色识别				//第一个颜色 蓝色
//		back_short(7,6);		//后退
//		avv_jiu (8,7);
//    turn(9,8,zhuan_xiang,zhuan_count);//转弯到相应
//		avv_jiu (10,9);
//    xingzoufangshi(11,10,1);	//	判断是行走方式
//    if(wan[1]==2)
//			{
//		staight_2(12,11);	
//		find_colur(13,12,red );//抓取  颜色识别				//第2个颜色 红色
//		back_short(14,13);		//后退
//		avv_jiu (15,14);
//    turn(16,15,zhuan_xiang,zhuan_count);//转弯到相应
//		avv_jiu (17,16);
//		xingzoufangshi(18,17,2);	//	判断是行走方式		


				for (i = 0; i < 4; i++)
    {   
			  chassis_move_control_loop->motor_chassis[i].speed_set = chassis_move.speed_set[i];
        PID_Calc(&chassis_move_control_loop->motor_speed_pid[i], chassis_move_control_loop->motor_chassis[i].speed, chassis_move_control_loop->motor_chassis[i].speed_set);
    }		
     //赋值电流值
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
	 //停车后退
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
	//  colur = clour_disguish();
	colur=yanse ;
	if(yan!=colur)
	{
		for (aa=0;aa<5;aa++)
		{
			 if(colur==se[aa])
			{
	
			zhuan=(weizhi-zhi[aa])*45;//顺时针小于0	
			if(weizhi-zhi[aa]<0)//顺时针
				{
			zhuan_count= zhi[aa]-weizhi;
			zhuan_xiang=you ;}
			if(weizhi-zhi[aa]>0)//逆时针
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


// 前进巡线模式
static void chassis_staight_gray(int ff)
{
	
		  chassis_move.speed_set[0] = left_go;
			chassis_move.speed_set[1] = left_go;	
			chassis_move.speed_set[2] = right_go;
			chassis_move.speed_set[3] = right_go;
	 
			if(key[1] == 1 && key[0] == 0)
			{		
			   chassis_move.speed_set[0] = left_go_cha;
				 chassis_move.speed_set[1] = left_go_cha;	
				 chassis_move.speed_set[2] = right_go;
				 chassis_move.speed_set[3] = right_go;		
			}
			if(key[15] == 1 && key[14] == 0)
			{		
			   chassis_move.speed_set[0] = 6.0;
				 chassis_move.speed_set[1] = 6.0;	
				 chassis_move.speed_set[2] = right_go;
				 chassis_move.speed_set[3] = right_go;		
			}			
			
			
			
			if(key[0] == 1 && key[1] == 0)
			{			
			   chassis_move.speed_set[0] = left_go;
				 chassis_move.speed_set[1] = left_go;	
				 chassis_move.speed_set[2] = right_go_cha;
  			 chassis_move.speed_set[3] = right_go_cha;
			}
			if(key[14] == 1 && key[15] == 0)
			{			
			   chassis_move.speed_set[0] = left_go;
				 chassis_move.speed_set[1] = left_go;	
				 chassis_move.speed_set[2] = -6.0;
  			 chassis_move.speed_set[3] = -6.0;
			}
			
			
			
			
			if(  key[8] == 1)				
			{
				cs1=1;
				if(cs==4){
				 chassis_move.speed_set[0] = 0.0f;
				 chassis_move.speed_set[1] = 0.0f;	
				 chassis_move.speed_set[2] = 0.0f;
  			 chassis_move.speed_set[3] = 0.0f;	
			   biao[ff]=1;
				 cs=0;
				 cs1=0;
				}
			}
			if(   key[8] == 0)				
			{ 
				if(cs1==1)
			  {
				   cs=cs+1;
					cs1=0;
				}
			}
			
}
// 前进巡线模式3
static void chassis_staight_gray_3(int ff)
{
		  chassis_move.speed_set[0] = left_go;
			chassis_move.speed_set[1] = left_go;	
			chassis_move.speed_set[2] = right_go;
			chassis_move.speed_set[3] = right_go;
	 
			if(key[1] == 1 && key[0] == 0)
			{		
			   chassis_move.speed_set[0] = left_go_cha;
				 chassis_move.speed_set[1] = left_go_cha;	
				 chassis_move.speed_set[2] = right_go;
				 chassis_move.speed_set[3] = right_go;		
			}
			if(key[0] == 1 && key[1] == 0)
			{			
			   chassis_move.speed_set[0] = left_go;
				 chassis_move.speed_set[1] = left_go;	
				 chassis_move.speed_set[2] = right_go_cha;
  			 chassis_move.speed_set[3] = right_go_cha;
			}
			if(  key[10] == 1 && key[11] == 1)				
			{
				cs1=1;
				if(cs==2){
				 chassis_move.speed_set[0] = 0.0f;
				 chassis_move.speed_set[1] = 0.0f;	
				 chassis_move.speed_set[2] = 0.0f;
  			 chassis_move.speed_set[3] = 0.0f;	
			   biao[ff]=1;
				 cs=0;
				 cs1=0;
				}
			}
			if(  key[10] == 0 && key[11] == 0)				
			{ 
				if(cs1==1)
			  {
				   cs=cs+1;
					cs1=0;
				}
			}
	  
}






// 前进巡线模式2
static void chassis_staight_gray_2(int ff)
 {
		  chassis_move.speed_set[0] = left_go_slow;
			chassis_move.speed_set[1] = left_go_slow;	
			chassis_move.speed_set[2] = right_go_slow;
			chassis_move.speed_set[3] = right_go_slow;
	 
			if(key[1] == 1 && key[0] == 0)
			{		
			   chassis_move.speed_set[0] = left_go_cha_slow;
				 chassis_move.speed_set[1] = left_go_cha_slow;	
				 chassis_move.speed_set[2] = right_go_slow;
				 chassis_move.speed_set[3] = right_go_slow;		
			}
			if(key[0] == 1 && key[1] == 0)
			{			
			   chassis_move.speed_set[0] = left_go_slow;
				 chassis_move.speed_set[1] = left_go_slow;	
				 chassis_move.speed_set[2] = right_go_cha_slow;
  			 chassis_move.speed_set[3] = right_go_cha_slow;
			}
			
			
			if(key[15] == 1 && key[14] == 0)
			{			
			   chassis_move.speed_set[0] = 4.0;
				 chassis_move.speed_set[1] = 4.0;	
				 chassis_move.speed_set[2] = -6.0;
  			 chassis_move.speed_set[3] = -6.0;
			}
			
			if(key[14] == 1 && key[15] == 0)
			{		
			   chassis_move.speed_set[0] = 6.0;
				 chassis_move.speed_set[1] = 6.0;	
				 chassis_move.speed_set[2] = -4.0;
				 chassis_move.speed_set[3] = -4.0;		
			}	
			
//			if( (key[6] == 1 && key[7] == 1) || (key[6] == 1 && key[10] == 1) || (key[7] == 1 && key[11] == 1) ||(key[10] == 1 && key[11] == 1))				
//			{
//				 chassis_move.speed_set[0] = 0.0f;
//				 chassis_move.speed_set[1] = 0.0f;	
//				 chassis_move.speed_set[2] = 0.0f;
//  			 chassis_move.speed_set[3] = 0.0f;	
//			  biao[ff]=1;
//			}
			
			
			
			if( key[10] == 1 && key[11] == 1)				
			{
				 chassis_move.speed_set[0] = 0.0f;
				 chassis_move.speed_set[1] = 0.0f;	
				 chassis_move.speed_set[2] = 0.0f;
  			 chassis_move.speed_set[3] = 0.0f;	
			  biao[ff]=1;
			}			

		}


// 倒退巡线模式
static void chassis_back_gray(int ff)
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
	
			
			if(  key[4] == 1 )				
			{
//				cs1=1;
//				if(cs==2){
				 chassis_move.speed_set[0] = 0.0f;
				 chassis_move.speed_set[1] = 0.0f;	
				 chassis_move.speed_set[2] = 0.0f;
  			 chassis_move.speed_set[3] = 0.0f;	
			   biao[ff]=1;
//				 cs=0;
//				 cs1=0;
				}
	//		}
//			if( key[5] == 0 )				
//			{ 
//				if(cs1==1)
//			  {
//				   cs=cs+1;
//					cs1=0;
//					//cs1=2;
//				}			}
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

void turn(int v,int g,int xiang,int ci)//v  这个的标识   g上一个标识
{
  if(biao[v]==0&&biao[g]==1)
	{
	chassis_turn(xiang,ci,v);  //左转90
	}
}
void staight_2(int v,int g)//v  这个的标识   g上一个标识
{
  if(biao[v]==0&&biao[g]==1)//3 2
	{
    //	chassis_turn(you,2,v);
		chassis_staight_gray_2(v); //直行
	}
}
void find_colur(int v,int g,int se)//v  这个的标识   g上一个标识
{
  if(biao[v]==0&&biao[g]==1)//3 2
	{
		colur_find(v,se);
	}
}

void back_short(int v,int g)//v  这个的标识   g上一个标识
{
  if(biao[v]==0&&biao[g]==1)
	{
	chassis_back_gray(v);
	}
}

void back_long(int v,int g)//v  这个的标识   g上一个标识
{
  if(biao[v]==0&&biao[g]==1)
	{
	chassis_back_gray_long(v);
	}
}


void xingzoufangshi(int v,int g,int hh)//v  这个的标识   g上一个标识
{
  if(biao[v]==0&&biao[g]==1)//3 2
	{

    ////	chassis_turn(you,2,v);
		//or (wn=0;wn<2;wn++){
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

void staight_3(int v,int g)//v  这个的标识   g上一个标识
{
  if(biao[v]==0&&biao[g]==1)
	{
	chassis_staight_gray_3(v);
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
  if(key[12] ==1)
	{	
  if(dd==1)//右
	{
		chassis_move.speed_set[0] = left_go;
		chassis_move.speed_set[1] = left_go;	
		chassis_move.speed_set[2] = left_go;
		chassis_move.speed_set[3] = left_go;
   }
  if(dd==0)//左
   {
    chassis_move.speed_set[0] = right_go;
		chassis_move.speed_set[1] = right_go;	
		chassis_move.speed_set[2] = right_go;
		chassis_move.speed_set[3] = right_go;
   }
	}
	//| (key[2] ==0 && key[5] == 0)
	if(key[12] ==0)
	 {	
    falg1 = 1;
		falg2 = 0;
		return 0;
	 }
	  return 2;
}

int chassis_turn_go(int dd,int ff,int ci)
{
	if(dd==1)//右
	{
		chassis_move.speed_set[0] = left_go;
		chassis_move.speed_set[1] = left_go;	
		chassis_move.speed_set[2] = left_go;
		chassis_move.speed_set[3] = left_go;
  }
	if(dd==0)//左
	{
    chassis_move.speed_set[0] = right_go;
		chassis_move.speed_set[1] = right_go;	
		chassis_move.speed_set[2] = right_go;
		chassis_move.speed_set[3] = right_go;
  }
	//| (key[2] ==1 && key[5] == 1)
  if( key[12] ==1    )
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


//灰度检测
void chassis_gary_loop()
{
    key[0]=GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_0);   //PA0
    key[1]=GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_1);   //PA1
    key[2]=GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_2);   //PA2
    key[3]=GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_3);   //PA3
    key[4]=GPIO_ReadInputDataBit(GPIOI,GPIO_Pin_5);   //PI5
    key[5]=GPIO_ReadInputDataBit(GPIOI,GPIO_Pin_6);   //PI6
    key[6]=GPIO_ReadInputDataBit(GPIOI,GPIO_Pin_7);   //PI7
    key[7]=GPIO_ReadInputDataBit(GPIOI,GPIO_Pin_2);   //PI12
	  key[8]=GPIO_ReadInputDataBit(GPIOH,GPIO_Pin_12);   //PH12
	  key[9]=GPIO_ReadInputDataBit(GPIOI,GPIO_Pin_0);   //PI0
	  key[10]=GPIO_ReadInputDataBit(GPIOH,GPIO_Pin_10);   //PI0
	  key[11]=GPIO_ReadInputDataBit(GPIOH,GPIO_Pin_11);   //PI0
	  key[12]=GPIO_ReadInputDataBit(GPIOD,GPIO_Pin_14);   //PI0
	  key[13]=GPIO_ReadInputDataBit(GPIOD,GPIO_Pin_15);   //PI0
	  key[14]=GPIO_ReadInputDataBit(GPIOD,GPIO_Pin_12);   //PI0
	  key[15]=GPIO_ReadInputDataBit(GPIOD,GPIO_Pin_13);   //PI0

}
