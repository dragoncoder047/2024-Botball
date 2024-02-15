#include <kipr/botball.h>

#define NOODLE_SERVO 1
#define FLAG_SERVO 0

#define SWITCH 0
#define SPACEMAN_BUTTON 9

#define N_CLOSE 1600
#define N_OPEN 200

#define FLAG_UP 1000
#define FLAG_DOWN 10

int flag_state = 0;

int main() {
    enable_servos();
    for (;;) {
        set_servo_position(NOODLE_SERVO, digital(SWITCH) == 0 ? N_OPEN : N_CLOSE);
        if (digital(SPACEMAN_BUTTON)) flag_state = 1;
        if (left_button()) flag_state = 0;
        set_servo_position(FLAG_SERVO, flag_state ? FLAG_UP : FLAG_DOWN);
    }
    return 1;
}
