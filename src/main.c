#include <stdint.h>
#include "stm32f446xx.h"


#define GPIOAEN               (1U<<0) // Left shift 1 bit at bit postion 0 = 0x0...01 
#define PIN5                  (1U<<5)
#define LED_PIN                PIN5 


int main(void)
{
  RCC->AHB1ENR |= GPIOAEN;

  GPIOA->MODER |= (1U<<10);
  GPIOA->MODER &=~ (1U<<11);

  while(1)
  {
    GPIOA->ODR ^= LED_PIN;
    for (int i=0;i<500000;i++){};
  }

};
