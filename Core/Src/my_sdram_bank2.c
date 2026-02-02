#include "fmc.h"
#include "stm32f4xx_hal_sdram.h"

void test_sdram_bank2(void)
{
    uint32_t write_data[4] = {0xDEADBEEF, 0xCAFEBABE, 0xBAADF00D, 0xFEEDFACE};
    uint32_t read_data[4] = {0};

    // Write data to SDRAM Bank 2
    for (uint32_t i = 0; i < 4; i++) {
        *(volatile uint32_t *)(0xD0000000 + i * 4) = write_data[i];
    }

    // Read data back from SDRAM Bank 2
    for (uint32_t i = 0; i < 4; i++) {
        read_data[i] = *(volatile uint32_t *)(0xD0000000 + i * 4);
    }

    // Verify the data
    for (uint32_t i = 0; i < 4; i++) {
        if (read_data[i] != write_data[i]) {
            // Handle error (data mismatch)
            while(1);
        }
    }
    // If we reach here, the test passed
}
