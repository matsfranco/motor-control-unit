// Encoder based on Andrew Kramer implementation available at http://andrewjkramer.net/pid-motor-control/

#include "Arduino.h"
#include "SpeedControl.h"
#include "Motor.h"
#include "Encoder.h"
#define DEFAULT_MIN_SPEED 60
const double defaultGain = 1.0;

SpeedControl::SpeedControl(Motor *motor, Encoder *encoder) {
	_encoder = encoder;
	_motor = motor;
	_iTerm = 0;
	_pwm = 0;
	_lastSpeed = 0;
	_kP = defaultGain;
	_kI = defaultGain;
	_kD = defaultGain;
	_setPoint = 0; // in degrees/second
	_minSpeed = DEFAULT_MIN_SPEED;
}

void SpeedControl::setGains(double kP, double kI, double kD) {
	_kP = kP;
	_kI = kI;
	_kD = kD;
}

double SpeedControl::getITerm() {
  return _iTerm;
}

int SpeedControl::getPWM() {
  return _pwm;
}

int SpeedControl::getSetPoint() {
  return _setPoint;
}

void SpeedControl::setMinSpeed(int minSpeed) {
	_minSpeed = minSpeed;
}

void SpeedControl::setSpeed(int speed) {
	if (speed < 0) {
		_motor->setBack();
		speed *= -1;
	} else if (speed > 0) {
		_motor->setFwd();
	} 
	if (speed == 0) {
		_motor->setFree();
	} 
	if (speed < _minSpeed && speed > 0) {
		speed = _minSpeed;
	}
	_setPoint = speed;
}

int SpeedControl::getDistance() {
	return _encoder->getDistance();
}

int SpeedControl::getSpeed() {
	return _lastSpeed;
}

int SpeedControl::getOutput() {
	return _pwm;
}

void SpeedControl::adjustPWM() {	
	int speed = _encoder->getSpeed(); // motor control returns vector speed
	if(speed < 0) {
        speed *= -1;  // convert speed to scalar
    }
	int error = _setPoint - speed;
	_iTerm += (_kI * (double)error);
	if( _iTerm > 255) {
        _iTerm = 255;
    } else if(_iTerm < 0) {
        _iTerm = 0;
    }
	double dInput = speed - _lastSpeed;
	int adjustment = (_kP * (double)error) + _iTerm - (_kD * dInput);
	_pwm += adjustment;
	if(_pwm > 255) { 
        _pwm = 255;
    } else if(_pwm < 0) {
        _pwm = 0;
    }
	_motor->setPWM(_pwm);
	_lastSpeed = speed;
}

void SpeedControl::resetController() {
  _iTerm = 0;
  _pwm = 0;
  _motor->setPWM(_pwm);
  _lastSpeed = 0;
}