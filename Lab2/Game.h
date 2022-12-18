#pragma once
#include "Field.h"
#include "Args.h"


class Game {
public:
	Game();
	Game(const Args&);
	~Game();
	void gameLoop();

private:
	std::string name;
	std::vector<int> conditions;//������ - birth, ��������� - survival
	Field field;
};