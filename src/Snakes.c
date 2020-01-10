
#include "Snakes.h"
#include "Parameters.h"
#include "Colors.h"
#include "Tutorial.h"
#include "raylib.h"
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <time.h>


void InitDemoScreen(Game* demoScreen , int w, int h)
{
    Player demo;
    InitPlayer(&demo,0,w , h, true, demoScreen->GameMode);
    demo.KeyDash = 32;
    demo.KeyLeft = 32;
    demo.KeyRight = 32;
    for (int i=0; i<MAX_SNAKE; i++)
    {
        InitSnake(&(demo.ControledSnake[i]),rand()%4,w,h,demoScreen->GameMode );
        demo.ControledSnake[i].FramesInHurt = 0; //we desactivate invulnerability at spawn to avoid flashing color
    }
    demo.SnakeNumber = MAX_SNAKE;
    demoScreen->PlayerCount = 1;
    demoScreen->Players[0] = demo;
    demoScreen->GameMode = NORMAL;
}

void UpdateDemoScreen(Game* demoScreen, int w, int h)
{
    UpdateSnakes(demoScreen);
    for (int i=0; i<MAX_SNAKE; i++)
    {
        UpdateDummySnake(&demoScreen->Players[0].ControledSnake[i],w,h);
    }
}

void DrawScores(Game* game, int h, int w)
{
    char score[10];
    for (int i=0;i<game->PlayerCount;i++)
    {
        sprintf(score,"%d",game->Players[i].Score);
        switch (i)
        {
            case 0: DrawText(score,w/4,h/4,80,BODY_COLORS[i]);break;
            case 1: DrawText(score,3*w/4,3*h/4,80,BODY_COLORS[i]);break;
            case 2: DrawText(score,w/4,3*h/4,80,BODY_COLORS[i]);break;
            case 3: DrawText(score,3*w/4,h/4,80,BODY_COLORS[i]);break;
            default: printf("Error: to much players"); exit(-1);
        }
    }
}

void InitSnake(Snake * snake, int num, int w, int h, Mode mode)
{
    snake->BodyColor = BODY_COLORS[num];
    snake->Dead = 0;
    if (mode == NORMAL) //the direction is random in normal mode
    {
        snake->Direction = ((float) (rand()%6283)) / 1000;
    }
    if (mode == COURSE) //If the mode if course, all snakes begi in the right direction to avoid instant death
    {
        snake->Direction = 0;
    }

    snake->FrameCount = 1;
    snake->FramesInHurt = 180; //Begining with 3 sec of invulnerability
    snake->HeadColor = HEAD_COLORS[num];
    snake->InDash = 0;
    snake->Length = 0;
    snake->MaxLength = INIIAL_LENGTH;
    Vector2 RandomVector = {rand()%MAX_DISTANCE - MAX_DISTANCE/2, rand()%MAX_DISTANCE - MAX_DISTANCE/2};
    Vector2 InitPos;
    switch (num)
    {
        case 0: InitPos.x = w/4; InitPos.y =  h/4; break;
        case 1: InitPos.x = 3*w/4; InitPos.y = 3*h/4; break;
        case 2: InitPos.x = w/4; InitPos.y = 3*h/4; break;
        case 3: InitPos.x = 3*w/4; InitPos.y = h/4; break;
        default: printf("Invalid argument") ; exit(-1);
    }
    InitPos.x += RandomVector.x;
    InitPos.y += RandomVector.y;
    snake->Position = InitPos;
    snake->RandomSeed = time(NULL)/(rand()%100+1);
    snake->RotSpeed = REGULAR_ROT_SPEED;
    snake->Speed = REGULAR_SPEED;
    snake->UpdatedFrameCount = 1;
    snake->Width = INITIAL_WIDTH;
    snake->Dummy = false;
}

void InitPlayer(Player * player, int num, int w, int h, bool FirstTime, Mode mode)
{
    Snake snake;
    InitSnake(&snake,num, w, h, mode);

    player->BodyColor = BODY_COLORS[num];
    player->HeadColor = HEAD_COLORS[num];
    player->SnakeNumber = 1;
    player->ControledSnake[0] = snake;
    player->ScoreUpdated = false;
    if (FirstTime)
    {
        player->Score = 0;
//We set the score to 0 for the first time but next we update it so at the begining of a new match we don't want to reset it
    }

}

