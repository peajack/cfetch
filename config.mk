PREFIX	=	/usr/local
CC		=	cc
CFLAGS	=	-std=c89 -O2 -Wall -Werror -pedantic
LDFLAGS	=	-s -lpthread

# uncomment if your system has strdup(3) within ANSI C
#LDFLAGS +=  -DHAS_STRDUP


BLOCKS	=	blocks/kernel blocks/user blocks/os blocks/shell\
			blocks/memory blocks/cpu blocks/uptime
MANUAL	=	cfetch.1.scd
