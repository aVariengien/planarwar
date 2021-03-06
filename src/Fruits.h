


#ifndef FRUITS_H_INCLUDED
#define FRUITS_H_INCLUDED
#include "raylib.h"
#include "Parameters.h"
#include "Snakes.h"
#include <stdlib.h>

struct Fruit
{
    Vector2 Position;
    float Radius;
    int Eaten;
    bool SuperFruit;
};
typedef struct Fruit Fruit;

struct Fruits
{
    Fruit Fruits[MAX_FRUITS];
    int FruitCount;
};


typedef struct Fruits Fruits;
bool IsCircleOnScreen(Vector2 pos, float rad, int h, int w); //To know if a screen is on screen during race code
int UpdateEatenFruits(Game* game, Fruits* fruits);
Fruit NewFruit(int h, int w);
int UpdateFruits(Game* game, Fruits* fruits, int h, int w);
void DrawFruits(Fruits * fruits);
#endif // FRUITS_H_INCLUDED
