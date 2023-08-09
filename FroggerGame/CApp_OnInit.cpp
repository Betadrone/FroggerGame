//==============================================================================
#include "CApp.h"
//==============================================================================

bool CApp::OnInit()
{
    int i;

    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0)
    {
        printf("SDL could not initialize! SDL Error: %s\n", SDL_GetError());
        return false;
    }

    if (TTF_Init() < 0)
    {
        printf("%s\n", TTF_GetError());
    }

    ourFont = TTF_OpenFont("lazy.ttf", 32);
    color = { 255, 255, 0 };
    if (ourFont == nullptr)
    {
        printf("Could not load font");
    }

    //Initialize SDL_mixer
    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
    {
        printf("SDL_mixer could not initialize! SDL_mixer Error: %s\n", Mix_GetError());
        //success = false;
    }

    window = SDL_CreateWindow("Frogger Game - Lab 6",
        SDL_WINDOWPOS_UNDEFINED,
        SDL_WINDOWPOS_UNDEFINED,
        WINDOW_WIDTH, WINDOW_HEIGHT,
        SDL_WINDOW_SHOWN);
    if (!window)
    {
        return false;
    }

    renderer = SDL_CreateRenderer(window, -1, 0);
    if (!renderer)
    {
        return false;
    }


    srand(time(NULL));

    //=====================================================================================================

    loadMedia();

    //If there is no music playing
    if (Mix_PlayingMusic() == 0)
    {
        Mix_PlayMusic(gMusic, -1); //Play the music
    }
    
    //======================================================================================================
    // To load in all the cars, the following five for loops are used
    for (i = 0; i < NUM_SPRITES; ++i)
    {
        strncpy_s(allplayers[i].imagename, "car3.bmp", 255);

        allplayers[i].loadPlayer(renderer);
        allplayers[i].position.y = 610;
        allplayers[i].velocity.x = -1;
        allplayers[i].velocity.y = 0;

        if (i == 0)
        {
            allplayers[i].position.x = 400;
        }
        else
        {
            allplayers[i].position.x = allplayers[i - 1].position.x + 170;
        }

    }

    for (i = 0; i < NUM_SPRITES - 1; ++i) 
    {
        strncpy_s(obstacles[i].imagename, "car1.bmp", 255);

        obstacles[i].loadPlayer(renderer);
        obstacles[i].position.y = 560;
        obstacles[i].velocity.x = 1;
        obstacles[i].velocity.y = 0;

        if (i == 0)
        {
            obstacles[i].position.x = 0;
        }
        else
        {
            obstacles[i].position.x = allplayers[i - 1].position.x - (170 + obstacles[i].position.w);
        }

    }

    for (i = 0; i < NUM_SPRITES; ++i)
    {
        strncpy_s(obstacles2[i].imagename, "car4.bmp", 255);

        obstacles2[i].loadPlayer(renderer);
        obstacles2[i].position.y = 510;
        obstacles2[i].velocity.x = 1;
        obstacles2[i].velocity.y = 0;

        if (i == 0)
        {
            obstacles2[i].position.x = 300;
        }
        else
        {
            obstacles2[i].position.x = obstacles2[i - 1].position.x + 170;
        }

    }

    for (i = 0; i < NUM_SPRITES; ++i)
    {
        strncpy_s(obstacles3[i].imagename, "car2.bmp", 255);

        obstacles3[i].loadPlayer(renderer);
        obstacles3[i].position.y = 465;
        obstacles3[i].velocity.x = 1;
        obstacles3[i].velocity.y = 0;

        if (i == 0)
        {
            obstacles3[i].position.x = 200;
        }
        else
        {
            obstacles3[i].position.x = obstacles3[i - 1].position.x - (180 + obstacles3[i].position.w);
        }

    }

    for (i = 0; i < NUM_SPRITES - 1; ++i)
    {
        strncpy_s(obstacles4[i].imagename, "car5.bmp", 255);

        obstacles4[i].loadPlayer(renderer);
        obstacles4[i].position.y = 418;
        obstacles4[i].velocity.x = 1;
        obstacles4[i].velocity.y = 0;

        if (i == 0)
        {
            obstacles4[i].position.x = 50;
        }
        else
        {
            obstacles4[i].position.x = obstacles4[i - 1].position.x + 200;
        }

    }
    
    //======================================================================================================

    for (i = 0; i < NUM_LOGS; ++i) // to load in the logs
    {
        strncpy_s(logs[i].imagename, "Untitled.bmp", 255);

        logs[i].loadPlayer(renderer);
        logs[i].velocity.x = -1;
        logs[i].velocity.y = 0;

        if (i > -1 && i < 2)
        {
            logs[i].position.y = 315;
        }
        else if (i >= 2 && i < 4)
        {
            logs[i].position.y = 267;
        }
        else if (i >= 4 && i < 6)
        {
            logs[i].position.y = 219;
        }
        else if (i >= 6 && i < 8)
        {
            logs[i].position.y = 171;
        }
        else if (i >= 8 && i < 10)
        {
            logs[i].position.y = 123;
        }

        if (i % 2 == 0)
        {
            logs[i].position.x = 25;
        }
        else
        {
            logs[i].position.x = logs[i - 1].position.x + 220;
        }

    }

    //=====================================================================================================
    // loads everything needed for the frogger game background
    strncpy_s(console.imagename, "froggerBackground.bmp", 255);

    console.loadPlayer(renderer);
    console.velocity.x = 0;
    console.velocity.y = 0;
    console.position.x = 0;
    console.position.y = 0;
    
    //========================================================================================================
    
    strncpy_s(frog.imagename, "frog1.bmp", 255);

    frog.loadPlayer(renderer);
    frog.velocity.x = 0;
    frog.velocity.y = 0;
    frog.position.x = (window_w / 2) - (frog.position.w / 2);
    frog.position.y = window_h - (frog.position.h + 50);

    //========================================================================================================

    for (int i = 0; i < NUM_SCROLL_SPRITES; i++)
    {
        strncpy_s(waves[i].imagename, "Wave.bmp", 255);
        if (i == 0)
        {
            waves[i].loadPlayer(renderer, 0, 121, 48); // to load the waves background
        }
        else 
        {
            waves[i].loadPlayer(renderer, 0, (waves[i - 1].destscr.y + waves[i - 1].destscr.h), 48);
        }

        if (i % 2 == 0)
        {
            waves[i].velocity.x += 1;
        }

        waves[i].set_scroll_loc(0, 0, window_w, CONSOLE_START_Y); // to set how you want it to scroll and where from
    }

    return true;
}
//==============================================================================

