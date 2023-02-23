#include <16f877a.h>
#fuses XT, NOWDT
#use delay(clock = 4000000)
#use standard_io(B)
#use standard_io(C)

// LIGHTS
void green(){
     for(int i=0; i<=100; i++){
          output_high(PIN_B2);
          delay_ms(50);
          output_low(PIN_B2);
         if(input(PIN_C0)==1){
           output_low(PIN_B2);
           break;
   }
}
}

void yellow(){
 int y=0;

     for (y=0; y < 4 ; y++){
     output_high(PIN_B1);
      delay_ms(375);
     output_low(PIN_B1);
      delay_ms(375);
  } 
}

void red(){
     for(int i=0; i<=100; i++){
          output_high(PIN_B0);
          delay_ms(80);
          output_low(PIN_B0);
         if(input(PIN_C0)==1){
         i=0;
   }
}
}

void main(){
    port_b_pullups (TRUE);
    output_low(PIN_B0);
    output_low(PIN_B1);
    output_low(PIN_B2);
    
    while (1)
    {
        green();
        yellow();
        red();
    }
}
