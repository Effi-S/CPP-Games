/*Bomberman
***************************************
	Files :

	Controller.cpp and Controller.h - controls the game.

	LevelLoader.cpp and LevelLoader.h - the level builder Class

	Robot.cpp and Robot.h - the Robot class  derrrived from character base class.
	Guard.cpp and Guard.h - Guards class derrrived from character base class.
	dumbGuard.cpp anddumbGuard.h - derrrived from Placeable base class.
	and smartGuard.cpp and smartGuard.h - derrrived from Placeable base class.
	Bomb.cpp and Bomb.h - the Bombs class  derrrived from Placeable base class.
	Door.cpp and Door.h - derrrived from Placeable base class.
	Stone.cpp and Stone.h -  derrrived from Placeable base class.
	Edge.cpp and Edge.h - derrrived from Placeable base class.
	Present.cpp and Presant.h - derrrived from Placeable base class.
	EmptyCell.cpp and EmptyCell.h -  derrrived from Placeable base class.
	CONSTS.h : hold constant values structs and enums for use of any of  classes.

	Placeable.cpp and Placeable.h-pure virtual class.
	Character.cpp and Character.h - pure virtual class derived from Placeable.

	highscore.txt : for holding the current highscore.
	board.txt file: for making gthe map:
	each level must have on top the rows the columns the time and the bombs in that order.
	a negetive number of bombs will give infinity bombs.
	the robot  is symbolized by the character '/'.
	the guard is symbolized by the character '!'.
	Stone is sybolized by the symbol '@'.
		or '&' for Stone with Present inside of it.
	Edge : is sybolized by '#'.
	 Door is symbolized by 'D'.
	 EmptyCell with presant is symbolyzed with '+'.


Description : This is the Bomberman game.
	Gameplay : 
	for each level the player is given 5 lives.
		and X amount of time to be the second number on the top of every
		level in "Boards.txt" right after the size of the level.
		
The Player moves according to the input given by the Users
The Guard moves according to their type.
and is killed if hit by bomb(explained in the Bomb section).

if the player reaches a door the next level is created
the player is given 5 lives and bombs according to the level.

if the Guard moves to the same cell as the player or the player is in the same cell
as a bomb that explodes or its  surrounding cells the player loses a life.

if the player runs out of time he also loses a life and the time is restarted.
losing a life returns the player to its first cell.

the game ends by either the player finishing all levels or losing all lives in a given level.

Design :
	
	the controller calls onto the UserInterface to receive from it the users choices 
	and act accordingly.
	the controller loads maps from the LevelLoader when neccessary.
	and if the user is in the game the controller for every TURN_UNIT amount of time
	(found in CONSTS.h) plays a turn.
	Controller:
		in charge of controlling the game play.
		it holds a member of class LevelLoader
		it calls on the it when neccessary to load another level.
		holds a member of UserInterface and map and decides 
		when to call on them.
		as well as when to print them to the screen.

	UserInterface:
		this is the user interface class incharge of interaction 
		with the user outside the game 
		it has 2 i rectangle arrays: 
		 1) the menu for when the game is not beeing played 
		 2) the toolbar for when the game is beeing played.
		
		it also prints to the screen on the whole 
		screen images that explain to the user 
		what has happend in the game.

	Robot:  
		the Robot moves on the screen two dimensionaly.
		by the user pressing the arrow key, searching for doors to the
		next level.
		he can plant bombs by pressing 'b' that explode within 5 seconds of being planted.
		The bombs kill / clear all Guards Stone or the Player himself in the surounding 4 cells on the
		screen or in its own cell once it finishes the countdown and for one turn.

	Guard:
		moves in 4 different ways on the screen : chase, chaseNear, random and
		and is the main obstacle for the Player, removing a life from the player if it acheives the goal of
		reaching the players cell.
		when getting hit by a bomb the guard is removed from the board for a short
		amount of turns and then returns to the first cell it apeard in.

	Bomb : the bomb is planted by the player then counts down from 5 to 1.
		(also changing its character symbol accordingly on the screen)
		and the explodes leavin its cell and all 4 surrounding cells the
		character '*'. if the player was in one of the cells it loses a life.
		if one of the cells was a guard it is killed.
		both will be deleted from the screen and return to their original placement
		on the boar, the player the next turn and the guard in the amount of turns it needs to wait
		untill it respawns.
		the bomb can also remove a Stone.explained in the stones section.

	Door:
	if the Robot reaches this cell the next level is printed onto
	the screen.

	Edge : 
			no moving characters can enter this cell nor can this cell be removed.
			(other by changing the level).

	Stone :
			this is a boarder that no moving charcter can cross but different to the Edge
			.it can be removed from the board by the explosion of a bombon in
			one of the cells adjacent to the stone.
			and it can then print a present if it has one.
	EmptyCell:
			it randomly generates a background from the img it receives 
			and can hold a present 
			has no other functionality other than allowing character movement into 
			its space.

	SmartGuard:
			this is the smart guard class
			 it is derrived from the base class guard 
			it uses bfs in order to find the shortest route to the robot
			that it receives a pointer to.
			
			it only uses bfs if  the folowing is true:
			 1) it in view
			2) it completed a full cell movement.

	DumbGuard:
			this is the dumbGuard class derrived from the Guard base class
			the only adjusment is that the move is random.

algorithms:
		the smartGuards use BfS

Known Bugs: bomb not always displayed after it hits Robot.
			



	*******************************************************************/


