#include "CPU.h"
#ifdef MAKELINUX
#include <gtk/gtk.h>
#include <iostream>
#include <cstdlib>
#else
#include "Windows.h"
#endif

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

#ifdef MAKELINUX
	std::cout << "You Lose:(" << std::endl;
    std::cout << "better Luck Next Time!" << std::endl;

    gtk_init(nullptr, nullptr);
    GtkWidget *dialog = gtk_message_dialog_new(nullptr,
                                                GTK_DIALOG_MODAL,
                                                GTK_MESSAGE_INFO,
                                                GTK_BUTTONS_OK,
                                                "You Lose :(");
    gtk_window_set_title(GTK_WINDOW(dialog), "better Luck Next Time!");
    gtk_dialog_run(GTK_DIALOG(dialog));
    gtk_widget_destroy(dialog);
    while (g_main_context_iteration(nullptr, FALSE));
    std::exit(0); // Exit the application
#else

	MessageBoxA(NULL,"You Lose :(",
		"better Luck Next Time", MB_OK);
	SendMessageA(NULL, WM_CLOSE, 0, 0);
#endif

}