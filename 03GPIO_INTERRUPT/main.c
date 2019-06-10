//
//*****************************************************************************
//  DEMO:     GPIO_INTERRUPT
//  MCU:      MSP432
//	NUMBER:   03
//  describe: ʹ���˴����жϽ��п��ƣ�P1.1��P1.4���ɿ��ƣ����ҵ�����LPM3ʡ��ģʽ
//*****************************************************************************
//https://blog.csdn.net/weixin_44048162/article/details/90646189

#include "msp.h"
#include <DriverLib/driverlib.h>

volatile uint32_t status; //���ڼ�¼�жϷ����Ķ˿ں�
/*volatile�ؼ���Ӱ�����������Ľ������volatile�����ı�����ʾ�ñ�����ʱ���ܷ����仯��
��ñ����йص����㣬��Ҫ���б����Ż����������*/

void gpio_isr(); //GPIO�жϷ������

void main(void)
{
	WDT_A_holdTimer();                                             //�رտ��Ź�
	GPIO_setAsOutputPin(GPIO_PORT_P1, GPIO_PIN0);                  //����P1.0Ϊ���
	GPIO_setAsInputPinWithPullUpResistor(GPIO_PORT_P1, GPIO_PIN1); //����P1.1Ϊ���룬Ĭ��Ϊ�ߵ�ƽ
	GPIO_setAsInputPinWithPullUpResistor(GPIO_PORT_P1, GPIO_PIN4); //����P1.4Ϊ���룬Ĭ��Ϊ�ߵ�ƽ
	GPIO_clearInterruptFlag(GPIO_PORT_P1, GPIO_PIN1);              //����жϱ�־
	GPIO_clearInterruptFlag(GPIO_PORT_P1, GPIO_PIN4);              //����жϱ�־
	GPIO_enableInterrupt(GPIO_PORT_P1, GPIO_PIN1);                 //ʹ��P1.1�ж�
	GPIO_enableInterrupt(GPIO_PORT_P1, GPIO_PIN4);                 //ʹ��P1.4�ж�
	Interrupt_enableInterrupt(INT_PORT1);
	GPIO_registerInterrupt(GPIO_PORT_P1, gpio_isr);                //ע��gpio_isrΪGPIO_P1�жϷ������

	while (1)
	{
		PCM_gotoLPM3(); //����LPM3ʡ��ģʽ
	}
}

void gpio_isr() //GPIO�жϷ������
{
	status = GPIO_getEnabledInterruptStatus(GPIO_PORT_P1); //��¼�˿ں�
	GPIO_toggleOutputOnPin(GPIO_PORT_P1, GPIO_PIN0);       //��תGPIO״̬��ʵ�ֵƵĿ���
	GPIO_clearInterrupt(GPIO_PORT_P1, status);             //�����Ӧ�ڵı�־
}
