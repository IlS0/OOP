//#include <iostream>//*****
#include "Game.h"

int main(int argc, char* argv[]) {
	Game game = (argc > 1) ? Game(Args(argv[1])) : Game();
	game.gameLoop();
}