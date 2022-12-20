#pragma once
#include <vector>
#include <iostream>


class Field
{
public:
	Field(int, int);
	Field();
	~Field();
	friend std::ostream& operator<<(std::ostream& o, const Field& i);
	void setVal(const int&, const int&);
	int getVal(const int&, const int&);
	void update(const std::vector<int>&, const std::vector<int>&);
	int getSizeX();
	int getSizeY();

private:
	int sizeX;
	int sizeY;
	std::vector<std::vector<char>> field;
	char newPointVal(const int&, const int&, const std::vector<int>&, const std::vector<int>&);
	int pointMod(const int&, const int&);
};


