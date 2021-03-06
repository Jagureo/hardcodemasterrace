
#include "game.h"
#include "Framework\console.h"
#include"levelmap.txt"
#include <iostream>
#include <iomanip>
#include <sstream>
#include <conio.h>
#include <string>
#include <fstream>
#include <Windows.h>
#include<MMSystem.h>
#pragma comment (lib, "winmm")

using std::cin;
using std::cout;
using std::endl;

bool g_abKeyPressed[K_COUNT];
bool levelfix = true;
bool keyinputaa = true;	
double  g_dElapsedTime;
double  g_dDeltaTime;
int levelnumber = 1;
int y;		
int rainbowhere = 9;
int gamestate = 1;
int ministate = 0;
int levelselected = 0;
int challengeselected = 0;
int achievementselected = 0;
int count2 = 0;
int levelarrowX = 22;
int levelarrowY = 8;
int challengearrowX = 32;
int challengearrowY = 10;        
int levelno = 1;
int level1[16][48];
int level1AI[16][48];
void loadlevel();
void loadlight();
void moveCharacter();
int deathcounter = 0;
int wincounter = 0;
COORD charLocation;
COORD consoleSize;

// Game specific variables here
SGameChar   g_sChar;
EGAMESTATES g_eGameState = S_SPLASHSCREEN;
double  g_dBounceTime; // this is to prevent key bouncing, so we won't trigger keypresses more than once

// Console object
Console g_Console(79, 28, "SP The Great Kappa");

const WORD colors[] = {
        0x1A, 0x2B, 0x3C, 0x4D, 0x5E, 0x6F,
        0xA1, 0xB2, 0xC3, 0xD4, 0xE5, 0xF6
    };
const WORD colorskappa[] =  {
	                        0x01, 0x02, 0x03, 0x04, 0x05, 0x06,
							0x07, 0x08, 0x09, 0x0A, 0x0B, 0x0C,
							0x0D, 0x0E, 0x0F
	                        };
//Copy pasta stuff
//g_Console.clearBuffer(0x1F);
//g_Console.writeToBuffer(c, wining);
//g_Console.flushBufferToConsole();

