/*
 * pIn_change_interrupt
 *
 * Created: 04-02-2019 14:36:34
 *  Author: yash
 */ 
//PCINT pins on various ports
/*	pins			 PCINT no.	 		digital_pins
	
	PB0 to PB7:		 0 to 7				  	
	PE0       :		   8					  0
	PJ0 to PJ6:		 9 to 15				
	PK0 to PK7:		16 to 23				
*/
#include <avr/io.h>
#include <avr/interrupt.h>

//pinMapping
uint8_t bIt[]={
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

char rEgister[54]={'e','e','e','e','g','e','h','h','h','h','b','b','b','b','j','j','h','h','d','d','d','d','a','a','a','a','a','a','a','a','c','c','c','c','c','c','c','c','d','g','g','g','l','l','l','l','l','l','l','l','b','b','b','b'};


uint8_t static volatile lAst_sTate_0=0; //_0 for PCIE0
uint8_t volatile cHanged_0;			
uint8_t rising_pins_0=0;
uint8_t falling_pins_0=0;

uint8_t static volatile lAst_sTate_1=0; //_1 for PCIE1
uint8_t volatile cHanged_1;			
uint8_t rising_pins_1=0;
uint8_t falling_pins_1=0;

uint8_t static volatile lAst_sTate_2=0; //_2 for PCIE2
uint8_t volatile cHanged_2;			
uint8_t rising_pins_2=0;
uint8_t falling_pins_2=0;

typedef void(*fUnc_pOinter)();	

//adress stored according to PCINT pins
fUnc_pOinter fUnc_aRray[24];

DPTI(uint8_t Pin_no,uint8_t mode,fUnc_pOinter func)
{
	//mode_all|=(mode<<Pin_no);
	
	switch(rEgister[Pin_no])
	{
		case 'b':
		 switch(bIt[Pin_no])
		 {
			 case 0:
			 PCICR|=1<<PCIE0;
			 PCMSK0|=(1<<PCINT0);
		//	 mode_all_b|=(~mode<<0);
		//	 interrupt_0=1;
			 fUnc_aRray[0]=func;
			 if(mode==1)
			{
			 rising_pins_0|=(1<<0);
			 falling_pins_0|=(0<<0);
			}
			else
			{
			 rising_pins_0|=(0<<0);
			 falling_pins_0|=(1<<0);
			}			 
			 break;
			 
			 case 1:
			 PCICR|=1<<PCIE0;
			 PCMSK0|=(1<<PCINT1);
			 fUnc_aRray[1]=func;
			 if(mode==1)
			{
			 rising_pins_0|=(1<<1);
			 falling_pins_0|=(0<<1);
			}
			else
			{
			 rising_pins_0|=(0<<1);
			 falling_pins_0|=(1<<1);
			}			 
		     break;
			 
			 case 2:
			 PCICR|=1<<PCIE0;
			 PCMSK0|=(1<<PCINT2);
			 fUnc_aRray[2]=func;
				  if(mode==1)
				{
				 rising_pins_0|=(1<<2);
				 falling_pins_0|=(0<<2);
				}
				else
				{
				 rising_pins_0|=(0<<2);
				 falling_pins_0|=(1<<2);
				}			 
			 break;
				 
			 case 3:
			 PCICR|=1<<PCIE0;
			 PCMSK0|=(1<<PCINT3);
			 fUnc_aRray[3]=func;
				 if(mode==1)
				{
				 rising_pins_0|=(1<<3);
				 falling_pins_0|=(0<<3);
				}
				else
				{
				 rising_pins_0|=(0<<3);
				 falling_pins_0|=(1<<3);
				}			 
		    break;
				 
			 case 4:
			 PCICR|=1<<PCIE0;
			 PCMSK0|=(1<<PCINT4);
			 fUnc_aRray[4]=func;
				 if(mode==1)
				{
				 rising_pins_0|=(1<<4);
				 falling_pins_0|=(0<<4);
				}
				else
				{
				 rising_pins_0|=(0<<4);
				 falling_pins_0|=(1<<4);
				}			 
			 break;
				 
			 case 5:
			 PCICR|=1<<PCIE0;
			 PCMSK0|=(1<<PCINT5);
			 fUnc_aRray[5]=func; 
				 if(mode==1)
				{
				 rising_pins_0|=(1<<5);
				 falling_pins_0|=(0<<5);
				}
				else
				{
				 rising_pins_0|=(0<<5);
				 falling_pins_0|=(1<<5);
				}			 
			break;
				 
			 case 6:
			 PCICR|=1<<PCIE0;
			 PCMSK0|=(1<<PCINT6);
			 fUnc_aRray[6]=func;
				 if(mode==1)
				{
				 rising_pins_0|=(1<<6);
				 falling_pins_0|=(0<<6);
				}
				else
				{
				 rising_pins_0|=(0<<6);
				 falling_pins_0|=(1<<6);
				}			 
			 break;
			 
			 case 7:
			 PCICR|=1<<PCIE0;
			 PCMSK0|=(1<<PCINT7);
			 fUnc_aRray[7]=func;
				if(mode==1)
				{
				 rising_pins_0|=(1<<7);
				 falling_pins_0|=(0<<7);
				}
				else
				{
				 rising_pins_0|=(0<<7);
				 falling_pins_0|=(1<<7);
				}			 
		   	break;
		}
		break;
		
		case 'e':
			switch(bIt[Pin_no])
			{
			case 0:
			PCICR|=1<<PCIE1;
			PCMSK1|=(1<<PCINT8);
			fUnc_aRray[8]=func;
				if(mode==1)
				{
					rising_pins_1|=(1<<0);
					falling_pins_1|=(0<<0);
				}
				else
				{
					rising_pins_1|=(0<<0);
					falling_pins_1|=(1<<0);
				}
			break;
			}		
		break;
			
		case 'j':
			switch(bIt[Pin_no])
			{
				case 0:
				PCICR|=1<<PCIE1;
				PCMSK1|=(1<<PCINT9);
				fUnc_aRray[9]=func;
				if(mode==1)
				{
					rising_pins_1|=(1<<1);
					falling_pins_1|=(0<<1);
				}
				else
				{
					rising_pins_1|=(0<<1);
					falling_pins_1|=(1<<1);
				}
				break;
				
				case 1:
				PCICR|=1<<PCIE1;
				PCMSK1|=(1<<PCINT10);
				fUnc_aRray[10]=func;
				if(mode==1)
				{
					rising_pins_1|=(1<<2);
					falling_pins_1|=(0<<2);
				}
				else
				{
					rising_pins_1|=(0<<2);
					falling_pins_1|=(1<<2)
				}
				break;
				
				case 2:
				PCICR|=1<<PCIE1;
				PCMSK1|=(1<<PCINT11);
				fUnc_aRray[11]=func;
				if(mode==1)
				{
					rising_pins_1|=(1<<3);
					falling_pins_1|=(0<<3);
				}
				else
				{
					rising_pins_1|=(0<<3);
					falling_pins_1|=(1<<3);
				}
				break;
				
				case 3:
				PCICR|=1<<PCIE1;
				PCMSK1|=(1<<PCINT12);
				fUnc_aRray[12]=func;
				if(mode==1)
				{
					rising_pins_1|=(1<<4);
					falling_pins_1|=(0<<4);
				}
				else
				{
					rising_pins_1|=(0<<4);
					falling_pins_1|=(1<<4);
				}
				break;
				
				case 4:
				PCICR|=1<<PCIE1;
				PCMSK1|=(1<<PCINT13);
				fUnc_aRray[13]=func;
				if(mode==1)
				{
					rising_pins_1|=(1<<5);
					falling_pins_1|=(0<<5);
				}
				else
				{
					rising_pins_1|=(0<<5);
					falling_pins_1|=(1<<5);
				}
				break;
				
				case 5:
				PCICR|=1<<PCIE1;
				PCMSK1|=(1<<PCINT14);
				fUnc_aRray[14]=func;
				if(mode==1)
				{
					rising_pins_1|=(1<<6);
					falling_pins_1|=(0<<6);
				}
				else
				{
					rising_pins_1|=(0<<6);
					falling_pins_1|=(1<<6);
				}
				break;
				
				case 6:
				PCICR|=1<<PCIE1;
				PCMSK1|=(1<<PCINT15);
				fUnc_aRray[15]=func;
				if(mode==1)
				{
					rising_pins_1|=(1<<7);
					falling_pins_1|=(0<<7);
				}
				else
				{
					rising_pins_1|=(0<<7);
					falling_pins_1|=(1<<7);
				}
				break;
			}	
		break;
		
	}
}

void call()
{
	PORTD=255;
	
}

void call1()
{
	PORTD=0;
}
 
ISR(PCINT0_vect)
{
	cHanged=((PINB^lAst_sTate_0) & ((rising_pins_0 & !lAst_sTate) | (falling_pins_0 & lAst_sTate)));		//only changed bits will be high in cHanged variable 	
	
	PCIFR|=(1<<PCIF0);						//clearing only that flags due to which interrupt occured,so if interrupt on that port occurs the flag should set
	
	if((PCMSK0 & 0b00000001) && (cHanged & 0b00000001)) //if pin declared as interrupt and pin has changed accordingly
	{
		(*fUnc_aRray[0])();		//PCINT0	
		//PORTD=255;
	}

	if((PCMSK0 & 0b00000010) && (cHanged & 0b00000010))
	{
		(*fUnc_aRray[1])();		//PCINT1
		//PORTD=0;
	}
	
	if((PCMSK0 & 0b00000100) && (cHanged & 0b00000100))
	{
		(*fUnc_aRray[2])();						//PCINT2
	//	PORTD=64;
	}
	if((PCMSK0 & 0b00001000) && (cHanged & 0b00001000))
	{
	    (*fUnc_aRray[3])();					//PCINT3
		//PORTD=128;
	}
	if((PCMSK0 & 0b00010000) && (cHanged & 0b00010000))
	{
	    (*fUnc_aRray[4])();					//PCINT4
		//PORTD=128;
	}
	if((PCMSK0 & 0b00100000) && (cHanged & 0b00100000))
	{
	    (*fUnc_aRray[5])();					//PCINT5
		//PORTD=128;
	}
	if((PCMSK0 & 0b01000000) && (cHanged & 0b01000000))
	{
	    (*fUnc_aRray[6])();					//PCINT6
		//PORTD=128;
	}
	if((PCMSK0 & 0b10001000) && (cHanged & 0b10000000))
	{
	    (*fUnc_aRray[7])();					//PCINT7
		//PORTD=128;
	}
	
	lAst_sTate_0=PINB;	
	//lAst_sTate=PINB;
}

int main(void)
{	
		sei();
		DDRD=0b11111111;
		DDRB=0b00000000;		
		//PORTB=0;
		//EICRA=0b00000011;
		//EIMSK=(1<<INT0);
		//
		//PCICR|=1<<PCIE0;
		//PCMSK0|=(1<<PCINT0)|(1<<PCINT2);
	//	lAst_sTate=PINB;
		DPTI(53,1,call);
		DPTI(52,0,call1);
		//PORTB=0b11110000;
    while(1)
    {
       // PORTB=0b00000000;
		//TODO:: Please write your application code 
		//PORTD=0b11110000;
	//	DDRB=0;
		
	}
}

