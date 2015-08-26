// This is the main file for the game logic and function
//
//
#include "game.h"
#include "Framework\console.h"
#include "levelmap.txt"
#include <iostream>
#include <iomanip>
#include <conio.h>
#include <string>
#include <fstream>
#include <ctime>
using std::cin;
using std::cout;
using std::endl;

double elapsedTime;
double deltaTime;
bool keyPressed[K_COUNT];
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
COORD charLocation;
COORD consoleSize;

const WORD colors[] =   {
	                        0x1A, 0x2B, 0x3C, 0x4D, 0x5E, 0x6F,
	                        0xA1, 0xB2, 0xC3, 0xD4, 0xE5, 0xF6,
							0x0F, 0x0E, 0x09, 0x0A, 0x0C
	                        };

const WORD colorskappa[] =  {
	                        0x01, 0x02, 0x03, 0x04, 0x05, 0x06,
							0x07, 0x08, 0x09, 0x0A, 0x0B, 0x0C,
							0x0D, 0x0E, 0x0F
	                        };

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

void init()
{
    // Set precision for floating point output
    std::cout << std::fixed << std::setprecision(3);

    SetConsoleTitle(L"The Great Kappa");

    // Sets the console size, this is the biggest so far.
    setConsoleSize(79, 28);

    // Get console width and height
    CONSOLE_SCREEN_BUFFER_INFO csbi; /* to get buffer info */     

    /* get the number of character cells in the current buffer */ 
    GetConsoleScreenBufferInfo( GetStdHandle( STD_OUTPUT_HANDLE ), &csbi );
    consoleSize.X = csbi.srWindow.Right + 1;
    consoleSize.Y = csbi.srWindow.Bottom + 1;

    // set the character to be in the center of the screen.
    charLocation.X = 1;
    charLocation.Y = 2;

    elapsedTime = 0.0;

	colour(colors[15]);
}

void shutdown()
{
    // Reset to white text on black background
	colour(FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED);
}

void getInput()
{    
    keyPressed[K_UP] = isKeyPressed(VK_UP);
    keyPressed[K_DOWN] = isKeyPressed(VK_DOWN);
    keyPressed[K_LEFT] = isKeyPressed(VK_LEFT);
    keyPressed[K_RIGHT] = isKeyPressed(VK_RIGHT);
    keyPressed[K_ESCAPE] = isKeyPressed(VK_ESCAPE);
	keyPressed[K_RETURN] = isKeyPressed(VK_RETURN);
}

