#
# makefile
# Libao Jin, 2018-11-09 11:03
#

# CC = g++  # g++ (Homebrew GCC 8.2.0) 8.2.0
# CFLAGS for g++ (Homebrew GCC 8.2.0) 8.2.0
# CFLAGS = --std=c++17 -lstdc++ -lfreeimage -lglut -lGLU -lGL -I/opt/X11/include -L/opt/X11/lib -Wno-deprecated -I/usr/local/include -L/usr/local/lib -DUSEFREEIMAGE=1 -D X11=1
# CFLAGS = --std=c++17 -lstdc++ -lfreeimage -framework GLUT -framework OpenGL -Wno-deprecated -I/usr/local/include -L/usr/local/lib -DUSEFREEIMAGE=1


# CC = /usr/bin/g++
CC = clang++

# use freeimage
# CFLAGS = --std=c++17 -lstdc++ -lfreeimage -framework GLUT -framework OpenGL -Wno-deprecated -D USEFREEIMAGE=1
# CFLAGS = --std=c++17 -lstdc++ -lfreeimage -lglut -lGLU -lGL -I/opt/X11/include -L/opt/X11/lib -Wno-deprecated -DUSEFREEIMAGE=1 -D X11=1

# do not use freeimage
CFLAGS = --std=c++17 -lstdc++ -framework GLUT -framework OpenGL -Wno-deprecated
# CFLAGS = --std=c++17 -lstdc++ -lglut -lGLU -lGL -I/opt/X11/include -L/opt/X11/lib -Wno-deprecated -D X11=1
EXECPATH = ./exec
RM = rm -rf

NAME = main main3a main3b main3c

.DEFAULT_GOAL := all

ALLPROGS = $(NAME)

all: distclean $(ALLPROGS)

main: main.cpp
	$(CC) $(CFLAGS) -o $(EXECPATH)/$@ $?

main3a: main.cpp
	$(CC) $(CFLAGS) -o $(EXECPATH)/$@ $? -DPROJECT=\"proj3a\"

main3b: main.cpp
	$(CC) $(CFLAGS) -o $(EXECPATH)/$@ $? -DPROJECT=\"proj3b\"

main3c: main.cpp
	$(CC) $(CFLAGS) -o $(EXECPATH)/$@ $? -DPROJECT=\"proj3c\"

clean:
	$(RM) $(addprefix $(EXECPATH)/, $(NAME:=.dSYM)) $(NAME:=.o)

distclean: clean
	$(RM) $(addprefix $(EXECPATH)/, $(NAME)) ./output/*png
