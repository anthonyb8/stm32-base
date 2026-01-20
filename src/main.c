#include "stm32f4xx_hal.h"

void SystemClock_Config(void);

int main(void)
{
  // Initialize HAL Library
  HAL_Init();
  
  // Configure system clock (optional for now, uses default HSI)
  SystemClock_Config();
  
  // GPIO configuration structure
  GPIO_InitTypeDef GPIO_InitStruct = {0};
  
  // Enable GPIOA clock
  __HAL_RCC_GPIOA_CLK_ENABLE();
  
  // Configure PA5 as output
  GPIO_InitStruct.Pin = GPIO_PIN_5;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;  // Push-pull output
  GPIO_InitStruct.Pull = GPIO_NOPULL;          // No pull-up/down
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW; // Low speed
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);
  
  // Main loop
  while(1)
  {
    // Toggle PA5
    HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_5);
    
    // Delay using HAL
    HAL_Delay(5);  // 500ms delay
  }
}

void SystemClock_Config(void)
{
  // Use default HSI clock (16 MHz) for now
  // You can configure PLL later for higher speeds
}

// Required for HAL_Delay to work
void SysTick_Handler(void)
{
  HAL_IncTick();
}

#ifdef USE_FULL_ASSERT
void assert_failed(uint8_t *file, uint32_t line)
{
  // User can add their own implementation to report the file name and line number
  // For example: printf("Wrong parameters value: file %s on line %d\r\n", file, line)
  
  // Infinite loop for debugging
  while (1)
  {
  }
}
#endif
