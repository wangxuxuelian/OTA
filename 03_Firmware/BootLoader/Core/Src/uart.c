/**
  ******************************************************************************
  * @file    uart.c
  * @author  山海照星河 && iswangxu150@163.com
  * @brief   provid io functions of uart1.
  * @version 1.0.0
  * @date    2025-03-10
  *
  ******************************************************************************
  * @attention
  *
  * Copyright (c).
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
    @verbatim
  ==============================================================================
                    ##### uart Peripheral features #####
  ==============================================================================





                    ##### How to use this driver #####
  ==============================================================================





**/

#include "uart.h"
#include "stm32f4xx_usart.h"
#include "stm32f4xx.h"

volatile uint32_t IDLE_FLAG = 0;



int init_uart(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE);
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);
    GPIO_PinAFConfig(GPIOA, GPIO_PinSource9, GPIO_AF_USART1);
    GPIO_PinAFConfig(GPIOA, GPIO_PinSource10, GPIO_AF_USART1);


    USART_InitTypeDef USART1_structure;
    USART1_structure.USART_BaudRate             = 115200;
    USART1_structure.USART_HardwareFlowControl  = USART_HardwareFlowControl_None;
    USART1_structure.USART_Mode                 = USART_Mode_Tx | USART_Mode_Rx;
    USART1_structure.USART_Parity               = USART_Parity_No;
    USART1_structure.USART_StopBits             = USART_StopBits_1;
    USART1_structure.USART_WordLength           = USART_WordLength_8b;
    USART_Init(USART1, &USART1_structure);

    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
    GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;  
    GPIO_Init(GPIOA, &GPIO_InitStructure);

    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
    GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP; 
    GPIO_Init(GPIOA, &GPIO_InitStructure);

    USART_ITConfig(USART1, USART_IT_IDLE, ENABLE);

    NVIC_InitTypeDef nvic_structure;
    nvic_structure.NVIC_IRQChannel                   = USART1_IRQn;
    nvic_structure.NVIC_IRQChannelCmd                = ENABLE;
    nvic_structure.NVIC_IRQChannelPreemptionPriority = 5;
    nvic_structure.NVIC_IRQChannelSubPriority        = 0;

    NVIC_Init(&nvic_structure);
    USART_Cmd(USART1, ENABLE);
    return 0;
}

static int send_data(uint16_t data)
{
    USART_SendData(USART1, data);
    while (USART_GetFlagStatus(USART1, USART_FLAG_TXE) == RESET) {
        ;
    }
    return 0;
}

int send_datas(uint8_t const *data, uint32_t const size)
{
    uint8_t *tmp = (uint8_t *)data;
    uint32_t i = 0;
    for (i = 0; i < size; i++) {
        send_data((uint16_t)*tmp);
        tmp++;
    }
    return size;
}


/// @brief receive a byte data.
/// @param data 
/// @return -1(idle), 0(receive a byte)
int receive_data(uint8_t *data)
{
    
    while (USART_GetFlagStatus(USART1, USART_FLAG_RXNE) == RESET) {
        /*空闲状态*/
        if (IDLE_FLAG == 1) {
            IDLE_FLAG = 0;
            return -1;
        }
    }

    *data = (uint8_t) USART_ReceiveData(USART1);
    return 0;
}

/// @brief  接收数据直到IDLE  暂不处理buffer 不够的情况
/// @param buff 
/// @param size 
/// @return 
int receive_datas(uint8_t *buff, uint32_t size, uint32_t *num)
{
    int    ret_val = 0; 
    uint32_t count = 0;
    for (; size > 0; size--) {
        ret_val = receive_data(buff);
        if (ret_val == 0) {
            buff++;
            count++;
        } else {
            *num = count;
            return 0;
        }
        
    }
    /* memory not enough*/
    *num = count;
    return -1;
}
