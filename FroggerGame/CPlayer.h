#pragma once
//==============================================================================
#ifndef CPLAYER_H
#define CPLAYER_H

#include <string.h>
#include <cstdio>

#include "mywindow.h"
#include "SDL.h"
//==============================================================================

/* Implement a sprite as a player.... */
class CPlayer
{
public:
    bool loaded;
    char imagename[255];
    bool activeGoal = true;

    SDL_Rect position;
    SDL_Rect velocity;

    CPlayer(const char image[] = "", int x = 0, int y = 0, int vx = 0, int vy = 0)
    {
        strncpy_s(imagename, image, 255);
        position.x = x;
        position.y = y;
        velocity.x = vx;
        velocity.y = vy;
        loaded = false;
    }

    int loadPlayer(SDL_Renderer* prenderer);

    void display(SDL_Renderer* prenderer);
    
    void move();
    virtual void move(int yPos, bool left = true);
    
    virtual void ResetF(int scoreToAdd = 0);
    virtual void Reset(int yCoordinate, bool left = true);

    bool check_collision(SDL_Rect A, SDL_Rect B);

    //define these following 
    int addScore(int num)
    {
        score += num;
        setBestScore();
        return 0;
    }

    int getBestScore()
    {
        return bestScore;
    }

    int death()
    {
        lives -= 1;
        return 0;
    }

    int getLivesCount()
    {
        return lives;
    }
protected:
    SDL_Texture* texture;

private:
    int score = 0;
    int bestScore = 0;
    int lives = 3;

    int setBestScore()
    {
        if (score > bestScore)
        {
            bestScore = score;
        }
        return 0;
    }

};

//==============================================================================

#endif
