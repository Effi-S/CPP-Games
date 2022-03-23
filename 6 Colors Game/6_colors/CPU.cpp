#include "CPU.h"
#include "Windows.h"

sf::Color MY_COLORS[6] = {
	sf::Color::Red,
	sf::Color::Blue,
	sf::Color::Green,
	sf::Color::Yellow,
	sf::Color::Magenta,
	sf::Color::Cyan,
};

//this is the CPU's move 
//it goes through the ShapeCells 
//and finds the colorcount of each color
//then it moves the most frequent color found.
void CPU::move(sf::Color color)
{
	int max=0;
	sf::Color frequent = sf::Color::White;

	for (sf::Color x: MY_COLORS)
		if (x != color)
		{
			int count = Player::getColorCount(x); // done in player so not to reveal private members.
			if (count >= max)
			{
				max = count;
				frequent = x;
			}
				
		}
						
	if(frequent!=sf::Color::White)
		Player::paintAll(frequent);
}

//prints that the Cpu won. 
void CPU::iWin() const
{	
	MessageBoxA(NULL,"You Lose",
		"better Luck Next Time", MB_OK);
	SendMessageA(NULL, WM_CLOSE, 0, 0);
}