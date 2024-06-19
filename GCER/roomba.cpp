#include <kipr/wombat.h>
#include <iostream>

#define light_sensor (analog(1))
#define line_sensor (analog(4))
#define line_on_black (line_sensor > 1000)

void wait() {
    try { create3_wait(); }
    catch (std::exception& exc) { (void)exc; }
}

#define elbow(x) slow_servo(2, x)
#define ELBOW_STOWED 0
#define ELBOW_BOTGUY 1175
#define ELBOW_DOWN 2047

#define claw(x) set_servo_position(3, x)
#define CLAW_OPEN 0
#define CLAW_CLOSED 790

#define sweeper_on() motor_power(2, 100)
#define sweeper_off() mav(2, 0)
void sweeper_home() {
    sweeper_on();
    while (!digital(9));
    msleep(200);
    sweeper_off();
}

#define switcher(x) set_servo_position(0, x)
#define SWITCHER_DOWN 2047
#define SWITCHER_UP 0
#define SWITCHER_NOPIPE 1300

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
#define WRIST_BOTGUY 10
#define WRIST_DOWN 10

void create3_run_into_wall() {
    for (int i = 0; create3_sensor_bump(i) == 0; i = (i + 1) % 5) {
        create3_velocity_set_components(0.5, 0);
    }
    create3_velocity_set_components(0, 0);
    create3_execute_next_command_post_haste();
    wait();
}

void setup() {
    enable_servos();
    elbow(ELBOW_STOWED);
    claw(CLAW_OPEN);
    wrist(WRIST_STOWED);
    mav(0, 1500);
    msleep(400);
    mav(0, 0);
    switcher(SWITCHER_DOWN);
    msleep(400);
    sweeper_home();
    create3_connect();
}

void wfl() {
    int start = analog(0);
    std::cout << "Wait for light, press b to bypass" << std::endl;
    while (analog(0) > start / 2) {
        msleep(1);
        if (b_button()) break;
    }
    std::cout << "Start Game!" << std::endl;
}

void grab() {
    wrist(WRIST_BOTGUY);
    mav(0, -1500);
    msleep(500);
    mav(0, 0);
    elbow(ELBOW_BOTGUY+100);
    claw(CLAW_CLOSED);
}

void pause() {
    std::cout << "Wait for other robot to pass, press b to bypass" << std::endl;
    for (int i = 0; i < 10000; i++) {
        msleep(1);
        if (b_button()) break;
    }
    std::cout << "Wait Over" << std::endl;
}

int main() {
    setup();
    wfl();
    std::cout << "back in main()" << std::endl;
    //#1 Drive to black line (cliff #2)
    create3_drive_straight(0.96, .5);
    wait();

    // Pull arm out of the way
    elbow(ELBOW_BOTGUY);
    claw(CLAW_OPEN);

    //#2 Rotate left 90d
    create3_rotate_degrees(90,45);
    wait();

    //#3 Drive to base and sweep
    sweeper_on();
    create3_drive_straight(0.45, .2);
    wait();
    sweeper_home();
    switcher(SWITCHER_NOPIPE);
    create3_run_into_wall();
    wait();

    //#4 Get Botguy and Cubes
    std::cout << "Get Botguy and cubes" << std::endl;
	
    grab();
    msleep(1000);
    elbow(ELBOW_STOWED);

    // Turn to drop Botguy
    create3_drive_straight(-0.1, 0.2);
    wait();
    int turnamt = 40;
    create3_rotate_degrees(turnamt,45);
    wait();
    claw(CLAW_OPEN);
    msleep(1000);
    create3_rotate_degrees(-turnamt,45);
    wait();

    // Go back to get cube
    create3_drive_straight(0.1, 0.2);
    create3_run_into_wall();
    wait();
    create3_rotate_degrees(-10, 45);
    wait();
    pause();

    // Grab yellow cube and hit switch
    wrist(WRIST_STOWED);
    elbow(ELBOW_BOTGUY);
    grab();
    switcher(SWITCHER_UP);
    msleep(1000);
    // Back and turn to get the second cube
    create3_drive_straight(-0.08, 0.2);
    wait();
    create3_rotate_degrees(-10, 45);
    wait();
    
    // Back up to drag cube
    create3_drive_straight(-0.25, 0.2);
    // Turn
    create3_rotate_degrees(60, 45);
    wait();
    // Let go
    elbow(ELBOW_DOWN);
    wrist(WRIST_DOWN);
    claw(CLAW_OPEN);
    msleep(1000);

    // Close down robot
    create3_wait();
    return 0;
}