void renderMap()
{
    // Set up sample colours, and output shadings
    COORD c;
    int xcoord = 0;
	int ycoord = 1;
	for (int i = 0; i < 16; ++i)
	{
		for(int j = 0; j < 48; ++j)
		{
			if(level1[i][j] == 0)
			{
				c.X = xcoord;
				c.Y = ycoord;
				g_Console.writeToBuffer(c, static_cast<char>(219));
				xcoord++;
				continue;
			}
			else if(level1[i][j] == 1)
			{
				//cout << ' ';
				c.X = xcoord;
				c.Y = ycoord;
				g_Console.writeToBuffer(c, ' ');
				xcoord++;
				continue;
			}
			else if(level1[i][j] == 2)
			{
				c.X = xcoord;
				c.Y = ycoord;
				g_Console.writeToBuffer(c, static_cast<char>(1));
				xcoord++;
				continue;
			}
			else if((level1[i][j] == 3)||(level1[i][j] == 4)||(level1[i][j] == 6)||(level1[i][j] == 7))
			{
				c.X = xcoord;
				c.Y = ycoord;
				g_Console.writeToBuffer(c, static_cast<char>(2));
				xcoord++;
				continue;
			}
			else if(level1[i][j] == 5)
			{
				colour(colors[13]);
				c.X = xcoord;
				c.Y = ycoord;
				g_Console.writeToBuffer(c, static_cast<char>(15), 0x0E);
				xcoord++;
				colour(colors[12]);
				continue;
			}
			else if((level1[i][j] == 15)||(level1[i][j] == 16)||(level1[i][j] == 17)||(level1[i][j] == 18))
			{
				colour(colors[16]);
				if(level1[i][j] == 15)
				{
					c.X = xcoord;
					c.Y = ycoord;
					g_Console.writeToBuffer(c, '^', 0x0C);
				}
				else if(level1[i][j] == 16)
				{
					c.X = xcoord;
					c.Y = ycoord;
					g_Console.writeToBuffer(c, 'V', 0x0C);
				}
				else if(level1[i][j] == 17)
				{
					c.X = xcoord;
					c.Y = ycoord;
					g_Console.writeToBuffer(c, '>', 0x0C);
				}
				else if(level1[i][j] == 18)
				{
					c.X = xcoord;
					c.Y = ycoord;
					g_Console.writeToBuffer(c, '<', 0x0C);
				}
				colour(colors[12]);
				xcoord++;
				continue;
			}
			else if(level1[i][j] == 19)
			{
				c.X = xcoord;
				c.Y = ycoord;
				g_Console.writeToBuffer(c, '^');
				xcoord++;
				continue;
			}
			else if(level1[i][j] == 20)
			{
				c.X = xcoord;
				c.Y = ycoord;
				g_Console.writeToBuffer(c, 'V');
				xcoord++;
				continue;
			}
			else if(level1[i][j] == 23)
			{
				c.X = xcoord;
				c.Y = ycoord;
				g_Console.writeToBuffer(c, '>');
				xcoord++;
				continue;
			}
			else if(level1[i][j] == 22)
			{
				c.X = xcoord;
				c.Y = ycoord;
				g_Console.writeToBuffer(c, '<');
				xcoord++;
				continue;
			}
			else if(level1[i][j] == 21)
			{
				colour(colors[16]);
				c.X = xcoord;
				c.Y = ycoord;
				g_Console.writeToBuffer(c, '|', 0x0C);
				xcoord++;
				colour(colors[12]);
				continue;
			}
			else if(level1[i][j] == 25)
			{
				colour(colors[16]);
				c.X = xcoord;
				c.Y = ycoord;
				g_Console.writeToBuffer(c, '-', 0x0C);
				xcoord++;
				colour(colors[12]);
				continue;
			}
			else if(level1[i][j] == 69)
			{
				c.X = xcoord;
				c.Y = ycoord;
				g_Console.writeToBuffer(c, 'x');
				xcoord++;
				continue;
			}
		}
		xcoord = 0;
		ycoord++;
	}
	renderCharacter();
	g_Console.flushBufferToConsole();
}
bool collisiondetection(int x)
{
	if (x == 1)
	{
		if(charLocation.Y > 0 && level1[charLocation.Y-2][charLocation.X] != 0 && level1[charLocation.Y-2][charLocation.X] != 15 && level1[charLocation.Y-2][charLocation.X] != 16 && level1[charLocation.Y-2][charLocation.X] != 17 && level1[charLocation.Y-2][charLocation.X] != 18 && level1[charLocation.Y-2][charLocation.X] != 19 && level1[charLocation.Y-2][charLocation.X] != 20 && level1[charLocation.Y-2][charLocation.X] != 22 && level1[charLocation.Y-2][charLocation.X] != 23)
		{
			return true;
		}
		else
		{
			return false;
		}
	}
	else if (x == 2)
	{
		if(charLocation.X > 0 && level1[charLocation.Y-1][charLocation.X-1] != 0 && level1[charLocation.Y-1][charLocation.X-1] != 15 && level1[charLocation.Y-1][charLocation.X-1] != 16 && level1[charLocation.Y-1][charLocation.X-1] != 17 && level1[charLocation.Y-1][charLocation.X-1] != 18 && level1[charLocation.Y-1][charLocation.X-1] != 19 && level1[charLocation.Y-1][charLocation.X-1] != 20 && level1[charLocation.Y-1][charLocation.X-1] != 22 && level1[charLocation.Y-1][charLocation.X-1] != 23)
		{
			return true;
		}
		else
		{
			return false;
		}
	}
	else if (x == 3)
	{
		if(charLocation.Y < consoleSize.Y - 1 && level1[charLocation.Y][charLocation.X] != 0 && level1[charLocation.Y][charLocation.X] != 15 && level1[charLocation.Y][charLocation.X] != 16 && level1[charLocation.Y][charLocation.X] != 17 && level1[charLocation.Y][charLocation.X] != 18 && level1[charLocation.Y][charLocation.X] != 19 && level1[charLocation.Y][charLocation.X] != 20 && level1[charLocation.Y][charLocation.X] != 22 && level1[charLocation.Y][charLocation.X] != 23)
		{
			return true;
		}
		else
		{
			return false;
		}
	}
	else if (x == 4)
	{
		if(charLocation.X < consoleSize.X - 1 && level1[charLocation.Y-1][charLocation.X+1] != 0 && level1[charLocation.Y-1][charLocation.X+1] != 15 && level1[charLocation.Y-1][charLocation.X+1] != 16 && level1[charLocation.Y-1][charLocation.X+1] != 17 && level1[charLocation.Y-1][charLocation.X+1] != 18 && level1[charLocation.Y-1][charLocation.X+1] != 19 && level1[charLocation.Y-1][charLocation.X+1] != 20 && level1[charLocation.Y-1][charLocation.X+1] != 22 && level1[charLocation.Y-1][charLocation.X+1] != 23)
		{
			return true;
		}
		else
		{
			return false;
		}
	}
	return true;
}
void update(double dt)
{
	
	/*switch(gamestate)
	{
		// main menu
		case 1: updateSplashScreen();
			break;
		// game
		case 2: updateMainMenu();
			break;
			//gameplay/playgame
		case 3: updateGame();
			break;
			//levelselect
		case 4: updateLevelSelect();
			break;
		case 5: updateChallenges();
			break;
		case 6: updateStats();
			break;
		
	}*/
	
    // get the delta time
    g_dElapsedTime += dt;
    g_dDeltaTime = dt;

	if(gamestate == 2)
	{
		// Updating the location of the character based on the key press
		moveCharacter();

		// quits the game i	f player hits the escape key
		if (g_abKeyPressed[K_ESCAPE])
		{
			gamestate = 1;
			g_dBounceTime = g_dElapsedTime + 0.125;
			//g_quitGame = true;
		}
	}
}
void updateSplashScreen()
{

}
void updateMainMenu()
{

}
void updateGame()
{

}
void updateLevelSelect()
{

}
void updateChallenges()
{

}
void updateStats()
{

}
void getInput( void )
{    
    g_abKeyPressed[K_UP]     = isKeyPressed(VK_UP);
    g_abKeyPressed[K_DOWN]   = isKeyPressed(VK_DOWN);
    g_abKeyPressed[K_LEFT]   = isKeyPressed(VK_LEFT);
    g_abKeyPressed[K_RIGHT]  = isKeyPressed(VK_RIGHT);
    g_abKeyPressed[K_RETURN] = isKeyPressed(VK_RETURN);
    g_abKeyPressed[K_ESCAPE] = isKeyPressed(VK_ESCAPE);
	g_abKeyPressed[K_SPACE]  = isKeyPressed(VK_SPACE);
}
void shutdown( void )
{
    // Reset to white text on black background
    colour(FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED);

    //g_Console.clearBuffer();
}
void init( void )
{
	PlaySound(TEXT("Beat1.wav"), NULL, SND_FILENAME|SND_LOOP|SND_ASYNC);

	g_dBounceTime = 0.0;

    std::cout << std::fixed << std::setprecision(3);

    SetConsoleTitle(L"The Great Kappa");

    // Get console width and height
    CONSOLE_SCREEN_BUFFER_INFO csbi; /* to get buffer info */     

    /* get the number of character cells in the current buffer */ 
    GetConsoleScreenBufferInfo( GetStdHandle( STD_OUTPUT_HANDLE ), &csbi );
    consoleSize.X = csbi.srWindow.Right + 1;
    consoleSize.Y = csbi.srWindow.Bottom + 1;

    // set the character to be in the center of the screen.
    charLocation.X = 1;
    charLocation.Y = 2;

	colour(colors[15]);
}
void render()
{
	//g_Console.clearBuffer(0x1F);
	COORD c ;
	//clearScreen();
	/*switch(gamestate)
	{
		// main menu
		case 1: renderSplashScreen();
			break;
		// game
		case 2: renderMainMenu();
			break;
			//gameplay/playgame
		case 3: renderGame();
			break;
			//levelselect
		case 4: renderLevelSelect();
			break;
		case 5: renderChallenges();
			break;
		case 6: renderStats();
			break;
		
	}*/

	renderToScreen();

	////////////////////////
	//if(gamestate == 1)
	//{
	int x;
	switch(gamestate)
	{
	case 1:
		x = newmainmenu();
		if(x == 69)
		{
			g_bQuitGame = true;
			return;
		}
		else if(x == 1)
		{
			gamestate = 2;
			for(int i = 0; i < 16; i++)
			{
				for(int j = 0; j < 48; j++)
				{
					level1[i][j] = blevel1[i][j];
				}
			}
			for(int i = 0; i < 16; i++)
			{
				for(int j = 0; j < 48; j++)
				{
					level1AI[i][j] = blevel1AI[i][j];
				}
			}
			charLocation.X = 1;
			charLocation.Y = 2;
		}
		else if(x == 2)
		{
			gamestate = 2;
			for(int i = 0; i < 16; i++)
			{
				for(int j = 0; j < 48; j++)
				{
					level1[i][j] = level2[i][j];
				}
			}
			for(int i = 0; i < 16; i++)
			{
				for(int j = 0; j < 48; j++)
				{
					level1AI[i][j] = level2AI[i][j];
				}
			}
			charLocation.X = 1;
			charLocation.Y = 2;
		}
		else if(x == 3)
		{
			gamestate = 2;
			for(int i = 0; i < 16; i++)
			{
				for(int j = 0; j < 48; j++)
				{
					level1[i][j] = level3[i][j];
				}
			}
			for(int i = 0; i < 16; i++)
			{
				for(int j = 0; j < 48; j++)
				{
					level1AI[i][j] = level3AI[i][j];
				}
			}
			charLocation.X = 1;
			charLocation.Y = 2;
		}
		else if(x ==4)
		{
			gamestate = 2;
			for(int i = 0; i < 16; i++)
			{
				for(int j = 0; j < 48; j++)
				{
					level1[i][j] = level4[i][j];
				}
			}
			for(int i = 0; i < 16; i++)
			{
				for(int j = 0; j < 48; j++)
				{
					level1AI[i][j] = level4AI[i][j];
				}
			}
			charLocation.X = 1;
			charLocation.Y = 2;
		}
		else if(x == 5)
		{
			gamestate = 2;
			for(int i = 0; i < 16; i++)
			{
				for(int j = 0; j < 48; j++)
				{
					level1[i][j] = level5[i][j];
				}
			}
			for(int i = 0; i < 16; i++)
			{
				for(int j = 0; j < 48; j++)
				{
					level1AI[i][j] = level5AI[i][j];
				}
			}
			charLocation.X = 1;
			charLocation.Y = 2;
		}
		else if(x == 6)
		{
			gamestate = 2;
			for(int i = 0; i < 16; i++)
			{
				for(int j = 0; j < 48; j++)
				{
					level1[i][j] = level6[i][j];
				}
			}
			for(int i = 0; i < 16; i++)
			{
				for(int j = 0; j < 48; j++)
				{
					level1AI[i][j] = level6AI[i][j];
				}
			}
			charLocation.X = 1;
			charLocation.Y = 2;
		}
		else if(x == 7)
		{
			gamestate = 2;
			for(int i = 0; i < 16; i++)
			{
				for(int j = 0; j < 48; j++)
				{
					level1[i][j] = level7[i][j];
				}
			}
			for(int i = 0; i < 16; i++)
			{
				for(int j = 0; j < 48; j++)
				{
					level1AI[i][j] = level7AI[i][j];
				}
			}
			charLocation.X = 1;
			charLocation.Y = 2;
		}
		else if(x == 8)
		{
			gamestate = 2;
			for(int i = 0; i < 16; i++)
			{
				for(int j = 0; j < 48; j++)
				{
					level1[i][j] = level8[i][j];
				}
			}
			for(int i = 0; i < 16; i++)
			{
				for(int j = 0; j < 48; j++)
				{
					level1AI[i][j] = level8AI[i][j];
				}
			}
			charLocation.X = 1;
			charLocation.Y = 2;
		}
		else if(x == 9)
		{
			gamestate = 2;
			for(int i = 0; i < 16; i++)
			{
				for(int j = 0; j < 48; j++)
				{
					level1[i][j] = level9[i][j];
				}
			}
			for(int i = 0; i < 16; i++)
			{
				for(int j = 0; j < 48; j++)
				{
					level1AI[i][j] = level9AI[i][j];
				}
			}
			charLocation.X = 1;
			charLocation.Y = 2;
		}
		else if(x == 10)
		{
			gamestate = 2;
			for(int i = 0; i < 16; i++)
			{
				for(int j = 0; j < 48; j++)
				{
					level1[i][j] = level10[i][j];
				}
			}
			for(int i = 0; i < 16; i++)
			{
				for(int j = 0; j < 48; j++)
				{
					level1AI[i][j] = level10AI[i][j];
				}
			}
			charLocation.X = 1;
			charLocation.Y = 2;
		}
		else if(x == 11)
		{
			gamestate = 2;
			for(int i = 0; i < 16; i++)
			{
				for(int j = 0; j < 48; j++)
				{
					level1[i][j] = level11[i][j];
				}
			}
			for(int i = 0; i < 16; i++)
			{
				for(int j = 0; j < 48; j++)
				{
					level1AI[i][j] = level11AI[i][j];
				}
			}
			charLocation.X = 1;
			charLocation.Y = 2;
		}
		else if(x == 12)
		{
			gamestate = 2;
			for(int i = 0; i < 16; i++)
			{
				for(int j = 0; j < 48; j++)
				{
					level1[i][j] = level12[i][j];
				}
			}
			for(int i = 0; i < 16; i++)
			{
				for(int j = 0; j < 48; j++)
				{
					level1AI[i][j] = level12AI[i][j];
				}
			}
			charLocation.X = 1;
			charLocation.Y = 2;
		}
		else if(x == 13)
		{
			gamestate = 2;
			for(int i = 0; i < 16; i++)
			{
				for(int j = 0; j < 48; j++)
				{
					level1[i][j] = level13[i][j];
				}
			}
			for(int i = 0; i < 16; i++)
			{
				for(int j = 0; j < 48; j++)
				{
					level1AI[i][j] = level13AI[i][j];
				}
			}
			charLocation.X = 1;
			charLocation.Y = 2;
		}
		else if(x == 14)
		{
			gamestate = 2;
			for(int i = 0; i < 16; i++)
			{
				for(int j = 0; j < 48; j++)
				{
					level1[i][j] = level14[i][j];
				}
			}
			for(int i = 0; i < 16; i++)
			{
				for(int j = 0; j < 48; j++)
				{
					level1AI[i][j] = level14AI[i][j];
				}
			}
			charLocation.X = 1;
			charLocation.Y = 2;
		}
		else if(x == 15)
		{
			gamestate = 2;
			for(int i = 0; i < 16; i++)
			{
				for(int j = 0; j < 48; j++)
				{
					level1[i][j] = level15[i][j];
				}
			}
			for(int i = 0; i < 16; i++)
			{
				for(int j = 0; j < 48; j++)
				{
					level1AI[i][j] = level15AI[i][j];
				}
			}
			charLocation.X = 1;
			charLocation.Y = 2;
		}
		else
		{
			return;
		}
	//}
	//else if(gamestate == 2)
	//{
	case 2:
		renderLevelSelect();
		renderFramerate();
		if(!keyinputaa)
		{
			return;
		}
		keyinputaa = false;
		g_Console.clearBuffer(0x0F);
		loadlevel();
		loadlight();

		colour(0x0F);
		gotoXY(0,1);
		renderMap();
		if(level1[charLocation.Y-1][charLocation.X] == 69)
		{
			resetlevel();
			keyinputaa = true;
			render();
			gotoXY (0, 17);
			c.X = 0;
			int ycoord = 17;
			c.Y = ycoord;
			colour(colorskappa[14]);
			std ::string wining;
			std::ifstream myfile ("youwin.txt");
			if (myfile.is_open())
			{
				while ( getline (myfile,wining) )
				{
					c.Y = ycoord;
					g_Console.writeToBuffer(c, wining);
					ycoord++;
				}
				myfile.close();
			}
			wincounter += 1;
				
		}
		else if(level1[charLocation.Y-1][charLocation.X] != 1)
		{
			resetlevel();
			keyinputaa = true;
			render();
			gotoXY (0, 19);
			c.X = 0;
			int ycoord = 19;
			c.Y = ycoord;
			colour(colorskappa[14]);
			std ::string losing;
			std::ifstream myfile ("youlose.txt");
			if (myfile.is_open())
			{
				while ( getline (myfile,losing) )
				{
					c.Y = ycoord;
					g_Console.writeToBuffer(c, losing);
					ycoord++;
				}
				myfile.close();
			}
 		    deathcounter += 1;
		}
	}
	renderFramerate();
}
void renderMainMenu()
{
	g_Console.clearBuffer(0x0F);
	COORD c;
    cls();

    std::  string line;
	std::ifstream myfile ("TGK.txt");
	int ycoord = 0;
	if (myfile.is_open())
	{
		while ( getline (myfile,line) )
		{
			c.X = 0;
			c.Y = ycoord;
			g_Console.writeToBuffer(c, line, 0x0A);
			ycoord++;
		}
		myfile.close();
	}
	rainbowhere += 1;
	if(rainbowhere > 14)
	{
		rainbowhere = 9;
	}
	colour(colorskappa[rainbowhere]);
	std:: string keepo;
	std::ifstream anotherfile ("kapp.txt");
	ycoord = 15;
	if (anotherfile.is_open())
	{
		while ( getline (anotherfile,keepo) )
		{
			c.X = 0;
			c.Y = ycoord;
			g_Console.writeToBuffer(c, keepo);
			ycoord++;
		}
		anotherfile.close();
	}

	colour(colors[15]);
	
    c.X = 45;
    c.Y = 14; 
	g_Console.writeToBuffer(c, " Welcome to ");     

    
	c.X = 45;
    c.Y = 15; 
	g_Console.writeToBuffer(c, " 'The Great Kappa' game! ");   

    c.X = 48;
    c.Y = 17;     
    g_Console.writeToBuffer(c, "PLAY GAME");  

	c.X = 48;
    c.Y = 19; 
    g_Console.writeToBuffer(c, "CHALLENGES");
      
	c.X = 48;
    c.Y = 21; 
    g_Console.writeToBuffer(c, "STATISTICS"); 

	c.X = 48;
    c.Y = 23; 
	g_Console.writeToBuffer(c, "EXIT GAME"); 

	int count = count2 ;
   
	if(count == 0)
	{
		c.X = 45;
		c.Y = 17;
		g_Console.writeToBuffer(c, ">"); 
	}
	else if(count == 1)
	{
		c.X = 45;
		c.Y = 19;
		g_Console.writeToBuffer(c, ">"); 
	}
	else if(count == 2)
	{
		c.X = 45;
		c.Y = 21;
		g_Console.writeToBuffer(c, ">"); 
	}
	else if(count == 3)
	{
		c.X = 45;
		c.Y = 23;
		g_Console.writeToBuffer(c, ">"); 
	}
    g_Console.flushBufferToConsole();
}
void renderLevelSelect()
{
	    COORD c;
    std::ostringstream ss;
    ss << std::fixed << std::setprecision(3);
    ss.str("");
    ss << "Level " << levelselected;
	c.X = g_Console.getConsoleSize().X - 50;
    c.Y = 0;
    g_Console.writeToBuffer(c, ss.str());
    g_Console.flushBufferToConsole();

if (levelselected == 1)
    {
        ss.str("");
        ss << "JUST RUN";
        c.X = g_Console.getConsoleSize().X - 30;
        c.Y = 2;
        g_Console.writeToBuffer(c, ss.str());
    }
    if (levelselected == 2)
    {
        ss.str("");
        ss << "Follow behind the guards!";
        c.X = g_Console.getConsoleSize().X - 30; 
        c.Y = 2;
        g_Console.writeToBuffer(c, ss.str());
    }
    if (levelselected == 3)
    {
        ss.str("");
        ss << "Stuck? Touch the laser arrow";
        c.X = g_Console.getConsoleSize().X - 30;
        c.Y = 2;
        g_Console.writeToBuffer(c, ss.str());
    }
    if (levelselected == 4)
    {
        ss.str("");
        ss << "Watch out, you are not the";
        c.X = g_Console.getConsoleSize().X - 40;
        c.Y = 2;
        g_Console.writeToBuffer(c, ss.str());
		ss.str("");
        ss << "only one who can interact with laser!";
        c.Y = 3;
        g_Console.writeToBuffer(c, ss.str());
    }
    if (levelselected == 5)
    {
        ss.str("");
        ss << "Look out above!";
        c.X = g_Console.getConsoleSize().X - 30;
        c.Y = 2;
        g_Console.writeToBuffer(c, ss.str());
    }
    if (levelselected == 6)
    {
        ss.str("");
        ss << "Be patient, and watch the";
        c.X = g_Console.getConsoleSize().X - 33;
        c.Y = 2;
        g_Console.writeToBuffer(c, ss.str());
		ss.str("");
        ss << "guard's patterns";
        c.Y = 3;
        g_Console.writeToBuffer(c, ss.str());
    }
    if (levelselected == 7)
    {
        ss.str("");
        ss << "Now...put what you have";
        c.X = g_Console.getConsoleSize().X - 30;
        c.Y = 2;
        g_Console.writeToBuffer(c, ss.str());
		ss.str("");
		ss << "learnt together.";
		c.Y = 3;
		g_Console.writeToBuffer(c, ss.str());
    }
    if (levelselected == 8)
    {
        ss.str("");
        ss << "MOAR LASER! thread carefully";
        c.X = g_Console.getConsoleSize().X - 30;
        c.Y = 2;
        g_Console.writeToBuffer(c, ss.str());
    }
    if (levelselected == 9)
    {
        ss.str("");
        ss << "Hint: guard's movement are";
        c.X = g_Console.getConsoleSize().X - 30;
        c.Y = 2;
        g_Console.writeToBuffer(c, ss.str());
		ss.str("");
        ss << "still not random!";
        c.X = g_Console.getConsoleSize().X - 30;
        c.Y = 3;
        g_Console.writeToBuffer(c, ss.str());
    }
    if (levelselected == 10)
    {
        ss.str("");
        ss << "Turn off lasers carefully...";
        c.X = g_Console.getConsoleSize().X - 30;
        c.Y = 2;
        g_Console.writeToBuffer(c, ss.str());
    }
}
void renderChallenges()
{
	g_Console.clearBuffer(0x0F);
	COORD c ;
    cls();     
	std:: string line;
	std::ifstream myfile ("chall.txt");
	int ycoord = 0;
	if (myfile.is_open())
	{
		while ( getline (myfile,line) )
		{
			c.X = 0;
			c.Y = ycoord;
			g_Console.writeToBuffer(c, line);
			ycoord++;
		}
		myfile.close();
	}

  else cout << "Unable to open file"; 

    c.X = 34;
	c.Y = 10;
	g_Console.writeToBuffer(c, "Level 1");
	c.X = 34;
	c.Y = 14;
	g_Console.writeToBuffer(c, "Level 2");
	c.X = 34;
	c.Y = 18;
	g_Console.writeToBuffer(c, "Level 3");
	c.X = 34;
	c.Y = 22;
	g_Console.writeToBuffer(c, "Level 4");
	c.X = 34;
	c.Y = 26;
	g_Console.writeToBuffer(c, "Level 5");
	c.X = challengearrowX;
	c.Y = challengearrowY;
	g_Console.writeToBuffer(c, ">");  
}			
void renderStats()
{

}
void splashScreenWait()    // waits for time to pass in splash screen
{
   // if (g_dElapsedTime > 3.0) // wait for 3 seconds to switch to game mode, else do nothing
     //   g_eGameState = S_GAME;
}
void gameplay()            // gameplay logic
{
    processUserInput(); // checks if you should change states or do something else with the game, e.g. pause, exit
    moveCharacter();    // moves the character, collision detection, physics, etc
                        // sound can be played here too.
}
void moveCharacter()
{
	if (g_abKeyPressed[K_UP] && g_dBounceTime < g_dElapsedTime)
		{
			bool nocollide = collisiondetection(1);
			if(nocollide)
			{
				Beep(1440, 60);
				charLocation.Y--; 
				keyinputaa = true;
				g_dBounceTime = g_dElapsedTime + 0.125;
			}
		}
		else if (g_abKeyPressed[K_LEFT] && g_dBounceTime < g_dElapsedTime)
		{
			bool nocollide = collisiondetection(2);
			if(nocollide)
			{
				Beep(1440, 60);
				charLocation.X--; 
				keyinputaa = true;
				g_dBounceTime = g_dElapsedTime + 0.125;
			}
		}
		else if (g_abKeyPressed[K_DOWN] && g_dBounceTime < g_dElapsedTime)
		{
			bool nocollide = collisiondetection(3);
			if(nocollide)
			{
				Beep(1440, 60);
				charLocation.Y++; 
				keyinputaa = true;
				g_dBounceTime = g_dElapsedTime + 0.125;
			}
		}
		else if (g_abKeyPressed[K_RIGHT] && g_dBounceTime < g_dElapsedTime)
		{
			bool nocollide = collisiondetection(4);
			if(nocollide)
			{
				Beep(1440, 60);
				charLocation.X++; 
				keyinputaa = true;
				g_dBounceTime = g_dElapsedTime + 0.125;
			}
		}
}
void processUserInput()
{
	/*
    // quits the game if player hits the escape key
    if (g_abKeyPressed[K_ESCAPE])
        g_bQuitGame = true;    
		*/
}
void clearScreen()
{
    // Clears the buffer with this colour attribute
    g_Console.clearBuffer(0x0F);
}
void renderSplashScreen()  // renders the splash screen
{
   /* COORD c = g_Console.getConsoleSize();
    c.Y /= 3;
    c.X = c.X / 2 - 9;
    g_Console.writeToBuffer(c, "A game in 3 seconds", 0x03);
    c.Y += 1;
    c.X = g_Console.getConsoleSize().X / 2 - 20;
    g_Console.writeToBuffer(c, "Press <Space> to change character colour", 0x09);
    c.Y += 1;
    c.X = g_Console.getConsoleSize().X / 2 - 9;
    g_Console.writeToBuffer(c, "Press 'Esc' to quit", 0x09);*/
}
void renderGame()
{
    renderMap();        // renders the map to the buffer first
    renderCharacter();  // renders the character into the buffer
}
void renderCharacter()
{
    // Draw the location of the character
   /* WORD charColor = 0x0C;
    if (g_sChar.m_bActive)
    {
        charColor = 0x0A;
    }
    g_Console.writeToBuffer(g_sChar.m_cLocation, (char)1, charColor);*/
	COORD c;
	c.X = charLocation.X;
	c.Y = charLocation.Y;
    g_Console.writeToBuffer(c, (char)1, 0x0C);
	g_Console.flushBufferToConsole();
}
void renderFramerate()
{
	
    COORD c;
    // displays the framerate
    std::ostringstream ss;
    ss << std::fixed << std::setprecision(3);
    ss << 1.0 / g_dDeltaTime << "fps";
    c.X = g_Console.getConsoleSize().X - 9;
    c.Y = 0;
    g_Console.writeToBuffer(c, ss.str());

    // displays the elapsed time
    ss.str("");
    ss << g_dElapsedTime << "secs";
    c.X = 0;
    c.Y = 0;
    g_Console.writeToBuffer(c, ss.str(), 0x59);
	g_Console.flushBufferToConsole();
	
}
void renderToScreen()
{
    // Writes the buffer to the console, hence you will see what you have written
    g_Console.flushBufferToConsole();
}
void errorreport()
{
	COORD c; 
	c.X = 0;
	c.Y = 0;
    g_Console.writeToBuffer(c, " _ Error loading level. Thanks, Obama.   ");
	g_Console.flushBufferToConsole();
}
int newmainmenu()
{
	keyinputaa = true;
	colour(colors[15]);
	switch(ministate)
	{
		case 0:
			ministate = menu();
			return 0;
		case 1:
			levelselected = levelselect();
			if(levelselected == 68)
			{
				ministate = 0;
				return 0;
			}
			else if(levelselected != 0 )
			{
				return levelselected;
			}
			else
			{
				return 0;
			}
		case 2:
			levelselected = challenge();
			if(levelselected == 68)
			{
				ministate = 0;
				return 0;
			}
			else if(levelselected != 0 )
			{
				return levelselected;
			}
			else
			{
				return 0;
			}
		case 3:
			achievementselected = stats();
			if(achievementselected == 4)
			{
				ministate = 0;
				return 0;
			}
			else
			{
				return 0;
			}
		case 69:
			return 69;
	}
}
void loadlevel(){
	//laser up
	if(level1[charLocation.Y-2][charLocation.X] == 15) //up
	{
		level1[charLocation.Y-2][charLocation.X] = 19;
		for(int k = 1; charLocation.Y-2-k >= 0; k++)
		{
			if((level1[charLocation.Y-2-k][charLocation.X] == 21)||(level1[charLocation.Y-2-k][charLocation.X] == 25))
			{
				level1[charLocation.Y-2-k][charLocation.X] = 1;
			}
			else
			{
				break;
			}
		}
	}
	if(level1[charLocation.Y-1][charLocation.X-1] == 15) //left
	{
		level1[charLocation.Y-1][charLocation.X-1] = 19;
		for(int k = 1; (charLocation.Y-1)-k >= 0; k++)
		{
			if((level1[charLocation.Y-1-k][charLocation.X-1] == 21)||(level1[charLocation.Y-1-k][charLocation.X-1] == 25))
			{
				level1[charLocation.Y-1-k][charLocation.X-1] = 1;
			}
			else
			{
				break;
			}
		}
	}
	if(level1[charLocation.Y-1][charLocation.X+1] == 15) //right
	{
		level1[charLocation.Y-1][charLocation.X+1] = 19;
		for(int k = 1; (charLocation.Y-1)-k >= 0; k++)
		{
			if((level1[(charLocation.Y-1)-k][charLocation.X+1] == 21)||(level1[(charLocation.Y-1)-k][charLocation.X+1] == 25))
			{
				level1[(charLocation.Y-1)-k][charLocation.X+1] = 1;
			}
			else
			{
				break;
			}
		}
	}
	//
	//laser down
	if(level1[charLocation.Y][charLocation.X] == 16) //down
	{
		level1[charLocation.Y][charLocation.X] = 20;
		for(int k = 1; charLocation.Y+k <= 17; k++)
		{
			if((level1[charLocation.Y+k][charLocation.X] == 21)||(level1[charLocation.Y+k][charLocation.X] == 25))
			{
				level1[charLocation.Y+k][charLocation.X] = 1;
			}
			else
			{
				break;
			}
		}
	}
	if(level1[charLocation.Y-1][charLocation.X-1] == 16) //left
	{
		level1[charLocation.Y-1][charLocation.X-1] = 20;
		for(int k = 1; (charLocation.Y-1)+k <= 17; k++)
		{
			if((level1[charLocation.Y-1+k][charLocation.X-1] == 21)||(level1[charLocation.Y-1+k][charLocation.X-1] == 25))
			{
				level1[charLocation.Y-1+k][charLocation.X-1] = 1;
			}
			else
			{
				break;
			}
		}
	}
	if(level1[charLocation.Y-1][charLocation.X+1] == 16) //right
	{
		level1[charLocation.Y-1][charLocation.X+1] = 20;
		for(int k = 1; (charLocation.Y-1)+k <= 17; k++)
		{
			if((level1[(charLocation.Y-1)+k][charLocation.X+1] == 21)||(level1[(charLocation.Y-1)+k][charLocation.X+1] == 25))
			{
				level1[(charLocation.Y-1)+k][charLocation.X+1] = 1;
			}
			else
			{
				break;
			}
		}
	}
	//
	//laser left
	if(level1[charLocation.Y-2][charLocation.X] == 18) //up
	{
		level1[charLocation.Y-2][charLocation.X] = 22;
		for(int k = 1; charLocation.X-k >= 0; k++)
		{
			if((level1[charLocation.Y-2][charLocation.X-k] == 25)||(level1[charLocation.Y-2][charLocation.X-k] == 21))
			{
				level1[charLocation.Y-2][charLocation.X-k] = 1;
			}
			else
			{
				break;
			}
		}
	}
	if(level1[charLocation.Y][charLocation.X] == 18) //down
	{
		level1[charLocation.Y][charLocation.X] = 22;
		for(int k = 1; charLocation.X-k >= 0; k++)
		{
			if((level1[charLocation.Y][charLocation.X-k] == 25)||(level1[charLocation.Y][charLocation.X-k] == 21))
			{
				level1[charLocation.Y][charLocation.X-k] = 1;
			}
			else
			{
				break;
			}
		}
	}
	if(level1[charLocation.Y-1][charLocation.X-1] == 18) //left
	{
		level1[charLocation.Y-1][charLocation.X-1] = 22;
		for(int k = 1; (charLocation.X-1)-k >= 0; k++)
		{
			if((level1[(charLocation.Y-1)][charLocation.X-1-k] == 25)||(level1[(charLocation.Y-1)][charLocation.X-1-k] == 21))
			{
				level1[(charLocation.Y-1)][charLocation.X-1-k] = 1;
			}
			else
			{
				break;
			}
		}
	}
	//
	//laser right
	if(level1[charLocation.Y-2][charLocation.X] == 17) //up
	{
		level1[charLocation.Y-2][charLocation.X] = 23;
		for(int k = 1; (charLocation.X)+k <= 49; k++)
		{
			if((level1[(charLocation.Y-2)][charLocation.X+k] == 25)||(level1[(charLocation.Y-2)][charLocation.X+k] == 21))
			{
				level1[(charLocation.Y-2)][charLocation.X+k] = 1;
			}
			else
			{
				break;
			}
		}
	}
	if(level1[charLocation.Y][charLocation.X] == 17) //down
	{
		level1[charLocation.Y][charLocation.X] = 23;
		for(int k = 1; charLocation.X+k <= 49; k++)
		{
			if((level1[charLocation.Y][charLocation.X+k] == 25)||(level1[charLocation.Y][charLocation.X+k] == 21))
			{
				level1[charLocation.Y][charLocation.X+k] = 1;
			}
			else
			{
				break;
			}
		}
	}
	if(level1[charLocation.Y-1][charLocation.X+1] == 17) //right
	{
		level1[charLocation.Y-1][charLocation.X+1] = 23;
		for(int k = 1; (charLocation.X+1)+k <= 49; k++)
		{
			if((level1[(charLocation.Y-1)][charLocation.X+1+k] == 25)||(level1[(charLocation.Y-1)][charLocation.X+1+k] == 21))
			{
				level1[(charLocation.Y-1)][charLocation.X+1+k] = 1;
			}
			else
			{
				break;
			}
		}
	}
	//
	for(int i = 0; i < 16; i++)
	{
		for(int j = 0; j < 48; j++)
		{
			//laser
			if((level1[i][j] == 15)||(level1[i][j] == 16)||(level1[i][j] == 17)||(level1[i][j] == 18))
			{
				if(level1[i][j] == 15)
				{
					for(int k = 1; i-k >= 0; k++)
					{
						if((level1[i-k][j] == 1)||level1[i-k][j] == 5)
						{
							level1[i-k][j] = 21;
						}
						else
						{
							break;
						}
					}
				}
				else if(level1[i][j] == 16)
				{
					for(int k = 1; i+k <= 12; k++)
					{
						if((level1[i+k][j] == 1)||level1[i+k][j] == 5)
						{
							level1[i+k][j] = 21;
						}
						else
						{
							break;
						}
					}
				}
				else if(level1[i][j] == 17)
				{
					for(int k = 1; j+k >= 0; k++)
					{
						if((level1[i][j+k] == 1)||level1[i][j+k] == 5)
						{
							level1[i][j+k] = 25;
						}
						else
						{
							break;
						}
					}
				}
				else if(level1[i][j] == 18)
				{
					for(int k = 1; j-k >= 0; k++)
					{
						if((level1[i][j-k] == 1)||level1[i][j-k] == 5)
						{
							level1[i][j-k] = 25;
						}
						else
						{
							break;
						}
					}
				}
			}
			//
			//guards
			//moving left
			if(level1[i][j] == 3)
			{
				//rotate up
				if(level1AI[i][j] == 11)
				{
					level1[i][j] = 6;
					if(level1[i][j-1] == 5)
					{
						level1[i][j-1] = 1;
					}
					if(level1[i][j-2] == 5)
					{
						level1[i][j-2] = 1;
					}
					if(level1[i][j-3] == 5)
					{
						level1[i][j-3] = 1;
					}
					if(level1[i-1][j] == 1)
					{
						level1[i-1][j] = 5;
						if(level1[i-2][j] == 1)
						{
							level1[i-2][j] = 5;
							if(level1[i-3][j] == 1)
							{
								level1[i-3][j] = 5;
							}
						}
					}
					continue;
				}
				//
				//rotate down
				if(level1AI[i][j] == 12)
				{
					level1[i][j] = 7;
					if(level1[i][j-1] == 5)
					{
						level1[i][j-1] = 1;
					}
					if(level1[i][j-2] == 5)
					{
						level1[i][j-2] = 1;
					}
					if(level1[i][j-3] == 5)
					{
						level1[i][j-3] = 1;
					}
					if(level1[i+1][j] == 1)
					{
						level1[i+1][j] = 5;
						if(level1[i+2][j] == 1)
						{
							level1[i+2][j] = 5;
							if(level1[i+3][j] == 1)
							{
								level1[i+3][j] = 5;
							}
						}
					}
					continue;
				}
				//
				//rotate right
				if(level1AI[i][j] == 13)
				{
					level1[i][j] = 4;
					if(level1[i][j-1] == 5)
					{
						level1[i][j-1] = 1;
					}
					if(level1[i][j-2] == 5)
					{
						level1[i][j-2] = 1;
					}
					if(level1[i][j-3] == 5)
					{
						level1[i][j-3] = 1;
					}
					if(level1[i][j+1] == 1)
					{
						level1[i][j+1] = 5;
						if(level1[i][j+2] == 1)
						{
							level1[i][j+2] = 5;
							if(level1[i][j+3] == 1)
							{
								level1[i][j+3] = 5;
							}
						}
					}
					continue;
				}
				//
				level1[i][j] = 1;
				level1[i][j-1] = 3;
				if((level1[i][j-2] == 1)||(level1[i][j-2] == 5))
				{
					level1[i][j-2] = 5;
					if((level1[i][j-3] == 1)||(level1[i][j-3] == 5))
					{
						level1[i][j-3] = 5;
						if((level1[i][j-4] == 1)||(level1[i][j-4] == 5))
						{
							level1[i][j-4] = 5;
						}
					}
				}
				if(level1[i][j-2] == 19) //laser activator left
				{
					level1[i][j-2] = 15;
				}
				else if(level1[i][j-2] == 20)
				{
					level1[i][j-2] = 16;
				}
				else if(level1[i][j-2] == 22)
				{
					level1[i][j-2] = 18;
				}
				if(level1[i-1][j-1] == 19) //laser activator above
				{
					level1[i-1][j-1] = 15;
				}
				else if(level1[i-1][j-1] == 23)
				{
					level1[i-1][j-1] = 17;
				}
				else if(level1[i-1][j-1] == 22)
				{
					level1[i-1][j-1] = 18;
				}
				if(level1[i+1][j-1] == 20) //laser activator below
				{
					level1[i+1][j-1] = 16;
				}
				else if(level1[i+1][j-1] == 23)
				{
					level1[i+1][j-1] = 17;
				}
				else if(level1[i+1][j-1] == 22)
				{
					level1[i+1][j-1] = 18;
				}
				continue;
			}
			//
			//moving right
			else if(level1[i][j] == 4)
			{
				//rotate left
				if(level1AI[i][j] == 14)
				{
					level1[i][j] = 3;
					if(level1[i][j+1] == 5)
					{
						level1[i][j+1] = 1;
					}
					if(level1[i][j+2] == 5)
					{
						level1[i][j+2] = 1;
					}
					if(level1[i][j+3] == 5)
					{
						level1[i][j+3] = 1;
					}
					if(level1[i][j-1] == 1)
					{
						level1[i][j-1] = 5;
						if(level1[i][j-2] == 1)
						{
							level1[i][j-2] = 5;
							if(level1[i][j-3] == 1)
							{
								level1[i][j-3] = 5;
							}
						}
					}
					continue;
				}
				//
				//rotate up
				if(level1AI[i][j] == 11)
				{
					level1[i][j] = 6;
					if(level1[i][j+1] == 5)
					{
						level1[i][j+1] = 1;
					}
					if(level1[i][j+2] == 5)
					{
						level1[i][j+2] = 1;
					}
					if(level1[i][j+3] == 5)
					{
						level1[i][j+3] = 1;
					}
					if(level1[i-1][j] == 1)
					{
						level1[i-1][j] = 5;
						if(level1[i-2][j] == 1)
						{
							level1[i-2][j] = 5;
							if(level1[i-3][j] == 1)
							{
								level1[i-3][j] = 5;
							}
						}
					}
					continue;
				}
				//
				//rotate down
				if(level1AI[i][j] == 12)
				{
					level1[i][j] = 7;
					if(level1[i][j+1] == 5)
					{
						level1[i][j+1] = 1;
					}
					if(level1[i][j+2] == 5)
					{
						level1[i][j+2] = 1;
					}
					if(level1[i][j+3] == 5)
					{
						level1[i][j+3] = 1;
					}
					if(level1[i+1][j] == 1)
					{
						level1[i+1][j] = 5;
						if(level1[i+2][j] == 1)
						{
							level1[i+2][j] = 5;
							if(level1[i+3][j] == 1)
							{
								level1[i+3][j] = 5;
							}
						}
					}
					continue;
				}
				//
				level1[i][j] = 1;
				level1[i][j+1] = 4;
				if((level1[i][j+2] == 1)||(level1[i][j+2] == 5))
				{
					level1[i][j+2] = 5;
					if((level1[i][j+3] == 1)||(level1[i][j+3] == 5))
					{
						level1[i][j+3] = 5;
						if((level1[i][j+4] == 1)||(level1[i][j+4] == 5))
						{
							level1[i][j+4] = 5;
						}
					}
				}
				j++;
				if(level1[i][j+1] == 19) //laser activator right
				{
					level1[i][j+1] = 15;
				}
				else if(level1[i][j+1] == 20)
				{
					level1[i][j+1] = 16;
				}
				else if(level1[i][j+1] == 23)
				{
					level1[i][j+1] = 17;
				}
				if(level1[i-1][j] == 19) //laser activator above
				{
					level1[i-1][j] = 15;
				}
				else if(level1[i-1][j] == 23)
				{
					level1[i-1][j] = 17;
				}
				else if(level1[i-1][j] == 22)
				{
					level1[i-1][j] = 18;
				}
				if(level1[i+1][j] == 20) //laser activator below
				{
					level1[i+1][j] = 16;
				}
				else if(level1[i+1][j] == 23)
				{
					level1[i+1][j] = 17;
				}
				else if(level1[i+1][j] == 22)
				{
					level1[i+1][j] = 18;
				}
				continue;
			}
			//
			//moving up
			else if(level1[i][j] == 6)
			{
				//rotate left
				if(level1AI[i][j] == 14)
				{
					level1[i][j] = 3;
					if(level1[i-1][j] == 5)
					{
						level1[i-1][j] = 1;
					}
					if(level1[i-2][j] == 5)
					{
						level1[i-2][j] = 1;
					}
					if(level1[i-3][j] == 5)
					{
						level1[i-3][j] = 1;
					}
					if(level1[i][j-1] == 1)
					{
						level1[i][j-1] = 5;
						if(level1[i][j-2] == 1)
						{
							level1[i][j-2] = 5;
							if(level1[i][j-3] == 1)
							{
								level1[i][j-3] = 5;
							}
						}
					}
					continue;
				}
				//
				//rotate right
				if(level1AI[i][j] == 13)
				{
					level1[i][j] = 4;
					if(level1[i-1][j] == 5)
					{
						level1[i-1][j] = 1;
					}
					if(level1[i-2][j] == 5)
					{
						level1[i-2][j] = 1;
					}
					if(level1[i-3][j] == 5)
					{
						level1[i-3][j] = 1;
					}
					if(level1[i][j+1] == 1)
					{
						level1[i][j+1] = 5;
						if(level1[i][j+2] == 1)
						{
							level1[i][j+2] = 5;
							if(level1[i][j+3] == 1)
							{
								level1[i][j+3] = 5;
							}
						}
					}
					continue;
				}
				//
				//rotate down
				if(level1AI[i][j] == 12)
				{
					level1[i][j] = 7;
					if(level1[i-1][j] == 5)
					{
						level1[i-1][j] = 1;
					}
					if(level1[i-2][j] == 5)
					{
						level1[i-2][j] = 1;
					}
					if(level1[i-3][j] == 5)
					{
						level1[i-3][j] = 1;
					}
					if(level1[i+1][j] == 1)
					{
						level1[i+1][j] = 5;
						if(level1[i+2][j] == 1)
						{
							level1[i+2][j] = 5;
							if(level1[i+3][j] == 1)
							{
								level1[i+3][j] = 5;
							}
						}
					}
					continue;
				}
				//
				level1[i][j] = 1;
				level1[i-1][j] = 6;
				if((level1[i-2][j] == 1)||(level1[i-2][j] == 5))
				{
					level1[i-2][j] = 5;
					if((level1[i-3][j] == 1)||(level1[i-3][j] == 5))
					{
						level1[i-3][j] = 5;
						if((level1[i-4][j] == 1)||(level1[i-4][j] == 5))
						{
							level1[i-4][j] = 5;
						}
					}
				}
				if(level1[i-1][j+1] == 19) //laser activator right
				{
					level1[i-1][j+1] = 15;
				}
				else if(level1[i-1][j+1] == 20)
				{
					level1[i-1][j+1] = 16;
				}
				else if(level1[i-1][j+1] == 23)
				{
					level1[i-1][j+1] = 17;
				}
				if(level1[i-2][j] == 19) //laser activator above
				{
					level1[i-2][j] = 15;
				}
				else if(level1[i-2][j] == 23)
				{
					level1[i-2][j] = 17;
				}
				else if(level1[i-2][j] == 22)
				{
					level1[i-2][j] = 18;
				}
				if(level1[i-1][j-1] == 20) //laser activator left
				{
					level1[i-1][j-1] = 16;
				}
				else if(level1[i-1][j-1] == 20)
				{
					level1[i-1][j-1] = 16;
				}
				else if(level1[i-1][j-1] == 22)
				{
					level1[i-1][j-1] = 18;
				}
				j++;
				continue;
			}
			//
			//moving down
			else if(level1[i][j] == 7)
			{
				//rotate left
				if(level1AI[i][j] == 14)
				{
					level1[i][j] = 3;
					if(level1[i+1][j] == 5)
					{
						level1[i+1][j] = 1;
					}
					if(level1[i+2][j] == 5)
					{
						level1[i+2][j] = 1;
					}
					if(level1[i+3][j] == 5)
					{
						level1[i+3][j] = 1;
					}
					if(level1[i][j-1] == 1)
					{
						level1[i][j-1] = 5;
						if(level1[i][j-2] == 1)
						{
							level1[i][j-2] = 5;
							if(level1[i][j-3] == 1)
							{
								level1[i][j-3] = 5;
							}
						}
					}
					continue;
				}
				//
				//rotate right
				if(level1AI[i][j] == 13)
				{
					level1[i][j] = 4;
					if(level1[i+1][j] == 5)
					{
						level1[i+1][j] = 1;
					}
					if(level1[i+2][j] == 5)
					{
						level1[i+2][j] = 1;
					}
					if(level1[i+3][j] == 5)
					{
						level1[i+3][j] = 1;
					}
					if(level1[i][j+1] == 1)
					{
						level1[i][j+1] = 5;
						if(level1[i][j+2] == 1)
						{
							level1[i][j+2] = 5;
							if(level1[i][j+3] == 1)
							{
								level1[i][j+3] = 5;
							}
						}
					}
					continue;
				}
				//
				//rotate up
				if(level1AI[i][j] == 11)
				{
					level1[i][j] = 6;
					if(level1[i+1][j] == 5)
					{
						level1[i+1][j] = 1;
					}
					if(level1[i+2][j] == 5)
					{
						level1[i+2][j] = 1;
					}
					if(level1[i+3][j] == 5)
					{
						level1[i+3][j] = 1;
					}
					if(level1[i-1][j] == 1)
					{
						level1[i-1][j] = 5;
						if(level1[i-2][j] == 1)
						{
							level1[i-2][j] = 5;
							if(level1[i-3][j] == 1)
							{
								level1[i-3][j] = 5;
							}
						}
					}
					continue;
				}
				//
				level1[i][j] = 1;
				level1[i+1][j] = 8;
				if((level1[i+2][j] == 1)||(level1[i+2][j] == 5))
				{
					level1[i+2][j] = 5;
					if((level1[i+3][j] == 1)||(level1[i+3][j] == 5))
					{
						level1[i+3][j] = 5;
						if((level1[i+4][j] == 1)||(level1[i+4][j] == 5))
						{
							level1[i+4][j] = 5;
						}
					}
				}
				if(level1[i+1][j+1] == 19) //laser activator right
				{
					level1[i+1][j+1] = 15;
				}
				else if(level1[i+1][j+1] == 20)
				{
					level1[i+1][j+1] = 16;
				}
				else if(level1[i+1][j+1] == 23)
				{
					level1[i+1][j+1] = 17;
				}
				if(level1[i+1][j-1] == 19) //laser activator left
				{
					level1[i+1][j-1] = 15;
				}
				else if(level1[i+1][j-1] == 20)
				{
					level1[i+1][j-1] = 16;
				}
				else if(level1[i+1][j-1] == 22)
				{
					level1[i+1][j-1] = 18;
				}
				if(level1[i+2][j] == 20) //laser activator below
				{
					level1[i+2][j] = 16;
				}
				else if(level1[i+2][j] == 23)
				{
					level1[i+2][j] = 17;
				}
				else if(level1[i+2][j] == 22)
				{
					level1[i+2][j] = 18;
				}
				j++;
				continue;
			}
			else if(level1[i][j] == 8)
			{
				level1[i][j] = 7;
			}
			//
			//
		}
	}
}
void loadlight(){
	for(int i = 0; i < 16; i++)
	{
		for(int j = 0; j < 48; j++)
		{
			//guard
			//moving left
			if(level1[i][j] == 3)
			{
				if((level1[i][j-1] == 1)||(level1[i][j-1] == 5))
				{
					level1[i][j-1] = 5;
					if((level1[i][j-2] == 1)||(level1[i][j-2] == 5))
					{
						level1[i][j-2] = 5;
						if((level1[i][j-3] == 1)||(level1[i][j-3] == 5))
						{
							level1[i][j-3] = 5;
						}
					}
				}
				continue;
			}
			//
			//moving right
			else if(level1[i][j] == 4)
			{
				if((level1[i][j+1] == 1)||(level1[i][j+1] == 5))
				{
					level1[i][j+1] = 5;
					if((level1[i][j+2] == 1)||(level1[i][j+2] == 5))
					{
						level1[i][j+2] = 5;
						if((level1[i][j+3] == 1)||(level1[i][j+3] == 5))
						{
							level1[i][j+3] = 5;
						}
					}
				}
				j++;
				continue;
			}
			//
			//moving up
			else if(level1[i][j] == 6)
			{
				if((level1[i-1][j] == 1)||(level1[i-1][j] == 5))
				{
					level1[i-1][j] = 5;
					if((level1[i-2][j] == 1)||(level1[i-2][j] == 5))
					{
						level1[i-2][j] = 5;
						if((level1[i-3][j] == 1)||(level1[i-3][j] == 5))
						{
							level1[i-3][j] = 5;
						}
					}
				}
				j++;
				continue;
			}
			//
			//moving down
			else if(level1[i][j] == 7)
			{
				if((level1[i+1][j] == 1)||(level1[i+1][j] == 5))
				{
					level1[i+1][j] = 5;
					if((level1[i+2][j] == 1)||(level1[i+2][j] == 5))
					{
						level1[i+2][j] = 5;
						if((level1[i+3][j] == 1)||(level1[i+3][j] == 5))
						{
							level1[i+3][j] = 5;
						}
					}
				}
				j++;
				continue;
			}
			else if(level1[i][j] == 8)
			{
				level1[i][j] = 7;
			}
			//
			//
			//laser
			if(level1[i][j] == 15)
			{
				for(int k = i-1; k >= 0; k--)
				{
					if((level1[k][j] == 1)||(level1[k][j] == 5)||(level1[k][j] == 21)||(level1[k][j] == 25))
					{
						level1[k][j] = 21;
					}
					else
					{
						break;
					}
				}
			}
			else if(level1[i][j] == 16)
			{
				for(int k = i+1; k <= 16; k++)
				{
					if((level1[k][j] == 1)||(level1[k][j] == 5)||(level1[k][j] == 21)||(level1[k][j] == 25))
					{
						level1[k][j] = 21;
					}
					else
					{
						break;
					}
				}
			}
			else if(level1[i][j] == 17)
			{
				for(int k = j+1; k <= 48; k++)
				{
					if((level1[i][k] == 1)||(level1[i][k] == 5)||(level1[i][k] == 21)||(level1[i][k] == 25))
					{
						level1[i][k] = 25;
					}
					else
					{
						break;
					}
				}
			}
			else if(level1[i][j] == 18)
			{
				for(int k = j-1; k >= 0; k--)
				{
					if((level1[i][k] == 1)||(level1[i][k] == 5)||(level1[i][k] == 21)||(level1[i][k] == 25))
					{
						level1[i][k] = 25;
					}
					else
					{
						break;
					}
				}
			}
			//
		}
	}
}
void resetlevel()
{
	if(levelselected == 1)
	{
		for(int i = 0; i < 16; i++)
		{
			for(int j = 0; j < 48; j++)
			{
				level1[i][j] = blevel1[i][j];
			}
		}
	}
	else if(levelselected == 2)
	{
		for(int i = 0; i < 16; i++)
			{
				for(int j = 0; j < 48; j++)
				{
					level1[i][j] = level2[i][j];
				}
			}
	}
	else if(levelselected == 3)
	{
		for(int i = 0; i < 16; i++)
			{
				for(int j = 0; j < 48; j++)
				{
					level1[i][j] = level3[i][j];
				}
			}
	}
	else if(levelselected == 4)
	{
		for(int i = 0; i < 16; i++)
			{
				for(int j = 0; j < 48; j++)
				{
					level1[i][j] = level4[i][j];
				}
			}
	}
	else if(levelselected == 5)
	{
		for(int i = 0; i < 16; i++)
			{
				for(int j = 0; j < 48; j++)
				{
					level1[i][j] = level5[i][j];
				}
			}
	}
	else if(levelselected == 6)
	{
		for(int i = 0; i < 16; i++)
			{
				for(int j = 0; j < 48; j++)
				{
					level1[i][j] = level6[i][j];
				}
			}
	}
	else if(levelselected == 7)
	{
		for(int i = 0; i < 16; i++)
			{
				for(int j = 0; j < 48; j++)
				{
					level1[i][j] = level7[i][j];
				}
			}
	}
	else if(levelselected == 8)
	{
		for(int i = 0; i < 16; i++)
			{
				for(int j = 0; j < 48; j++)
				{
					level1[i][j] = level8[i][j];
				}
			}
	}
	else if(levelselected == 9)
	{
		for(int i = 0; i < 16; i++)
			{
				for(int j = 0; j < 48; j++)
				{
					level1[i][j] = level9[i][j];
				}
			}
	}
	else if(levelselected == 10)
	{
		for(int i = 0; i < 16; i++)
			{
				for(int j = 0; j < 48; j++)
				{
					level1[i][j] = level10[i][j];
				}
			}
	}
	else if(levelselected == 11)
	{
		for(int i = 0; i < 16; i++)
			{
				for(int j = 0; j < 48; j++)
				{
					level1[i][j] = level11[i][j];
				}
			}
	}
	else if(levelselected == 12)
	{
		for(int i = 0; i < 16; i++)
			{
				for(int j = 0; j < 48; j++)
				{
					level1[i][j] = level12[i][j];
				}
			}
	}
	else if(levelselected == 13)
	{
		for(int i = 0; i < 16; i++)
			{
				for(int j = 0; j < 48; j++)
				{
					level1[i][j] = level13[i][j];
				}
			}
	}
	else if(levelselected == 14)
	{
		for(int i = 0; i < 16; i++)
			{
				for(int j = 0; j < 48; j++)
				{
					level1[i][j] = level14[i][j];
				}
			}
	}
	else if(levelselected == 15)
	{
		for(int i = 0; i < 16; i++)
			{
				for(int j = 0; j < 48; j++)
				{
					level1[i][j] = level15[i][j];
				}
			}
	}
	charLocation.X = 1;
	charLocation.Y = 2;
	//g_dElapsedTime = 0.0;
}
int levelselect()
{  
	g_Console.clearBuffer(0x0F);
	COORD c ;
	colour(0x0F);
    cls();
	gotoXY(2,0);
	colour(colors[15]);
	std:: string line;
	std::ifstream myfile ("levelselect.txt");
	int ycoord = 0;
	if (myfile.is_open())
	{
		while ( getline (myfile,line) )
		{
			c.X = 0;
			c.Y = ycoord;
			g_Console.writeToBuffer(c, line);
			ycoord++;
		}
		myfile.close();
	}
	c.X = 24;
	c.Y = 8;
    g_Console.writeToBuffer(c, "Level 1");

	c.X = 24;
	c.Y = 12;
    g_Console.writeToBuffer(c, "Level 2");

	c.X = 24;
	c.Y = 16;
    g_Console.writeToBuffer(c, "Level 3");
	
	c.X = 24;
	c.Y = 20;
    g_Console.writeToBuffer(c, "Level 4");

	
	c.X = 24;
	c.Y = 24;
    g_Console.writeToBuffer(c, "Level 5");

	c.X = 44;
	c.Y = 8;
    g_Console.writeToBuffer(c, "Level 6");

	c.X = 44;
	c.Y = 12;
    g_Console.writeToBuffer(c, "Level 7");

	c.X = 44;
	c.Y = 16;
    g_Console.writeToBuffer(c, "Level 8");

	c.X = 44;
	c.Y = 20;
    g_Console.writeToBuffer(c, "Level 9");
	
	c.X = 44;
	c.Y = 24;
    g_Console.writeToBuffer(c, "Level 10");
	
	c.X = levelarrowX;
	c.Y = levelarrowY;
    g_Console.writeToBuffer(c, ">");

	 g_Console.flushBufferToConsole();

	gotoXY(2,0);
	int leftarrowX = levelarrowX;
	int leftarrowY = levelarrowY;
		//getInput();
		if(g_abKeyPressed[K_DOWN] && levelnumber != 5 && levelnumber != 10 && levelnumber != 15 && levelnumber != 20 && levelnumber != 25 && g_dBounceTime < g_dElapsedTime)
		{
			g_dBounceTime = g_dElapsedTime + 0.125;
			levelnumber += 1;
			c.X = leftarrowX;
			c.Y = leftarrowY;
			g_Console.writeToBuffer(c, " ");
			leftarrowY += 4;
			c.X = leftarrowX;
			c.Y = leftarrowY;
			g_Console.writeToBuffer(c, ">");
			gotoXY(2,0);
			g_Console.flushBufferToConsole();
		}
		else if(g_abKeyPressed[K_UP] && levelnumber != 1 && levelnumber != 6 && levelnumber != 11 && levelnumber != 16 && levelnumber != 21 && g_dBounceTime < g_dElapsedTime)
		{
			g_dBounceTime = g_dElapsedTime + 0.125;
			levelnumber -= 1;
			c.X = leftarrowX;
			c.Y = leftarrowY;
			g_Console.writeToBuffer(c, " ");
			leftarrowY -= 4;
			c.X = leftarrowX;
			c.Y = leftarrowY;
			g_Console.writeToBuffer(c, ">");
			gotoXY(2,0);
			g_Console.flushBufferToConsole();
		}
		else if(g_abKeyPressed[K_LEFT] && levelnumber > 5 && g_dBounceTime < g_dElapsedTime)
		{
			g_dBounceTime = g_dElapsedTime + 0.125;
			levelnumber -= 5;
			c.X = leftarrowX;
			c.Y = leftarrowY;
			g_Console.writeToBuffer(c, " ");
			leftarrowX -= 20;
			c.X = leftarrowX;
			c.Y = leftarrowY;
			g_Console.writeToBuffer(c, ">");
			gotoXY(2,0);
			g_Console.flushBufferToConsole();
		}
		else if(g_abKeyPressed[K_RIGHT] && levelnumber < 6 && g_dBounceTime < g_dElapsedTime)
		{
			g_dBounceTime = g_dElapsedTime + 0.125;
			levelnumber += 5;
			c.X = leftarrowX;
			c.Y = leftarrowY;
			g_Console.writeToBuffer(c, " ");
			leftarrowX += 20;
			c.X = leftarrowX;
			c.Y = leftarrowY;
			g_Console.writeToBuffer(c, ">");
			gotoXY(2,0);
			g_Console.flushBufferToConsole();
		}
		else if(g_abKeyPressed[K_RETURN] && g_dBounceTime < g_dElapsedTime)
		{
			g_Console.clearBuffer(0x0F);
			return levelnumber;
		}
		else if(g_abKeyPressed[K_ESCAPE] && g_dBounceTime < g_dElapsedTime)
		{	
			g_dBounceTime = g_dElapsedTime + 0.125;
			return 68;
		}
	levelarrowX = leftarrowX;
	levelarrowY = leftarrowY;
	return 0;
}
int menu()  
{   
	g_Console.clearBuffer(0x0F);
	COORD c;
    cls();
    int count = count2 ;

	renderMainMenu();

	int frequency = 2640;    
    if ( g_abKeyPressed[K_DOWN] == 1 && g_dBounceTime < g_dElapsedTime)    
    {
		g_dBounceTime = g_dElapsedTime + 0.125;
        if ( count == 0 )   
        {	
			c.X = 45;
			c.Y = 17;
            g_Console.writeToBuffer(c, " "); 

			c.X = 45;
			c.Y = 19;
            g_Console.writeToBuffer(c, ">");

            count = 1 ;       
			frequency -= 300;
			Beep(frequency, 60);
			g_Console.flushBufferToConsole();
        }
        else if ( count == 1 )   
        {
				
            c.X = 45;
			c.Y = 19;
			g_Console.writeToBuffer(c, " ");

			c.X = 45;
			c.Y = 21;
            g_Console.writeToBuffer(c, ">");

            count = 2 ;   
			frequency -= 300;
			Beep(frequency, 60);
			g_Console.flushBufferToConsole();
        }
        else if ( count == 2 ) 
        {
			c.X = 45;
			c.Y = 21;
            g_Console.writeToBuffer(c, " ");

            c.X = 45;
			c.Y = 23;
            g_Console.writeToBuffer(c, ">");
               
            count = 3 ;    
			frequency -= 300;
			Beep(frequency, 60);
			g_Console.flushBufferToConsole();
        }
			
    }   
    else if ( g_abKeyPressed[K_UP] == 1 && g_dBounceTime < g_dElapsedTime)     
    {
		g_dBounceTime = g_dElapsedTime + 0.125;
        if ( count == 1 )  
        {
			c.X = 45;
			c.Y = 19;
            g_Console.writeToBuffer(c, " ");
                

			c.X = 45;
			c.Y = 17;
            g_Console.writeToBuffer(c, ">");           
            count = 0 ;   
			frequency += 300;
			Beep(frequency, 60);
			g_Console.flushBufferToConsole();
        }
        else if ( count == 2 ) 
        {
			c.X = 45;
			c.Y = 21;
            g_Console.writeToBuffer(c, " ");
                
			c.X = 45;
			c.Y = 19;
            g_Console.writeToBuffer(c, ">");
                
            count = 1 ;    
			frequency += 300;
			Beep(frequency, 60);
			g_Console.flushBufferToConsole();
         }
         else if ( count == 3 )   
         {
			c.X = 45;
			c.Y = 23;
            g_Console.writeToBuffer(c, " ");
                
			c.X = 45;
			c.Y = 21;
            g_Console.writeToBuffer(c, ">");
                
            count = 2 ;    
			frequency += 300;
			Beep(frequency, 60);
			g_Console.flushBufferToConsole();
         }
    }     
    else if ( g_abKeyPressed[K_RETURN] == 1 )        
    {
		g_dBounceTime = g_dElapsedTime + 0.125;
		if ( count == 0 )  
        {
            return 1;  
        }
        if ( count == 1 )   
        {
            levelnumber = 11 ;
            return 2;    
        }  
        if ( count == 2 )  
        {
            return 3;   
        }
        if ( count == 3 )      
        {

			c.X = 30;
			c.Y = 10;
            g_Console.writeToBuffer(c, "Are you SURE?");
			g_Console.flushBufferToConsole();
            Sleep(500);

			c.X = 50;
			c.Y = 6;
            g_Console.writeToBuffer(c, "SRSLY");
			g_Console.flushBufferToConsole();
            Sleep(400);

			c.X = 13;
			c.Y = 27;
            g_Console.writeToBuffer(c, "REALLY?");
			g_Console.flushBufferToConsole();
			Sleep(300);

			c.X = 43;
			c.Y = 21;
            g_Console.writeToBuffer(c, "BUT WHY");
			g_Console.flushBufferToConsole();
            Sleep(200);


			c.X = 3;
			c.Y = 16;
            g_Console.writeToBuffer(c, "I THOUGHT YOU LOVED ME");
			g_Console.flushBufferToConsole();
            Sleep(200);       

			c.X = 70;
			c.Y = 23;
            g_Console.writeToBuffer(c, ":-("); 
			g_Console.flushBufferToConsole();
            Sleep(200); 

			c.X = 17;
			c.Y = 5;
            g_Console.writeToBuffer(c, "GET BACK HERE");
			g_Console.flushBufferToConsole();
            Sleep(200);   

			c.X = 39;
			c.Y = 14;
            g_Console.writeToBuffer(c, "DONT PRESS ENTER");
			g_Console.flushBufferToConsole();
            Sleep(200);      

			c.X = 39;
			c.Y = 17;
            g_Console.writeToBuffer(c, "NOOOOOOOOOO");
			g_Console.flushBufferToConsole();
                
			gotoXY(0,0);
            return 69;

        }   
    } 
	count2 = count;
	return 0;
}
int challenge() 
{
	g_Console.clearBuffer(0x0F);
	COORD c ;
    cls();     
	renderChallenges();
    if ( g_abKeyPressed[K_ESCAPE] == 1 )   
    {
        levelnumber = 1; 
        g_dBounceTime = g_dElapsedTime + 0.125;
	    return 68; 
    }
    if ( ( g_abKeyPressed[K_DOWN] == 1 ) && ( challengearrowY < 26 ) && g_dBounceTime < g_dElapsedTime )  
    {
		g_dBounceTime = g_dElapsedTime + 0.125;
        c.X = challengearrowX;
		c.Y = challengearrowY;
		g_Console.writeToBuffer(c, " ");
		challengearrowY += 4;
		c.X = challengearrowX;
		c.Y = challengearrowY;
		g_Console.writeToBuffer(c, ">");      
        levelnumber += 1 ;
    } 
    if ( ( g_abKeyPressed[K_UP] == 1 ) && ( challengearrowY > 10 ) && g_dBounceTime < g_dElapsedTime )  
    {
		g_dBounceTime = g_dElapsedTime + 0.125;
        c.X = challengearrowX;
		c.Y = challengearrowY;
		g_Console.writeToBuffer(c, " ");
		challengearrowY -= 4;
		c.X = challengearrowX;
		c.Y = challengearrowY;
		g_Console.writeToBuffer(c, ">");    
        levelnumber -= 1 ; 
    }       
    if ( (g_abKeyPressed[K_RETURN] == 1 ) && g_dBounceTime < g_dElapsedTime )     
    {
        g_Console.clearBuffer(0x0F);     
        return levelnumber ;
    }
	g_Console.flushBufferToConsole();
	return 0;
}   
int stats()  
{     
	cls();
	COORD c;
	g_Console.clearBuffer(0x0F);
	c.X = 0;
	int ycoord = 0;
	c.Y = ycoord;
    std:: string line;
	std::ifstream myfile ("stats.txt");    
	if (myfile.is_open())
	{
		while ( getline (myfile,line) )
		{
			c.Y = ycoord;
			g_Console.writeToBuffer(c, line);
			ycoord++;
			cout << line << '\n';
		}
		myfile.close();
	}
	c.X = 5 ;   
	c.Y = 10 ;    
	g_Console.writeToBuffer(c,"You have died ");
	c.X = 19 ;    
	g_Console.writeToBuffer(c,static_cast<char>(deathcounter+48)) ;    
	c.X = 24 ;    
	g_Console.writeToBuffer(c,"times.");

	c.X = 5 ;   
	c.Y = 15 ;    
	g_Console.writeToBuffer(c,"You have completed ");
	c.X = 24 ;    
	g_Console.writeToBuffer(c,static_cast<char>(wincounter+48)) ;    
	c.X = 29 ;    
	g_Console.writeToBuffer(c,"levels.");
    getInput();
    if ( g_abKeyPressed[K_ESCAPE] == 1 )    
    {
        return 4;  
    } 
	g_Console.flushBufferToConsole();
	return 0;
}