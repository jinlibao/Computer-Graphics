
//resources for reading and writing file formats...
/* writing bmp files:  http://www.etsimo.uniovi.es/hypvis/asp_data/compimag/bmpfile.htm */
/*http://www.opengl.org/resources/faq/technical/miscellaneous.htm*/

// Libao Jin
// ljin1@uwyo.edu
// #define X11 X11
#if defined __APPLE__ && !defined X11
#include <OpenGL/gl.h>
// #include <OpenGL/glu.h>
#include <GLUT/glut.h>
#else
#include <GL/gl.h>
// #include <GL/glu.h>
#include <GL/glut.h>
#endif
#include <cstring>
#include <cstdio>
#include <cmath>
#include <FreeImage.h>
#include <iostream>
#include <fstream>

typedef unsigned char uchar;
typedef unsigned short ushort;
typedef unsigned long ulong;

using namespace std;

// handy typedefs for grey and RGBA pixels
typedef unsigned char Greypixel;

fstream inf; // global in this file for convenience

int ROWS, COLS;
//typedef unsigned char RGBApixel[4];
struct RGBApixel { //struct from CG book by Hill
    unsigned char r, g, b, a;
};

struct RGBpixel { //struct from CG book by Hill
    uchar r, g, b;
};

RGBpixel *pixel;

int Width, Height;

#define WIDTH 640
#define HEIGHT 480
#define BitsPerPixel 24

void saveImage() {
    FreeImage_Initialise();
    cout << "FreeImage " << FreeImage_GetVersion() << endl;
    cout << FreeImage_GetCopyrightMessage() << endl;
    FIBITMAP *bitmap = FreeImage_Allocate(WIDTH, HEIGHT, BitsPerPixel);
    GLfloat pixels[3 * WIDTH * HEIGHT];
    glReadPixels(0, 0, WIDTH, HEIGHT, GL_RGB, GL_FLOAT, pixels);
    RGBQUAD color;
    if (!bitmap)
        exit(1);
    for (int i = 0; i < WIDTH; ++i) {
        for (int j = 0; j < HEIGHT; ++j) {
            color.rgbRed = pixels[3 * (j * WIDTH + i)] * 255;
            color.rgbGreen = pixels[3 * (j * WIDTH + i) + 1] * 255;
            color.rgbBlue = pixels[3 * (j * WIDTH + i) + 2] * 255;
            FreeImage_SetPixelColor(bitmap, i, j, &color);
        }
    }
    char filename[100] = "";
    sprintf(filename, "../../output/textures_%s_%s.png", IMAGE, OPTION);
    printf("%s\n", filename);
    if (FreeImage_Save(FIF_PNG, bitmap, filename, 0))
        cout << "Image succesfully saved!\n";
    FreeImage_DeInitialise();
}

void drawScreen() {
    glEnable(GL_TEXTURE_2D);
    glRasterPos2i(0, 0);
    glClear(GL_COLOR_BUFFER_BIT);
    glClearColor(0.0, 0.0, 0.0, 0.0);

    if (strcmp(OPTION, "step_1") == 0)
        glDrawPixels(Width, Height, GL_RGB, GL_UNSIGNED_BYTE, pixel);

    if (strcmp(OPTION, "step_6a") != 0 &&
        strcmp(OPTION, "step_6b") != 0 &&
        strcmp(OPTION, "step_6c") != 0)
        glColor3f(0.0, 0.0, 1.0);

    if (strcmp(OPTION, "step_1") != 0 &&
        strcmp(OPTION, "step_2") != 0) {
        glBindTexture(GL_TEXTURE_2D,2001);
        if (strcmp(OPTION, "step_5") == 0) {
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,GL_NEAREST);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER,GL_NEAREST);
        }
        else {
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,GL_LINEAR);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER,GL_LINEAR);
        }
        if (strcmp(OPTION, "step_6a") == 0) {
            glTexImage2D(GL_TEXTURE_2D,0,GL_RGB,640,480,0,GL_RGB, GL_UNSIGNED_BYTE, pixel);
            glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_REPEAT);
            glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,GL_REPEAT);
        }
        else if (strcmp(OPTION, "step_6b") == 0) {
            glTexImage2D(GL_TEXTURE_2D,0,GL_RGB,640,480,0,GL_RGB, GL_UNSIGNED_BYTE, pixel);
            glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_MIRRORED_REPEAT);
            glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,GL_MIRRORED_REPEAT);
        }
        else if (strcmp(OPTION, "step_6c") == 0) {
            glTexImage2D(GL_TEXTURE_2D,0,GL_RGB,640,480,0,GL_RGB, GL_UNSIGNED_BYTE, pixel);
            glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_CLAMP_TO_EDGE);
            glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,GL_CLAMP_TO_EDGE);
        }
        else {
            glTexImage2D(GL_TEXTURE_2D,0,GL_RGBA,480,480,0,GL_RGBA, GL_UNSIGNED_BYTE, pixel);
        }
    }

    glBegin(GL_QUADS);

    if (strcmp(OPTION, "step_1") == 0 ||
        strcmp(OPTION, "step_2") == 0 ||
        strcmp(OPTION, "step_3a") == 0) {
        // glTexCoord2f(0.0,0.0);
        glVertex2f(100, 250);
        // glTexCoord2f(0.0,1.0);
        glVertex2f(250, 250);
        // glTexCoord2f(1.0,1.0);
        glVertex2f(250, 100);
        // glTexCoord2f(1.0,0.0);
        glVertex2f(100, 100);
    }
    else if (strcmp(OPTION, "step_3b") == 0) {
        // step 3b
        glTexCoord2f(0.0,0.0);
        glVertex2f(100, 250);
        glTexCoord2f(0.0,1.0);
        glVertex2f(250, 250);
        glTexCoord2f(1.0,1.0);
        glVertex2f(250, 100);
        glTexCoord2f(1.0,0.0);
        glVertex2f(100, 100);
    }
    else {
        // step 4, 5, 6a, 6b, 6c
        glTexCoord2f(0.0,0.0);
        glVertex2f(100, 100);
        glTexCoord2f(0.0,2.0);
        glVertex2f(100, 250);
        glTexCoord2f(2.0,2.0);
        glVertex2f(250, 250);
        glTexCoord2f(2.0,0.0);
        glVertex2f(250, 100);
    }

    glEnd();

    saveImage();
    glFlush();
}

