#ifndef _GAME_H
#define _GAME_H

#include "Framework\timer.h"

extern StopWatch g_timer;
extern bool g_quitGame;

enum Keys
{
    K_UP,
    K_DOWN,
    K_LEFT,
    K_RIGHT,
    K_ESCAPE,
    K_COUNT,
	K_RETURN
};

void init();                // initialize your variables, allocate memory, etc
void getInput();            // get input from player
void update(double dt, int &levelunlock, int level1[16][48], int level1reset[16][48], int level1AI[16][48]);     // update the game and the state of the game
void render(int &levelunlock, int level1[16][48], int level1reset[16][48], int level1AI[16][48]);              // renders the current state of the game to the console
void shutdown();            // do clean up, free memory
int levelselect();
void resetlevel(int level1[16][48], int level1reset[16][48], int level1AI[16][48]);
void errorreport();
int achievement();
int challenge();
int menu();

#endif // _GAME_H