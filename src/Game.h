// Game.h
// Copyright Ian Finlayson 2010
// This is part of UltraBear1 distributed under the MIT
// The game game state

#ifndef ULTRA1_GAME
#define ULTRA1_GAME

#include <string>

#include "GameState.h"
#include "Level.h"
#include "Bear.h"

namespace Ultra1
{
	void DoDisplay( Ultra1::App* app, std::string& l, std::string& c, std::string& p );

	class Game : public Ultra1::GameState
	{
	private:
		Ultra1::App* app;

	public:
		Game( Ultra1::App* app )
		{
			this->app = app;
		}

		// Run the game, return where user goes next...
		StateNumber Run( );
	};
}

#endif





