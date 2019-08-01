#include <stm32f10x.h> 
#include "lcd.h" 
#include "delay.h" 


int main(void) 
{
	SystemInit() ; 
	delayms(30) ; 
	init_lcd() ; 
	while(1)
	{
	clr_lcd() ; 
	lcd((char*)"  GOOD MORNING   ") ;
	cmd(0xC0) ; 
	lcd((char*)"    TEACHERS   ") ;
  delayms(1000) ; 	
	clr_lcd() ; 
	lcd((char*)"  WELCOME TO  ") ;
  cmd(0xC0) ; 
	lcd((char*)"   REVIEW-I   ") ;
	clr_lcd() ; 
	lcd((char*)"  MINI PROJECT I  ") ;
  cmd(0xC0) ; 
	lcd((char*)"  STM32F100   ") ;	
	delayms(1000) ;
  clr_lcd() ; 
  lcd((char*)"   16BEC020   ") ;
  cmd(0xC0) ; 
  lcd((char*)"   16BEC021   ") ;	
	}
	}
