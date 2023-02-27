#include <16f877a.h> 
#device ADC = 10
#use delay(crystal = 4000000)
#fuses XT, NOWDT
#use STANDARD_IO(B)
#use STANDARD_IO(C)
#use STANDARD_IO(D)

#include <lcd_c.c>
#include <kbd_b 4x4.c>
#include <getnum16.c>

#define motor1 PIN_D0
#define motor2 PIN_D1
#define motor3 PIN_D2
#define stop PIN_D3

void main(){
  PORT_B_PULLUPS(1);
  lcd_init();
  kbd_init();
  
  int16 nomotor, motortime;
  int1 condition;
  int16 i;
   while(1){
   do{
   printf(lcd_putc,"\fCHOOSE A MOTOR"); //Elegir motor
   nomotor = get_num_lcd(9,2);
   printf(lcd_putc,"\fMOTOR CHOSEN: \n%5lu", nomotor);
   delay_ms(700);
   condition = (nomotor != 1) && (nomotor != 2) && (nomotor != 3);
         if(condition == 1){
           printf(lcd_putc,"\fMOTOR NOT VALID");
           delay_ms(1000);
           }
   }while(condition==1);
   
   lcd_gotoxy(9,1);
   printf(lcd_putc,"\fCHOOSE TIME"); //Elegir tiempo
   motortime = get_num_lcd(9,2);
      if(motortime<1 || motortime>120){
      printf(lcd_putc,"\fVVALUE OUT \nOF RANGE");
      delay_ms(500);
      lcd_gotoxy(9,2);
      printf(lcd_putc,"\fENTER TIME");
      motortime = get_num_lcd(9,2);
      delay_ms(1000);
      }
      
//////////////////////////////////////////////////////

  switch(nomotor){

case 1:
          for(i=0; i < motortime*10;){
         printf(lcd_putc,"\fMOTOR 1 IS ON for  \n%5lu %5lu", i, motortime*10);//Motor 1
          output_high(motor1);
          delay_ms(100);
                     if (input(stop) == 1 ){     //STOP
                     output_LOW(motor1);
                     printf(lcd_putc,"\fEMERGENCY STOP!!");
                     delay_ms(100);
                     printf(lcd_putc,"\fPRESS ANY KEY");
                     nomotor = get_num_lcd(1,2);
                     break;
                     if(i>motortime*10){
                     break;
                     }
               }
               i++;
          }
output_low(motor1);

break;

/////////////////////////////////////////////////////

case 2:
 int16 cicloform2 = motortime*10;
          for (int i = 0 ; i < cicloform2 ; ){
            
            if ( i > -1  &&  i < (cicloform2/4)){
              printf(lcd_putc,"\fMOTOR 2 IS ON");//Motor 1
              output_high(motor2);
              delay_ms(100);
                if (input(stop) == 1 ){     //STOP
                     output_LOW(motor2);
                     printf(lcd_putc,"\fEMERGENCY STOP!!");
                     delay_ms(500);
                     printf(lcd_putc,"\fPRESS ANY KEY");
                     nomotor = get_num_lcd(1,2);
                     break;
                }
            }
            
            if ( i > (cicloform2/4) &&  i < ((cicloform2/4)*2)){
              printf(lcd_putc,"\fMOTOR 2 IS OFF");//Motor 1
              output_LOW(motor2);
              delay_ms(100);
                if (input(stop) == 1 ){     //STOP
                     output_LOW(motor2);
                     printf(lcd_putc,"\fEMERGENCY STOP!!");
                     delay_ms(500);
                     printf(lcd_putc,"\fPRESS ANY KEY");
                     nomotor = get_num_lcd(1,2);
                     break;
                }
            }
            
             if ( i > ((cicloform2/4)*2) &&  i < ((cicloform2/4)*3)){
              printf(lcd_putc,"\fMOTOR 2 IS ON");//Motor 1
              output_high(motor2);
              delay_ms(100);
                if (input(stop) == 1 ){     //STOP
                     output_LOW(motor2);
                     printf(lcd_putc,"\fEMERGENCY STOP!!");
                     delay_ms(500);
                     printf(lcd_putc,"\fPRESS ANY KEY");
                     nomotor = get_num_lcd(1,2);
                     break;
                }
            }
            
            if ( i > ((cicloform2/4)*3) &&  i < ((cicloform2/4)*4)){
              printf(lcd_putc,"\fMOTOR 2 IS OFF");//Motor 1
              output_LOW(motor2);
              delay_ms(100);
                if (input(stop) == 1 ){     //STOP
                     output_LOW(motor2);
                     printf(lcd_putc,"\fEMERGENCY STOP!!");
                     delay_ms(500);
                     printf(lcd_putc,"\fPRESS ANY KEY");
                     nomotor = get_num_lcd(1,2);
                     break;
                }
            }
            
          i++;
   
          }
   output_low(motor2);

    
   break;
   
/////////////////////////////////////////////////////
   
case 3:

//
  int16 cicloform3 = motortime; // PARES
  if(cicloform3 % 2==0){// checo si el modulo es 0
  double even = (cicloform3 / 2);
       for (int i = 0 ; i < even; i++){
       printf(lcd_putc,"\fMOTOR 3 IS ON");//Motor 3
      output_high(motor3);
      delay_ms(1000);
      printf(lcd_putc,"\fMOTOR 3 IS OFF");
      output_low(motor3);
      delay_ms(1000);
               if (input(stop) == 1 ){     //STOP
                     output_LOW(motor3);
                     printf(lcd_putc,"\fEMERGENCY STOP!!");
                     delay_ms(500);
                     printf(lcd_putc,"\fPRESS ANY KEY");
                     nomotor = get_num_lcd(1,2);
                     break;
               }
       }
   output_low(motor3);
   } else{ // IMPARES
      cicloform3+=1;
      double odd=cicloform3/2;
      for(i=0; i<odd; i++){
       printf(lcd_putc,"\fMOTOR 3 IS ON");//Motor 3
      output_high(motor3);
      delay_ms(1000);
       printf(lcd_putc,"\fMOTOR 3 IS OFF");//Motor 3
      output_low(motor3);
      delay_ms(1000);
      if (input(stop) == 1 ){     //STOP
                     output_LOW(motor3);
                     printf(lcd_putc,"\fEMERGENCY STOP!!");
                     delay_ms(500);
                     printf(lcd_putc,"\fPRESS ANY KEY");
                     nomotor = get_num_lcd(1,2);
                     break;
               }
   }
 output_low(motor3);
   }
break;

/////////////////////////////////////////////////////
  }

 }
}
