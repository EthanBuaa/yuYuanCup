#ifndef CODER_H_
#define CODER_H_

#if defined(ARDUINO) && ARDUINO >= 100
	#include "Arduino.h"
#else
	#include "WProgram.h"
#endif

#define LONG_MAX (4294967295) 

// look at here ===>
// need to adjust this macro 
// -----------------------------------------------
#define VELOCITY_SCALE_VALUE (20)
// -----------------------------------------------
// look at here ==>

class Coder {
private:
    // coder_VCC and coder_GND are two coder pins that supply power
	// the coder_GND pin (coder_GND_) connect the the GND of arduino 
	
	// positive_pin and negative_pin are two pins that supply the coder output
	int positive_pin_;
	int negative_pin_;

	// pulseCount record the number of pulses during the interval from last_time_us_ to cur_time_us_
	// if pulse_count > 0, the motor is running forward 
	// else, the motor move backwards
	volatile long *pulse_count_ptr_;

	// intialize time_last_micros_ to 0
	unsigned long time_last_millis_ = 0;

    unsigned long static getChange(long current, long previous) {
		// Overflow has occured
		if (current < previous) {
			return LONG_MAX - previous + current;
		}
		// No overflow
		return current - previous;
	}

public:
    Coder();
    Coder(int VCC_pin, int positive_pin, int negative_pin, volatile long *pulse_count_ptr);
    double getCurrentVelocity();
};

#endif

