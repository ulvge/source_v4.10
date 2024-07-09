/**************************************
 * �ļ���  ��IR.c
 * ����    �����񣬲���PWM��Ƶ�ʣ�ռ�ձ� 
 * ԭ��    �������벶�����һ�θߵ�ƽ����ʱ���ԭ����ͼ�������������ش����жϣ�������������ʱ��
 �ö�ʱ�����¼������������½��ش����жϡ����½��ص���ʱ����¼�´�ʱ��ʱ����ֵCCRx2��
 �ڸߵ�ƽ�ڼ䣬��ʱ��������N�������
 �����ܹ���������Ϊ  N*ARR + CCRx2���ٳ���һ�μ�����ʱ��͵õ��ߵ�ƽ���ȡ�

 �����ж�:����CNT��ֵ������ARR��ʱ����Ҫ����װ��CNT��Ҳ������ν�ĸ��£�����ô�Ϳ��Դ��������жϡ�
 �����ж�:�������벶���ʱ�򣬵�����������ֵ�ʱ����ô�Ϳ������𴥷��жϡ�

 * Ӳ�����ӣ�----------------------
 *          |   PA3  - ����       |
 *          |   PA8  - ���PWM    |
 *           ----------------------
 * ԭ��ο�: https://blog.csdn.net/weixin_51466742/article/details/118336297
 * ԭ��ο�: https://blog.csdn.net/qq_16055183/article/details/118313393

*********************************************************/

#define		IR_GLOBALS  
#include    "includes.h" 
#include	"typedef.h"
#include	"IR.h"
#include	"TM1637.h"

#if  DBG_IR
#define IRE_DEBUG( X)   do {DPrint X ;} while(0)
#else
#define IRE_DEBUG( X)    
#endif

// PA0,PA1,PA2,PA3 ; remap:PA0,PA1,PB10,PB11
#define IR_TIME TIM2
#define IR_TIME_CHANNLE TIM_Channel_4
#define IR_IT_CHANNLE TIM_IT_CC4
#define IR_IRQChannel TIM2_IRQChannel

#define IR_RELOAD_VAL 0x10000

#define IR_PIN GPIO_Pin_3

#define IR_TIME_HANDLER_PERIOD (100)
#define IR_INACTIVE_AFTER_X_MS  _MS2TICK(2500) // x ms���ж�Ϊ�Ѿ����ź���

#define IR_WORK_FREQUENCY (1000*1000)
#define IR_WORK_CLOCK_PSC  (OS_CLOCK/IR_WORK_FREQUENCY)

typedef union {
    struct {
        unsigned  count : 5;         //bit0~bit4
        unsigned  isCapHighLevel : 1;
        unsigned  isCapOver : 1;
        unsigned  isOverflow : 1;
    }bits;
    INT8U status;
}CaptureStatus;

typedef struct {
    INT32U activeTimeStamp;
    INT32U frequency;
}IRMeasureStatus;

typedef struct {
    INT32U	workFreq;
    INT16U	preScale;
    INT32U	Perio;      //arr
} IR_CFG;
IR_CFG  g_IRCfg;
static CaptureStatus g_captureStatus; //���벶��״̬  
static IRMeasureStatus g_IRMeasureStatus; //���벶��״̬        
static TIMER* TmrIR;

static INT32U IR_calcFrequnecy(INT32U rawCounts);

/**
 * ��ʱ�� ͨ��1���벶������
 */
void TIME_Cap_Init(IR_CFG* config)
{
    //GPIO_InitTypeDef GPIO_InitStructure;
    TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
    TIM_ICInitTypeDef TIM_ICInitStructure;
    NVIC_InitTypeDef NVIC_InitStructure;

    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);    /*ʹ��IR_TIMEʱ��*/
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE); /*ʹ��GPIOAʱ��*/

    /*��ʼ����ʱ�� IR_TIME*/
    TIM_TimeBaseStructure.TIM_Period = (INT16U)(config->Perio - 1); /*�趨�������Զ���װֵ */
    TIM_TimeBaseStructure.TIM_Prescaler = config->preScale - 1; /*Ԥ��Ƶ�� */
    TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1; /*����ʱ�ӷָ�:TDTS = Tck_tim*/
    TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up; /*TIM���ϼ���ģʽ*/
    TIM_TimeBaseInit(IR_TIME, &TIM_TimeBaseStructure); /*����TIM_TimeBaseInitStruct��ָ���Ĳ�����ʼ��TIMx��ʱ�������λ*/

    /* ��ʼ��IR_TIME���벶����� */
    TIM_ICInitStructure.TIM_Channel = IR_TIME_CHANNLE; /* ѡ�������ͨ��*/
    TIM_ICInitStructure.TIM_ICPolarity = TIM_ICPolarity_Rising; /*�����ز���*/
    TIM_ICInitStructure.TIM_ICSelection = TIM_ICSelection_DirectTI; /*ӳ�䵽TI1��*/
    TIM_ICInitStructure.TIM_ICPrescaler = TIM_ICPSC_DIV1; /*���������Ƶ,����Ƶ*/
    TIM_ICInitStructure.TIM_ICFilter = 1; /*IC1F=0000 ���������˲��� 0x0~0x0F */
    TIM_ICInit(IR_TIME, &TIM_ICInitStructure);

    /*�жϷ����ʼ��*/
    NVIC_InitStructure.NVIC_IRQChannel = IR_IRQChannel;    /*IR_TIME�ж�*/
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0; /*��ռ���ȼ�2��*/
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 5; /*�����ȼ�0��*/
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; /*IRQͨ����ʹ��*/
    NVIC_Init(&NVIC_InitStructure);

    TIM_OC1PolarityConfig(IR_TIME, TIM_ICPolarity_Rising); //init ����Ϊ�����ز���
    TIM_ITConfig(IR_TIME, TIM_IT_Update | IR_IT_CHANNLE, ENABLE);/*��������ж� ,����CC1IE�����ж�*/
    TIM_Cmd(IR_TIME, ENABLE); /*ʹ�ܶ�ʱ��*/
}

