# Maze Solving Robot

## Project Description
This project is the result of Maze Quest organized by Robotics Club, Purwanchal Campus. The robot is able to solve the maze using **Left Hand Rule**. 

## Features
- Autonomous line-following
- Maze mapping and shortest path calculation
- Real-time decision-making

## Hardware
- Arduino UNO / Mega
- IR Sensor Array (for line tracking)
- Motor Driver (L298N or similar)
- DC Motors 
- Chassis and Wheels
- Battery Pack

## Software & Algorithm
- Arduino C++
- Wall Follower Algorithm
- PID Control for precise movement

## Working Process
1. Follows a black line in a maze using IR sensors
2. Detects junctions (T, L, Cross) and records paths
3. Solves the maze
4. Once it reaches the goal, retraces the shortest path

## Setup

1. Clone the repository
2. Upload the code to Arduino
3. Assemble the robot and connect sensors/motors
4. Place on maze and power it up

