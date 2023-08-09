//==============================================================================
#include "CApp.h"
//==============================================================================

void CApp::MoveSprites()
{
    int i;

    /* Draw a gray background */

    /* Move the sprite, bounce at the wall, and draw */
    for (i = 0; i < NUM_SPRITES; ++i)
    {
        allplayers[i].move(610);
        allplayers[i].display(renderer);

        obstacles[i].move(560, false);
        obstacles[i].display(renderer);

        obstacles2[i].move(510);
        obstacles2[i].display(renderer);

        obstacles3[i].move(465, false);
        obstacles3[i].display(renderer);

        obstacles4[i].move(418);
        obstacles4[i].display(renderer);

        for (int i = 0; i < NUM_SPRITES; i++)
        {
            if (frog.check_collision(frog.position, allplayers[i].position) == true)
            {
                frog.ResetF(-10);
                Mix_PlayChannel(-1, gOver, 0);
                frog.death();
            }

            if (frog.check_collision(frog.position, obstacles2[i].position) == true)
            {
                frog.ResetF(-30);
                Mix_PlayChannel(-1, gOver, 0);
                frog.death();
            }

            if (frog.check_collision(frog.position, obstacles3[i].position) == true)
            {
                frog.ResetF(-40);
                Mix_PlayChannel(-1, gOver, 0);
                frog.death();
            }

        }

        for (int i = 0; i < 2; i++)
        {
            if (frog.check_collision(frog.position, obstacles[i].position) == true)
            {
                frog.ResetF(-20);
                Mix_PlayChannel(-1, gOver, 0);
                frog.death();
            }

            if (frog.check_collision(frog.position, obstacles4[i].position) == true)
            {
                frog.ResetF(-50);
                Mix_PlayChannel(-1, gOver, 0);
                frog.death();
            }
        }
    }
    
    for (i = 0; i < NUM_LOGS; i++)
    {
        if (i > -1 && i < 2)
        {
            logs[i].move(315);
            logs[i].display(renderer);
        }
        else if (i >= 2 && i < 4)
        {
            logs[i].move(267, false);
            logs[i].display(renderer);
        }
        else if (i >= 4 && i < 6)
        {
            logs[i].move(219);
            logs[i].display(renderer);
        }
        else if (i >= 6 && i < 8)
        {
            logs[i].move(171, false);
            logs[i].display(renderer);
        }
        else if (i >= 8 && i < 10)
        {
            logs[i].move(123);
            logs[i].display(renderer);
        }
    }

    // If frog enters water zone, check if it is on a log.
    // If yes, make the frog x velocity equal to the log velocity
    // or else reset the frog back at spawn point
    if (frog.position.y >= 122 && frog.position.y <= 363)
    {

        if(frog.check_collision(frog.position, logs[0].position))
        { 
            frog.velocity.x = logs[0].velocity.x;
        }
        else if (frog.check_collision(frog.position, logs[1].position))
        {
            frog.velocity.x = logs[1].velocity.x;
        }
        else if (frog.check_collision(frog.position, logs[2].position))
        {
            frog.velocity.x = logs[2].velocity.x;
        }
        else if (frog.check_collision(frog.position, logs[3].position))
        {
            frog.velocity.x = logs[3].velocity.x;
        }
        else if (frog.check_collision(frog.position, logs[4].position))
        {
            frog.velocity.x = logs[4].velocity.x;
        }
        else if (frog.check_collision(frog.position, logs[5].position))
        {
            frog.velocity.x = logs[5].velocity.x;
        }
        else if (frog.check_collision(frog.position, logs[6].position))
        {
            frog.velocity.x = logs[6].velocity.x;
        }
        else if (frog.check_collision(frog.position, logs[7].position))
        {
            frog.velocity.x = logs[7].velocity.x;
        }
        else if (frog.check_collision(frog.position, logs[8].position))
        {
            frog.velocity.x = logs[8].velocity.x;
        }
        else if (frog.check_collision(frog.position, logs[9].position))
        {
            frog.velocity.x = logs[9].velocity.x;
        }
        else if (frog.position.y >= 314 && frog.position.y < 363)
        {
            frog.ResetF(-70);
            Mix_PlayChannel(-1, gOver, 0);
            frog.death();
        }
        else if (frog.position.y >= 266 && frog.position.y < 314)
        {
            frog.ResetF(-80);
            Mix_PlayChannel(-1, gOver, 0);
            frog.death();
        }
        else if (frog.position.y >= 218 && frog.position.y < 266)
        {
            frog.ResetF(-90);
            Mix_PlayChannel(-1, gOver, 0);
            frog.death();
        }
        else if (frog.position.y >= 170 && frog.position.y < 218)
        {
            frog.ResetF(-100);
            Mix_PlayChannel(-1, gOver, 0);
            frog.death();
        }
        else if (frog.position.y >= 122 && frog.position.y < 170)
        {
            frog.ResetF(-110);
            Mix_PlayChannel(-1, gOver, 0);
            frog.death();
        }
    }
    else // This makes sure that when off of the logs, the frog does not continue moving left or right
    {
        frog.velocity.x = 0;
    }
}

