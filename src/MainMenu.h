// Menu.h
// Copyright Ian Finlayson 2010
// This is part of UltraBear1 distributed under the MIT
// The menu game state

#ifndef ULTRA1_MENU
#define ULTRA1_MENU

#include "GameState.h"

namespace Ultra1
{
	class MainMenu : public Ultra1::GameState
	{
	private:
		Ultra1::App* app;

	public:
		MainMenu( Ultra1::App* app )
		{
			this->app = app;
		}

		// Run the menu, return users choice...
		StateNumber Run( );
	};
}

#endif



