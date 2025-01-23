#ifndef PID_H
#define PID_H

class PID {
private:
    double kp;  // Proportional gain
    double ki;  // Integral gain
    double kd;  // Derivative gain

    double prevError;  // Previous error for derivative calculation
    double integral;   // Integral term

    double outputMin;  // Minimum output limit
    double outputMax;  // Maximum output limit

public:
    // Constructor
    PID(double kp, double ki, double kd, double outputMin = -255, double outputMax = 255);

    // Set PID parameters
    void setParameters(double kp, double ki, double kd);

    // Set output limits
    void setOutputLimits(double min, double max);

    // Compute PID output
    double compute(double setpoint, double actual, double dt);
};

#endif
