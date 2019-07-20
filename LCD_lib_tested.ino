/*
 * Avr_practice.c
 *
 * Created: 01-07-2019 14:33:28
 *  Author: yash
 */ 

#define F_CPU 16000000UL
#include<avr/io.h>
#include<util/delay.h>
//#define PORTD PORTD
//#define DDRD DDRD
//#define LCD_PIN PINA
#define LCD_RS 0
#define LCD_RW 1
#define LCD_EN 2

void lCdData(unsigned char data)
{
PORTD = (PORTD & 0x0F)|(data & 0xF0);
PORTB |= (1<<LCD_RS); //RS 1 for data               //if we want write any data then RS pin of Lcd should be made 1 so that Lcd understands that data is being printed and therefore encoding is done accordingly.
PORTB &=~(1<<LCD_RW); //RW 0 for write
PORTB |= (1<<LCD_EN); //EN 1 for H-to-L             //when we write new data to Lcd,EN pin should be made high for 1 microsec.Then Lcd reads this pins and encodes it accordingly.
_delay_us(1);
PORTB &=~(1<<LCD_EN);
PORTD = (PORTD & 0x0F)|(data<<4);
PORTB|= (1<<LCD_EN);
_delay_us(1);
PORTB &=~(1<<LCD_EN);
_delay_ms(2);
}

void lCdCommand(unsigned char cmnd)
{
PORTD = (PORTD & 0b00001111)|(cmnd & 0b11110000);//only first 4MSB bits of cmnd are stored in PORTD without changing the last 4LSB bits of PORTD
PORTB &=~(1<<LCD_RS); //RS 0 for command
PORTB &=~(1<<LCD_RW); //RW 0 for write
PORTB |= (1<<LCD_EN); //EN 1 for H-to-L
_delay_us(1);
PORTB &=~(1<<LCD_EN);
_delay_us (200);
PORTD = (PORTD & 0x0F)|(cmnd<<4);
PORTB|= (1<<LCD_EN);
_delay_us(1);
PORTB &=~(1<<LCD_EN);
_delay_ms(2);
}

void lCdprint(char str[])
{
  unsigned char i = 0;
  while (str[i]!='\0')
  {
   lCdData(str[i]);
   i++;
  }
}

void lCdSetCursor(unsigned char x_c, unsigned char y_c)
{
  unsigned char lIne[]={0x80,0xC0,0x94,0xD4};
  lCdCommand (lIne[y_c-1] + x_c - 1);
  _delay_us(100);
}

void lCdClear()
{
  lCdCommand(0x01);   /* Clear display */
  _delay_ms(5);
  lCdCommand(0x80);   /* Cursor at home position */
}

void lCdLeftToRight()
{
  lCdCommand(0x06);  
}

void lCdRightToLeft()
{
  lCdCommand(0x04);  
}

void lCdHome()
{
  lCdCommand(0x02);  
}

void lCdNocursor()
{
  lCdCommand(0x0C);  
}

void lCd_init()
{
DDRD = 0xFF;
_delay_ms(20);
lCdCommand(0x33);        //to set the 4 bit mode
lCdCommand(0x32);       //to set the 4 bit mode
lCdCommand(0x28);
lCdCommand(0x0F);
lCdCommand(0x06);
lCdCommand(0x01);
}

void lCdblink()
{
  lCdCommand(0x0F);  
}

void lCdnoblink()
{
  lCdCommand(0x0E);  
}

void lCdserial(int32_t ser)
{
 uint8_t u=0;
 int32_t Ser=abs(ser);
 uint8_t t=0,sIgn_fLag=0;
 
 //if()
 if(ser>=0)
  sIgn_fLag=1; 
 else
  sIgn_fLag=0;
  
ser=abs(ser);
  while(ser!=0)                // calculating no. of digits in given number stored in the variable.  
  {
    u++;
    ser=ser/10; 
  }

int8_t ser1[u];
   while(t<u)                 // storing the digits of given variable in array(from unit to higher place) 
  {
    ser1[t]=Ser%10;
    ser1[t]=ser1[t]+48;
    Ser=Ser/10;
    t++;
   }
 
  if(sIgn_fLag==0)
    lCdData('-');
    
   while(u>0)                 //printing the data stored in array on Lcd.
  {
    lCdData(ser1[u-1]);
    u--;
  }
  //lCdData(ser1[1]);
}

int main(void)
{
DDRB=0xFF;
DDRD=0xFF;
lCd_init();
lCdClear();
//lCdData('a');
//lCdprint("welcome to devel");
//lCdLeftToRight();
//lCdNocursor();
lCdserial(4300);

//lCdSetCursor(1,2);
//lCdprint("opment board..");
while(1);


}
