.POSIX:

include config.mk

all: cfetch cfetch.1

$(BLOCKS:=.o): cfetch.h
logos.o: cfetch.h
util.o: util.h
cfetch.o: cfetch.c cfetch.h config.h logos.h $(BLOCKS:=.h)

config.h: config.def.h
	cat config.def.h > config.h

cfetch: cfetch.o util.o logos.o $(BLOCKS:=.o)
	$(CC) -o $@ $(LDFLAGS) $(BLOCKS:=.o) util.o logos.o cfetch.o

cfetch.1: $(MANUAL)
	scdoc < $(MANUAL) > cfetch.1

clean:
	rm -f cfetch *.o blocks/*.o

.SUFFIXES: .c .o
.c.o:
	$(CC) -o $@ $(CFLAGS) -c $<


