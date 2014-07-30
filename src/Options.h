// Help.h
// Options Screen for Ultra Bear
// Copyright Ian Finlayson 2010
// This is part of UltraBear1 distributed under the MIT

#ifndef ULTRA1_OPTIONS
#define ULTRA1_OPTIONS

#include "GameState.h"

namespace Ultra1
{
	class OptionsState : public Ultra1::GameState
	{
	private:
		Ultra1::App* app;

	public:
		OptionsState( Ultra1::App* app )
		{
			this->app = app;
		}

		StateNumber Run( );
	};
}

#endif



