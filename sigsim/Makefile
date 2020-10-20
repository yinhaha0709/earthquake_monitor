bin = ../bin
inc = ../include
lib = ../lib
src = ../src
man = ../mandata
sim = ../sigsim

objects_sim = $(lib)/sigsim.o $(lib)/arrayop.o $(lib)/systime.o $(lib)/checkrow.o $(lib)/database.o \
	$(lib)/datacharacteric.o $(lib)/savdata.o $(lib)/searchaverage.o $(lib)/searchmax.o $(lib)/searchmin.o

$(bin)/sigsim: $(objects_sim)
	cc -o $(bin)/sigsim $(objects_sim) -lmysqlclient -D_REENTRANT -lpthread 

$(lib)/sigsim.o: $(inc)/systime.h $(inc)/arrayop.h $(inc)/config.h $(inc)/database.h \
			$(inc)/savdata.h $(inc)/checkrow.h $(inc)/datacharacteric.h
	cc -o $(lib)/sigsim.o -D_REENTRANT -lmysqlclient -lpthread -c sigsim.c

include $(man)/Makefile

.PHONY: clean
clean:
	rm $(bin)/sigsim $(objects_sim)
