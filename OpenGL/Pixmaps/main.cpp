// resources for reading and writing file formats...
/* writing bmp files:
 * http://www.etsimo.uniovi.es/hypvis/asp_data/compimag/bmpfile.htm */
/*http://www.opengl.org/resources/faq/technical/miscellaneous.htm*/

#include <fstream>
#include <iostream>

#if defined __APPLE__ && !defined X11
#include <GLUT/glut.h>
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#else
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#endif

const int WIDTH = 640;
const int HEIGHT = 480;
const int BitsPerPixel = 24;
int frameNumber = 1;

using namespace std;

#ifndef STEP
#define STEP "1"
#endif

#ifdef USEFREEIMAGE
#undef USEFREEIMAGE
#define USEFREEIMAGE 1

#include <FreeImage.h>

void saveImage()
{
    FreeImage_Initialise();
    // cout << "FreeImage " << FreeImage_GetVersion() << endl;
    // cout << FreeImage_GetCopyrightMessage() << endl;
    FIBITMAP *bitmap = FreeImage_Allocate(WIDTH, HEIGHT, BitsPerPixel);
    GLfloat pixels[3 * WIDTH * HEIGHT];
    glReadPixels(0, 0, WIDTH, HEIGHT, GL_RGB, GL_FLOAT, pixels);
    RGBQUAD color;
    if (!bitmap) exit(1);
    for (int i = 0; i < WIDTH; ++i) {
        for (int j = 0; j < HEIGHT; ++j) {
            color.rgbRed = pixels[3 * (j * WIDTH + i)] * 255;
            color.rgbGreen = pixels[3 * (j * WIDTH + i) + 1] * 255;
            color.rgbBlue = pixels[3 * (j * WIDTH + i) + 2] * 255;
            FreeImage_SetPixelColor(bitmap, i, j, &color);
        }
    }
    char filename[100] = "";
    sprintf(filename, "../output/pixmaps_%s.png", STEP);
    if (FreeImage_Save(FIF_PNG, bitmap, filename, 0))
        cout << "Image successfully saved: " << filename << endl;
    FreeImage_DeInitialise();
}

#else
#define USEFREEIMAGE 0
void saveImage(){};
#endif

typedef unsigned char uchar;
typedef unsigned short ushort;
typedef unsigned long ulong;

// handy typedefs for grey and RGBA pixels
typedef unsigned char Greypixel;

// typedef unsigned char RGBApixel[4];
struct RGBApixel { // struct from CG book by Hill
    unsigned char r, g, b, a;
};

struct RGGpixel { // struct from CG book by Hill
    unsigned char r, g, b;
};

// globals for 3 different kinds of pixmaps
Greypixel *greymap1d;
Greypixel **greymap2d;
RGBApixel **pixmap2d;
RGGpixel *pixel;

int Width, Height;

//
// drawing callback routine. Uncomment the line to draw the pixmap you want
//
void drawScreen()
{
    glRasterPos2i(0, 0);

    // draw pixmap here
    // step 1- what does this display?
    if (strcmp(STEP, "1") == 0) {
        glDrawPixels(Width, Height, GL_LUMINANCE, GL_UNSIGNED_BYTE, greymap1d);
    }
    else if (strcmp(STEP, "2") == 0) {
        glDrawPixels(Width, Height, GL_LUMINANCE, GL_UNSIGNED_BYTE,
                     greymap2d[0]);
    }
    else if (strcmp(STEP, "3") == 0 || strcmp(STEP, "4a") == 0 ||
             strcmp(STEP, "4b") == 0) {
        glDrawPixels(Width, Height, GL_RGBA, GL_UNSIGNED_BYTE, pixmap2d[0]);
    }
    else if (strcmp(STEP, "5") == 0) {
        int blocksize = 40;
        int m = WIDTH / blocksize;
        int n = HEIGHT / blocksize;
        for (int i = 0; i < m; i = i + 1) {
            for (int j = 0; j < n; j = j + 1) {
                if ((i + j) % 2 == 0) {
                    glColor3f(0.0, 1.0 * (i + j) / (m + n),
                              1.0 * (i + j) / (m + n));
                    glRecti(blocksize * i, blocksize * j, blocksize * (i + 1),
                            blocksize * (j + 1));
                }
                else {
                    glColor3f(1.0 * (i + j) / (m + n), 0.0, 0.0);
                    glRecti(blocksize * i, blocksize * j, blocksize * (i + 1),
                            blocksize * (j + 1));
                }
            }
        }
    }
    // Step 2: comment step 1, and uncomment this next line- what is displayed?
    // glDrawPixels(Width, Height, GL_LUMINANCE, GL_UNSIGNED_BYTE,
    // greymap2d[0]);

    // Step 3: comment step 2, and uncomment this next line- what is displayed?
    //	glDrawPixels(Width, Height, GL_RGBA, GL_UNSIGNED_BYTE, pixmap2d[0]);

    // step 4 is in a different function below

    /* Step 5 - complete the missing code.. use pixmap2d[][], glrecti and loop
       through pixel blocks to display 2d squares to represent pixelblocks int
       blocksize=20; for (int i = 0; i <     ; i=i+    ){ for (int j = 0; j < ;
       j=j+    ){ glColor3f(   ); glRecti(    );
                   }
          }


*/

    if (USEFREEIMAGE) saveImage();
    glFlush();
}

