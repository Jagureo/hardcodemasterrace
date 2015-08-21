// This is the main file to hold everthing together

#include "Framework\timer.h"
#include "game.h"
#include "splash.h"
#include "levelmap.txt"


StopWatch g_timer;            // Timer function to keep track of time and the frame rate
bool g_quitGame = false;      // Set to true if you want to quit the game
const unsigned char FPS = 7; // FPS of this game
const unsigned int frameTime = 1000 / FPS; // time for each frame
int levelno = 1;
int menuselect = 0;
int levelunlock = 1;

void mainLoop();

// TODO:
// Bug in waitUnitil. it waits for the time from getElapsedTime to waitUntil, but should be insignificant.

int main() 
{
	splash();
	init();      // initialize your variables
    mainLoop();  // main loop
    shutdown();  // do clean up, if any. free memory.
	return 0;
}

// This main loop calls functions to get input, update and render the game
// at a specific frame rate
void mainLoop()
{
    g_timer.startTimer();    // Start timer to calculate how long it takes to render this frame
	backtomenuselect:
	menuselect = menu();
	if(menuselect == 1)
	{
		goto backtolevelselect;
	}
	else if(menuselect == 2)
	{
		goto backtochallengeselect;
	}
	else if(menuselect == 3)
	{
		goto backtoachievementselect;
	}
	else if(menuselect == 69)
	{
		return;
	}
backtochallengeselect:
	menuselect = challenge(); 
	if(menuselect == 4)
	{
		goto backtomenuselect;
	}
backtoachievementselect:
	menuselect = achievement();
	if(menuselect == 4)
	{
		goto backtomenuselect;
	}
backtolevelselect:
	levelno = levelselect();
	if(levelno == 1)
	{
		render(levelunlock, blevel1, blevel1reset, blevel1AI);
	}
	else if(levelno == 2 && levelunlock > 1)
	{
		render(levelunlock, level2, level2reset, level2AI);
	}
	else if(levelno == 69)
	{
		goto backtomenuselect;
	}
	else
	{
		errorreport();
		return;
	}
    while (!g_quitGame)      // run this loop until user wants to quit 
	{        
        getInput();                         // get keyboard input
		if(levelno == 1)
		{
			update(g_timer.getElapsedTime(), levelunlock, blevel1, blevel1reset, blevel1AI);   // update the game
		}
		else if(levelno == 2)
		{
			update(g_timer.getElapsedTime(), levelunlock, level2, level2reset, level2AI);
		}
        //render();                           // render the graphics output to screen
        g_timer.waitUntil(frameTime);       // Frame rate limiter. Limits each frame to a specified time in ms.      
	}
	g_quitGame = false;
	if(levelno == 1)
	{
		resetlevel(blevel1, blevel1reset, blevel1AI);
	}
	else if(levelno == 2)
	{
		resetlevel(level2, level2reset, level2AI);
	}
	goto backtolevelselect;
}
