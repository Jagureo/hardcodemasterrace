
#include "game.h"
#include "Framework\console.h"
#include"levelmap.txt"
#include <iostream>
#include <iomanip>
#include <sstream>
#include <conio.h>
#include <string>
#include <fstream>

using std::cin;
using std::cout;
using std::endl;

double  g_dElapsedTime;
double  g_dDeltaTime;
bool    g_abKeyPressed[K_COUNT];
int levelnumber;
int y;
bool levelfix = true;
bool keyinputaa = true;			
int rainbowhere = 9;
int gamestate = 1;
int levelno = 1;
int level1[16][48];
int level1reset[16][48];
int level1AI[16][48];
void loadlevel();
void loadlight();

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


void renderMap()
{
    // Set up sample colours, and output shadings
 

    COORD c;
    for (int i = 0; i < 12; ++i)
    {
        c.X = 5 * i;
        c.Y = i + 1;
        colour(colors[i]);
        g_Console.writeToBuffer(c, " °±²Û", colors[i]);
    }
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
	
	switch(gamestate)
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
		
	}
	
    // get the delta time
    g_dElapsedTime += dt;
    g_dDeltaTime = dt;

	  // Updating the location of the character based on the key press
    if (g_abKeyPressed[K_UP])
    {
		bool nocollide = collisiondetection(1);
		if(nocollide)
		{
			Beep(1440, 60);
			charLocation.Y--; 
			keyinputaa = true;
		}
		//render();
    }
    else if (g_abKeyPressed[K_LEFT])
    {
		bool nocollide = collisiondetection(2);
		if(nocollide)
		{
			Beep(1440, 60);
			charLocation.X--; 
			keyinputaa = true;
		}
		//render();
    }
    else if (g_abKeyPressed[K_DOWN])
    {
		bool nocollide = collisiondetection(3);
		if(nocollide)
		{
			Beep(1440, 60);
			charLocation.Y++; 
			keyinputaa = true;
		}
		//render();
    }
    else if (g_abKeyPressed[K_RIGHT])
    {
		bool nocollide = collisiondetection(4);
		if(nocollide)
		{
			Beep(1440, 60);
			charLocation.X++; 
			keyinputaa = true;
		}
		//render();
    }

    // quits the game i	f player hits the escape key
    if (g_abKeyPressed[K_ESCAPE])
		gamestate = 1;
        //g_quitGame = true;

   /* switch (g_eGameState)
    {
        case S_SPLASHSCREEN : splashScreenWait(); // game logic for the splash screen
            break;
        case S_GAME: gameplay(); // gameplay logic when we are in the game
            break;
    }*/
	
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
   /* // Set precision for floating point output
    g_dElapsedTime = 0.0;
    g_dBounceTime = 0.0;

    // sets the initial state for the game
    g_eGameState = S_SPLASHSCREEN;

    g_sChar.m_cLocation.X = g_Console.getConsoleSize().X / 2;
    g_sChar.m_cLocation.Y = g_Console.getConsoleSize().Y / 2;
    g_sChar.m_bActive = true;
    // sets the width, height and the font name to use in the console
    g_Console.setConsoleFont(0, 16, L"Consolas");*/
}
void render()
{
	//g_Console.clearBuffer(0x1F);
	COORD c ;
	//clearScreen();
	switch(gamestate)
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
		
	}

	renderToScreen();

	////////////////////////
	if(gamestate == 1)
	{
		int x = newmainmenu();
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
					level1reset[i][j] = blevel1reset[i][j];
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
			//render();
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
					level1reset[i][j] = level2reset[i][j];
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
			//render();
		}
		else
		{
			errorreport();
			return;
		}
	}
	else
	{
		if(!keyinputaa)
		{
			return;
		}
		keyinputaa = false;

		loadlevel();
		loadlight();

		// clear previous screen
		colour(0x0F);
		//cls();
		//g_Console.clearBuffer(0x0F);
		//render the game

		//render test screen code (not efficient at all)
		/*const WORD colors[] =   {
								0x1A, 0x2B, 0x3C, 0x4D, 0x5E, 0x6F,
								0xA1, 0xB2, 0xC3, 0xD4, 0xE5, 0xF6,
								0x0F, 0x0E, 0x09, 0x0A
								};*/
	
		/*for (int i = 0; i < 12; ++i)
		{
			gotoXY(3*i,i+1);
			colour(colors[i]);
			std::cout << "WOW";
		}*/
		gotoXY(0,1);
		int xcoord = 0;
		int ycoord = 1;
		for (int i = 0; i < 16; ++i)
		{
			for(int j = 0; j < 48; ++j)
			{
				//colour(colors[12]);
				//gotoXY(j,i+1);
				if(level1[i][j] == 0)
				{
					//cout << static_cast<char>(219);
					c.X = xcoord;
					c.Y = ycoord;
					//g_Console.writeToBuffer(c, static_cast<char>(219));
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
					//cout << static_cast<char>(1);
					c.X = xcoord;
					c.Y = ycoord;
					//g_Console.writeToBuffer(c, static_cast<char>(1));
					g_Console.writeToBuffer(c, static_cast<char>(1));
					xcoord++;
					continue;
				}
				else if((level1[i][j] == 3)||(level1[i][j] == 4)||(level1[i][j] == 6)||(level1[i][j] == 7))
				{
					//cout << static_cast<char>(2);
					c.X = xcoord;
					c.Y = ycoord;
					//g_Console.writeToBuffer(c, static_cast<char>(2));
					g_Console.writeToBuffer(c, static_cast<char>(2));
					xcoord++;
					continue;
				}
				else if(level1[i][j] == 5)
				{
					colour(colors[13]);
					//cout << static_cast<char>(15);
					c.X = xcoord;
					c.Y = ycoord;
					//g_Console.writeToBuffer(c, static_cast<char>(15));
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
						//cout << '^';
						c.X = xcoord;
						c.Y = ycoord;
						g_Console.writeToBuffer(c, '^');
					}
					else if(level1[i][j] == 16)
					{
						//cout << 'V';
						c.X = xcoord;
						c.Y = ycoord;
						g_Console.writeToBuffer(c, 'V');
					}
					else if(level1[i][j] == 17)
					{
						//cout << '>';
						c.X = xcoord;
						c.Y = ycoord;
						g_Console.writeToBuffer(c, '>');
					}
					else if(level1[i][j] == 18)
					{
						//cout << '<';
						c.X = xcoord;
						c.Y = ycoord;
						g_Console.writeToBuffer(c, '<');
					}
					colour(colors[12]);
					xcoord++;
					continue;
				}
				else if(level1[i][j] == 19)
				{
					//cout << '^';
					c.X = xcoord;
					c.Y = ycoord;
					g_Console.writeToBuffer(c, '^');
					xcoord++;
					continue;
				}
				else if(level1[i][j] == 20)
				{
					//cout << 'V';
					c.X = xcoord;
					c.Y = ycoord;
					g_Console.writeToBuffer(c, 'V');
					xcoord++;
					continue;
				}
				else if(level1[i][j] == 23)
				{
					//cout << '>';
					c.X = xcoord;
					c.Y = ycoord;
					g_Console.writeToBuffer(c, '>');
					xcoord++;
					continue;
				}
				else if(level1[i][j] == 22)
				{
					//cout << '<';
					c.X = xcoord;
					c.Y = ycoord;
					g_Console.writeToBuffer(c, '<');
					xcoord++;
					continue;
				}
				else if(level1[i][j] == 21)
				{
					colour(colors[16]);
					//cout << '|';
					c.X = xcoord;
					c.Y = ycoord;
					g_Console.writeToBuffer(c, '|');
					xcoord++;
					colour(colors[12]);
					continue;
				}
				else if(level1[i][j] == 25)
				{
					colour(colors[16]);
					//cout << '-';
					c.X = xcoord;
					c.Y = ycoord;
					g_Console.writeToBuffer(c, '-');
					xcoord++;
					colour(colors[12]);
					continue;
				}
				else if(level1[i][j] == 69)
				{
					//cout << 'x';
					c.X = xcoord;
					c.Y = ycoord;
					g_Console.writeToBuffer(c, 'x');
					xcoord++;
					continue;
				}
			}
			//cout << '\n';
			xcoord = 0;
			ycoord++;
		}
		g_Console.flushBufferToConsole();
		if(level1[charLocation.Y-1][charLocation.X] == 69)
			{
				resetlevel();
				//loadlevel();
				keyinputaa = true;
				render();
				gotoXY (0, 17);
				colour(colorskappa[14]);
				//cout<<"    "<<static_cast<char>(219)<<static_cast<char>(219)<<static_cast<char>(187)<<"   "<<static_cast<char>(219)<<static_cast<char>(219)<<static_cast<char>(187)<<" "<<static_cast<char>(219)<<static_cast<char>(219)<<static_cast<char>(219)<<static_cast<char>(219)<<static_cast<char>(219)<<static_cast<char>(219)<<static_cast<char>(187)<<" "<<static_cast<char>(219)<<static_cast<char>(219)<<static_cast<char>(187)<<"   "<<static_cast<char>(219)<<static_cast<char>(219)<<static_cast<char>(187)<<"    "<<static_cast<char>(219)<<static_cast<char>(219)<<static_cast<char>(187)<<"    "<<static_cast<char>(219)<<static_cast<char>(219)<<static_cast<char>(187)<<static_cast<char>(219)<<static_cast<char>(219)<<static_cast<char>(187)<<static_cast<char>(219)<<static_cast<char>(219)<<static_cast<char>(219)<<static_cast<char>(187)<<"   "<<static_cast<char>(219)<<static_cast<char>(219)<<static_cast<char>(187)<<endl;
				//cout<<"    "<<static_cast<char>(200)<<static_cast<char>(219)<<static_cast<char>(219)<<static_cast<char>(187)<<" "<<static_cast<char>(219)<<static_cast<char>(219)<<static_cast<char>(201)<<static_cast<char>(188)<<static_cast<char>(219)<<static_cast<char>(219)<<static_cast<char>(201)<<static_cast<char>(205)<<static_cast<char>(205)<<static_cast<char>(205)<<static_cast<char>(219)<<static_cast<char>(219)<<static_cast<char>(187)<<static_cast<char>(219)<<static_cast<char>(219)<<static_cast<char>(186)<<"   "<<static_cast<char>(219)<<static_cast<char>(219)<<static_cast<char>(186)<<"    "<<static_cast<char>(219)<<static_cast<char>(219)<<static_cast<char>(186)<<"    "<<static_cast<char>(219)<<static_cast<char>(219)<<static_cast<char>(186)<<static_cast<char>(219)<<static_cast<char>(219)<<static_cast<char>(186)<<static_cast<char>(219)<<static_cast<char>(219)<<static_cast<char>(219)<<static_cast<char>(219)<<static_cast<char>(187)<<"  "<<static_cast<char>(219)<<static_cast<char>(219)<<static_cast<char>(186)<<endl;
				//cout<<"    "<<" "<<static_cast<char>(200)<<static_cast<char>(219)<<static_cast<char>(219)<<static_cast<char>(219)<<static_cast<char>(219)<<static_cast<char>(201)<<static_cast<char>(188)<<" "<<static_cast<char>(219)<<static_cast<char>(219)<<static_cast<char>(186)<<"   "<<static_cast<char>(219)<<static_cast<char>(219)<<static_cast<char>(186)<<static_cast<char>(219)<<static_cast<char>(219)<<static_cast<char>(186)<<"   "<<static_cast<char>(219)<<static_cast<char>(219)<<static_cast<char>(186)<<"    "<<static_cast<char>(219)<<static_cast<char>(219)<<static_cast<char>(186)<<" "<<static_cast<char>(219)<<static_cast<char>(187)<<" "<<static_cast<char>(219)<<static_cast<char>(219)<<static_cast<char>(186)<<static_cast<char>(219)<<static_cast<char>(219)<<static_cast<char>(186)<<static_cast<char>(219)<<static_cast<char>(219)<<static_cast<char>(201)<<static_cast<char>(219)<<static_cast<char>(219)<<static_cast<char>(187)<<" "<<static_cast<char>(219)<<static_cast<char>(219)<<static_cast<char>(186)<<endl;
				//cout<<"    "<<"  "<<static_cast<char>(200)<<static_cast<char>(219)<<static_cast<char>(219)<<static_cast<char>(201)<<static_cast<char>(188)<<"  "<<static_cast<char>(219)<<static_cast<char>(219)<<static_cast<char>(186)<<"   "<<static_cast<char>(219)<<static_cast<char>(219)<<static_cast<char>(186)<<static_cast<char>(219)<<static_cast<char>(219)<<static_cast<char>(186)<<"   "<<static_cast<char>(219)<<static_cast<char>(219)<<static_cast<char>(186)<<"    "<<static_cast<char>(219)<<static_cast<char>(219)<<static_cast<char>(186)<<static_cast<char>(219)<<static_cast<char>(219)<<static_cast<char>(219)<<static_cast<char>(187)<<static_cast<char>(219)<<static_cast<char>(219)<<static_cast<char>(186)<<static_cast<char>(219)<<static_cast<char>(219)<<static_cast<char>(186)<<static_cast<char>(219)<<static_cast<char>(219)<<static_cast<char>(186)<<static_cast<char>(200)<<static_cast<char>(219)<<static_cast<char>(219)<<static_cast<char>(187)<<static_cast<char>(219)<<static_cast<char>(219)<<static_cast<char>(186)<<endl;
				//cout<<"    "<<"   "<<static_cast<char>(219)<<static_cast<char>(219)<<static_cast<char>(186)<<"   "<<static_cast<char>(200)<<static_cast<char>(219)<<static_cast<char>(219)<<static_cast<char>(219)<<static_cast<char>(219)<<static_cast<char>(219)<<static_cast<char>(219)<<static_cast<char>(201)<<static_cast<char>(188)<<static_cast<char>(200)<<static_cast<char>(219)<<static_cast<char>(219)<<static_cast<char>(219)<<static_cast<char>(219)<<static_cast<char>(219)<<static_cast<char>(219)<<static_cast<char>(201)<<static_cast<char>(188)<<"    "<<static_cast<char>(200)<<static_cast<char>(219)<<static_cast<char>(219)<<static_cast<char>(219)<<static_cast<char>(201)<<static_cast<char>(219)<<static_cast<char>(219)<<static_cast<char>(219)<<static_cast<char>(201)<<static_cast<char>(188)<<static_cast<char>(219)<<static_cast<char>(219)<<static_cast<char>(186)<<static_cast<char>(219)<<static_cast<char>(219)<<static_cast<char>(186)<<" "<<static_cast<char>(200)<<static_cast<char>(219)<<static_cast<char>(219)<<static_cast<char>(219)<<static_cast<char>(219)<<static_cast<char>(186)<<endl;
				//cout<<"    "<<"   "<<static_cast<char>(200)<<static_cast<char>(205)<<static_cast<char>(188)<<"    "<<static_cast<char>(200)<<static_cast<char>(205)<<static_cast<char>(205)<<static_cast<char>(205)<<static_cast<char>(205)<<static_cast<char>(205)<<static_cast<char>(188)<<"  "<<static_cast<char>(200)<<static_cast<char>(205)<<static_cast<char>(205)<<static_cast<char>(205)<<static_cast<char>(205)<<static_cast<char>(205)<<static_cast<char>(188)<<"      "<<static_cast<char>(200)<<static_cast<char>(205)<<static_cast<char>(205)<<static_cast<char>(188)<<static_cast<char>(200)<<static_cast<char>(205)<<static_cast<char>(205)<<static_cast<char>(188)<<" "<<static_cast<char>(200)<<static_cast<char>(205)<<static_cast<char>(188)<<static_cast<char>(200)<<static_cast<char>(205)<<static_cast<char>(188)<<"  "<<static_cast<char>(200)<<static_cast<char>(205)<<static_cast<char>(205)<<static_cast<char>(205)<<static_cast<char>(188)<<endl;
				//cout<<"    "<<"        Press ESC to exit to Level Select screen";
				/*for(int i = 0; i < 7; i++)
				{
					cout << "    ";
					for(int j = 0; j < 58; j++)
					{
						cout << static_cast<char>(niyin[i][j]);
					}
					cout << endl;
				}
				*/
	std ::string wining;
  std::ifstream myfile ("youwin.txt");
  if (myfile.is_open())
  {
    while ( getline (myfile,wining) )
    {
      cout << wining << '\n';
    }
    myfile.close();
  }

  else cout << "Unable to open file"; 
				_getch();
				
			}
			else if(level1[charLocation.Y-1][charLocation.X] != 1)
			{
				resetlevel();
				//loadlevel();
				keyinputaa = true;
				render();
				gotoXY (0, 19);
				colour(colorskappa[14]);
				//cout<<"    "<<static_cast<char>(219)<<static_cast<char>(219)<<static_cast<char>(187)<<"   "<<static_cast<char>(219)<<static_cast<char>(219)<<static_cast<char>(187)<<" "<<static_cast<char>(219)<<static_cast<char>(219)<<static_cast<char>(219)<<static_cast<char>(219)<<static_cast<char>(219)<<static_cast<char>(219)<<static_cast<char>(187)<<" "<<static_cast<char>(219)<<static_cast<char>(219)<<static_cast<char>(187)<<"   "<<static_cast<char>(219)<<static_cast<char>(219)<<static_cast<char>(187)<<"    "<<static_cast<char>(219)<<static_cast<char>(219)<<static_cast<char>(187)<<"      "<<static_cast<char>(219)<<static_cast<char>(219)<<static_cast<char>(219)<<static_cast<char>(219)<<static_cast<char>(219)<<static_cast<char>(219)<<static_cast<char>(187)<<" "<<static_cast<char>(219)<<static_cast<char>(219)<<static_cast<char>(219)<<static_cast<char>(219)<<static_cast<char>(219)<<static_cast<char>(219)<<static_cast<char>(219)<<static_cast<char>(187)<<static_cast<char>(219)<<static_cast<char>(219)<<static_cast<char>(219)<<static_cast<char>(219)<<static_cast<char>(219)<<static_cast<char>(219)<<static_cast<char>(219)<<static_cast<char>(187)<<endl;
				//cout<<"    "<<static_cast<char>(200)<<static_cast<char>(219)<<static_cast<char>(219)<<static_cast<char>(187)<<" "<<static_cast<char>(219)<<static_cast<char>(219)<<static_cast<char>(201)<<static_cast<char>(188)<<static_cast<char>(219)<<static_cast<char>(219)<<static_cast<char>(201)<<static_cast<char>(205)<<static_cast<char>(205)<<static_cast<char>(205)<<static_cast<char>(219)<<static_cast<char>(219)<<static_cast<char>(187)<<static_cast<char>(219)<<static_cast<char>(219)<<static_cast<char>(186)<<"   "<<static_cast<char>(219)<<static_cast<char>(219)<<static_cast<char>(186)<<"    "<<static_cast<char>(219)<<static_cast<char>(219)<<static_cast<char>(186)<<"     "<<static_cast<char>(219)<<static_cast<char>(219)<<static_cast<char>(201)<<static_cast<char>(205)<<static_cast<char>(205)<<static_cast<char>(205)<<static_cast<char>(219)<<static_cast<char>(219)<<static_cast<char>(187)<<static_cast<char>(219)<<static_cast<char>(219)<<static_cast<char>(201)<<static_cast<char>(205)<<static_cast<char>(205)<<static_cast<char>(205)<<static_cast<char>(205)<<static_cast<char>(188)<<static_cast<char>(219)<<static_cast<char>(219)<<static_cast<char>(201)<<static_cast<char>(205)<<static_cast<char>(205)<<static_cast<char>(205)<<static_cast<char>(205)<<static_cast<char>(188)<<endl;
				//cout<<"    "<<" "<<static_cast<char>(200)<<static_cast<char>(219)<<static_cast<char>(219)<<static_cast<char>(219)<<static_cast<char>(219)<<static_cast<char>(201)<<static_cast<char>(188)<<" "<<static_cast<char>(219)<<static_cast<char>(219)<<static_cast<char>(186)<<"   "<<static_cast<char>(219)<<static_cast<char>(219)<<static_cast<char>(186)<<static_cast<char>(219)<<static_cast<char>(219)<<static_cast<char>(186)<<"   "<<static_cast<char>(219)<<static_cast<char>(219)<<static_cast<char>(186)<<"    "<<static_cast<char>(219)<<static_cast<char>(219)<<static_cast<char>(186)<<"     "<<static_cast<char>(219)<<static_cast<char>(219)<<static_cast<char>(186)<<"   "<<static_cast<char>(219)<<static_cast<char>(219)<<static_cast<char>(186)<<static_cast<char>(219)<<static_cast<char>(219)<<static_cast<char>(219)<<static_cast<char>(219)<<static_cast<char>(219)<<static_cast<char>(219)<<static_cast<char>(219)<<static_cast<char>(187)<<static_cast<char>(219)<<static_cast<char>(219)<<static_cast<char>(219)<<static_cast<char>(219)<<static_cast<char>(219)<<static_cast<char>(187)<<endl;
				//cout<<"    "<<"  "<<static_cast<char>(200)<<static_cast<char>(219)<<static_cast<char>(219)<<static_cast<char>(201)<<static_cast<char>(188)<<"  "<<static_cast<char>(219)<<static_cast<char>(219)<<static_cast<char>(186)<<"   "<<static_cast<char>(219)<<static_cast<char>(219)<<static_cast<char>(186)<<static_cast<char>(219)<<static_cast<char>(219)<<static_cast<char>(186)<<"   "<<static_cast<char>(219)<<static_cast<char>(219)<<static_cast<char>(186)<<"    "<<static_cast<char>(219)<<static_cast<char>(219)<<static_cast<char>(186)<<"     "<<static_cast<char>(219)<<static_cast<char>(219)<<static_cast<char>(186)<<"   "<<static_cast<char>(219)<<static_cast<char>(219)<<static_cast<char>(186)<<static_cast<char>(200)<<static_cast<char>(205)<<static_cast<char>(205)<<static_cast<char>(205)<<static_cast<char>(205)<<static_cast<char>(219)<<static_cast<char>(219)<<static_cast<char>(186)<<static_cast<char>(219)<<static_cast<char>(219)<<static_cast<char>(201)<<static_cast<char>(205)<<static_cast<char>(205)<<static_cast<char>(188)<<endl;
				//cout<<"    "<<"   "<<static_cast<char>(219)<<static_cast<char>(219)<<static_cast<char>(186)<<"   "<<static_cast<char>(200)<<static_cast<char>(219)<<static_cast<char>(219)<<static_cast<char>(219)<<static_cast<char>(219)<<static_cast<char>(219)<<static_cast<char>(219)<<static_cast<char>(201)<<static_cast<char>(188)<<static_cast<char>(200)<<static_cast<char>(219)<<static_cast<char>(219)<<static_cast<char>(219)<<static_cast<char>(219)<<static_cast<char>(219)<<static_cast<char>(219)<<static_cast<char>(201)<<static_cast<char>(188)<<"    "<<static_cast<char>(219)<<static_cast<char>(219)<<static_cast<char>(219)<<static_cast<char>(219)<<static_cast<char>(219)<<static_cast<char>(219)<<static_cast<char>(219)<<static_cast<char>(187)<<static_cast<char>(200)<<static_cast<char>(219)<<static_cast<char>(219)<<static_cast<char>(219)<<static_cast<char>(219)<<static_cast<char>(219)<<static_cast<char>(219)<<static_cast<char>(201)<<static_cast<char>(188)<<static_cast<char>(219)<<static_cast<char>(219)<<static_cast<char>(219)<<static_cast<char>(219)<<static_cast<char>(219)<<static_cast<char>(219)<<static_cast<char>(219)<<static_cast<char>(186)<<static_cast<char>(219)<<static_cast<char>(219)<<static_cast<char>(219)<<static_cast<char>(219)<<static_cast<char>(219)<<static_cast<char>(219)<<static_cast<char>(219)<<static_cast<char>(187)<<endl;
				//cout<<"    "<<"   "<<static_cast<char>(200)<<static_cast<char>(205)<<static_cast<char>(188)<<"    "<<static_cast<char>(200)<<static_cast<char>(205)<<static_cast<char>(205)<<static_cast<char>(205)<<static_cast<char>(205)<<static_cast<char>(205)<<static_cast<char>(188)<<"  "<<static_cast<char>(200)<<static_cast<char>(205)<<static_cast<char>(205)<<static_cast<char>(205)<<static_cast<char>(205)<<static_cast<char>(205)<<static_cast<char>(188)<<"     "<<static_cast<char>(200)<<static_cast<char>(205)<<static_cast<char>(205)<<static_cast<char>(205)<<static_cast<char>(205)<<static_cast<char>(205)<<static_cast<char>(205)<<static_cast<char>(188)<<" "<<static_cast<char>(200)<<static_cast<char>(205)<<static_cast<char>(205)<<static_cast<char>(205)<<static_cast<char>(205)<<static_cast<char>(205)<<static_cast<char>(188)<<" "<<static_cast<char>(200)<<static_cast<char>(205)<<static_cast<char>(205)<<static_cast<char>(205)<<static_cast<char>(205)<<static_cast<char>(205)<<static_cast<char>(205)<<static_cast<char>(188)<<static_cast<char>(200)<<static_cast<char>(205)<<static_cast<char>(205)<<static_cast<char>(205)<<static_cast<char>(205)<<static_cast<char>(205)<<static_cast<char>(205)<<static_cast<char>(188)<<endl;
				//cout<<"    "<<"                     The level has been reset";
				/*for(int i = 0; i < 7; i++)
				{
					cout << "    ";
					for(int j = 0; j < 68; j++)
					{
						cout << static_cast<char>(nishu[i][j]);
					}
					cout << endl;
				}*/
				std ::string losing;
  std::ifstream myfile ("youlose.txt");
  if (myfile.is_open())
  {
    while ( getline (myfile,losing) )
    {
      cout << losing << '\n';
    }
    myfile.close();
  }

  else cout << "Unable to open file"; 
				_getch();
				
			}
		// render time taken to calculate this frame
		gotoXY(70, 0);
		colour(0x1A);
		std::cout << 1.0 / g_dDeltaTime << "fps" << std::endl;
  
		gotoXY(0, 0);
		colour(0x59);
		std::cout << g_dElapsedTime << "secs" << std::endl;

		// render character
		gotoXY(charLocation);
		colour(0x0C);
		std::cout << (char)1;
	}
    /*clearScreen();      // clears the current screen and draw from scratch 
    switch (g_eGameState)
    {
        case S_SPLASHSCREEN: renderSplashScreen();
            break;
        case S_GAME: renderGame();
            break;
    }
    renderFramerate();  // renders debug information, frame rate, elapsed time, etc
    renderToScreen();   // dump the contents of the buffer to the screen, one frame worth of game
	*/
}
void renderMainMenu()
{

}
void renderLevelSelect()
{

}
void renderChallenges()
{

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
	/*
    bool bSomethingHappened = false;
    if (g_dBounceTime > g_dElapsedTime)
        return;

    // Updating the location of the character based on the key press
    // providing a beep sound whenver we shift the character
    if (g_abKeyPressed[K_UP] && g_sChar.m_cLocation.Y > 0)
    {
        //Beep(1440, 30);
        g_sChar.m_cLocation.Y--;
        bSomethingHappened = true;
    }
    if (g_abKeyPressed[K_LEFT] && g_sChar.m_cLocation.X > 0)
    {
        //Beep(1440, 30);
        g_sChar.m_cLocation.X--;
        bSomethingHappened = true;
    }
    if (g_abKeyPressed[K_DOWN] && g_sChar.m_cLocation.Y < g_Console.getConsoleSize().Y - 1)
    {
        //Beep(1440, 30);
        g_sChar.m_cLocation.Y++;
        bSomethingHappened = true;
    }
    if (g_abKeyPressed[K_RIGHT] && g_sChar.m_cLocation.X < g_Console.getConsoleSize().X - 1)
    {
        //Beep(1440, 30);
        g_sChar.m_cLocation.X++;
        bSomethingHappened = true;
    }
    if (g_abKeyPressed[K_SPACE])
    {
        g_sChar.m_bActive = !g_sChar.m_bActive;
        bSomethingHappened = true;
    }

    if (bSomethingHappened)
    {
        // set the bounce time to some time in the future to prevent accidental triggers
        g_dBounceTime = g_dElapsedTime + 0.125; // 125ms should be enough
    }
	*/
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
}
void renderFramerate()
{
	/*
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
	*/
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
	while (true)
	{
		keyinputaa = true;
		colour(colors[15]);
		int x = menu();
		switch (x)
		{
		case 1:
			while (levelfix)
			{
				y = levelselect();
				if(y == 68)
				{
					levelfix = false;
				}
				else
				{
					return y;
				}
			}
			levelfix = true;
			break;
		case 2:
			challenge();
			break;
		case 3:
			achievement();
			break;
		case 69:
			return 69;
		}
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
						if(level1[i][j-2] == 5)
						{
							level1[i][j-2] = 1;
							if(level1[i][j-3] == 5)
							{
								level1[i][j-3] = 1;
							}
						}
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
						if(level1[i][j-2] == 5)
						{
							level1[i][j-2] = 1;
							if(level1[i][j-3] == 5)
							{
								level1[i][j-3] = 1;
							}
						}
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
						if(level1[i][j-2] == 5)
						{
							level1[i][j-2] = 1;
							if(level1[i][j-3] == 5)
							{
								level1[i][j-3] = 1;
							}
						}
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
						if(level1[i][j+2] == 5)
						{
							level1[i][j+2] = 1;
							if(level1[i][j+3] == 5)
							{
								level1[i][j+3] = 1;
							}
						}
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
						if(level1[i][j+2] == 5)
						{
							level1[i][j+2] = 1;
							if(level1[i][j+3] == 5)
							{
								level1[i][j+3] = 1;
							}
						}
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
						if(level1[i][j+2] == 5)
						{
							level1[i][j+2] = 1;
							if(level1[i][j+3] == 5)
							{
								level1[i][j+3] = 1;
							}
						}
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
						if(level1[i-2][j] == 5)
						{
							level1[i-2][j] = 1;
							if(level1[i-3][j] == 5)
							{
								level1[i-3][j] = 1;
							}
						}
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
						if(level1[i-2][j] == 5)
						{
							level1[i-2][j] = 1;
							if(level1[i-3][j] == 5)
							{
								level1[i-3][j] = 1;
							}
						}
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
						if(level1[i-2][j] == 5)
						{
							level1[i-2][j] = 1;
							if(level1[i-3][j] == 5)
							{
								level1[i-3][j] = 1;
							}
						}
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
						level1[i-1][j] = 1;
						if(level1[i+2][j] == 5)
						{
							level1[i+2][j] = 1;
							if(level1[i+3][j] == 5)
							{
								level1[i+3][j] = 1;
							}
						}
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
						if(level1[i+2][j] == 5)
						{
							level1[i+2][j] = 1;
							if(level1[i+3][j] == 5)
							{
								level1[i+3][j] = 1;
							}
						}
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
						if(level1[i+2][j] == 5)
						{
							level1[i+2][j] = 1;
							if(level1[i+3][j] == 5)
							{
								level1[i+3][j] = 1;
							}
						}
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
	for (int i = 0; i < 16; ++i)
	{
		for(int j = 0; j < 48; ++j)
		{
			level1[i][j] = level1reset[i][j];
		}
	}
	charLocation.X = 1;
	charLocation.Y = 2;
	g_dElapsedTime = 0.0;
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
        //cout << line << '\n';
		g_Console.writeToBuffer(c, line);
		ycoord++;
    }
    myfile.close();
  }

  else cout << "Unable to open file";

	c.X = 4;
	c.Y = 8;
    g_Console.writeToBuffer(c, "Level 1");

	c.X = 4;
	c.Y = 12;
    g_Console.writeToBuffer(c, "Level 2");

	c.X = 4;
	c.Y = 16;
    g_Console.writeToBuffer(c, "Level 3");
	
	c.X = 4;
	c.Y = 20;
    g_Console.writeToBuffer(c, "Level 4");

	
	c.X = 4;
	c.Y = 24;
    g_Console.writeToBuffer(c, "Level 5");

	c.X = 24;
	c.Y = 8;
    g_Console.writeToBuffer(c, "Level 6");

	c.X = 24;
	c.Y = 12;
    g_Console.writeToBuffer(c, "Level 7");

	c.X = 24;
	c.Y = 16;
    g_Console.writeToBuffer(c, "Level 8");

	c.X = 24;
	c.Y = 20;
    g_Console.writeToBuffer(c, "Level 9");
	

	c.X = 24;
	c.Y = 24;
    g_Console.writeToBuffer(c, "Level 10");
	

	c.X = 44;
	c.Y = 8;
    g_Console.writeToBuffer(c, "Level 11");
	

	c.X = 44;
	c.Y = 12;
    g_Console.writeToBuffer(c, "Level 12");
	

	c.X = 44;
	c.Y = 16;
    g_Console.writeToBuffer(c, "Level 13");


	c.X = 44;
	c.Y = 20;
    g_Console.writeToBuffer(c, "Level 14");

	c.X = 44;
	c.Y = 20;
    g_Console.writeToBuffer(c, "Level 14");


	c.X = 44;
	c.Y = 24;
    g_Console.writeToBuffer(c, "Level 15");


	c.X = 64;
	c.Y = 8;
    g_Console.writeToBuffer(c, "Level 16");
	

	c.X = 64;
	c.Y = 12;
    g_Console.writeToBuffer(c, "Level 17");


	c.X = 64;
	c.Y = 16;
    g_Console.writeToBuffer(c, "Level 18");

	c.X = 64;
	c.Y = 20;
    g_Console.writeToBuffer(c, "Level 19");
	

	c.X = 64;
	c.Y = 24;
    g_Console.writeToBuffer(c, "Level 20");
	
	c.X = 2;
	c.Y = 8;
    g_Console.writeToBuffer(c, ">");

	c.X = 12;
	c.Y = 8;
    g_Console.writeToBuffer(c, "<");
	 g_Console.flushBufferToConsole();

	gotoXY(2,0);
	levelnumber = 1;
	int leftarrowX = 2;
	int leftarrowY = 8;
	int rightarrowX = 12;
	int rightarrowY = 8;
	system("pause > nul");
	while(true)
	{
		getInput();
		if(g_abKeyPressed[K_DOWN] && levelnumber != 5 && levelnumber != 10 && levelnumber != 15 && levelnumber != 20 && levelnumber != 25)
		{
			levelnumber += 1;
			c.X = leftarrowX;
			c.Y = leftarrowY;
			g_Console.writeToBuffer(c, " ");
			c.X = rightarrowX;
			c.Y = rightarrowY;
			g_Console.writeToBuffer(c, " ");
			leftarrowY += 4;
			rightarrowY += 4;
			c.X = leftarrowX;
			c.Y = leftarrowY;
			g_Console.writeToBuffer(c, ">");
			c.X = rightarrowX;
			c.Y = rightarrowY;
			g_Console.writeToBuffer(c, "<");
			gotoXY(2,0);
			g_Console.flushBufferToConsole();
			system("pause > nul");
		}
		else if(g_abKeyPressed[K_UP] && levelnumber != 1 && levelnumber != 6 && levelnumber != 11 && levelnumber != 16 && levelnumber != 21)
		{
			levelnumber -= 1;
			c.X = leftarrowX;
			c.Y = leftarrowY;
			g_Console.writeToBuffer(c, " ");
			c.X = rightarrowX;
			c.Y = rightarrowY;
			g_Console.writeToBuffer(c, " ");
			leftarrowY -= 4;
			rightarrowY -= 4;
			c.X = leftarrowX;
			c.Y = leftarrowY;
			g_Console.writeToBuffer(c, ">");
			c.X = rightarrowX;
			c.Y = rightarrowY;
			g_Console.writeToBuffer(c, "<");
			gotoXY(2,0);
			g_Console.flushBufferToConsole();
			system("pause > nul");
		}
		else if(g_abKeyPressed[K_LEFT] && levelnumber > 5)
		{
			levelnumber -= 5;
			c.X = leftarrowX;
			c.Y = leftarrowY;
			g_Console.writeToBuffer(c, " ");
			c.X = rightarrowX;
			c.Y = rightarrowY;
			g_Console.writeToBuffer(c, " ");
			leftarrowX -= 20;
			rightarrowX -= 21;
			c.X = leftarrowX;
			c.Y = leftarrowY;
			g_Console.writeToBuffer(c, ">");
			c.X = rightarrowX;
			c.Y = rightarrowY;
			g_Console.writeToBuffer(c, "<");
			gotoXY(2,0);
			g_Console.flushBufferToConsole();
			system("pause > nul");
		}
		else if(g_abKeyPressed[K_RIGHT] && levelnumber < 16)
		{
			levelnumber += 5;
			c.X = leftarrowX;
			c.Y = leftarrowY;
			g_Console.writeToBuffer(c, " ");
			c.X = rightarrowX;
			c.Y = rightarrowY;
			g_Console.writeToBuffer(c, " ");
			leftarrowX += 20;
			rightarrowX += 21;
			c.X = leftarrowX;
			c.Y = leftarrowY;
			g_Console.writeToBuffer(c, ">");
			c.X = rightarrowX;
			c.Y = rightarrowY;
			g_Console.writeToBuffer(c, "<");
			gotoXY(2,0);
			g_Console.flushBufferToConsole();
			system("pause > nul");
		}
		else if(g_abKeyPressed[K_RETURN])
		{
			cout << "seriously? no";
			g_Console.clearBuffer(0x0F);
			return levelnumber;
		}
		else if(g_abKeyPressed[K_ESCAPE])
		{
			cout << "hello my friends";	
			return 68;
		}
	}
}
int menu()  
{   g_Console.clearBuffer(0x0F);
	COORD c ;
    cls();
    int count = 0 ;

          std::  string line;
  std::ifstream myfile ("TGK.txt");
  int ycoord = 0;
  if (myfile.is_open())
  {
	  
    while ( getline (myfile,line) )
    {
		c.X = 0;
		c.Y = ycoord;
//cout  << line << '\n';
		 g_Console.writeToBuffer(c, line, 0x0A);
		 ycoord++;
    }
    myfile.close();
  }

  else cout << "Unable to open file"; 
	rainbowhere += 1;
	if(rainbowhere > 14)
	{
		rainbowhere = 9;
	}
	colour(colorskappa[rainbowhere]);
	/*
    ////cout << static_cast<char>(176)<<static_cast<char>(176)<<static_cast<char>(176)<<static_cast<char>(176)<<static_cast<char>(176)<<static_cast<char>(176)<<static_cast<char>(176)<<static_cast<char>(176)<<static_cast<char>(176)<<static_cast<char>(176)<<static_cast<char>(176)<<static_cast<char>(176)<<static_cast<char>(176)<<static_cast<char>(176)<<static_cast<char>(176)<<static_cast<char>(176)<<static_cast<char>(176)<<static_cast<char>(176)<<static_cast<char>(176)<<static_cast<char>(176)<<static_cast<char>(176)<<static_cast<char>(176) << endl ;     
    cout << static_cast<char>(176)<<static_cast<char>(176)<<static_cast<char>(176)<<static_cast<char>(176)<<static_cast<char>(220)<<static_cast<char>(223)<<static_cast<char>(223)<<static_cast<char>(223)<<static_cast<char>(223)<<static_cast<char>(223)<<static_cast<char>(219)<<static_cast<char>(223)<<static_cast<char>(223)<<static_cast<char>(223)<<static_cast<char>(223)<<static_cast<char>(176)<<static_cast<char>(176)<<static_cast<char>(176)<<static_cast<char>(176)<<static_cast<char>(176)<<static_cast<char>(176)<<static_cast<char>(176) << endl;   
    cout << static_cast<char>(176)<<static_cast<char>(176)<<static_cast<char>(220)<<static_cast<char>(223)<<static_cast<char>(177)<<static_cast<char>(178)<<static_cast<char>(177)<<static_cast<char>(178)<<static_cast<char>(178)<<static_cast<char>(177)<<static_cast<char>(178)<<static_cast<char>(177)<<static_cast<char>(177)<<static_cast<char>(178)<<static_cast<char>(177)<<static_cast<char>(178)<<static_cast<char>(223)<<static_cast<char>(220)<<static_cast<char>(176)<<static_cast<char>(176)<<static_cast<char>(176)<<static_cast<char>(176) << endl ;
    cout << static_cast<char>(220)<<static_cast<char>(223)<<static_cast<char>(177)<<static_cast<char>(177)<<static_cast<char>(178)<<static_cast<char>(177)<<static_cast<char>(178)<<static_cast<char>(177)<<static_cast<char>(177)<<static_cast<char>(178)<<static_cast<char>(177)<<static_cast<char>(178)<<static_cast<char>(177)<<static_cast<char>(178)<<static_cast<char>(178)<<static_cast<char>(177)<<static_cast<char>(177)<<static_cast<char>(178)<<static_cast<char>(223)<<static_cast<char>(220)<<static_cast<char>(176)<<static_cast<char>(176) << endl;
    cout << static_cast<char>(219)<<static_cast<char>(178)<<static_cast<char>(177)<<static_cast<char>(178)<<static_cast<char>(177)<<static_cast<char>(178)<<static_cast<char>(177)<<static_cast<char>(178)<<static_cast<char>(178)<<static_cast<char>(178)<<static_cast<char>(176)<<static_cast<char>(176)<<static_cast<char>(176)<<static_cast<char>(176)<<static_cast<char>(176)<<static_cast<char>(176)<<static_cast<char>(178)<<static_cast<char>(178)<<static_cast<char>(219)<<static_cast<char>(176)<<static_cast<char>(176)<<static_cast<char>(176) << endl ;
    cout << static_cast<char>(219)<<static_cast<char>(178)<<static_cast<char>(178)<<static_cast<char>(178)<<static_cast<char>(178)<<static_cast<char>(178)<<static_cast<char>(177)<<static_cast<char>(178)<<static_cast<char>(177)<<static_cast<char>(176)<<static_cast<char>(176)<<static_cast<char>(176)<<static_cast<char>(176)<<static_cast<char>(176)<<static_cast<char>(176)<<static_cast<char>(176)<<static_cast<char>(176)<<static_cast<char>(177)<<static_cast<char>(178)<<static_cast<char>(219)<<static_cast<char>(176)<<static_cast<char>(176) << endl ;
    cout << static_cast<char>(178)<<static_cast<char>(178)<<static_cast<char>(178)<<static_cast<char>(178)<<static_cast<char>(178)<<static_cast<char>(177)<<static_cast<char>(176)<<static_cast<char>(176)<<static_cast<char>(176)<<static_cast<char>(176)<<static_cast<char>(176)<<static_cast<char>(176)<<static_cast<char>(176)<<static_cast<char>(176)<<static_cast<char>(176)<<static_cast<char>(176)<<static_cast<char>(176)<<static_cast<char>(176)<<static_cast<char>(219)<<static_cast<char>(176)<<static_cast<char>(176)<<static_cast<char>(176) << endl ;
    cout << static_cast<char>(178)<<static_cast<char>(178)<<static_cast<char>(178)<<static_cast<char>(178)<<static_cast<char>(176)<<static_cast<char>(176)<<static_cast<char>(176)<<static_cast<char>(176)<<static_cast<char>(220)<<static_cast<char>(220)<<static_cast<char>(220)<<static_cast<char>(220)<<static_cast<char>(176)<<static_cast<char>(176)<<static_cast<char>(176)<<static_cast<char>(220)<<static_cast<char>(219)<<static_cast<char>(220)<<static_cast<char>(223)<<static_cast<char>(176)<<static_cast<char>(176)<<static_cast<char>(176) << endl ;
    cout << static_cast<char>(176)<<static_cast<char>(223)<<static_cast<char>(220)<<static_cast<char>(178)<<static_cast<char>(176)<<static_cast<char>(176)<<static_cast<char>(177)<<static_cast<char>(223)<<static_cast<char>(178)<<static_cast<char>(178)<<static_cast<char>(177)<<static_cast<char>(177)<<static_cast<char>(176)<<static_cast<char>(176)<<static_cast<char>(219)<<static_cast<char>(178)<<static_cast<char>(177)<<static_cast<char>(177)<<static_cast<char>(176)<<static_cast<char>(176)<<static_cast<char>(176)<<static_cast<char>(176) << endl ;
    cout << static_cast<char>(223)<<static_cast<char>(220)<<static_cast<char>(176)<<static_cast<char>(176)<<static_cast<char>(176)<<static_cast<char>(176)<<static_cast<char>(176)<<static_cast<char>(176)<<static_cast<char>(176)<<static_cast<char>(176)<<static_cast<char>(176)<<static_cast<char>(176)<<static_cast<char>(176)<<static_cast<char>(176)<<static_cast<char>(223)<<static_cast<char>(220)<<static_cast<char>(177)<<static_cast<char>(177)<<static_cast<char>(219)<<static_cast<char>(176)<<static_cast<char>(176)<<static_cast<char>(176) << endl ;   
    cout << static_cast<char>(176)<<static_cast<char>(223)<<static_cast<char>(176)<<static_cast<char>(223)<<static_cast<char>(176)<<static_cast<char>(176)<<static_cast<char>(176)<<static_cast<char>(176)<<static_cast<char>(176)<<static_cast<char>(177)<<static_cast<char>(177)<<static_cast<char>(223)<<static_cast<char>(220)<<static_cast<char>(220)<<static_cast<char>(177)<<static_cast<char>(223)<<static_cast<char>(177)<<static_cast<char>(177)<<static_cast<char>(219)<<static_cast<char>(176)<<static_cast<char>(176)<<static_cast<char>(176) << endl ;
    cout << static_cast<char>(176)<<static_cast<char>(176)<<static_cast<char>(223)<<static_cast<char>(176)<<static_cast<char>(176)<<static_cast<char>(176)<<static_cast<char>(176)<<static_cast<char>(176)<<static_cast<char>(176)<<static_cast<char>(177)<<static_cast<char>(220)<<static_cast<char>(220)<<static_cast<char>(177)<<static_cast<char>(220)<<static_cast<char>(220)<<static_cast<char>(220)<<static_cast<char>(177)<<static_cast<char>(177)<<static_cast<char>(219)<<static_cast<char>(176)<<static_cast<char>(176)<<static_cast<char>(176) << endl ; 
    cout << static_cast<char>(176)<<static_cast<char>(176)<<static_cast<char>(176)<<static_cast<char>(223)<<static_cast<char>(220)<<static_cast<char>(220)<<static_cast<char>(177)<<static_cast<char>(177)<<static_cast<char>(176)<<static_cast<char>(176)<<static_cast<char>(176)<<static_cast<char>(176)<<static_cast<char>(223)<<static_cast<char>(223)<<static_cast<char>(177)<<static_cast<char>(177)<<static_cast<char>(220)<<static_cast<char>(223)<<static_cast<char>(176)<<static_cast<char>(176)<<static_cast<char>(176)<<static_cast<char>(176) << endl ;
    cout << static_cast<char>(176)<<static_cast<char>(176)<<static_cast<char>(176)<<static_cast<char>(176)<<static_cast<char>(176)<<static_cast<char>(223)<<static_cast<char>(219)<<static_cast<char>(220)<<static_cast<char>(177)<<static_cast<char>(177)<<static_cast<char>(176)<<static_cast<char>(176)<<static_cast<char>(176)<<static_cast<char>(176)<<static_cast<char>(177)<<static_cast<char>(220)<<static_cast<char>(223)<<static_cast<char>(176)<<static_cast<char>(176)<<static_cast<char>(176)<<static_cast<char>(176)<<static_cast<char>(176) << endl ;  
    cout << static_cast<char>(176)<<static_cast<char>(176)<<static_cast<char>(176)<<static_cast<char>(176)<<static_cast<char>(176)<<static_cast<char>(176)<<static_cast<char>(176)<<static_cast<char>(176)<<static_cast<char>(223)<<static_cast<char>(223)<<static_cast<char>(219)<<static_cast<char>(220)<<static_cast<char>(220)<<static_cast<char>(220)<<static_cast<char>(220)<<static_cast<char>(223)<<static_cast<char>(176)<<static_cast<char>(176)<<static_cast<char>(176)<<static_cast<char>(176)<<static_cast<char>(176)<<static_cast<char>(176);
	*/
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
      //cout << keepo << '\n';
    }
    anotherfile.close();
  }

  else cout << "Unable to open file"; 


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
    g_Console.writeToBuffer(c, "ACHIEVEMENTS & OPTIONS"); 

	c.X = 48;
    c.Y = 23; 
	g_Console.writeToBuffer(c, "EXITERINO"); 
   
	c.X = 45;
    c.Y = 17;
    g_Console.writeToBuffer(c, ">"); 
    g_Console.flushBufferToConsole();/////
	int frequency = 2640;
    while (true)  
    {
        getInput();     
        if ( g_abKeyPressed[K_DOWN] == 1 )    
        {
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
                system("pause > nul");
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
                system("pause > nul");
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
                system("pause > nul");
            }
			
        }   
        else if ( g_abKeyPressed[K_UP] == 1 )     
        {
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
                system("pause > nul");
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
                system("pause > nul");
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
                system("pause > nul");
            }
        }     
        else if ( g_abKeyPressed[K_RETURN] == 1 )        
        {
            if ( count == 0 )  
            {
                return 1;  
                break; 
            }
            if ( count == 1 )   
            {
                return 2;    
                break;
            }  
            if ( count == 2 )  
            {
                return 3;   
                break;
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
    }   
}
int challenge() 
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
      //cout << line << '\n';
		g_Console.writeToBuffer(c, line);
		ycoord++;
    }
    myfile.close();
  }

  else cout << "Unable to open file"; 

    c.X = 4;
	c.Y = 10;
	g_Console.writeToBuffer(c, "Level 1");
	c.X = 4;
	c.Y = 14;
	g_Console.writeToBuffer(c, "Level 2");
	c.X = 4;
	c.Y = 18;
	g_Console.writeToBuffer(c, "Level 3");
	c.X = 4;
	c.Y = 22;
	g_Console.writeToBuffer(c, "Level 4");
	c.X = 4;
	c.Y = 26;
	g_Console.writeToBuffer(c, "Level 5");
	c.X = 24;
	c.Y = 10;
	g_Console.writeToBuffer(c, "Level 6");
	c.X = 24;
	c.Y = 14;
	g_Console.writeToBuffer(c, "Level 7");
	c.X = 24;
	c.Y = 18;
	g_Console.writeToBuffer(c, "Level 8");
	c.X = 24;
	c.Y = 22;
	g_Console.writeToBuffer(c, "Level 9");
	c.X = 24;
	c.Y = 26;
	g_Console.writeToBuffer(c, "Level 10");
	c.X = 44;
	c.Y = 10;
	g_Console.writeToBuffer(c, "Level 11");
	c.X = 44;
	c.Y = 14;
	g_Console.writeToBuffer(c, "Level 12");
	c.X = 44;
	c.Y = 18;
	g_Console.writeToBuffer(c, "Level 13");
	c.X = 44;
	c.Y = 22;
	g_Console.writeToBuffer(c, "Level 14");
	c.X = 44;
	c.Y = 26;
	g_Console.writeToBuffer(c, "Level 15");
	c.X = 64;
	c.Y = 10;
	g_Console.writeToBuffer(c, "Level 16");
	c.X = 64;
	c.Y = 14;
	g_Console.writeToBuffer(c, "Level 17");
	c.X = 64;
	c.Y = 18;
	g_Console.writeToBuffer(c, "Level 18");
	c.X = 64;
	c.Y = 22;
	g_Console.writeToBuffer(c, "Level 19");
	c.X = 64;
	c.Y = 26;
	g_Console.writeToBuffer(c, "Level 20");

	c.X = 2;
	c.Y = 10;
	g_Console.writeToBuffer(c, ">"); 
	g_Console.flushBufferToConsole();
    int xcoord = 2 ;   
    ycoord = 10 ;  
    while ( true )  
    {
        getInput();  
        if ( g_abKeyPressed[K_ESCAPE] == 1 )   
        {
            return 4;  
            break;
        }
        if ( ( g_abKeyPressed[K_RIGHT] == 1 ) && ( xcoord < 65 ) )    
        {
            gotoXY(xcoord,ycoord);    
            cout << " " ;    
            xcoord += 20 ;
            gotoXY(xcoord ,ycoord);   
            cout << ">" ;    
            system("pause > nul");
        }    
        if ( ( g_abKeyPressed[K_LEFT] == 1) && ( xcoord>5 ) )    
        {
            gotoXY(xcoord,ycoord); 
            cout << " " ; 
            xcoord -= 20 ;  
            gotoXY(xcoord,ycoord) ;   
            cout << ">" ;  
            system("pause > nul"); 
        }    
        if ( ( g_abKeyPressed[K_DOWN] == 1 ) && ( ycoord < 26 ) )  
        {
            gotoXY(xcoord,ycoord); 
            cout << " " ; 
            ycoord += 4;  
            gotoXY(xcoord,ycoord) ;   
            cout << ">" ;  
            system("pause > nul");   
        } 
        if ( ( g_abKeyPressed[K_UP] == 1 ) && ( ycoord > 10 ) )  
        {
            gotoXY(xcoord,ycoord); 
            cout << " " ; 
            ycoord -= 4;  
            gotoXY(xcoord,ycoord) ;   
            cout << ">" ;  
            system("pause > nul");   
        }
    }
}   
int achievement()  
{     
    cls();
     std:: string line;
  std::ifstream myfile ("achi.txt");
  if (myfile.is_open())
  {
    while ( getline (myfile,line) )
    {
      cout << line << '\n';
    }
    myfile.close();
  }

  else cout << "Unable to open file"; 
    while (true)   
    {
        getInput();
        if ( g_abKeyPressed[K_ESCAPE] == 1 )    
        {
            return 4;  
            break;
        } 
    }
}