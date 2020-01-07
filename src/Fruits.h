
#include "raylib.h"
#include "Parameters.h"
#include "Snakes.h"
#include <stdlib.h>

#ifndef FRUITS_H_INCLUDED
#define FRUITS_H_INCLUDED


struct Fruit
{
    Vector2 Position;
    float Radius;
    int Eaten;
};
typedef struct Fruit Fruit;

struct Fruits
{
    Fruit Fruits[MAX_FRUITS];
    int FruitCount;
};


typedef struct Fruits Fruits;
bool IsCircleOnScreen(Vector2 pos, float rad, int h, int w);
int UpdateEatenFruits(Game* game, Fruits* fruits);
Fruit NewFruit(int h, int w);
int UpdateFruits(Game* game, Fruits* fruits, int h, int w);
void DrawFruits(Fruits * fruits);
#endif // FRUITS_H_INCLUDED
