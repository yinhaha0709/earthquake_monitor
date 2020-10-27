#../bin/test_query: ../lib/database.o ../test/test_query.c
#	cc -o ../bin/test_query ../lib/database.o ../test/test_query.c -lmysqlclient
../bin/mqttpub_test: ../include/config.h ../test/mqttpub_test.c
	cc -o ../bin/mqttpub_test ../test/mqttpub_test.c -lmosquitto	

include ../src/Makefile

.PHONY: clean
clean:
#	rm ../bin/test_query
	rm ../bin/mqttpub_test
