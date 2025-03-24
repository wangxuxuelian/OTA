/**
  ******************************************************************************
    WeAct Î¢ÐÐ´´ÐÂ
    >> ±ê×¼¿â GPIO
  ******************************************************************************
  */

#include "gpio.h"

/*Exported fuctions-------------------------------------------------------------*/


void key_init(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;

    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;
    GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;

    GPIO_Init(GPIOA, &GPIO_InitStructure);
}
void led_init(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;

    /* Output HSE clock on MCO1 pin(PA8) ****************************************/
    /* Enable the GPIOA peripheral */
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);

    /* Configure MCO1 pin(PA8) in alternate function */
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
    GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
    GPIO_Init(GPIOA, &GPIO_InitStructure);

    /* HSE clock selected to output on MCO1 pin(PA8)*/
    RCC_MCO1Config(RCC_MCO1Source_HSE, RCC_MCO1Div_1);

    /* LED on C13 pin(PC13) ***********************************/
    /* Enable the GPIOCperipheral */
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC, ENABLE);
    

    /* Configure C13 pin(PC13) in output function */
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
    GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;

    GPIO_Init(GPIOC, &GPIO_InitStructure);
}

int key_scan(void)
{
    
    if (GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_0) == Bit_RESET) {
        Delay(40);
        if (GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_0) == Bit_RESET) {
            return 1;
        } else {
            return 0;
        }
    } else {
        return 0;
    }
}


void breathing_light(void)
{
    
    /* C13 ºôÎüµÆ²âÊÔ */
    static uint8_t pwmset;
    static uint16_t time;
    static uint8_t timeflag;
    static uint8_t timecount;

     /* ºôÎüµÆ */
    if(timeflag == 0)
    {
    	time ++;
    	if(time >= 1600) timeflag = 1;
    }
    else
    {
    	time --;
    	if(time == 0) timeflag = 0;
    }

    /* Õ¼¿Õ±ÈÉèÖÃ */
    pwmset = time/80;

    /* 20ms Âö¿í */
    if(timecount > 20) timecount = 0;
    else timecount ++;

    if(timecount >= pwmset ) GPIO_SetBits(LED_C13_PORT,LED_C13_PIN);
    else GPIO_ResetBits(LED_C13_PORT,LED_C13_PIN);

	Delay(1);

}
