/**
  ******************************************************************************
	WeAct 微行创新 
	>> 标准库 GPIO
  ******************************************************************************
  */

#ifndef __gpio_H
#define __gpio_H

#ifdef __cplusplus
 extern "C" {
#endif 
/*Include---------------------------------------------------------------------*/
#include "stm32f4xx.h"
#include "main.h"


/*Exported fuctions-----------------------------------------------------------*/

void key_init(void);
void led_init(void);

int key_scan(void);
void breathing_light(void);
#ifdef __cplusplus
}
#endif

#endif
