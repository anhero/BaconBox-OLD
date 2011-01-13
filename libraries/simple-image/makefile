#Makefile for simple-image
#

OBJS = simple-image.o \
	simple-image-png.o


libsimple-image.a : $(OBJS)
	ar -rfs libsimple-image.a simple-image.o simple-image-png.o
	@echo :: $@ generation complete



$(OBJS) : %.o : %.c
	g++ -o $@ -c $<
	@echo :: $< compiled as $@

.PHONY: clean

clean : 
	-rm -f libsimple-image.a
	-rm -f $(OBJS)
	@echo :: cleaned
