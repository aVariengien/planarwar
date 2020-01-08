

#ifndef SNAKES_H_INCLUDED
#define SNAKES_H_INCLUDED

#include "raylib.h"
#include "Parameters.h"


typedef struct Game Game;
void DrawScores(Game* game, int h, int w);

void InitDemoScreen(Game* demoScreen , int w, int h);
void UpdateDemoScreen(Game* demoScreen, int w, int h);

Snake CreateNewSnake(Snake snake);
void InitSnake(Snake * snake, int num, int w, int h, Mode);
void InitPlayer(Player * player, int num, int w, int h, bool FirstTime, Mode);

int UpdatePlayer(Player* player, Mode mode);
int UpdateSnakes(Game* game);


int DrawSnake(Snake* snake);
int DrawAllSnakes(Game* game);

int CollisionAllSnakes(Game* game);
int CollisionSnakes(Snake snake1,Snake snake2);
int CheckForCuts(Snake snake, Player* player, int snakeIndex);
int SnakeHurt(Snake * snake, Player * player, int snakeIndex);
int SnakeLocallyHurt(Snake * snake, Player * player,int snakeIndex, int place);
int CollisionScreen(Vector2 Position,int w,int h);
int CollisionAllSnakeScreen(Game * game, int w, int h);
int PlayersAlive(Game* game); //return -1 if there is more than one player alive; the number of the last player alive


#endif // SNAKES_H_INCLUDED
