#
# makefile
# Libao Jin, 2018-10-08 15:31
#

# CC = g++
# CC = /usr/bin/g++
CC = clang
# CFLAGS = -lstdc++ -lfreeimage -framework GLUT -framework OpenGL -Wno-deprecated
CFLAGS = -std=c++17 -lstdc++ -lfreeimage -lglut -lGLU -lGL -I/opt/X11/include -L/opt/X11/lib -Wno-deprecated # X11
# CFLAGS = -lstdc++ -framework GLUT -framework OpenGL -Wno-deprecated
# CFLAGS = -lstdc++ -lglut -lGLU -lGL -I/opt/X11/include -L/opt/X11/lib -Wno-deprecated # X11
# CFLAGS = -lstdc++ -framework GLUT -framework OpenGL -I/opt/X11/include -L/opt/X11/lib -Wno-deprecated # X11
# CFLAGS = -lstdc++ -framework OpenGL -lglut -L/opt/X11/lib -Wno-deprecated
# EXECX = ./exec/apple
# EXECX = ./exec/xquartz

RM = rm -rf

NAME = meshes

.DEFAULT_GOAL := all

ALLPROGS = $(NAME)

all: $(ALLPROGS)

$(NAME): $(NAME:=.cpp)
	$(CC) $(CFLAGS) -o $@ $<

clean:
	$(RM) $(NAME:=.dSYM) $(NAME:=.o)

distclean: clean
	$(RM) $(ALLPROGS)
