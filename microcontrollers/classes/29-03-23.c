#include <16F877A.h>
#device ADC=10
#use delay(crystal=4MHz)
#FUSES NOWDT, NOBROWNOUT, NOLVP, HS
#USE STANDARD_IO(B)

#include <lcd_c.c>

int16 contador=0;
int1 huboCambio=0;
int1 a;
int1 b;
int1 c;
int1 d;

#INT_RB
void rb_isr(){
if(input(PIN_B4)==1){
   contador=contador+1;
   if(a==1){
      contador=contador-1;
   }
   a=1;
}
if(input(PIN_B4)==0){
      a=0;
   }
if(input(PIN_B5)==1){
   contador=contador+2;
   if(b==1){
      contador=contador-2;
   }
   b=1;
}
if(input(PIN_B5)==0){
      b=0;
   }

if(input(PIN_B6)==1){
   contador=contador+5;
   if(c==1){
      contador=contador-5;
   }
   c=1;
}
if(input(PIN_B6)==0){
      c=0;
   }

if(input(PIN_B7)==1){
   contador=contador+10;
   if(d==1){
      contador=contador-10;
   }
   d=1;
}
if(input(PIN_B7)==0){
      d=0;
   }
huboCambio = 1;
}

void main(){
   lcd_init();
   enable_interrupts(GLOBAL);
   while(TRUE){
      enable_interrupts(INT_RB);
      if(huboCambio){
         printf(lcd_putc,"\fContador:%lu",contador);
         huboCambio=0;
      }
   } //WHILE CLOSE
} //MAIN CLOSE