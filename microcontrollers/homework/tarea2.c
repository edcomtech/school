#include <16F877a.h>
#device ADC = 10
#use delay(crystal = 20000000)
#FUSES NOWDT, NOBROWNOUT, NOLVP, HS

#use rs232(BAUD=9600, XMIT = PIN_C6, RCV=PIN_C7)

#use STANDARD_IO(A)
#use STANDARD_IO(B)

#define bsum PIN_A0
#define bres PIN_A1

int8 index = 0;

int8 num[] = {

   0b00111111, // 0
   0b00000110, // 1
   0b01011011, // 2
   0b01001111, // 3
   0b01100110  // 4
   0b01101101, // 5
   0b01111101, // 6
   0b00000111, // 7
   0b01111111, // 8
   0b01101111, // 9
   0b1110111,  //A
   0b1111100,  //b
   0b0111001,  //C
   0b1011110,  //d
   0b1111001,  //E
   0b1110001;  //F
};


void show(){
    output_b(num[index]); 
}

void incrementar(){
   if(index == 9) index = 0;
   else index++;
   show();
}

void decrementar(){
   if(index == 0) index = 9;
   else index--;
   show();
}

void main()
{
   setup_uart(9600);

   output_b(0);
   input(bsum);
   input(bres);
   show();

   int8 sact = 0;
   int8 ract = 0;
   int8 sprev = 0;
   int8 rprev = 0;

   while (TRUE){
       if(input(bsum) == 1){
         while(input(bsum) == 1){}
         incrementar();
       }

       if(input(bres) == 1){
         while(input(bres) == 1){}
         decrementar();
       }
    }
}