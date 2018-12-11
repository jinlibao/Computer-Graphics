// score.h
// Implementation for Color class
// COSC 5450 Project 4
// Libao Jin <ljin1@uwyo.edu>
// Updated date: 12/10/2018

#ifndef SCORE_H
#define SCORE_H

#include "color.h"
#include <string>

class Score {
  public:
    Point position;
    int score;
    int healthPoints;
    Color fontColor;
    string scoreKeeper;

    Score() {
        position.set(0, 0);
        score = 0;
        fontColor.set(1, 1, 1);
    }

    Score(int score, int healthPoints) {
        position.set(0, 0);
        this->score = score;
        this->healthPoints = healthPoints;
        fontColor.set(1, 1, 1);
    }

    Score(float x, float y, int score, int healthPoints) {
        position.set(x, y);
        this->score = score;
        this->healthPoints = healthPoints;
        fontColor.set(1, 1, 1);
    }

    Score(float x, float y, int score, int healthPoints, const Color &fontColor) {
        position.set(x, y);
        this->score = score;
        this->healthPoints = healthPoints;
        this->fontColor.set(fontColor);
    }

    Score(float x, float y, int score, int healthPoints, float r, float g, float b) {
        position.set(x, y);
        this->score = score;
        this->healthPoints = healthPoints;
        this->fontColor.set(r, g, b);
    }

    void set(int score) { this->score = score; }

    void print(bool gameOver = false) {
        char text[100] = "";
        if (gameOver) {
            sprintf(text, "Game Over :(");
            scoreKeeper = text;
            glColor4f(fontColor.r, fontColor.g, fontColor.b, fontColor.a);
            glRasterPos2f(-50, 0);
            glPushMatrix();
            glScalef(20, 20, 0);
            for (int i = 0; i < (int)scoreKeeper.size(); ++i)
                glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, scoreKeeper[i]);
            glPopMatrix();
        }

        sprintf(text, "Score: %d    HP: %d", score, healthPoints);
        scoreKeeper = text;
        glColor4f(fontColor.r, fontColor.g, fontColor.b, fontColor.a);
        glRasterPos2f(position.x, position.y);
        for (int i = 0; i < (int)scoreKeeper.size(); ++i)
            glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, scoreKeeper[i]);
    }
};

#endif
