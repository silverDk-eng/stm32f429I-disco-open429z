#ifndef _MY_USART_H_
#define _MY_USART_H_    

// #include "../../Drivers/STM32F4xx_HAL_Driver/Inc/stm32f4xx_hal.h"
// #include "../../Drivers/STM32F4xx_HAL_Driver/Inc/stm32f4xx_ll_usart.h"

extern UART_HandleTypeDef *gHuart;
extern UART_HandleTypeDef huart5;
extern UART_HandleTypeDef huart1;

int getkey(void);
int sendchar(int ch);

#endif /* _MY_USART_H_ */