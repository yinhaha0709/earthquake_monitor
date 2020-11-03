#../bin/test_query: ../lib/database.o ../test/test_query.c
#	cc -o ../bin/test_query ../lib/database.o ../test/test_query.c -lmysqlclient
#../bin/mqttpub_test: ../include/config.h ../test/mqttpub_test.c
#	cc -o ../bin/mqttpub_test ../test/mqttpub_test.c -lmosquitto
	
#../bin/mqttsub_test: ../include/config.h ../test/mqttsub_test.c
#	cc -o ../bin/mqttsub_test ../test/mqttsub_test.c -lmosquitto

#../bin/net_test: ../include/config.h ../test/net_test.c
#	cc -o ../bin/net_test ../test/net_test.c

../bin/port_test: ../include/config.h ../test/port_test.c
	cc -o ../bin/port_test ../test/port_test.c

include ../src/Makefile

.PHONY: clean
clean:
#	rm ../bin/test_query
#	rm ../bin/mqttpub_test
#	rm ../bin/mqttsub_test
#	rm ../bin/net_test
	rm ../bin/port_test
