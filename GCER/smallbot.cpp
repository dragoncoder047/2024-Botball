#include <kipr/wombat.h>
#include <iostream>

// Left wheel motor = 3
// Right wheel motor = 1
// Light sensor = 5
// Line sensor = 2
// Arm servo = 0
// Grab servo = 3

#define light_sensor (analog(5))
#define line_sensor (analog(2))
#define On_Black (line_sensor > 600)
#define On_White (line_sensor < 600)
#define LeftWheel (3)
#define RightWheel (1)
#define Arm (0)
#define Claw (3)
#define ArmDown (150)
#define ArmUp (950)
#define ClawOpen (740)
#define ClawClose (0) 
#define Speed (1200)

void slow_servo(int which, int to) {
    int from = get_servo_position(which);
    if (from > to) for (int i = from; i >= to; i--) set_servo_position(which, i), msleep(1);
    else for (int i = from; i <= to; i++) set_servo_position(which, i), msleep(1);
}

void wfl()  {
    int initial = analog(5);
    std::cout << "Wait for light, press B to cancel" << std::endl;
    while (analog(5) > initial / 2) {
        msleep(1);
        if(b_button()) break;
    }
    std::cout << "Start Round!" << std::endl;
}

void move(int lpower, int rpower, int ton, int toff = 0) {
    mav(LeftWheel, lpower);
    mav(RightWheel, rpower);
    msleep(ton);
    mav(LeftWheel, 0);
    mav(RightWheel, 0);
    msleep(toff);
}

void wait_for_milliseconds(int ms) {
    std::cout << "Wait, press A to cancel" << std::endl;
    while (--ms) {
        msleep(1);
        if (a_button()) break;
    }
    std::cout << "Wait Over" << std::endl;
}

int main() {

    printf("Starting\n");
    enable_servos();
    wfl();
    wait_for_milliseconds(14000);
    msleep(1000);
    msleep(500);
    set_servo_position(Arm, ArmUp);
    set_servo_position(Claw, ClawOpen); 
    printf("Light = %d\n",line_sensor);
    msleep(1000);

    //grab 2 people to put in airlock
    mav(LeftWheel,Speed); mav(RightWheel,Speed);
    while(On_White);
    mav(LeftWheel,0); mav(RightWheel,0);
    msleep(1000);
    move(500, 500, 900);
    move(2000, 200, 800, 1000);
    move(600, 600, 800, 1000);
    slow_servo(Arm, ArmDown);
    msleep(1000);
    set_servo_position(3,800);
    msleep(1000);
    slow_servo(Claw,30);
    msleep(1000);
    slow_servo(Arm, ArmUp);
    msleep(1000);
    move(-600, -600, 800, 1000);
    move(-2000, -200, 800);
    move(-500, -500, 900);

    //go to airlock
    move(Speed, Speed, 1500);
    move(150, 1800, 600, 500);
    move(Speed, Speed, 3000);
    move(-1400, -900, 1600);
    move(1800, 600, 1900);
    move(1900, -200, 1000);
    move(-900, -1200, 2500, 500);
    move(200, Speed, 1200);
    move(Speed, Speed, 200, 500);
    set_servo_position(Claw,ClawOpen);
    msleep(500);

    
    // Return to Start Box and square up
    mav(LeftWheel, -Speed); mav(RightWheel, -Speed);
    while (On_White);
    move(Speed, -Speed, 300, 500);
    // Now squared up again
	
 	// Normal get man to put in flag station
    move(Speed, Speed, 500, 550);
    set_servo_position(Claw, ClawOpen); 

    move(1000, -1000, 1000, 2000); // Turn right 30d
    move(Speed, Speed, 45);
    slow_servo(Arm, ArmDown);


    set_servo_position(Claw,ClawClose);
    msleep(1000);
    set_servo_position(Arm, ArmUp);
    msleep(1000);
    move(1200, 250, 800);

    // Go forward 12 sec
    move(1100, 1080, 12000);
    std::cout << "Arrived" << std::endl;
    msleep(1000);

    // Back up a little
    move(-500, -500, 1650);
    std::cout << "Deposit" << std::endl;
    msleep(1000);
    mav(LeftWheel,-50); mav(RightWheel,100);
    msleep(270);

    slow_servo(0,100);
    msleep(1000);

    //Hit the guy on the head
    set_servo_position(Claw, ClawOpen);
    msleep(500);
    move(0, 0, 0, 13);
    set_servo_position(Arm,ArmUp);
    msleep(500);
    set_servo_position(Claw,ClawClose);
    msleep(500);
    set_servo_position(Arm,ArmDown);
    msleep(1000);
    set_servo_position(Claw,ClawOpen);
    msleep(650);
    set_servo_position(Arm,ArmUp);
    msleep(500);
    set_servo_position(Arm,ArmDown);
    msleep(1000);
    set_servo_position(Arm,ArmUp);
    msleep(500);

    //Go to Lava Tube Area
    move(-Speed, -Speed, 1000);
    move(-400, 400, 4500);
    move(400, -400, 2000);
    move(1300, 1000, 3500);
    set_servo_position(Arm,ArmDown); 
    msleep(1500);
    set_servo_position(Arm,0);
    msleep(1000); 
    set_servo_position(Claw,ClawClose);
    msleep(1000);
    set_servo_position(Arm,ArmUp);
    msleep(1000);
    move(-500, -500, 2000);
    move(-50, 500, 2600);
    move(300, 300, 1400);
    set_servo_position(Claw,ClawOpen);
    msleep(500);

    //Go to Lava Tube Area for more
    move(-Speed, -Speed, 300);
    move(400, -400, 2000);
    move(400, 400, 2000, 300);
    set_servo_position(Arm,ArmDown); 
    msleep(1500);
    set_servo_position(Arm,0);
    msleep(1000); 
    set_servo_position(Claw,ClawClose);
    msleep(1000);
    set_servo_position(Arm,ArmUp);
    msleep(1000);
    move(-500, -500, 2000);
    move(-50, 500, 2600);
    move(300, 300, 1400);
    set_servo_position(Claw,ClawOpen);
    msleep(500);

    // Go knock over pool noodle 
    move(-Speed, -Speed, 2000);
    move(-Speed, Speed, 1000);
    move(Speed, Speed, 3000);





    ao();
    disable_servos();
    return 0;
}
