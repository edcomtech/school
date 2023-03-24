#include <16F877a.h>
#device ADC=10
#use delay(crystal=4Mhz)
#FUSES NOWDT, NOBROWNOUT, NOLVP

#USE STANDARD_IO(A)
#USE STANDARD_IO(B)
#USE STANDARD_IO(D)

#include <lcd_d.c>
#include <kbd_b 4x4.c>
#include <getnum16.c>

#use rs232(BAUD=9600, XMIT = PIN_C6, RCV=PIN_C7)

#define servo PIN_A1

void posicionarServo(int16 pos){

   int16 ancho_alto = -10.2*(float)pos + 2390;
   int16 complemento = 20000 - ancho_alto;
   
   for(int8 i = 0; i < 50; i++){
      output_high(servo);
      delay_us(ancho_alto);
      output_low(servo);
      delay_us(complemento);
   }
}

void main(){
   port_b_pullups(1);
   output_low(servo);
   kbd_init(); 
   lcd_init(); 
   
   int16 degrees = 0;
   
   while(1){
      do{
         printf(lcd_putc,"\fDe: %lu",degrees);
         printf(lcd_putc,"\nA: ");
         
         degrees = get_num_lcd(4,2);
        
      }while(degrees > 180);
         posicionarServo(degrees);
   }
}
