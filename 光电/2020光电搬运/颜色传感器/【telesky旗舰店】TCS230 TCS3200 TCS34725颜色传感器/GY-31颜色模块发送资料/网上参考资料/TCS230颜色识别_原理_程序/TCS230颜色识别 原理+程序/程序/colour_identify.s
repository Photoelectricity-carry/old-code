	.module colour_identify.c
	.area data(ram, con, rel)
_AC_TABLE::
	.blkb 2
	.area idata
	.byte 128,129
	.area data(ram, con, rel)
	.blkb 2
	.area idata
	.byte 130,131
	.area data(ram, con, rel)
	.blkb 2
	.area idata
	.byte 132,133
	.area data(ram, con, rel)
	.blkb 2
	.area idata
	.byte 134,135
	.area data(ram, con, rel)
	.blkb 2
	.area idata
	.byte 144,145
	.area data(ram, con, rel)
	.blkb 2
	.area idata
	.byte 146,147
	.area data(ram, con, rel)
	.blkb 2
	.area idata
	.byte 148,149
	.area data(ram, con, rel)
	.blkb 2
	.area idata
	.byte 150,151
	.area data(ram, con, rel)
	.blkb 2
	.area idata
	.byte 136,137
	.area data(ram, con, rel)
	.blkb 2
	.area idata
	.byte 138,139
	.area data(ram, con, rel)
	.blkb 2
	.area idata
	.byte 140,141
	.area data(ram, con, rel)
	.blkb 2
	.area idata
	.byte 142,143
	.area data(ram, con, rel)
	.blkb 2
	.area idata
	.byte 152,153
	.area data(ram, con, rel)
	.blkb 2
	.area idata
	.byte 154,155
	.area data(ram, con, rel)
	.blkb 2
	.area idata
	.byte 156,157
	.area data(ram, con, rel)
	.blkb 2
	.area idata
	.byte 158,159
	.area data(ram, con, rel)
	.dbfile C:\DOCUME~1\Administrator\桌面\程序/12864.h
	.dbsym e AC_TABLE _AC_TABLE A[32:32]c
	.area text(rom, con, rel)
	.dbfile C:\DOCUME~1\Administrator\桌面\程序/12864.h
	.dbfunc e delay_us _delay_us fV
;              i -> R20,R21
;              j -> R22,R23
;              t -> R16,R17
	.even
_delay_us::
	xcall push_gset2
	.dbline -1
	.dbline 59
; /*******************************************
; * 文件名： 
; * 功能： 
; * 说明： 
; /********************************************/
; #include <iom128v.h>
; #include <macros.h>
; #include "12864.h"
; 
; //颜色识别器色光滤波器选择：红色(S2,S3=0,0)，蓝色(S2,S3=0,1)，绿色(S2,S3=1,1)
; #define S2 _PC7
; #define S3 _PC6
; 
; //变量、常量定义
; volatile uchar red=0,blue=0,green=0,flag=0,i=0,j=0,data[5]={0};
; volatile uint counter=0;
; 
; //中断定义
; #pragma interrupt_handler interrupt_int2:4 
; #pragma interrupt_handler interrupt_timer1:15
; 
; /*******************************************
; * 函数名称: int2_init()
; * 函数功能: 外部中断2初始化
; * 入口参数: 无
; * 出口参数: 无
; /********************************************/
; void int2_init() 
; {
;    DDRD &= ~BIT(2);//中断引脚设置为输入
;    PORTD |= BIT(2); //设置输出口上拉
;    EICRA = 0X20; //下降沿触发
; }
; 
; /*******************************************
; * 函数名称: timer1_init()
; * 函数功能: 定时器1初始化
; * 入口参数: 无
; * 出口参数: 无
; /********************************************/
; void timer1_init()
; {
;     TCCR1B = 0X02;// 设置分频数为8
; 	TCNT1H = 0x63;// 设置计数初值, 定时20ms
;     TCNT1L = 0xC0;
; }
; /*******************************************
; * 函数名称: port_init()
; * 函数功能: 端口初始化
; * 入口参数: 无
; * 出口参数: 无
; /********************************************/
; void port_init()
; {
;    DDRA = 0XFF;//PORTA3~0为液晶数据线
;    DDRC = 0XFF;//控制S2与S3  
; }
; 
; /*******************************************
	.dbline 61
; * 函数名称:  main()
; /********************************************/
	movw R20,R16
	xjmp L5
L2:
	.dbline 62
	ldi R22,2
	ldi R23,0
	xjmp L9
L6:
	.dbline 62
L7:
	.dbline 62
	subi R22,1
	sbci R23,0
L9:
	.dbline 62
	cpi R22,0
	cpc R22,R23
	brne L6
X0:
L3:
	.dbline 61
	subi R20,1
	sbci R21,0
L5:
	.dbline 61
	cpi R20,0
	cpc R20,R21
	brne L2
X1:
	.dbline -2
L1:
	xcall pop_gset2
	.dbline 0 ; func end
	ret
	.dbsym r i 20 i
	.dbsym r j 22 i
	.dbsym r t 16 i
	.dbend
	.dbfunc e delay_ms _delay_ms fV
