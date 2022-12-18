#include "Field.h"
//#include <iostream>


Field::Field(int x, int y )
{
	sizeX = x;
	sizeY = y;
	std::vector<char> inter = std::vector<char>(sizeY+2, 0);
	field = std::vector<std::vector<char>>(sizeX+2, inter);
}

Field::Field() : Field(15, 15) {}

Field::~Field(){}


char Field::newPointVal(const int& y, const int& x)
{
	//создать замкнутое поле
	char neighborCnt = field[y - 1][x - 1]+ field[y - 1][x]+ field[y - 1][x + 1]+ field[y][x - 1]
		+ field[y][x + 1]+ field[y + 1][x - 1]+ field[y + 1][x]+ field[y + 1][x + 1];

	switch (neighborCnt)
	{
		case 3: 
			return 1;
		case 2:
			return field[y][x];
		default: return 0;
	}

}



void Field::update()
{	
	//сделать замкнутое поле
	std::vector<std::vector<char>> newField = field;
	for (int y{ 1 }; y < sizeY; ++y) {
		for (int x{ 1 }; x < sizeX; ++x) {
			newField[y][x] = newPointVal(y, x);
		}
	}
	field = newField;
}


void Field::setVal(const int& x, const int& y)
{
	field[y][x] = 1;
}


std::ostream& operator<<(std::ostream& o, const Field& i)
{
	for (int y{ 0 }; y < i.sizeX; ++y) {
		for (int x{ 0 }; x < i.sizeY; ++x) {
			(!i.field[y][x]) ? o << " " << " " : o << '#' << " ";
		}
		o << std::endl;
	}
	o << "_______________________________" << std::endl;
	return o;
}