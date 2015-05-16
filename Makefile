CC=gcc
LD=$(CC)
CFLAGS= -Wall -Wextra -Wpedantic -I . -std=c11

PROJECTNAME=test

ODIR=build

LIBS=-lm

SOURCE=$(shell find . -name "*.c")

$(ODIR)/%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

all: $(OBJ)
	mkdir -p $(ODIR)
	$(LD) $(CFLAGS) $(LIBS) $(SOURCE) -o $(ODIR)/$(PROJECTNAME)

.PHONY: clean

clean:
	rm -f $(ODIR) 