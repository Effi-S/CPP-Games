//this is a Factory class for creating 
//a drawable object by simply sending 
//a string with the name  and upto 4 floats
//as parameters placed into a struct ObjInfo . 
//this lets any object register itself 
//with RegiterMe function 
//the functions are placed into a map 
//to be later created be the board 
// via the levelloader or during runtime.
#pragma once
#include <map>
#include <memory>
#include <sstream>
#include <iostream>
#include <string>

//a helpful struct for placing a string into a name and 4 
//seperate floats without allot of work.
	struct  ObjInfo {
		ObjInfo(std::string str){
			std::stringstream ss(str);
			ss >> _name >> _x1 >> _x2 >> _x3 >> _x4;
		}; 
		
		std::string _name;
		float _x1 = -1, _x2 = -1, _x3 = -1, _x4 = -1;
	};
//the Factory class itself.
class DrawableFactory
{
public:
	
	static void createDrawable(std::string );

	static bool registerMe(const std::string & str, void(*f)(ObjInfo info,class Board & ));

private:
	DrawableFactory() = default;
	~DrawableFactory() = default;

	
	static std::map<std::string, void(*)(ObjInfo info,class Board &board)> & MyMap() {
		static std::map<std::string, void(*)(ObjInfo info,class Board &board)> m;
		return m;}// for internal use only //returning the map of the creation functions

};








