CC = gcc
CFLAGS = -lncurses -lmenu -I$(IDIR) -std=c89 -Wall -Werror -Wextra -Wpedantic -Wformat=2
SRCDIR = ./src/
SOURCES = $(SRCDIR)*.c\
	  $(SRCDIR)/utils/*.c\
	  $(SRCDIR)/entities/*.c\
	  $(SRCDIR)/entities/items/*.c\
	  $(SRCDIR)/windows/*.c

IDIR = ./include/

all: spells_curses

spells_curses: $(SOURCES) 
	$(CC) $(SOURCES) $(CFLAGS) -o $@

run:
	./spells_curses

clean:
	rm -f spells_curses
