Main Disty program
==================

This is the main program to handle Disty moves and control.

## Build the software

To build this software, you will need to have [WiringPi](http://wiringpi.com/)
installed system-wide. To use Disty, you will have to have support for GPIOs.

* Create a `build` directory.
* Use CMake to generate Makefiles: `cd build; cmake ..`
* Make: `make`

If you want to tweak the behaviour of the program (such as the used GPIOs),
just edit the `headers/constants.hpp` file.


## Easy test

* Run the program: `cd build; sudo ./disty` (you need to run it as root for PWM
  and GPIO access).
* The server is now listening for commands. Available commands can be found in
  `Robot::listen`. These are `FORWARD`, `BACKWARD`, `STOP` and `KILL`.
* You can use `netcat` on the RaspberryPi to send UDP commands to test it:
  `nc -u localhost 4242`.

## Run the program and control with the webview

Just run the program with `cd build; sudo ./disty` and let it run.
