//==============================================================================
#include "CScroll_Player.h"
//==============================================================================

CScroll_Player::CScroll_Player()
{
    //constructor
}

CScroll_Player::~CScroll_Player()
{
    //destructor
}

//==============================================================================

void CScroll_Player::display(SDL_Renderer* prenderer)
{
    SDL_RenderCopy(prenderer, texture, &src, &destscr);
}

//==============================================================================

int CScroll_Player::loadPlayer(SDL_Renderer* prenderer)
{
    int retval;

    retval = CPlayer::loadPlayer(prenderer);

    destscr.x = 0;
    destscr.y = 0;
    destscr.h = CONSOLE_START_Y;
    destscr.w = window_w;

    // sets the velocity in either the x or y directions (or for both)
    velocity.x = 1;
    velocity.y = 0;

    return (retval);
}

int CScroll_Player::loadPlayer(SDL_Renderer* prenderer, int x, int y, int h, int w)
{
    int retval;

    retval = CPlayer::loadPlayer(prenderer);

    destscr.x = x;
    destscr.y = y;
    destscr.h = h;
    destscr.w = w;

    // sets the velocity in either the x or y directions (or for both)
    velocity.x = 1;
    velocity.y = 0;

    return (retval);
}

//==============================================================================

void CScroll_Player::move()
{
    src.x += velocity.x;
    src.y += velocity.y;

    // if scrolling in the y direction, then flips it up and down
    if (src.y >= position.h - window_h)
    {
        velocity.y = -velocity.y;
        src.y += velocity.y;
    }
    if (src.y < 0)
    {
        velocity.y = -velocity.y;
        src.y += velocity.y;
    }

    //if scrolling in the x direction, then flips it left and right 
    if (src.x >= position.w - window_w)   // Assumes that image is greater than window width..
    {
        velocity.x = -velocity.x;
        src.x += velocity.x;
    }
    if (src.x < 0)
    {
        velocity.x = -velocity.x;
        src.x += velocity.x;
    }

}
//==============================================================================