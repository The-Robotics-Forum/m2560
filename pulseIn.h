/*
This code includes the pulsein library to calculate HIGH pulsewidth for atmega2560.
returns time in MIcro seconds.
ICP pins of 2560 are used 
wherein only 48=ICP5 and 49=ICP4 pins on mega can be used.
Since ICP1 and ICP3 are for CLK we cannot use them here  
*/

//PL0=49(ICP4)
//PL1=48(ICP5)
uint32_t tIme=0;
volatile uint8_t tImeroVerfLow; //declaring as volatile since it has to be changed in ISR 

int pulsein(uint8_t eCho)
{	tImeroVerfLow=0;			//resetting timeroverflow
	switch(eCho)
	{
		case 48:
			 DDRL&=~(1<<PL1);
			 sei();                 // Enable global interrupt 
  			 TIMSK5= (1 << TOIE5);  // Enable Timer5 overflow interrupts 
  			 TCCR5B|=(1<<ICES5)|(1<<CS51)|(1<<CS50);   //Capture on rising edge, 64 prescaler
    		 TIFR5|=1<<ICF5;                           // Clear ICP flag (Input Capture flag) 
    		 TIFR5|=1<<TOV5;                           // Clear Timer Overflow flag */
   			 while ((TIFR5 & (1 << ICF5)) == 0);       //Wait for rising edge 
		     TCNT5 = 0;                                // Clear Timer counter 
		     TCCR5B&=~(1<<ICES1);                      //Capture on falling edge, 64prescaler 
		     TIFR5|=1<<ICF5;                           //Clear ICP flag (Input Capture flag) 
		     TIFR5|=1<<TOV5;                           // Clear Timer Overflow flag 
		     tImerOverflow=0;                          // Clear Timer overflow count 
		     while ((TIFR5&(1<<ICF5))==0)              //Wait for falling edge 
		     {
		     	if(tImeroVerfLow>=8)					//if pulse width is greater than 2.097s
		     	   break;
		     }
		     tIme=ICR5*4+(65535*4*TimerOverflow);     //value of timer when ICF flag is set is stored in ICR 
			 if(tImeroVerfLow>=8)
			    tIme=0;
			 break;			   

		case 49:
			  DDRL&=~(1<<PL0);
			  sei();                 // Enable global interrupt 
  			  TIMSK4= (1 << TOIE4);  // Enable Timer4 overflow interrupts 
  			  TCCR4B|=(1<<ICES4)|(1<<CS41)|(1<<CS40);   //Capture on rising edge, 64 prescaler
    		  TIFR4|=1<<ICF4;                           // Clear ICP flag (Input Capture flag) 
    		  TIFR4|=1<<TOV4;                           // Clear Timer Overflow flag */
   			  while ((TIFR4 & (1 << ICF4)) == 0);       //Wait for rising edge 
		   	  TCNT4 = 0;                                // Clear Timer counter 
		      TCCR4B&=~(1<<ICES4);                      //Capture on falling edge, 1024 prescaler 
		   	  TIFR4|=1<<ICF4;                           //Clear ICP flag (Input Capture flag) 
		   	  TIFR4|=1<<TOV4;                           // Clear Timer Overflow flag 
		   	  tImerOverflow=0;                          // Clear Timer overflow count 
			  while ((TIFR4&(1<<ICF4))==0);             //Wait for falling edge 
			  {
			  	  if(tImeroVerfLow>=8)
					break;			  	  	 
			  }		      
		      tIme=ICR4*4+(65535*4*tImerOverflow);    //value of timer when ICF flag is set is stored in ICR 
		      if(tImeroVerfLow>=8)
		      	tIme=0;
		      break;
	}
	return(tIme);
}

ISR(TIMER4_OVF_vect)
{
	tImeroVerfLow++; 
}

ISR(TIMER5_OVF_vect)
{
	tImeroVerfLow++; 
}
