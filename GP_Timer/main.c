#include "stm32f4xx.h"                  // Device header

void delay (uint32_t ms)
{
	RCC->APB1ENR |= (1<<1) ; 		// Enable clock to timer 3 
	TIM3->PSC = 15999;	      // Set prescaler to 16000 (PSC + 1) , since CLK = 16MHz 
        TIM3->ARR = ms;	            // Auto reload value 
	TIM3->CR1 = TIM_CR1_CEN			 // Enable timer 3, TIM_CR1_CEN and TIM_SR_UIF are defined in Device Header. 
        while((TIM3->SR & TIM_SR_UIF)==0) ; 								
        TIM3->SR &= ~TIM_SR_UIF;	
}

int main()
{

	/* DEFAULT CLK = 16MHz for STM32F4 Discovery Board. */
	//SystemInit() ;  
	 
	RCC -> AHB1ENR |= (1<<3) ;  // enable GPIOD clock  
	GPIOD -> MODER |= (1<<24) ; 		// Set PD12 to GPIO output
	
	while(1)
	{
	GPIOD -> ODR |= (1<<12) ; 	// Set PD12
	delay(1000) ; 
	GPIOD -> ODR &= ~(1<<12) ; 		//RESET PD12 
	delay(1000) ;
	}		
}
