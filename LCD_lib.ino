
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
PORTB |= (1<<LCD_RS); //RS 1 for data
PORTB &=~(1<<LCD_RW); //RW 0 for write
PORTB |= (1<<LCD_EN); //EN 1 for H-to-L
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
lCdCommand(0x33);
lCdCommand(0x32);
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

void lCdserial(uint32_t ser)
{
  /*uint8_t Ser=ser; 
  int i=0;
  uint8_t ser1[3]={0,0,0};
 while(ser!=0)
 {
   //uint8_t i=2;
  // uint8_t ser1[3];
   ser1[i]=ser%10;
  // Serial.println(m);
   ser1[i]=ser1[i]+48;
   ser=ser/10;
   i++;
 }
 i=2;
 while(i>=0)
  {
   //ser1[i]=ser1[i]+48;
   lCdData(ser1[i]);
   i--;
  }
 */
 uint8_t u=0;
 uint32_t Ser=ser;
 uint8_t t=0;
while(ser!=0)
{
    u++;
    ser=ser/10;
}

uint8_t ser1[u];
 while(t<u)
 {
   //uint8_t i=2;
  // uint8_t ser1[3];
   ser1[t]=Ser%10;
  // Serial.println(m);
   ser1[t]=ser1[t]+48;
   Ser=Ser/10;
   
  // lCdData(ser1[t]);
   t++;
 }
 
 while(u>0)
 {
  lCdData(ser1[u-1]);
  u--;
 }
  
//lCdData(ser1[1]);
}

int main(void)
{
Serial.begin(9600);
DDRB=0xFF;
DDRD=0xFF;
//PORTD&=~(1<<LCD_EN);
//_delay_ms(4500);
lCd_init();
/*DDRB=0xFF;
DDRD=0xFF;
PORTD&=~(1<<LCD_EN);
_delay_ms(4500);
//lCd_print ("The world is but");
PORTD = 0b00100000;//only first 4MSB bits of cmnd are stored in PORTD without changing the last 4LSB bits of PORTD
PORTB &=~(1<<LCD_RS); //RS 0 for command
PORTB &=~(1<<LCD_RW); //RW 0 for write
PORTB |= (1<<LCD_EN); //EN 1 for H-to-L
_delay_us(1);
PORTB &=~(1<<LCD_EN);
_delay_us(40);
PORTD = 0b01000000;
PORTB|= (1<<LCD_EN);
_delay_us(1);
PORTB &=~(1<<LCD_EN);
_delay_ms(2);*/

lCdClear();
//lCdprint("1");
//lCdLeftToRight();
//lCdNocursor();

uint8_t k=0;

//Serial.print(k);
//lCdData(i);
/*for(k;k<255;k++)
{
  lCdserial(k);
  lCdHome(); 
  _delay_ms(100);
  //lCdLeftToRight(); 
}*/
uint32_t q=65540;
  lCdserial(q);
  lCdClear();
 lCdserial(30);
while(1);
}
