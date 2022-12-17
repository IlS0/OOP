#pragma once
#include <vector>
#include <iostream>


class Field
{
public:
	Field(int, int);
	~Field();
	friend std::ostream& operator<<(std::ostream& o, const Field& i);

private:
	int sizeX;
	int sizeY;
	std::vector<std::vector<bool>> field;
	void update();
};


