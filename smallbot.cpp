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
  //Drive curved
    motor(1,-100);
    motor(2,-100);
    msleep(800);
  //Turn Left
    motor(1, -1000);
    motor (2, -10);
    msleep(500); 
   //Move forward
    motor(1,-1000);
    motor(2,-580);
    msleep(5400);
    //Lower Claw
    motor(1,0);
    motor(2,0);
    msleep(100);
    set_servo_position(1,1175);
    msleep(50);
    set_servo_position(1,1290);  
    msleep(1000);
    set_servo_position(2,250);
    msleep(50);
    
    //End of "Raising Flag" Mission
    
    //Flip the Switch Mission
   return 0;

    
    
    
    
    
}
