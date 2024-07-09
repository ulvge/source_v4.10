/****************************************Copyright (c)****************************************************
**                            Shenzhen HONGMEN electronics Co.,LTD.
**
**                                 http://www.hong-men.com
**
**--------------File Info---------------------------------------------------------------------------------
** File Name          : PWM.C
** Last modified Date : 2011-06-02
** Last Version       : V1.00
** Descriptions       : TIMER File
**
**--------------------------------------------------------------------------------------------------------
** Modified by        :
** Modified date      :
** Version            :
** Descriptions       :
**
*********************************************************************************************************/
#define PWM_GLOBALS 
#include "includes.h" 
#include	"typedef.h"	
#include	"pwm.h"
/****************************************************************
 * ��������void GPIO_Config(void) 
 * ����  �����ø������PWMʱ�õ���I/O 
 * ����  ���� 
 * ���  ���� 
 * ����  ��main()���� 
�� TIM1_CH1 pin (PA8)   pwm
�� TIM1_CH1N pin (PB13)
�� TIM1_CH2 pin (PA9)
�� TIM1_CH2N pin (PB14)
�� TIM1_CH3 pin (PA10)
�� TIM1_CH3N pin (PB15)
 ***************************************************************/
#define PWM_TIM TIM1
#define PWM_PIN GPIO_Pin_8
#define PWM_PERCNET_DEFAULT 50	
#define PWM_RESOLUTION_DEFAULT 5	//step

//32Mϵͳʱ�ӣ�����Ƶ��32M, ���Ƶ��32M
//32Mϵͳʱ�ӣ�32��Ƶ��1M, ���Ƶ��1M.
//TIM_Period = 1000����1ms; ��Ƶ��Ϊ1000HZ
//TIM_Period = 500����0.5ms; ��Ƶ��Ϊ2000HZ

//Ƶ��Ϊ1000HZ,������1ms��  TIM_Period = 1000
//Ƶ��Ϊ2000HZ ������0.5ms��TIM_Period = 500
INT32U PWM_FREQUENCY =  1500;

#define PWM_PRE_SCALE_DIV36_1M   (OS_CLOCK_X_MHZ)
#define PWM_PRE_SCALE_DIV3600_1K  (OS_CLOCK_X_KHZ)
typedef struct {
	INT32U	freMax;		           //��ǰԤ��Ƶ�����֧�ֵ�PWMƵ��
	INT16U	preScale;              //Ԥ��Ƶ��ֵ
	INT16U	repetNums;              //Ԥ��Ƶֵ

	//�趨�ָ�Ƶ�ʣ������˲�ϵ�������Ĳ���Ƶ�ʺ�N�¼��������˳���Ƶ�����ź�
	INT16U	clkDiv;               //��PWM�����ź��й� https://blog.csdn.net/yuyan7045/article/details/121289037?spm=1001.2101.3001.6650.1&utm_medium=distribute.pc_relevant.none-task-blog-2%7Edefault%7ECTRLIST%7Edefault-1.nonecase&depth_1-utm_source=distribute.pc_relevant.none-task-blog-2%7Edefault%7ECTRLIST%7Edefault-1.nonecase
}FrequecnyPreScale_ST;
static const FrequecnyPreScale_ST g_tablePreScale[] = {
	{100,			PWM_PRE_SCALE_DIV3600_1K, 0, TIM_CKD_DIV1},
	{1000 * 1000,	PWM_PRE_SCALE_DIV36_1M, 0, TIM_CKD_DIV1},
};

typedef enum {
	PWM_DispMode_CntSlef = (INT8U)0,	//����
	PWM_DispMode_Table,			//���
	PWM_DispMode_Remote,			//Զ�̿���
	PWM_DispMode_MAX,
}PWM_DispMode_ST;

//ͨ��shell����ѡ��LEDģʽ,
typedef struct {
	INT32U	workFreq;
	INT16U	preScale;
	INT16U	repetNums;
	INT16U	clkDiv;

	INT16U	Perio;      //����
	INT16U	Resolution; //�ֱ��� ������/�� ʱ��stepVal��ֵ
	INT16U	DispRGBMode;
	INT16U	DispSpeedMode;
	INT16U	DispTbIndex;//TBColor�е�index
} PWM_CFG;
PWM_CFG  PwmCfg;

