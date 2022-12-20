#include "Field.h"

Field::Field(int x, int y )
{
	sizeX = x;
	sizeY = y;
	std::vector<char> inter = std::vector<char>(sizeY+2, 0);
	field = std::vector<std::vector<char>>(sizeX+2, inter);
}

Field::Field() : Field(15, 15) {}

Field::~Field(){}


int Field::pointMod(const int& neigh, const int& size) 
{
	int _neigh{ neigh };
	
	if (neigh <= 0) {
		_neigh = -1;
	}
	else if (neigh >= size) {
		_neigh = size + 1;
	}

	return (_neigh + size) % size;

}


char Field::newPointVal(const int& y, const int& x, const std::vector<int>& birthConds, const std::vector<int>& survConds)
{
	char neighborCnt = field[pointMod(y - 1 , sizeY +1 )][pointMod(x - 1, sizeX +1)]
		+ field[pointMod(y - 1, sizeY +1 )][pointMod(x, sizeX +1 )]
		+ field[pointMod(y - 1, sizeY +1 )][pointMod(x + 1, sizeX +1)]
		+ field[pointMod(y, sizeY +1 )][pointMod(x - 1, sizeX +1 )]
		+ field[pointMod(y, sizeY +1 )][pointMod(x + 1, sizeX +1 )]
		+ field[pointMod(y + 1, sizeY +1 )][pointMod(x - 1, sizeX +1 )]
		+ field[pointMod(y + 1, sizeY +1 )][pointMod(x, sizeX +1 )]
		+ field[pointMod(y + 1, sizeY +1 )][pointMod(x + 1, sizeX +1 )];

	auto i = birthConds.begin();
	for (i; i != birthConds.end(); ++i) {
		if (neighborCnt == *i && (*i!=0)/*чтоб при cnt =0 не срабатывал*/) return 1;
	}

	auto j= survConds.begin();
	for (j; j != survConds.end(); ++j) {
		if (neighborCnt == *j && (*j != 0)) return field[y][x];
	}

	return 0;
}


void Field::update(const std::vector<int>& birthConds, const std::vector<int>& survConds)
{	
	std::vector<std::vector<char>> newField = field;
	for (int y{ 1 }; y <=sizeY; ++y) {
		for (int x{ 1 }; x <=sizeX; ++x) {
			newField[y][x] = newPointVal(y, x, birthConds, survConds);
		}
	}
	field = newField;
}


void Field::setVal(const int& x, const int& y)
{ 
	field[pointMod(y,sizeY)+1][pointMod(x,sizeX)+1] = 1;
	//+1, тк всё считается с 1 на поле
}

int Field::getVal(const int& y, const int& x) { return field[y][x]; }

int Field::getSizeX() { return sizeX; }

int  Field::getSizeY(){ return sizeY; }

std::ostream& operator<<(std::ostream& o, const Field& i)
{
	for (int y{ 0 }; y <=i.sizeX+1; ++y) {
		o << " ";
		for (int x{ 0 }; x <= i.sizeY+1; ++x) {
			if ((x == 0 && y == 0) || (x == i.sizeX + 1 && y == i.sizeY + 1)
				|| (y == 0 && x == i.sizeX + 1) || (x == 0 && y == i.sizeY + 1)) {
				o << "+";
				continue;
			}

			if (x<1 || x>i.sizeX) {
				o << "|";
				continue;
			}

			if (y<1 || y>i.sizeY) {
				o << "--" ;
				continue;
			}
			(!i.field[y][x]) ? o<<" " <<" ": o << '#'<<" " ;
		}
		o << std::endl;
	}
	return o;
}