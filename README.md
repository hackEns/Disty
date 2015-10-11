Disty
=====

Disty is a [hackEns](http://hackens.org) project by [Phyks](http://phyks.me)
and [Elie](http://exppad.com/) aiming at building a low-cost telepresence robot
for videoconference.

More infos can be found on the [project page](http://hackens.org/disty) (in
French). The README and the source code is another good source of
documentation, which should be self-explanatory, in English.

This repo contains all the drawings and code we used to make it work.

![Screen capture](https://raw.githubusercontent.com/hackEns/Disty/master/doc/screenshot.png)

<hr/>

![3D model](https://raw.githubusercontent.com/hackEns/Disty/master/doc/3Dmodel.png)

<hr/>

![Disty](http://pub.hackens.org/images/disty/disty1.jpg)

![Disty](http://pub.hackens.org/images/disty/disty2.jpg)

![Disty](http://pub.hackens.org/images/disty/disty3.jpg)



## Content of this repo

* `blueprints` contains all the blueprints and drawings for this project.
* `disty` contains the main C++ code, responsible for handling Disty movements
and basic operations.
* `webview` contains the code for the webview, which is the web interface used
to control Disty and display camera (for the remote user).

Note that these folders also contain useful READMEs with more detailed
information on them.

Blueprints are either in `eps` (ready to cut files) or `svg` (working files).
These should be the same and both are provided only to ease usage and
modifications. STL files are ready to print files. They should be included in
the Blender blend files, for easy modifications.

You should laser cut the `top` and `bottom` files for the two main plates.
You should 3D print:
* the `picam_case_*` files for the camera case (licensed under CC BY SA).
* `teleprez.blend` is the complete CAO model of the robot in Blender.
* `camera_servo_holder.stl` is the plastic part to hold the camera servo. You
need to print it once.
* `wheel_servo_holder.stl` is the plastic part to hold the servos for the
wheels. You need four of them.


## Wiring

![Wiring](https://raw.githubusercontent.com/hackEns/Disty/master/doc/gpio.png)


## License

All the source code we wrote is under a beer-ware license, under otherwise specified.

    * --------------------------------------------------------------------------------
    * "THE BEER-WARE LICENSE" (Revision 42):
    * Phyks and Élie wrote this file. As long as you retain this notice you
    * can do whatever you want with this stuff (and you can also do whatever you want
    * with this stuff without retaining it, but that's not cool...). If we meet some
    * day, and you think this stuff is worth it, you can buy us a beer
    * in return.
    *                                                                       hackEns
    * ---------------------------------------------------------------------------------

If you need a more legally valid license, you can consider Disty to be under an MIT license.


## Credits

Thanks https://api.youmagine.com/designs/raspberry-pi-snap-together-camera-case for the camera case (CC BY SA license).
