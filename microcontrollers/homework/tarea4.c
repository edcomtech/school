#include <16F877a.h>
#device ADC = 10
#use delay(crystal = 20000000)
#FUSES NOWDT, NOBROWNOUT, NOLVP, HS

#include <lcd_d.c>
#include <kbd4x4_b.c>
#include <getNum16.c>


void main(){
   port_b_pullups (TRUE);
   lcd_init();
   kbd_init();

   int16 numA, numB;

    printf(lcd_putc,"\fEnter A:");
    numA = get_num_lcd(1,2);  
    printf(lcd_putc,"\fEnter B:");
    numB = get_num_lcd(1,2);
    
      if(numB<numA){
        printf(lcd_putc,"\fB es menor que A");
      }if((numB>numA)){
        printf(lcd_putc,"\fA es menor que B");
      }if((numB==numA)){
        printf(lcd_putc,"\fA es igual que B");
      }

    }
