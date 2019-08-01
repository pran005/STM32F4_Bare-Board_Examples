#include <stm32f10x.h> 
#include "lcd.h" 
#include "delay.h" 

   

int main(void)
{	
	  SystemInit() ; 
  	RCC->APB2ENR |=  RCC_APB2ENR_ADC1EN | RCC_APB2ENR_IOPAEN; 
    init_lcd() ;    
	  GPIOA -> CRL &= ~ (1<<2) ; 
		ADC1 -> CR2 |= (1<<0) | (1<<1) ;
		ADC1 -> SMPR1 |= (1<<18) | (1<19)  ; 
	  ADC1 -> SQR3 |= (0<<0) ; 
    ADC1 -> CR1 |= (1<<5) ; 
	  NVIC_EnableIRQ(ADC1_IRQn) ;
		ADC1 -> CR2 |= (1<<0) ; 

}

extern "C" {
	
void ADC1_IRQHandler(void) 
{
		uint32_t data = ADC1 ->DR ; 
	  clr_lcd() ; 
		int moisture = ((4095 - data)*100/4095);  
		lcd((char*)"MOISTURE :") ; 
		lcd(moisture) ;
		lcd((char*)"%") ; 
	  delayms(1000) ; 
		

}
}  



