#include <iostream>

Initialize();
GetInput();
UpdateGame();
Render();

ShutDown();

using namespace std;

int main()
{
	Initialize();

	while (!exitGame)
	{
		GetInput();
		UpdateGame();
		Render();
	}

	ShutDown();

	return 0;
}