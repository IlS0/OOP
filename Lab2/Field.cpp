#include "Field.h"
#include <iostream>


Field::Field(int x, int y )
{
	sizeX = x;
	sizeY = y;
	std::vector<bool> inter = std::vector<bool>(sizeY, false);
	field = std::vector<std::vector<bool>>(sizeX, inter);
}

Field::~Field(){}

void Field::update()
{


}


std::ostream& operator<<(std::ostream& o, const Field& i)
{
	for (int y = 0; y < i.sizeX; ++y) {
		for (int x = 0; x < i.sizeY; ++x) {
			o << i.field[y][x] << " ";
		}
		o << std::endl;
	}
	o << "_______________________________" << std::endl;
	return o;
}