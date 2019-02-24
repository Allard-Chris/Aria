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
SFILES			= aria_core.c
IFILES			= aria_core.h aria_const.h aria_type.h
OBJFILES		= $(patsubst %,$(SRCDIR)/%,$(SFILES))
INCFILES		= $(patsubst %,$(SRCDIR)/%,$(IFILES))
CFLAGS_GEN		= -Wall -O -DVERSION=\"$(VERSION)\" $(CFLAGS)
CLANG-FORMAT		= $(shell command -v clang-format 2> /dev/null)
CLANG-TIDY		= $(shell command -v clang-tidy 2> /dev/null)

all: $(PROGNAME)

$(PROGNAME): clean style-format style-tidy $(SRCDIR)/$(PROGNAME).c $(OBJFILES) $(INCFILES)
	@echo "Compiling Aria:"
	$(CC) $(SRCDIR)/$(PROGNAME).c -o $(PROGNAME) \
	$(CFLAGS_GEN) $(OBJFILES)

style-format:
ifneq ($(CLANG-FORMAT),)
	@echo "Clang-format formatting:"
	@for src in $(SRCDIR)/* ; do \
		echo "Formatting $$src..."; \
		clang-format -i "$$src" ; \
	done
else
	@echo "Warning: clang-format>=3.8.0 is not installed...Skipping"
endif

style-tidy:
ifneq ($(CLANG-TIDY),)
	@echo "Clang-tiddy formatting:"
	@for src in $(SRCDIR)/* ; do \
		echo "Formatting $$src..."; \
		clang-tidy -fix "$$src" -- ; \
	done
else
	@echo "Warning: clang-tidy>=3.8.0 is not installed...Skipping"
endif

clean:
	@echo "Cleaning:"
	rm -f $(PROGNAME) *.exe *.o *~ a.out core core.[1-9][0-9]* *.stackdump


