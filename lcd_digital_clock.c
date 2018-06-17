#include<avr/io.h>
#define F_CPU 16000000UL
#include<util/delay.h>
#define lcd PORTD 
void lcd_command(unsigned char cmd)
{
lcd= cmd&0xF0;
lcd|= 0b00000100;
_delay_ms(1);
lcd&= 0xF0;
_delay_ms(1);
lcd= (cmd<<4)& 0xF0;
lcd|= 0b00000100;
_delay_ms(1);
lcd&= 0xF0;
_delay_ms(1);
}

void lcd_data(unsigned char da)
{
lcd= da&0xF0;
lcd|= 0b00000101;
_delay_ms(1);
lcd&= 0xF1;
_delay_ms(1);
lcd= (da<<4)&0xF0;
lcd|= 0b00000101;
_delay_ms(1);
lcd&= 0xF1;
_delay_ms(1);
}

void lcd_init()
{
lcd_command(0x02);
lcd_command(0x28);
lcd_command(0x0c);
lcd_command(0x06);
}
void lcd_string (unsigned char *str)
{
 char i=0;
   while( str[i]!='\0')
   { lcd_data(str[i]);
   i++;
   }
   }
void main()
{
DDRD= 0xFF;
lcd_init();

while(1)

{
lcd_command(0x80);
lcd_command(0x06);
lcd_string("  DIGITAL CLOCK");

lcd_command(0xc4);
lcd_command(0x06);
lcd_string("00:00:00");
_delay_ms(100);
for(int n=0; n<3; n++)
{
  for(int m=0; m<=9; m++)
  {
        for (int l=0; l<6; l++)   // for 10+ mins
   {
    for(int k=0; k<=9; k++)  // till 9 mins
      { 
       for( int j=0; j<6; j++)    //  till j for 59 secs
         {   
          for(int i=0; i<=9;i++)     
             { lcd_command(0xCB);
               lcd_data(i+48);
               _delay_ms(1);
              }
           lcd_command(0xCA);
           lcd_data(j+49);    // 59 secs over
          } 
		  lcd_command(0xca);
		  lcd_string("0");
          lcd_command(0xc8);
		  lcd_data(49+k);
		  }
        lcd_command(0xc7);
		lcd_data(l+49);
		lcd_command(0xc8);
		lcd_string("0");

		}
		lcd_command(0xc5);
		lcd_data(49+m);
		lcd_command(0xc7);
		lcd_string("00");
		if((n==2) && (m==3))
		goto restart;
		}
		lcd_command(0xc4);
		lcd_data(49+n);
		lcd_command(0xc5);
		lcd_string("0");
		}
		restart:
		lcd_command(0xc4);
		lcd_string("00:00:00");
		_delay_ms(1000);
}
}

  



