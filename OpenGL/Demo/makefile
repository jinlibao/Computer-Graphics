#
# makefile
# Libao Jin, 2018-09-04 11:31
#

cc = gcc  # clang
cflags = --std=c11 -g -Wall
CC = clang
CFLAGS1 = -framework OpenGL -framework GLUT -Wno-deprecated
CFLAGS2 = -I/usr/local/Cellar/freeglut/3.0.0/include -L/usr/local/Cellar/freeglut/3.0.0/lib -w -framework OpenGL -lGLUT
CFLAGS3 = -I/usr/local/Cellar/freeglut/3.0.0/include -L/usr/local/Cellar/freeglut/3.0.0/lib -lGLUT -w -framework OpenGL -framework GLUT
JC = javac
FC = gfortran
RM = rm -rf

ALLPROGS = demo

.DEFAULT_GOAL := all

all: $(ALLPROGS) # $(addsuffix FreeGLUT,$(ALLPROGS)) $(addsuffix Mixed,$(ALLPROGS))

demo: demo.cpp
	$(CC) $(CFLAGS1) -o $@ $<

demoFreeGLUT: demo.cpp
	$(CC) $(CFLAGS2) -o $@ $<

demoMixed: demo.cpp
	$(CC) $(CFLAGS3) -o $@ $<

clean:
	$(RM) $(ALLPROGS:=.dSYM) $(ALLPROGS:=.o)

distclean: clean
	$(RM) $(ALLPROGS) $(addsuffix FreeGLUT,$(ALLPROGS)) $(addsuffix Mixed,$(ALLPROGS))
