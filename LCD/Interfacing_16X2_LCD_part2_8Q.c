#include<lpc21xx.h>

#define WRITEBYTE(WORD,POS,BYTE) WORD=(WORD &(~(255<<POS)))|(BYTE<<POS)
#define SSETBIT(WORD,POS) WORD = 1<<POS
#define SETBIT(WORD,POS)  WORD |= 1<<POS
#define READBIT(WORD,POS) ((WORD>>POS)&1)
#define SCLRBIT(WORD,POS) WORD =1<<POS
//types.h
				   typedef unsigned char u8;
				   typedef signed char s8;
				   typedef unsigned short u16;
				   typedef signed short s16;
				   typedef unsigned int u32;
				   typedef signed int s32;
				   typedef float f32;
//delay_files
void delay_ms(unsigned int dlyms){
     dlyms *=12000;
	 while(dlyms--);
}
void delay_us(unsigned int dlyus){
     dlyus *=12;
	 while(dlyus--);
}		
void delay_s(unsigned int dlys){
     dlys *=12000000;
	 while(dlys--);
}		
//lcd_defines.h
#define CLRLCD 0X01
#define CUR_HOME 0X02
#define SFT_CUR_RGT 0X06
#define SFT_CUR_LEFT 0X07
#define DISP_OFF_CUR_OFF 0X08
#define DISP_ON_CUR_OFF 0X0C
#define DISP_ON_CUR_ON 0X0E
#define DISP_ON_CUR_BLK 0X0F
#define SFT_DISP_RGT 0X1C
#define SFT_DISP_LFT 0X18
#define MODE_8BIT_2LINE 0X38
#define MODE_4BIT_2LINE 0X28
#define CGRAM_START_ADDR 0X40
#define DDRAM_START_ADDR 0X80
#define GOTO_LINE1_POS0 0X80
#define GOTO_LINE2_POS0 0XC0
#define GOTO_LINE3_POS0 0X94
#define GOTO_LINE4_POS0 0XD4
#define LCD_DATA 8
#define LCD_RS 19
#define LCD_EN 20
#define LCD_RW 18

//lcd.c
void writeLCD(u8 dat)
{
	//SCLRBIT(IOCLR0,LCD_RW);
	WRITEBYTE(IOPIN0,LCD_DATA,dat);
	SSETBIT(IOSET0,LCD_EN);
	delay_us(1);
	SCLRBIT(IOCLR0,LCD_EN);
	delay_ms(2);
}
void cmdLCD(u8 cmd)
{
	SCLRBIT(IOCLR0,LCD_RS);
	writeLCD(cmd);
}
void charLCD(u8 ascii)
{
	SSETBIT(IOSET0,LCD_RS);
	writeLCD(ascii);
}
void strLCD(s8 *p)
{
	while(*p)
	{
		charLCD(*p++);
	}
}
void u32LCD(u32 n)
{
	u8 a[10];
	s32 i=0;
	if(n==0)
	{
		charLCD('0');
	}
	else
	{
		while(n>0)
		{
			a[i++]=(n%10)+48;
			n/=10;
		}
		for(--i;i>=0;i--)
		{
			charLCD(a[i]);
		}
	}
}
void s32LCD(s32 n)
{
	if(n==0)
		charLCD('0');
	else if(n<0)
	{
		charLCD('-');
		n=-n;
		u32LCD(n);
	}
}
void f32LCD(f32 f,u8 ndp)
{
	u32 i,j;
	if(f<0.0)
	{
		charLCD('-');
		f=-f;
	}
	i=f;
	u32LCD(i);
	charLCD('.');
	for(j=0;j<ndp;j++)
	{
		f=(f-i)*10;
		i=f;
		charLCD(i+48);
	}
}
void binLCD(u32 n)
{
	s8 bit=15;
	while(bit>=0)
	{
		charLCD(((n>>bit)&1)+48);
		bit--;
	}
}
void hexLCD(u32 n)
{
	s32 i=0,nibble;
	u8 a[8];
	if(n==0)
		charLCD('0');
	else
	{
		while(n)
		{
			nibble=n%16;
			nibble=(nibble>9)?((nibble-10)+'A'):(nibble+48);
			a[i++]=nibble;
			n/=16;
		}
		for(--i;i>=0;i--)
		{
			charLCD(a[i]);
		}
	}
}
void octLCD(u32 n)
{
	u8 a[15];
	s32 i=0,x;
	if(n==0)
		charLCD('0');
	else
	{
		while(n)
		{
			x=n%8;
			a[i++]=x+48;
			n/=8;
		}
		for(--i;i>=0;i--)
			charLCD(a[i]);
	}
}
void InitLCD()
{
	WRITEBYTE(IODIR0,LCD_DATA,0XFF);
	SETBIT(IODIR0,LCD_RS);
	SETBIT(IODIR0,LCD_EN);
	//SETBIT(IODIR0,LCD_RW);
	delay_ms(15);
	cmdLCD(0x30);
	delay_ms(5);
	cmdLCD(0x30);
	delay_us(100);
	cmdLCD(0x30);
	cmdLCD(MODE_8BIT_2LINE);
	cmdLCD(SFT_CUR_RGT);
	cmdLCD(DISP_ON_CUR_BLK);
	cmdLCD(CLRLCD);
}

