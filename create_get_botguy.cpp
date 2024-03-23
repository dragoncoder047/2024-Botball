#include <kipr/wombat.h>

#define light_sensor (analog(1))
#define line_sensor (analog(4))
#define line_on_black (line_sensor > 1000)

#define pause(...) //create3_wait()

#define elbow(x) slow_servo(2, x)
#define ELBOW_STOWED 0
#define ELBOW_BOTGUY 1520

#define sweeper(x) motor(3, x)

#define claw(x) set_servo_position(3, x)
#define CLAW_OPEN 2047
#define CLAW_CLOSED 0

void slow_servo(int which, int to) {
    int from = get_servo_position(which);
    if (from > to) for (int i = from; i >= to; i--) set_servo_position(which, i), msleep(1);
    else for (int i = from; i <= to; i++) set_servo_position(which, i), msleep(1);
}

int abs(int a) { return a > 0 ? a : -a; }

#define wrist_position (analog(5))
void wrist(int pos) {
    while (abs(wrist_position - pos) > 10) mav(0, 16 * (pos - wrist_position));
    mav(0, 0);
}
#define WRIST_STOWED 4060
#define WRIST_BOTGUY 70

void setup() {
    create3_connect();
    printf("Create3 Connected.\n");
    enable_servos();
    elbow(ELBOW_STOWED);
    claw(CLAW_OPEN);
    wrist(WRIST_STOWED);
}

void wfl() {
    printf("TODO: IMPLEMENT wfl()\n");
    msleep(1000);
    return;
}

int main() {
    setup();
    wfl();
    //#1 Drive to black line (cliff #2)
    double velocity = 0.15;
    create3_velocity_set_components(velocity,0);
    //create3_wait();

    msleep(5000); // Skip over first black line
    while (velocity !=0) {
        if (line_on_black) {
            printf("Black Line 1\n");
            velocity = 0;
        }
        create3_velocity_set_components(velocity,0);
        //create3_wait();
    }
    pause();
	
    // Pull arm out of the way
    elbow(ELBOW_BOTGUY);
    wrist(WRIST_BOTGUY);
    claw(CLAW_CLOSED);

    //#2 Rotate left 90d
    create3_rotate_degrees(90,45);
    create3_wait();
    pause();

    //#3 Drive to base (line sensor) (may want to try line following)
    sweeper(100);
    velocity = 0.15;
    create3_velocity_set_components(velocity,0);
    //create3_wait();
    msleep(5000); // Skip over first black line
    while (velocity !=0) {
        if (line_on_black) {
            printf("Black Line 2\n");
            velocity = 0;
        }
        create3_velocity_set_components(velocity,0);
        //create3_wait();
    }
    sweeper(0);
    pause();

    //#4 Get Botguy and Cubes
    printf("Get Botguy and cubes\n");
    pause();

    // Close down robot
    ao();
    disable_servos();
    create3_wait();
    printf("done");
    return 0;
}
