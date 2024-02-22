#include <kipr/wombat.h>

int main()
{
    printf("Hello World\n");
    set_servo_position(1,250);
    set_servo_position(2,170);
    motor(1, -60);
    motor(2, -70);
    msleep(2750);
    set_servo_position(1,1500);
    motor(1,0);
    motor(2,0);
    msleep(500);
    set_servo_position(2,1780);
    msleep(1000);
    set_servo_position(1,250);
    msleep(750);
    motor(1,-1000);
    motor(2,-100);
    msleep(3000);
    motor(1,-50);
    motor(2,1);
    msleep(500);
   return 0;

    
    
    
    
    
}
