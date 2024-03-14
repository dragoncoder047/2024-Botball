#include <kipr/wombat.h>

#define light_sensor (analog(4))

#define elbow(x) slow_servo(2, x)
#define ELBOW_STOWED 0
#define ELBOW_BOTGUY 1520

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
#define WRIST_STOWED 4080
#define WRIST_BOTGUY 70

void setup() {
    enable_servos();
    elbow(ELBOW_STOWED);
    claw(CLAW_OPEN);
    wrist(WRIST_STOWED);
}

void wfl() {
    printf("TODO: IMPLEMENT wfl()\n");
    return;
}

int main() {
    setup();
    wfl();
    printf("blooey!\n");
    elbow(ELBOW_BOTGUY);
    wrist(WRIST_BOTGUY);
    claw(CLAW_CLOSED);
    return 1;
}