int UpdatePlayer(Player* player, Mode mode) //Fonction qui met à jour les positions des snakes d'un joueur
{
    Snake* snake;
    //BodyPart bp;
    for (int i = 0; i<player->SnakeNumber; i++) //On update tous les snakes controlés par le joueur
    {

        snake = &((player->ControledSnake)[i]);
        UpdateColor(snake);

        if (snake->MaxLength <=0)
        {
            snake->Dead = 1;
        }

        if (snake->Dead == 0)
        {
            if (snake->FramesInHurt >0)
            {
                snake->FramesInHurt --;
            }

            if ( ((snake->InDash == 0) && ( ((float) snake->UpdatedFrameCount) / ((float) snake->FrameCount) < ((float)REGULAR_SPEED)/((float)DASH_SPEED) )) || snake->InDash)
            {


                if (snake->InDash == 0)
                {
                    snake->UpdatedFrameCount ++;
                }

                if (snake->Length >= snake->MaxLength)
                {
                    snake->Length = snake->MaxLength;

                    for(int j=snake->Length-1 ; j>0 ; j--)
                    {
                        snake->Body[j].Position = snake->Body[j-1].Position;
                    }
                    snake->Body[0].Position = snake->Position;

                }
                else
                {

                    BodyPart bp = { snake->Position, snake->Width, CloseRandomColor(snake->BodyColor,snake->Length, snake->RandomSeed)} ;
                    if (snake->InDash)
                    {
                        bp.PartColor = CloseRandomColor(DASH_COLOR,snake->Length*DASH_COLOR_VARIATION_SPEED, snake->RandomSeed);
                    }

                    for(int j=snake->Length ; j>0 ; j--)
                    {
                        snake->Body[j] = snake->Body[j-1];
                    }
                    snake->Body[0] = bp;
                    snake->Length ++;
                }
            }
            if (snake->InDash == 0)
            {
                snake->FrameCount ++; //when the snake is not in dash, we update the local framecount of the snake.
                //We update the body position just for a fraction of time REGLAR_SPEED/DASH_SPEED
                //This allow us to keep a constant length between dash and non dash time.
            }
            //printf("%d %d %f\n",snake->UpdatedFrameCount, snake->FrameCount, ((float) snake->UpdatedFrameCount) / ((float) snake->FrameCount));

            if (IsKeyDown(player->KeyLeft))
            {
                snake->Direction -= snake->RotSpeed;
            }
            if (IsKeyDown(player->KeyRight))
            {
                snake->Direction += snake->RotSpeed;
            }

            if (IsKeyPressed(player->KeyDash))
            {
                snake->InDash = 1;

            }
            if (snake->InDash)
            {
                snake->Speed = DASH_SPEED;
                snake->RotSpeed = DASH_ROT_SPEED;
            }

            if (IsKeyReleased(player->KeyDash))
            {
                snake->InDash = 0;
                snake->Speed = REGULAR_SPEED;
                snake->RotSpeed = REGULAR_ROT_SPEED;
            }

            if (snake->InDash && !snake->Dummy) //to show the effect of collision on a dshing snake, dummy snake are dashing without loss of length
            {
                if (rand()%LENGTH_LOSS_SPEED == 0)
                {
                    snake->Length --; // random to reduce length loss speed
                    snake->MaxLength --;
                }
            }

            snake->Position.x += (snake->Speed)*cos(snake->Direction);
            snake->Position.y += (snake->Speed)*sin(snake->Direction);
            ///MODE COURSE TEST
            if (mode == COURSE) //Snakes drift to the left if this is  course
            {
                snake->Position.x -= REGULAR_SPEED;
                for (int i =0; i<snake->Length; i++)
                {
                    snake->Body[i].Position.x -= REGULAR_SPEED;
                }
            }

            ///END MODE COURSE TEST
        }
        else
        {
            snake->FramesInHurt = 0; //If the snake is dead, it's no longer invulnerable
        }

    }

    return 0;
}

int DrawSnake(Snake* snake)
{
    for (int i =0; i<snake->Length; i++)
    {
        DrawCircleV(snake->Body[i].Position,snake->Body[i].Radius,snake->Body[i].PartColor);
    }

    DrawCircleV(snake->Position,snake->Width,snake->HeadColor);

    return 0;
}

int DrawAllSnakes(Game* game)
{
    for (int i = 0; i<game->PlayerCount; i++)
    {
        for (int j=0; j<game->Players[i].SnakeNumber; j++)
        {
            DrawSnake(&(game->Players[i].ControledSnake[j]));
        }
    }
    return 0;
}

