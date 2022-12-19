#pragma once
#include <string>
#include <fstream>
#include <vector>
#include <tuple>
#include <iostream>

class FileArgs {
public:
	FileArgs(const char* input)
	{
		std::ifstream fin(input);
		if (!fin) {
			std::cerr << "The file hasn't been opened. Probably it doesn't exist in the directory.";
			exit(1);
		}

		std::string buf;
		getline(fin, buf);
		name = buf.substr(3);

		getline(fin, buf);
		bool isSurvCond = false;
		for (auto i = buf.begin(); i != buf.end(); ++i) {

			if (*i == '/') isSurvCond = true;

			if (*i >= '0' && *i <= '9') {
				if(isSurvCond)
					survConds.push_back(*i - '0');
				else 
					birthConds.push_back(*i - '0');
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

	~FileArgs() {}
	std::string name;
	std::vector<int> birthConds;
	std::vector<int> survConds;
	int sizeX, sizeY;
	std::vector<std::tuple<int, int>> points;	
};