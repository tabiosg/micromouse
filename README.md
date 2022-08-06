# Micromouse

<img src="https://user-images.githubusercontent.com/71603173/183257361-174de9f3-0ced-4d2f-ab51-1513a5d51f29.jpg" height=400> <img src="https://user-images.githubusercontent.com/71603173/183257370-1f89a8ac-3b1a-450b-acdc-89bb1d2a6e38.jpg" height=400>

For EECS 373, our group decided on making a maze-solving robot project. It served its purpose for our class final presentation, demonstration, and exposition. Created by Abdel, Alan, and Guthrie.

---

## Description

Our Micromouse is a small robot that is able to solve a 4x4 maze autonomously. 

The robot itself has a Zumo robot chassis with a STM32F411RET6 Nucleo board on it to control all the onboard operations. It controls the state machine, inputs, and outputs of the robot. Other devices on the robot include an XBEE module, a custom shield, a servo sensor, and an ultrasonic sound sensor.

To complement the robot, there was a controller module. The controller module allows the user to control the robot wirelessly and manually. It also allows the user to monitor the status of the robot (its current state at any given moment, including its status while solving the maze). The controller includes another Nucleo board with a STM32F411RET6 chip, an XBEE module, a custom keypad, and an LCD graphic display. 

---

## Getting Started

The project first needs to be assembled according to the pinouts below.
The code inside the micromouse directory should be flashed onto the STM32 chip on the robot. The code inside the controller directory should be flashed onto the STM32 chip on the controller.

Extra steps in the code includes configuring the servo angles.

---

## Autonomous Mode Explained

The robot is able to solve a 4x4 maze. With a birds-eye view of the maze, the robot assumes that its start is the South-West corner facing North and its destination is the North-East corner. The servo sensor connects to the ultrasonic sensor which allows it to detect walls on the left, front, and right of the front of the robot.

---

## Movement Explained

The robot drives in tank mode. The speeds of the wheels is determined in the code. The robot is able to detect if it is too close to a wall through the use of its ultrasonic sensor. If it is close to a wall, it adjusts by changing the speeds of each wheel slightly. If it is dangerously close to a wall, it will adjust by moving back safely and moving back forward at a correct angle to center itself.

---

## Robot Pinout

This will be organized in order of the Nucleo board pins (left to right, top to bottom).

- PA15 - Servo PWM
- PA1 - Ultrasonic Echo 
- PB8 - Ultrasonic Trigger
- PB6 - Left H-Bridge PWM
- PB7 - Right H-Bridge PWM
- PA9 - Left H-Bridge Direction
- PA8 - Right H-Bridge Direction
- PC6 - USART TX (connects to XBEE)
- PA12 - USART RX (connects to XBEE)

You will also need to power the connected devices. The H-Bridge pins connect straight to the Zumo with the Arduino headers.

---

## Controller Pinout

- PC0 - Keypad Row 0
- PC1 - Keypad Row 1
- PC2 - Keypad Row 2
- PC3 - Keypad Row 3
- PA8 - Keypad Col 0
- PC7 - Keypad Col 1
- PC8 - Keypad Col 2
- PC9 - Keypad Col 3
- PA2 - USART TX (connects to XBEE)
- PA3 - USART RX (connects to XBEE)
- PB10 - LCD I2C SCL
- PB9 - LCD I2C SDA

---

## XBEE Settings

The XBEE settings transmit at a baud rate of 9600.

---

## Authors

- Abdel
- Alan - [Github](https://github.com/polishdudealan)
- Guthrie - [Github](https://github.com/tabiosg)
