// Encoder based on Andrew Kramer implementation available at http://andrewjkramer.net/pid-motor-control/

#ifndef SpeedControl_h
#define SpeedControl_h

#include"Arduino.h"
#include "Motor.h"
#include "Encoder.h"

class SpeedControl {
	
	public:
		SpeedControl(Motor *motor, Encoder *encoder);
		void setGains(double kP, double kI, double kD);
		void setSpeed(int speed); // in degrees/s
		void setMinSpeed(int minSpeed);
		int getDistance();
		int getSpeed();
		int getOutput();
		void adjustPWM();
 		void resetController();
  		double getITerm();
  		int getPWM();
  		int getSetPoint();

	private:
		int _setPoint, _pwm, _minSpeed, _lastSpeed;
		double _iTerm, _kP, _kI, _kD;
		Motor *_motor;
		Encoder *_encoder;
		void constrainPWM();
	
};

#endif