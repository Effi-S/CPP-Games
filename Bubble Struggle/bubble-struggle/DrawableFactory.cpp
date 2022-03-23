#include "DrawableFactory.h"
#include "Board.h"

void DrawableFactory::createDrawable(std::string str)
{
	Board & board = Board::inst();
	ObjInfo info(str);

	auto it = MyMap().find(info._name);

	if(it !=MyMap().end())
		it->second(info, board);
		
}

bool DrawableFactory::registerMe(const std::string & str, void(*f)(ObjInfo info ,Board &))
{
	MyMap().emplace(str, f);
	return true;
}





