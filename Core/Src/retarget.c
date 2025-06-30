#include <retarget.h>
#include <stdio.h>

#define STDIN  0
#define STDOUT 1
#define STDERR 2

static UART_HandleTypeDef *gHuart;

int _isatty(int fd)
{
    return 1; // Always return true for simplicity
}
int _write(int fd, char* ptr, int len)
{
    if (fd == STDOUT || fd == STDERR) {
        HAL_UART_Transmit(gHuart, (uint8_t*)ptr, len, HAL_MAX_DELAY);
        return len; // Return number of bytes written
    }
    return -1; // Error for other file descriptors
}
int _close(int fd)
{
    return -1; // Not implemented, return error
}
int _read(int fd, char* ptr, int len)
{
    if (fd == STDIN) {
        HAL_UART_Receive(gHuart, (uint8_t*)ptr, len, HAL_MAX_DELAY);
        return len; // Return number of bytes read
    }
    return -1; // Error for other file descriptors
}
int _fstat(int fd, struct stat* st)
{
    st->st_mode = S_IFCHR; // Character device
    return 0; // Success
}

void RetargetInit(UART_HandleTypeDef *huart)
{
    // Initialize the UART for retargeting
    gHuart = huart; // Assuming gHuart is defined globally in your project
    // HAL_UART_Init(gHuart);

/* Disable I/O buffering for STDOUT stream, so that
  * chars are sent out as soon as they are printed. */
    setvbuf(stdout, NULL, _IONBF, 0);
}