static void PWM_CfgRGBMode(INT8U mode);
static void PWM_getRunParaByFreq(INT32U freq, PWM_CFG* config)
{
	INT32U num = sizeof(g_tablePreScale) / sizeof(g_tablePreScale[0]);
	INT32U idx = 0;
	for (idx = 0; idx < num - 1; idx++) {
		if (freq <= g_tablePreScale[idx].freMax) {
			break;
		}
	}
	config->preScale	= g_tablePreScale[idx].preScale;
	config->repetNums	= g_tablePreScale[idx].repetNums;
	config->clkDiv		= g_tablePreScale[idx].clkDiv;
}
static INT16U PWM_getPWMDefaultConfig(PWM_CFG* config)
{
	config->Resolution = PWM_RESOLUTION_DEFAULT;
	config->DispSpeedMode = 1;
	config->DispTbIndex = 0;
	//PWM_CfgRGBMode(PWM_DispMode_CntSlef);
	PWM_CfgRGBMode(PWM_DispMode_Remote);

	PWM_getRunParaByFreq(PWM_FREQUENCY, config);
	config->workFreq = OS_CLOCK / config->preScale / ((config->clkDiv>>16) + 1);

	INT32U period = config->workFreq / PWM_FREQUENCY;
	if (period > 0xFFFF) {
		return FALSE;
	}
	config->Perio = period;
	return TRUE;
}

 /* ����TIM1�������PWMʱ�õ���I/O  */
static void PWM_GPIO_Config(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;

	/* TIM1 clock enable */
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1, ENABLE);

	/* GPIOA and GPIOB clock enable */
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_GPIOB, ENABLE);

	GPIO_InitStructure.GPIO_Pin = PWM_PIN;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;

	GPIO_Init(GPIOA, &GPIO_InitStructure);
}


void PWM_ReqRGBMode(void)
{   
	PWM_DEBUG(("->: PWM CfgMode  = 0x%o\n", PwmCfg.DispRGBMode));
}
static void PWM_CfgRGBMode(INT8U mode)
{   
    if(mode >= PWM_DispMode_MAX){
		PWM_DEBUG(("->err: PWM CfgMode  = 0x%o\n", mode));
		return;
	}
	PwmCfg.DispRGBMode= mode;
	PWM_DEBUG(("->: PWM CfgMode  = 0x%o\n", mode));
}
void PWM_SetDuty(TIM_TypeDef* TIMx,INT16U pin,INT16U duty)
{
    TIM_OCInitTypeDef  TIM_OCInitStructure;  
	
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;                           //����ΪPWMģʽ1  
	TIM_OCInitStructure.TIM_Pulse = duty;                                       //��������ֵ�������������������ֵʱ����ƽ��������  
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;                    //����ʱ������ֵС��CCR2ʱΪ�͵�ƽ 
	
	TIM_OCInitStructure.TIM_OCIdleState = TIM_OCIdleState_Reset;					//RGBΪ�������ʿ���ʱҲ����
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;    
    //TIM_OCInitStructure.TIM_OCNPolarity = TIM_OCNPolarity_Low;//������ͨ��
	
    switch(pin){
        case PWM_PIN:
            /* PWM1 Mode configuration: Channel1 */                            
            TIM_OC1Init(PWM_TIM, &TIM_OCInitStructure);            
			if(duty == 0)	TIM_OC1PreloadConfig(PWM_TIM, TIM_OCPreload_Disable);
            else 			TIM_OC1PreloadConfig(PWM_TIM, TIM_OCPreload_Enable);  
            break;
        default:
            return;
    }
    return;
}
/*
*dutyPercent:ֵ[0,100]
PwmCfg.Resolution  :�ֱ��� 100����0~99��100������
*/
static INT16U  PWM_calcDutyByPercent(INT8U dutyPercent)
{
	INT16U pluseNum;
	pluseNum = PwmCfg.Perio * dutyPercent / 100;
	return pluseNum;
}          
static INT16U dutyPercent = PWM_PERCNET_DEFAULT;
void PWM_DutyChange(BOOLEAN isAdd)
{              
	if (isAdd) {
		if (dutyPercent + PwmCfg.Resolution < 100) {
			dutyPercent += PwmCfg.Resolution;
		}else{
            dutyPercent = 100;
        }
	} else {
		if (dutyPercent >= PwmCfg.Resolution) {
			dutyPercent -= PwmCfg.Resolution;
		} else{
            dutyPercent = 0;
        }
	} 
	PWM_DEBUG(("->: PWM_DutyChange [%l]\n", dutyPercent)); 
    PWM_SetDuty(PWM_TIM, PWM_PIN, PWM_calcDutyByPercent(dutyPercent));
}
static void PWM_TIM1_Config(PWM_CFG* pwmConfig) //INT8U psc, INT32U repetNums)
{
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1, ENABLE);
	/* Time base configuration */
	TIM_TimeBaseStructure.TIM_Prescaler = pwmConfig->preScale - 1;                   //����Ԥ��Ƶ��Ԥ��Ƶ=32����Ϊ32/32=1MHz  
	TIM_TimeBaseStructure.TIM_ClockDivision = pwmConfig->clkDiv;                 //0������Ƶ;����ʱ�ӷ�Ƶϵ��������Ƶ  
	TIM_TimeBaseStructure.TIM_Period = pwmConfig->Perio - 1;
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;                 //���ϼ������ģʽ  

	TIM_TimeBaseStructure.TIM_RepetitionCounter = 0;		//ÿ��������������������¼�;�������,�ظ�x�κ󣬲��ϱ�һ���ж�
	TIM_TimeBaseInit(PWM_TIM, &TIM_TimeBaseStructure);
	PWM_SetDuty(PWM_TIM, PWM_PIN, PWM_calcDutyByPercent(PWM_PERCNET_DEFAULT));
	//����PWM_TIM��PWM���Ϊʹ��
	TIM_CtrlPWMOutputs(PWM_TIM, ENABLE);
	/* PWM_TIM enable counter */
	TIM_ARRPreloadConfig(PWM_TIM, ENABLE);                                         //ʹ��PWM_TIM���ؼĴ���ARR  
	
	
	PWM_DEBUG(("->: PWM_Duty percent default [%l]\n", PWM_PERCNET_DEFAULT));
}

