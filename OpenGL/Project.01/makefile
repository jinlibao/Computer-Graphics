#
# makefile
# Libao Jin, 2018-09-04 11:31
#

CC = clang
CFLAGS = -framework OpenGL -framework GLUT -Wno-deprecated
RM = rm -rf

ALLPROGS = paint

.DEFAULT_GOAL := all

all: $(ALLPROGS)

paint: paint.cpp
	$(CC) $(CFLAGS) -o $@ $<

clean:
	$(RM) $(ALLPROGS:=.dSYM) $(ALLPROGS:=.o)

distclean: clean
	$(RM) $(ALLPROGS)