;              i -> R20,R21
;              j -> R22,R23
;              t -> R16,R17
	.even
_delay_ms::
	xcall push_gset2
	.dbline -1
	.dbline 73
; void main(void)
; {   
;    port_init();
;    int2_init();
;    timer1_init();
;    Init_12864();  
;    LcmClearTXT(); //文本区清RAM函数
;    Display_x_y_data(0,0,"颜色识别：");
;    Display_x_y_data(1,0,"红色成分：");
;    Display_x_y_data(2,0,"蓝色成分：");
;    Display_x_y_data(3,0,"绿色成分：");
;    S2=0;//先检测红色(S2,S3=0,0)
	.dbline 75
;    S3=0;
;    SEI();
	movw R20,R16
	xjmp L14
L11:
	.dbline 76
	ldi R22,2800
	ldi R23,10
	xjmp L18
L15:
	.dbline 76
L16:
	.dbline 76
	subi R22,1
	sbci R23,0
L18:
	.dbline 76
	cpi R22,0
	cpc R22,R23
	brne L15
X2:
L12:
	.dbline 75
	subi R20,1
	sbci R21,0
L14:
	.dbline 75
	cpi R20,0
	cpc R20,R21
	brne L11
X3:
	.dbline -2
L10:
	xcall pop_gset2
	.dbline 0 ; func end
	ret
	.dbsym r i 20 i
	.dbsym r j 22 i
	.dbsym r t 16 i
	.dbend
	.dbfunc e Sendbyte _Sendbyte fV
;              i -> R20
;           data -> R22
	.even
_Sendbyte::
	xcall push_gset2
	mov R22,R16
	.dbline -1
	.dbline 87
;    EIMSK |= BIT(2); //打开外部中断
;    TIMSK |=  BIT(2);//打开溢出中断
;    while(1);  
; }
; 
;  /*******************************************
; * 函数名称:  interrupt_int2()  
; * 函数功能: 
; * 入口参数: 无
; * 出口参数: 无
; /********************************************/
; void interrupt_int2()  
	.dbline 88
; {  
	clr R20
	.dbline 89
; 	counter++;
	.dbline 90
; }
	ldi R16,8
	ldi R17,0
	xcall _delay_us
	.dbline 91
; 
	xjmp L23
L20:
	.dbline 92
