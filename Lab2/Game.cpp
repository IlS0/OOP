#include "Game.h"

Game::Game(const FileArgs& universe, const char mode) {
	gameMode = mode;
	name = universe.name;
	birthConds = universe.birthConds;
	survConds = universe.survConds;
	field = Field(universe.sizeX,universe.sizeY);
	for (auto i = universe.points.begin(); i != universe.points.end(); ++i) {

		field.setVal(std::get<0>(*i), std::get<1>(*i));
	}
};


Game::Game() {
	gameMode = DEFAULT_MODE;
	name = "The game of life";
	birthConds = { 3 };
	survConds = { 2, 3 };
	field = Field();

	//дефолтное поле 15x15 с бесконечно-живущей фигурой
	field.setVal(4, 5);
	field.setVal(5, 5);
	field.setVal(6, 5);
	field.setVal(6, 4);
	field.setVal(5, 3);
}


Game::~Game(){}


void Game::saveUniverse(const std::string& filename)
{
	std::ofstream fout(filename);
	fout <<"#N "<< name<<std::endl;
	fout << "#R B";
	for (auto i = birthConds.begin(); i != birthConds.end(); ++i) {
		fout << (*i);
	}
	fout << "/S";
	for (auto i = survConds.begin(); i != survConds.end(); ++i) {
		fout << (*i);
	}
	fout << std::endl;

	fout << "#F " << field.getSizeX() << " " << field.getSizeY() << std::endl;
	for (int y{ 1 }; y < field.getSizeY(); ++y) {
		for (int x{ 1 }; x < field.getSizeX(); ++x) {
			if (field.getVal(x,y) == 1) {
				fout << y << " " << x << std::endl;
			}
		}
	}
	fout.close();
}


void Game::gameLoop(const int& iters, const std::string& output)
{
	int ticks{ iters };
	std::string command, buf;

	if (gameMode == OFFLINE_MODE) {
		for (int i{ 0 }; i < ticks; ++i) {
			field.update(birthConds, survConds);
		}
		saveUniverse(output);
		return;
	}

	if (gameMode == DEFAULT_MODE) {
		std::cout << "There are no arguments. Game parameters have been set to default." << std::endl;
	}

	std::cout << "Game> Enter a command. Type \"help\" to get the command-list." << std::endl;
	std::cout << std::endl;
	std::cout << "User>";
	while (getline(std::cin,command)) {
		if (command == "exit") {
			return;
		}
		if (command == "help") {
			std::cout << "Short description:" << std::endl;
			std::cout << " help                    prints the command-list" << std::endl;
			std::cout << " dump <filename>         saves a universe as a txt, string arg, no default value" << std::endl;
			std::cout << " tick <n>                updates a field n times, int arg, 1 is default value" << std::endl;
			std::cout << " exit                    ends the game" << std::endl;
			std::cout << std::endl;
		}
		else if (command.substr(0, 4) == "dump") {
			try {
				saveUniverse(command.substr(5));
			}
			catch (std::out_of_range) {
				std::cerr << "Game> No output file. The file has been created with default name." << std::endl;
				saveUniverse("Output.txt");
			}
			std::cout << std::endl;
		}
		else if (command.substr(0,4) == "tick") {
			try {
				buf = command.substr(5);
				ticks = stoi(buf);
				if (buf != std::to_string(ticks)) {
					throw std::invalid_argument("");
				}
			}
			catch (std::out_of_range) {
				ticks = 1;
			}
			catch (std::invalid_argument) {
				std::cerr << "Game> Invalid tick value."<<std::endl;
				ticks = 0;
				std::cout << "User>";
				continue;
			}
			for (int i{ 0 }; i < ticks; ++i) {
				field.update(birthConds, survConds);
			}
			std::cout << *this;
		}
		else {
			std::cerr << "Game> Invalid command. Use \"help\" to get the command-list." << std::endl;
			std::cout << std::endl;
		}
		std::cout << "User>";
	}
}


std::ostream& operator<<(std::ostream& o, const Game& i) {
	o <<" "<<i.name << std::endl;
	o << " B";
	for (auto j = i.birthConds.begin(); j != i.birthConds.end(); ++j) {
		o << (*j);
	}
	o << "/S";
	for (auto j = i.survConds.begin(); j!= i.survConds.end(); ++j) {
		o << (*j);
	}
	o << std::endl << i.field<<std::endl;
	return o;
}

