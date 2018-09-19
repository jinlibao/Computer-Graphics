#
# makefile
# Libao Jin, 2018-09-04 11:31
#

cc = gcc  # clang
cflags = --std=c11 -g -Wall
CC = clang
CFLAGS = -framework OpenGL -framework GLUT -Wno-deprecated
JC = javac
FC = gfortran
RM = rm -rf

ALLPROGS = paint

.DEFAULT_GOAL := all

all: $(ALLPROGS) # $(addsuffix FreeGLUT,$(ALLPROGS)) $(addsuffix Mixed,$(ALLPROGS))

paint: paint.cpp
	$(CC) $(CFLAGS) -o $@ $<

ProjectionExampleClass: ProjectionExampleClass.cpp
	$(CC) $(CFLAGS) -o $@ $<

clean:
	$(RM) $(ALLPROGS:=.dSYM) $(ALLPROGS:=.o)

distclean: clean
	$(RM) $(ALLPROGS) $(addsuffix FreeGLUT,$(ALLPROGS)) $(addsuffix Mixed,$(ALLPROGS))
