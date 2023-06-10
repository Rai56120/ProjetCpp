GTKMM_CF ='pkg-config gtkmm-3.0 --cflags'
GTKMM_LD ='pkg-config gtkmm-3.0 --libs'

CFLAGS = $(GTKMM_CF) -Wall
LDFLAGS = $(GTKMM_LD)

CC = g++

SRC = main.cpp

PROG = main

OBJS = $(SRC:.cpp=.o)
.SUFFIXES: .cpp .o

all: $(PROG)


$(PROG): $(OBJS)
		$(CC) -o $@ $^ $(LDFLAGS)

main.cpp : headers/vue.hpp

.PHONY: clean
clean:
		rm -f *.o *- core $(PROG)