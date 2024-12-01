.POSIX:

include config.mk

all: cfetch cfetch.1

$(BLOCKS:=.o): cfetch.h
logos.o: cfetch.h
util.o: util.h
cfetch.o: cfetch.c cfetch.h config.h logos.h $(BLOCKS:=.h)

config.h:
	cat config.def.h > config.h

cfetch: cfetch.o util.o logos.o $(BLOCKS:=.o)
	$(CC) -o $@ $(LDFLAGS) $(BLOCKS:=.o) util.o logos.o cfetch.o

cfetch.1: $(MANUAL)
	scdoc < $(MANUAL) > cfetch.1

clean:
	rm -f cfetch.1 cfetch *.o blocks/*.o

install: all
	cp -f ./cfetch "$(PREFIX)/bin"
	chmod 755 "$(PREFIX)/bin/cfetch"
	mkdir -p "$(PREFIX)/share/man/man1"
	cp -f ./cfetch.1 "$(PREFIX)/share/man/man1"
	chmod 644 "$(PREFIX)/share/man/man1/cfetch.1"

.SUFFIXES: .c .o
.c.o:
	$(CC) -o $@ $(CFLAGS) -c $<