bool CApp::loadMedia()
{
    //Loading success flag
    bool success = true;

    //Load music
    gMusic = Mix_LoadMUS("8bit-music-for-game-68698.wav");
    if (gMusic == NULL) {
        printf("Failed to load beat music! SDL_mixer Error: %s\n", Mix_GetError());
        success = false;
    }

    //Load sound effects
    gOver = Mix_LoadWAV("mixkit-arcade-retro-game-over-213.wav");
    if (gOver == NULL) {
        printf("Failed to load scratch sound effect! SDL_mixer Error: %s\n", Mix_GetError());
        success = false;
    }
    gSpinJump = Mix_LoadWAV("mixkit-video-game-spin-jump-2648.wav");
    if (gSpinJump == NULL) {
        printf("Failed to load high sound effect! SDL_mixer Error: %s\n", Mix_GetError());
        success = false;
    }
    gJump = Mix_LoadWAV("mixkit-player-jumping-in-a-video-game-2043.wav");
    if (gJump == NULL) {
        printf("Failed to load medium sound effect! SDL_mixer Error: %s\n", Mix_GetError());
        success = false;
    }
    gGoal = Mix_LoadWAV("mixkit-game-flute-bonus-2313.wav");
    if (gGoal == NULL) {
        printf("Failed to load low sound effect! SDL_mixer Error: %s\n", Mix_GetError());
        success = false;
    }
    return success;
}