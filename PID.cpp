#include "PID.h"

// Constructor
PID::PID(double kp, double ki, double kd, double outputMin, double outputMax) 
    : kp(kp), ki(ki), kd(kd), prevError(0), integral(0), outputMin(outputMin), outputMax(outputMax) {}

// Set PID parameters
void PID::setParameters(double kp, double ki, double kd) {
    this->kp = kp;
    this->ki = ki;
    this->kd = kd;
}

// Set output limits
void PID::setOutputLimits(double min, double max) {
    outputMin = min;
    outputMax = max;
}

// Compute PID output
double PID::compute(double setpoint, double actual, double dt) {

  
  
    // Calculate error
    double error = setpoint - actual;
    if(error == 0){
      integral = 0;
    }

    // Proportional term
    double proportional = kp * error;

    // Integral term
    integral += error * dt;
    double integralTerm = ki * integral;

    // Derivative term
    double derivative = (error - prevError) / dt;
    double derivativeTerm = kd * derivative;

    // Total output
    double output = proportional + integralTerm + derivativeTerm;

    // Clamp output to set limits
    if (output > outputMax) output = outputMax;
    if (output < outputMin) output = outputMin;

    // Save current error for next iteration
    prevError = error;

    return output;
}
