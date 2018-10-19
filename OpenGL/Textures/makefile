# makefile
# Libao Jin, 2018-10-08 15:31

CC = clang
CFLAGS = -std=c++17 -lstdc++ -lfreeimage -framework GLUT -framework OpenGL -Wno-deprecated
# CFLAGS = -std=c++17 -lstdc++ -lfreeimage -lglut -lGLU -lGL -I/opt/X11/include -L/opt/X11/lib -Wno-deprecated # X11
EXECFOLDER = ./exec/apple
# EXECFOLDER = ./exec/xquartz

RM = rm -rf
NAME = textures_kitty_1 textures_kitty_2 textures_kitty_3a textures_kitty_3b textures_kitty_4 textures_kitty_5 textures_kitty_6a  textures_kitty_6b  textures_kitty_6c \
	   textures_chick_1 textures_chick_2 textures_chick_3a textures_chick_3b textures_chick_4 textures_chick_5 textures_chick_6a  textures_chick_6b  textures_chick_6c
.DEFAULT_GOAL := all
ALLPROGS = $(NAME)

all: $(ALLPROGS)

textures_kitty_1: textures.cpp
	$(CC) $(CFLAGS) -D OPTION=\"step_1\" -D IMAGE=\"kitty\" -o $(EXECFOLDER)/$@ $<
textures_kitty_2: textures.cpp
	$(CC) $(CFLAGS) -D OPTION=\"step_2\" -D IMAGE=\"kitty\" -o $(EXECFOLDER)/$@ $<
textures_kitty_3a: textures.cpp
	$(CC) $(CFLAGS) -D OPTION=\"step_3a\" -D IMAGE=\"kitty\" -o $(EXECFOLDER)/$@ $<
textures_kitty_3b: textures.cpp
	$(CC) $(CFLAGS) -D OPTION=\"step_3b\" -D IMAGE=\"kitty\" -o $(EXECFOLDER)/$@ $<
textures_kitty_4: textures.cpp
	$(CC) $(CFLAGS) -D OPTION=\"step_4\" -D IMAGE=\"kitty\" -o $(EXECFOLDER)/$@ $<
textures_kitty_5: textures.cpp
	$(CC) $(CFLAGS) -D OPTION=\"step_5\" -D IMAGE=\"kitty\" -o $(EXECFOLDER)/$@ $<
textures_kitty_6a: textures.cpp
	$(CC) $(CFLAGS) -D OPTION=\"step_6a\" -D IMAGE=\"kitty\" -o $(EXECFOLDER)/$@ $<
textures_kitty_6b: textures.cpp
	$(CC) $(CFLAGS) -D OPTION=\"step_6b\" -D IMAGE=\"kitty\" -o $(EXECFOLDER)/$@ $<
textures_kitty_6c: textures.cpp
	$(CC) $(CFLAGS) -D OPTION=\"step_6c\" -D IMAGE=\"kitty\" -o $(EXECFOLDER)/$@ $<

textures_chick_1: textures.cpp
	$(CC) $(CFLAGS) -D OPTION=\"step_1\" -D IMAGE=\"chick\" -o $(EXECFOLDER)/$@ $<
textures_chick_2: textures.cpp
	$(CC) $(CFLAGS) -D OPTION=\"step_2\" -D IMAGE=\"chick\" -o $(EXECFOLDER)/$@ $<
textures_chick_3a: textures.cpp
	$(CC) $(CFLAGS) -D OPTION=\"step_3a\" -D IMAGE=\"chick\" -o $(EXECFOLDER)/$@ $<
textures_chick_3b: textures.cpp
	$(CC) $(CFLAGS) -D OPTION=\"step_3b\" -D IMAGE=\"chick\" -o $(EXECFOLDER)/$@ $<
textures_chick_4: textures.cpp
	$(CC) $(CFLAGS) -D OPTION=\"step_4\" -D IMAGE=\"chick\" -o $(EXECFOLDER)/$@ $<
textures_chick_5: textures.cpp
	$(CC) $(CFLAGS) -D OPTION=\"step_5\" -D IMAGE=\"chick\" -o $(EXECFOLDER)/$@ $<
textures_chick_6a: textures.cpp
	$(CC) $(CFLAGS) -D OPTION=\"step_6a\" -D IMAGE=\"chick\" -o $(EXECFOLDER)/$@ $<
textures_chick_6b: textures.cpp
	$(CC) $(CFLAGS) -D OPTION=\"step_6b\" -D IMAGE=\"chick\" -o $(EXECFOLDER)/$@ $<
textures_chick_6c: textures.cpp
	$(CC) $(CFLAGS) -D OPTION=\"step_6c\" -D IMAGE=\"chick\" -o $(EXECFOLDER)/$@ $<

clean:
	$(RM) $(NAME:=.dSYM) $(NAME:=.o)
distclean: clean
	$(RM) $(ALLPROGS) $(addprefix $(EXECFOLDER)/, $(ALLPROGS))
