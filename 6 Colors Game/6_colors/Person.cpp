
#include "Person.h"
#include "ToolBar.h"
#ifdef MAKELINUX
#include <gtk/gtk.h>
#include <iostream>
#include <cstdlib>
#else
#include "Windows.h"
#endif

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

#ifdef MAKELINUX
    std::cout << "Player WON!" << std::endl;
    std::cout << "CONGRATULATIONS!" << std::endl;
    
    gtk_init(nullptr, nullptr);
    GtkWidget *dialog = gtk_message_dialog_new(nullptr,
                                                GTK_DIALOG_MODAL,
                                                GTK_MESSAGE_INFO,
                                                GTK_BUTTONS_OK,
                                                "Player WON!");
    gtk_window_set_title(GTK_WINDOW(dialog), "CONGRATULATIONS!");
    gtk_dialog_run(GTK_DIALOG(dialog));
    gtk_widget_destroy(dialog);
    while (g_main_context_iteration(nullptr, FALSE));
    std::exit(0); // Exit the application
#else
    MessageBoxA(NULL, "Player WON!", "CONGRATULATIONS!", MB_OK);
    SendMessageA(NULL, WM_CLOSE, 0, 0);
#endif
}
