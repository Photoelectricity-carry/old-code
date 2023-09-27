#include "encoder.h"
#include "tim.h"

//��ʼ���������ṹ��
ecd_t ecd = {0};

//���������ʱ��
#define LEFT_ECD_TIM	TIM2
//���������ʱ��ֵ
#define LEFT_ECD_VAL	LEFT_ECD_TIM->CNT
//���������ʱ�����
#define hLEFT_ECD_TIM	htim2
//���������ʱ�����ָ��
#define phLEFT_ECD_TIM	&hLEFT_ECD_TIM

//�ұ�������ʱ��
#define RIGHT_ECD_TIM	TIM3
//�ұ�������ʱ��ֵ
#define RIGHT_ECD_VAL	RIGHT_ECD_TIM->CNT
//�ұ�������ʱ�����
#define hRIGHT_ECD_TIM	htim3
//�ұ�������ʱ�����ָ��
#define phRIGHT_ECD_TIM	&hRIGHT_ECD_TIM

//��ʱ��ʱ�����
#define hECD_TIMER		htim4
//��ʱ��ʱ�����ָ��
#define phECD_TIMER		&htim4
//��ʱ��ʱ��
#define ECD_TIMER		TIM4


/*��������ʼ��*/
void ecd_init(void){
	/*��������������*/
	HAL_TIM_Encoder_Start(phLEFT_ECD_TIM, TIM_CHANNEL_ALL);
	HAL_TIM_Encoder_Start(phRIGHT_ECD_TIM, TIM_CHANNEL_ALL);
	//�����Ĵ�������
	LEFT_ECD_VAL = RIGHT_ECD_VAL = 0;
	//��������������
	ecd.leftECD = ecd.rightECD = 0;
	//������ʱ���ж�
	HAL_TIM_Base_Start_IT(phECD_TIMER);
}

/*��ȡ�������ٶ�ֵ*/
void ecd_read_speed(ecd_t * pecd){
	//��ȡ�������ֵ
	pecd->leftECD = (int16_t)LEFT_ECD_VAL;
	//���������ʱ������
	LEFT_ECD_VAL = 0;
	
	//��ȡ�ұ�����ֵ
	pecd->rightECD = (int16_t)RIGHT_ECD_VAL;
	//�ұ�������ʱ������
	RIGHT_ECD_VAL = 0;
}


/*���ر������ṹ��ָ�뺯��*/
ecd_t * get_ecd_pointer(void){
	return &ecd;
}


void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim){
	if (htim->Instance == ECD_TIMER){
		ecd_read_speed(&ecd);
	}
}

