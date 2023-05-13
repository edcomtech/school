#INCLUDE <16F877a.h>
#DEVICE ADC=10
#USE delay(crystal=4Mhz)
#fuses HS,NOWDT,NOPROTECT,PUT,NOLVP,NOBROWNOUT

#USE STANDARD_IO(B)
#USE STANDARD_IO(C)
#USE STANDARD_IO(D)

//#use I2C(MASTER, SDA=PIN_C4, SCL=PIN_C3, FAST)

#DEFINE M1 PIN_E0

//#define ADDRESS_LCD 0x4E
//#include <LCD_I2C.c>
#include <LCD_C.c>
#include <kbd4x4_d.c>
#include <getnum16.c>

short High = 0;

int16 T_HIGH;
int16 T_LOW;

int16 contador=0;
double porcentaje;
int16 RPM;
int16 pulsos = 20;
int16 objetivo;
int error;

#INT_EXT
void ext_isr(){
   contador++;
}

#INT_TIMER0
void ext_isr2(){
      if(porcentaje >= 100){
         set_timer0(T_HIGH);
         output_high(M1);
      return;
      }
      if(porcentaje == 0){
         set_timer0(T_HIGH);
         output_low(M1);
      return;
      }
      if(High){
       set_timer0(T_HIGH); 
       output_high(M1);
     }else{
       set_timer0(T_LOW);
       output_low(M1);
     }
   High++;
}

void main(){
   input(PIN_B0);
   kbd_init();
   lcd_init();
   
   output_low(PIN_E0);
   output_low(PIN_E1);
   
   printf(lcd_putc,"OBJETIVO \n(45-150RPM):");
   objetivo = get_num_lcd(14,2);
   
    if(objetivo<45 || objetivo>150){
    printf(lcd_putc,"\fOUT OF \nRANGE RESET");
    delay_ms(1000);
   }else {
   
   enable_interrupts(INT_EXT);
   
   setup_timer_0(RTCC_INTERNAL | RTCC_DIV_256);
   ext_int_edge(H_TO_L);
   enable_interrupts(INT_TIMER0);
 
   enable_interrupts(GLOBAL);
   set_timer0(255);
   
   porcentaje = (objetivo*100)/150;
   
  
   while(1){
   printf(lcd_putc,"\fRPM %lu PER %lf \nOBJ %lu  ERR %u",RPM,porcentaje,objetivo,error);
    delay_ms(5000);
    ///////////////////////////////////////////////////////////////
    RPM = (60 * contador)/ (5.0 * pulsos); // Calcular RPM
    
    if (rpm < objetivo){
    error = objetivo - rpm;
    } else if(rpm > objetivo){
    error = rpm - objetivo;
    }
    contador = 0;
    
    printf(lcd_putc,"\fRPM %lu PER %lf \nOBJ %lu  ERR %u",RPM,porcentaje,objetivo,error);
   
    
     if(RPM < objetivo-3){
         porcentaje += 3;
         }
      else if(RPM > objetivo+3){
         porcentaje -= 3;
    }
    T_LOW= (int16)(((float)porcentaje*255.0)/100);
    T_HIGH =255-T_LOW;
   }
  }
}

