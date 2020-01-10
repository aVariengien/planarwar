
/*******************************************************************************************
*
*
*   PlanarWar
*   Fight for your life against other genetically modified planarian worms in a Petri box !
*   You can cut a worm in pieces by crashing on it but be careful : the pieces become new living worms !
*
*   This game has been created by Alexandre Variengien using raylib (www.raylib.com)
*   raylib is licensed under an unmodified zlib/libpng license (View raylib.h for details)
*
*   Copyright (c) 2014-2019 Ramon Santamaria (@raysan5)
*
********************************************************************************************/

///Bugs : crash C0000094, ghost snakes from previousgames, dash when not pressed

#include "raylib.h"
#include "Parameters.h"
#include "Snakes.h"
#include "Fruits.h"
#include "Colors.h"
#include "background.h"
#include "Tutorial.h"
//#include <emscripten.h>
//#include <dos.h>

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <time.h>



bool delay(int frames, int FramesCounter, bool reset) //fonction de delay à usage unique basée sur le nombre de frames
{
    static bool FirstCall = true;
    static int InitialFC = 0;

    if (reset)
    {
        FirstCall = true;
        return true;
    }
    else
    {
        if (FirstCall)
        {
            FirstCall = false;
            InitialFC = FramesCounter;
        }

        if (FramesCounter - InitialFC > frames)
        {
            return true;
        }
        else
        {
            return false;
        }
    }

}


int GetKeyboardKeyDown()
{
    for (int i=0; i<105; i++)
    {
        if (IsKeyPressed(keys[i]))
        {
            return keys[i];
        }
    }
    return -1;
}


//----------------------------------------------------------------------------------
// Types and Structures Definition
//----------------------------------------------------------------------------------
typedef enum GameScreen { LOGO = 0, TITLE, GAMEPLAY, ENDING, RULES, GAME_PARAM,TUTORIAL } GameScreen;

///nb de joueurs -> keys -> game


//----------------------------------------------------------------------------------
// Main entry point
//----------------------------------------------------------------------------------
int main(void)

