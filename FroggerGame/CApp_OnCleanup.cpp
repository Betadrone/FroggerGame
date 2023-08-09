//==============================================================================
#include "CApp.h"

//==============================================================================
void CApp::OnCleanup() {
    //SDL_FreeSurface(Surf_Display);
    TTF_CloseFont(ourFont);
    TTF_Quit();

    //Free the sound effects
    Mix_FreeChunk(gOver);
    Mix_FreeChunk(gSpinJump);
    Mix_FreeChunk(gJump);
    Mix_FreeChunk(gGoal);
    gOver = NULL;
    gSpinJump = NULL;
    gJump = NULL;
    gGoal = NULL;
    //Free the music
    Mix_FreeMusic(gMusic);
    gMusic = NULL;

    Mix_Quit();
    SDL_Quit();
}

//==============================================================================
