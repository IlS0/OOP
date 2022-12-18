#pragma once
#include <string>
#include <fstream>
#include <vector>
#include <tuple>

class Args {
public:
	Args(const char* args)
	{
		std::ifstream fin(args);
		std::string buf;
		getline(fin, buf);
		name = buf.substr(3);

		getline(fin, buf);
		for (auto i = buf.begin(); i != buf.end(); ++i) {
			if (*i >= '0' && *i <= '9') {
				conds.push_back(*i - '0');
			}
		}

		fin >> buf;
		fin >> sizeX >> sizeY;
		int fst{ 0 }, snd{ 0 };
		while (!fin.eof()) {
			fin >> fst >> snd;
			points.push_back(std::make_tuple(fst, snd));
		}
		fin.close();
	}

	~Args() {}
	std::string name;
	std::vector<int> conds;
	int sizeX, sizeY;
	std::vector<std::tuple<int, int>> points;
	
};