{
    // Initialization (Note windowTitle is unused on Android)
    //--------------------------------------------------------------------------------------
    int screenWidth = 1920/2;
    int screenHeight = 1080/2;

    InitWindow(screenWidth, screenHeight, "PlanarWar !");

    if (GetMonitorCount() > 0)
    {
        screenHeight = GetMonitorHeight(0);
        screenWidth = GetMonitorWidth(0);
    }
    else
    {
        printf("\n ERROR : No Monitor recognised\n");
        exit(-1);
    }
    CloseWindow();

    InitWindow(screenWidth, screenHeight, "PlanarWar !"); //We open the proper widows once we have the dimension of the screen

    ToggleFullscreen();

    GameScreen currentScreen = LOGO;
    printf("ok");
    // TODO: Initialize all required variables and load all required data here!

    srand(time(NULL));
    int framesCounter = 0;          // Useful to count frames

    SetTargetFPS(60);               // Set desired framerate (frames-per-second)
    //--------------------------------------------------------------------------------------
    Game game;
    game.GameMode = NORMAL;
    Player CurrentPlayer;

    Game DemoScreen;
    InitDemoScreen(&DemoScreen, screenWidth, screenHeight);


    Fruits fruits;
    fruits.FruitCount = 0;



    Background b;
    InitBackgroung(&b,screenWidth,screenHeight);

    //tutorial variables

    Fruits tutoFruits;


    Game tuto;
    Player playerTuto;
    tuto.PlayerCount = 3; //the player and a dummy snake to test attacks
    tuto.GameMode = NORMAL;
    InitPlayer(&playerTuto,0,screenWidth,screenHeight,true,NORMAL);
    playerTuto.KeyLeft = KEY_LEFT;
    playerTuto.KeyRight = KEY_RIGHT;
    playerTuto.KeyDash = KEY_UP;
    tuto.Players[0] = playerTuto;

    InitPlayer(&playerTuto,1,screenWidth,screenHeight,true,NORMAL); //a dummy player
    playerTuto.KeyLeft = KEY_ONE; //random key not to be used
    playerTuto.KeyRight = KEY_ONE;
    playerTuto.KeyDash = KEY_ONE;
    playerTuto.ControledSnake[0].Dummy = true;
    tuto.Players[1] = playerTuto;


    InitPlayer(&playerTuto,2,screenWidth,screenHeight,true,NORMAL); //a dead player
    playerTuto.KeyLeft = KEY_ONE; //random key not to be used
    playerTuto.KeyRight = KEY_ONE;
    playerTuto.KeyDash = KEY_ONE;
    tuto.Players[2] = playerTuto;


    //Control variables
    bool BeginGame = false;
    int StepGetParam = 0;
    int NumKey = 0;
    int NumPlayer = 0;
    int playerAlive = 0;
    bool EndGame = false;

    // Main game loop

    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        framesCounter++;    // Count frames
        // Update
        //----------------------------------------------------------------------------------
        switch(currentScreen)
        {
            case LOGO:
            {
                // TODO: Update LOGO screen variables here!
                // Wait for 2 seconds (120 frames) before jumping to TITLE screen
                if (framesCounter > 1)
                {
                    currentScreen = TITLE;
                    InitDemoScreen(&DemoScreen, screenWidth, screenHeight);

                }
            } break;
            case TITLE:
            {
                UpdateDemoScreen(&DemoScreen,screenWidth,screenHeight);

                if (IsKeyPressed(KEY_ENTER) )
                {
                    currentScreen = GAME_PARAM;
                }

                if (IsKeyPressed(KEY_T))
                {
                    InitPlayer(&tuto.Players[0],0,b.Width,b.Height,false,tuto.GameMode); //initialiation of tutorial variables
                    InitPlayer(&tuto.Players[1],1,b.Width,b.Height,false,tuto.GameMode);
                    InitPlayer(&tuto.Players[2],2,b.Width,b.Height,false,tuto.GameMode);
                    tuto.Players[1].ControledSnake[0].Dummy = true;
                    currentScreen = TUTORIAL;
                }
            } break;
            case TUTORIAL:
                {
                    if (!UpdateTutorial(&tuto,&tutoFruits,&b))
                    {
                        currentScreen = LOGO;
                    }
                } break;

            case GAME_PARAM:
            {
                if (StepGetParam == 0)
                {
                    StepGetParam = 1;
                    switch (GetKeyPressed())
                    {
                    case KEY_TWO: game.PlayerCount = 2;  break;
                    case KEY_THREE: game.PlayerCount = 3; break;
                    case KEY_FOUR: game.PlayerCount = 4; break;
                    default: StepGetParam = 0; /*printf("%d \n", GetKeyPressed());*/ break;
                    }
                }

                if (StepGetParam == 1)
                {
                    StepGetParam = 2;
                    switch (GetKeyPressed())
                    {
                    case 'c': game.GameMode = COURSE; InitPlayer(&CurrentPlayer,0, screenWidth, screenHeight, true, game.GameMode);  break; //We initialize the current player to be ready for the next step
                    case 'n': game.GameMode = NORMAL; InitPlayer(&CurrentPlayer,0, screenWidth, screenHeight, true, game.GameMode); break;
                    default: StepGetParam = 1; break;
                    }
                }


                if ((StepGetParam >= 2) && delay(30,framesCounter, false) && !BeginGame)
                {

                    int k = GetKeyboardKeyDown();
                    if ((k != -1) && !BeginGame)
                    {
                        switch (NumKey)
                        {
                            case 0: CurrentPlayer.KeyLeft = k; NumKey ++; break;
                            case 1: CurrentPlayer.KeyRight = k; NumKey ++; break;
                            case 2:
                                {
                                    CurrentPlayer.KeyDash = k;
                                    NumKey=0;
                                    game.Players[NumPlayer] = CurrentPlayer;
                                    NumPlayer ++;
                                    if (NumPlayer == game.PlayerCount)
                                    {
                                        BeginGame = true;
                                    }
                                    else
                                    {
                                        InitPlayer(&CurrentPlayer,NumPlayer, screenWidth, screenHeight, true, game.GameMode);
                                    }
                                }break;
                            default: break;
                        }
                    }


                }

                if (BeginGame && IsKeyPressed(KEY_ENTER) )
                {
                    currentScreen = GAMEPLAY;
                }
            } break;
            case GAMEPLAY:
            {
                playerAlive = PlayersAlive(&game);
                if (game.GameMode == COURSE)
                {
                    UpdateBackground(&b, screenWidth,screenHeight);
                }

                if (playerAlive == -1)
                {
                    CollisionAllSnakes(&game);
                    CollisionAllSnakeScreen(&game,screenWidth,screenHeight);
                    UpdateSnakes(&game);
                    UpdateFruits(&game,&fruits,screenHeight,screenWidth);
                }
                else
                {
                    EndGame = true;
                    if (playerAlive != -2)
                    {
                        if (!game.Players[playerAlive].ScoreUpdated)
                        {
                            game.Players[playerAlive].Score ++;
                            game.Players[playerAlive].ScoreUpdated = true;
                        }
                    }
                }


                if (EndGame && IsKeyPressed(KEY_ENTER))
                {
                    currentScreen = GAMEPLAY;
                    BeginGame = true;
                    EndGame = false;
                    for (int r = 0; r<game.PlayerCount; r++)
                    {
                        InitPlayer(&game.Players[r],r,screenWidth,screenHeight, false, game.GameMode);
                    }
                    fruits.FruitCount = 0;

                }

                if (EndGame && (IsKeyPressed(KEY_BACKSPACE) || IsKeyPressed(KEY_R) ))
                {
                    currentScreen = LOGO;
                    delay(0,0,true);
                    BeginGame = false;
                    StepGetParam = 0;
                    NumKey = 0;
                    NumPlayer = 0;
                    EndGame = false;
                    InitPlayer(&CurrentPlayer,0, screenWidth, screenHeight, true, game.GameMode);
                }


            } break;

            default: break;
        }

        //----------------------------------------------------------------------------------

        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();

            ClearBackground(RAYWHITE);

            switch(currentScreen)
            {
                case LOGO:
                {

                    DrawText("Welcome to Planar War !", screenWidth/4,screenHeight/2, 90, LIGHTGRAY);
                    DrawText("WAIT for 2 SECONDS...", 1000, 1000, 20, GRAY);

                } break;
                case TITLE:
                {

                    DrawRectangle(0, 0, screenWidth, screenHeight, GREEN);
                    DrawAllSnakes(&DemoScreen);
                    DrawText("Welcome to Planar War !", screenWidth/10,screenHeight/3, 110, LIGHTGRAY);
                    DrawText("Press ENTER to begin the Game !", screenWidth/9, screenHeight/2, 80, WHITE);
                    DrawText("Press <ESC> to quit, T to begin the tutorial", screenWidth/9, screenHeight*5/6, 40, WHITE);
                    DrawFPS(0,0);

                } break;
                case GAME_PARAM:
                {
                    DrawRectangle(0, 0, screenWidth, screenHeight, GREEN);
                    if (StepGetParam == 0)
                    {
                        DrawText("How many Players ?", screenWidth/10,screenHeight/3, 80, LIGHTGRAY);
                        DrawText("From 2 to 4. Press a digit.", screenWidth/9, screenHeight/2, 60, WHITE);
                    }

                    if (StepGetParam == 1)
                    {
                        DrawText("Game Mode ?", screenWidth/10,screenHeight/3, 80, LIGHTGRAY);
                        DrawText("Press N for NORMAL Mode, C for COURSE Mode", screenWidth/9, screenHeight/2, 60, WHITE);
                    }


                    if (StepGetParam == 2)
                    {
                        char InfoPlayers[60];
                        sprintf(InfoPlayers, "Game with %d Players", game.PlayerCount);
                        DrawText(InfoPlayers, screenWidth/10,screenHeight/9, 50, LIGHTGRAY);

                        char InfoNumPlayer[60];
                        if (NumPlayer < game.PlayerCount)
                        {
                            sprintf(InfoNumPlayer, "Player %d choose your control keys !", NumPlayer+1);
                            DrawText(InfoNumPlayer, screenWidth/10,screenHeight/3, 80, BODY_COLORS[NumPlayer]);
                            switch (NumKey)
                            {
                                case 0: DrawText("Press your LEFT Key ", screenWidth/9, screenHeight/2, 60, WHITE); break;
                                case 1: DrawText("Press your RIGHT Key ", screenWidth/9, screenHeight/2, 60, WHITE); break;
                                case 2: DrawText("Press your DASH Key ", screenWidth/9, screenHeight/2, 60, WHITE); break;
                                default: break;
                            }
                        }

                        if (BeginGame)
                        {
                            DrawText("Press ENTER to begin the PLANARWAR !", screenWidth/9,screenHeight/2, 70, WHITE);
                        }
                    }

                } break;


                case TUTORIAL:
                    {
                        DrawTutorial(&tuto,&tutoFruits,&b);
                    }break;

                case GAMEPLAY:
                {

                    DrawBackground(&b);
                    DrawFPS(0,0);
                    if (playerAlive == -1)
                    {
                        DrawAllSnakes(&game);
                        DrawFruits(&fruits);
                    }
                    else
                    {
                        DrawAllSnakes(&game);
                        DrawFruits(&fruits);
                        DrawText("Press ENTER to rematch !", 3*screenWidth/14, 6*screenHeight/10, 80, WHITE);
                        DrawText("Press R or <- to restart", 4*screenWidth/14, 7*screenHeight/10, 40, WHITE);
                        if (playerAlive == -2)
                        {
                            DrawScores(&game,screenHeight,screenWidth);
                            DrawText("END OF THE GAME : It's a DRAW !", 3*screenWidth/14,screenHeight/2, 100, LIGHTGRAY);
                        }
                        else
                        {
                            DrawScores(&game,screenHeight,screenWidth);
                            char Winner[60];
                            sprintf(Winner, "Player %d win the Game !", playerAlive+1);
                            DrawText(Winner, 3*screenWidth/14,screenHeight/2, 100, BODY_COLORS[playerAlive]);
                        }
                    }

                } break;

                default: break;
            }

        EndDrawing();
        //----------------------------------------------------------------------------------
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------

    // TODO: Unload all loaded data (textures, fonts, audio) here!

    CloseWindow();        // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}
