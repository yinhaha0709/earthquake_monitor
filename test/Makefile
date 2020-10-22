../bin/test_query: ../lib/database.o ../test/test_query.c
	cc -o ../bin/test_query ../lib/database.o ../test/test_query.c -lmysqlclient

include ../src/Makefile

.PHONY: clean
clean:
	rm ../bin/test_query
