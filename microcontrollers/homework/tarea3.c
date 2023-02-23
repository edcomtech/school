#include <16F877a.h>
#device ADC=10
#use delay(crystal=20000000)
#FUSES NOWDT, NOBROWNOUT, NOLVP

#define LCD_DATA_PORT   0X07
#define LCD_ENABLE_PIN  PIN_C1
#define LCD_RS_PIN      PIN_C3
#define LCD_RW_PIN      PIN_C2
#define LCD_DATA4       PIN_C4
#define LCD_DATA5       PIN_C5
#define LCD_DATA6       PIN_C6
#define LCD_DATA7       PIN_C7

#include <lcd.c>

#USE STANDARD_IO(D)
#DEFINE limitl 0
#DEFINE limitr 15
#DEFINE upbutton PIN_D0
#DEFINE downbutton PIN_D1
int8 count = 0;

void refresh(){
   printf(lcd_putc,"\fNumero: %02u",count);
}

void incrementar(){
   if(count == limitr){
      count=limitl;
   }else{
      count++;
   }
   refresh();
}

void decrementar(){
   if(count == limitl){
      count = limitr;
   }else{
      count--;
   }
   refresh();
}

void main()
{
   lcd_init();
   refresh();
   while(TRUE){
      if(input(upbutton)){
         while(input(upbutton)){}
         incrementar();
      }if(input(downbutton)){
         while(input(downbutton)){}
         decrementar();
      }
   }
}