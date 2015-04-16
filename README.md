Disty
=====

Disty is a [hackEns](http://hackens.org) project aiming at building a low-cost telepresence robot for videoconference.

More infos can be found on the [project page](http://hackens.org/disty).

This repo contains all the drawings and code we used to make it work.


## Build the software

* Checkout this Git repository: `git checkout https://git.eleves.ens.fr/hackens/Disty.git`
* Create a `build` directory in the project root.
* Use CMake to generate Makefiles: `cd build; cmake ..`
* Makethe code: `make`


## Easy test

* Run the program: `cd build; ./disty`.
* The server is now listening for commands. Available commands can be found in `Robot::listen`. These are `FORWARD`, `BACKWARD`, `STOP` and `KILL`.
* You can use `netcat` on the RaspberryPi to send UDP commands to test it: `nc -u localhost 4242`.


## License

All the source code we wrote is under a `no-alcohol beer-ware license`.
```
* --------------------------------------------------------------------------------
* "THE NO-ALCOHOL BEER-WARE LICENSE" (Revision 42):
* Phyks (webmaster@phyks.me) wrote this file. As long as you retain this notice you
* can do whatever you want with this stuff (and you can also do whatever you want
* with this stuff without retaining it, but that's not cool...). If we meet some
* day, and you think this stuff is worth it, you can buy me a <del>beer</del> soda
* in return.
*																		hackEns
* ---------------------------------------------------------------------------------
```
