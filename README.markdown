The RedBox engine 
=================
*Version: Development snapshot*

What is the RedBox Engine?
--------------------------
The RedBox Engine is a 2D engine designed to run on every major platform. RedBox 
was greatly inspired by the well known Flixel and Unity engines. The goal was to 
mix the cool stuff the popular engines had and smooth out some of the rough 
edges. There is still more to come for this engine; it is still in its infancy.

More detailed informations are available on 
[the RedBox Engine website](http://redboxengine.com/).

Getting help
============
For any help, you can go to [the website](http://redboxengine.com), which is
the documentation website or you can use [our forums](http://anhero.net/forum/)
and make your mark in the community.

When you find a bug with our engine or anything we do, you should post a bug
report on [our bug tracker](http://bugs.anhero.net/).

License informations
======================
For license details about RedBox, see the wiki or the license.txt file.

More details
============

How to use
----------
The RedBox engine is a library that is compiled and then used as the framework 
for game development. You might need to lookt at a RedBoxApp project to know more
about how to use this.

This project is more aimed at the porters, builders and hackers of The RedBox
Engine.

Project structure
-----------------
	CMake/                ->  Contains files needed by CMake.
		configureScript/  ->  Contains special configure scripts called by the
		                      main configure script depending on the passed 
		                      arguments
		module/           ->  Contains custom modules for CMake
		toolchain/        ->  Contains custom CMake toolchains
	ide/                  ->  Static IDE projects.
	libraries/            ->  The dependencies for The RedBox Engine are there,
	                          They are built using libbuildtool.
	meta/                 ->  The Doxygen config file and the generated 
	                          documentation goes right there
	RedBox/               ->  The RedBox Engine sources
	CMakeLists.txt        ->  Main Cmake script
	configure             ->  Main configure script, it calls cmake with the 
	                          right arguments depending on the passed arguments