//
//  Open window and start up glut/OpenGL graphics
//
void startgraphics(int width, int height) {

    // open window and establish coordinate system on it
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA);
    glutInitWindowSize(width, height);
    char title[100] = "Texture Example - ";
    glutCreateWindow(strcat(title, OPTION));

    glMatrixMode(GL_PROJECTION); //set projection to 2D
    glLoadIdentity();
    gluOrtho2D(0, width, 0, height);
}

//<<<<<<<<<<<<<<<<<<<<< getShort >>>>>>>>>>>>>>>>>>>>
ushort getShort() //helper function
{
    //BMP format uses little-endian integer types
    // get a 2-byte integer stored in little-endian form
    char ic;
    ushort ip;
    inf.get(ic); ip = ic;  //first byte is little one
    inf.get(ic);  ip |= ((ushort)ic << 8); // or in high order byte
    return ip;
}
//<<<<<<<<<<<<<<<<<<<< getLong >>>>>>>>>>>>>>>>>>>
ulong getLong() //helper function
{
    //BMP format uses little-endian integer types
    // get a 4-byte integer stored in little-endian form
    ulong ip = 0;
    char ic = 0;
    unsigned char uc = ic;
    inf.get(ic); uc = ic; ip = uc;
    inf.get(ic); uc = ic; ip |= ((ulong)uc << 8);
    inf.get(ic); uc = ic; ip |= ((ulong)uc << 16);
    inf.get(ic); uc = ic; ip |= ((ulong)uc << 24);
    return ip;
}

int readBMPFile(string fname)
{
    // Read into memory an mRGB image from an uncompressed BMP file.
    // return 0 on failure, 1 on success
    int nRows, nCols;
    nRows = Height;
    nCols = Width;
    ROWS = nRows;
    COLS = nCols;
    pixel = new RGBpixel[Width * Height];

    inf.open(fname.c_str(), ios::in | ios::binary); //read binary char's
    if (!inf) {
        printf(" can't open file: %s\n", fname.c_str());
        return 0;
    }
    int k, row, col, numPadBytes, nBytesInRow;
    // read the file header information
    char ch1, ch2;
    inf.get(ch1); inf.get(ch2);         //type: always 'BM'
    ulong fileSize = getLong();
    ushort reserved1 = getShort();      // always 0
    ushort reserved2 = getShort();      // always 0
    ulong offBits = getLong();          // offset to image - unreliable
    ulong headerSize = getLong();       // always 40
    ulong numCols = getLong();          // number of columns in image
    ulong numRows = getLong();          // number of rows in image
    ushort planes = getShort();         // always 1
    ushort bitsPerPixel = getShort();   //8 or 24; allow 24 here
    ulong compression = getLong();      // must be 0 for uncompressed
    ulong imageSize = getLong();        // total bytes in image
    ulong xPels = getLong();            // always 0
    ulong yPels = getLong();            // always 0
    ulong numLUTentries = getLong();    // 256 for 8 bit, otherwise 0
    ulong impColors = getLong();        // always 0
    if (bitsPerPixel != 24)
    {
        // error - must be a 24 bit uncompressed image
        printf("not a 24 bit/pixelimage, or is compressed!\n");
        inf.close(); return 0;
    }
    //add bytes at end of each row so total # is a multiple of 4
    // round up 3*numCols to next mult. of 4
    nBytesInRow = ((3 * numCols + 3) / 4) * 4;
    numPadBytes = nBytesInRow - 3 * numCols; // need this many
    nRows = numRows; // set class's data members
    nCols = numCols;

    pixel = new RGBpixel[nRows * nCols]; //make space for array
    if (!pixel) return 0; // out of memory!
    long count = 0;
    char dum;
    for (row = 0; row < nRows; row++) // read pixel values
    {
        for (col = 0; col < nCols; col++)
        {
            char r, g, b;
            inf.get(b); inf.get(g); inf.get(r); //read bytes
            pixel[count].r = r; //place them in colors
            pixel[count].g = g;
            pixel[count++].b = b;
        }
        for (k = 0; k < numPadBytes; k++) //skip pad bytes at row's end
            inf >> dum;
    }

    inf.close(); return 1; // success
}

int main(int argc, char *argv[]) {
    int row, col;
    Width = 640;
    Height = 480;

    // get image width and height from command line
    // or error if command line parameters missing
    if (argc >= 3) {
        //usage: pixmaps w h, else default values are being set to 640x 480
        //set default
        Width = atoi(argv[1]);
        Height = atoi(argv[2]);
    }

    // open window and establish coordinate system on it
    glutInit(&argc, argv);
    startgraphics(Width, Height);

    // Step 1: replace with your texture and run, make sure can see it
    char imagefile[100];
    sprintf(imagefile, "../../pics/%s.bmp", IMAGE);
    printf("%s\n", imagefile);
    readBMPFile(imagefile);

    // register display callback routine
    glutDisplayFunc(drawScreen);
    glutMainLoop();

    return 0;
}
