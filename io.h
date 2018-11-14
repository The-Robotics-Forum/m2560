/***********************************************
 |		#########   #########	#########      |
 |		    #       #       #   #              |
 | 		    #       #       #   #              |
 |		    #       #########	######         |
 |		    #       #  #        #              |
 |		    #       #     #     #              |
 |		    #       #       #   #              |
 |               Varun Gujarathi               |
 |               Parth Basole                  |
 |               Chaitanya Ashtekar            |
 |               Sakshi Rathi                  |
 **********************************************/
/*************INDEX******************
*BUG – a known bug that should be corrected.
*FIXME – should be corrected.
*HACK – a workaround.
*TODO – something to be done.
*UNDONE – a reversal or "roll back" of previous code.
*XXX – warn other programmers of problematic or misguiding code
*/


/*
TODO: Add Toggle Mode in pinMode and digitalWrite function
TODO: Enable the millis() function
*/
#include <avr/io.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <math.h>
#include <avr/pgmspace.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/atomic.h>
#ifndef F_CPU
#define F_CPU 16000000UL   //SET CPU CLOCK
#endif
#include <util/delay.h>
#define CTC_MATCH_OVERFLOW ((F_CPU / 1000) / 8)
/**************************************************************************************************************************/
const uint8_t OUTPUT=1,INPUT=0;
const uint8_t HIGH=1,LOW=0;
const uint8_t RISING=2,FALLING=3,CHANGE=4;
volatile unsigned long tImer0_millis;
volatile int  x;
//pinMapping
int bIt[]={
	 0 	, // PE 0 ** 0 ** USART0_RX
	 1 	, // PE 1 ** 1 ** USART0_TX
	 4 	, // PE 4 ** 2 ** PWM2
	 5 	, // PE 5 ** 3 ** PWM3
	 5 	, // PG 5 ** 4 ** PWM4
	 3 	, // PE 3 ** 5 ** PWM5
	 3 	, // PH 3 ** 6 ** PWM6
	 4 	, // PH 4 ** 7 ** PWM7
	 5 	, // PH 5 ** 8 ** PWM8
	 6 	, // PH 6 ** 9 ** PWM9
	 4 	, // PB 4 ** 10 ** PWM10
	 5 	, // PB 5 ** 11 ** PWM11
	 6 	, // PB 6 ** 12 ** PWM12
	 7 	, // PB 7 ** 13 ** PWM13
	 1 	, // PJ 1 ** 14 ** USART3_TX
	 0 	, // PJ 0 ** 15 ** USART3_RX
	 1 	, // PH 1 ** 16 ** USART2_TX
	 0 	, // PH 0 ** 17 ** USART2_RX
	 3 	, // PD 3 ** 18 ** USART1_TX
	 2 	, // PD 2 ** 19 ** USART1_RX
	 1 	, // PD 1 ** 20 ** I2C_SDA
	 0 	, // PD 0 ** 21 ** I2C_SCL
	 0 	, // PA 0 ** 22 ** D22
	 1 	, // PA 1 ** 23 ** D23
	 2 	, // PA 2 ** 24 ** D24
	 3 	, // PA 3 ** 25 ** D25
	 4 	, // PA 4 ** 26 ** D26
	 5 	, // PA 5 ** 27 ** D27
	 6 	, // PA 6 ** 28 ** D28
	 7 	, // PA 7 ** 29 ** D29
	 7 	, // PC 7 ** 30 ** D30
	 6 	, // PC 6 ** 31 ** D31
	 5 	, // PC 5 ** 32 ** D32
	 4 	, // PC 4 ** 33 ** D33
	 3 	, // PC 3 ** 34 ** D34
	 2 	, // PC 2 ** 35 ** D35
	 1 	, // PC 1 ** 36 ** D36
	 0 	, // PC 0 ** 37 ** D37
	 7 	, // PD 7 ** 38 ** D38
	 2 	, // PG 2 ** 39 ** D39
	 1 	, // PG 1 ** 40 ** D40
	 0 	, // PG 0 ** 41 ** D41
	 7 	, // PL 7 ** 42 ** D42
	 6 	, // PL 6 ** 43 ** D43
	 5 	, // PL 5 ** 44 ** D44
	 4 	, // PL 4 ** 45 ** D45
	 3 	, // PL 3 ** 46 ** D46
	 2 	, // PL 2 ** 47 ** D47
	 1 	, // PL 1 ** 48 ** D48
	 0 	, // PL 0 ** 49 ** D49
	 3 	, // PB 3 ** 50 ** SPI_MISO
	 2 	, // PB 2 ** 51 ** SPI_MOSI
	 1 	, // PB 1 ** 52 ** SPI_SCK
	 0 	, // PB 0 ** 53 ** SPI_SS
	 0 	, // PF 0 ** 54 ** A0
	 1 	, // PF 1 ** 55 ** A1
	 2 	, // PF 2 ** 56 ** A2
	 3 	, // PF 3 ** 57 ** A3
	 4 	, // PF 4 ** 58 ** A4
	 5 	, // PF 5 ** 59 ** A5
	 6 	, // PF 6 ** 60 ** A6
	 7 	, // PF 7 ** 61 ** A7
	 0 	, // PK 0 ** 62 ** A8
	 1 	, // PK 1 ** 63 ** A9
	 2 	, // PK 2 ** 64 ** A10
	 3 	, // PK 3 ** 65 ** A11
	 4 	, // PK 4 ** 66 ** A12
	 5 	, // PK 5 ** 67 ** A13
	 6 	, // PK 6 ** 68 ** A14
	 7 	, // PK 7 ** 69 ** A15
};

char rEgister[60]={'e','e','e','e','g','e','h','h','h','h','b','b','b','b','j','j','h','h','d','d','a','a','a','a','a','a','a','a','c','c','c','c','c','c','c','c','d','g','g','g','l','l','l','l','l','l','l','l','b','b','b','b'};


/**************************************************************************************************************************/

//Function declaration
void analogWrite(uint8_t ,uint8_t);
int analogRead(uint8_t);
void delay(unsigned long);
void delayMicroseconds(long unsigned);
long map(long, long, long, long, long);
long constrain(long, long, long);
void attachIntterupt(int, void *,int);
unsigned long millis();
void (*cAllisr)(void); //function pointer used in ISR()
void softwareInterrupt(void *);
void (*uSerfun(void));
void pinMode(uint8_t , uint8_t );
static void turnOffPWM(uint8_t );
void digitalWrite(uint8_t , uint8_t );
uint8_t digitalRead(uint8_t );
void setup(void);
void loop(void);

/**************************************************************************************************************************/
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
