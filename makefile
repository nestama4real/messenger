CC = gcc
CFLAGS = -Wall -Wextra -Werror -Iinclude
LDFLAGS = -lsodium


all:
	$(CC) $(CFLAGS) src/identity.c -o messenger $(LDFLAGS)