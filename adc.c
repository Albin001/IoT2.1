
#include<pic.h>
#define XTAL_FREQ 20000000
#pragma config FOSC = HS        // Oscillator Selection bits (HS oscillator)
#pragma config WDTE = OFF       // Watchdog Timer Enable bit (WDT disabled)
#pragma config PWRTE = OFF      // Power-up Timer Enable bit (PWRT disabled)
#pragma config BOREN = OFF      // Brown-out Reset Enable bit (BOR disabled)
#pragma config LVP = OFF        // Low-Voltage (Single-Supply) In-Circuit Serial Programming Enable bit (RB3 is digital I/O, HV on MCLR must be used for programming)
#pragma config CPD = OFF        // Data EEPROM Memory Code Protection bit (Data EEPROM code protection off)
#pragma config WRT = OFF        // Flash Program Memory Write Enable bits (Write protection off; all program memory may be written to by EECON control)
#pragma config CP = OFF   
#define rs  RC0
#define  e RC1
unsigned int i,j;
unsigned int a,b,c,d;
unsigned int a1,b1,c1,d1;
unsigned int a2,b2,c2,d2;
void delay(unsigned int count);
void lcd_cmd(unsigned char cd);
void lcd_data(unsigned char data);
void lcd_display(const unsigned char *a5);
void  delay1();
void transmit(unsigned char a6);
void main(void) {
    TRISC=0x00;
    TRISD=0x00;
    TRISA=0xFF;
    OPTION_REG=0x07;
    TMR0=0x3D;
    ADCON1=0x00;
    TXSTA=0x24;
    RCSTA=0x90;
    SPBRG=129;
    lcd_cmd(0x38);
    lcd_cmd(0x06);
    lcd_cmd(0x0E);
    lcd_cmd(0x80);
    lcd_cmd(0x01);
    lcd_display("Welcome");
      lcd_cmd(0xC3);
      lcd_display("Embedded");
      delay(500);
      lcd_cmd(0x01);
    while(1)
    {
    ADCON0=0x00;
    ADCON0=0x00;
    ADCON0=0x01;
    delay1();
    GO_DONE=1;
    while(GO_DONE==1);
    a=ADRESH;
     transmit('{');
      b=((a/100)+48);
      lcd_cmd(0x80);
      lcd_display("Hum");
      lcd_cmd(0xC0);
      lcd_data(b);
      transmit(b);
      c=((a%100)/10+48);
      lcd_data(c);
      transmit(c);
      d=((a%10)+48);
      lcd_data(d);
     transmit(d);
     transmit(',');
    
    lcd_cmd(0x01);
    lcd_cmd(0x86);
    lcd_display("Temp");
    ADCON0=0x08;
    ADCON0=0x08;
    ADCON0=0x09;
    delay1();
    GO_DONE=1;
    while(GO_DONE==1);
 
    a1=ADRESH;
     b1=((a1/100)+48);
     transmit(b1);
     lcd_cmd(0xC6);
    lcd_data(b1);
    c1=((a1%100)/10+48);
    transmit(c1);
    lcd_data(c1);
    d1=((a1%10)+48);
    transmit(d1);
    transmit(',');
    lcd_data(d1);
    lcd_cmd(0x01);
    lcd_cmd(0x86);
    lcd_display("Moist");
    ADCON0=0x10;
    ADCON0=0x10;
    ADCON0=0x11;
    lcd_cmd(0xC6);
    delay1();
     GO_DONE=1;
    while(GO_DONE==1);
    a2=ADRESH;
     b2=((a2/100)+48);
     transmit(b2);
    lcd_data(b2);
    c2=((a2%100)/10+48);
   transmit(c2);
    lcd_data(c2);
    d2=((a2%10)+48);
   transmit(d2);
    transmit('}');
   transmit('$');
    lcd_data(d2);
    lcd_cmd(0x01);
    delay1();
    
    }
    return;
}
void delay(unsigned int count)
{
    for(i=0;i<count;i++)
        for(j=0;j<count;j++);
}
void lcd_cmd(unsigned char cd)
{
    PORTD=cd;
    rs=0;
    e=1;
    delay(250);
    e=0;
    //delay(100);
}
void lcd_data(unsigned char data)
{
     
    PORTD=data;
    rs=1;
    e=1;
    delay(250);
    e=0;
    //delay(50);
}
void lcd_display(const unsigned char *a5)
{
     while(*a5!=0)
    {
        lcd_data(*a5);
        a5++;
    }
}
void  transmit(unsigned char a6)
{
    TXREG=a6;
    while(TXIF==0);
    TXIF=0;
}
void delay1()
{
    while(TMR0IF==0);
    TMR0=0x3D;
    TMR0IF=0;
}