// EntityList.h
// Copyright Ian Finlayson 2010
// This is part of UltraBear1 distributed under the MIT

// Encapsulates all the entites in a level at one time.

#include "Pickups.h"
#include "Enemies.h"
#include "Bosses.h"
#include "Dusty.h"

#include "Level.h"

namespace Ultra1
{
	class EntityList
	{
	private:
		Entity** entities;
		int num_entities;
		Level* level;

	public:
		EntityList( Level* the_level );
		~EntityList( );

		void Update( unsigned int elapsed_ms );
		void Draw( SDL_Surface* screen );
		void SetPause( bool pause );

		// Returns where UB hit entity (or NO_COLLIDE or GOT_COIN...)
		CardinalDirection Collide( SDL_Rect* bear_pos, Dusty* dust, bool bear_force );
	};
}



