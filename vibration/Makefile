bin = ../bin
inc = ../include
lib = ../lib
src = ../src
man = ../mandata
vib = ../vibration

objects_Aliyun = $(lib)/vibrationAliyun.o $(lib)/systime.o $(lib)/checkrow.o $(lib)/datacharacteric.o $(lib)/savdata.o $(lib)/Crc16.o $(lib)/arrayop.o $(lib)/database.o $(lib)/searchaverage.o $(lib)/searchmax.o $(lib)/searchmin.o

$(bin)/vibrationAliyun: $(objects_Aliyun)
	cc -o $(bin)/vibrationAliyun $(objects_Aliyun) -lmysqlclient -D_REENTRANT -lpthread

$(lib)/vibrationAliyun.o: $(vib)/vibrationAliyun.c $(inc)/systime.h $(inc)/config.h $(inc)/savdata.h $(inc)/checkrow.h $(inc)/datacharacteric.h
	cc -o $(lib)/vibrationAliyun.o -D_REENTRANT -l mysqlclient -lpthread -c $(vib)/vibrationAliyun.c

include $(man)/Makefile

.PHONY: clean
clean:
	rm $(bin)/vibrationAliyun $(objects_Aliyun)
