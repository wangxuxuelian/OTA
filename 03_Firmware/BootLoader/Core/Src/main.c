/**
  ******************************************************************************
  WeAct 微行创新
  >> 标准库实例例程
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/

#define LOG_TAG    "wifi.proto"
#define LOG_LVL    ELOG_LVL_DEBUG
#include "main.h"
#include "tim.h"
#include "gpio.h"
#include "uart.h"
#include "string.h"
#include "elog.h"
#include "flash.h"
// 全局定义 STM32F411xE 或者 STM32F401xx
// 当前定义 STM32F411xE

// STM32F411 外部晶振25Mhz，考虑到USB使用，内部频率设置为96Mhz
// 需要100mhz,自行修改system_stm32f4xx.c

/** @addtogroup Template_Project
 * @{
 */

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
static __IO uint32_t uwTimingDelay;
RCC_ClocksTypeDef RCC_Clocks;

/* Private function prototypes -----------------------------------------------*/

/* Private functions ---------------------------------------------------------*/
/*
 *power by WeAct Studio
 *The board with `WeAct` Logo && `version number` is our board, quality guarantee.
 *For more information please visit: https://github.com/WeActTC/MiniF4-STM32F4x1
 *更多信息请访问：https://gitee.com/WeActTC/MiniF4-STM32F4x1
 */
/**
 * @brief  Main program
 * @param  None
 * @retval None
 */
int main(void)
{
    /* Enable Clock Security System(CSS): this will generate an NMI exception
       when HSE clock fails *****************************************************/
    RCC_ClockSecuritySystemCmd(ENABLE);

    /*!< At this stage the microcontroller clock setting is already configured,
          this is done through SystemInit() function which is called from startup
          files before to branch to application main.
          To reconfigure the default setting of SystemInit() function,
          refer to system_stm32f4xx.c file */

    /* SysTick end of count event each 1ms */
    SystemCoreClockUpdate();
    RCC_GetClocksFreq(&RCC_Clocks);
    SysTick_Config(RCC_Clocks.HCLK_Frequency / 1000);

    /* Add your application code here */
    /* Insert 50 ms delay */
    Delay(50);
    /*Configure NVIC */
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_4);

    TIM_Config();
    init_uart();
    key_init();
    led_init();

    // elog init
    elog_init();
    elog_start();
    /* 断言：输出所有内容 */
    elog_set_fmt(ELOG_LVL_ASSERT, ELOG_FMT_ALL);
    /* 错误：输出级别、标签和时间 */
    elog_set_fmt(ELOG_LVL_ERROR, ELOG_FMT_LVL | ELOG_FMT_TAG | ELOG_FMT_TIME);
    /* 警告：输出级别、标签和时间 */
    elog_set_fmt(ELOG_LVL_WARN, ELOG_FMT_LVL | ELOG_FMT_TAG | ELOG_FMT_TIME);
    /* 信息：输出级别、标签和时间 */
    elog_set_fmt(ELOG_LVL_INFO, ELOG_FMT_LVL | ELOG_FMT_TAG | ELOG_FMT_TIME);
    /* 调试：输出除了方法名之外的所有内容 */
    elog_set_fmt(ELOG_LVL_DEBUG, ELOG_FMT_ALL & ~ELOG_FMT_FUNC);
    /* 详细：输出除了方法名之外的所有内容 */
    elog_set_fmt(ELOG_LVL_VERBOSE, ELOG_FMT_ALL & ~ELOG_FMT_FUNC);
    /* Infinite loop */


    if (EreaseAppSector(FLASH_Sector_6) == FLASH_COMPLETE) {
        Flash_Write(0x08040000,0x55555555);
    }

    uint8_t buff[1024];
    uint32_t num;
    while (1) {

        char name[20] = "xuelian\n";
        send_datas((uint8_t const *)name, 9);
        elog_raw("wangxu loves lvxueian \n");
        breathing_light();
        //receive_datas(buff, 1024, &num);
        //buff[num] = '\0';
        //elog_raw("%s", buff);


        elog_a(LOG_TAG, "xuelian\n");
        elog_assert("xuelian", "aini\n");
        log_a("wangxu\n");
        log_a("xuelian");
        ELOG_ASSERT(1 == 0);  
        Delay(10);
    }
}

/**
 * @brief  Inserts a delay time.
 * @param  nTime: specifies the delay time length, in milliseconds.
 * @retval None
 */
void Delay(__IO uint32_t nTime)
{
    uwTimingDelay = nTime;

    while (uwTimingDelay != 0)
        ;
}

/**
 * @brief  Decrements the TimingDelay variable.
 * @param  None
 * @retval None
 */
void TimingDelay_Decrement(void)
{
    if (uwTimingDelay != 0x00)
    {
        uwTimingDelay--;
    }
}

#ifdef USE_FULL_ASSERT

/**
 * @brief  Reports the name of the source file and the source line number
 *         where the assert_param error has occurred.
 * @param  file: pointer to the source file name
 * @param  line: assert_param error line source number
 * @retval None
 */
void assert_failed(uint8_t *file, uint32_t line)
{
    /* User can add his own implementation to report the file name and line number,
       ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */

    /* Infinite loop */
    while (1)
    {
    }
}
#endif

/**
 * @}
 */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
