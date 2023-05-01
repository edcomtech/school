#include <16F877a.h>
#device ADC=10
#use delay(crystal=4000000)
#FUSES NOWDT, NOBROWNOUT, NOLVP

#USE STANDARD_IO(A)
#USE STANDARD_IO(D)

#include <lcd_d.c>
#include <kbd_b 4x4.c>
#include <getnum16.c>


int8 pasos[8] = {
   0b1000,//0
   0b1010,//1
   0b0010,//2
   0b0110,//3
   0b0100,//4
   0b0101,//5
   0b0001,//6
   0b1001 //7
};

int8 index = 0;
float objetivo = 0;
float numviejo = 0;
float captura;
int8 grados_real = 0;
float monitor=0;
float registro = 0;
int16 gradosnuev;
void actualizar(){
   output_a(pasos[index]); 
}

void incrementIndex(){
   if(index == 7){
      index = 0;
   }else{
      index++;
   }
}

void decrementIndex(){
   if(index == 0){
      index = 7;
   }else{
      index--;
   }
}

void main(){

   port_b_pullups(1);
   kbd_init(); 
   lcd_init(); 
   
   actualizar();
   delay_ms(3);
   
   int16 longitud;
   int16 grados;
   float conver;
   while(TRUE){
     inicio:
      printf(lcd_putc,"\fDe: %f",registro);
      printf(lcd_putc,"\nA: ");
      longitud = get_num_lcd(5,2);
      
      
     conver=(longitud *180)/(3.1416 * 1.27324);
     grados = conver;
     objetivo = grados;
     captura= grados;
     
     if(longitud <= 300 && longitud >= 0)
  {
    
      if(objetivo < numviejo){
         objetivo =numviejo - objetivo;
         
         int16 pasos_a_recorrer = (objetivo / 0.9);
         grados_real = pasos_a_recorrer * 0.9;
        
        if (grados_real < pasos_a_recorrer){
        pasos_a_recorrer+=1;
         }
        
        if (grados_real > pasos_a_recorrer){
        pasos_a_recorrer-=1;
        }

       //decrementar grados
       
          printf(lcd_putc,"\fDe: %f",registro);
        
         for(int16 i = pasos_a_recorrer; i > 0 ; i--){
            monitor-=0.2;
            decrementIndex();
            lcd_gotoxy(1,2);
            printf(lcd_putc,"avanzando: %f",monitor);
            actualizar();
            registro = monitor;
            delay_ms(3);
         }
      printf(lcd_putc,"\fOperacion\nFinalizada ");
      delay_ms(1000);
      numviejo = captura;
      goto inicio;
      }
         objetivo = objetivo - numviejo;
         int16 pasos_a_recorrer = (objetivo / 0.9);
         grados_real = pasos_a_recorrer * 0.9;
        
        if (grados_real < pasos_a_recorrer)
        {
        pasos_a_recorrer+=1;
        
        }
        
        if (grados_real > pasos_a_recorrer){
        pasos_a_recorrer-=1;
        }

       //incrementar grados
          printf(lcd_putc,"\fDe: %f",registro);
        
         for(int16 i = 0; i < pasos_a_recorrer; i++){
            monitor+=0.2;
            incrementIndex();
            lcd_gotoxy(1,2);
            printf(lcd_putc,"avanzando: %f",monitor);
            actualizar();
            registro = monitor;
            delay_ms(3);
         }
      numviejo = captura;
       printf(lcd_putc,"\fOperacion\nFinalizada ");
      delay_ms(1000);

   }else{
   
   printf(lcd_putc,"\ffuera del\nrango");
   delay_ms(1000);
   }

  } // while
} // main

