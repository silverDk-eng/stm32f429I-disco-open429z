
#include "stm32f4xx_hal.h"
#include "usart.h"
#include "my_usart.h"

#include <stdarg.h>
#include <stdio.h>
#include <string.h>
#include "../../Drivers/STM32F4xx_HAL_Driver/Inc/stm32f4xx_hal.h"
#include "../../Drivers/STM32F4xx_HAL_Driver/Inc/stm32f4xx_ll_usart.h"
#include "../../Drivers/STM32F4xx_HAL_Driver/Inc/stm32f4xx_ll_dma.h"

LL_USART_InitTypeDef USART1_InitStruct;
LL_DMA_InitTypeDef DMA_USART1_TX_InitStruct;
LL_DMA_InitTypeDef DMA_USART1_RX_InitStruct;

#define RX_FIFO_SIZE 256

typedef struct {
  uint8_t buffer[RX_FIFO_SIZE];
  uint16_t head;
  uint16_t tail;      
} rxtx_fifo_t;

rxtx_fifo_t uart1_rx_fifo = { .head = 0, .tail = 0 };
rxtx_fifo_t uart5_rx_fifo = { .head = 0, .tail = 0 };

#define RX_BUFFER_SIZE (128)
uint8_t rxBuffer_it[RX_BUFFER_SIZE];

#if 0
void user_usart1_init(void)
{
  /* USER CODE BEGIN USART1_Init 0 */

  /* USER CODE END USART1_Init 0 */

  /* USER CODE BEGIN USART1_Init 1 */

  /* USER CODE END USART1_Init 1 */

  USART1_InitStruct.BaudRate = 115200;
  USART1_InitStruct.DataWidth = LL_USART_DATAWIDTH_8B;
  USART1_InitStruct.StopBits = LL_USART_STOPBITS_1;
  USART1_InitStruct.Parity = LL_USART_PARITY_NONE;
  USART1_InitStruct.TransferDirection = LL_USART_DIRECTION_TX_RX;
  USART1_InitStruct.HardwareFlowControl = LL_USART_HWCONTROL_NONE;
  USART1_InitStruct.OverSampling = LL_USART_OVERSAMPLING_16;
  if (LL_USART_Init(USART1, &USART1_InitStruct) != SUCCESS)
  {
    Error_Handler();
  }

    DMA_USART1_TX_InitStruct.Direction = LL_DMA_DIRECTION_MEMORY_TO_PERIPH;
    DMA_USART1_TX_InitStruct.PeriphOrM2MSrcAddress = (uint32_t)&USART1->DR;
    DMA_USART1_TX_InitStruct.MemoryOrM2MDstAddress = (uint32_t)rxBuffer;
    DMA_USART1_TX_InitStruct.PeriphOrM2MSrcIncMode = LL_DMA_PERIPH_NOINCREMENT;
    DMA_USART1_TX_InitStruct.MemoryOrM2MDstIncMode = LL_DMA_MEMORY_INCREMENT;
    DMA_USART1_TX_InitStruct.PeriphOrM2MSrcDataSize = LL_DMA_PDATAALIGN_BYTE;                 
    DMA_USART1_TX_InitStruct.MemoryOrM2MDstDataSize = LL_DMA_MDATAALIGN_BYTE;
    DMA_USART1_TX_InitStruct.Mode = LL_DMA_MODE_NORMAL;
    DMA_USART1_TX_InitStruct.NbData = RX_BUFFER_SIZE;
    if (LL_DMA_Init(DMA2, LL_DMA_STREAM_7, &DMA_USART1_TX_InitStruct) != SUCCESS)
    {
        Error_Handler();
    }
}
#endif

int getkey(void)
{
    uint8_t ch = 0;    
    /* Wait until RXNE flag is set */
    while (!LL_USART_IsActiveFlag_RXNE(UART5))
    {
    }
    /* Read received character */
    ch = LL_USART_ReceiveData8(UART5);
    return ch;
}

int putchar_uart5(int ch)
{
    /* Wait until TXE flag is set */
    while (!LL_USART_IsActiveFlag_TXE(UART5))
    {
    }
    /* Transmit character */
    LL_USART_TransmitData8(UART5, (uint8_t)ch);
    return ch;
}

void my_iprintf(const char *fmt, ...)
{
    char buffer[128];
    va_list args;
    va_start(args, fmt);
    int len = vsnprintf(buffer, sizeof(buffer), fmt, args);
    va_end(args);

    for (int i = 0; i < len; i++) {
        putchar_uart5(buffer[i]);
    }
}



