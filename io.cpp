
//Functions:

void pinMode(uint8_t pInno,uint8_t mOde)
{
  	if(mOde==0)
    {
    	switch(rEgister[pInno]){
            case'a':
			          DDRA&=~(1<<bIt[pInno]);
					  break;
          	case'b':
                  DDRB&=~(1<<bIt[pInno]);
		           break;
          	case'c':
                 DDRC&=~(1<<bIt[pInno]);
		          break;
          	case'd':
                 DDRD&=~(1<<bIt[pInno]);
		          break;
	      	case'e':
                  DDRE&=~(1<<bIt[pInno]);
		           break;
		    case'g':
                  DDRG&=~(1<<bIt[pInno]);
		           break;
			case'h':
                  DDRH&=~(1<<bIt[pInno]);
				  break;
		    case'j':
                  DDRJ&=~(1<<bIt[pInno]);
		          break;
			case'l':
                  DDRL&=~(1<<bIt[pInno]);
		          break;
     	}
	}
	else{
			switch(rEgister[pInno])
         	{   case'a':
			          DDRA|=(1<<bIt[pInno]);
					  break;

	        	case'b':
	            	DDRB|=(1<<bIt[pInno]);
			    	break;
	          	case'c':
	                DDRC|=(1<<bIt[pInno]);
			        break;
	          	case'd':
	                DDRD|=(1<<bIt[pInno]);
			        break;
		      	case'e':
	                DDRE|=(1<<bIt[pInno]);
			        break;
			    case'g':
	                DDRG|=(1<<bIt[pInno]);
			        break;
			 	case'h':
	                DDRH|=(1<<bIt[pInno]);
			        break;
			    case'j':
	                DDRJ|=(1<<bIt[pInno]);
			        break;
				case'l':
	                DDRL|=(1<<bIt[pInno]);
			        break;
	     }
	}
}

void digitalWrite (uint8_t pInno ,uint8_t mOde)
{
   if(mOde==0){
    	switch(rEgister[pInno])
     	{    case'a':
			          PORTA&=~(1<<bIt[pInno]);
					  break;

	        case'b':
	            PORTB&=~(1<<bIt[pInno]);
			    break;

	        case'c':
	            PORTC&=~(1<<bIt[pInno]);
			    break;

	        case'd':
	            PORTD&=~(1<<bIt[pInno]);
			    break;

		    case'e':
	        	PORTE&=~(1<<bIt[pInno]);
			    break;

			case'g':
	        	PORTG&=~(1<<bIt[pInno]);
			    break;

			case'h':
	            PORTH&=~(1<<bIt[pInno]);
			    break;

			case'j':
	            PORTJ&=~(1<<bIt[pInno]);
			    break;

			case'l':
	            PORTL&=~(1<<bIt[pInno]);
			    break;
	    }
	}
	else{
		switch(rEgister[pInno])
		{   case'a':
			          PORTA|=(1<<bIt[pInno]);
					  break;

	        case'b':
	        	PORTB|=(1<<bIt[pInno]);
			    break;

	        case'c':
	        	PORTC|=(1<<bIt[pInno]);
			    break;

	        case'd':
	            PORTD|=(1<<bIt[pInno]);
			    break;

		    case'e':
	            PORTE|=(1<<bIt[pInno]);
			    break;

			case'g':
	            PORTG|=(1<<bIt[pInno]);
			    break;

			case'h':
	            PORTH|=(1<<bIt[pInno]);
			    break;

			case'j':
	        	PORTJ|=(1<<bIt[pInno]);
			    break;

			case'l':
	            PORTL|=(1<<bIt[pInno]);
			    break;
	    }
	}
}

