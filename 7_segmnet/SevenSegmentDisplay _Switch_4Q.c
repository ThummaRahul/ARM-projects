#include<LPC21XX.h>
#define SETBIT(WORD,BITPOS) WORD|=(1<<BITPOS)
#define SSETBIT(WORD,BITPOS) WORD=(1<<BITPOS)
#define SCLRBIT(WORD,BITPOS) WORD=(1<<BITPOS) 
#define WRITEBYTE(WORD,SBITPOS,BYTE) WORD=(WORD&(~(255<<SBITPOS)))|(BYTE<<SBITPOS)
void delay_s(unsigned int dlys)
{
    dlys *=12000000;
    while(dlys--);
}
void delay_ms(unsigned int dlyms)
{
    dlyms *=12000;
    while(dlyms--);
}
#define CA7_DATA_PINS 0
#define DSEL1 8
#define DSEL2 9
char arr[10]={0xc0,0xf9,0xa4,0xb0,0x99,0x92,0x82,0xf8,0x80,0x90};

main()
{
	unsigned int i,j;
	WRITEBYTE(IODIR0,CA7_DATA_PINS,255);
	SETBIT(IODIR0,DSEL1);
	SETBIT(IODIR0,DSEL2);
	while(1)
	{
		for(i=0;i<100;i++)
		{
			for(j=0;j<=500;j++)
			{
				SSETBIT(IOSET0,DSEL1);
				WRITEBYTE(IOPIN0,CA7_DATA_PINS,arr[i/10]);
				delay_ms(1);
				SCLRBIT(IOCLR0,DSEL1);
				SSETBIT(IOSET0,DSEL2);
				WRITEBYTE(IOPIN0,CA7_DATA_PINS,arr[i%10]);
				delay_ms(1);
				SCLRBIT(IOCLR0,DSEL2);
			}
		}
	}
}