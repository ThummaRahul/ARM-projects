#include<LPC21XX.h>
#define SETBIT(WORD,BITPOS) WORD|=(1<<BITPOS)
#define SSETBIT(WORD,BITPOS) WORD=(1<<BITPOS)
#define WRITEBYTE(WORD,SBITPOS,BYTE) WORD=(WORD&(~(255<<SBITPOS)))|(BYTE<<SBITPOS)
void delay_s(unsigned int dlys)
{
    dlys *=12000000;
    while(dlys--);
}

#define CA7_DATA_PINS 0
#define DSEL1 8
main()
{
WRITEBYTE(IODIR0,CA7_DATA_PINS,255);
SETBIT(IODIR0,DSEL1);
SSETBIT(IOSET0,DSEL1);
while(1)
{
  WRITEBYTE(IOPIN0,CA7_DATA_PINS,255);
  delay_s(1);
  WRITEBYTE(IOPIN0,CA7_DATA_PINS,0);
  delay_s(1);
 }
}