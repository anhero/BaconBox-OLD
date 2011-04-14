# Michael Aaron Safyan (michaelsafyan@gmail.com). Copyright (C) 2009-2010. Simplified BSD License.

##############################################################
#               CMake Project Wrapper Makefile               #
############################################################## 

SHELL := /bin/bash
RM    := rm -rf

all: ./build/Makefile
	@ $(MAKE) -C build

./build/Makefile:
	@ (cd build >/dev/null 2>&1 && cmake ..)

distclean:
	@- $(RM) ./build
	@- $(RM) ./Makefile

    

ifeq ($(findstring distclean,$(MAKECMDGOALS)),)

	$(MAKECMDGOALS): ./build/Makefile
	@ $(MAKE) -C build $(MAKECMDGOALS)

endif

