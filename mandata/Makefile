inc = ../include
lib = ../lib
src = ../src
man = ../mandata

targets_man = $(lib)/checkrow.o $(lib)/datacharacteric.o $(lib)/eqintensity.o $(lib)/savdata.o

all: $(targets_man)

.PHONY: all

include $(src)/Makefile

$(lib)/checkrow.o: $(man)/checkrow.c $(inc)/config.h $(inc)/checkrow.h $(inc)/database.h
	cc -o $(lib)/checkrow.o -c $(man)/checkrow.c -D_REENTRANT -lpthread -lmysqlclient

$(lib)/datacharacteric.o: $(man)/datacharacteric.c $(inc)/config.h $(inc)/database.h $(inc)/searchmin.h \
			$(inc)/searchmax.h $(inc)/searchaverage.h $(inc)/datacharacteric.h $(inc)/systime.h
	cc -o $(lib)/datacharacteric.o -c $(man)/datacharacteric.c -lmysqlclient

$(lib)/eqintensity.o: $(man)/eqintensity.c $(inc)/eqintensity.h
	cc -o $(lib)/eqintensity.o -c $(man)/eqintensity.c

$(lib)/savdata.o: $(man)/savdata.c $(inc)/config.h $(inc)/savdata.h $(inc)/database.h $(inc)/systime.h $(inc)/arrayop.h
	cc -o $(lib)/savdata.o -c $(man)/savdata.c -lmysqlclient -lpthread

.PHONY: clean
clean:
	rm $(targets_man)
