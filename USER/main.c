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
 ALIENTEKս��STM32������ʵ��20
 DAC ʵ��  
 ����֧�֣�www.openedv.com
 �Ա����̣�http://eboard.taobao.com 
 ��ע΢�Ź���ƽ̨΢�źţ�"����ԭ��"����ѻ�ȡSTM32���ϡ�
 ������������ӿƼ����޹�˾  
 ���ߣ�����ԭ�� @ALIENTEK
************************************************/


#define PI 3.1415962

//������Ҳ�����
void dac_sin_out(u8 dots)
{
    u8 i;
    u16 buf[255];
    float inc=2*PI/dots;    //����������һ������dots���㣩
    float outdata=0;
    for(i=0;i<dots;i++)
    {
        outdata=2047*(1+sin(inc*i));    //������dots����Ϊ���ڵ�ÿ�����ֵ���Ŵ�2048������ƫ�Ƶ���������
        printf("%f\r\n",outdata);
        buf[i]=outdata;
    }
    while(1)                //��ͣ�Ĳ������Ҳ�
    {
        for(i=0;i<dots;i++)
        {
            DAC->DHR12R1=buf[i];
        }
    } 
}


 int main(void)
 {	  
	delay_init();	    	 //��ʱ������ʼ��	  
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//�����ж����ȼ�����Ϊ��2��2λ��ռ���ȼ���2λ��Ӧ���ȼ�
	uart_init(115200);	 	//���ڳ�ʼ��Ϊ115200
	KEY_Init();			  //��ʼ����������
 	LED_Init();			     //LED�˿ڳ�ʼ��
	LCD_Init();			 	 //LCD��ʼ��
	usmart_dev.init(72);	//��ʼ��USMART	
 	Adc_Init();		  		//ADC��ʼ��
	Dac1_Init();				//DAC��ʼ��

     
     
	POINT_COLOR=RED;//��������Ϊ��ɫ 
	LCD_ShowString(60,50,200,16,16,"WarShip STM32");	
	LCD_ShowString(60,70,200,16,16,"DAC TEST");	
	LCD_ShowString(60,90,200,16,16,"ATOM@ALIENTEK");
	LCD_ShowString(60,110,200,16,16,"2015/1/15");	
	LCD_ShowString(60,130,200,16,16,"WK_UP:+  KEY1:-");	
	//��ʾ��ʾ��Ϣ											      
	POINT_COLOR=BLUE;//��������Ϊ��ɫ
	LCD_ShowString(60,150,200,16,16,"DAC VAL:");	      
	LCD_ShowString(60,170,200,16,16,"DAC VOL:0.000V");	      
	LCD_ShowString(60,190,200,16,16,"ADC VOL:0.000V");
	
    DAC_SetChannel1Data(DAC_Align_12b_R, 0);//��ʼֵΪ0	    	      
	while(1)
	{
        dac_sin_out(100);    //��������50���� �����Ҳ�
		  
	}
 }