void loadlevel(){
	//laser up
	if(level1[charLocation.Y-2][charLocation.X] == 15) //up
	{
		level1[charLocation.Y-2][charLocation.X] = 19;
		for(int k = 1; charLocation.Y-2-k >= 0; k++)
		{
			if((level1[charLocation.Y-2-k][charLocation.X] == 21))
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
			if((level1[charLocation.Y-1-k][charLocation.X-1] == 21))
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
			if(level1[(charLocation.Y-1)-k][charLocation.X+1] == 21)
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
			if((level1[charLocation.Y+k][charLocation.X] == 21))
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
			if((level1[charLocation.Y-1+k][charLocation.X-1] == 21))
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
			if(level1[(charLocation.Y-1)+k][charLocation.X+1] == 21)
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
			if((level1[charLocation.Y-2][charLocation.X-k] == 25))
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
			if((level1[charLocation.Y][charLocation.X-k] == 25))
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
			if(level1[(charLocation.Y-1)][charLocation.X-1-k] == 25)
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
			if((level1[(charLocation.Y-2)][charLocation.X+k] == 25))
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
			if((level1[charLocation.Y][charLocation.X+k] == 25))
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
			if((level1[(charLocation.Y-1)][charLocation.X+1+k] == 25))
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
					if((level1[k][j] == 1)||(level1[k][j] == 5))
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
					if((level1[k][j] == 1)||(level1[k][j] == 5))
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
					if((level1[i][k] == 1)||(level1[i][k] == 5))
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
					if((level1[i][k] == 1)||(level1[i][k] == 5))
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
	elapsedTime = 0.0;
}

void render()
{
	if(gamestate == 1)
	{
		int x = newmainmenu();
		if(x == 69)
		{
			g_quitGame = true;
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
			render();
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
			render();
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
		cls();

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
		for (int i = 0; i < 16; ++i)
		{
			for(int j = 0; j < 48; ++j)
			{
				//colour(colors[12]);
				//gotoXY(j,i+1);
				if(level1[i][j] == 0)
				{
					cout << static_cast<char>(219);
					continue;
				}
				else if(level1[i][j] == 1)
				{
					cout << ' ';
					continue;
				}
				else if(level1[i][j] == 2)
				{
					cout << static_cast<char>(1);
					continue;
				}
				else if((level1[i][j] == 3)||(level1[i][j] == 4)||(level1[i][j] == 6)||(level1[i][j] == 7))
				{
					cout << static_cast<char>(2);
					continue;
				}
				else if(level1[i][j] == 5)
				{
					colour(colors[13]);
					cout << static_cast<char>(15);
					colour(colors[12]);
					continue;
				}
				else if((level1[i][j] == 15)||(level1[i][j] == 16)||(level1[i][j] == 17)||(level1[i][j] == 18))
				{
					colour(colors[16]);
					if(level1[i][j] == 15)
					{
						cout << '^';
					}
					else if(level1[i][j] == 16)
					{
						cout << 'V';
					}
					else if(level1[i][j] == 17)
					{
						cout << '>';
					}
					else if(level1[i][j] == 18)
					{
						cout << '<';
					}
					colour(colors[12]);
					continue;
				}
				else if(level1[i][j] == 19)
				{
					cout << '^';
					continue;
				}
				else if(level1[i][j] == 20)
				{
					cout << 'V';
					continue;
				}
				else if(level1[i][j] == 23)
				{
					cout << '>';
					continue;
				}
				else if(level1[i][j] == 22)
				{
					cout << '<';
					continue;
				}
				else if(level1[i][j] == 21)
				{
					colour(colors[16]);
					cout << '|';
					colour(colors[12]);
					continue;
				}
				else if(level1[i][j] == 25)
				{
					colour(colors[16]);
					cout << '-';
					colour(colors[12]);
					continue;
				}
				else if(level1[i][j] == 69)
				{
					cout << 'x';
					continue;
				}
			}
			cout << '\n';
		}
		if(level1[charLocation.Y-1][charLocation.X] == 69)
			{
				resetlevel();
				//loadlevel();
				keyinputaa = true;
				render();
				gotoXY (0, 19);
				colour(colorskappa[14]);
				cout<<"    "<<static_cast<char>(219)<<static_cast<char>(219)<<static_cast<char>(187)<<"   "<<static_cast<char>(219)<<static_cast<char>(219)<<static_cast<char>(187)<<" "<<static_cast<char>(219)<<static_cast<char>(219)<<static_cast<char>(219)<<static_cast<char>(219)<<static_cast<char>(219)<<static_cast<char>(219)<<static_cast<char>(187)<<" "<<static_cast<char>(219)<<static_cast<char>(219)<<static_cast<char>(187)<<"   "<<static_cast<char>(219)<<static_cast<char>(219)<<static_cast<char>(187)<<"    "<<static_cast<char>(219)<<static_cast<char>(219)<<static_cast<char>(187)<<"    "<<static_cast<char>(219)<<static_cast<char>(219)<<static_cast<char>(187)<<static_cast<char>(219)<<static_cast<char>(219)<<static_cast<char>(187)<<static_cast<char>(219)<<static_cast<char>(219)<<static_cast<char>(219)<<static_cast<char>(187)<<"   "<<static_cast<char>(219)<<static_cast<char>(219)<<static_cast<char>(187)<<endl;
				cout<<"    "<<static_cast<char>(200)<<static_cast<char>(219)<<static_cast<char>(219)<<static_cast<char>(187)<<" "<<static_cast<char>(219)<<static_cast<char>(219)<<static_cast<char>(201)<<static_cast<char>(188)<<static_cast<char>(219)<<static_cast<char>(219)<<static_cast<char>(201)<<static_cast<char>(205)<<static_cast<char>(205)<<static_cast<char>(205)<<static_cast<char>(219)<<static_cast<char>(219)<<static_cast<char>(187)<<static_cast<char>(219)<<static_cast<char>(219)<<static_cast<char>(186)<<"   "<<static_cast<char>(219)<<static_cast<char>(219)<<static_cast<char>(186)<<"    "<<static_cast<char>(219)<<static_cast<char>(219)<<static_cast<char>(186)<<"    "<<static_cast<char>(219)<<static_cast<char>(219)<<static_cast<char>(186)<<static_cast<char>(219)<<static_cast<char>(219)<<static_cast<char>(186)<<static_cast<char>(219)<<static_cast<char>(219)<<static_cast<char>(219)<<static_cast<char>(219)<<static_cast<char>(187)<<"  "<<static_cast<char>(219)<<static_cast<char>(219)<<static_cast<char>(186)<<endl;
				cout<<"    "<<" "<<static_cast<char>(200)<<static_cast<char>(219)<<static_cast<char>(219)<<static_cast<char>(219)<<static_cast<char>(219)<<static_cast<char>(201)<<static_cast<char>(188)<<" "<<static_cast<char>(219)<<static_cast<char>(219)<<static_cast<char>(186)<<"   "<<static_cast<char>(219)<<static_cast<char>(219)<<static_cast<char>(186)<<static_cast<char>(219)<<static_cast<char>(219)<<static_cast<char>(186)<<"   "<<static_cast<char>(219)<<static_cast<char>(219)<<static_cast<char>(186)<<"    "<<static_cast<char>(219)<<static_cast<char>(219)<<static_cast<char>(186)<<" "<<static_cast<char>(219)<<static_cast<char>(187)<<" "<<static_cast<char>(219)<<static_cast<char>(219)<<static_cast<char>(186)<<static_cast<char>(219)<<static_cast<char>(219)<<static_cast<char>(186)<<static_cast<char>(219)<<static_cast<char>(219)<<static_cast<char>(201)<<static_cast<char>(219)<<static_cast<char>(219)<<static_cast<char>(187)<<" "<<static_cast<char>(219)<<static_cast<char>(219)<<static_cast<char>(186)<<endl;
				cout<<"    "<<"  "<<static_cast<char>(200)<<static_cast<char>(219)<<static_cast<char>(219)<<static_cast<char>(201)<<static_cast<char>(188)<<"  "<<static_cast<char>(219)<<static_cast<char>(219)<<static_cast<char>(186)<<"   "<<static_cast<char>(219)<<static_cast<char>(219)<<static_cast<char>(186)<<static_cast<char>(219)<<static_cast<char>(219)<<static_cast<char>(186)<<"   "<<static_cast<char>(219)<<static_cast<char>(219)<<static_cast<char>(186)<<"    "<<static_cast<char>(219)<<static_cast<char>(219)<<static_cast<char>(186)<<static_cast<char>(219)<<static_cast<char>(219)<<static_cast<char>(219)<<static_cast<char>(187)<<static_cast<char>(219)<<static_cast<char>(219)<<static_cast<char>(186)<<static_cast<char>(219)<<static_cast<char>(219)<<static_cast<char>(186)<<static_cast<char>(219)<<static_cast<char>(219)<<static_cast<char>(186)<<static_cast<char>(200)<<static_cast<char>(219)<<static_cast<char>(219)<<static_cast<char>(187)<<static_cast<char>(219)<<static_cast<char>(219)<<static_cast<char>(186)<<endl;
				cout<<"    "<<"   "<<static_cast<char>(219)<<static_cast<char>(219)<<static_cast<char>(186)<<"   "<<static_cast<char>(200)<<static_cast<char>(219)<<static_cast<char>(219)<<static_cast<char>(219)<<static_cast<char>(219)<<static_cast<char>(219)<<static_cast<char>(219)<<static_cast<char>(201)<<static_cast<char>(188)<<static_cast<char>(200)<<static_cast<char>(219)<<static_cast<char>(219)<<static_cast<char>(219)<<static_cast<char>(219)<<static_cast<char>(219)<<static_cast<char>(219)<<static_cast<char>(201)<<static_cast<char>(188)<<"    "<<static_cast<char>(200)<<static_cast<char>(219)<<static_cast<char>(219)<<static_cast<char>(219)<<static_cast<char>(201)<<static_cast<char>(219)<<static_cast<char>(219)<<static_cast<char>(219)<<static_cast<char>(201)<<static_cast<char>(188)<<static_cast<char>(219)<<static_cast<char>(219)<<static_cast<char>(186)<<static_cast<char>(219)<<static_cast<char>(219)<<static_cast<char>(186)<<" "<<static_cast<char>(200)<<static_cast<char>(219)<<static_cast<char>(219)<<static_cast<char>(219)<<static_cast<char>(219)<<static_cast<char>(186)<<endl;
				cout<<"    "<<"   "<<static_cast<char>(200)<<static_cast<char>(205)<<static_cast<char>(188)<<"    "<<static_cast<char>(200)<<static_cast<char>(205)<<static_cast<char>(205)<<static_cast<char>(205)<<static_cast<char>(205)<<static_cast<char>(205)<<static_cast<char>(188)<<"  "<<static_cast<char>(200)<<static_cast<char>(205)<<static_cast<char>(205)<<static_cast<char>(205)<<static_cast<char>(205)<<static_cast<char>(205)<<static_cast<char>(188)<<"      "<<static_cast<char>(200)<<static_cast<char>(205)<<static_cast<char>(205)<<static_cast<char>(188)<<static_cast<char>(200)<<static_cast<char>(205)<<static_cast<char>(205)<<static_cast<char>(188)<<" "<<static_cast<char>(200)<<static_cast<char>(205)<<static_cast<char>(188)<<static_cast<char>(200)<<static_cast<char>(205)<<static_cast<char>(188)<<"  "<<static_cast<char>(200)<<static_cast<char>(205)<<static_cast<char>(205)<<static_cast<char>(205)<<static_cast<char>(188)<<endl;
				cout<<"    "<<"        Press ESC to exit to Level Select screen";
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
				cout<<"    "<<static_cast<char>(219)<<static_cast<char>(219)<<static_cast<char>(187)<<"   "<<static_cast<char>(219)<<static_cast<char>(219)<<static_cast<char>(187)<<" "<<static_cast<char>(219)<<static_cast<char>(219)<<static_cast<char>(219)<<static_cast<char>(219)<<static_cast<char>(219)<<static_cast<char>(219)<<static_cast<char>(187)<<" "<<static_cast<char>(219)<<static_cast<char>(219)<<static_cast<char>(187)<<"   "<<static_cast<char>(219)<<static_cast<char>(219)<<static_cast<char>(187)<<"    "<<static_cast<char>(219)<<static_cast<char>(219)<<static_cast<char>(187)<<"      "<<static_cast<char>(219)<<static_cast<char>(219)<<static_cast<char>(219)<<static_cast<char>(219)<<static_cast<char>(219)<<static_cast<char>(219)<<static_cast<char>(187)<<" "<<static_cast<char>(219)<<static_cast<char>(219)<<static_cast<char>(219)<<static_cast<char>(219)<<static_cast<char>(219)<<static_cast<char>(219)<<static_cast<char>(219)<<static_cast<char>(187)<<static_cast<char>(219)<<static_cast<char>(219)<<static_cast<char>(219)<<static_cast<char>(219)<<static_cast<char>(219)<<static_cast<char>(219)<<static_cast<char>(219)<<static_cast<char>(187)<<endl;
				cout<<"    "<<static_cast<char>(200)<<static_cast<char>(219)<<static_cast<char>(219)<<static_cast<char>(187)<<" "<<static_cast<char>(219)<<static_cast<char>(219)<<static_cast<char>(201)<<static_cast<char>(188)<<static_cast<char>(219)<<static_cast<char>(219)<<static_cast<char>(201)<<static_cast<char>(205)<<static_cast<char>(205)<<static_cast<char>(205)<<static_cast<char>(219)<<static_cast<char>(219)<<static_cast<char>(187)<<static_cast<char>(219)<<static_cast<char>(219)<<static_cast<char>(186)<<"   "<<static_cast<char>(219)<<static_cast<char>(219)<<static_cast<char>(186)<<"    "<<static_cast<char>(219)<<static_cast<char>(219)<<static_cast<char>(186)<<"     "<<static_cast<char>(219)<<static_cast<char>(219)<<static_cast<char>(201)<<static_cast<char>(205)<<static_cast<char>(205)<<static_cast<char>(205)<<static_cast<char>(219)<<static_cast<char>(219)<<static_cast<char>(187)<<static_cast<char>(219)<<static_cast<char>(219)<<static_cast<char>(201)<<static_cast<char>(205)<<static_cast<char>(205)<<static_cast<char>(205)<<static_cast<char>(205)<<static_cast<char>(188)<<static_cast<char>(219)<<static_cast<char>(219)<<static_cast<char>(201)<<static_cast<char>(205)<<static_cast<char>(205)<<static_cast<char>(205)<<static_cast<char>(205)<<static_cast<char>(188)<<endl;
				cout<<"    "<<" "<<static_cast<char>(200)<<static_cast<char>(219)<<static_cast<char>(219)<<static_cast<char>(219)<<static_cast<char>(219)<<static_cast<char>(201)<<static_cast<char>(188)<<" "<<static_cast<char>(219)<<static_cast<char>(219)<<static_cast<char>(186)<<"   "<<static_cast<char>(219)<<static_cast<char>(219)<<static_cast<char>(186)<<static_cast<char>(219)<<static_cast<char>(219)<<static_cast<char>(186)<<"   "<<static_cast<char>(219)<<static_cast<char>(219)<<static_cast<char>(186)<<"    "<<static_cast<char>(219)<<static_cast<char>(219)<<static_cast<char>(186)<<"     "<<static_cast<char>(219)<<static_cast<char>(219)<<static_cast<char>(186)<<"   "<<static_cast<char>(219)<<static_cast<char>(219)<<static_cast<char>(186)<<static_cast<char>(219)<<static_cast<char>(219)<<static_cast<char>(219)<<static_cast<char>(219)<<static_cast<char>(219)<<static_cast<char>(219)<<static_cast<char>(219)<<static_cast<char>(187)<<static_cast<char>(219)<<static_cast<char>(219)<<static_cast<char>(219)<<static_cast<char>(219)<<static_cast<char>(219)<<static_cast<char>(187)<<endl;
				cout<<"    "<<"  "<<static_cast<char>(200)<<static_cast<char>(219)<<static_cast<char>(219)<<static_cast<char>(201)<<static_cast<char>(188)<<"  "<<static_cast<char>(219)<<static_cast<char>(219)<<static_cast<char>(186)<<"   "<<static_cast<char>(219)<<static_cast<char>(219)<<static_cast<char>(186)<<static_cast<char>(219)<<static_cast<char>(219)<<static_cast<char>(186)<<"   "<<static_cast<char>(219)<<static_cast<char>(219)<<static_cast<char>(186)<<"    "<<static_cast<char>(219)<<static_cast<char>(219)<<static_cast<char>(186)<<"     "<<static_cast<char>(219)<<static_cast<char>(219)<<static_cast<char>(186)<<"   "<<static_cast<char>(219)<<static_cast<char>(219)<<static_cast<char>(186)<<static_cast<char>(200)<<static_cast<char>(205)<<static_cast<char>(205)<<static_cast<char>(205)<<static_cast<char>(205)<<static_cast<char>(219)<<static_cast<char>(219)<<static_cast<char>(186)<<static_cast<char>(219)<<static_cast<char>(219)<<static_cast<char>(201)<<static_cast<char>(205)<<static_cast<char>(205)<<static_cast<char>(188)<<endl;
				cout<<"    "<<"   "<<static_cast<char>(219)<<static_cast<char>(219)<<static_cast<char>(186)<<"   "<<static_cast<char>(200)<<static_cast<char>(219)<<static_cast<char>(219)<<static_cast<char>(219)<<static_cast<char>(219)<<static_cast<char>(219)<<static_cast<char>(219)<<static_cast<char>(201)<<static_cast<char>(188)<<static_cast<char>(200)<<static_cast<char>(219)<<static_cast<char>(219)<<static_cast<char>(219)<<static_cast<char>(219)<<static_cast<char>(219)<<static_cast<char>(219)<<static_cast<char>(201)<<static_cast<char>(188)<<"    "<<static_cast<char>(219)<<static_cast<char>(219)<<static_cast<char>(219)<<static_cast<char>(219)<<static_cast<char>(219)<<static_cast<char>(219)<<static_cast<char>(219)<<static_cast<char>(187)<<static_cast<char>(200)<<static_cast<char>(219)<<static_cast<char>(219)<<static_cast<char>(219)<<static_cast<char>(219)<<static_cast<char>(219)<<static_cast<char>(219)<<static_cast<char>(201)<<static_cast<char>(188)<<static_cast<char>(219)<<static_cast<char>(219)<<static_cast<char>(219)<<static_cast<char>(219)<<static_cast<char>(219)<<static_cast<char>(219)<<static_cast<char>(219)<<static_cast<char>(186)<<static_cast<char>(219)<<static_cast<char>(219)<<static_cast<char>(219)<<static_cast<char>(219)<<static_cast<char>(219)<<static_cast<char>(219)<<static_cast<char>(219)<<static_cast<char>(187)<<endl;
				cout<<"    "<<"   "<<static_cast<char>(200)<<static_cast<char>(205)<<static_cast<char>(188)<<"    "<<static_cast<char>(200)<<static_cast<char>(205)<<static_cast<char>(205)<<static_cast<char>(205)<<static_cast<char>(205)<<static_cast<char>(205)<<static_cast<char>(188)<<"  "<<static_cast<char>(200)<<static_cast<char>(205)<<static_cast<char>(205)<<static_cast<char>(205)<<static_cast<char>(205)<<static_cast<char>(205)<<static_cast<char>(188)<<"     "<<static_cast<char>(200)<<static_cast<char>(205)<<static_cast<char>(205)<<static_cast<char>(205)<<static_cast<char>(205)<<static_cast<char>(205)<<static_cast<char>(205)<<static_cast<char>(188)<<" "<<static_cast<char>(200)<<static_cast<char>(205)<<static_cast<char>(205)<<static_cast<char>(205)<<static_cast<char>(205)<<static_cast<char>(205)<<static_cast<char>(188)<<" "<<static_cast<char>(200)<<static_cast<char>(205)<<static_cast<char>(205)<<static_cast<char>(205)<<static_cast<char>(205)<<static_cast<char>(205)<<static_cast<char>(205)<<static_cast<char>(188)<<static_cast<char>(200)<<static_cast<char>(205)<<static_cast<char>(205)<<static_cast<char>(205)<<static_cast<char>(205)<<static_cast<char>(205)<<static_cast<char>(205)<<static_cast<char>(188)<<endl;
				cout<<"    "<<"                     The level has been reset";
				/*for(int i = 0; i < 7; i++)
				{
					cout << "    ";
					for(int j = 0; j < 54; j++)
					{
						cout << static_cast<char>(nishu[i][j]);
					}
					cout << endl;
				}*/
				_getch();
				
			}
		// render time taken to calculate this frame
		gotoXY(70, 0);
		colour(0x1A);
		std::cout << 1.0 / deltaTime << "fps" << std::endl;
  
		gotoXY(0, 0);
		colour(0x59);
		std::cout << elapsedTime << "secs" << std::endl;

		// render character
		gotoXY(charLocation);
		colour(0x0C);
		std::cout << (char)1;
	}
}

void update(double dt)
{
    // get the delta time
    elapsedTime += dt;
    deltaTime = dt;

    // Updating the location of the character based on the key press
    if (keyPressed[K_UP])
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
    else if (keyPressed[K_LEFT])
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
    else if (keyPressed[K_DOWN])
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
    else if (keyPressed[K_RIGHT])
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
    if (keyPressed[K_ESCAPE])
		gamestate = 1;
        //g_quitGame = true;
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
}

int levelselect()
{
	colour(0x0F);
    cls();
	gotoXY(0,0);
	colour(colors[15]);
	cout<<"  _     _______      _______ _         _____ _____ _     _____ _____ _______ "<<endl;
	cout<<" | |   |  ___\\ \\    / /  ___| |       / ____|  ___| |   |  ___/ ____|__   __|"<<endl;
	cout<<" | |   | |_   \\ \\  / /| |_  | |      | (___ | |_  | |   | |_ | |       | |   "<<endl;
	cout<<" | |   |  _|   \\ \\/ / |  _| | |       \\___ \\|  _| | |   |  _|| |       | |   "<<endl;
	cout<<" | |___| |___   \\  /  | |___| |___    ____) | |___| |___| |__| |____   | |   "<<endl;
	cout<<" |_____|_____|   \\/   |_____|_____|  |_____/|_____|_____|_____\\_____|  |_|   "<<endl;
	gotoXY(4, 8);
	cout << "Level 1";
	gotoXY(4, 12);
	cout << "Level 2";
	gotoXY(4, 16);
	cout << "Level 3";
	gotoXY(4, 20);
	cout << "Level 4";
	gotoXY(4, 24);
	cout << "Level 5";
	gotoXY(24, 8);
	cout << "Level 6";
	gotoXY(24, 12);
	cout << "Level 7";
	gotoXY(24, 16);
	cout << "Level 8";
	gotoXY(24, 20);
	cout << "Level 9";
	gotoXY(24, 24);
	cout << "Level 10";
	gotoXY(44, 8);
	cout << "Level 11";
	gotoXY(44, 12);
	cout << "Level 12";
	gotoXY(44, 16);
	cout << "Level 13";
	gotoXY(44, 20);
	cout << "Level 14";
	gotoXY(44, 24);
	cout << "Level 15";
	gotoXY(64, 8);
	cout << "Level 16";
	gotoXY(64, 12);
	cout << "Level 17";
	gotoXY(64, 16);
	cout << "Level 18";
	gotoXY(64, 20);
	cout << "Level 19";
	gotoXY(64, 24);
	cout << "Level 20";
	gotoXY(2,8);
	cout << ">";
	gotoXY(12,8);
	cout << "<";
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
		if(keyPressed[K_DOWN] && levelnumber != 5 && levelnumber != 10 && levelnumber != 15 && levelnumber != 20 && levelnumber != 25)
		{
			levelnumber += 1;
			gotoXY(leftarrowX,leftarrowY);
			cout << " ";
			gotoXY(rightarrowX,rightarrowY);
			cout << " ";
			leftarrowY += 4;
			rightarrowY += 4;
			gotoXY(leftarrowX,leftarrowY);
			cout << ">";
			gotoXY(rightarrowX,rightarrowY);
			cout << "<";
			gotoXY(2,0);
			system("pause > nul");
		}
		else if(keyPressed[K_UP] && levelnumber != 1 && levelnumber != 6 && levelnumber != 11 && levelnumber != 16 && levelnumber != 21)
		{
			levelnumber -= 1;
			gotoXY(leftarrowX,leftarrowY);
			cout << " ";
			gotoXY(rightarrowX,rightarrowY);
			cout << " ";
			leftarrowY -= 4;
			rightarrowY -= 4;
			gotoXY(leftarrowX,leftarrowY);
			cout << ">";
			gotoXY(rightarrowX,rightarrowY);
			cout << "<";
			gotoXY(2,0);
			system("pause > nul");
		}
		else if(keyPressed[K_LEFT] && levelnumber > 5)
		{
			levelnumber -= 5;
			gotoXY(leftarrowX,leftarrowY);
			cout << " ";
			gotoXY(rightarrowX,rightarrowY);
			cout << " ";
			leftarrowX -= 20;
			rightarrowX -= 21;
			gotoXY(leftarrowX,leftarrowY);
			cout << ">";
			gotoXY(rightarrowX,rightarrowY);
			cout << "<";
			gotoXY(2,0);
			system("pause > nul");
		}
		else if(keyPressed[K_RIGHT] && levelnumber < 16)
		{
			levelnumber += 5;
			gotoXY(leftarrowX,leftarrowY);
			cout << " ";
			gotoXY(rightarrowX,rightarrowY);
			cout << " ";
			leftarrowX += 20;
			rightarrowX += 21;
			gotoXY(leftarrowX,leftarrowY);
			cout << ">";
			gotoXY(rightarrowX,rightarrowY);
			cout << "<";
			gotoXY(2,0);
			system("pause > nul");
		}
		else if(keyPressed[K_RETURN])
		{
			cout << "seriously? no";
			return levelnumber;
		}
		else if(keyPressed[K_ESCAPE])
		{
			cout << "hello my friends";
			return 68;
		}
	}
}

void errorreport()
{
	gotoXY(0,0);
	cout << "  _ Error loading level. Thanks, Obama.   ";
}

int menu()  
{   
    cls();
    int count = 0 ;
    keyPressed[K_UP] = isKeyPressed(VK_UP);
    keyPressed[K_DOWN] = isKeyPressed(VK_DOWN);
    keyPressed[K_LEFT] = isKeyPressed(VK_LEFT);
    keyPressed[K_RIGHT] = isKeyPressed(VK_RIGHT);
    keyPressed[K_ESCAPE] = isKeyPressed(VK_ESCAPE);     
    keyPressed[K_RETURN] = isKeyPressed(VK_RETURN);
    cout << "  _______ _             _____                _    " << endl ;  
    cout << " |__   __| |           / ____|              | |   " << endl ;    
    cout << "    | |  | |__   ___  | |  __ _ __ ___  __ _| |_  " << endl ;   
    cout << "    | |  | '_ \\ / _ \\ | | |_ | '__/ _ \\/ _` | __| " << endl ;     
    cout << "    | |  | | | |  __/ | |__| | | |  __/ (_| | |_  " << endl ;  
    cout << "    |_|  |_| |_|\\___|  \\_____|_|  \\___\\\\__,_|\\__| "  << endl;              
    cout << "   _  __                        "<< endl ;    
    cout << "  | |/ /                        "<< endl ;   
    cout << "  | ' / __ _ _ __  _ __   __ _  " << endl;   
    cout << "  |  < / _` | '_ \\| '_ \\ / _` | " << endl;   
    cout << "  | . \\ (_| | |_) | |_) | (_| | " << endl;    
    cout << "  |_|\\_\\__,_| .__/| .__/ \\__,_| " << endl;   
    cout << "            | |   | |           "<< endl ;  
    cout << "            |_|   |_|           " << endl;        
	rainbowhere += 1;
	if(rainbowhere > 14)
	{
		rainbowhere = 9;
	}
	colour(colorskappa[rainbowhere]);
    //cout << static_cast<char>(176)<<static_cast<char>(176)<<static_cast<char>(176)<<static_cast<char>(176)<<static_cast<char>(176)<<static_cast<char>(176)<<static_cast<char>(176)<<static_cast<char>(176)<<static_cast<char>(176)<<static_cast<char>(176)<<static_cast<char>(176)<<static_cast<char>(176)<<static_cast<char>(176)<<static_cast<char>(176)<<static_cast<char>(176)<<static_cast<char>(176)<<static_cast<char>(176)<<static_cast<char>(176)<<static_cast<char>(176)<<static_cast<char>(176)<<static_cast<char>(176)<<static_cast<char>(176) << endl ;     
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
    colour(colors[15]);
	gotoXY(45,14);
    cout << " Welcome to  " ;         
    gotoXY(45,15);   
    cout << " 'The Great Kappa' game! " ;                
    gotoXY(48,17);
    cout << "PLAY GAME" ;  
    gotoXY(48,19);   
    cout << "CHALLENGES" ;    
    gotoXY(48,21);   
    cout << "ACHIEVEMENTS & OPTIONS" ;    
    gotoXY(48,23);      
    cout << "EXITERINO" ;    
    gotoXY(45,17);   
    cout << '>' ;  
	int frequency = 2640;
    while (true)  
    {
        getInput();     
        if ( keyPressed[K_DOWN] == 1 )    
        {
            if ( count == 0 )   
            {
                gotoXY(45,17);
                cout << ' ' ;  
                gotoXY(45,19);
                cout << '>' ;  
                count = 1 ;       
				frequency -= 300;
			Beep(frequency, 60);
                system("pause > nul");
            }
            else if ( count == 1 )   
            {
                gotoXY(45,19);
                cout << ' ' ;
                gotoXY(45,21); 
                cout << '>' ;
                count = 2 ;   
				frequency -= 300;
			Beep(frequency, 60);
                system("pause > nul");
            }
            else if ( count == 2 ) 
            {
                gotoXY(45,21);
                cout << ' ' ;  
                gotoXY(45,23);
                cout << '>' ; 
                count = 3 ;    
				frequency -= 300;
			Beep(frequency, 60);
                system("pause > nul");
            }
			
        }   
        else if ( keyPressed[K_UP] == 1 )     
        {
            if ( count == 1 )  
            {
                gotoXY(45,19);
                cout << ' ' ;
                gotoXY(45,17);
                cout << '>' ;
                count = 0 ;   
				frequency += 300;
			Beep(frequency, 60);
                system("pause > nul");
            }
            else if ( count == 2 ) 
            {
                gotoXY(45,21);
                cout << ' ' ;
                gotoXY(45,19);
                cout << '>' ;
                count = 1 ;    
				frequency += 300;
			Beep(frequency, 60);
                system("pause > nul");
            }
            else if ( count == 3 )   
            {
                gotoXY(45,23); 
                cout << ' ' ; 
                gotoXY(45,21);  
                cout << '>' ; 
                count = 2 ;    
				frequency += 300;
			Beep(frequency, 60);
                system("pause > nul");
            }
        }     
        else if ( keyPressed[K_RETURN] == 1 )        
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
                gotoXY(30,10);   
                cout << "Are you SURE?" ;      
                Sleep(500);
                gotoXY(50,6);     
                cout << "SRSLY" ;       
                Sleep(400);
                gotoXY(13,27);   
                cout << "REALLY?" ;    
                Sleep(300);
                gotoXY(43,21);   
                cout << "BUT WHY" ;   
                Sleep(200);
                gotoXY(3,16);    
                cout << "I THOUGHT YOU LOVED ME" ;    
                Sleep(200);        
                gotoXY(70,23);    
                cout << ":-(" ;    
                Sleep(200);    
                gotoXY(17,5);    
                cout << "GET BACK HERE" ;     
                Sleep(200);       
                gotoXY(39,14);    
                cout << "DONT PRESS ENTER" ;     
                Sleep(200);      
                gotoXY(39,17);        
                cout << "NOOOOOOOOOO";   
				gotoXY(0,0);
                return 69;
            }   
        }
    }   
}

