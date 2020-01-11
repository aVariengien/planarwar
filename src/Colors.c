
#include "Colors.h"
#include "Parameters.h"
#include "stb_perlin.h" //a library to create perlin noise
#include "raylib.h"





int StayInBound(int x, int lower, int higher)
{
    if (x >higher)
    {
        return higher;
    }
    if (x<lower)
    {
        return lower;
    }
    return x;
}

int CloseNumber(int x, int A,float f)
{
    return StayInBound( x + ((int) A*f), 10, 255);
}

Color CloseRandomColor(Color col, int v, int seed)
//get a random color with a nice smooth continuity along v and diversity thank to a random seed
//useful for snakes' color
{
    float f1 = stb_perlin_noise3_seed(0,0,v/50.0,0,0,0,seed);
    float f2 = stb_perlin_noise3_seed(0,v/50.0,0,0,0,0,seed);
    float f3 = stb_perlin_noise3_seed(v/50.0,0,0,0,0,0,seed);

    Color c = { CloseNumber(col.r,100,f1),CloseNumber(col.g,100,f2),CloseNumber(col.b,100,f3), col.a};
    return c;
}
//color update function to adapt to circumstances
void DashColor(Snake* snake)
{
    for (int i = 0; i<snake->Length; i++)
    {
        snake->Body[i].PartColor = CloseRandomColor(DASH_COLOR, i*5,snake->RandomSeed);
    }
}


Color GetHurtColor(Color c)
{
    Color res = {StayInBound(c.r + 100,0,255),StayInBound(c.g - 100,0,255),StayInBound(c.b - 100,0,255), c.a };
    return res;
}


Color GetDeadColor(Color c)
{
    Color res = {StayInBound(c.r - 100,0,255),StayInBound(c.g - 100,0,255),StayInBound(c.b - 100,0,255),c.a};
    return res;
}

void HurtColor(Snake* snake)
{
    Color c = GetHurtColor(snake->BodyColor);
    for (int i=0; i<snake->Length; i++)
    {
        snake->Body[i].PartColor = CloseRandomColor(c, i/2,snake->RandomSeed);
    }
}

void DeadColor(Snake* snake)
{
    Color c = GetDeadColor(snake->BodyColor);
    for (int i=0; i<snake->Length; i++)
    {
        snake->Body[i].PartColor = CloseRandomColor(c, i/2,snake->RandomSeed);
    }
}

void RegularColor(Snake* snake)
{
    for (int i = 0; i<snake->Length; i++)
    {
        snake->Body[i].PartColor = CloseRandomColor(snake->BodyColor, i,snake->RandomSeed);
    }
}

//global function to set the color of a snake
//It's called at each frame for each snake. That's slightly unefficient but it really simplify the code
int UpdateColor(Snake * snake)
{
    if (snake->Dead)
    {
        DeadColor(snake);
        return 0;
    }
    if (snake->InDash)
    {
        DashColor(snake);
        return 0;
    }
    if (snake->FramesInHurt%COLOR_FLASHING_SPEED > COLOR_FLASHING_SPEED/2 )
    {
        HurtColor(snake);
        return 0;
    }

    RegularColor(snake);
    return 0;

}
