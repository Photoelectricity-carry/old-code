//#include "LED.h"
////#include "stm32f10x_gpio.h"
////初始化PD.13和PG.14为输出口
////LED IO初始化
//	void LED_Init(void)
//{
//	GPIO_InitTypeDef GPIO_InitStructure;
//	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOD | RCC_APB2Periph_GPIOG,ENABLE);		//使能PD,PG端口时钟
//	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13;										//LED_0-->PD.13推挽输出
//	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
//	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
//	GPIO_Init(GPIOD,&GPIO_InitStructure);
//	GPIO_SetBits(GPIOD,GPIO_Pin_13);												//PD.13输出高
//	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_14;
//	GPIO_Init(GPIOG,&GPIO_InitStructure);
//	GPIO_SetBits(GPIOG,GPIO_Pin_14);											    //PG.14输出高
//}
//  //颜色识别为红色
//	void led_r(void)
//{
////	 while(1)
//	 {
//	 	LED_0 = 0;
//		LED_1 = 0;
//	 }
//}
//  //颜色识别为绿色
//	void led_g(void)
//{
////	while(1)
//	 {
//	 	LED_0 = 1;
//		LED_1 = 1;
//	 }
//}
//  //颜色识别为蓝色
//	void led_b(void)
//{
////	while(1)
//	 {
//	 	LED_0 = 0;
//		LED_1 = 1;
//	 }
//}
//  //颜色识别为白色
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
//  //颜色识别为黑色
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
