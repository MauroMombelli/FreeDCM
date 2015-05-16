PROJECTNAME=test
CC=gcc

CFLAGS= -I .

TARGETS=all clean

ODIR=build

LIBS=-lm

SUBDIRS_TARGETS := \
    $(foreach t,$(TARGETS),$(addsuffix $t,$(SUBDIRS)))

DEPS = $(patsubst %,$(IDIR)/%,$(_DEPS))


$(ODIR)/%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

all: $(OBJ)
	mkdir -p $(ODIR)
	gcc -o $(ODIR)/$(PROJECTNAME).o $(CFLAGS) $(LIBS) test/main.c 

.PHONY: clean

clean:
	rm -f $(ODIR)/*.o *~ core $(INCDIR)/*~ 