#ifndef CC
CC=gcc
CFLAGS= -I TrigonomeC -Wall -Wextra -Wpedantic -I . -std=c11
#endif
LD=$(CC)

PROJECTNAME=Test_FreeDcmTest

ODIR=build

LIBS=-lm

SOURCE=$(shell find . -follow -name "*.c")

$(ODIR)/%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

all: $(OBJ)
	mkdir -p $(ODIR)
	$(LD) $(CFLAGS) $(LIBS) $(SOURCE) -o $(ODIR)/$(PROJECTNAME)

.PHONY: clean

clean:
	rm -f $(ODIR) 
