#include "raylib.h"
#include "Parameters.h"

#ifndef SNAKES_H_INCLUDED
#define SNAKES_H_INCLUDED


struct BodyPart
{
    Vector2 Position;
    float Radius;
    Color PartColor;
};

typedef struct BodyPart BodyPart;


struct Snake
{
    Vector2 Position;
    BodyPart Body[MAX_LENGTH];
    int Length;
    int Dead;
    int MaxLength;
    float Direction;
    float Speed;
    float Width;
    float RotSpeed;
    int InDash;
    int FramesInHurt;
    Color BodyColor;
    Color HeadColor;
    int RandomSeed; //For randomized color
    int UpdatedFrameCount;
    int FrameCount;
    bool Dummy; //useful for dummy snakes
};

typedef struct Snake Snake;

struct Player //Un joueur peut controler plusieurs snakes
{
    Snake ControledSnake[MAX_SNAKE];
    Color BodyColor;
    Color HeadColor; //Tous les snakes controlés ont la même couleur : la couleur du joueur
    int SnakeNumber;
    int KeyRight;
    int KeyLeft;
    int KeyDash;
    int Score;
    bool ScoreUpdated;

};

typedef struct Player Player;

struct Game
{
    Player Players[MAX_PLAYERS];
    int PlayerCount;
    Mode GameMode;
};

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