; /*******************************************
	.dbline 93
; * 函数名称: interrupt_timer1()
	sbrs R22,7
	rjmp L24
	.dbline 94
; * 函数功能: 
	in R24,0x1b
	ori R24,2
	out 0x1b,R24
	xjmp L25
L24:
	.dbline 96
; * 入口参数: 无
; * 出口参数: 无
	in R24,0x1b
	andi R24,253
	out 0x1b,R24
L25:
	.dbline 97
	in R24,0x1b
	ori R24,4
	out 0x1b,R24
	.dbline 98
	ldi R16,8
	ldi R17,0
	xcall _delay_us
	.dbline 99
	lsl R22
	.dbline 100
	in R24,0x1b
	andi R24,251
	out 0x1b,R24
	.dbline 101
	ldi R16,8
	ldi R17,0
	xcall _delay_us
	.dbline 102
L21:
	.dbline 91
	inc R20
L23:
	.dbline 91
	cpi R20,8
	brlo L20
	.dbline -2
L19:
	xcall pop_gset2
	.dbline 0 ; func end
	ret
	.dbsym r i 20 c
	.dbsym r data 22 c
	.dbend
	.dbfunc e Receivebyte _Receivebyte fc
;          temp2 -> R16
;          temp1 -> R18
;              i -> R20
	.even
_Receivebyte::
	xcall push_gset1
	.dbline -1
	.dbline 113
; /********************************************/
; void interrupt_timer1()
; {
;     CLI();//关总中断
;     TCCR1B = 0X00;//定时器停止工作
; 	TIMSK &= ~ BIT(2);//关闭溢出中断
; 	EIMSK &= ~BIT(2); //关闭外部中断      	
; 	flag++;//实现先检测红色,再检测蓝色,然后检测绿色,循环检测
; 	if(flag==1)
; 	{   		 
; 		 red=counter;
; 		 data[0]=counter/100+0x30;		 
; 		 counter=counter%100;
; 		 data[1]=counter/10+0x30;
; 		 counter=counter%10;
; 		 data[2]=counter+0x30;		
;    		 Locate_x_y(1,5);	
	.dbline 115
;    		 for(i=0;i<3;i++)	    
; 	     		 Writedata(data[i]);    		
	clr R16
	clr R18
	.dbline 116
; 		S2=0;//下次检测蓝色(S2,S3=0,1)
	clr R20
	xjmp L30
L27:
	.dbline 117
; 		S3=1;		
	.dbline 118
; 	}
	lsl R18
	.dbline 119
; 	else if(flag==2)
	in R24,0x1b
	andi R24,251
	out 0x1b,R24
	.dbline 120
; 	{
	in R24,0x1b
	ori R24,4
	out 0x1b,R24
	.dbline 121
;    		 blue=counter;
	in R24,0x1b
	andi R24,251
	out 0x1b,R24
	.dbline 122
; 		 data[0]=counter/100+0x30;		 
	in R24,0x1b
	lsr R24
	andi R24,1
	breq L31
	.dbline 122
	inc R18
L31:
	.dbline 123
L28:
	.dbline 116
	inc R20
L30:
	.dbline 116
	cpi R20,8
	brlo L27
	.dbline 124
; 		 counter=counter%100;
; 		 data[1]=counter/10+0x30;
	clr R20
	xjmp L36
L33:
	.dbline 125
; 		 counter=counter%10;
	.dbline 126
; 		 data[2]=counter+0x30;		
	lsl R16
	.dbline 127
;    		 Locate_x_y(2,5);	
	in R24,0x1b
	andi R24,251
	out 0x1b,R24
	.dbline 128
;    		 for(i=0;i<3;i++)	    
	in R24,0x1b
	ori R24,4
	out 0x1b,R24
	.dbline 129
; 	     		 Writedata(data[i]);    			
	in R24,0x1b
	andi R24,251
	out 0x1b,R24
	.dbline 130
; 		S2=1;//下次检测绿色(S2,S3=1,1)
	in R24,0x1b
	lsr R24
	andi R24,1
	breq L37
	.dbline 130
	inc R16
L37:
	.dbline 131
L34:
	.dbline 124
	inc R20
L36:
	.dbline 124
	cpi R20,8
	brlo L33
	.dbline 132
; 		S3=1;
; 	}
	mov R24,R16
	andi R24,15
	mov R16,R18
	andi R16,240
	add R16,R24
	.dbline -2
L26:
	xcall pop_gset1
	.dbline 0 ; func end
	ret
	.dbsym r temp2 16 c
	.dbsym r temp1 18 c
	.dbsym r i 20 c
	.dbend
	.dbfunc e Checkbusy _Checkbusy fV
	.even
_Checkbusy::
	.dbline -1
	.dbline 142
;     else if(flag==3)
; 	{
;    		 green=counter;
; 		 data[0]=counter/100+0x30;		 
; 		 counter=counter%100;
; 		 data[1]=counter/10+0x30;
; 		 counter=counter%10;
; 		 data[2]=counter+0x30;	
;    		 Locate_x_y(3,5);	
;    		 for(i=0;i<3;i++)	    
L40:
	.dbline 143
; 	     		 Writedata(data[i]);   				 
	ldi R16,252
	xcall _Sendbyte
L41:
	.dbline 144
; 		S2=0;//下次检测红色(S2,S3=0,0)
	xcall _Receivebyte
	sbrc R16,7
	rjmp L40
	.dbline -2
L39:
	.dbline 0 ; func end
	ret
	.dbend
	.dbfunc e Writecommand _Writecommand fV
;           data -> R20
	.even
_Writecommand::
	xcall push_gset1
	mov R20,R16
	.dbline -1
	.dbline 154
; 		S3=0;
; 	}
; 	else if(flag==4) 
; 	{      
; 	     flag=0;		 
; 		 if((red+5)>(blue+green))		 
; 		     Display_x_y_data(0,5,"红色");
; 		 else if((blue+8>red)&&(blue+2>green))
; 		     Display_x_y_data(0,5,"蓝色");		
; 		 else if((green-3<red)&&(green-15>blue))
	.dbline 155
; 		     Display_x_y_data(0,5,"黄色");	  	
	in R24,0x1b
	ori R24,1
	out 0x1b,R24
	.dbline 156
; 		 else if((green+5>red)&&(green>blue))
	xcall _Checkbusy
	.dbline 157
; 		     Display_x_y_data(0,5,"绿色");		   
	ldi R16,248
	xcall _Sendbyte
	.dbline 158
; 		/*else if((blue>red)&&(green>blue))
	mov R16,R20
	andi R16,240
	xcall _Sendbyte
	.dbline 159
; 		     Display_x_y_data(0,5,"白色");*/
	mov R16,R20
	andi R16,15
	andi R16,#0x0F
	swap R16
	xcall _Sendbyte
	.dbline 160
; 		 else
	in R24,0x1b
	andi R24,254
	out 0x1b,R24
	.dbline -2
L43:
	xcall pop_gset1
	.dbline 0 ; func end
	ret
	.dbsym r data 20 c
	.dbend
	.dbfunc e Writedata _Writedata fV
;           data -> R20
	.even
_Writedata::
	xcall push_gset1
	mov R20,R16
	.dbline -1
	.dbline 169
; 		     Display_x_y_data(0,5,"未知");		 
; 	}
; 	//delay_ms(200); 
; 	counter = 0;//清零外中断计数标志		
; 	TCCR1B = 0X02;// 设置分频数为8
; 	TCNT1H = 0x63;//重新装入初值
;     TCNT1L = 0xC0;
; 	TIMSK |=  BIT(2);//打开溢出中断
; 	EIMSK |= BIT(2); //打开外部中断		
	.dbline 170
; 	SEI();//开总中断
	in R24,0x1b
	ori R24,1
	out 0x1b,R24
	.dbline 171
; }
	xcall _Checkbusy
	.dbline 172
; }
	ldi R16,250
	xcall _Sendbyte
	.dbline 173