int challenge() 
{
    cls();     
    cout << "             _____ _           _ _                             " << endl ;    
    cout << "            / ____| |         | | |                            " << endl ;   
    cout << "           | |    | |__   __ _| | | ___ _ __   __ _  ___  ___  " << endl ;   
    cout << "           | |    | '_ \\ / _` | | |/ _ \\ '_ \\ / _` |/ _ \\/ __| " << endl ;   
    cout << "           | |____| | | | (_| | | |  __/ | | | (_| |  __/\\__ \\ " << endl ;     
    cout << "            \\_____|_| |_|\\__,_|_|_|\\___|_| |_|\\__, |\\___||___/ " << endl ;   
    cout << "                                               __/ |           " << endl ;   
    cout << "                                              |___/            " << endl ;

    gotoXY(4,10);   
    cout << "Level 1" ;     
    gotoXY(4,14); 
    cout << "Level 2" ;     
    gotoXY(4,18);
    cout << "Level 3" ;  
    gotoXY(4,22);
    cout << "Level 4" ;   
    gotoXY(4,26);   
    cout << "Level 5" ;       
    gotoXY(24,10);   
    cout << "Level 6" ;  
    gotoXY(24,14);
    cout << "Level 7" ;   
    gotoXY(24,18);    
    cout << "Level 8" ;  
    gotoXY(24,22);
    cout << "Level 9" ;   
    gotoXY(24,26);
    cout << "Level 10" ;     
    gotoXY(44,10);
    cout << "Level 11" ;   
    gotoXY(44,14);
    cout << "Level 12" ; 
    gotoXY(44,18);   
    cout << "Level 13" ;   
    gotoXY(44,22);
    cout << "Level 14" ;   
    gotoXY(44,26);
    cout << "Level 15" ;    
    gotoXY(64,10);
    cout << "Level 16" ;   
    gotoXY(64,14);
    cout << "Level 17" ; 
    gotoXY(64,18);   
    cout << "Level 18" ;   
    gotoXY(64,22);
    cout << "Level 19" ;   
    gotoXY(64,26);
    cout << "Level 20" ;        
    gotoXY(2,10);    
    cout << ">" ;    
    int xcoord = 2 ;   
    int ycoord = 10 ;  
    while ( true )  
    {
        getInput();  
        if ( keyPressed[K_ESCAPE] == 1 )   
        {
            return 4;  
            break;
        }
        if ( ( keyPressed[K_RIGHT] == 1 ) && ( xcoord < 65 ) )    
        {
            gotoXY(xcoord,ycoord);    
            cout << " " ;    
            xcoord += 20 ;
            gotoXY(xcoord ,ycoord);   
            cout << ">" ;    
            system("pause > nul");
        }    
        if ( ( keyPressed[K_LEFT] == 1) && ( xcoord>5 ) )    
        {
            gotoXY(xcoord,ycoord); 
            cout << " " ; 
            xcoord -= 20 ;  
            gotoXY(xcoord,ycoord) ;   
            cout << ">" ;  
            system("pause > nul"); 
        }    
        if ( ( keyPressed[K_DOWN] == 1 ) && ( ycoord < 26 ) )  
        {
            gotoXY(xcoord,ycoord); 
            cout << " " ; 
            ycoord += 4;  
            gotoXY(xcoord,ycoord) ;   
            cout << ">" ;  
            system("pause > nul");   
        } 
        if ( ( keyPressed[K_UP] == 1 ) && ( ycoord > 10 ) )  
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
    cout << "               _     _                                     _       " << endl;
    cout << "     /\\       | |   (_)                                   | |      " << endl;    
    cout << "    /  \\   ___| |__  _  _____   _____ _ __ ___   ___ _ __ | |_ ___ " << endl;   
    cout << "   / /\\ \\ / __| '_ \\| |/ _ \\ \\ / / _ \\ '_ ` _ \\ / _ \\ '_ \\| __/ __|" << endl;
    cout << "  / ____ \\ (__| | | | |  __/\\ V /  __/ | | | | |  __/ | | | |_\\__ \\" << endl;     
    cout << " /_/    \\_\\___|_| |_|_|\\___| \\_/ \\___|_| |_| |_|\\___|_| |_|\\__|___/" << endl;       
    while (true)   
    {
        getInput();
        if ( keyPressed[K_ESCAPE] == 1 )    
        {
            return 4;  
            break;
        } 
    }
}