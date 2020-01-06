#include "Snakes.h"
#include "Fruits.h"
#include "background.h"

void LauchTutorial(int w, int h)
{
    bool QuitTutorial = false;
    int tutoStep = 0;
    Game tuto;
    tuto.PlayerCount = 1;
    Player player;
    InitPlayer(&player,0,w,h,true,NORMAL);
    player.KeyLeft = KEY_LEFT;
    player.KeyRight = KEY_RIGHT;
    player.KeyDash = KEY_UP;
    tuto.Players[0] = player;

    Background b;
    InitBackgroung(&b,w,h);

    Fruits fruits;
    fruits.FruitCount = 2;
    fruits.Fruits[0] = NewFruit(h,w);

    while (!QuitTutorial)
    {
        SetTargetFPS(60);

        //Update
        switch (tutoStep)
        {
            case 0: break;
        }


        //Drawing
        BeginDrawing();
        switch (tutoStep)
        {
            case 0: break;
        }
        EndDrawing();
    }
}
