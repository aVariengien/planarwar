#include "Fruits.h"
#include "Parameters.h"
#include "Colors.h"
#include "raylib.h"




void SwitchFruit(Fruits * fruits, int x, int y)
{
    Fruit tmp;
    tmp = fruits->Fruits[y];
    fruits->Fruits[y] = fruits->Fruits[x];
    fruits->Fruits[x] = tmp;
}


int UpdateEatenFruits(Game* game, Fruits* fruits)
{

    for (int j =0; j<game->PlayerCount; j++)
    {
        for (int k = 0; k< game->Players[j].SnakeNumber; k++)
        {
            Snake *snake = &(game->Players[j].ControledSnake[k]);
            for (int f=0; f<fruits->FruitCount; f++)
            {
                if (!(fruits->Fruits[f].Eaten) && CheckCollisionCircles(fruits->Fruits[f].Position, fruits->Fruits[f].Radius,snake->Position,snake->Width ))
                {

                    fruits->Fruits[f].Eaten = 1;
                    SwitchFruit(fruits, f, fruits->FruitCount-1); //we place the eaten fruit at the end of the array to delete it
                    fruits->FruitCount --;

                    int length_gain = ((int) fruits->Fruits[f].Radius)*FRUITS_POWER;
                    if (snake->MaxLength +length_gain < MAX_LENGTH)
                    {
                        snake->MaxLength += length_gain; //The size of the fruit is related to the length gain
                    }
                    else
                    {
                        snake->MaxLength = MAX_LENGTH;
                    }


                }
            }
        }
    }

    return 0;
}

Fruit NewFruit(int h, int w)
{
    int x = rand()%(8*w/10) + w/10;
    int y = rand()%(8*h/10) + h/10;
    float r = (float) (rand()%FRUIT_BIRTH_MAX_SIZE);
    Vector2 pos;
    pos.x = x;
    pos.y = y;
    Fruit f = {pos, r, 0};
    return f;
}

bool IsCircleOnScreen(Vector2 pos, float rad, int h, int w)
{
    return ((pos.x + rad) > 0);
}

int UpdateFruit(Game* game, Fruits* fruits, int h, int w)
{
    if ((rand()%FRUIT_APPARITION_SPEED == 0) && (fruits->FruitCount < MAX_FRUITS))
    {
        fruits->FruitCount ++;
        fruits->Fruits[fruits->FruitCount-1] = NewFruit(h,w);
    }
    UpdateEatenFruits(game,fruits);

    for (int i=0; i<fruits->FruitCount; i++)
    {
        if (fruits->Fruits[i].Radius < FRUIT_MAX_SIZE) //fruits growth until they are big enough
        {
            fruits->Fruits[i].Radius += FRUIS_GROWTH_SPEED;
        }
    }
    ///MODE TEST COURSE
    if (game->GameMode == COURSE)
    {
        for (int i=0; i<fruits->FruitCount; i++)
        {
            fruits->Fruits[i].Position.x -= FRUIT_SPEED;
            if (!IsCircleOnScreen(fruits->Fruits[i].Position,fruits->Fruits[i].Radius,h,w))
            {
                SwitchFruit(fruits, i, fruits->FruitCount-1); //we place the fruit at the end of the array to delete it
                fruits->FruitCount --;
            }
        }
    }
    ///END MODE TEST
    return 0;
}

void DrawFruits(Fruits * fruits)
{

    for (int i =0; i<fruits->FruitCount; i++)
    {
        if (!fruits->Fruits[i].Eaten)
        {
            DrawCircleV(fruits->Fruits[i].Position,fruits->Fruits[i].Radius,FRUIT_OUT_COLOR);
            DrawCircleV(fruits->Fruits[i].Position,fruits->Fruits[i].Radius*0.8,CloseRandomColor(FRUIT_COLOR, i, 0));

        }
    }
}