uint8_t digitalRead(uint8_t pInno)
{
	uint8_t digitalstatus;
	uint8_t reference=0;				//not a good practice
   switch(rEgister[pInno])
      {   case'a':      reference=(1<<bIt[pInno]);
				        digitalstatus=!(!(PINA&reference));
						break;
	        case'b':    reference=(1<<bIt[pInno]);
				    	digitalstatus=!(!(PINB&reference));
			            break;
	        case'c':    reference=(1<<bIt[pInno]);
					    digitalstatus=!(!(PINC&reference));
			            break;
	        case'd':    reference=(1<<bIt[pInno]);
					    digitalstatus=!(!(PIND&reference));
			            break;
		      case'e':  reference=(1<<bIt[pInno]);
			            digitalstatus=!(!(PINE&reference));
			            break;
		    	case'g':reference=(1<<bIt[pInno]);
			            digitalstatus=!(!(PING&reference));
			            break;
			    case'h':reference=(1<<bIt[pInno]);
		              digitalstatus=!(!(PINH&reference));
		              break;
			    case'j':reference=(1<<bIt[pInno]);
		              digitalstatus=!(!(PINJ&reference));
		              break;
			    case'l':reference=(1<<bIt[pInno]);
			            digitalstatus=!(!(PINL&reference));
			            break;
	     }
return digitalstatus;
}
//FIXME
/*static void turnOffPWM(uint8_t tImer)
{
	switch (tImer)
	{
		#if defined(TCCR1A) && defined(COM1A1)
		case TIMER1A:   cbi(TCCR1A, COM1A1);    break;
		#endif
		#if defined(TCCR1A) && defined(COM1B1)
		case TIMER1B:   cbi(TCCR1A, COM1B1);    break;
		#endif
		#if defined(TCCR1A) && defined(COM1C1)
		case TIMER1C:   cbi(TCCR1A, COM1C1);    break;
		#endif

		#if defined(TCCR2) && defined(COM21)
		case  TIMER2:   cbi(TCCR2, COM21);      break;
		#endif

		#if defined(TCCR0A) && defined(COM0A1)
		case  TIMER0A:  cbi(TCCR0A, COM0A1);    break;
		#endif

		#if defined(TCCR0A) && defined(COM0B1)
		case  TIMER0B:  cbi(TCCR0A, COM0B1);    break;
		#endif
		#if defined(TCCR2A) && defined(COM2A1)
		case  TIMER2A:  cbi(TCCR2A, COM2A1);    break;
		#endif
		#if defined(TCCR2A) && defined(COM2B1)
		case  TIMER2B:  cbi(TCCR2A, COM2B1);    break;
		#endif

		#if defined(TCCR3A) && defined(COM3A1)
		case  TIMER3A:  cbi(TCCR3A, COM3A1);    break;
		#endif
		#if defined(TCCR3A) && defined(COM3B1)
		case  TIMER3B:  cbi(TCCR3A, COM3B1);    break;
		#endif
		#if defined(TCCR3A) && defined(COM3C1)
		case  TIMER3C:  cbi(TCCR3A, COM3C1);    break;
		#endif

		#if defined(TCCR4A) && defined(COM4A1)
		case  TIMER4A:  cbi(TCCR4A, COM4A1);    break;
		#endif
		#if defined(TCCR4A) && defined(COM4B1)
		case  TIMER4B:  cbi(TCCR4A, COM4B1);    break;
		#endif
		#if defined(TCCR4A) && defined(COM4C1)
		case  TIMER4C:  cbi(TCCR4A, COM4C1);    break;
		#endif
		#if defined(TCCR4C) && defined(COM4D1)
		case TIMER4D:	cbi(TCCR4C, COM4D1);	break;
		#endif

		#if defined(TCCR5A)
		case  TIMER5A:  cbi(TCCR5A, COM5A1);    break;
		case  TIMER5B:  cbi(TCCR5A, COM5B1);    break;
		case  TIMER5C:  cbi(TCCR5A, COM5C1);    break;
		#endif
	}
}
*/

