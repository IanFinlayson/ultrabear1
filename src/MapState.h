// MapState.h
// Copyright Ian Finlayson 2010
// This is part of UltraBear1 distributed under the MIT
// The map state

#ifndef ULTRA1_MAPSTATE
#define ULTRA1_MAPSTATE

#include "GameState.h"

namespace Ultra1
{
	class MapState : public Ultra1::GameState
	{
	private:
		Ultra1::App* app;

	public:
		MapState( Ultra1::App* app )
		{
			this->app = app;
		}

		// Run the map, return game and keep track of which level the user is at
		StateNumber Run( );
	};
}

#endif



