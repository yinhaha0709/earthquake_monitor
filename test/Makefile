bin = ../bin
inc = ../include
lib = ../lib
test = ../test
src = ../src

targets_test = $(bin)/test_query $(bin)/mqttpub_test $(bin)/mqttsub_test $(bin)/net_test $(bin)/port_test $(bin)/send_port_test_float $(bin)/send_port_test_hex $(bin)/send_port_test_V $(bin)/mqtt_test $(bin)/server_test

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

$(bin)/send_port_test_V: $(inc)/config.h $(inc)/Crc16.h $(inc)/systime.h $(test)/send_port_test.c $(lib)/Crc16.o $(lib)/systime.o
	cc -o $(bin)/send_port_test_V $(test)/send_port_test.c $(lib)/Crc16.o $(lib)/systime.o

$(bin)/send_port_test_hex: $(inc)/config.h $(test)/send_port_test1.c
	cc -o $(bin)/send_port_test_hex $(test)/send_port_test1.c

$(bin)/send_port_test_float: $(inc)/config.h $(inc)/Crc16.h $(inc)/systime.h $(test)/send_port_test2.c $(lib)/Crc16.o $(lib)/systime.o
	cc -o $(bin)/send_port_test_float $(test)/send_port_test2.c $(lib)/Crc16.o $(lib)/systime.o

$(bin)/mqtt_test: $(inc)/config.h $(inc)/registerSend.h $(inc)/mqtt.h $(inc)/cJSON.h $(test)/mqtt_test.c $(lib)/mqtt.o $(lib)/cJSON.o $(lib)/registerSend.o
	cc -o $(bin)/mqtt_test $(test)/mqtt_test.c $(lib)/mqtt.o $(lib)/cJSON.o $(lib)/registerSend.o -lmosquitto

$(bin)/server_test: $(inc)/config.h $(inc)/mqtt.h $(test)/server_test.c $(lib)/mqtt.o
	cc -g -o $(bin)/server_test $(test)/server_test.c $(lib)/mqtt.o -lmosquitto

include ../AliyunSend/Makefile
include ../src/Makefile

.PHONY: clean
clean:
	rm $(targets_test)