//==============================================================================

void CApp::checkGoal(CPlayer* frog, CPlayer* goal, SDL_Renderer* renderer, Mix_Chunk* gGoal, Mix_Chunk* gOver)
{
    //this function will check if the frog sprite has touched one of the five goals.
    //if yes: the goal will be turned off, and an x picture bmp will be placed.
    //if no: the goal will remain turned on.
    //player gets ponit bonus when all goals have been conquered.
    
    // If frog reaches the end of the map, check if it enters any goal's range
    if (frog->position.y <= 121)
    {

        if ((frog->position.x >= 36 && frog->position.x <= 90) && (frog->position.y >= 63 && frog->position.y <= 110))
        {
            frog->ResetF();
            if (goal->activeGoal)
            {
                Mix_PlayChannel(-1, gGoal, 0);
                //gain 40 points
                frog->addScore(40);
                //place cross on it to indicate that it is conquered
                strncpy_s(goal->imagename, "conquered.bmp", 255);

                goal->loadPlayer(renderer);
                goal->position.x = 36;
                goal->position.y = 63;
                goal->activeGoal = false;
            }
        }
        else if ((frog->position.x >= 176 && frog->position.x <= 230) && (frog->position.y >= 61 && frog->position.y <= 111))
        {
            frog->ResetF();
            goal+=1;
            if (goal->activeGoal)
            {
                Mix_PlayChannel(-1, gGoal, 0);
                //gain 40 points
                frog->addScore(40);
                //place cross on it
                strncpy_s(goal->imagename, "conquered.bmp", 255);

                goal->loadPlayer(renderer);
                goal->position.x = 176;
                goal->position.y = 61;
                goal->activeGoal = false;
            }
        }
        else if ((frog->position.x >= 306 && frog->position.x <= 360) && (frog->position.y >= 60 && frog->position.y <= 113))
        {
            frog->ResetF();
            goal += 2;
            if (goal->activeGoal)
            {
                Mix_PlayChannel(-1, gGoal, 0);
                //gain 40 points
                frog->addScore(40);
                //place cross on it
                strncpy_s(goal->imagename, "conquered.bmp", 255);

                goal->loadPlayer(renderer);
                goal->position.x = 306;
                goal->position.y = 60;
                goal->activeGoal = false;
            }
        }
        else if ((frog->position.x >= 447 && frog->position.x <= 501) && (frog->position.y >= 59 && frog->position.y <= 112))
        {
            frog->ResetF();
            goal += 3;
            if (goal->activeGoal)
            {
                Mix_PlayChannel(-1, gGoal, 0);
                //gain 40 points
                frog->addScore(40);
                //place cross on it
                strncpy_s(goal->imagename, "conquered.bmp", 255);

                goal->loadPlayer(renderer);
                goal->position.x = 447;
                goal->position.y = 59;
                goal->activeGoal = false;
            }
        }
        else if ((frog->position.x >= 581 && frog->position.x <= 638) && (frog->position.y >= 58 && frog->position.y <= 112))
        {
            frog->ResetF();
            goal += 4;
            if (goal->activeGoal)
            {
                Mix_PlayChannel(-1, gGoal, 0);
                //gain 40 points
                frog->addScore(40);
                //place cross on it
                strncpy_s(goal->imagename, "conquered.bmp", 255);

                goal->loadPlayer(renderer);
                goal->position.x = 581;
                goal->position.y = 58;
                goal->activeGoal = false;
            }
        }
        else
        {
            frog->ResetF();
            Mix_PlayChannel(-1, gOver, 0);
            frog->death();
        }
    }

    // Check to see if all goals have been conquered
    // If yes, then re-initiate them and grant the player a bonus
    // If no, then continue on with normal code
    if (!(goal->activeGoal) && !((goal + 1)->activeGoal) && !((goal + 2)->activeGoal) && !((goal + 3)->activeGoal) && !((goal + 4)->activeGoal))
    {
        for (int i = 0; i < NUM_GOALS; i++)
        {
            strncpy_s((goal + i)->imagename, "empty.bmp", 255);
            (goal + i)->loadPlayer(renderer);

            (goal + i)->activeGoal = true;
        }
        printf("all goals conquered... Bonus points granted...");
        frog->addScore(200);
    }

}