void fifo_put(rxtx_fifo_t *fifo, uint8_t data)
{
    fifo->buffer[fifo->head] = data;
    fifo->head = (fifo->head + 1) % sizeof(fifo->buffer);
}
uint8_t fifo_get(rxtx_fifo_t *fifo)
{
    uint8_t data = fifo->buffer[fifo->tail];
    fifo->tail = (fifo->tail + 1) % sizeof(fifo->buffer);
    return data;
}
int fifo_is_empty(rxtx_fifo_t *fifo)
{
    return fifo->head == fifo->tail;
}
int fifo_is_full(rxtx_fifo_t *fifo)
{
    return ((fifo->head + 1) % sizeof(fifo->buffer)) == fifo->tail;
}
// void USART1_IRQHandler(void)
// {
//     if (LL_USART_IsActiveFlag_RXNE(USART1))
//     {
//         uint8_t ch = LL_USART_ReceiveData8(USART1);
//         fifo_put(&uart1_rx_fifo, ch);
//     }
// }


int uart_getchar_nonblocking(uint8_t *ch, rxtx_fifo_t *fifo)
{
    if (fifo_is_empty(fifo)) {
        return 0; // No data available
    }
    *ch = fifo_get(fifo);
    return 1; // Data retrieved
}
int uart_putchar_nonblocking(uint8_t ch)
{
    if (LL_USART_IsActiveFlag_TXE(USART1))
    {
        LL_USART_TransmitData8(USART1, ch);
        return 1; // Character sent
    }
    return 0; // TXE not set, character not sent
}
int uart_putchar_blocking(uint8_t ch)
{
    while (!LL_USART_IsActiveFlag_TXE(USART1))
    {
    }
    LL_USART_TransmitData8(USART1, ch);
    return 1; // Character sent
}
int uart_getchar_blocking(uint8_t *ch)
{
    while (fifo_is_empty(&uart1_rx_fifo)) {
    }
    *ch = fifo_get(&uart1_rx_fifo);
    return 1; // Data retrieved
}

/* < strtok >
내부 원리
정적(static) 포인터를 내부에 저장
다음 호출에서 이전 위치부터 계속 탐색
구분자를 '\0'으로 직접 덮어씀

"C M D , 1 2 3 , A B C \0"
 ↓
"C M D \0 1 2 3 \0 A B C \0"

3️⃣ strtok의 치명적 문제점 🚨
❌ 1. Thread-safe 아님
내부 static 상태 공유
RTOS 멀티 태스크에서 충돌
❌ 2. ISR에서 사용 불가
재진입 불가
상태 꼬임
❌ 3. const 문자열 사용 불가
4️⃣ 언제 strtok을 써도 되는가? ✅
✔ 단일 스레드
✔ 로컬 버퍼
✔ 임시 파싱
✔ RTOS 아님 or 보호됨

👉 PC 툴 / 테스트 코드 / 간단 CLI
5️⃣ strtok_r (권장 ⭐⭐⭐)
reentrant 버전
*/
#define cmd_line_size (64)
static char cmd_line[cmd_line_size];
static int cmd_index = 0;

static char *args[10]; // 최대 10개의 인수
static int arg_count = 0;
const int arg_max_count = 10;

static int command_parser(char *p_cmd_line, size_t len)
{
    char *saveptr;    
    
    if(len >= cmd_line_size)
        len = cmd_line_size - 1;

    p_cmd_line[len] = '\0'; // Ensure null termination

    // if (strcmp(p_cmd_line, "exit") == 0) {
    //     my_iprintf("Exiting command processor.\r\n");
    //     return 1;
    // }

    int ret = 0;
    arg_count = 0;  
    
    args[arg_count++] = strtok_r(p_cmd_line, " ", &saveptr); // Get the command part
    //my_iprintf("Command received: %s\r\n", cmd);
    if(args[0] == NULL)
        return 0;
    else
        ret = 1;
    

    while((args[arg_count] = strtok_r(NULL, " ", &saveptr)) != NULL) {
        ++arg_count;
        if(arg_count >= arg_max_count) // 최대 인수 개수 제한
            break;       
    }    

    return ret;
}

typedef struct
{
    const char *name;
    int (*func)(char *const argv[], int argc);
} command_t;

int led_on_command(char *const argv[], int argc)
{
    // my_iprintf("LED ON command executed.\r\n");
    HAL_GPIO_WritePin(GPIOG, LD3_GRN_Pin, GPIO_PIN_SET);
    HAL_GPIO_WritePin(GPIOG, LD4_RED_Pin, GPIO_PIN_SET);
    return 0;
}
int led_off_command(char *const argv[], int argc)
{
    // my_iprintf("LED OFF command executed.\r\n");
    HAL_GPIO_WritePin(GPIOG, LD3_GRN_Pin, GPIO_PIN_RESET);
    HAL_GPIO_WritePin(GPIOG, LD4_RED_Pin, GPIO_PIN_RESET);
    return 0;
}
command_t command_table[] = {
    {"led_on", led_on_command},
    {"led_off", led_off_command},
    {NULL, NULL} // 테이블 종료 표시
};

