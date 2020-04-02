#include"game.h"

int main()
{
	RenderWindow app(VideoMode(860, 600), "MineSweeper-byQJY");
	Game game(&app);
	game.Run();

	return 0;
}