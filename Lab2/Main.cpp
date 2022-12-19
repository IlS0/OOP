#include "Game.h"


int main(int argc, char* argv[]) {
	//Game game = Game();///?
	//std::cout << argc<<std::endl;
	//argv[2 или 3] - итерации
	//argv[3 или 4] - аутпут
	switch (argc)
	{
	case 1: {
		Game game = Game();
		game.gameLoop();
	}
		break;

	case 2: {
		Game game = Game(FileArgs(argv[1]), FILE_MODE);
		game.gameLoop();
	}
		break;

	case 6: {
		int iters{ -1 };
		std::string out;
		for (int i{ 1 }; i < argc-1; ++i) {
			//std::cout << argv[i] << std::endl;
			if (!strcmp(argv[i], "-i")) {
				iters = atoi(argv[i + 1]);
				if (argv[i + 1] != std::to_string(iters)) {
					std::cerr << "Invalid iterations value." << std::endl;
					return 0;
				}
			}
			else if (!strcmp(argv[i], "-o")) {
				out = argv[i + 1];
			}
		}

		if (iters == -1) {
			std::cerr << "Invalid iterations value." << std::endl;
			return 0;
		}

		if (out.empty() || out=="-i") {
			std::cerr << "Invalid name of the output file. Default name has been set." << std::endl;
			out = "Output.txt";
		}
		Game game = Game(FileArgs(argv[1]), OFFLINE_MODE);
		game.gameLoop(iters, out);
	}
		break;

	default:
		std::cerr << "Invalid arguments" << std::endl;
	}
}	