// Lost.h
// Lost Screen for Ultra Bear
// Copyright Ian Finlayson 2010
// This is part of UltraBear1 distributed under the MIT

#ifndef ULTRA1_LOST
#define ULTRA1_LOST

#include "GameState.h"

namespace Ultra1
{
	class LostState : public Ultra1::GameState
	{
	private:
		Ultra1::App* app;

	public:
		LostState( Ultra1::App* app )
		{
			this->app = app;
		}

		StateNumber Run( );
	};
}

#endif



