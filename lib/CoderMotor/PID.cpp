#if defined(ARDUINO) && ARDUINO >= 100
	#include "Arduino.h"
#else
	#include "WProgram.h"
#endif

#include "PID.h"

int speed_on_wheels[4];

void set_speed_on_wheels
    (int decision_coefficient, float direction_coefficient, float distance_coefficient) {
    switch (decision_coefficient) {
      case 1: {
        speed_on_wheels[0] = speed_on_wheels[3] = MAX_SPEED * distance_coefficient;
        speed_on_wheels[1] = speed_on_wheels[2] = MAX_SPEED * direction_coefficient * distance_coefficient;
        break;
      }
      case 2: {
        speed_on_wheels[1] = speed_on_wheels[2] = MAX_SPEED * distance_coefficient;
        speed_on_wheels[0] = speed_on_wheels[3] = MAX_SPEED * direction_coefficient * distance_coefficient;
        break;
      }
      default: {
        for (int i = 0; i < 4; ++i) { 
            speed_on_wheels[i] = MAX_SPEED * distance_coefficient;
        }
        break;
      }
    }
    return ;
}

void set_forward_velocity(int expected_pixel, double distance) {
    float distance_coefficient = 0;
    if (distance > DECELERATION_DISTANCE) {
        distance_coefficient = 1; 
    } else if (distance < MIN_DISTANCE) {
        distance_coefficient = 0;
    } else {
        distance_coefficient = (float)distance / DECELERATION_DISTANCE;
    }
    
    float direction_coefficient = 1 - abs(expected_pixel) * corresponding_angle / 45;
    
    int decision_coefficient = 0;
    
    if (expected_pixel > MIN_PIXEL) {
        // turn right 
        decision_coefficient = 1;
    } else if (expected_pixel < -MIN_PIXEL) { 
        // turn left
        decision_coefficient = 2; 
    }
            
    set_speed_on_wheels(decision_coefficient, direction_coefficient, distance_coefficient);
    return ;
}

void set_backward_velocity(int opt) {
    switch (opt) {
      case LEFT_BACK:
        speed_on_wheels[0] = speed_on_wheels[2] = -MAX_SPEED;
        speed_on_wheels[1] = speed_on_wheels[3] = -0.15 * MAX_SPEED;
        break;
      case RIGHT_BACK:
        speed_on_wheels[1] = speed_on_wheels[3] = -MAX_SPEED;
        speed_on_wheels[0] = speed_on_wheels[2] = -0.15 * MAX_SPEED;
        break;
      default: {
        // move backward straight
        for (int i = 0; i < 4; i++) {
            speed_on_wheels[i] = -MAX_SPEED;
        }
        break;
      }
    }
    
    return ;
}

void set_spin_velocity(int opt=0) {
    if (opt & 1) { 
        // spin clockwise 
        speed_on_wheels[0] = speed_on_wheels[3] = MAX_SPEED;
        speed_on_wheels[1] = speed_on_wheels[2] = -MAX_SPEED;

    } else {
        // spin counter-clockwise
        speed_on_wheels[0] = speed_on_wheels[3] = -MAX_SPEED;
        speed_on_wheels[1] = speed_on_wheels[2] = MAX_SPEED;

    }
    return;
}

void set_stop_velocity() {
    for (int i = 0; i < 4; i++) {
        speed_on_wheels[i] = 0;
    }
    return ;
}

