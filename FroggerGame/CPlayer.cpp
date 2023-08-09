//==============================================================================
#include "CPlayer.h"
//==============================================================================

int CPlayer::loadPlayer(SDL_Renderer* renderer)
{
    SDL_Surface* temp;

    /* Load the sprite image */
    temp = SDL_LoadBMP(imagename);
    if (temp == NULL)
    {
        fprintf(stderr, "Couldn't load %s: %s\n", imagename, SDL_GetError());
        return (-1);
    }

    position.w = temp->w;
    position.h = temp->h;

    /* Set transparent pixel as the pixel at (0,0) */
    if (temp->format->palette)
    {
        SDL_SetColorKey(temp, SDL_TRUE, *(Uint8*)temp->pixels);
    }
    else
    {
        switch (temp->format->BitsPerPixel)
        {
        case 15:
            SDL_SetColorKey(temp, SDL_TRUE,
                (*(Uint16*)temp->pixels) & 0x00007FFF);
            break;
        case 16:
            SDL_SetColorKey(temp, SDL_TRUE, *(Uint16*)temp->pixels);
            break;
        case 24:
            SDL_SetColorKey(temp, SDL_TRUE,
                (*(Uint32*)temp->pixels) & 0x00FFFFFF);
            break;
        case 32:
            SDL_SetColorKey(temp, SDL_TRUE, *(Uint32*)temp->pixels);
            break;
        }
    }

    /* Create textures from the image */
    texture = SDL_CreateTextureFromSurface(renderer, temp);
    if (!texture)
    {
        fprintf(stderr, "Couldn't create texture: %s\n", SDL_GetError());
        SDL_FreeSurface(temp);
        return (-1);
    }

    SDL_FreeSurface(temp);

    /* We're ready to roll. :) */
    return (0);
}

//==============================================================================

void CPlayer::display(SDL_Renderer* renderer)
{
    SDL_RenderCopy(renderer, texture, NULL, &position);
}

//==============================================================================

void CPlayer::move(int ypos, bool left)
{
    SDL_Rect* p;
    SDL_Rect* v;

    p = &position;
    v = &velocity;

    if (left == false)
    {
        v->x = 2;
    }
    else
    {
        v->x = -1;
    }

    p->x += v->x;
    if ((p->x < (0 - p->w * 7)) || (p->x >= (window_w + (p->w * 5))))
    {
        v->x = -v->x;
        p->x += v->x;
    }

    p->y += v->y;
    if ((p->y < 0) || (p->y >= (window_h - p->h)))
    {
        v->y = -v->y;
        p->y += v->y;
    }

    if (left == false)
    {
        if (p->x >= window_w)
        {

            Reset(ypos, false); // brings the projectiles back to the top
        }
    }
    else
    {
        if (p->x <= (0 - p->w))
        {

            Reset(ypos); // brings the projectiles back to the top
        }
    }
}

void CPlayer::move()
{
    SDL_Rect* p;
    SDL_Rect* v;

    p = &position;
    v = &velocity;

    p->x += v->x;
    if ((p->x < 0) || (p->x >= (window_w - p->w)))
    {
        v->x = -v->x;
        p->x += v->x;
    }

    p->y += v->y;
    if ((p->y < 0) || (p->y >= (window_h - p->h)))
    {
        v->y = -v->y;
        p->y += v->y;
    }
}

//==============================================================================