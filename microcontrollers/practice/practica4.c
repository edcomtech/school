#include <16f877a.h>
#device ADC=10
#use delay(crystal=4000000)
#FUSES XT, NOWDT
#USE STANDARD_IO(A)
#USE STANDARD_IO(B)
#USE STANDARD_IO(D)

#include <lcd_d.c>
#include <kbd_b 4x4.c>
#include <getnum16.c>

int8 steps[8] = {
   0b1000,
   0b1010,
   0b0010,
   0b0110,
   0b0100,
   0b0101,
   0b0001,
   0b1001 
};

int8 index = 0;
float target = 0, oldnum = 0, capture;
int8 rdeg = 0;
float dis = 0;
float regis = 0;

void refresh(){
    output_a(steps[index]);
}

void increment(){
    if(index == 7){
        index = 0;
    } else{
        index++;
    }
}

void decrement(){
    if(index == 0){
        index = 7;
    } else{
        index--;
    }
}

void main(){
   PORT_B_PULLUPS(1);
   kbd_init();
   lcd_init();
   
   refresh();
   delay_ms(50);

   int16 degrees;

   while(1){
    begin:
     printf(lcd_putc,"\fCURR POS: %f", regis);
     printf(lcd_putc,"\nTARGET POS: ");
     degrees = get_num_lcd(12,2);
     target = degrees;
     capture = degrees;

     if(degrees <= 360 && degrees >= 0){
        if(target < oldnum){
            target=oldnum-target;
            int16 steps_to_tar = (target / 0.9);
            rdeg = steps_to_tar * 0.9;
            if(rdeg < steps_to_tar){
                steps_to_tar+=1;
            }
            if(rdeg > steps_to_tar){
                steps_to_tar-=1;
            }
            //DECREMENT DEGREES//
            printf(lcd_putc,"\fSTEPS TO GO: %lu", steps_to_tar);
            for(int16 i = steps_to_tar; i>0; i--){
                dis-=0.9;
                decrement();
                lcd_gotoxy(1,2);
                printf(lcd_putc,"DEGREES: %f",dis);
                refresh();
                regis=dis;
                delay_ms(100);
            }
            oldnum = capture;
            goto begin;
        }
        target = target-oldnum;
        int16 steps_to_tar = (target/0.9);
        rdeg =  steps_to_tar*0.9;

        if(rdeg<steps_to_tar){
            steps_to_tar+=1;
        }
        if(rdeg>steps_to_tar){
            steps_to_tar-=1;
        }
         //INCREMENT STEPS//
        printf(lcd_putc,"\fSTEPS TO GO: %lu", steps_to_tar);
        for(int16 i = 0; i<steps_to_tar; i++){
                dis+=0.9;
                increment();
                lcd_gotoxy(1,2);
                printf(lcd_putc,"DEGREES: %f",dis);
                refresh();
                regis=dis;
                delay_ms(100);
            }
            oldnum = capture;
     }

    //WHILE CLOSE//
   }

    //MAIN CLOSE//
}