; }
	mov R16,R20
	andi R16,240
	xcall _Sendbyte
	.dbline 174
; }
	mov R16,R20
	andi R16,15
	andi R16,#0x0F
	swap R16
	xcall _Sendbyte
	.dbline 175
; }
	in R24,0x1b
	andi R24,254
	out 0x1b,R24
	.dbline -2
L44:
	xcall pop_gset1
	.dbline 0 ; func end
	ret
	.dbsym r data 20 c
	.dbend
	.dbfunc e Locate_x_y _Locate_x_y fV
;           addr -> R20
;              y -> R22
;              x -> R10
	.even
_Locate_x_y::
	xcall push_gset3
	mov R22,R18
	mov R10,R16
	.dbline -1
	.dbline 185
; }
; }
; }
; }
; }
; }
; }
; }
; }
; }
	.dbline 186
; }
	ldi R20,128
	.dbline 187
; }
	ldi R16,128
	xcall _Writecommand
	.dbline 188
; }
	clr R11
	tst R10
	brne X4
	tst R11
	breq L49
X4:
	movw R24,R10
	cpi R24,1
	ldi R30,0
	cpc R25,R30
	breq L50
	cpi R24,2
	ldi R30,0
	cpc R25,R30
	breq L51
	cpi R24,3
	ldi R30,0
	cpc R25,R30
	breq L52
	xjmp L47
X5:
	.dbline 189
; }
L49:
	.dbline 190
; }
	mov R20,R22
	subi R20,128    ; addi 128
	.dbline 190
	xjmp L47
L50:
	.dbline 191
; }
	mov R20,R22
	subi R20,112    ; addi 144
	.dbline 191
	xjmp L47
L51:
	.dbline 192
; }
	mov R20,R22
	subi R20,120    ; addi 136
	.dbline 192
	xjmp L47
L52:
	.dbline 193
; }
	mov R20,R22
	subi R20,104    ; addi 152
	.dbline 193
	.dbline 194
; }
L47:
	.dbline 196
; }
; }
	mov R16,R20
	xcall _Writecommand
	.dbline -2
L45:
	xcall pop_gset3
	.dbline 0 ; func end
	ret
	.dbsym r addr 20 c
	.dbsym r y 22 c
	.dbsym r x 10 c
	.dbend
	.dbfunc e Display_x_y_symbol _Display_x_y_symbol fV
;              j -> R20
;              i -> R22
;           data -> y+4
;              y -> R22
;              x -> R20
	.even
_Display_x_y_symbol::
	xcall push_gset2
	mov R22,R18
	mov R20,R16
	.dbline -1
	.dbline 205
; }
; }
; }
; }
; }
; }
; }
; }
; }
	.dbline 207
; }
; }
	mov R18,R22
	mov R16,R20
	xcall _Locate_x_y
	.dbline 208
; }
	ldd R20,y+4
	ldd R21,y+5
	.dbline 209
; }
	movw R22,R20
	mov R22,R23
	clr R23
	.dbline 210
; }
	mov R16,R22
	xcall _Writedata
	.dbline 211
; }
	mov R16,R20
	xcall _Writedata
	.dbline -2
L53:
	xcall pop_gset2
	.dbline 0 ; func end
	ret
	.dbsym r j 20 c
	.dbsym r i 22 c
	.dbsym l data 4 i
	.dbsym r y 22 c
	.dbsym r x 20 c
	.dbend
	.dbfunc e Write_string _Write_string fV
;              s -> R20,R21
	.even
_Write_string::
	xcall push_gset1
	movw R20,R16
	.dbline -1
	.dbline 220
; }
; }
; }
; }
; }
; }
; }
; }
; }
	.dbline 221
; }
	xjmp L58
L55:
	.dbline 222
	.dbline 223
	movw R30,R20
	ldd R16,z+0
	xcall _Writedata
	.dbline 224
L56:
	.dbline 221
	subi R20,255  ; offset = 1
	sbci R21,255
L58:
	.dbline 221
	movw R30,R20
	ldd R2,z+0
	tst R2
	brne L55
	.dbline -2
L54:
	xcall pop_gset1
	.dbline 0 ; func end
	ret
	.dbsym r s 20 pc
	.dbend
	.dbfunc e Display_x_y_data _Display_x_y_data fV
;           data -> R20,R21
;              y -> R22
;              x -> R10
	.even
_Display_x_y_data::
	xcall push_gset3
	mov R22,R18
	mov R10,R16
	ldd R20,y+6
	ldd R21,y+7
	.dbline -1
	.dbline 233
; }
; }
; }
; }
; }
; }
; }
; }
; }
; }
; }
; }
	.dbline 234
; }
	ldi R24,8
	mul R24,R10
	movw R30,R0
	mov R2,R22
	clr R3
	add R30,R2
	adc R31,R3
	ldi R24,<_AC_TABLE
	ldi R25,>_AC_TABLE
	add R30,R24
	adc R31,R25
	ldd R16,z+0
	xcall _Writecommand
	.dbline 235
; }
	xjmp L63
L60:
	.dbline 236
; }
	.dbline 237
; }
	cpi R22,16
	brne L64
	.dbline 238
; }
	.dbline 239
