// GameState.h
// Copyright Ian Finlayson 2010
// This is part of UltraBear1 distributed under the MIT
// Represents a virtual state the game could be in
// eg Game Intro Menu etc...

#ifndef ULTRA1_STATE
#define ULTRA1_STATE

namespace Ultra1
{
	class GameState
	{
	public:
		// Returns the next game state to go to...
		virtual StateNumber Run( ) = 0;
	};
}

#endif