/*unsigned long pulseIn(volatile uint8_t pInno, uint8_t vAlue)
{
	char x;
  TCCR2A = (1 << WGM21) | (1 << COM2A1) | (1 << FOC2A) | (0 << COM2A0) | (0 << WGM20); //initializing in CTC mode
  TCCR2A = (1 << CS20);
  unsigned long mAxloops = 500000;
  unsigned long wIdth = 0;
  // wait for any previous pulse to end
  switch(rEgister[pInno]){
            case'b':
	               { while (((PINB) && ((bIt[pInno]))) == vAlue)
	              {
		          if (--mAxloops == 0)
		            return 0;
	                }
             // wait for the pulse to start
              while (((PINB) && (bIt[pInno])) != vAlue)
	              {
		     if (--mAxloops == 0)
		          return 0;
	           }
            // wait for the pulse to stop
             while (((PINB) && (bIt[pInno])) == vAlue)
	                   {
	               	if (++wIdth == mAxloops)
		          return 0;
	                      }
              return wIdth;
                    }  break;
 case'c':
	                 { while (((PINC) && (bIt[pInno])) == vAlue)
	                {
		              if (--mAxloops == 0)
		               return 0;
	                   }
  // wait for the pulse to start
                  while (((PINC) && (bIt[pInno])) != vAlue)
	                  {
		              if (--mAxloops == 0)
		                 return 0;
	                      }
  // wait for the pulse to stop
                while (((PINC) && (bIt[pInno])) == vAlue)
	                 {
                 		if (++wIdth == mAxloops)
                  		return 0;
                     	    }
                     return wIdth;
                         }break;

	 case'd':

	                 { while (((PIND) && (bIt[pInno])) == vAlue)
	                {
		              if (--mAxloops == 0)
		               return 0;
	                   }
  // wait for the pulse to start
                  while (((PIND) && (bIt[pInno])) != vAlue)
	                  {
		              if (--mAxloops == 0)
		                 return 0;
	                      }
  // wait for the pulse to stop
                while (((PIND) && (bIt[pInno])) == vAlue)
	                 {
                 		if (++wIdth == mAxloops)
                  		return 0;
                     	    }
                     return wIdth;
                         } break; 		//case'h':
				  //  DDRH|(0<<bIt[pInno]);
	case'e':

	                 { while (((PINE) && (bIt[pInno])) == vAlue)
	                {
		              if (--mAxloops == 0)
		               return 0;
	                   }
  // wait for the pulse to start
                  while (((PINE) && (bIt[pInno])) != vAlue)
	                  {
		              if (--mAxloops == 0)
		                 return 0;
	                      }
  // wait for the pulse to stop
                while (((PINE) && (bIt[pInno])) == vAlue)
	                 {
                 		if (++wIdth == mAxloops)
                  		return 0;
                     	    }
                     return wIdth;
                         } break;

case'h':

	                 { while (((PINH) &&(bIt[pInno])) == vAlue)
	                {
		              if (--mAxloops == 0)
		               return 0;
	                   }
  // wait for the pulse to start
                  while (((PINH) && (bIt[pInno])) != vAlue)
	                  {
		              if (--mAxloops == 0)
		                 return 0;
	                      }
  // wait for the pulse to stop
                while (((PINH) && ((bIt[pInno]))) == vAlue)
	                 {
                 		if (++wIdth == mAxloops)
                  		return 0;
                     	    }
                     return wIdth;
                         } break;
case'j':

	                 { while (((PINJ) && (bIt[pInno])) == vAlue)
	                {
		              if (--mAxloops == 0)
		               return 0;
	                   }
  // wait for the pulse to start
                  while (((PINJ) && (bIt[pInno])) != vAlue)
	                  {
		              if (--mAxloops == 0)
		                 return 0;
	                      }
  // wait for the pulse to stop
                while (((PINJ) && (bIt[pInno])) == vAlue)
	                 {
                 		if (++wIdth == mAxloops)
                  		return 0;
                     	    }
                     return wIdth;
                         }
			           break;
case 'l':

	                 { while (((PINL) && (bIt[pInno])) == vAlue)
	                {
		              if (--mAxloops == 0)
		               return 0;
	                   }
  // wait for the pulse to start
                  while (((PINL) && (bIt[pInno])) != vAlue)
	                  {
		              if (--mAxloops == 0)
		                 return 0;
	                      }
  // wait for the pulse to stop
                while (((PINL) && (bIt[pInno])) == vAlue)
	                 {
                 		if (++wIdth == mAxloops)
                  		return 0;
                     	    }
                     return wIdth;
                         }
			           break;
	     			}
	}

*/
class Serial
{
	public:
	void begin( unsigned int BAUD){
		/*Set baud rate */int uBrr;
		uBrr=(F_CPU/16UL/BAUD-1);
		UBRR0H = (unsigned char)(uBrr>>8);
		UBRR0L = (unsigned char)uBrr;
		/* Enable receiver and transmitter */
		UCSR0B = (1<<RXEN0)|(1<<TXEN0);
		/* Set frame format: 8data, 2stop bit */
		UCSR0C = (1<<USBS0)|(3<<UCSZ00);
	}
	/* Set frame format: 8data, 2stop bit */
	void write( unsigned char dAta ){
		/* Wait for empty transmit buffer */
		while ((UCSR0A & (1<<UDRE0))==0);
		/* Put data into buffer, sends the data */
		UDR0 = dAta;
		_delay_ms(100);
	}
	unsigned char read( void ){
		/* Wait for data to be received */
		while ( !(UCSR0A & (1<<RXC0)) )
		;
		/* Get and return received data from buffer */
		return UDR0;
	}
	void flush(void){
		unsigned char dUmmy;
		while ( UCSR0A & (1<<RXC0) ) dUmmy = UDR0;
	}

