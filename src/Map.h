// Map.h
// Copyright Ian Finlayson 2010
// This is part of UltraBear1 distributed under the MIT
// Represents a Map in the map screen from
// which UB can select levels

#ifndef ULTRA1_MAP
#define ULTRA1_MAP

#include <SDL/SDL.h>
#include "SimImage.h"
#include "SimSprite.h"

#include "Constants.h"

namespace Ultra1
{
	class Map
	{
	private:
		Sim::Image* image;	// The image the map has

		Sim::Sprite level_dot;	// The level markers sprites
		Sim::Sprite level_lock;

		Sim::Image dot_image;	// The level markers images
		Sim::Image lock_image;
		
		int map_number;
		int current_next_beat;

	public:
		struct LevelInfo
		{
			int x, y;				// Coords of the level
			CardinalDirection next;	// Direction player must go to get to next level
		};

		LevelInfo info[7];		// There are 5 levels per map...Level 0 is the "start" of the map...Level 6 is the "end"

		Map( int map_number, int current_next_beat );
		~Map( );
		
		void Update( unsigned int elapsed_ms );
		void Draw( SDL_Surface* screen );
	};
}

#endif



