// Won.h
// Copyright Ian Finlayson 2010
// This is part of UltraBear1 distributed under the MIT

// The won game state

#ifndef ULTRA1_WON
#define ULTRA1_WON

#include "GameState.h"

namespace Ultra1
{
	class WonState : public Ultra1::GameState
	{
	private:
		Ultra1::App* app;

	public:
		WonState( Ultra1::App* app )
		{
			this->app = app;
		}

		// Run the won screen, return to menu...
		StateNumber Run( );
	};
}

#endif



