#define S1 2  // Leftmost sensor
#define S2 10 // Second sensor from the left
#define S3 4  // Center sensor
#define S4 11 // Second sensor from the right
#define S5 12 // Rightmost sensor

#define M1 6
#define M2 7
#define M3 8
#define M4 9

#define PWM1 3
#define PWM2 5

#include"Motor.h"
#include"PID.h"

int prevS1 = 0;
int prevS5 = 0;


Motor motorLeft(PWM1,M1,M2);
Motor motorRight(PWM2,M3,M4);

PID controlMotorLeft(15,3,0,-50,50);
PID controlMotorRight(15,3,0,-60,60);

long current_time;

void setup() {
  pinMode(S1, INPUT);
  pinMode(S2, INPUT);
  pinMode(S3, INPUT);
  pinMode(S4, INPUT);
  pinMode(S5, INPUT);

  current_time = millis();
  Serial.begin(9600);
}


void loop() {
  int sensor1 = digitalRead(S1);
  int sensor2 = digitalRead(S2);
  int sensor3 = digitalRead(S3);
  int sensor4 = digitalRead(S4);
  int sensor5 = digitalRead(S5);

  Serial.print(sensor1);
  Serial.print(sensor2);
  Serial.print(sensor3);
  Serial.print(sensor4);
  Serial.println(sensor5);
  float actual = sensor1*(-1.5) + sensor2*(-0.5) + sensor3*(0) + sensor4*(0.5) + sensor5*(1.5);
  Serial.print(actual);
  Serial.print("\n");

  // float PWM = float(control.compute(0, actual, (millis() - current_time)/1000.0));

  if(actual > 0.00001 || actual <= -0.00001){
    
    motorLeft.rotate(50 + int(controlMotorLeft.compute(0, actual, (millis() - current_time)/1000.0)));
    motorRight.rotate(60- int(controlMotorRight.compute(0, actual, (millis() - current_time)/1000.0)));
  }else{
    if(sensor3 == 0 && sensor1 == 1 && sensor5 == 1){
    motorLeft.rotate(50);
    motorRight.rotate(60);
    Serial.println("forward");
    }else if(sensor3 == 0 && sensor1 == 0 && sensor5 == 0 && sensor2 == 0 && sensor4 == 0){
    motorLeft.rotate(0);
    motorRight.rotate(0);
    Serial.println("aard");
    }
    else if(sensor3 == 1 && sensor1 == 1 && sensor5 == 1 && sensor2 == 1 && sensor4 == 1){
      if(prevS1 == 0){
      motorLeft.rotate(-50);
      motorRight.rotate(60);
      }else if(prevS5 == 0){
      motorLeft.rotate(50);
      motorRight.rotate(-60);
      }
      Serial.println("aard");
    }
  }

  current_time = millis();
  prevS1 = sensor1;
  prevS5 = sensor5;
  delay(100);
}
