#
# makefile
# Libao Jin, 2018-10-04 10:15
#

# CC = g++
# CC = /usr/bin/g++
CC = clang
CFLAGSX = -lstdc++ -lfreeimage -framework GLUT -framework OpenGL -Wno-deprecated
# CFLAGSX = -lstdc++ -lfreeimage -lglut -lGLU -lGL -I/opt/X11/include -L/opt/X11/lib -Wno-deprecated # X11
# CFLAGS = -lstdc++ -framework GLUT -framework OpenGL -Wno-deprecated
# CFLAGS = -lstdc++ -lglut -lGLU -lGL -I/opt/X11/include -L/opt/X11/lib -Wno-deprecated # X11
# CFLAGS = -lstdc++ -framework GLUT -framework OpenGL -I/opt/X11/include -L/opt/X11/lib -Wno-deprecated # X11
# CFLAGS = -lstdc++ -framework OpenGL -lglut -L/opt/X11/lib -Wno-deprecated
EXECX = ./exec/apple
# EXECX = ./exec/xquartz

RM = rm -rf

NAME = lectureMaterialsLighting

.DEFAULT_GOAL := all

ALLPROGS = $(NAME:=_0) \
	$(NAME:=_1a) $(NAME:=_1b) $(NAME:=_1c) $(NAME:=_1d) $(NAME:=_1e) \
	$(NAME:=_2.lr) $(NAME:=_2.rl) \
	$(NAME:=_2.fb) $(NAME:=_2.bf) \
	$(NAME:=_2.bt) $(NAME:=_2.tb) \
	$(NAME:=_2.bltr) $(NAME:=_2.trbl) \
	$(NAME:=_2.lra) $(NAME:=_2.lrd) $(NAME:=_2.lrs) $(NAME:=_2.lrblue) \
	$(NAME:=_3) $(NAME:=_3a) $(NAME:=_3az0) $(NAME:=_3az1) $(NAME:=_3az2) $(NAME:=_3az3) \
	$(NAME:=_3b5) $(NAME:=_3b3) $(NAME:=_3c) $(NAME:=_3d5) $(NAME:=_3d1) \
	$(NAME:=_4) \
	$(NAME:=_4aa1) $(NAME:=_4aa2) $(NAME:=_4aa3) \
	$(NAME:=_4ad1) $(NAME:=_4ad2) $(NAME:=_4ad3) \
	$(NAME:=_4as1) $(NAME:=_4as2) $(NAME:=_4as3) \
	$(NAME:=_4ash1) $(NAME:=_4ash2) $(NAME:=_4ash3) $(NAME:=_4ash4) \
	$(NAME:=_4b1a1) $(NAME:=_4b1a2) $(NAME:=_4b1a3) \
	$(NAME:=_4b1d1) $(NAME:=_4b1d2) $(NAME:=_4b1d3) \
	$(NAME:=_4b1s1) $(NAME:=_4b1s2) $(NAME:=_4b1s3) \
	$(NAME:=_4b1sh1) $(NAME:=_4b1sh2) $(NAME:=_4b1sh3) $(NAME:=_4b1sh4) \
	$(NAME:=_4b2a1) $(NAME:=_4b2a2) $(NAME:=_4b2a3) \
	$(NAME:=_4b2d1) $(NAME:=_4b2d2) $(NAME:=_4b2d3) \
	$(NAME:=_4b2s1) $(NAME:=_4b2s2) $(NAME:=_4b2s3) \
	$(NAME:=_4b2sh1) $(NAME:=_4b2sh2) $(NAME:=_4b2sh3) $(NAME:=_4b2sh4) \
	$(NAME:=_4b3a1) $(NAME:=_4b3a2) $(NAME:=_4b3a3) \
	$(NAME:=_4b3d1) $(NAME:=_4b3d2) $(NAME:=_4b3d3) \
	$(NAME:=_4b3s1) $(NAME:=_4b3s2) $(NAME:=_4b3s3) \
	$(NAME:=_4b3sh1) $(NAME:=_4b3sh2) $(NAME:=_4b3sh3) $(NAME:=_4b3sh4) \