int CollisionSnakes(Snake snake1,Snake snake2)
{
    int contact = 0;
    for (int i = ((int) snake1.Width)/2 +1 ; i<snake1.Length; i++) //on ne teste que s'il y a un contact tête / corps. S'il y a un contact tête/tête, il ne se passe rien.
                                                        // Cela permet de tester aussi si un Snake est en collision avec son propre corps
    {
        if (CheckCollisionCircles(snake1.Body[i].Position, snake1.Body[i].Radius, snake2.Position, snake2.Width))
        {
            contact = i;
        }
    }
    return contact; //if no collision : contact = 0, else, contact is the position of the collision
}

///TODO : minimum length to create a living snake
///Debug

Snake CreateNewSnake(Snake snake)
{
    Snake newSnake;
    newSnake.BodyColor = snake.BodyColor;
    newSnake.Dead = snake.Dead; //If we cut a dead snake, the resultant snake are also dead
    newSnake.Direction = snake.Direction;

    newSnake.FrameCount = snake.FrameCount;
    newSnake.FramesInHurt = snake.FramesInHurt;
    newSnake.HeadColor = snake.HeadColor;
    newSnake.InDash = snake.InDash;
    newSnake.Length = 0;
    newSnake.MaxLength = 0;
    //newSnake.Position;
    newSnake.RandomSeed = snake.RandomSeed;
    newSnake.RotSpeed = snake.RotSpeed;
    newSnake.Speed = snake.Speed;
    newSnake.UpdatedFrameCount = snake.UpdatedFrameCount;
    newSnake.Width = snake.Width;
    newSnake.Dummy = snake.Dummy;
    return newSnake;

}


int CheckForCuts(Snake snake, Player* player, int snakeIndex) //If there is a hurt, we check for a (or several) cut in the snake
//Each living connexe part become a new snake alive. The dead parts became dead leftover
{
    Snake newSnake = CreateNewSnake(snake); //A copy of snake but Dead, Position, Length and MaxLength still must be assigned
    newSnake.Position = snake.Position;

    player->ControledSnake[snakeIndex] = player->ControledSnake[player->SnakeNumber-1];
    player->ControledSnake[player->SnakeNumber-1] = snake; //we place the current snake at the end of the list in order to easily add new snakes

    bool InLeftOver = (snake.Body[0].Radius <= 0);
    if (InLeftOver)
    {
        newSnake.Dead = 1; //If the head is part of a dead snake
    }

    int newSnakeBegining = 0;

    for (int i=0; i<snake.Length; i++)
    {

        if (InLeftOver && (snake.Body[i].Radius > 0) )
        {
            InLeftOver = false;
            newSnake.Length = i - newSnakeBegining;
            newSnake.MaxLength = i - newSnakeBegining;
            newSnake.Dead = 1;
            if (player->SnakeNumber < MAX_SNAKE)
            {
                player->ControledSnake[player->SnakeNumber-1] = newSnake;
                player->SnakeNumber ++;
            }

            newSnakeBegining = i;
            newSnake = CreateNewSnake(snake);
            newSnake.Position = snake.Body[i].Position;
        }

        if (snake.Body[i].Radius <= 0 && (!InLeftOver))
        {
            InLeftOver = true;
            newSnake.Length = i - newSnakeBegining;
            newSnake.MaxLength = i - newSnakeBegining;

            if (player->SnakeNumber < MAX_SNAKE)
            {
                player->ControledSnake[player->SnakeNumber-1] = newSnake;
                player->SnakeNumber ++;
            }


            newSnake = CreateNewSnake(snake);
            newSnakeBegining = i;
            newSnake.Position = snake.Body[i].Position;
            newSnake.Dead = 1; //The next snake to be created is the dead left over
        }

        newSnake.Body[i-newSnakeBegining] = snake.Body[i];

        if (InLeftOver)
        {
            newSnake.Body[i-newSnakeBegining].Radius = MINIMUM_LEFTOVER_RADIUS; //we reset the width of the snake before the hurt
        }
        //printf("i : %d LeftO : %d\n",i,InLeftOver );
    }

    newSnake.Length = snake.Length - newSnakeBegining;
    newSnake.MaxLength = snake.MaxLength - newSnakeBegining;

    if (player->SnakeNumber < MAX_SNAKE)
    {
        player->ControledSnake[player->SnakeNumber-1] = newSnake;
        //player->SnakeNumber ++;
    }
    return 0;
}



int SnakeHurt(Snake * snake, Player * player, int snakeIndex)
{
    for (int i = 0; i<snake->Length; i++)
    {
        snake->Body[i].Radius -= HURT_WIDTH_REDUCTION;
    }
    snake->Width -= HURT_WIDTH_REDUCTION;
    if (snake->Width <=0)
    {
        snake->Width += HURT_WIDTH_REDUCTION;
    }
    snake->FramesInHurt = INVULNERABILITY_TIME;
    CheckForCuts(*snake,player,snakeIndex);
    return 0;
}

