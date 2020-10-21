inc = ../include
lib = ../lib
src = ../src

targets_src = $(lib)/database.o $(lib)/arrayop.o $(lib)/systime.o $(lib)/searchmin.o \
	$(lib)/searchmax.o $(lib)/searchaverage.o

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

.PHONY: clean
clean:
	rm $(targets_src)