/*
		8. Write an ECP to convert first and last character of each word in to upper case and
		display the final result on LCD.
		Note: Connect two switches. Based on first switch press, take “vector india” as input and
		do the operation; Based on second switch press, take “vector Hyderabad” as input and do
		the operation. In both cases print input and output on lcd screen.
		Output:
		When Switch1 is pressed, display “vector india” on the 1 st line of LCD and when the
		switch1 is released display “VectoR IndiA” on the 2nd line of LCD.
		When Switch2 is pressed, display “vector hyderabad” on the 1 st line of LCD and when
		the switch2 is released display “VectoR HyderabaD” on the 2 nd line of LCD.
		If none of the switch is pressed, display “waiting for input” on the 1 st line of LCD.
*/
#include<string.h>
#define AL_SW1 0
#define AL_SW2 1
void convert_lower_to_upper(s8 *p)
{
	s32 len;
	len=strlen(p)-1;
	if((p[0]>=97)&&(p[0]<=122))
		p[0]=p[0]-32;
	if((p[len]>=97)&&(p[len]<=122))
		p[len]=p[len]-32;
	while(p=strchr(p,' '))
	{
		if((p[1]>=97)&&(p[1]<=122))
			p[1]=p[1]-32;
		if((p[-1]>=97)&&(p[-1]<=122))
			p[-1]=p[-1]-32;
		p++;
	}
}
int main()
{
	s8 s1[]="vector india";
	s8 s2[]="vector hyderabad";
	s8 s3[50],s4[50];
	strcpy(s3,s1);
	strcpy(s4,s2);
	convert_lower_to_upper(s3);
	convert_lower_to_upper(s4);
	InitLCD();
	cmdLCD(GOTO_LINE1_POS0);
	strLCD("waiting for input");
	while(1)
	{
		if(READBIT(IOPIN0,AL_SW1)==0)
		{
			cmdLCD(CLRLCD);
			cmdLCD(GOTO_LINE1_POS0);
			strLCD(s1);
			while(READBIT(IOPIN0,AL_SW1)==0);
			cmdLCD(GOTO_LINE2_POS0);
			strLCD(s3);
		}
		else if(READBIT(IOPIN0,AL_SW2)==0)
		{
			cmdLCD(CLRLCD);
			cmdLCD(GOTO_LINE1_POS0);
			strLCD(s2);
			while(READBIT(IOPIN0,AL_SW2)==0);
			cmdLCD(GOTO_LINE2_POS0);
			strLCD(s4);
		}
	}
}