; }
	clr R22
	.dbline 240
; }
	inc R10
	.dbline 241
; }
	mov R24,R10
	cpi R24,4
	brne L66
	.dbline 241
	clr R10
L66:
	.dbline 242
; }
	ldi R24,8
	mul R24,R10
	movw R30,R0
	mov R2,R22
	clr R3
	add R30,R2
	adc R31,R3
	ldi R24,<_AC_TABLE
	ldi R25,>_AC_TABLE
	add R30,R24
	adc R31,R25
	ldd R16,z+0
	xcall _Writecommand
	.dbline 243
; }
L64:
	.dbline 244
	movw R30,R20
	ldd R16,z+0
	xcall _Writedata
	.dbline 245
	inc R22
	.dbline 246
L61:
	.dbline 235
	subi R20,255  ; offset = 1
	sbci R21,255
L63:
	.dbline 235
	movw R30,R20
	ldd R2,z+0
	tst R2
	brne L60
	.dbline -2
L59:
	xcall pop_gset3
	.dbline 0 ; func end
	ret
	.dbsym r data 20 pc
	.dbsym r y 22 c
	.dbsym r x 10 c
	.dbend
	.dbfunc e LcmClearTXT _LcmClearTXT fV
;              i -> R20
	.even
_LcmClearTXT::
	xcall push_gset1
	.dbline -1
	.dbline 256
; }
; }
; }
; }
; }
; }
; }
; }
; }
; }
; }
; }
; }
	.dbline 258
; }
; }
	ldi R16,48
	xcall _Writecommand
	.dbline 259
; }
	ldi R16,128
	xcall _Writecommand
	.dbline 260
; }
	clr R20
	xjmp L72
L69:
	.dbline 261
	ldi R16,32
	xcall _Writedata
L70:
	.dbline 260
	inc R20
L72:
	.dbline 260
	cpi R20,64
	brlo L69
	.dbline -2
L68:
	xcall pop_gset1
	.dbline 0 ; func end
	ret
	.dbsym r i 20 c
	.dbend
	.dbfunc e Init_12864 _Init_12864 fV
	.even
_Init_12864::
	.dbline -1
	.dbline 271
; }
; }
; }
; }
; }
; }
; }
; }
; }
; }
; }
	.dbline 272
; }
	ldi R16,50
	ldi R17,0
	xcall _delay_ms
	.dbline 273
; }
	ldi R16,48
	xcall _Writecommand
	.dbline 274
; }
	ldi R16,3
	xcall _Writecommand
	.dbline 275
; }
	ldi R16,12
	xcall _Writecommand
	.dbline 276
; }
	ldi R16,1
	xcall _Writecommand
	.dbline 277
; }
	ldi R16,6
	xcall _Writecommand
	.dbline -2
L73:
	.dbline 0 ; func end
	ret
	.dbend
	.area data(ram, con, rel)
	.dbfile C:\DOCUME~1\Administrator\桌面\程序/12864.h
_red::
	.blkb 1
	.area idata
	.byte 0
	.area data(ram, con, rel)
	.dbfile C:\DOCUME~1\Administrator\桌面\程序/12864.h
	.dbfile C:\DOCUME~1\Administrator\桌面\程序\colour_identify.c
	.dbsym e red _red c
_blue::
	.blkb 1
	.area idata
	.byte 0
	.area data(ram, con, rel)
	.dbfile C:\DOCUME~1\Administrator\桌面\程序\colour_identify.c
	.dbsym e blue _blue c
_green::
	.blkb 1
	.area idata
	.byte 0
	.area data(ram, con, rel)
	.dbfile C:\DOCUME~1\Administrator\桌面\程序\colour_identify.c
	.dbsym e green _green c
_flag::
	.blkb 1
	.area idata
	.byte 0
	.area data(ram, con, rel)
	.dbfile C:\DOCUME~1\Administrator\桌面\程序\colour_identify.c
	.dbsym e flag _flag c
_i::
	.blkb 1
	.area idata
	.byte 0
	.area data(ram, con, rel)
	.dbfile C:\DOCUME~1\Administrator\桌面\程序\colour_identify.c
	.dbsym e i _i c
_j::
	.blkb 1
	.area idata
	.byte 0
	.area data(ram, con, rel)
	.dbfile C:\DOCUME~1\Administrator\桌面\程序\colour_identify.c
	.dbsym e j _j c
_data::
	.blkb 1
	.area idata
	.byte 0
	.area data(ram, con, rel)
	.dbfile C:\DOCUME~1\Administrator\桌面\程序\colour_identify.c
	.blkb 4
	.area idata
	.byte 0,0,0,0
	.area data(ram, con, rel)
	.dbfile C:\DOCUME~1\Administrator\桌面\程序\colour_identify.c
	.dbsym e data _data A[5:5]c