__attribute__((unused)) static void PWN_ITConfig(void)
{
	NVIC_InitTypeDef NVIC_InitStructure;

	//Step3.�ж�NVIC���ã������жϣ��������ȼ� 
	NVIC_InitStructure.NVIC_IRQChannel = TIM1_UP_IRQChannel;    //�����¼� 
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2;   //��ռ���ȼ�0 
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;        //��Ӧ���ȼ�1 
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;           //�����ж� 
	NVIC_Init(&NVIC_InitStructure);                       //д������ 

	//ʹ��TIM1�ж�Դ 
	TIM_ITConfig(PWM_TIM, TIM_IT_Update, ENABLE);
}
/// <summary>
/// ����Ƶ�ʣ����жϴ���==Ƶ��ʱ����ӡ�����ȷ��ʱ�䣬�Ƿ�պ���1s
/// </summary>
/// <param name=""></param>
void TIM1_UP_IRQHandler_ISR(void)
{
	static INT32U count;

	if (TIM_GetITStatus(TIM1, TIM_IT_Update) != RESET) {//���ָ����TIM�жϷ������:TIM �ж�Դ 
		TIM_ClearITPendingBit(TIM1, TIM_IT_Update);//���TIMx���жϴ�����λ:TIM �ж�Դ 
	}
	count++;
	if (count >= PWM_FREQUENCY) {
		count = 0;
		PWM_DEBUG(("->: PWM work ...frequency[%l] \n", PWM_FREQUENCY));
	}
}

static void PWM_Init(void)
{
	PWM_GPIO_Config();

	if (PWM_getPWMDefaultConfig(&PwmCfg) == FALSE) {
		PWM_DEBUG(("->: PWM freqency of config is error\n"));
		while (1);
	}

	PWM_TIM1_Config(&PwmCfg);
	//PWN_ITConfig();
	TIM_Cmd(PWM_TIM, ENABLE);                   //ʹ��PWM_TIM   
}

CoreInitCall(PWM_Init);