//---sfml headers---
#ifdef _DEBUG
#pragma comment ( lib , "openal32.lib" )
#pragma comment ( lib , "opengl32.lib" )
#pragma comment ( lib , "winmm.lib" )
#pragma comment ( lib , "gdi32.lib" )
#pragma comment ( lib , "ws2_32.lib" )
#pragma comment ( lib , "flac.lib" )
#pragma comment ( lib , "vorbisenc.lib" )
#pragma comment ( lib , "vorbisfile.lib" )
#pragma comment ( lib , "vorbis.lib" )
#pragma comment ( lib , "freetype.lib" )
#pragma comment ( lib , "ogg.lib" )

#pragma comment ( lib , "sfml-system-s-d.lib" )
#pragma comment ( lib , "sfml-window-s-d.lib" )
#pragma comment ( lib , "sfml-graphics-s-d.lib" )
#pragma comment ( lib , "sfml-audio-s-d.lib" )
#pragma comment ( lib , "sfml-main-d.lib" )
#elif defined (NDEBUG)
#pragma comment ( lib , "openal32.lib" )
#pragma comment ( lib , "opengl32.lib" )
#pragma comment ( lib , "winmm.lib" )
#pragma comment ( lib , "gdi32.lib" )
#pragma comment ( lib , "ws2_32.lib" )
#pragma comment ( lib , "flac.lib" )
#pragma comment ( lib , "vorbisenc.lib" )
#pragma comment ( lib , "vorbisfile.lib" )
#pragma comment ( lib , "vorbis.lib" )
#pragma comment ( lib , "freetype.lib" )
#pragma comment ( lib , "ogg.lib" )

#pragma comment ( lib , "sfml-system-s.lib" )
#pragma comment ( lib , "sfml-window-s.lib" )
#pragma comment ( lib , "sfml-graphics-s.lib" )
#pragma comment ( lib , "sfml-audio-s.lib" )
#pragma comment ( lib , "sfml-main.lib" )
#elif defined (MAKELINUX)
#else
#error "Unrecognized configuration!"
#endif
//---------------

//---------include--------
#include "Map.h"
#include "Controller.h"
#include<cstdlib>
#include "LevelLoader.h"

//************main  section***************
int main()
{
	srand(time(NULL));

	LevelLoader lvloader;
	
	Controller controller(lvloader);
	controller.Run();
	
	return EXIT_SUCCESS;
}
//*****************************************