	void end(void){
		flush();
		UCSR0B&=0xe7;	//disabling RXEN & TXEN
	}
	uint8_t available(void){	//working fine
		 if((UCSR0A & (1<<RXC0)))
			return 1;
 		else
			return 0;
	}
};


class Serial1
{
	public:
	void begin( unsigned int BAUD){
		int uBrr;		/*Set baud rate */
		uBrr=(F_CPU/16/BAUD-1);
		UBRR1H = (unsigned char)(uBrr>>8);
		UBRR1L = (unsigned char)uBrr;
		/*Enable receiver and transmitter */
		UCSR1B = (1<<RXEN1)|(1<<TXEN1);
	}
	/* Set frame format: 8data, 2stop bit */
	void write( unsigned char data ){
		/* Wait for empty transmit buffer */
		while ( !( UCSR1A & (1<<UDRE1)) )
		;
		/* Put data into buffer, sends the data */
		UDR1= data;
		_delay_ms(100);
	}
	unsigned char read( void ){
		/* Wait for data to be received */
		while ( !(UCSR1A & (1<<RXC1)) )
		;
		/* Get and return received data from buffer */
		return UDR1;
	}
	void flush(void){
		unsigned char dUmmy;
		while ( UCSR1A & (1<<RXC1) ) dUmmy = UDR1
		;
	}

	void end(void){
		flush();
		UCSR1B&=0xe7;	//disabling RXEN & TXEN
	}
	uint8_t available(void){	//working fine
	if((UCSR1A & (1<<RXC1)))
		return 1;
 	else
		return 0;
	}
};
class Serial2
{
	public:
	void begin( unsigned int BAUD){
		/*Set baud rate */
		int uBrr;
		uBrr=(F_CPU/16/BAUD-1);
		UBRR2H = (unsigned char)(uBrr>>8);
		UBRR2L = (unsigned char)uBrr;
		/*Enable receiver and transmitter */
		UCSR2B = (1<<RXEN2)|(1<<TXEN2);
	}
	/* Set frame format: 8data, 2stop bit */
	void write( unsigned char dAta ){
		/* Wait for empty transmit buffer */
		while ( !( UCSR2A & (1<<UDRE2)) )
		;
		/* Put data into buffer, sends the data */
		UDR2= dAta;
		_delay_ms(100);
	}
	unsigned char read(){
		/* Wait for data to be received */
		while ( !(UCSR2A & (1<<RXC2)) )
		;
		/* Get and return received data from buffer */
		return UDR2;
	}
	void flush(void){
		unsigned char dUmmy;
		while ( UCSR2A & (1<<RXC2) ) dUmmy = UDR1
		;
	}

	void end(void){
		flush();
		UCSR2B&=0xe7;	//disabling RXEN & TXEN
	}
	uint8_t available(void){	//working fine
		if((UCSR2A & (1<<RXC2)))
			return 1;
 		else
			return 0;
	}
};