all: $(ALLPROGS)
# all: $(NAME:=_3d1)

$(NAME:=_0): $(NAME:=.cpp)
	$(CC) $(CFLAGSX) -D OPTION=\"0\" -o $(EXECX)/$@ $<

$(NAME:=_1a): $(NAME:=.cpp)
	$(CC) $(CFLAGSX) -D OPTION=\"1a\" -o $(EXECX)/$@ $<

$(NAME:=_1b): $(NAME:=.cpp)
	$(CC) $(CFLAGSX) -D OPTION=\"1b\" -o $(EXECX)/$@ $<

$(NAME:=_1c): $(NAME:=.cpp)
	$(CC) $(CFLAGSX) -D OPTION=\"1c\" -o $(EXECX)/$@ $<

$(NAME:=_1d): $(NAME:=.cpp)
	$(CC) $(CFLAGSX) -D OPTION=\"1d\" -o $(EXECX)/$@ $<

$(NAME:=_1e): $(NAME:=.cpp)
	$(CC) $(CFLAGSX) -D OPTION=\"1e\" -o $(EXECX)/$@ $<

$(NAME:=_2.lr): $(NAME:=.cpp)
	$(CC) $(CFLAGSX) -D OPTION=\"2.lr\" -o $(EXECX)/$@ $<

$(NAME:=_2.rl): $(NAME:=.cpp)
	$(CC) $(CFLAGSX) -D OPTION=\"2.rl\" -o $(EXECX)/$@ $<

$(NAME:=_2.fb): $(NAME:=.cpp)
	$(CC) $(CFLAGSX) -D OPTION=\"2.fb\" -o $(EXECX)/$@ $<

$(NAME:=_2.bf): $(NAME:=.cpp)
	$(CC) $(CFLAGSX) -D OPTION=\"2.bf\" -o $(EXECX)/$@ $<

$(NAME:=_2.bt): $(NAME:=.cpp)
	$(CC) $(CFLAGSX) -D OPTION=\"2.bt\" -o $(EXECX)/$@ $<

$(NAME:=_2.tb): $(NAME:=.cpp)
	$(CC) $(CFLAGSX) -D OPTION=\"2.tb\" -o $(EXECX)/$@ $<

$(NAME:=_2.bltr): $(NAME:=.cpp)
	$(CC) $(CFLAGSX) -D OPTION=\"2.bltr\" -o $(EXECX)/$@ $<

$(NAME:=_2.trbl): $(NAME:=.cpp)
	$(CC) $(CFLAGSX) -D OPTION=\"2.trbl\" -o $(EXECX)/$@ $<

$(NAME:=_2.lra): $(NAME:=.cpp)
	$(CC) $(CFLAGSX) -D OPTION=\"2.lra\" -o $(EXECX)/$@ $<

$(NAME:=_2.lrd): $(NAME:=.cpp)
	$(CC) $(CFLAGSX) -D OPTION=\"2.lrd\" -o $(EXECX)/$@ $<

$(NAME:=_2.lrs): $(NAME:=.cpp)
	$(CC) $(CFLAGSX) -D OPTION=\"2.lrs\" -o $(EXECX)/$@ $<

$(NAME:=_2.lrblue): $(NAME:=.cpp)
	$(CC) $(CFLAGSX) -D OPTION=\"2.lrblue\" -o $(EXECX)/$@ $<

$(NAME:=_3): $(NAME:=.cpp)
	$(CC) $(CFLAGSX) -D OPTION=\"3\" -o $(EXECX)/$@ $<

$(NAME:=_3a): $(NAME:=.cpp)
	$(CC) $(CFLAGSX) -D OPTION=\"3a\" -o $(EXECX)/$@ $<

