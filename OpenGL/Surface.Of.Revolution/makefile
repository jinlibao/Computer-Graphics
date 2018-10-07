#
# makefile
# Libao Jin, 2018-09-25 10:15
#

# CC = g++
# CC = /usr/bin/g++
CC = clang
# CFLAGS = -lstdc++ -framework GLUT -framework OpenGL -Wno-deprecated
CFLAGS = -lstdc++ -lglut -lGLU -lGL -I/opt/X11/include -L/opt/X11/lib -Wno-deprecated # X11
# CFLAGS = -lstdc++ -framework GLUT -framework OpenGL -I/opt/X11/include -L/opt/X11/lib -Wno-deprecated # X11
# CFLAGS = -lstdc++ -framework OpenGL -lglut -L/opt/X11/lib -Wno-deprecated

RM = rm -rf

ALLPROGS = lectureMesh

.DEFAULT_GOAL := all

all: $(ALLPROGS)

$(ALLPROGS): $(ALLPROGS:=.cpp)
	$(CC) $(CFLAGS) -o $@ $<

clean:
	$(RM) $(ALLPROGS:=.dSYM) $(ALLPROGS:=.o)

distclean: clean
	$(RM) $(ALLPROGS)
