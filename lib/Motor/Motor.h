// Encoder based on Andrew Kramer implementation available at http://andrewjkramer.net/pid-motor-control/

#ifndef Motor_h
#define Motor_h

#include "Arduino.h"

class Motor
{
public:
	Motor(int dir1, int dir2, int pwm);
	void setFwd();
	void setBack();
	void setFree();
	void setStop();
	void setPWM(int level);
private:
	int _dir1, _dir2, _pwm;
};

#endif