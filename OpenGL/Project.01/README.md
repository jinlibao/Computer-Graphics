# Paint App by Libao Jin

## Compile

The code is developed  on macOS High Sierra. Here is the makefile:

```
# makefile
# Libao Jin, 2018-09-04 11:31
#

CC = clang
CFLAGS = -framework OpenGL -framework GLUT -Wno-deprecated
RM = rm -rf

ALLPROGS = paint

.DEFAULT_GOAL := all

all: $(ALLPROGS)

paint: paint.cpp
	$(CC) $(CFLAGS) -o $@ $<

clean:
	$(RM) $(ALLPROGS:=.dSYM) $(ALLPROGS:=.o)

distclean: clean
	$(RM) $(ALLPROGS)
```

## Functionalities

* Draw: Draw a continuous line with the mouse. First, we need to enter "Drawing Mode" by right click and then press "Drawing mode". Then click the mouse button (and hold), then it would draw the continuous lines. Another way to enter the "Drawing Mode" is to click the brush size button on the toolbar.
* Erase: To enter the "Erase Mode", we need to right click and "Erase Mode".
* Change the size/color/draw filled paint shape (circle, triangle, square, Microsoft Logo). To create a circle, you can try right click and "Draw - Circle" which will draw the circle with the default size 5px. Or you can go to the bottom part of the toolbar, select one of the types and click the left button on the mouse and hold to decide the size of the object.
* A delete tool (needs to be optimized) would delete the content in the selected area.
* Two view ports, one for the toolbar and one for the drawing area.

## To be improved

* The reshape functionality needs to be improved.
