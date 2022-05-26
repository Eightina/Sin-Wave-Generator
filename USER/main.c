#include "led.h"
#include "delay.h"
#include "key.h"
#include "sys.h"
#include "lcd.h"
#include "usart.h"	 	 
#include "dac.h"
#include "adc.h"
#include "usmart.h"
#include "math.h"
 
/************************************************
 ALIENTEK战舰STM32开发板实验20
 DAC 实验  
 技术支持：www.openedv.com
 淘宝店铺：http://eboard.taobao.com 
 关注微信公众平台微信号："正点原子"，免费获取STM32资料。
 广州市星翼电子科技有限公司  
 作者：正点原子 @ALIENTEK
************************************************/


#define PI 3.1415962

//输出正弦波函数
void dac_sin_out(u8 dots)
{
    u8 i;
    u16 buf[255];
    float inc=2*PI/dots;    //计算增量（一个周期dots个点）
    float outdata=0;
    for(i=0;i<dots;i++)
    {
        outdata=2047*(1+sin(inc*i));    //计算以dots个点为周期的每个点的值，放大2048倍，并偏移到正数区域。
        printf("%f\r\n",outdata);
        buf[i]=outdata;
    }
    while(1)                //不停的产生正弦波
    {
        for(i=0;i<dots;i++)
        {
            DAC->DHR12R1=buf[i];
        }
    } 
}


 int main(void)
 {	  
	delay_init();	    	 //延时函数初始化	  
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//设置中断优先级分组为组2：2位抢占优先级，2位响应优先级
	uart_init(115200);	 	//串口初始化为115200
	KEY_Init();			  //初始化按键程序
 	LED_Init();			     //LED端口初始化
	LCD_Init();			 	 //LCD初始化
	usmart_dev.init(72);	//初始化USMART	
 	Adc_Init();		  		//ADC初始化
	Dac1_Init();				//DAC初始化

     
     
	POINT_COLOR=RED;//设置字体为红色 
	LCD_ShowString(60,50,200,16,16,"WarShip STM32");	
	LCD_ShowString(60,70,200,16,16,"DAC TEST");	
	LCD_ShowString(60,90,200,16,16,"ATOM@ALIENTEK");
	LCD_ShowString(60,110,200,16,16,"2015/1/15");	
	LCD_ShowString(60,130,200,16,16,"WK_UP:+  KEY1:-");	
	//显示提示信息											      
	POINT_COLOR=BLUE;//设置字体为蓝色
	LCD_ShowString(60,150,200,16,16,"DAC VAL:");	      
	LCD_ShowString(60,170,200,16,16,"DAC VOL:0.000V");	      
	LCD_ShowString(60,190,200,16,16,"ADC VOL:0.000V");
	
    DAC_SetChannel1Data(DAC_Align_12b_R, 0);//初始值为0	    	      
	while(1)
	{
        dac_sin_out(100);    //产生周期50个点 的正弦波
		  
	}
 }

