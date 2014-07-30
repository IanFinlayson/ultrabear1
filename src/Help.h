// Help.h
// Copyright Ian Finlayson 2010
// This is part of UltraBear1 distributed under the MIT
// Ian Finlayson 2010

#ifndef ULTRA1_HELP
#define ULTRA1_HELP

#include "GameState.h"

namespace Ultra1
{
	class HelpState : public Ultra1::GameState
	{
	private:
		Ultra1::App* app;

	public:
		HelpState( Ultra1::App* app )
		{
			this->app = app;
		}

		StateNumber Run( );
	};
}

#endif



