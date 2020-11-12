inc = ../include
lib = ../lib
src = ../src
aliyun = ../AliyunSend

targets_Aliyun = $(lib)/registerSend.o $(lib)/ontimeSend.o $(lib)/generalSend.o

all: $(targets_Aliyun)

.PHONY: all

$(lib)/registerSend.o: $(aliyun)/registerSend.c $(inc)/config.h $(inc)/registerSend.h $(inc)/mqtt.h $(inc)/cJSON.h
	cc -o $(lib)/registerSend.o -c $(aliyun)/registerSend.c

$(lib)/ontimeSend.o: $(inc)/config.h $(inc)/mqtt.h $(inc)/cJSON.h $(inc)/ontimeSend.h $(aliyun)/ontimeSend.c
	cc -o $(lib)/ontimeSend.o -c $(aliyun)/ontimeSend.c

$(lib)/generalSend.o: $(inc)/config.h $(inc)/mqtt.h $(inc)/cJSON.h $(inc)/generalSend.h $(aliyun)/generalSend.c
	cc -o $(lib)/generalSend.o -c $(aliyun)/generalSend.c

include ../src/Makefile

.PHONY: clean
clean:
	rm $(targets_Aliyun)
