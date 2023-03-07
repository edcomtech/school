#include <16f877a.h>
#device ADC=10
#use delay(crystal=4000000)
#FUSES NOWDT, NOBROWNOUT, NOLVP, HS
#USE STANDARD_IO(A)
#USE STANDARD_IO(D)
#USE STANDARD_IO(E)

#include <lcd_d.c>
#include <kbd_b 4x4.c>
#include <getnum16.c>

#define right PIN_E1
#define left PIN_E0
#define stop PIN_E2

int1 delay_stop(int16 sec);

int16 routine; 

void rightmov(){
    output_high(right);
    output_low(left);
}

void leftmov(){
    output_high(left);
    output_low(right);
}

void motorstop(){
    output_low(right);
    output_low(left);
}

void r105(){
int8 i = 0;
int1 salir = 0;
while(i<3){
rightmov();
salir = delay_stop(5);
    if(salir == 1)break;
motorstop();
salir = delay_stop(1);
    if(salir == 1)break;
leftmov();
salir = delay_stop(5);
    if(salir == 1)break;
motorstop();
salir = delay_stop(1);
    if(salir == 1)break;
i++;
}
}

void r210(){
int i = 0;
int1 salir = 0;
while(i<4){
rightmov();
salir = delay_stop(3);
    if(salir == 1)break;
motorstop();
salir = delay_stop(1);
    if(salir == 1)break;
i++;
}
}

void r315(int16 timet){
int i = 0;
int1 salir = 0;
while(i<3){
    rightmov();
    salir = delay_stop(timet);
    if(salir == 1)break;
    motorstop();
    salir = delay_stop(1);
    if(salir == 1)break;
    leftmov();
    salir = delay_stop(timet);
    if(salir == 1)break;
    motorstop();
    salir = delay_stop(1);
    if(salir == 1)break;
i++;
}
}

void r420(int16 timet, int16 iterationt){
int i = 0;
int1 salir = 0;
while(i<iterationt){
    rightmov();
     salir = delay_stop(timet);
    if(salir == 1)break;
    motorstop();
    salir = delay_stop(1);
    if(salir == 1)break;
    leftmov();
    delay_stop(timet);
    motorstop();
    salir = delay_stop(1);
    if(salir == 1)break; 
i++;
}
}


void emergency_stop(){
   motorstop();
   printf(lcd_putc,"\fEMERGENCY STOP");
   delay_ms(1000);
   while(input(stop) == 1){}
   printf(lcd_putc,"\fENTER KEY");
   char c = read_key();
}

int1 delay_stop(int16 sec){
   for(int16 i = 0; i < sec * 100; i++){
      delay_ms(10);
      if(input(stop)){
         emergency_stop();
         return 1;
      }
   }
   return 0;
}

void main(){
   PORT_B_PULLUPS(1);
   kbd_init();
   lcd_init();
   motorstop();

   int16 timett,iteration;
   int1 condition;
   input(stop);

  while(1){
  do{
   lcd_putc("\fLOADING...");
   delay_ms(1000);
   lcd_putc("\fCHOOSE ROUTINE");
   lcd_gotoxy(1,2);
   routine = get_num_lcd(9,2);
   condition = (routine!=105) && (routine!=210) && (routine!=315) && (routine!=420);
   if(condition == 1){
   lcd_putc("\fINCORRECT\nROUTINE  ");
   delay_ms(1000);
   }
   }while(condition==1);

switch(routine){
//105//
    case 105:
    lcd_putc("\fROUTINE 105 \nRUNNING");
    r105();
    break;
 //210// 
    case 210:
    lcd_putc("\fROUTINE 210 \nRUNNING");
    r210();
    break;
 //315// 
    case 315:
    lcd_gotoxy(9,1);
    printf(lcd_putc,"\fDEFINE TIME");
    timett = get_num_lcd(9,2);
    if(timett<1 || timett>120){
    printf(lcd_putc,"\fOUT OF \nRANGE");
    delay_ms(500);
    lcd_gotoxy(9,2);
    printf(lcd_putc,"\fDEFINE TIME");
    timett = get_num_lcd(9,2);
    delay_ms(1000);
    }
    lcd_putc("\fROUTINE 315 \nRUNNING");
    r315(timett);
    break;

 //420//
    case 420:
    lcd_gotoxy(9,1);
    printf(lcd_putc,"\fDEFINE TIME");
    timett = get_num_lcd(9,2);
    if(timett<1 || timett>120){
    printf(lcd_putc,"\fOUT OF \nRANGE");
    delay_ms(500);
    lcd_gotoxy(9,2);
    printf(lcd_putc,"\fDEFINE TIME");
    timett = get_num_lcd(9,2);
    delay_ms(1000);
    }
    printf(lcd_putc,"\fDEFINE ITERATION");
    iteration = get_num_lcd(9,2);
    if(iteration<1 || iteration>50){
    printf(lcd_putc,"\fOUT OF \nRANGE");
    delay_ms(500);
    lcd_gotoxy(9,2);
    printf(lcd_putc,"\fDEFINE TIME");
    iteration = get_num_lcd(9,2);
    delay_ms(1000);
    }
    lcd_putc("\fROUTINE 420 \nRUNNING");
    r420(timett, iteration);
    break;

    //SWITCH CLOSE//
}
   
   //WHILE CLOSE//
   }
   //MAIN CLOSE//
}
