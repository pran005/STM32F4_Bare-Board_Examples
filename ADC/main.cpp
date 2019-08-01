#include <stm32f10x.h> 
#include "lcd.h" 
#include "delay.h" 

   

int main(void)
{	
	  SystemInit() ; 
  	  RCC->APB2ENR |=  RCC_APB2ENR_ADC1EN | RCC_APB2ENR_IOPAEN; //enable clocks
    	  init_lcd() ;    
	  GPIOA -> CRL &= ~ (1<<2) ;		 // analog in mode 
	  ADC1 -> CR2 |= (1<<0) | (1<<1) ;	// power ON ADC | Continous mode
	  ADC1 -> SMPR1 |= (1<<18) | (1<19)  ; // setup sample speed
	  ADC1 -> SQR3 |= (0<<0) ; 	      //setup sequence number
    	  ADC1 -> CR1 |= (1<<5) ; 	     //enable ADC interrupts
	  NVIC_EnableIRQ(ADC1_IRQn) ;		
	  ADC1 -> CR2 |= (1<<0) ;	   // Trigger Conversion		

}

extern "C" {
	
void ADC1_IRQHandler(void) 
{
		uint32_t data = ADC1 ->DR ; 
	  	clr_lcd() ; 
		int moisture = ((4095 - data)*100/4095);  //scale moisture from moisture sensor
		lcd((char*)"MOISTURE :") ; 
		lcd(moisture) ;
		lcd((char*)"%") ; 
	  	delayms(1000) ; 
		

}
}  



