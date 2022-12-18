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
	void update(/*передавать условия игры*/);

private:
	int sizeX;
	int sizeY;
	std::vector<std::vector<char>> field;
	char newPointVal(const int&, const int& /*условия*/);
};


