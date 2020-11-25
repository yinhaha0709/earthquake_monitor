inc = ../include
lib = ../lib
src = ../src

targets_src = $(lib)/database.o $(lib)/arrayop.o $(lib)/systime.o $(lib)/searchmin.o $(lib)/getstatus.o\
	$(lib)/searchmax.o $(lib)/searchaverage.o $(lib)/cJSON.o $(lib)/mqtt.o $(lib)/Crc16.o

all: $(targets_src)

.PHONY: all

$(lib)/database.o: $(src)/database.c $(inc)/config.h $(inc)/database.h
	cc -o $(lib)/database.o -c $(src)/database.c -lmysqlclient

$(lib)/arrayop.o: $(src)/arrayop.c $(inc)/arrayop.h
	cc -o $(lib)/arrayop.o -c $(src)/arrayop.c

$(lib)/systime.o: $(src)/systime.c $(inc)/systime.h
	cc -o $(lib)/systime.o -c $(src)/systime.c

$(lib)/searchmin.o: $(src)/searchmin.c $(inc)/searchmin.h
	cc -o $(lib)/searchmin.o -c $(src)/searchmin.c

$(lib)/searchmax.o: $(src)/searchmax.c $(inc)/searchmax.h
	cc -o $(lib)/searchmax.o -c $(src)/searchmax.c

$(lib)/searchaverage.o: $(src)/searchaverage.c $(inc)/searchaverage.h
	cc -o $(lib)/searchaverage.o -c $(src)/searchaverage.c -lm

$(lib)/cJSON.o:	$(src)/cJSON.c
	cc -o $(lib)/cJSON.o -c $(src)/cJSON.c -lm

$(lib)/mqtt.o: $(src)/mqtt.c $(inc)/config.h $(inc)/mqtt.h $(inc)/cJSON.h $(inc)/database.h
	cc -o $(lib)/mqtt.o -c $(src)/mqtt.c -lmosquitto -lmysqlclient

$(lib)/Crc16.o: $(src)/Crc16.c $(inc)/Crc16.h
	cc -o $(lib)/Crc16.o -c $(src)/Crc16.c

$(lib)/getstatus.o: $(src)/getstatus.c $(inc)/config.h $(inc)/searchmax.h $(inc)/getstatus.h
	cc -o $(lib)/getstatus.o -c $(src)/getstatus.c -lm

.PHONY: clean
clean:
	rm $(targets_src)
