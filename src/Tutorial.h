#ifndef TUTORIAL_H_INCLUDED
#define TUTORIAL_H_INCLUDED

#include "Snakes.h"
#include "background.h"
#include "Fruits.h"
#include <math.h>

void UpdateDummySnake(Snake * dummy, int w, int h);
bool UpdateTutorial(Game* tuto, Fruits *fruits, Background *b);
void DrawTutorial(Game* tuto, Fruits *fruits, Background *b);

static const char TUTO_TEXT[8][1000] = {"You are a planarian flatworm confined into an aquarium by scientists.\n\
They are doing research on your epic regeneration abilities during fight. \n\
You will soon know what I mean by that. But for now, discover how you move\n\
You can turn with <- and ->. Dash with -> \n ",
"There is a lot of ways to die here.\n\
For example : when you dash you move and turn faster but you lose length.\n\
When you have no length, you're dead. Simple.",
"You hurt yourself if you run on your body : your width decreases \n\
and your color changes, giving you a few seconds of invulnerability \n\
If you're too thin, you're dead. Simple.\n\
Also, walls are deadly too ...",
"But the thing is, you're not alone. You're here to fight !\n\
Dash into the enemy to hurt it and it's split in two !\n\
I told you : epic regeneration abilities !\n\
To be more effective you can also make the enemy run into you.", //Dash into the enemy to hurt it. Hurt it enough and it's split in two !\n
"Be careful, if you dash on it as \n\
it's dashing ... all your body is hurt !\n\
Now that you have a dashing enemy, you can also try to be split ;)",
"Be aware, if you run into a dead or alive body part \n\
without dash, you're hurt. Simple\n\
Use this as a way to kill enemies !",
"Luckily for you, there are bits of  growing mushrooms to eat.\n\
The green in order to regenerate length and the blue for both length and width !",
 "Yeay ! You're ready for fight now !"};


#endif // TUTORIAL_H_INCLUDED
