Robotic Labyrinth Game

Code to enable a microcontroller to play the game Labyrinth, using servo motors to rotate the playing board and move the marble through the maze while avoiding obstacles.

The project has two parts: model and gnc.

The model contains a simulation of the dynamics, actuators, and sensors. It is mainly used to test the embedded software and control algorithms. It may additionally be used by the controller in model-based control architectures.

The gnc section contains the actual embedded software running on the microcontroller. It process sensor data, computes an output command, and drives the servo motors.
