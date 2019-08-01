#include <stm32f10x.h> 
#include "lcd.h" 
#include "delay.h" 
#include <stdio.h> 
#include <string.h>

/*************************ALWAYS USE PULLUPS WITH HC05 FOR MAX. SUCCESS***************************************/  

void init_UART()
{
	RCC->APB2ENR |= RCC_APB2ENR_IOPAEN | RCC_APB2ENR_USART1EN ;  // enable clocks
	
	GPIOA -> CRH |= (1<<4) | (1<<7)  ;				// set up GPIOs 
	
  USART1 -> BRR = 0x9C4 ;  		// set baudrate = 9600 
	USART1 -> CR1 |= (1<<13) | (1<<3) | (1<<2) | (1<<5) ; // Enable USART | Enable Rx and Tx | Enable Rx Not EMpty Interrupt

}	

/** TRANSMIT CHARACTER **/ 
void UART_tx(char data) 
{
  while(!(USART1->SR & USART_SR_TXE));
  USART1->DR = data; 
}

void UART_tx(int data) 
{
  while(!(USART1->SR & USART_SR_TXE));
  USART1->DR = data; 
}

void UART_tx(uint8_t data) 
{
  while(!(USART1->SR & USART_SR_TXE));
  USART1->DR = data; 
}
/** TRANSMIT String **/ 
void UART_tx(char *string) 
{
	while(*string) 
		UART_tx(*string++) ; 
}
/** Receive CHARACTER **/ 
unsigned char UART_rx()
{
	while((USART1->SR & (1<<5))==0) ;			// wait to Recieve
		return USART1->DR ; 
}

/** Receive string | @Argument : pointer to string buffer **/ 
void UART_str(char* string)
{
	unsigned char i=0,j=0 ; 
	do
	{
		*(string+i) = UART_rx() ; 
		j = *(string+i) ; 
		i++ ; 
	
	}
	while((j != '\r') && (j!='\n')) ;
		i++ ; 
	  *(string+i) = '\0' ; 
}

int main(void)
{	
	  SystemInit() ; 
  	RCC->APB2ENR |=   RCC_APB2ENR_ADC1EN | RCC_APB2ENR_IOPAEN;
    GPIOA -> CRL = 0x0000000000000000; 	
    init_lcd() ;    
	  init_UART() ; 
		ADC1 -> CR2 |= (1<<0) | (1<<1)| (1<<23)   ;
		ADC1 -> SMPR1 &=  ~(1<<18) ; 
		ADC1 -> SQR3 |= (1<<4) ;
    //ADC1 -> CR2 |= (1<<23) ; 	
    ADC1 -> CR1 |= (1<<5); 
	  NVIC_EnableIRQ(ADC1_IRQn) ;
		ADC1 -> CR2 |= (1<<0) ; 
		
}

extern "C" {
	
void ADC1_IRQHandler(void) 
{
	  uint32_t data = ADC1 ->DR ; 
		float v25 = 1.42 ; 
		float vsense = data*(3.3/4096) ; 
		int16_t temp = ((vsense - v25)/4.6) + 25 ; 
	  clr_lcd() ; 
  	lcd((char*)"Chip Temperature : ") ; 
		cmd(0xC0) ; 
		lcd(temp) ;
	  char c[20] ;
		memset(c,0,20) ; 
	  sprintf(c,"Chip Temp : %d °C\r\n", temp) ;  
		UART_tx(c) ; 
		lcd((char*)" °C") ; 
	  delayms(1000) ; 
		//ADC1 -> CR2 |= (1<<0) | (1<<22)  ; 
}
}  
