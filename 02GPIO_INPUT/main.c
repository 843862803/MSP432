//*****************************************************************************
//
// MSP432 main.c template - Empty main
//
//****************************************************************************

#include "msp.h"
#include <ti/devices/msp432p4xx/driverlib/driverlib.h>

void main(void)
{
	
    //WDTCTL = WDTPW | WDTHOLD;           // Stop watchdog timer
    WDT_A_holdTimer();
    GPIO_setAsOutputPin(GPIO_PORT_P1, GPIO_PIN0);                  //����P1.0Ϊ���
    GPIO_setAsInputPinWithPullUpResistor(GPIO_PORT_P1, GPIO_PIN4); //����P1.4Ϊ���룬Ĭ��Ϊ�ߵ�ƽ

    while(1)
    {
    	while(! GPIO_getInputPinValue(GPIO_PORT_P1, GPIO_PIN4))
    	{
    		SysTick_setPeriod(150000); //SysTick��ʼ��������⵽��������ʱ����ʱ5ms����
    		SysTick_enableModule();
    		while(SysTick_getValue()&15000); //���������ٴ��ж��Ƿ���
    		SysTick_disableModule();
    		if(! GPIO_getInputPinValue(GPIO_PORT_P1, GPIO_PIN4))
    		{
    			GPIO_toggleOutputOnPin(GPIO_PORT_P1, GPIO_PIN0); //�����ת
    			while(! GPIO_getInputPinValue(GPIO_PORT_P1, GPIO_PIN4)); //���ֵ������ͷ�
    			SysTick_setPeriod(150000); //SysTick��ʼ������ʱ5ms����
    			SysTick_enableModule();
    			while(SysTick_getValue()&15000);
    			SysTick_disableModule();   //�رն�ʱ��
    			GPIO_setAsInputPinWithPullUpResistor(GPIO_PORT_P1, GPIO_PIN4); //����P1.4Ϊ���룬Ĭ��Ϊ�ߵ�ƽ
    		}
    	}
    }
}
