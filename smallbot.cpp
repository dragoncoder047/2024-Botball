#include <kipr/wombat.h>

int main()
{
    printf("Hello World\n");
  // Lift and Open Claw
    set_servo_position(1,250);
    set_servo_position(2,170);
  // Drive Forward 
    motor(1, -80);
    motor(2, -90);
    msleep(2895);
  // Get wooden person
    set_servo_position(1,1720);   
    motor(1,0);
    motor(2,0);
    msleep(400);
  //Grab Person
    set_servo_position(2, 2830);
    msleep(1100);
  //Lift Person
    set_servo_position(1, 350);
    msleep(750);
  //Drive straight a bit
    motor(1,-500);
    motor(2,-500);
    msleep(1000);
   //Turn left
    motor(2,-1000);
    motor(1,1000);
    msleep(500);
    motor(1,-500);
    motor(2,-500);
    msleep(1000);
  //Turn right
    motor(1,-1000);
    motor(2,1000);
    msleep(1000);
    motor(1,-500);
    motor(2,-500);
    msleep(6000);
    motor(1,500);
    motor(2,500);
    msleep(1000);
    motor(1,-1000);
    motor(2,1000);
    msleep(800);
    motor(1,-400);
    motor(2,-300);
    msleep(1500);
    motor(1,-70);
    motor(2,-10);
    msleep(500);
    
    //Drop in person
    while (!digital(8)) msleep(10);
    motor(1,0);
    motor(2,0);
    msleep(100);
    motor(1,500);
    motor(2,500);
    msleep(1000);
    motor(2,-1000);
    motor(1,100);
    msleep(475);
    motor(1,-150);
    motor(2,-150);
    msleep(275);
    motor(1,0);
    motor(2,0);
    msleep(100);
    set_servo_position(1,1175);
    msleep(50);
    set_servo_position(1,1290);  
    msleep(1000);
    set_servo_position(2,250);
    msleep(1700);
    
    //Hit the guy on the head
    set_servo_position(1,400);
    msleep(2000);
    set_servo_position(2,2000);
    msleep(2000);
    set_servo_position(1,1600);
    msleep(1500);
    set_servo_position(1,400);
    msleep(2000);
    set_servo_position(2,2000);
    msleep(2000);
    set_servo_position(1,1600);
    msleep(1500); 
    
   return 0;
    
    
    
    
    
    
}
