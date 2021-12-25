#include "GameWindow.h"

int CALLBACK WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpComLine, int nComShow) {

	GameWindow game(hInstance);
	game.Init();
	game.Run();
	return 0;
}