$(NAME:=_3az0): $(NAME:=.cpp)
	$(CC) $(CFLAGSX) -D OPTION=\"3az0\" -o $(EXECX)/$@ $<

$(NAME:=_3az1): $(NAME:=.cpp)
	$(CC) $(CFLAGSX) -D OPTION=\"3az1\" -o $(EXECX)/$@ $<

$(NAME:=_3az2): $(NAME:=.cpp)
	$(CC) $(CFLAGSX) -D OPTION=\"3az2\" -o $(EXECX)/$@ $<

$(NAME:=_3az3): $(NAME:=.cpp)
	$(CC) $(CFLAGSX) -D OPTION=\"3az3\" -o $(EXECX)/$@ $<

$(NAME:=_3b5): $(NAME:=.cpp)
	$(CC) $(CFLAGSX) -D OPTION=\"3b5\" -o $(EXECX)/$@ $<

$(NAME:=_3b3): $(NAME:=.cpp)
	$(CC) $(CFLAGSX) -D OPTION=\"3b3\" -o $(EXECX)/$@ $<

$(NAME:=_3c): $(NAME:=.cpp)
	$(CC) $(CFLAGSX) -D OPTION=\"3c\" -o $(EXECX)/$@ $<

$(NAME:=_3d1): $(NAME:=.cpp)
	$(CC) $(CFLAGSX) -D OPTION=\"3d1\" -o $(EXECX)/$@ $<

$(NAME:=_3d5): $(NAME:=.cpp)
	$(CC) $(CFLAGSX) -D OPTION=\"3d5\" -o $(EXECX)/$@ $<

$(NAME:=_4): $(NAME:=.cpp)
	$(CC) $(CFLAGSX) -D OPTION=\"4\" -o $(EXECX)/$@ $<

$(NAME:=_4aa1): $(NAME:=.cpp)
	$(CC) $(CFLAGSX) -D OPTION=\"4aa1\" -o $(EXECX)/$@ $<

$(NAME:=_4aa2): $(NAME:=.cpp)
	$(CC) $(CFLAGSX) -D OPTION=\"4aa2\" -o $(EXECX)/$@ $<

$(NAME:=_4aa3): $(NAME:=.cpp)
	$(CC) $(CFLAGSX) -D OPTION=\"4aa3\" -o $(EXECX)/$@ $<

$(NAME:=_4ad1): $(NAME:=.cpp)
	$(CC) $(CFLAGSX) -D OPTION=\"4ad1\" -o $(EXECX)/$@ $<

$(NAME:=_4ad2): $(NAME:=.cpp)
	$(CC) $(CFLAGSX) -D OPTION=\"4ad2\" -o $(EXECX)/$@ $<

$(NAME:=_4ad3): $(NAME:=.cpp)
	$(CC) $(CFLAGSX) -D OPTION=\"4ad3\" -o $(EXECX)/$@ $<

$(NAME:=_4as1): $(NAME:=.cpp)
	$(CC) $(CFLAGSX) -D OPTION=\"4as1\" -o $(EXECX)/$@ $<

$(NAME:=_4as2): $(NAME:=.cpp)
	$(CC) $(CFLAGSX) -D OPTION=\"4as2\" -o $(EXECX)/$@ $<

$(NAME:=_4as3): $(NAME:=.cpp)
	$(CC) $(CFLAGSX) -D OPTION=\"4as3\" -o $(EXECX)/$@ $<

$(NAME:=_4ash1): $(NAME:=.cpp)
	$(CC) $(CFLAGSX) -D OPTION=\"4ash1\" -o $(EXECX)/$@ $<

$(NAME:=_4ash2): $(NAME:=.cpp)
	$(CC) $(CFLAGSX) -D OPTION=\"4ash2\" -o $(EXECX)/$@ $<

$(NAME:=_4ash3): $(NAME:=.cpp)
	$(CC) $(CFLAGSX) -D OPTION=\"4ash3\" -o $(EXECX)/$@ $<

