#
# makefile
# Libao Jin, 2018-10-08 15:31
#

# CC = g++  # g++ (Homebrew GCC 8.2.0) 8.2.0
# CFLAGS for g++ (Homebrew GCC 8.2.0) 8.2.0
# CFLAGS = --std=c++17 -lstdc++ -lfreeimage -lglut -lGLU -lGL -I/opt/X11/include -L/opt/X11/lib -Wno-deprecated -I/usr/local/include -L/usr/local/lib -DUSEFREEIMAGE=1 -D X11=1
# CFLAGS = --std=c++17 -lstdc++ -lfreeimage -framework GLUT -framework OpenGL -Wno-deprecated -I/usr/local/include -L/usr/local/lib -DUSEFREEIMAGE=1


# CC = /usr/bin/g++
CC = clang++

# use freeimage
# CFLAGS = --std=c++17 -lstdc++ -lfreeimage -framework GLUT -framework OpenGL -Wno-deprecated -D USEFREEIMAGE=1
CFLAGS = --std=c++17 -lstdc++ -lfreeimage -lglut -lGLU -lGL -I/opt/X11/include -L/opt/X11/lib -Wno-deprecated -DUSEFREEIMAGE=1 -D X11=1

# do not use freeimage
# CFLAGS = --std=c++17 -lstdc++ -framework GLUT -framework OpenGL -Wno-deprecated
# CFLAGS = --std=c++17 -lstdc++ -lglut -lGLU -lGL -I/opt/X11/include -L/opt/X11/lib -Wno-deprecated -D X11=1
EXEC = ./exec

RM = rm -rf

NAME = main main_1 main_2 main_3 main_4a main_4b main_5

.DEFAULT_GOAL := all

ALLPROGS = $(NAME)

all: distclean $(NAME)

main: main.cpp
	$(CC) $(CFLAGS) -o $(EXEC)/$@ $?

main_1: main.cpp
	$(CC) $(CFLAGS) -o $(EXEC)/$@ $? -D STEP=\"1\"

main_2: main.cpp
	$(CC) $(CFLAGS) -o $(EXEC)/$@ $? -D STEP=\"2\"

main_3: main.cpp
	$(CC) $(CFLAGS) -o $(EXEC)/$@ $? -D STEP=\"3\"

main_4a: main.cpp
	$(CC) $(CFLAGS) -o $(EXEC)/$@ $? -D STEP=\"4a\"

main_4b: main.cpp
	$(CC) $(CFLAGS) -o $(EXEC)/$@ $? -D STEP=\"4b\"

main_5: main.cpp
	$(CC) $(CFLAGS) -o $(EXEC)/$@ $? -D STEP=\"5\"


clean:
	$(RM) $(NAME:=.dSYM) $(NAME:=.o)

distclean: clean
	$(RM) $(EXEC)/$(ALLPROGS) ./output/*png
