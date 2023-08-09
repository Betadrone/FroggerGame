#pragma once
//==============================================================================

#ifndef _CAPP_H_
#define _CAPP_H_

#define TICK_INTERVAL    10
#define NUM_SPRITES     3
#define MAX_SPEED       1
#define NUM_SCROLL_SPRITES  5
#define NUM_LOGS        10
#define NUM_GOALS       5

#include <string.h>
#include <cstdio>
#include <stdlib.h>
#include <time.h>

#include "mywindow.h"
#include "SDL.h"
#include "CPlayer.h"
#include "CScroll_Player.h"

#include <SDL_image.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>

//==============================================================================

class CApp
{

    //In C++, there are three access specifiers :

    //public	- members are accessible from outside the class
    //private	- members cannot be accessed(or viewed) from outside the class
    //protected - members cannot be accessed from outside the class, however, they can be accessed in inherited classes.

    // Default value - private

private:
    bool            Running;

    Uint32 next_time;
    SDL_Window* window;
    SDL_Renderer* renderer;
    CPlayer allplayers[NUM_SPRITES];
    CPlayer obstacles[NUM_SPRITES];
    CPlayer obstacles2[NUM_SPRITES];
    CPlayer obstacles3[NUM_SPRITES];
    CPlayer obstacles4[NUM_SPRITES];
    CPlayer logs[NUM_LOGS];
    CPlayer console;
    
    TTF_Font* ourFont; //font object we will use for the message
    SDL_Color color; //color of the message
    char message[100]; //the message string
    SDL_Surface* messageSurface; //surface that stores the message
    SDL_Texture* messageTexture; //surface is converted to a texture
    SDL_Rect messageRect; //location of the message

    //The music that will be played
    Mix_Music* gMusic = NULL;
    //Four short sound effects that will be used
    Mix_Chunk* gOver = NULL;
    Mix_Chunk* gSpinJump = NULL;
    Mix_Chunk* gJump = NULL;
    Mix_Chunk* gGoal = NULL;

    CPlayer goals[NUM_GOALS];
    CPlayer frog;
    CPlayer* p_frog = &frog;
    CPlayer* p_goals = goals;

    CScroll_Player waves[NUM_SCROLL_SPRITES];

public:
    CApp();
    Uint32 time_left(void);
    int OnExecute();

public:
    bool OnInit();
    bool loadMedia();

    void OnEvent(SDL_Event* Event);

    void OnLoop();

    void OnRender();
    int LoadSprite(char* file, SDL_Texture** psprite, SDL_Rect* prect);
    void MoveSprites();

    void OnCleanup();

    void displayScore(int x, int y, const char* formattedString, int number);

    static void checkGoal(CPlayer* frog, CPlayer* console, SDL_Renderer* renderer, Mix_Chunk* gGoal, Mix_Chunk* gOver);

};

//==============================================================================

#endif