$(NAME:=_4ash4): $(NAME:=.cpp)
	$(CC) $(CFLAGSX) -D OPTION=\"4ash4\" -o $(EXECX)/$@ $<

$(NAME:=_4b1a1): $(NAME:=.cpp)
	$(CC) $(CFLAGSX) -D OPTION=\"4b1a1\" -o $(EXECX)/$@ $<

$(NAME:=_4b1a2): $(NAME:=.cpp)
	$(CC) $(CFLAGSX) -D OPTION=\"4b1a2\" -o $(EXECX)/$@ $<

$(NAME:=_4b1a3): $(NAME:=.cpp)
	$(CC) $(CFLAGSX) -D OPTION=\"4b1a3\" -o $(EXECX)/$@ $<

$(NAME:=_4b1d1): $(NAME:=.cpp)
	$(CC) $(CFLAGSX) -D OPTION=\"4b1d1\" -o $(EXECX)/$@ $<

$(NAME:=_4b1d2): $(NAME:=.cpp)
	$(CC) $(CFLAGSX) -D OPTION=\"4b1d2\" -o $(EXECX)/$@ $<

$(NAME:=_4b1d3): $(NAME:=.cpp)
	$(CC) $(CFLAGSX) -D OPTION=\"4b1d3\" -o $(EXECX)/$@ $<

$(NAME:=_4b1s1): $(NAME:=.cpp)
	$(CC) $(CFLAGSX) -D OPTION=\"4b1s1\" -o $(EXECX)/$@ $<

$(NAME:=_4b1s2): $(NAME:=.cpp)
	$(CC) $(CFLAGSX) -D OPTION=\"4b1s2\" -o $(EXECX)/$@ $<

$(NAME:=_4b1s3): $(NAME:=.cpp)
	$(CC) $(CFLAGSX) -D OPTION=\"4b1s3\" -o $(EXECX)/$@ $<

$(NAME:=_4b1sh1): $(NAME:=.cpp)
	$(CC) $(CFLAGSX) -D OPTION=\"4b1sh1\" -o $(EXECX)/$@ $<

$(NAME:=_4b1sh2): $(NAME:=.cpp)
	$(CC) $(CFLAGSX) -D OPTION=\"4b1sh2\" -o $(EXECX)/$@ $<

$(NAME:=_4b1sh3): $(NAME:=.cpp)
	$(CC) $(CFLAGSX) -D OPTION=\"4b1sh3\" -o $(EXECX)/$@ $<

$(NAME:=_4b1sh4): $(NAME:=.cpp)
	$(CC) $(CFLAGSX) -D OPTION=\"4b1sh4\" -o $(EXECX)/$@ $<

$(NAME:=_4b2a1): $(NAME:=.cpp)
	$(CC) $(CFLAGSX) -D OPTION=\"4b2a1\" -o $(EXECX)/$@ $<

$(NAME:=_4b2a2): $(NAME:=.cpp)
	$(CC) $(CFLAGSX) -D OPTION=\"4b2a2\" -o $(EXECX)/$@ $<

$(NAME:=_4b2a3): $(NAME:=.cpp)
	$(CC) $(CFLAGSX) -D OPTION=\"4b2a3\" -o $(EXECX)/$@ $<

$(NAME:=_4b2d1): $(NAME:=.cpp)
	$(CC) $(CFLAGSX) -D OPTION=\"4b2d1\" -o $(EXECX)/$@ $<

$(NAME:=_4b2d2): $(NAME:=.cpp)
	$(CC) $(CFLAGSX) -D OPTION=\"4b2d2\" -o $(EXECX)/$@ $<

$(NAME:=_4b2d3): $(NAME:=.cpp)
	$(CC) $(CFLAGSX) -D OPTION=\"4b2d3\" -o $(EXECX)/$@ $<

