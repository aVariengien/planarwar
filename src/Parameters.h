#include "raylib.h"


#ifndef PARAMETERS_H_INCLUDED
#define PARAMETERS_H_INCLUDED


typedef enum Mode {COURSE, NORMAL} Mode;

#define MAX_SPOTS 150
#define BACKGROUND_COLOR CLITERAL{118,215,202,255}
#define CIRCLES_PER_SPOT 3

static const Color SPOTS_COLORS[] = {{162,200,124,255} , {118,215,170,255}, {118,215,202,255}};
static const int SPOTS_RADIUS[] = {160,130,110};

#define FRUIT_COLOR CLITERAL{30,200,30,255}
#define FRUIT_OUT_COLOR CLITERAL{30,100,30,255}
#define DASH_COLOR CLITERAL{200,200,100,255}

static const Color BODY_COLORS[] = {ORANGE, SKYBLUE, LIME, DARKPURPLE};
static const Color HEAD_COLORS[] = {PINK, BLUE, DARKGREEN, PURPLE};

#define INIIAL_LENGTH 100
#define INITIAL_WIDTH 20
#define MAX_LENGTH 350
#define TUTORIAL_INITIAL_LENGTH 250
#define MAX_SNAKE 20
#define MAX_PLAYERS 4

#define MAX_DISTANCE 200

#define SPOT_SPEED 10 //for course mode
#define FRUIT_SPEED 3

#define DASH_SPEED 5
#define DASH_ROT_SPEED 0.1
#define REGULAR_SPEED 2.3
#define REGULAR_ROT_SPEED 0.05

#define LENGTH_LOSS_SPEED 2 //the speed at which the snake losses length when it dashes (an int, the lower the faster)


#define FRUIT_APPARITION_SPEED 110 //The higher the slower
#define COURSE_FRUIT_APPARITION_SPEED 70
#define MAX_FRUITS 10
#define FRUIT_BIRTH_MAX_SIZE 30
#define FRUIT_MAX_SIZE 100
#define FRUITS_POWER 2
#define FRUIS_GROWTH_SPEED 0.04

#define DASH_COLOR_VARIATION_SPEED 5



#define MINIMUM_LEFTOVER_RADIUS 5
#define INVULNERABILITY_TIME 100
#define IMPACT_WIDTH 30
#define HURT_WIDTH_REDUCTION 7
#define COLOR_FLASHING_SPEED 20

static const int keys[] = {39,44,45,46,47,48,49,50,51,52,53,54,55,56,57,59,61,65,66,67,68,69,70,71,72,73,74,75,76,77,78,79,80,81,82,83,84,85,86,87,88,89,90,32,256,257,258,259,260,261,262,263,264,265,266,267,268,269,280,281,282,283,284,290,291,292,293,294,295,296,297,298,299,300,301,340,341,342,343,344,345,346,347,348,91,92,93,96,320,321,322,323,324,325,326,327,328,329,330,331,332,333,334,335,
336};

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


#endif // PARAMETERS_H_INCLUDED


