//#include "LED.h"
////#include "stm32f10x_gpio.h"
////��ʼ��PD.13��PG.14Ϊ�����
////LED IO��ʼ��
//	void LED_Init(void)
//{
//	GPIO_InitTypeDef GPIO_InitStructure;
//	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOD | RCC_APB2Periph_GPIOG,ENABLE);		//ʹ��PD,PG�˿�ʱ��
//	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13;										//LED_0-->PD.13�������
//	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
//	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
//	GPIO_Init(GPIOD,&GPIO_InitStructure);
//	GPIO_SetBits(GPIOD,GPIO_Pin_13);												//PD.13�����
//	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_14;
//	GPIO_Init(GPIOG,&GPIO_InitStructure);
//	GPIO_SetBits(GPIOG,GPIO_Pin_14);											    //PG.14�����
//}
//  //��ɫʶ��Ϊ��ɫ
//	void led_r(void)
//{
////	 while(1)
//	 {
//	 	LED_0 = 0;
//		LED_1 = 0;
//	 }
//}
//  //��ɫʶ��Ϊ��ɫ
//	void led_g(void)
//{
////	while(1)
//	 {
//	 	LED_0 = 1;
//		LED_1 = 1;
//	 }
//}
//  //��ɫʶ��Ϊ��ɫ
//	void led_b(void)
//{
////	while(1)
//	 {
//	 	LED_0 = 0;
//		LED_1 = 1;
//	 }
//}
//  //��ɫʶ��Ϊ��ɫ
//	void led_w(void)
//{
////	while(1)
//	 {
//	 	LED_0 = 0;
//		LED_1 = 0;
//		delay_ms(1000);
//		LED_0 = 1;
//		LED_1 = 0;
//		delay_ms(1000);


//	 }
//}
//  //��ɫʶ��Ϊ��ɫ
//	void led_black(void)
//{
////	while(1)
//	 {
//	 	LED_0 = 1;
//		LED_1 = 0;
////		delay_ms(1000);
////		LED_0 = 1;
////		LED_1 = 1;
////		delay_ms(1000);

//	 }
//}
