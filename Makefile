CC 		= gcc
CFLAGS 	= -std=gnu99
DBFLAGS = -Wall -W -g
LDFLAGS = -lm
SRC 	= main.c dyn_list.c dyn_list.h

debug: $(SRC)
	$(CC) $(CFLAGS) $(DBFLAGS) main.c dyn_list.c -o main
prod: $(SRC)
	$(CC) $(CFLAGS) -O3 main.c dyn_list.c -o main
tar:
	tar -cvf ha_prog.tar dyn_list.c dyn_list.h main.c main Makefile

open:
	vi -p $(SRC) Makefile
