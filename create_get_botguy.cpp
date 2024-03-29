#include <kipr/wombat.h>
#include <iostream>

#define light_sensor (analog(1))
#define line_sensor (analog(4))
#define line_on_black (line_sensor > 1000)

#define wait(...) create3_wait()

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
    enable_servos();
    elbow(ELBOW_STOWED);
    claw(CLAW_OPEN);
    wrist(WRIST_STOWED);
}

void wfl() {
    std::cout << "TODO: IMPLEMENT wfl()" << std::endl;
}

int main() {
    create3_connect();
    std::cout << "create3 connect returned" << std::endl;
    setup();
    wfl();
    std::cout << "back in main()" << std::endl;
    //#1 Drive to black line (cliff #2)
    create3_drive_straight(0.92, .25);
    wait();

    // Pull arm out of the way
    elbow(ELBOW_BOTGUY);
    wrist(WRIST_BOTGUY);
    claw(CLAW_OPEN);

    //#2 Rotate left 90d
    sweeper(100);
    create3_rotate_degrees(90,45);
    wait();

    //#3 Drive to base (line sensor) (may want to try line following)
    create3_drive_straight(0.5, .25);
    wait();
    sweeper(0);

    //#4 Get Botguy and Cubes
    std::cout << "Get Botguy and cubes" << std::endl;

    // Close down robot
    create3_wait();
    return 0;
}
