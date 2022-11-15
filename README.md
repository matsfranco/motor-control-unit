# motor-control-unit

This projects implements a firmware for Arduino Nano with ATMega328P to control a pair of DC motors
Basically it implements two adjustables PID controllers for precise rotational speed control.
The libraries were developed base on Andrew Kramer library, available at http://andrewjkramer.net/pid-motor-control/

## Next Steps
Actually it is controlled by a set of instructions by Serial Port. But I will develop aditional features like:
- PPM Control, to attach Radiocontrollers
- LiPo Battery voltage and H-Bridge Driver temperature measures
- Automatic Calibration routines
