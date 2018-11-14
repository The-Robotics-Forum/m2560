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
#include<io.cpp>
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

/
