#include <16F877A.h>
#fuses XT,NOWDT
#use delay(clock= 4 MHz)  

#use I2C(MASTER, SDA=PIN_C4, SCL=PIN_C3, FAST)
#use standard_io(B)        

#define ADDRESS_LCD 0x4E
#define LED PIN_E0   
#include <LCD_I2C.c>

int16 desbordes = 0;

#INT_TIMER1
void t1_isr(){
   set_timer1(0);
   desbordes++; 
}

void hello_there ()
{
   printf(lcd_putc,"\fPractica 3 U3 ");
   printf(lcd_putc,"\nConteo de Tiempo");
   delay_ms(1000);
}

void ledbeh(int16 x){
output_high(LED);
delay_ms(x);
output_low(LED);
break;
}

void main(){
   PORT_B_PULLUPS(1);
   input(PIN_B0);
   output_low(LED);
   lcd_init();
   
   setup_timer_1(T1_INTERNAL | T1_DIV_BY_8); 
   enable_interrupts(GLOBAL);
   enable_interrupts(INT_TIMER1);   
   
   //float tiempo_ms;
   int16 pulsos;
   float tiempo_ms;
   int16 time_led;
   
   hello_there();

   while (TRUE)
   {
      if(input(pin_b0)==0)
      {  
       set_timer1(0);
       printf(lcd_putc,"\fCounting ");    
       desbordes = 0;  
       while (input(pin_b0)==0);
       pulsos = get_timer1(); 
       tiempo_ms = (float)pulsos * 0.008 + (float)desbordes * 524.288;
       time_led = tiempo_ms;
       printf(lcd_putc,"\f%lu\n%f",pulsos,tiempo_ms);
       ledbeh(time_led);
       pulsos = 0;
       desbordes = 0;
       delay_ms(3000);
      }
       if(input(pin_b0)==1)
      {
         printf(lcd_putc,"\fPresionar Boton");
         while (input(pin_b0)==1) pulsos = 0;
      }
   }
}