_counter::
	.blkb 2
	.area idata
	.word 0
	.area data(ram, con, rel)
	.dbfile C:\DOCUME~1\Administrator\桌面\程序\colour_identify.c
	.dbsym e counter _counter i
	.area vector(rom, abs)
	.org 12
	jmp _interrupt_int2
	.area data(ram, con, rel)
	.dbfile C:\DOCUME~1\Administrator\桌面\程序\colour_identify.c
	.area vector(rom, abs)
	.org 56
	jmp _interrupt_timer1
	.area data(ram, con, rel)
	.dbfile C:\DOCUME~1\Administrator\桌面\程序\colour_identify.c
	.area text(rom, con, rel)
	.dbfile C:\DOCUME~1\Administrator\桌面\程序\colour_identify.c
	.dbfunc e int2_init _int2_init fV
	.even
_int2_init::
	.dbline -1
	.dbline 29
	.dbline 30
	cbi 0x11,2
	.dbline 31
	sbi 0x12,2
	.dbline 32
	ldi R24,32
	sts 106,R24
	.dbline -2
L74:
	.dbline 0 ; func end
	ret
	.dbend
	.dbfunc e timer1_init _timer1_init fV
	.even
_timer1_init::
	.dbline -1
	.dbline 42
	.dbline 43
	ldi R24,2
	out 0x2e,R24
	.dbline 44
	ldi R24,99
	out 0x2d,R24
	.dbline 45
	ldi R24,192
	out 0x2c,R24
	.dbline -2
L75:
	.dbline 0 ; func end
	ret
	.dbend
	.dbfunc e port_init _port_init fV
	.even
_port_init::
	.dbline -1
	.dbline 54
	.dbline 55
	ldi R24,255
	out 0x1a,R24
	.dbline 56
	out 0x14,R24
	.dbline -2
L76:
	.dbline 0 ; func end
	ret
	.dbend
	.dbfunc e main _main fV
	.even
_main::
	sbiw R28,2
	.dbline -1
	.dbline 63
	.dbline 64
	xcall _port_init
	.dbline 65
	xcall _int2_init
	.dbline 66
	xcall _timer1_init
	.dbline 67
	xcall _Init_12864
	.dbline 68
	xcall _LcmClearTXT
	.dbline 69
	ldi R24,<L78
	ldi R25,>L78
	std y+1,R25
	std y+0,R24
	clr R18
	clr R16
	xcall _Display_x_y_data
	.dbline 70
	ldi R24,<L79
	ldi R25,>L79
	std y+1,R25
	std y+0,R24
	clr R18
	ldi R16,1
	xcall _Display_x_y_data
	.dbline 71
	ldi R24,<L80
	ldi R25,>L80
	std y+1,R25
	std y+0,R24
	clr R18
	ldi R16,2
	xcall _Display_x_y_data
	.dbline 72
	ldi R24,<L81
	ldi R25,>L81
	std y+1,R25
	std y+0,R24
	clr R18
	ldi R16,3
	xcall _Display_x_y_data
	.dbline 73
	in R24,0x15
	andi R24,127
	out 0x15,R24
	.dbline 74
	in R24,0x15
	andi R24,191
	out 0x15,R24
	.dbline 75
	sei
	.dbline 76
	in R24,0x39
	ori R24,4
	out 0x39,R24
	.dbline 77
	in R24,0x37
	ori R24,4
	out 0x37,R24
L82:
	.dbline 78
L83:
	.dbline 78
	xjmp L82
X6:
	.dbline -2
L77:
	adiw R28,2
	.dbline 0 ; func end
	ret
	.dbend
	.dbfunc e interrupt_int2 _interrupt_int2 fV
	.even
_interrupt_int2::
	st -y,R24
	st -y,R25
	in R24,0x3f
	st -y,R24
	.dbline -1
	.dbline 88
	.dbline 89
	lds R24,_counter
	lds R25,_counter+1
	adiw R24,1
	sts _counter+1,R25
	sts _counter,R24
	.dbline -2
L85:
	ld R24,y+
	out 0x3f,R24
	ld R25,y+
	ld R24,y+
	.dbline 0 ; func end
	reti
	.dbend
	.dbfunc e interrupt_timer1 _interrupt_timer1 fV
	.even
_interrupt_timer1::
	xcall push_lset
	sbiw R28,2
	.dbline -1
	.dbline 99
	.dbline 100
	cli
	.dbline 101
	clr R2
	out 0x2e,R2
	.dbline 102
	in R24,0x37
	andi R24,251
	out 0x37,R24
	.dbline 103
	in R24,0x39
	andi R24,251
	out 0x39,R24
	.dbline 104
	lds R24,_flag
	subi R24,255    ; addi 1
	sts _flag,R24
	.dbline 105
	lds R24,_flag
	cpi R24,1
	breq X7
	xjmp L87
X7:
	.dbline 106
	.dbline 107
	lds R2,_counter
	lds R3,_counter+1
	sts _red,R2
	.dbline 108
	ldi R18,100
	ldi R19,0
	lds R16,_counter
	lds R17,_counter+1
	xcall div16u
	movw R24,R16
	adiw R24,48
	sts _data,R24
	.dbline 109
	ldi R18,100
	ldi R19,0
	lds R16,_counter
	lds R17,_counter+1
	xcall mod16u
	sts _counter+1,R17
	sts _counter,R16
	.dbline 110
	ldi R18,10
	ldi R19,0
	lds R16,_counter
	lds R17,_counter+1
	xcall div16u
	movw R24,R16
	adiw R24,48
	sts _data+1,R24
	.dbline 111
	ldi R18,10
	ldi R19,0
	lds R16,_counter
	lds R17,_counter+1
	xcall mod16u
	sts _counter+1,R17
	sts _counter,R16
	.dbline 112
	lds R24,_counter
	lds R25,_counter+1
	adiw R24,48
	sts _data+2,R24
	.dbline 113
	ldi R18,5
	ldi R16,1
	xcall _Locate_x_y
	.dbline 114
	clr R2
	sts _i,R2
	xjmp L94