static int command_executor(const char *cmd, char *const argv[], int argc)
{
    for(int i = 0; command_table[i].name != NULL; i++)
    {
        if(strcmp(cmd, command_table[i].name) == 0)
        {
            if(command_table[i].func != NULL)
            {
                return command_table[i].func(argv, argc);
            }
            break;
        }
    }

    // if(strcmp(cmd, "led_on") == 0)
    // {
    //     my_iprintf("LED ON command executed.\r\n");
    // }
    // else if(strcmp(cmd, "led_off") == 0)
    // {
    //     my_iprintf("LED OFF command executed.\r\n");
    // }
    // else
    // {
    //     my_iprintf("Unknown command: %s\r\n", args[0]);
    // }
    return 0;
}

void command_processor_uart5(void)
{
    uint8_t ch;
    //my_iprintf("Enter commands (type 'exit' to quit):\r\n");
	#define command_size (256)
    static char command[command_size];

    if(!uart_getchar_nonblocking(&ch, &uart5_rx_fifo)) // Clear any existing data
        return;
    
/* 주요 줄바꿈 문자
Line Feed       LF 0x0A 커서를 한 줄 아래로 이동
Carriage Return CR 0x0D 커서를 현재 줄의 맨 앞으로 이동

Windows: CR + LF (\r\n)를 사용합니다. 타자기에서 종이를 한 줄 올리고(LF), 뭉치를 맨 왼쪽으로 미는(CR) 동작을 모두 수행하는 방식입니다.
Unix / Linux / macOS: LF (\n)만 사용합니다. 현대적인 시스템에서는 LF 하나만으로도 줄바꿈과 줄 시작점 이동을 동시에 의미하는 경우가 많습니다.
Old macOS (Classic): 아주 오래된 맥 OS에서는 CR (\r)만 사용하기도 했습니다.
*/        
    switch (ch)
    {
    	case 0x0D : //'\r': // Carriage Return
    		break;
        case 0x0A : //'\n': // Line Feed

            command[cmd_index] = '\0'; // Null-terminate the command
            char *end = memchr(command, '\0', sizeof(command));
            size_t len = 0;

            if(end)
            {
                len = end - command;
                memcpy(cmd_line, command, len + 1); // +1 to include null terminator
                cmd_line[len] = '\0'; // Ensure null termination                     
            }
            cmd_index = 0;    
            if(command_parser(cmd_line, len))
            {
                command_executor(args[0], &args[1], arg_count - 1);
            }
            break;
        case 0x1B : // ESC key
            cmd_index = 0; // Clear command buffer
            command[cmd_index] = '\0';
            break;
        case 0x08 :// Backspace '\b'              
            if(cmd_index)
                cmd_index--;                
            break;
        default:
            command[cmd_index++] = ch;
            break;
    }
    // while (1) {
    //     if (uart_getchar_blocking(&ch)) {
    //         if (ch == '\r' || ch == '\n') {
    //             command[cmd_index] = '\0'; // Null-terminate the command
    //             my_iprintf("\r\nYou entered: %s\r\n", command);
    //             if (strcmp(command, "exit") == 0) {
    //                 my_iprintf("Exiting command processor.\r\n");
    //                 break;
    //             }
    //             cmd_index = 0; // Reset for next command
    //             my_iprintf("Enter commands (type 'exit' to quit):\r\n");
    //         } else {
    //             if (cmd_index < sizeof(command) - 1) {
    //                 command[cmd_index++] = ch;
    //                 uart_putchar_blocking(ch); // Echo back
    //             }
    //         }
    //     }
    // }
}

void my_uart_init(void)
{
    MX_UART5_Init(); 
    HAL_UART_Receive_IT(&huart5, (uint8_t *)rxBuffer_it, 1);

    MX_USART1_UART_Init();
}

void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
    if(huart->Instance == UART5)
    {        
        fifo_put(&uart5_rx_fifo, rxBuffer_it[0]);  // Read received character       
        HAL_UART_Receive_IT(&huart5, (uint8_t *)rxBuffer_it, 1);
    }
    else if(huart->Instance == USART1){
        uint8_t ch = huart->Instance->DR; // Read received character
        fifo_put(&uart1_rx_fifo, ch);   
    }    
    /* Prevent unused argument(s) compilation warning */
    UNUSED(huart);
}
