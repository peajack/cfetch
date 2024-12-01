PREFIX	=	/usr/local
CC		=	cc
CFLAGS	=	-std=c99 -O2 -Werror -Wall -pedantic
LDFLAGS	=	-s -lpthread
BLOCKS	=	blocks/kernel blocks/user blocks/os blocks/shell\
			blocks/memory blocks/cpu blocks/uptime
MANUAL	=	cfetch.1.scd