class Serial3
{
	public:
	void begin( unsigned int BAUD){
		int uBrr;/*Set baud rate */
		  uBrr=(F_CPU/16/BAUD-1);
		UBRR3H = (unsigned char)(uBrr>>8);
		UBRR3L = (unsigned char)uBrr;
		/*Enable receiver and transmitter */
		UCSR3B = (1<<RXEN3)|(1<<TXEN3);
	}
	/* Set frame format: 8data, 2stop bit */
	void write( unsigned char data ){
		/* Wait for empty transmit buffer */
		while ( !( UCSR3A & (1<<UDRE3)) )
		;
		/* Put data into buffer, sends the data */
		UDR3= data;
		_delay_ms(100);
	}
	unsigned char read( void ){
		/* Wait for data to be received */
		while ( !(UCSR3A & (1<<RXC3)) )
		;
		/* Get and return received data from buffer */
		return UDR3;
	}
	void flush(void){
		unsigned char dUmmy;
		while ( UCSR3A & (1<<RXC3) ) dUmmy = UDR1
		;
	}

	void end(void){
		flush();
		UCSR3B&=0xe7;	//disabling RXEN & TXEN
	}
		uint8_t available(void){	//working fine
		 if((UCSR3A & (1<<RXC3)))
			return 1;
 		else
			return 0;
	}
};
Serial Serial;
Serial1 Serial1;
Serial2 Serial2;
Serial3 Serial3;
void initADC()
{
	ADMUX=(1<<REFS0);				//Aref=AVcc
	ADCSRA=(1<<ADEN)|(1<<ADPS2)|(1<<ADPS1);		//ADC enabled, Prescaler 64
}

int analogRead(int (pInno))
{
        //prescalar set to default
  	initADC();
  	ADMUX=(1<<REFS0)|(0<<REFS1);
  	ADCSRA|=(1<<ADEN);
    ADMUX|=(pInno%8);//chose value from 0 to 7 to chose adc pin accordingly
    ADCSRA|=(1<<ADEN);
    ADCSRA|=(1<<ADSC);
	while(ADCSRA&(1<<ADSC));
	return (ADC);
}

void analogWrite(uint8_t pInno,uint8_t dUtycY)
{
  switch(pInno)
  {
	  case 11:
		   DDRB|=(1<<PB5);
		   TCCR1A|=(1<<WGM10)|(1<<WGM12)|(1<<COM1A1);
		   TCCR1B|=(1<<CS11)|(1<<CS10);
		   OCR1A=dUtycY;
		   break;
	  case 12:
		  DDRB|=(1<<PB6);
		  TCCR1A|=(1<<WGM10)|(1<<WGM12)|(1<<COM1B1);
		  TCCR1B|=(1<<CS11)|(1<<CS10);
		  OCR1B=dUtycY;
		  break;
	  case 10:
		  DDRB|=(1<<PB4);
		  TCCR2A|=(1<<COM2A1)|(1<<WGM21)|(1<<WGM20);
		  TCCR2B|=(1<<CS20);
		  OCR2A=dUtycY;
		  break;
	  case 9:
		   DDRH|=(1<<PH6);
		   TCCR2A|=(1<<WGM21)|(1<<WGM20)|(1<<COM2B1);
		   TCCR2B|=(1<<CS20);
		   OCR2B=dUtycY;
		   break;
	  case 5:
		  DDRE|=(1<<PE3);
		  TCCR3A|=(1<<WGM32)|(1<<WGM30)|(1<<COM3A1);
		  TCCR3B|=(1<<CS30);
		  OCR3A=dUtycY;
		  break;
	  case 2:
	  	  DDRE|=(1<<PE4);
		  TCCR3A|=(1<<WGM32)|(1<<WGM30)|(1<<COM3B1);
		  TCCR3B|=(1<<CS30);
		  OCR3B=dUtycY;
		  break;
	  case 46:
		  DDRL|=(1<<PL3);
		  TCCR5A|=(1<<WGM52)|(1<<WGM50)|(1<<COM5A1);
		  TCCR5B|=(1<<CS50);
		  OCR5A=dUtycY;
		  break;
	  case 45:
		  DDRL|=(1<<PL4);
		  TCCR5A|=(1<<WGM52)|(1<<WGM50)|(1<<COM5B1);
		  TCCR5B|=(1<<CS50);
		  OCR5B=dUtycY;
		  break;
	  case 13:
		  DDRB|=(1<<PB7);
		  TCCR0A|=(1<<WGM10)|(1<<WGM00)|(1<<COM0A1);
		  TCCR0B|=(1<<CS00);
		  OCR0A=dUtycY;
		  break;
	  case 4:
	  	DDRG|=(1<<PG5);
		TCCR0A|=(1<<WGM10)|(1<<WGM00)|(1<<COM0B1);
		TCCR0B|=(1<<CS00);
		OCR0B=dUtycY;
		break;

	  case 6:
		  DDRH|=(1<<PH3);
		  TCCR4A|=(1<<WGM42)|(1<<WGM40)|(1<<COM4A1);
		  TCCR4B|=(1<<CS40);
		  OCR4A=dUtycY;
		  break;
	  case 7:

		  DDRH|=(1<<PH4);
		TCCR4A|=(1<<WGM42)|(1<<WGM40)|(1<<COM4B1);
		  TCCR4B|=(1<<CS40);
		  OCR4B=dUtycY;
		  break;


  }
}
unsigned long millis ()
{
    unsigned long millis_return;

    // Ensure this cannot be disrupted
    ATOMIC_BLOCK(ATOMIC_FORCEON) {
        millis_return = tImer0_millis;
    }

    return millis_return;
}