//
//  Open window and start up glut/OpenGL graphics
//
void startgraphics(int width, int height)
{

    // open window and establish coordinate system on it
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA);
    glutInitWindowSize(width, height);
    glutCreateWindow("Pixmap Example");

    glMatrixMode(GL_PROJECTION); // set projection to 2D
    glLoadIdentity();
    gluOrtho2D(0, width, 0, height);
}

int main(int argc, char *argv[])
{
    int row, col;
    Width = WIDTH;
    Height = HEIGHT;

    // get image width and height from command line
    // or error if command line parameters missing
    if (argc >= 3) {
        // usage: pixmaps w h, else default values are being set to 640x 480
        // set default
        Width = atoi(argv[1]);
        Height = atoi(argv[2]);
    }

    // allocate a greymap organized as a 1D array
    greymap1d = new Greypixel[Width * Height];

    // allocate a greymap organized as a 2D array
    greymap2d = new Greypixel *[Height];
    greymap2d[0] = new Greypixel[Width * Height];
    for (row = 1; row < Height; row++)
        greymap2d[row] = greymap2d[row - 1] + Width;

    // allocate a full RGBA pixmap organized as a 2D array
    // allocate a full RGBA pixmap organized as a 2D array
    pixmap2d = new RGBApixel *[Height];
    pixmap2d[0] = new RGBApixel[Width * Height];
    for (row = 1; row < Height; row++)
        pixmap2d[row] = pixmap2d[row - 1] + Width;

    // make checkerboards: grey and red:
    //   if board row + board col is odd, then black,
    //   else white for a greymap or red for a pixmap
    // Step 4a: change the pixel color values for the grid
    // Step 4b: move away from the grid and color your pixmap any pattern or way
    // you wish.
    for (row = 0; row < Height; row++)
        for (col = 0; col < Width; col++)
            if ((row / 8 + col / 8) % 2) {

                // set colors here
                greymap1d[Width * row + col] = 0;
                greymap2d[row][col] = 0;

                if (strcmp(STEP, "4a") == 0) {
                    pixmap2d[row][col].r = 0;
                    pixmap2d[row][col].g = 100;
                    pixmap2d[row][col].b = 0;
                    pixmap2d[row][col].a = 255;
                }
                else {
                    pixmap2d[row][col].r = 0;
                    pixmap2d[row][col].g = 0;
                    pixmap2d[row][col].b = 0;
                    pixmap2d[row][col].a = 255;
                }
            }
            else {

                // set colors here
                greymap1d[Width * row + col] = 255;
                greymap2d[row][col] = 255;

                if (strcmp(STEP, "4a") == 0) {
                    pixmap2d[row][col].r = 0;
                    pixmap2d[row][col].g = 0;
                    pixmap2d[row][col].b = 255;
                    pixmap2d[row][col].a = 255;
                }
                else {
                    pixmap2d[row][col].r = 255;
                    pixmap2d[row][col].g = 0;
                    pixmap2d[row][col].b = 0;
                    pixmap2d[row][col].a = 255;
                }

            }

    // open window and establish coordinate system on it
    glutInit(&argc, argv);
    startgraphics(Width, Height);

    // register display callback routine
    glutDisplayFunc(drawScreen);
    glutMainLoop();

    return 0;
}
