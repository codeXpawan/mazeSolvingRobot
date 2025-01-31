#define S1 A0  
#define S2 A1 
#define S3 A2 
#define S4 A3 
#define S5 A4 
#define S6 A5 
#define S7 A6
#define S8 A7
 


#define M1 5
#define M2 4
#define M3 7
#define M4 6

#define PWM1 9
#define PWM2 10

#define buttonPin 13

#include"Motor.h"
#include"PID.h"
#include"Stack.h"
#define THRESHOLD 750



Motor motorLeft(PWM1,M1,M2);
Motor motorRight(PWM2,M3,M4);

PID controlMotorLeft(40,5,0,-50,50);
PID controlMotorRight(50,5,0,-60,60);

long current_time;

Stack turns;

float error;
bool status = false;

void setup() {
  pinMode(S1, INPUT);
  pinMode(S2, INPUT);
  pinMode(S3, INPUT);
  pinMode(S4, INPUT);
  pinMode(S5, INPUT);
  pinMode(S6, INPUT);
  pinMode(S7, INPUT);
  pinMode(S8, INPUT);

  pinMode(buttonPin, INPUT_PULLUP);

  current_time = millis();
  Serial.begin(9600);
}


void loop() {
  // while (digitalRead(buttonPin)) { 
  //   readSensors();
  // }
  
  mazeSolve(); // First pass to solve the maze
  while (digitalRead(buttonPin)) { }
  
}


void mazeSolve(void)
{
    while (!status)
    {
      int mode = readSensors();
      Serial.print("mode: ");
      Serial.print(mode);
      switch (mode)
      {   
        case 0:  
        Serial.print("Case 0");
          motorStop();
          goAndTurn ('L');
          turns.push('B');
          break;
        
        case 1: 
        Serial.print("Case 1");
          runExtraInch();
          mode = readSensors();
          if (mode != 1) {
            goAndTurn ('L'); 
            turns.push('L');
          } // or it is a "T" or "Cross"). In both cases, goes to 'L'
          else mazeEnd(); 
          break;
          
        case 2: 
        Serial.print("Case 2");
          runExtraInch();
          mode = readSensors();
          if (mode == 0) {goAndTurn ('R'); turns.push('R');}
          else turns.push('S');
          break;   
          
        case 3: 
        Serial.print("Case 3");
        runExtraInch();
          goAndTurn ('L'); 
          turns.push('L');
          break;   
        
        case 4: 
        Serial.print("Case 4");
          followingLine();
          break;      
      
      }
      current_time = millis();
      delay(50);
    }
}

int readSensors(){
  int sensor1 = analogRead(S1) > THRESHOLD ? 1 : 0;
  int sensor3 = analogRead(S3) > THRESHOLD ? 1 : 0;
  int sensor2 = analogRead(S2) > THRESHOLD ? 1 : 0;
  int sensor4 = analogRead(S4) > THRESHOLD ? 1 : 0;
  int sensor5 = analogRead(S5) > THRESHOLD ? 1 : 0;
  int sensor6 = analogRead(S6) > THRESHOLD ? 1 : 0;
  int sensor7 = analogRead(S7) > THRESHOLD ? 1 : 0;
  int sensor8 = analogRead(S8) > THRESHOLD ? 1 : 0;
  Serial.print(sensor1);
  Serial.print(" ");
  Serial.print(sensor2);
  Serial.print(" ");
  Serial.print(sensor3);
  Serial.print(" ");
  Serial.print(sensor4);
  Serial.print(" ");
  Serial.print(sensor5);
  Serial.print(" ");
  Serial.print(analogRead(S5));
  Serial.print(" ");
  Serial.print(sensor6);
  Serial.print(" ");
  Serial.print(sensor7);
  Serial.print(" ");
  Serial.println(sensor8);
  error =  sensor2*(-1) + sensor3*(-0.5) + sensor4*(0) + sensor5*(0) + sensor6*(0.5) + sensor7*(1);
  if(sensor2 == 1 && sensor3 == 1 && sensor4 == 1 && sensor5 == 1 && sensor6 == 1 && sensor7 == 1){
    return 0; //No Line
  }
  if(sensor2== 0 && sensor3 == 0 && sensor4 == 0 && sensor5 == 0 && sensor6 == 0 && sensor7 == 0){
    return 1; //Continue line
  }
  if(sensor8 == 0 && sensor7 == 0 && sensor1 == 1){
    return 2; //Right turn
  }
  if(sensor1 == 0 && sensor2 == 0 && sensor8 == 1){
    return 3; //Left turn
  }
  return 4;
}

void followingLine(){
  Serial.print("left pid ");
  Serial.print(int(controlMotorLeft.compute(0, error, (millis() - current_time)/1000.0)));
  Serial.print(" ");
  motorLeft.rotate(50 + int(controlMotorLeft.compute(0, error, (millis() - current_time)/1000.0)));
  motorRight.rotate(60 - int(controlMotorRight.compute(0, error, (millis() - current_time)/1000.0)));
}

void runExtraInch(){
  motorStop();
  Serial.print("run extra");
  motorLeft.rotate(60);
  motorRight.rotate(60);
  delay(500);
  motorStop();
}

void goAndTurn(char dir){
    Serial.print(dir);
  if(dir == 'L'){
    Serial.print("Turning Left ");
    while(digitalRead(S3) != 0 && digitalRead(S4) != 0){
      motorLeft.rotate(-60);
      motorRight.rotate(50);
      delay(100);
    }
  }else if( dir == 'R'){
    Serial.print("Turning Right ");
    while(digitalRead(S6) != 0 && digitalRead(S5) != 0){
      motorLeft.rotate(60);
      motorRight.rotate(-50);
      delay(100);
    }
  }
  motorStop();
}

void motorStop(){
  Serial.print("Stop");
  motorLeft.rotate(0);
  motorRight.rotate(0);
  delay(1000);
}

void mazeEnd(){
  motorStop();
  Serial.print("Maze End");
  status = true;
}
