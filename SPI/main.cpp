#include <stm32f10x.h> 
#include "delay.h"
#include "lcd.h" 

uint8_t SPI_Communicate(char tx_data)
{
		while(!(SPI1->SR & SPI_SR_TXE)) ; 
		SPI1 -> DR = tx_data++ ; 
		while(!(SPI1->SR & SPI_SR_RXNE)) ;
		uint8_t dummy = SPI1 -> DR ; 
		if(SPI1->SR & (1<<6))
		{		
				clr_lcd() ; 
				lcd("OVRR") ;       // Indicate overrun error
				delayms(800) ; 
		}
		if(SPI1->SR & (1<<5))
		{		
				clr_lcd() ; 	
				lcd("MODD") ;			// Indicate Mode Fault Error.
				delayms(800) ; 
		}
		//lcd((char)dummy) ; 
		return dummy ; // SPI1 -> DR ;
}

int main()
{
	SystemInit()  ;
	init_lcd() ; 
	
	RCC -> APB2ENR |= RCC_APB2ENR_SPI1EN  | RCC_APB2ENR_IOPAEN  ;
	
	/* PA4->NSS -> I/P Floating Hardware master /slave NSS o/p Disabled , PA5 -> SCK -> Input Floating , PA6 -> MISO -> AFIO Push-pull , PA7 -> MOSI -> INPUT Floating */
	
	GPIOA -> CRL &= ~(1<<24) & ~(1<<27) & ~(1<<25) & ~(1<<26)   ;
	GPIOA -> CRL |= (1<<24) | (1<<27)   ; 
	uint8_t tx_data = 0x00 ;  
	uint8_t rx_data ; 
	SPI1 -> CR1 = 0x00000000 ; 
	SPI1 -> CR1 |= (SPI_CR1_SPE) ; 
		
	while(1) 
	{
		clr_lcd() ; 
		rx_data = SPI_Communicate(tx_data++) ; 
		lcd_data(SPI_Communicate(tx_data++)) ;
		//SPI_Communicate(tx_data++) ; 		
		delayms(200) ; 
	
	}
}
