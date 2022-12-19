#pragma once
#include "Field.h"
#include "FileArgs.h"

//THE GAME MODES
#define DEFAULT_MODE 0
#define FILE_MODE 1
#define OFFLINE_MODE 2


class Game {
public:
	Game();
	Game(const FileArgs&,const char);
	~Game();
	void gameLoop(const int& = 0, const std::string& = "");
	friend std::ostream& operator<<(std::ostream& o, const Game& i);

private:
	std::string name;
	std::vector<int> birthConds;
	std::vector<int> survConds;
	Field field;
	char gameMode;
	void saveUniverse(const std::string&);
};