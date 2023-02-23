#include <16F877a.h>
#device ADC = 10
#use delay(crystal = 20000000)
#FUSES NOWDT, NOBROWNOUT, NOLVP

//Directiva para utilizar puerto USART
#use rs232(BAUD=9600, XMIT = PIN_C6, RCV=PIN_C7)

int8 sum(int8 x, int8 y)
{
   return x+y;
}

int8 diff(int8 x, int8 y)
{
   return x-y;
}

int8 prod(int8 x, int8 y)
{
   return x*y;
}

int8 div(int8 x, int8 y)
{
   return x/y;
}


void main()
{
   setup_uart(9600); //Configurar baudios
   
   int8 num1, num2, suma, resta, multi;
   float divi;
   
   printf("Aritmetic Operations in PIC16F877A\n\r");
   printf("Please enter two integers numbers\n\r");
   
   scanf("%d %d", &num1, &num2);
   
   suma = sum(num1,num2);
   resta = diff(num1,num2);
   multi = prod(num1,num2);
   divi = div(num1,num2);
   
   printf("The sum of both numbers is: %u + %u: %u\n\r",num1,num2,suma);
   printf("The difference of both numbers is: %u - %u: %u\n\r",num1,num2,resta);
   printf("The product of both numbers is: %u * %u: %u\n\r",num1,num2,multi);
   printf("The division of both numbers is: %u / %u: %f\n\r",num1,num2,divi);
}