L91:
	.dbline 115
	ldi R24,<_data
	ldi R25,>_data
	lds R30,_i
	clr R31
	add R30,R24
	adc R31,R25
	ldd R16,z+0
	xcall _Writedata
L92:
	.dbline 114
	lds R24,_i
	subi R24,255    ; addi 1
	sts _i,R24
L94:
	.dbline 114
	lds R24,_i
	cpi R24,3
	brlo L91
	.dbline 116
	in R24,0x15
	andi R24,127
	out 0x15,R24
	.dbline 117
	in R24,0x15
	ori R24,64
	out 0x15,R24
	.dbline 118
	xjmp L88
L87:
	.dbline 119
	lds R24,_flag
	cpi R24,2
	breq X8
	xjmp L95
X8:
	.dbline 120
	.dbline 121
	lds R2,_counter
	lds R3,_counter+1
	sts _blue,R2
	.dbline 122
	ldi R18,100
	ldi R19,0
	lds R16,_counter
	lds R17,_counter+1
	xcall div16u
	movw R24,R16
	adiw R24,48
	sts _data,R24
	.dbline 123
	ldi R18,100
	ldi R19,0
	lds R16,_counter
	lds R17,_counter+1
	xcall mod16u
	sts _counter+1,R17
	sts _counter,R16
	.dbline 124
	ldi R18,10
	ldi R19,0
	lds R16,_counter
	lds R17,_counter+1
	xcall div16u
	movw R24,R16
	adiw R24,48
	sts _data+1,R24
	.dbline 125
	ldi R18,10
	ldi R19,0
	lds R16,_counter
	lds R17,_counter+1
	xcall mod16u
	sts _counter+1,R17
	sts _counter,R16
	.dbline 126
	lds R24,_counter
	lds R25,_counter+1
	adiw R24,48
	sts _data+2,R24
	.dbline 127
	ldi R18,5
	ldi R16,2
	xcall _Locate_x_y
	.dbline 128
	clr R2
	sts _i,R2
	xjmp L102
L99:
	.dbline 129
	ldi R24,<_data
	ldi R25,>_data
	lds R30,_i
	clr R31
	add R30,R24
	adc R31,R25
	ldd R16,z+0
	xcall _Writedata
L100:
	.dbline 128
	lds R24,_i
	subi R24,255    ; addi 1
	sts _i,R24
L102:
	.dbline 128
	lds R24,_i
	cpi R24,3
	brlo L99
	.dbline 130
	in R24,0x15
	ori R24,128
	out 0x15,R24
	.dbline 131
	in R24,0x15
	ori R24,64
	out 0x15,R24
	.dbline 132
	xjmp L96
L95:
	.dbline 133
	lds R24,_flag
	cpi R24,3
	breq X9
	xjmp L103
X9:
	.dbline 134
	.dbline 135
	lds R2,_counter
	lds R3,_counter+1
	sts _green,R2
	.dbline 136
	ldi R18,100
	ldi R19,0
	lds R16,_counter
	lds R17,_counter+1
	xcall div16u
	movw R24,R16
	adiw R24,48
	sts _data,R24
	.dbline 137
	ldi R18,100
	ldi R19,0
	lds R16,_counter
	lds R17,_counter+1
	xcall mod16u
	sts _counter+1,R17
	sts _counter,R16
	.dbline 138
	ldi R18,10
	ldi R19,0
	lds R16,_counter
	lds R17,_counter+1
	xcall div16u
	movw R24,R16
	adiw R24,48
	sts _data+1,R24
	.dbline 139
	ldi R18,10
	ldi R19,0
	lds R16,_counter
	lds R17,_counter+1
	xcall mod16u
	sts _counter+1,R17
	sts _counter,R16
	.dbline 140
	lds R24,_counter
	lds R25,_counter+1
	adiw R24,48
	sts _data+2,R24
	.dbline 141
	ldi R18,5
	ldi R16,3
	xcall _Locate_x_y
	.dbline 142
	clr R2
	sts _i,R2
	xjmp L110
L107:
	.dbline 143
	ldi R24,<_data
	ldi R25,>_data
	lds R30,_i
	clr R31
	add R30,R24
	adc R31,R25
	ldd R16,z+0
	xcall _Writedata
L108:
	.dbline 142
	lds R24,_i
	subi R24,255    ; addi 1
	sts _i,R24
L110:
	.dbline 142
	lds R24,_i
	cpi R24,3
	brlo L107
	.dbline 144
	in R24,0x15
	andi R24,127
	out 0x15,R24
	.dbline 145
	in R24,0x15
	andi R24,191
	out 0x15,R24
	.dbline 146
	xjmp L104
