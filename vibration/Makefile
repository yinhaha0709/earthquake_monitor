bin = ../bin
inc = ../include
lib = ../lib
src = ../src
man = ../mandata
vib = ../vibration
aliyun = ../AliyunSend
server = ../ServerSend

objects_Aliyun = $(lib)/vibrationAliyun.o $(lib)/systime.o $(lib)/checkrow.o $(lib)/datacharacteric.o $(lib)/savdata.o $(lib)/Crc16.o $(lib)/arrayop.o $(lib)/database.o $(lib)/searchaverage.o $(lib)/searchmax.o $(lib)/searchmin.o $(lib)/ontimeSend.o $(lib)/cJSON.o $(lib)/mqtt.o $(lib)/registerSend.o $(lib)/generalSend.o

objects_Server = $(lib)/vibration.o $(lib)/systime.o $(lib)/rowchange.o $(lib)/sigsave.o $(lib)/commfeature.o $(lib)/Crc16.o $(lib)/arrayop.o $(lib)/database.o $(lib)/searchaverage.o $(lib)/searchmax.o $(lib)/searchmin.o $(lib)/getstatus.o $(lib)/mqtt.o $(lib)/infoinit.o $(lib)/register.o $(lib)/cJSON.o $(lib)/idchange.o

target_vibration = $(bin)/vibrationAliyun $(bin)/vibration

all: $(target_vibration)

.PHONY: all

$(bin)/vibrationAliyun: $(objects_Aliyun)
	cc -o $(bin)/vibrationAliyun $(objects_Aliyun) -lmysqlclient -D_REENTRANT -lpthread -lm -lmosquitto

$(bin)/vibration: $(objects_Server)
	cc -o $(bin)/vibration $(objects_Server) -lmysqlclient -D_REENTRANT -lpthread -lm -lmosquitto

$(lib)/vibrationAliyun.o: $(vib)/vibrationAliyun.c $(inc)/systime.h $(inc)/config.h $(inc)/savdata.h $(inc)/checkrow.h $(inc)/datacharacteric.h $(inc)/mqtt.h $(inc)/Crc16.h $(inc)/registerSend.h $(inc)/ontimeSend.h
	cc -o $(lib)/vibrationAliyun.o -D_REENTRANT -lmysqlclient -lpthread -c $(vib)/vibrationAliyun.c

$(lib)/vibration.o: $(vib)/vibration.c $(inc)/config.h $(inc)/systime.h $(inc)/sigsave.h $(inc)/rowchange.h $(inc)/commfeature.h $(inc)/mqtt.h $(inc)/Crc16.h $(inc)/infoinit.h $(inc)/register.h $(inc)/idchange.h
	cc -o $(lib)/vibration.o -D_REENTRANT -lmysqlclient -lpthread -c $(vib)/vibration.c

include $(aliyun)/Makefile

include $(server)/Makefile

include $(man)/Makefile

.PHONY: clean
clean:
	rm $(bin)/vibrationAliyun $(objects_Aliyun) $(bin)/vibration $(objects_Server)
