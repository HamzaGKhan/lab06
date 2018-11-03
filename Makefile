CC=gcc
CFLAGS=-lWarn -pedantic

tempSensor:	tempSensor.o libmyifttt.a
	$(CC) tempSensor.o -L. -lwiringPi -lmyifttt -lcurl -o tempSensor

libmyifttt.a:	ifttt.o
	ar -rcs libmyifttt.a ifttt.o

ifttt.o: 	ifttt.c ifttt.h
	$(CC) $(CFLAGS) -c -ansi $<

tempSensor.o:	tempSensor.c ifttt.h
	$(CC) $(CFLAGS) -c -ansi $<

all:	tempSensor

clean:
	rm tempSensor *.o
