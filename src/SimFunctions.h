//SimFunctions.h
// Copyright Ian Finlayson 2010

#ifndef SIM_FUNCTIONS
#define SIM_FUNCTIONS

#include <vector>
#include <string>
#include <SDL/SDL.h>

namespace Sim
{
	// Bounding box collision detections...
	// Returns the direction from which a hits b
	// NO COLLISION  -1
	// EAST    0
	// NORTH   1
	// WEST    2
	// SOUTH   3
	// so if it returns 0, a is to the right of b
	int Collide( SDL_Rect* a, SDL_Rect* b, int error=0 );

}

#endif



