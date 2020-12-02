inc = ../include
lib = ../lib
src = ../src
man = ../mandata
server = ../ServerSend

targets_server = $(lib)/infoinit.o $(lib)/register.o $(lib)/commfeature.o $(lib)/ontime.o $(lib)/event.o

all: $(targets_server)

.PHONY: all

$(lib)/infoinit.o: $(server)/infoinit.c $(inc)/config.h $(inc)/infoinit.h
	cc -o $(lib)/infoinit.o -c $(server)/infoinit.c

$(lib)/register.o: $(server)/register.c $(inc)/config.h $(inc)/mqtt.h $(inc)/register.h
	cc -o $(lib)/register.o -c $(server)/register.c

$(lib)/commfeature.o: $(server)/commfeature.c $(inc)/config.h $(inc)/database.h $(inc)/searchaverage.h $(inc)/searchmax.h $(inc)/searchmin.h $(inc)/getstatus.h $(inc)/systime.h $(inc)/mqtt.h $(inc)/commfeature.h
	cc -o $(lib)/commfeature.o -c $(server)/commfeature.c -D_REENTRANT -lpthread -lmysqlclient

$(lib)/ontime.o: $(server)/ontime.c $(inc)/config.h $(inc)/mqtt.h $(inc)/systime.h $(inc)/ontime.h
	cc -o $(lib)/ontime.o -c $(server)/ontime.c -D_REENTRANT -lpthread

$(lib)/event.o: $(server)/event.c $(inc)/config.h $(inc)/event.h $(inc)/mqtt.h $(inc)/database.h
	cc -o $(lib)/event.o -c $(server)/event.c -D_REENTRANT -lm -lmysqlclient -lpthread

include $(man)/Makefile

.PHONY: clean
clean:
	rm $(targets_server)