L103:
	.dbline 147
	lds R24,_flag
	cpi R24,4
	breq X10
	xjmp L111
X10:
	.dbline 148
	.dbline 149
	clr R2
	sts _flag,R2
	.dbline 150
	lds R2,_green
	lds R3,_blue
	add R3,R2
	lds R24,_red
	subi R24,251    ; addi 5
	cp R3,R24
	brsh L113
	.dbline 151
	ldi R24,<L115
	ldi R25,>L115
	std y+1,R25
	std y+0,R24
	ldi R18,5
	clr R16
	xcall _Display_x_y_data
	xjmp L114
L113:
	.dbline 152
	lds R2,_red
	lds R24,_blue
	subi R24,248    ; addi 8
	cp R2,R24
	brsh L116
	lds R2,_green
	lds R24,_blue
	subi R24,254    ; addi 2
	cp R2,R24
	brsh L116
	.dbline 153
	ldi R24,<L118
	ldi R25,>L118
	std y+1,R25
	std y+0,R24
	ldi R18,5
	clr R16
	xcall _Display_x_y_data
	xjmp L117
L116:
	.dbline 154
	lds R2,_red
	lds R24,_green
	subi R24,3
	cp R24,R2
	brsh L119
	lds R2,_blue
	lds R24,_green
	subi R24,15
	cp R2,R24
	brsh L119
	.dbline 155
	ldi R24,<L121
	ldi R25,>L121
	std y+1,R25
	std y+0,R24
	ldi R18,5
	clr R16
	xcall _Display_x_y_data
	xjmp L120
L119:
	.dbline 156
	lds R2,_red
	lds R24,_green
	subi R24,251    ; addi 5
	cp R2,R24
	brsh L122
	lds R2,_blue
	lds R3,_green
	cp R2,R3
	brsh L122
	.dbline 157
	ldi R24,<L124
	ldi R25,>L124
	std y+1,R25
	std y+0,R24
	ldi R18,5
	clr R16
	xcall _Display_x_y_data
	xjmp L123
L122:
	.dbline 161
	ldi R24,<L125
	ldi R25,>L125
	std y+1,R25
	std y+0,R24
	ldi R18,5
	clr R16
	xcall _Display_x_y_data
L123:
L120:
L117:
L114:
	.dbline 162
L111:
L104:
L96:
L88:
	.dbline 164
	clr R2
	clr R3
	sts _counter+1,R3
	sts _counter,R2
	.dbline 165
	ldi R24,2
	out 0x2e,R24
	.dbline 166
	ldi R24,99
	out 0x2d,R24
	.dbline 167
	ldi R24,192
	out 0x2c,R24
	.dbline 168
	in R24,0x37
	ori R24,4
	out 0x37,R24
	.dbline 169
	in R24,0x39
	ori R24,4
	out 0x39,R24
	.dbline 170
	sei
	.dbline -2
L86:
	adiw R28,2
	xcall pop_lset
	.dbline 0 ; func end
	reti
	.dbend
	.area data(ram, con, rel)
	.dbfile C:\DOCUME~1\Administrator\桌面\程序\colour_identify.c
L125:
	.blkb 5
	.area idata
	.byte 206,180,214,170,0
	.area data(ram, con, rel)
	.dbfile C:\DOCUME~1\Administrator\桌面\程序\colour_identify.c
L124:
	.blkb 5
	.area idata
	.byte 194,204,201,171,0
	.area data(ram, con, rel)
	.dbfile C:\DOCUME~1\Administrator\桌面\程序\colour_identify.c
L121:
	.blkb 5
	.area idata
	.byte 187,198,201,171,0
	.area data(ram, con, rel)
	.dbfile C:\DOCUME~1\Administrator\桌面\程序\colour_identify.c
L118:
	.blkb 5
	.area idata
	.byte 192,182,201,171,0
	.area data(ram, con, rel)
	.dbfile C:\DOCUME~1\Administrator\桌面\程序\colour_identify.c
L115:
	.blkb 5
	.area idata
	.byte 186,236,201,171,0
	.area data(ram, con, rel)
	.dbfile C:\DOCUME~1\Administrator\桌面\程序\colour_identify.c
L81:
	.blkb 11
	.area idata
	.byte 194,204,201,171,179,201,183,214,163,186,0
	.area data(ram, con, rel)
	.dbfile C:\DOCUME~1\Administrator\桌面\程序\colour_identify.c
L80:
	.blkb 11
	.area idata
	.byte 192,182,201,171,179,201,183,214,163,186,0
	.area data(ram, con, rel)
	.dbfile C:\DOCUME~1\Administrator\桌面\程序\colour_identify.c
L79:
	.blkb 11
	.area idata
	.byte 186,236,201,171,179,201,183,214,163,186,0
	.area data(ram, con, rel)
	.dbfile C:\DOCUME~1\Administrator\桌面\程序\colour_identify.c
L78:
	.blkb 11
	.area idata
	.byte 209,213,201,171,202,182,177,240,163,186,0
	.area data(ram, con, rel)
	.dbfile C:\DOCUME~1\Administrator\桌面\程序\colour_identify.c
