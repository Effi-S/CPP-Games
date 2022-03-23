
#include "Person.h"
#include "ToolBar.h"
#include "Windows.h"

//this is the players move 
//receives a sfml color into color 
//and paints all the neighbouring cells 
//that color.
void Person::move(sf::Color color)
{	
	if(color != sf::Color::White && color!=sf::Color::Black)
		paintAll(color);	
}

//the player prints to screen that it won
void Person::iWin() const
{	
	MessageBoxA(NULL, "Player WON!",
		"CONGRADULATION!", MB_OK);
	SendMessageA(NULL, WM_CLOSE, 0, 0);
}