/**
 * ��ʱ���жϷ������
 */
__inline void IR_TIME_IRQHandler_ISR(void)
{
    INT16U isUpdate = TIM_GetITStatus(IR_TIME, TIM_IT_Update);
    INT16U isChannle = TIM_GetITStatus(IR_TIME, IR_IT_CHANNLE);

    if (!g_captureStatus.bits.isCapOver) { //��δ�ɹ�����  
        // ����CNT��ֵ������ARR��ʱ����Ҫ����װ��CNT��Ҳ������ν�ĸ��£�����ô�Ϳ��Դ��������ж�
        if (isUpdate != RESET) { // re-load value   
            if (++g_captureStatus.bits.count == 0) {//�ߵ�ƽ̫����
                if (g_captureStatus.bits.isCapHighLevel) {//�Ѿ����񵽸ߵ�ƽ��
                    g_captureStatus.status = 0;
                    g_captureStatus.bits.isOverflow = TRUE;
                }
            }
        }
    }

    if (isChannle != RESET) {
        g_IRMeasureStatus.activeTimeStamp = RTC_GetSysTick();
        if (g_captureStatus.bits.isCapHighLevel) { // step2 ֮ǰ�Ѿ��й������ش������������̽���
            INT32U countVal = TIM_GetCounter(IR_TIME);
            INT32U rawCounts = g_captureStatus.bits.count * IR_RELOAD_VAL + countVal;
            g_IRMeasureStatus.frequency = IR_calcFrequnecy(rawCounts);             
            g_captureStatus.status = 0; //���
            g_captureStatus.bits.isCapOver = TRUE;        //��ǳɹ�����һ��������

            TIM_OC1PolarityConfig(IR_TIME, TIM_ICPolarity_Rising); //CC1P=0 ����Ϊ�����ز���
        } else { // step1 ���񵽣������ش���������״̬���޸ĳ� �½�����ģʽ
            TIM_OC1PolarityConfig(IR_TIME, TIM_ICPolarity_Falling);        //CC1P=1 ����Ϊ�½��ز���
            TIM_SetCounter(IR_TIME, 0);

            g_captureStatus.status = 0; //���
            g_captureStatus.bits.isCapHighLevel = TRUE; //��ǲ�����������
        }
    }

    INT16U itVal = 0;
    if (isUpdate) {
        itVal |= TIM_IT_Update;
    }
    if (isChannle) {
        itVal |= IR_IT_CHANNLE;
    }
    TIM_ClearITPendingBit(IR_TIME, itVal); /*����жϱ�־λ*/
}

// PA0,PA1,PA2,PA3 ; remap:PA0,PA1,PB10,PB11
//����ʹ�� PA3 ���в���
void IR_InitPin(void)
{
    /* GPIOA clock enable */;
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE); //��������˿�PA��ʱ��

    /* GPIOA_0 */;
    GPIO_InitTypeDef GPIO_InitStructure;
    GPIO_InitStructure.GPIO_Pin = IR_PIN; /**/
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD; /*PA0 ����*/
    GPIO_Init(GPIOA, &GPIO_InitStructure);
    GPIO_ResetBits(GPIOA, IR_PIN); /*PA0 ����*/
}

/*
32��Ƶ��1M ������1000 * 1000�� / 1s
Ƶ�� = 1s�ܸ��� / ʵ�����ĸ���
1s�ܸ��� = PWMƵ�� * ʵ�����ĸ���
1s�ܸ��� = ʵ�����ĸ��� / PWM����
1���ܸ��� * PWM���� = ʵ�����ĸ���
*/

/// <summary>
/// ����������rawCounts������Ƶ��freq
/// </summary>
/// <param name="rawCounts"></param>
/// <returns></returns>
static INT32U IR_calcFrequnecy(INT32U rawCounts)
{
    INT32U freq = 0;
    rawCounts++;
    if (rawCounts != 0) {
        freq = ((IR_WORK_FREQUENCY * 10) / rawCounts + 5) /10; // �÷Ŵ�10�ķ�����ʵ����������
    }
    return freq;
}

static void IR_main(void)
{
    if (RTC_MsOffSet(g_IRMeasureStatus.activeTimeStamp) > IR_INACTIVE_AFTER_X_MS) {
        g_captureStatus.status = 0;
        return;
    }
    if (g_captureStatus.bits.isOverflow == TRUE) {
        g_captureStatus.bits.isOverflow = FALSE;
        IRE_DEBUG(("IR Overflow\n"));
        return;
    }
    if (g_IRMeasureStatus.frequency) {
        TM1637_DisplayVal(DISPLAY_TYPE_FREQUENCY, g_IRMeasureStatus.frequency, 2000);
    } else {
        return;
    }
}

static void IR_getIRDefaultConfig(IR_CFG* config)
{
    config->workFreq = IR_WORK_FREQUENCY;
    config->Perio = IR_RELOAD_VAL;
    config->preScale = OS_CLOCK / config->workFreq;
}
static void IR_Init(void)
{
    IR_getIRDefaultConfig(&g_IRCfg);
    TIME_Cap_Init(&g_IRCfg);    //��1Mhz��Ƶ�ʼ���
    IR_InitPin();

    TmrIR = CreateTimer(IR_main);
    StartTimer(TmrIR, _MS(IR_TIME_HANDLER_PERIOD));

	return;
}

CoreInitCall(IR_Init);

