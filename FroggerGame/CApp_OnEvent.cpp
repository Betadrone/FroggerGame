//==============================================================================
#include "CApp.h"

//==============================================================================
void CApp::OnEvent(SDL_Event* Event) {
    if (Event->type == SDL_QUIT || Event->type == SDL_KEYDOWN) {
        
        switch (Event->key.keysym.sym)
        {
            case SDLK_UP:
            {
                frog.position.y -= 49;
                if (!(frog.position.y <= 121))
                {
                    frog.addScore(10);
                }

                strncpy_s(frog.imagename, "frog1.bmp", 255);
                frog.loadPlayer(renderer);

                Mix_PlayChannel(-1, gJump, 0);

                break;
            }
            case SDLK_DOWN:
            {
                frog.position.y += 49;
                if (!(frog.position.y >= (window_h - (frog.position.h + 50))))
                {
                    frog.addScore(-10);
                }
                
                strncpy_s(frog.imagename, "frogD.bmp", 255);
                frog.loadPlayer(renderer);

                Mix_PlayChannel(-1, gJump, 0);

                break;
            }
            case SDLK_RIGHT:
            {
                frog.position.x += 49;
                strncpy_s(frog.imagename, "frogR.bmp", 255);
                frog.loadPlayer(renderer);

                Mix_PlayChannel(-1, gJump, 0);

                break;
            }
            case SDLK_LEFT:
            {
                frog.position.x -= 49;
                strncpy_s(frog.imagename, "frogL.bmp", 255);
                frog.loadPlayer(renderer);

                Mix_PlayChannel(-1, gJump, 0);

                break;
            }
            case SDLK_0:
            {
                //If music is being played
                //If the music is paused
                if (Mix_PausedMusic() == 1) {
                    //Resume the music
                    Mix_ResumeMusic();
                }
                //If the music is playing
                else {
                    //Pause the music
                    Mix_PauseMusic();
                }
                break;
            }
            default:
            {
                Running = false;
                break;
            }
        }

        if (frog.position.x >= window_w - frog.position.w)
        {
            frog.position.x = window_w - frog.position.w;
        }
        if (frog.position.x <= 0)
        {
            frog.position.x = 0;
        }
        if (frog.position.y >= window_h - frog.position.h - 50)
        {
            frog.position.y = window_h - frog.position.h - 50;
        }
        if (frog.position.y <= 50)
        {
            frog.position.y = 50;
        }

        
    }
}

//==============================================================================
