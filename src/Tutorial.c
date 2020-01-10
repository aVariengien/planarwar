#include "Snakes.h"
#include "Fruits.h"
#include "Tutorial.h"
#include "background.h"
#include <math.h>


//extern TUTO_TEXT;


static int TutoStep = 0;

void UpdateDummySnake(Snake * dummy, int w, int h)
{
    int c = CollisionScreen(dummy->Position,w,h); //bonce on wall
    if (c==1)
    {
        dummy->Direction = PI - dummy->Direction;
    }
    if (c==2)
    {
        dummy->Direction = - dummy->Direction;
    }
    if (c != 0)
    {
        dummy->Position.x += dummy->Speed * cos(dummy->Direction);
        dummy->Position.y += dummy->Speed * sin(dummy->Direction);
    }
}

bool UpdateTutorial(Game* tuto, Fruits *fruits, Background *b)
{
    if (IsKeyPressed('r')) //restart step
    {
        InitPlayer(&tuto->Players[0],0,b->Width,b->Height,false,tuto->GameMode);
        InitPlayer(&tuto->Players[1],1,b->Width,b->Height,false,tuto->GameMode);
        InitPlayer(&tuto->Players[2],2,b->Width,b->Height,false,tuto->GameMode);
        tuto->Players[1].ControledSnake[0].Dummy = true;
        tuto->Players[0].ControledSnake[0].MaxLength = TUTORIAL_INITIAL_LENGTH;
    }
    if (IsKeyPressed('a')||IsKeyPressed('q')) //quit but A=Q : azerty/qwerty keyboard ... So I accept both to be sure
    {
        TutoStep = 0;
        return false;
    }
    if (IsKeyPressed('n'))
    {
        TutoStep ++;
        InitPlayer(&tuto->Players[0],0,b->Width,b->Height,false,tuto->GameMode);
        InitPlayer(&tuto->Players[1],1,b->Width,b->Height,false,tuto->GameMode);
        tuto->Players[1].ControledSnake[0].Dummy = true;
        tuto->Players[0].ControledSnake[0].MaxLength = TUTORIAL_INITIAL_LENGTH;
    }
    if (IsKeyPressed(KEY_P)) //Previous step
    {
        if (TutoStep >0)
        {
            TutoStep --;
        }

        InitPlayer(&tuto->Players[0],0,b->Width,b->Height,false,tuto->GameMode);
        InitPlayer(&tuto->Players[1],1,b->Width,b->Height,false,tuto->GameMode);
        tuto->Players[1].ControledSnake[0].Dummy = true;
    }

    UpdateSnakes(tuto);

    for (int r=0; r<tuto->Players[1].SnakeNumber;r++)
    {
        UpdateDummySnake(&tuto->Players[1].ControledSnake[r],b->Width,b->Height);
    }

    CollisionAllSnakeScreen(tuto,b->Width,b->Height);
    switch (TutoStep)
    {
        case 0:
            {
                tuto->PlayerCount = 1;

            } break;
        case 1:
            {
                tuto->PlayerCount = 1;
            } break;
        case 2:
            {
                CollisionAllSnakes(tuto);
                tuto->PlayerCount = 1;
            } break;
        case 3:
            {
                CollisionAllSnakes(tuto);
                tuto->PlayerCount = 2;
            } break;
        case 4:
            {
                CollisionAllSnakes(tuto);
                tuto->PlayerCount = 2;
                for (int i=0; i<tuto->Players[1].SnakeNumber; i++)
                {
                    tuto->Players[1].ControledSnake[i].InDash = 1;

                }
            } break;
        case 5:
            {
                CollisionAllSnakes(tuto);
                tuto->PlayerCount = 3; //we add a player that will crash on a wall to experiment with dead body
            } break;
        case 6:
            {
                CollisionAllSnakes(tuto);
                tuto->PlayerCount = 1;
                UpdateFruits(tuto,fruits,b->Height,b->Width);
                //UpdateFruit(tuto,fruits,b->Height,b->Width);

            } break;
        case 7:
            {
                CollisionAllSnakes(tuto);
                tuto->PlayerCount = 1;
            } break;
        default: TutoStep = 0;return false;
    }
    return true;
}

void DrawTutorial(Game* tuto, Fruits *fruits, Background *b)
{
    DrawBackground(b);
    DrawAllSnakes(tuto);

    switch (TutoStep)
    {
    case 0: //movements
        {
            DrawText("Welcome member of the species Schmidtea mediterranea !" , b->Width/9, 15*b->Height/30,50,GRAY);
        } break;
    case 6:
        {
            DrawFruits(fruits);
        } break;
    default: break;

    }
    DrawText( TUTO_TEXT[TutoStep] , b->Width/4, 17*b->Height/30,25,BLACK);
    DrawText("Planar War Totorial !",b->Width/10,b->Height/10,40,GRAY);
    DrawText("Press N to go to the next step of the Tutorial,P for the previous,\nR to restart this step and Q to quit the Tutorial",b->Width/10,b->Height/7,30,BLACK);
}