ISR (TIMER0_COMPA_vect)
{
    tImer0_millis++;
}

int mIcros()
{float l;
  l=(x*0.16+0.00000625*TCNT2)*(10^6);
return l;
}
ISR(TIMER2_OVF_vect)
{x++;  
}

void tinit()
{
	TCCR0A|=(1<<WGM10)|(1<<WGM12)|(1<<COM1A1);
    TCCR0B|=(1<<CS11)|(1<<CS10);
	// Load the high byte, then the low byte
	// into the output compare
     OCR0A = CTC_MATCH_OVERFLOW;
    // OCR0A = CTC_MATCH_OVERFLOW;
	// Enable the compare match interrupt
	TIMSK0 |= (1 << OCIE0A);

	// Now enable global interrupts
	sei();
}


void delay(unsigned long mIllisec)
{
	int i;
	for(i=0;i<mIllisec;i++)
	{
		_delay_ms(1);
	}
	return;
}

void delayMicroseconds(unsigned long mIcrosec)
{
	int i;
	for(i=0;i<mIcrosec;i++)
	{
		_delay_us(1);
	}
	return;
}

long map(long x, long in_min, long in_max, long out_min, long out_max)
{
  return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}

long constrain(long nUm, long lOwer, long uPper)
{
	if(nUm>uPper){
      return uPper;
  	}
    else if(nUm<lOwer){
      return lOwer;
  	}
    else
    return nUm;
}
void attachIntterupt(int pIn, void (*iSrfunc)(void), int cOmpare)		//cOmpare:LOW=0,HIGH1,RISING=2,FALLING=3
{
	sei();
	cAllisr=iSrfunc;
	switch(pIn)	  //enabling interrupt pin
	{
		case 0:
		EIMSK|=1<<INT0;
		switch(cOmpare){
			case 2:
			EICRA|=(1<<ISC00)|(1<<ISC01);
			break;
			case 3:
			EICRA|=(0<<ISC00)|(1<<ISC01);
			break;
			case 4:
			EICRA|=(1<<ISC00)|(0<<ISC01);
			break;
			default:
			EICRA|=(0<<ISC00)|(0<<ISC01);
		}
		break;

		case 1:
		EIMSK|=1<<INT1;
                switch(cOmpare)
		{
			case 2:
			EICRA|=(1<<ISC10)|(1<<ISC11);
			break;
			case 3:
			EICRA=(0<<ISC10)|(1<<ISC11);
			break;
			case 4:
			EICRA|=(1<<ISC10)|(0<<ISC11);
			break;
			default:
			EICRA|=(0<<ISC10)|(0<<ISC11);
		}
		break;

		case 2:
		EIMSK|=1<<INT2;
		switch(cOmpare)
		{
			case 2:
			EICRA|=(1<<ISC20)|(1<<ISC21);
			break;
			case 3:
			EICRA=(0<<ISC20)|(1<<ISC21);
			break;
			case 4:
			EICRA|=(1<<ISC20)|(0<<ISC21);
			break;
			default:
			EICRA|=(0<<ISC20)|(0<<ISC21);
		}
		break;

		case 3:
		EIMSK|=1<<INT3;
		switch(cOmpare)
		{
			case 2:
			EICRA|=(1<<ISC30)|(1<<ISC31);
			break;
			case 3:
			EICRA=(0<<ISC30)|(1<<ISC31);
			break;
			case 4:
			EICRA|=(1<<ISC30)|(0<<ISC31);
			break;
			default:
			EICRA|=(0<<ISC30)|(0<<ISC31);
		}
		break;

		case 4:
		EIMSK|=1<<INT4;
                switch(cOmpare)
		{
			case 2:
			EICRB|=(1<<ISC40)|(1<<ISC41);
			break;
			case 3:
			EICRB=(0<<ISC40)|(1<<ISC41);
			break;
			case 4:
			EICRB|=(1<<ISC40)|(0<<ISC41);
			break;
			default:
			EICRB|=(0<<ISC40)|(0<<ISC41);
		}
		break;

		case 5:
		EIMSK|=1<<INT5;
		switch(cOmpare)
		{
			case 2:
			EICRB|=(1<<ISC50)|(1<<ISC51);
			break;
			case 3:
			EICRB=(0<<ISC50)|(1<<ISC51);
			break;
			case 4:
			EICRB|=(1<<ISC50)|(0<<ISC51);
			break;
			default:
                 	EICRB|=(0<<ISC40)|(0<<ISC41);

		}
		break;

		case 6:
		EIMSK|=1<<INT6;
	        switch(cOmpare)
		{
			case 2:
			EICRB|=(1<<ISC60)|(1<<ISC61);
			break;
			case 3:
			EICRB=(0<<ISC60)|(1<<ISC61);
			break;
			case 4:
			EICRB|=(1<<ISC60)|(0<<ISC61);
			break;
			default:
			EICRB|=(0<<ISC60)|(0<<ISC61);

		}
		break;

		case 7:
		EIMSK|=1<<INT7;
		switch(cOmpare)
		{
			case 2:
			EICRB|=(1<<ISC70)|(1<<ISC71);
			break;
			case 3:
			EICRB=(0<<ISC70)|(1<<ISC71);
			break;
			case 4:
			EICRB|=(1<<ISC70)|(0<<ISC71);
			break;
			default:
			EICRB|=(0<<ISC70)|(0<<ISC71);
		}
		break;

	        default:EICRA|=(0<<ISC01)|(0<<ISC00);
	}
}
ISR(INT0_vect)
{
   cAllisr();
}
ISR(INT1_vect)
{
   cAllisr();
}
ISR(INT2_vect)
{
   cAllisr();
}
ISR(INT3_vect)
{
   cAllisr();
}
ISR(INT4_vect)
{
    cAllisr();
}
ISR(INT5_vect)
{
    cAllisr();
}
ISR(INT6_vect)
{
    cAllisr();
}
ISR(INT7_vect)
{
    cAllisr();
}

/*void softwareInterrupt(void (*iSrfun(void)))
{
	uSerfun=iSrfun;
        TCCR1A|=(1<<WGM11);
	TCCR1B|=(1<<WGM12)|(1<<WGM13)|(1<<CS10); // fast pwm mode and prescalar is set as 1
	TIMSK1|=(1<<TOIE1); // overflow interrupt flag is set
}

ISR(TIMER1_OVF_vect)
{
	uSerfun();
}*/
int main(){
	//tinit();
	setup();
	while(1){
		loop();
	}
}
