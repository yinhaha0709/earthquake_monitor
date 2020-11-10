bin = ../bin
inc = ../include
lib = ../lib
test = ../test
src = ../src

targets_test = $(bin)/test_query $(bin)/mqttpub_test $(bin)/mqttsub_test $(bin)/net_test $(bin)/port_test $(bin)/send_port_test $(bin)/send_port_test1

all: $(targets_test)

.PHONY: all

$(bin)/test_query: $(lib)/database.o $(test)/test_query.c
	cc -o $(bin)/test_query $(lib)/database.o $(test)/test_query.c -lmysqlclient

$(bin)/mqttpub_test: $(inc)/config.h $(test)/mqttpub_test.c
	cc -o $(bin)/mqttpub_test $(test)/mqttpub_test.c -lmosquitto
	
$(bin)/mqttsub_test: $(inc)/config.h $(test)/mqttsub_test.c
	cc -o $(bin)/mqttsub_test $(test)/mqttsub_test.c -lmosquitto

$(bin)/net_test: $(inc)/config.h $(test)/net_test.c
	cc -o $(bin)/net_test $(test)/net_test.c

$(bin)/port_test: $(inc)/config.h $(test)/port_test.c $(lib)/Crc16.o
	cc -o $(bin)/port_test $(test)/port_test.c $(lib)/Crc16.o

$(bin)/send_port_test: $(inc)/config.h $(inc)/Crc16.h $(inc)/systime.h $(test)/send_port_test.c $(lib)/Crc16.o $(lib)/systime.o
	cc -o $(bin)/send_port_test $(test)/send_port_test.c $(lib)/Crc16.o $(lib)/systime.o

$(bin)/send_port_test1: $(inc)/config.h $(test)/send_port_test1.c
	cc -o $(bin)/send_port_test1 $(test)/send_port_test1.c

include ../src/Makefile

.PHONY: clean
clean:
	rm $(targets_test)
