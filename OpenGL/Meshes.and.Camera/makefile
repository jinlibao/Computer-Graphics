#
# makefile
# Libao Jin, 2018-10-08 15:31
#

# CC = g++
# CC = /usr/bin/g++
CC = clang++
# CFLAGS = --std=c++17 -lstdc++ -lfreeimage -framework GLUT -framework OpenGL -Wno-deprecated
CFLAGS = --std=c++17 -lstdc++ -lfreeimage -lglut -lGLU -lGL -I/opt/X11/include -L/opt/X11/lib -Wno-deprecated # X11

RM = rm -rf

NAME = main matrix mesh camera

.DEFAULT_GOAL := all

ALLPROGS = $(NAME)

all: distclean main

main: main.cpp camera.cpp matrix.cpp mesh.cpp
	$(CC) $(CFLAGS) -o $@ $?

# matrix.o: matrix.cpp
# 	$(CC) $(CFLAGSO) -c $<
# 
# mesh.o: matrix.o mesh.cpp
# 	$(CC) $(CFLAGS0) -c $?
# 
# camera.o: matrix.o camera.cpp
# 	$(CC) $(CFLAGSO) -c $?

clean:
	$(RM) $(NAME:=.dSYM) $(NAME:=.o)

distclean: clean
	$(RM) $(ALLPROGS)
