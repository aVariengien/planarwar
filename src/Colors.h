
#include "raylib.h"
#include "Snakes.h"

#ifndef COLORS_H_INCLUDED
#define COLORS_H_INCLUDED






int StayInBound(int x, int lower, int higher);
int CloseNumber(int x, int A,float f);
Color CloseRandomColor(Color col, int v, int seed);
void DashColor(Snake* snake);
Color GetHurtColor(Color c);
Color GetDeadColor(Color c);
void HurtColor(Snake* snake);
void DeadColor(Snake* snake);
void RegularColor(Snake* snake);
int UpdateColor(Snake * snake);



#endif // COLORS_H_INCLUDED
