inc = ../include
lib = ../lib
src = ../src
man = ../mandata

targets_man = $(lib)/checkrow.o $(lib)/datacharacteric.o $(lib)/eqintensity.o $(lib)/savdata.o $(lib)/stationreg.o $(lib)/rowchange.o $(lib)/sigsave.o $(lib)/idchange.o

all: $(targets_man)

.PHONY: all

include $(src)/Makefile

$(lib)/checkrow.o: $(man)/checkrow.c $(inc)/config.h $(inc)/checkrow.h $(inc)/database.h
	cc -o $(lib)/checkrow.o -c $(man)/checkrow.c -D_REENTRANT -lpthread -lmysqlclient

$(lib)/datacharacteric.o: $(man)/datacharacteric.c $(inc)/config.h $(inc)/database.h $(inc)/searchmin.h \
			$(inc)/searchmax.h $(inc)/searchaverage.h $(inc)/datacharacteric.h $(inc)/systime.h $(inc)/generalSend.h
	cc -o $(lib)/datacharacteric.o -c $(man)/datacharacteric.c -lmysqlclient -D_REENTRANT -lpthread

$(lib)/eqintensity.o: $(man)/eqintensity.c $(inc)/eqintensity.h
	cc -o $(lib)/eqintensity.o -c $(man)/eqintensity.c

$(lib)/savdata.o: $(man)/savdata.c $(inc)/config.h $(inc)/savdata.h $(inc)/database.h $(inc)/systime.h $(inc)/arrayop.h
	cc -o $(lib)/savdata.o -c $(man)/savdata.c -lmysqlclient -lpthread

$(lib)/stationreg.o: $(man)/stationreg.c $(inc)/config.h $(inc)/stationreg.h $(inc)/mqtt.h
	cc -o $(lib)/stationreg.o -c $(man)/stationreg.c

$(lib)/rowchange.o: $(man)/rowchange.c $(inc)/config.h $(inc)/database.h $(inc)/systime.h $(inc)/rowchange.h
	cc -o $(lib)/rowchange.o -c $(man)/rowchange.c -D_REENTRANT -lpthread -lmysqlclient

$(lib)/sigsave.o: $(man)/sigsave.c $(inc)/config.h $(inc)/sigsave.h $(inc)/database.h $(inc)/systime.h $(inc)/arrayop.h
	cc -o $(lib)/sigsave.o -c $(man)/sigsave.c -lmysqlclient -lpthread

$(lib)/idchange.o: $(man)/idchange.c $(inc)/config.h $(inc)/database.h $(inc)/systime.h $(inc)/idchange.h
	cc -o $(lib)/idchange.o -c $(man)/idchange.c -lmysqlclient -lpthread

.PHONY: clean
clean:
	rm $(targets_man)
