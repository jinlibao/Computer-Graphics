#
# makefile
# Libao Jin, 2018-10-28 15:31
#

# CC = g++  # g++ (Homebrew GCC 8.2.0) 8.2.0
# CFLAGS for g++ (Homebrew GCC 8.2.0) 8.2.0
# CFLAGS = --std=c++17 -lstdc++ -lfreeimage -lglut -lGLU -lGL -I/opt/X11/include -L/opt/X11/lib -Wno-deprecated -I/usr/local/include -L/usr/local/lib -DUSEFREEIMAGE=1 -D X11=1
# CFLAGS = --std=c++17 -lstdc++ -lfreeimage -framework GLUT -framework OpenGL -Wno-deprecated -I/usr/local/include -L/usr/local/lib -DUSEFREEIMAGE=1


# CC = /usr/bin/g++
CC = clang++

# use freeimage
# CFLAGS = --std=c++17 -lstdc++ -lfreeimage -framework GLUT -framework OpenGL -Wno-deprecated -D USEFREEIMAGE=1
# CFLAGS = -g --std=c++17 -lstdc++ -lfreeimage -lglut -lGLU -lGL -I/opt/X11/include -L/opt/X11/lib -Wno-deprecated -DUSEFREEIMAGE=1 -D X11=1

# do not use freeimage
CFLAGS = --std=c++17 -lstdc++ -framework GLUT -framework OpenGL -Wno-deprecated
# CFLAGS = --std=c++17 -lstdc++ -lglut -lGLU -lGL -I/opt/X11/include -L/opt/X11/lib -Wno-deprecated -D X11=1

RM = rm -rf

NAME = main matrix mesh camera

.DEFAULT_GOAL := all

ALLPROGS = $(NAME)

all: distclean main

main: main.cpp camera.cpp matrix.cpp
	$(CC) $(CFLAGS) -o $@ $?

clean:
	$(RM) $(NAME:=.dSYM) $(NAME:=.o)

distclean: clean
	$(RM) $(ALLPROGS) ./output/*png
