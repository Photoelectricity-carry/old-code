#include "encoder.h"
#include "tim.h"

//³õÊ¼»¯±àÂëÆ÷½á¹¹Ìå
ecd_t ecd = {0};

//×ó±àÂëÆ÷¶¨Ê±Æ÷
#define LEFT_ECD_TIM	TIM2
//×ó±àÂëÆ÷¶¨Ê±Æ÷Öµ
#define LEFT_ECD_VAL	LEFT_ECD_TIM->CNT
//×ó±àÂëÆ÷¶¨Ê±Æ÷¾ä±ú
#define hLEFT_ECD_TIM	htim2
//×ó±àÂëÆ÷¶¨Ê±Æ÷¾ä±úÖ¸Õë
#define phLEFT_ECD_TIM	&hLEFT_ECD_TIM

//ÓÒ±àÂëÆ÷¶¨Ê±Æ÷
#define RIGHT_ECD_TIM	TIM3
//ÓÒ±àÂëÆ÷¶¨Ê±Æ÷Öµ
#define RIGHT_ECD_VAL	RIGHT_ECD_TIM->CNT
//ÓÒ±àÂëÆ÷¶¨Ê±Æ÷¾ä±ú
#define hRIGHT_ECD_TIM	htim3
//ÓÒ±àÂëÆ÷¶¨Ê±Æ÷¾ä±úÖ¸Õë
#define phRIGHT_ECD_TIM	&hRIGHT_ECD_TIM

//¼ÆÊ±¶¨Ê±Æ÷¾ä±ú
#define hECD_TIMER		htim4
//¼ÆÊ±¶¨Ê±Æ÷¾ä±úÖ¸Õë
#define phECD_TIMER		&htim4
//¼ÆÊ±¶¨Ê±Æ÷
#define ECD_TIMER		TIM4


/*±àÂëÆ÷³õÊ¼»¯*/
void ecd_init(void){
	/*¿ªÆô±àÂëÆ÷¼ÆÊý*/
	HAL_TIM_Encoder_Start(phLEFT_ECD_TIM, TIM_CHANNEL_ALL);
	HAL_TIM_Encoder_Start(phRIGHT_ECD_TIM, TIM_CHANNEL_ALL);
	//¼ÆÊý¼Ä´æÆ÷ÇåÁã
	LEFT_ECD_VAL = RIGHT_ECD_VAL = 0;
	//±àÂëÆ÷±äÁ¿ÇåÁã
	ecd.leftECD = ecd.rightECD = 0;
	//¿ªÆô¶¨Ê±Æ÷ÖÐ¶Ï
	HAL_TIM_Base_Start_IT(phECD_TIMER);
}

/*¶ÁÈ¡±àÂëÆ÷ËÙ¶ÈÖµ*/
void ecd_read_speed(ecd_t * pecd){
	//¶ÁÈ¡×ó±àÂëÆ÷Öµ
	pecd->leftECD = (int16_t)LEFT_ECD_VAL;
	//×ó±àÂëÆ÷¶¨Ê±Æ÷ÇåÁã
	LEFT_ECD_VAL = 0;
	
	//¶ÁÈ¡ÓÒ±àÂëÆ÷Öµ
	pecd->rightECD = (int16_t)RIGHT_ECD_VAL;
	//ÓÒ±àÂëÆ÷¶¨Ê±Æ÷ÇåÁã
	RIGHT_ECD_VAL = 0;
}


/*·µ»Ø±àÂëÆ÷½á¹¹ÌåÖ¸Õëº¯Êý*/
ecd_t * get_ecd_pointer(void){
	return &ecd;
}


void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim){
	if (htim->Instance == ECD_TIMER){
		ecd_read_speed(&ecd);
	}
}

