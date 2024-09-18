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

#include "Controller.h"
#include <cstdlib>
#include <memory>
#include "Menu.h"
#include "LoadScreen.h"

int main()
{
	Window::get().setActive(false);
	LoadScreen loading;

	//Window::get().setFramerateLimit(35);
	Window::get().setKeyRepeatEnabled(false);
	Window::get().setMouseCursorGrabbed(false);
	
	Controller controller;

	//init menu
	Menu menu(ResourceManager::instance()->getTexture(ResourceManager::Texture::MainMenu_bg));
	menu.add("1player", std::make_unique<Single>(controller));
	menu.add("2player", std::make_unique<Coop>(controller));
	menu.add("controls", std::make_unique<Controls>());
	menu.add("quit", std::make_unique<Quit>());

	loading.wait();
	while (Window::get().isOpen())
	{
		try {
			Window::get().clear();
			menu.run();
			Window::get().display();
		}
		catch (...) {}
	}

	return EXIT_SUCCESS;
}