int SnakeLocallyHurt(Snake * snake, Player * player,int snakeIndex, int place)
{
    for (int i=StayInBound(place-IMPACT_WIDTH,0,snake->Length-1); i <= StayInBound(place+IMPACT_WIDTH,0,snake->Length-1); i++)
    {
        snake->Body[i].Radius -= IMPACT_WIDTH_REDUCTION;
    }
    snake->FramesInHurt = INVULNERABILITY_TIME;
    CheckForCuts(*snake,player,snakeIndex);
    return 0;
}

int CollisionAllSnakes(Game* game)
{
    int col = 0;
    for (int j =0; j<game->PlayerCount; j++)
    {
        for (int k = 0; k< game->Players[j].SnakeNumber; k++)
        {
            for (int p =0; p<game->PlayerCount; p++)
            {
                for (int n = 0; n< game->Players[p].SnakeNumber; n++)
                {
                    Snake* snakeHead = &game->Players[p].ControledSnake[n];
                    Snake* snakeBody = &game->Players[j].ControledSnake[k];

                    col = CollisionSnakes(*snakeBody, *snakeHead);

                    if (j==p && k==n && snakeHead->Dummy) //if the snake is dummy, it cannot eat itself, we undo any collision with itself. useful for dummy snakes
                    {
                        col = 0;
                    }

                    if (!(j==p && k==n) && !col) //if we are'nt considering the same snake, we check for head collision
                    {
                        col = col || CheckCollisionCircles(snakeHead->Position,snakeHead->Width,snakeBody->Position,snakeBody->Width);
                    }

                    if (col ) //On teste s'il y a une collision pour toute paire de Snake, y compris des Snake avec eux mêmes
                    {
                        if ((snakeBody->FramesInHurt == 0) && (snakeHead->FramesInHurt == 0) && (!snakeHead->Dead) && !(snakeBody->Dead && snakeHead->InDash)) //snakeBody and snakeHead have invulnerability time if it's hurt
                            //If snakeHead is dashing in a dead body, nothing happen
                        {
                            if (snakeBody->InDash)
                            {
                                SnakeHurt(snakeHead, &game->Players[p],n); //SnakeHead has tried to cut a dashing snake : it's hurt
                            }
                            else
                            {
                                if (snakeHead->InDash)
                                {
                                    SnakeLocallyHurt(snakeBody,&game->Players[j],k,col); //snakeHead dashed in a regular snake : it hurts its body at the spot of the collision
                                }
                                else
                                {
                                    SnakeHurt(snakeHead, &game->Players[p],n); //regular collision : nobody is dashing
                                }
                            }
                        }

                    }

                }
            }

        }
    }
    return 0;
}

int UpdateSnakes(Game* game)
{
    for (int i = 0; i<game->PlayerCount; i++)
    {
        UpdatePlayer(&(game->Players[i]),game->GameMode);
    }
    return 0;
}



int CollisionScreen(Vector2 Position,int w,int h)
{
    if ((0 > Position.x) ||(Position.x  > w))
    {
        return 1;
    }
    if ( (0 > Position.y) || (Position.y > h))
    {
        return 2;
    }
    return 0;
}

int CollisionAllSnakeScreen(Game * game, int w, int h)
{

    for (int j =0; j<game->PlayerCount; j++)
    {
        for (int k = 0; k< game->Players[j].SnakeNumber; k++)
        {
            if (CollisionScreen(game->Players[j].ControledSnake[k].Position,w,h))
            {
                game->Players[j].ControledSnake[k].Dead = 1;
            }
        }
    }
    return 0;
}



int PlayersAlive(Game* game) //return -1 if there is more than one player alive; the number of the last player alive
{
    bool playerAlreadySeen = false;
    int CountAlive = 0;
    int alivePlayer = -2;
    for (int j =0; j<game->PlayerCount; j++)
    {
        playerAlreadySeen  = false;
        for (int k = 0; k< game->Players[j].SnakeNumber; k++)
        {
            if (!game->Players[j].ControledSnake[k].Dead && !playerAlreadySeen)
            {
                playerAlreadySeen = true;
                alivePlayer = j;
                CountAlive ++;
            }
        }
    }
    if (CountAlive > 1)
    {
        return -1;
    }
    else
    {
        return alivePlayer; //if we return -2, no player is alive : it's a draw
    }
}
