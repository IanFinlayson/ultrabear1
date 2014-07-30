// Story.h
// Copyright Ian Finlayson 2010
// This is part of UltraBear1 distributed under the MIT
// Story Screen for Ultra Bear

#ifndef ULTRA1_STORY
#define ULTRA1_STORY

#include "GameState.h"

namespace Ultra1
{
	class StoryState : public Ultra1::GameState
	{
	private:
		Ultra1::App* app;

	public:
		StoryState( Ultra1::App* app )
		{
			this->app = app;
		}

		StateNumber Run( );
	};
}

#endif



