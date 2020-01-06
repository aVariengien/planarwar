#ifndef BACKGROUND_H_INCLUDED
#define BACKGROUND_H_INCLUDED

#include "raylib.h"
#include "Colors.h"

struct Spot
{
    Vector2 Position;
    int Radius[CIRCLES_PER_SPOT];
    Color Colors[CIRCLES_PER_SPOT];
    int RandomSeed;
};

typedef struct Spot Spot;

struct Background
{
    Spot Spots[MAX_SPOTS];
    Color BackColor;
    int Width;
    int Height;
};
typedef struct Background Background;


Spot NewSpot(int w, int h, int xoffset);
void InitBackgroung(Background* b, int w, int h);

void UpdateBackground(Background* b, int w, int h);
void DrawBackground(Background *b);
#endif // BACKGROUND_H_INCLUDED
