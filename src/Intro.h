// Intro.h
// Copyright Ian Finlayson 2010
// This is part of UltraBear1 distributed under the MIT
// The intro game state

#ifndef ULTRA1_INTRO
#define ULTRA1_INTRO

#include "GameState.h"

namespace Ultra1
{
	class Intro : public Ultra1::GameState
	{
	private:
		Ultra1::App* app;

	public:
		Intro( Ultra1::App* app )
		{
			this->app = app;
		}

		// Run the intro, return menu
		StateNumber Run( );
	};
}

#endif



