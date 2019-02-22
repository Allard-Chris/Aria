#**********************************************/
# Author  : Chris Allard, Corentin Aulagnier
# Date    : 2019-02
# Source  : https://github.com/Allard-Chris/Aria
# Version : 0.1
###
# Aria Makefile
#**********************************************/

PROGNAME 		= aria
VERSION 		= 0.1
SRCDIR			= src
SFILES			=	aria_core.c
IFILES			=	aria_core.h aria_const.h aria_type.h
OBJFILES		=	$(patsubst %,$(SRCDIR)/%,$(SFILES))
INCFILES		=	$(patsubst %,$(SRCDIR)/%,$(IFILES))
CFLAGS_GEN	=	-Wall -O -DVERSION=\"$(VERSION)\" $(CFLAGS)

all: $(PROGNAME)

$(PROGNAME): $(SRCDIR)/$(PROGNAME).c $(OBJFILES) $(INCFILES)
	@echo "Checking code style:"
	make style
	@echo "Compile:"
	$(CC) $(SRCDIR)/$(PROGNAME).c -o $(PROGNAME) \
	$(CFLAGS_GEN) $(OBJFILES)

style:
	@for src in $(SRCDIR)/* ; do \
		echo "Formatting $$src..."; \
		clang-format -i "$$src" ; \
		clang-tidy -fix "$$src" -- ; \
	done

clean:
	rm -f $(PROGNAME) *.exe *.o *~ a.out core core.[1-9][0-9]* *.stackdump
