RedBox engine 

For any help:
http://redboxengine.com (Documentation / wiki)
http://anhero.net/forum/ (Forum)

If you find a bug:
http://bugs.anhero.net/ (bug tracker)

For license detail see the wiki or license.txt


Project structure:
- CMake/ 				(Contain CMake needed files)
	configureScript/	(Contain special configure script called by the main configure script depending on the passed arguments)
	module/				(Contain custom modules for CMake)
	toolchain/			(Contain CMake custom toolchain)
- ide/ 					(ide projects, we are implementing CMake to generate those project automaticly, so we won't need this folder in the near future)
- libraries/ 			(put your needed libraries there, it should at least contain the redbox engine)
- meta/					(Doxygen config file and generated documentation goes right there)
- RedBox/				(RedBox engine sources)
- CMakeList.txt			(Main Cmake script)
- configure				(Main configure script, it call cmake with the needed arguments depending on the passed arguments)
