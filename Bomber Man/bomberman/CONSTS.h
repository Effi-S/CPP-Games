#pragma once
//*******************
//constant to be used by
//any or all class's
//*******************
#pragma once
#include <SFML/Graphics.hpp>


//default window size
const int defwindow_x = 1024;
const int defwindow_y = 512;
//----
//window clearing colors.
const sf::Color CLEAR1(215, 255, 245, 255);
const sf::Color MINI_CLEAR(215, 215, 200, 255);
const sf::Color TOOL_CLEAR(216, 216, 255, 216);
const sf::Color MENU_CLEAR(216, 255, 216, 255);

//default cell size:
const sf::Vector2f CELLSIZE(32.f, 32.f);

//const int ITEMS = 10;//the number of items

//menu buttonsizes
const sf::Vector2f MENU_BUTTONSIZE(192.f, 64.f);
const sf::Vector2f TOOLBAR_BUTTONSIZE(100.f, 62.f);

//toolbar
enum toolbar_index_t
{	bar_pause_t =0 , bar_restart_t =1 ,
bar_time_t=2, bar_lives_t =3,  bar_bombs_t=4 ,  bar_score_t=5, bar_lvl_t=6
};

//menu 
enum menu_index_t
{
	play_t = 0, helpMe_t=1,  highScore_t = 2, exitGame_t = 3
};
//images 
const int IMAGES = 9;
enum img_t {
	empty_t = 0, edge_t = 1, stone_t = 2, door_t = 3,
	robot_t = 4, guard_t = 5, bomb_t = 6 ,smartGuard_t =7 , present_t = 8
	
};

//moves
enum move_t {
	up_t=0, down_t=1, left_t=2,	right_t=3 ,extra_t=4 ,no_move=5
};

const float latMove = (CELLSIZE.y / 8);
const float horMove = (CELLSIZE.x / 8);

const sf::Time TURN_UNIT = sf::seconds(0.03f);


//actions
enum action_t {
	NO_ACTION = 0,
	RESTART = 1,
	PAUSE = 2, 
	NEXT_LVL = 3,
	END_GAME=4,
	CLOSE = 5

};
 
struct gameInfo
{
	int time = 0;
	int lives = 5;
	int bombs = 10;
	int score = 0;

	bool nextlvl = false;
};

const int PRESENTS = 4;

enum pres_t {
	oneUp_t = 0,
	scoreUp_t = 1,
	bombUp_t = 2,	
	ammoUp_t = 3,
	noUp_t = PRESENTS
};