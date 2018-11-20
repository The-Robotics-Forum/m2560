

#include <avr/io.h>
#define  TWI_FREQ 100000L
#define F_CPU 1000000UL
class Wire
{
public:


void begin()
{DDRC|=0b00000011;
 TWBR=((F_CPU/TWI_FREQ)-16)/2;
 PORTC=(1<<0)|(1<<1);
 TWCR=(1<<TWSTA)|(1<<TWINT)|(1<<TWEN);
}
void begin(uint8_t sLave_address)
{TWAR=sLave_address;	
 TWBR=((F_CPU/TWI_FREQ)-16)/2;
  TWCR=(1<<TWEN)|(1<<TWEA)|(1<<TWINT);
}
uint8_t requestFrom(uint8_t sLave_address)
{uint8_t stat;
	DDRB=255;
	while(!(TWCR&(1<<TWINT)))
	{
		PORTB|=7;
	}
	stat=TWSR&0xF8;
	if (stat==0x08)
	{
		PORTB=1;
	}
	TWDR=sLave_address;
	TWCR=(1<<TWINT)|(1<<TWEN);
	while(!(TWCR&(1<<TWINT)));
    stat=TWSR&0xF8;	
	if (stat == 0x18)
	{
		PORTB|=16;
	}
	if(stat==0x20)
	{
		PORTB|=4;
	}
}
void read(uint8_t dAta)
{ uint8_t stat;
TWCR=(1<<TWEN)|(1<<TWINT);
while(!(TWCR&(1<<TWINT)));
if (stat==0x28)
 stat=TWSR&0xF8;
return (TWDR);
PORTB=8;	
}
};
