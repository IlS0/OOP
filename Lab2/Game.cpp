#include "Game.h"
#include "windows.h"//**

Game::Game(const Args& universe) {
	name = universe.name;
	conditions = universe.conds;
	field = Field(universe.sizeX,universe.sizeY);
	for (auto i = universe.points.begin(); i != universe.points.end(); ++i) {
		field.setVal(std::get<0>(*i), std::get<1>(*i));
	}
};


Game::Game() {
	name = "The game of life";
	conditions = { 3,2,3 };
	field = Field();
	//заменить на возможность рисовать с интерфейса
	field.setVal(4, 5);
	field.setVal(5, 5);
	field.setVal(6, 5);
	field.setVal(6, 4);
	field.setVal(5, 3);
}


Game::~Game(){}

void Game::gameLoop()
{
	std::cout << "Press any key" << std::endl;//
	std::cin.get();//
	std::cout <<name<< std::endl;
	std::cout << field;
	Sleep(1000);
	while (1/*std::cin.get() != 'q'*/) {
		field.update();
		std::cout << name << std::endl;
		std::cout << field;
		Sleep(1000);///
	}
}

