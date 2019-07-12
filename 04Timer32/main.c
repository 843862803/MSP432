//
//*****************************************************************************
//  DEMO:     Timer32
//  MCU:      MSP432
//	NUMBER:   04
//  describe: ʹ��Timer32��ʱ��ʵ��LED 1s��˸
//*****************************************************************************
//https://me.csdn.net/weixin_44048162

#include "msp.h"
#include <DriverLib/driverlib.h>

void Timer32IsrHandler();

int main()
{
	WDT_A_holdTimer();                                                  //�رտ��Ź�
	CS_initClockSignal(CS_MCLK, CS_LFXTCLK_SELECT, CS_CLOCK_DIVIDER_1); //ʱ�ӳ�ʼ��������MCLKʱ�ӵ�ʱ��ԴΪLFXTCLK������Ƶ
	GPIO_setAsOutputPin(GPIO_PORT_P1, GPIO_PIN0);                       //����P1.0Ϊ���
	GPIO_setOutputLowOnPin(GPIO_PORT_P1, GPIO_PIN0);                    //P1.0Ĭ������͵�ƽ

	Timer32_initModule(TIMER32_0_BASE, TIMER32_PRESCALER_1, TIMER32_32BIT, TIMER32_PERIODIC_MODE);
	/*Timer32��ʱ��ѡ��timer0����һ����ʱ��������ʱ������Ƶ��32λ��С����������ģʽ*/
	Timer32_setCount(TIMER32_0_BASE, 0x8000);                     //Timer0��װ���ֵ0x8000��32768��
	Interrupt_registerInterrupt(INT_T32_INT1, Timer32IsrHandler); //ע��Timer32IsrHandlerΪINT_T32_INT1�жϷ������
	Interrupt_enableInterrupt(INT_T32_INT1);                      //ʹ��Timer32�жϷ������
	Timer32_enableInterrupt(TIMER32_0_BASE);                      //ʹ��Timer32�ж�
	Timer32_startTimer(TIMER32_0_BASE, false);                    //����Timer32��ʱ��������ѭ������

	while (1)
	{
		__sleep();
	}

	return 0;
}

void Timer32IsrHandler()
{
	Timer32_clearInterruptFlag(TIMER32_0_BASE);      //���Timer32�жϱ�־
	GPIO_toggleOutputOnPin(GPIO_PORT_P1, GPIO_PIN0); //��תGPIO״̬��ʵ�ֵƵĿ���
}
