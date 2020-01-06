#include "background.h"
#include "Colors.h"
#include "raylib.h"
#include "Fruits.h"
#include <stdlib.h>
#include <stdio.h>


Spot NewSpot(int w, int h, int xoffset)
{
    Spot s;
    for (int i=0; i<CIRCLES_PER_SPOT; i++)
    {
        s.Radius[i] = SPOTS_RADIUS[i] + rand()%11 -5;
        s.Colors[i] = CloseRandomColor(SPOTS_COLORS[i],i,s.RandomSeed);
    }
    s.Position.x = rand()%w + xoffset;
    s.Position.y= rand()%h;
    s.RandomSeed = rand();
    return s;
}


void UpdateBackground(Background* b, int w, int h)
{
    for (int i=0; i<MAX_SPOTS; i++)
    {
        b->Spots[i].Position.x -= SPOT_SPEED;
        if (!(IsCircleOnScreen(b->Spots[i].Position,b->Spots[i].Radius[0],h,w)))
        {
            b->Spots[i] = NewSpot(2*w,h,w+b->Spots[i].Radius[0]);
        }
    }
}

void InitBackgroung(Background* b, int w, int h)
{
    for (int i=0; i<MAX_SPOTS; i++)
    {
        b->Spots[i] = NewSpot(w,h,0);
    }
    b->BackColor = BACKGROUND_COLOR;
    b->Width = w;
    b->Height = h;
}

void DrawSpot(Spot s)
{
    for (int i=0; i<CIRCLES_PER_SPOT; i++)
    {
        DrawCircleV(s.Position,s.Radius[i],s.Colors[i]);
    }
}

void DrawBackground(Background *b)
{
    DrawRectangle(0,0,b->Width,b->Height,b->BackColor);
    for (int i =0; i< MAX_SPOTS; i++)
    {
        DrawSpot(b->Spots[i]);
    }
}
