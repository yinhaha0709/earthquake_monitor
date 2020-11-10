bin = ../bin
lib = ../lib
watchdog = ../watchdog

$(bin)/watchdog: $(watchdog)/watchdog.c
	cc -o $(bin)/watchdog $(watchdog)/watchdog.c

.PHONY: clean
clean:
	rm $(bin)/watchdog
