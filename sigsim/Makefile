inc = ../include
src = ../src
objects = sigsim.o $(src)/arrayop.o $(src)/systime.o

sigsim: $(objects)
	cc -lm -o sigsim $(objects)

sigsim.o: $(inc)/systime.h $(inc)/arrayop.h

include $(src)/Makefile

.PHONY: clean
clean:
	rm sigsim $(objects)
