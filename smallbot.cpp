#include <kipr/wombat.h>

int main()
{
    printf("Hello World\n");
  // Lift and Open Claw
    set_servo_position(1,250);
    set_servo_position(2,170);
  // Drive Forward 
    motor(1, -60);
    motor(2, -70);
    msleep(2750);
  // Get wooden person
    set_servo_position(1,1450);   
    motor(1,0);
    motor(2,0);
    msleep(500);
  //Grab Person
    set_servo_position(2, 1830);
    msleep(1000);
  //Lift Person
    set_servo_position(1, 350);
    msleep(750);
  //Drive curved
    motor(1,-500);
    motor(2,-100);
    msleep(750);
  //Turn Left
    motor(1, -1000);
    motor (2, -10);
    msleep(500); 
   //Move forward
    motor(1,-550);
    motor(2,-480);
    msleep(5350);
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