$(NAME:=_4b2s1): $(NAME:=.cpp)
	$(CC) $(CFLAGSX) -D OPTION=\"4b2s1\" -o $(EXECX)/$@ $<

$(NAME:=_4b2s2): $(NAME:=.cpp)
	$(CC) $(CFLAGSX) -D OPTION=\"4b2s2\" -o $(EXECX)/$@ $<

$(NAME:=_4b2s3): $(NAME:=.cpp)
	$(CC) $(CFLAGSX) -D OPTION=\"4b2s3\" -o $(EXECX)/$@ $<

$(NAME:=_4b2sh1): $(NAME:=.cpp)
	$(CC) $(CFLAGSX) -D OPTION=\"4b2sh1\" -o $(EXECX)/$@ $<

$(NAME:=_4b2sh2): $(NAME:=.cpp)
	$(CC) $(CFLAGSX) -D OPTION=\"4b2sh2\" -o $(EXECX)/$@ $<

$(NAME:=_4b2sh3): $(NAME:=.cpp)
	$(CC) $(CFLAGSX) -D OPTION=\"4b2sh3\" -o $(EXECX)/$@ $<

$(NAME:=_4b2sh4): $(NAME:=.cpp)
	$(CC) $(CFLAGSX) -D OPTION=\"4b2sh4\" -o $(EXECX)/$@ $<

$(NAME:=_4b3a1): $(NAME:=.cpp)
	$(CC) $(CFLAGSX) -D OPTION=\"4b3a1\" -o $(EXECX)/$@ $<

$(NAME:=_4b3a2): $(NAME:=.cpp)
	$(CC) $(CFLAGSX) -D OPTION=\"4b3a2\" -o $(EXECX)/$@ $<

$(NAME:=_4b3a3): $(NAME:=.cpp)
	$(CC) $(CFLAGSX) -D OPTION=\"4b3a3\" -o $(EXECX)/$@ $<

$(NAME:=_4b3d1): $(NAME:=.cpp)
	$(CC) $(CFLAGSX) -D OPTION=\"4b3d1\" -o $(EXECX)/$@ $<

$(NAME:=_4b3d2): $(NAME:=.cpp)
	$(CC) $(CFLAGSX) -D OPTION=\"4b3d2\" -o $(EXECX)/$@ $<

$(NAME:=_4b3d3): $(NAME:=.cpp)
	$(CC) $(CFLAGSX) -D OPTION=\"4b3d3\" -o $(EXECX)/$@ $<

$(NAME:=_4b3s1): $(NAME:=.cpp)
	$(CC) $(CFLAGSX) -D OPTION=\"4b3s1\" -o $(EXECX)/$@ $<

$(NAME:=_4b3s2): $(NAME:=.cpp)
	$(CC) $(CFLAGSX) -D OPTION=\"4b3s2\" -o $(EXECX)/$@ $<

$(NAME:=_4b3s3): $(NAME:=.cpp)
	$(CC) $(CFLAGSX) -D OPTION=\"4b3s3\" -o $(EXECX)/$@ $<

$(NAME:=_4b3sh1): $(NAME:=.cpp)
	$(CC) $(CFLAGSX) -D OPTION=\"4b3sh1\" -o $(EXECX)/$@ $<

$(NAME:=_4b3sh2): $(NAME:=.cpp)
	$(CC) $(CFLAGSX) -D OPTION=\"4b3sh2\" -o $(EXECX)/$@ $<

$(NAME:=_4b3sh3): $(NAME:=.cpp)
	$(CC) $(CFLAGSX) -D OPTION=\"4b3sh3\" -o $(EXECX)/$@ $<

$(NAME:=_4b3sh4): $(NAME:=.cpp)
	$(CC) $(CFLAGSX) -D OPTION=\"4b3sh4\" -o $(EXECX)/$@ $<

clean:
	$(RM) $(NAME:=.dSYM) $(NAME:=.o)

distclean: clean
	$(RM) $(ALLPROGS)