//==============================================================================

void CApp::OnLoop()
{
    SDL_SetRenderDrawColor(renderer, 0xA0, 0xA0, 0xA0, 0xFF);
    SDL_RenderClear(renderer);


    console.display(renderer);
    for (int i = 0; i < NUM_SCROLL_SPRITES; i++)
    {
        waves[i].move();
        waves[i].display(renderer);
    }
    MoveSprites();
    frog.move();
    CApp::checkGoal(p_frog, p_goals, renderer, gGoal, gOver);
    frog.display(renderer);

    for (int i = 0; i < 5; i++)
    {
        goals[i].display(renderer);
    }

    displayScore(0, 0, "Your Score: %i", frog.getBestScore());
    displayScore(0, 698, "Lives Remaining: %i", frog.getLivesCount());

    if (frog.getLivesCount() == 0)
    {
        printf("Game Over!\nYour Score: %i", frog.getBestScore());
        Running = false;
    }
}

//==============================================================================

void CPlayer::ResetF(int scoreToAdd)
{
    SDL_Rect* p;
    SDL_Rect* v;

    p = &position;
    v = &velocity;

    p->y = window_h - (p->h + 50);
    p->x = (window_w / 2) - (p->w / 2);

    v->x = 0;
    v->y = 0;

    addScore(scoreToAdd);
}

void CPlayer::Reset(int yCoordinate, bool left)
{
    SDL_Rect* p;
    SDL_Rect* v;

    p = &position;
    v = &velocity;

    p->y = yCoordinate;

    if (left == false)
    {
        p->x = 0 - p->w;
        v->x = 1;
    }
    else 
    {
        p->x = window_w;
        v->x = -1;
    }
}

bool CPlayer::check_collision(SDL_Rect A, SDL_Rect B)
{
    //The sides of the rectangles
    int leftA, leftB;
    int rightA, rightB;
    int topA, topB;
    int bottomA, bottomB;

    //Calculate the sides of rect A 
    leftA = A.x;
    rightA = A.x + A.w;
    topA = A.y;
    bottomA = A.y + A.h;

    //Calculate the sides of rect B 
    leftB = B.x;
    rightB = B.x + B.w;
    topB = B.y;
    bottomB = B.y + B.h;

    //If any of the sides from A are outside of B 
    if (bottomA <= topB)
    {
        return false;
    }
    if (rightA <= leftB)
    {
        return false;
    }
    if (leftA >= rightB)
    {
        return false;
    }
    if (topA >= bottomB)
    {
        return false;
    }

    //If none of the sides from A are outside B 
    return true;
}

