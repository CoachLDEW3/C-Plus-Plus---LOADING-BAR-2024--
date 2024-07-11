/************************************************************************************************
	Name:	 CoachLDEW
	Date:	 07.11.2024
	Purpose: This program demonstrates a loading bar 
*************************************************************************************************/

#include <iostream>			//This library contains standard input and output processes
#include <conio.h>			//This library contains the function to detect keypresses
#include <Windows.h>		//This library contains the function to control the cursor position


using namespace std;


//Function to hide the cursor
void HideCursor()
{
	HANDLE hCon;
	hCon = GetStdHandle(STD_OUTPUT_HANDLE);		//Get the ID of the console window
	//Data Structure that controls the apearance of the cursor.  It has two attributes dwSize and bVisible
	CONSOLE_CURSOR_INFO cursor;
	//This attribute changes the size of the cursor. Here it is set at 100%
	cursor.dwSize = 100;
	//This Boolean attribute sets the cursor to visible or invisible.  False is invisible
	cursor.bVisible = false;

	//Manipulates the characteristics it takes two parameters.  The ID of the console window and a data structure that
	//handles the appearance of the cursor
	//You have to pass the cursor variable by reference so that it can make changes to the actual object
	SetConsoleCursorInfo(hCon, &cursor);
}//End HideCursor()


//Function that changes the window size
void WindowSize(int x, int y)
{
	HWND console = GetConsoleWindow();		//Get the Console Window and put it in a variable of the Window Handle type
	RECT ConsoleRect;						//Rect Structure defines a Rectangle (The Window)
	GetWindowRect(console, &ConsoleRect);

	MoveWindow(console, ConsoleRect.left, ConsoleRect.top, x, y, TRUE);
}//End WindowSize()


void GoToXY(int x, int y)
{
	HANDLE hCon;
	hCon = GetStdHandle(STD_OUTPUT_HANDLE);		//Get the ID of the console window

	COORD coord;								//Variable of type COORD that holds the X and Y position
	coord.X = x;
	coord.Y = y;

	//Takes two parameters.  The ID of the console window and Structure of the type COORD which are the coordinates where
	//we want to position the cursor.	
	SetConsoleCursorPosition(hCon, coord);
}//End GoToXY


void DrawBorders()
{
	//Border Dimensions (Playing Field Size)
	int width = 65;
	int height = 41;

	int tAndB = 205;			//Character code for top and bottom borders
	int lAndR = 186;			//Character code for left and right borders
	int topLeft = 201;			//Character code for top left corner
	int botLeft = 200;			//Character code for bottom left corner
	int topRight = 187;			//Character code for top right corner
	int botRight = 188;			//Character code for bottom right corner

	//Top & Bottom Borders
	for (int i = 2; i < width - 3; i++)
	{
		GoToXY(i, 3);
		cout << (char)tAndB;

		GoToXY(i, height - 2);
		cout << (char)tAndB;
	}

	//Left & Right Borders
	for (int j = 4; j < height - 2; j++)
	{
		GoToXY(2, j);
		cout << (char)lAndR;

		GoToXY(61, j);
		cout << (char)lAndR;
	}

	//Corners
	//Top Left
	GoToXY(2, 3);
	cout << (char)topLeft;

	//Bottom Left
	GoToXY(2, height - 2);
	cout << (char)botLeft;

	//Top Right
	GoToXY(61, 3);
	cout << (char)topRight;

	//Bottom Right
	GoToXY(61, height - 2);
	cout << (char)botRight;
	//Add 3 to the amount of spaces in the app name and subtract that from the width
	GoToXY(width - 18, height - 1);
	cout << "LOADING BAR 1.0";
}//End DrawBorders()


void SetConsoleColor(int textColor, int bgColor) {
	/************************************************************************************************
			 0 - BLACK			6 - YELLOW			12 - LIGHTRED
			 1 - BLUE			7 - WHITE			13 - LIGHTPURPLE
			 2 - GREEN			8 - GREY			14 - LIGHTYELLOW
			 3 - AQUA			9 - LIGHTBLUE		15 - BRIGHT WHITE
			 4 - RED			10 - LIGHTGREEN
			 5 - PURPLE			11 - LIGHTAQUA
************************************************************************************************/
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), (textColor + (bgColor * 16)));
}//End SetConsoleColor()


//This funtion will place a loading bar on the screen
void LoadingBar()
{
	int tAndB = 205;			//Character code for top and bottom borders
	int lAndR = 186;			//Character code for left and right borders
	int topLeft = 201;			//Character code for top left corner
	int botLeft = 200;			//Character code for bottom left corner
	int topRight = 187;			//Character code for top right corner
	int botRight = 188;			//Character code for bottom right corner
	int loadSquare = 178;

	GoToXY(10, 20);
	cout << "LOADING...";
	

	//Level Percentage %
	int level = 12;			//The level will start at 13% and go until 100%


	SetConsoleColor(4, 0);
	//Loading bar frame
	for (int x = 10; x < 55; x++)
	{
		GoToXY(x, 22);
		cout << (char)tAndB;

		GoToXY(x, 24);
		cout << (char)tAndB;
	}

	for (int y = 23; y < 24; y++)
	{
		GoToXY(10, y);
		cout << (char)lAndR;

		GoToXY(55, y);
		cout << (char)lAndR;
	}
	//Left Corners
	GoToXY(10, 22);
	cout << (char)topLeft;

	GoToXY(10, 24);
	cout << (char)botLeft;

	//Right Corners
	GoToXY(55, 22);
	cout << (char)topRight;

	GoToXY(55, 24);
	cout << (char)botRight;

	SetConsoleColor(15, 0);
	//Internal Bar Content
	for (int loading = 11; loading < 55; loading++)
	{
		GoToXY(loading, 23);
		cout << (char)loadSquare;
		Sleep(100);

		//Loading Percentage
		level += 2;				//Adding 3 to every cycle
		GoToXY(32, 25);
		cout << level << "%";
	}
}



int main()
{
	//Places a title in the Title Bar
	SetConsoleTitle(L"Loading Bar...");
	//Changes console window to 500x700
	WindowSize(500, 700);
	//Hides the cursor
	HideCursor();
	//Draws the borders
	DrawBorders();
	//Displays a loading bar
	LoadingBar();
	

	bool gameOver = false;

	//Game Loop.  While the game is not over do...
	while (!gameOver)
	{;

		//Hit the escape key to end the program
		if (GetAsyncKeyState(VK_ESCAPE)) gameOver = true;


		Sleep(10);
	}

	return 0;
}