// Entity.h
// Copyright Ian Finlayson 2010
// This is part of UltraBear1 distributed under the MIT
// Base class for all the entities


#ifndef ENTITY_H
#define ENTITY_H

#include "SimSprite.h"
#include "SimVector.h"

#include "Level.h"

namespace Ultra1
{
	class Entity : public Sim::Sprite
	{
	protected:
		Sim::Vector<float, 2> position;
		Sim::Vector<float, 2> velocity;
		Level* level;
		bool in_sight;
		bool dead;
		bool jumping;
		bool falling;
		bool on_ground;
		bool pickup;
		bool encountered;

		Direction heading;		// Either LEFT or RIGHT
		int width, height;

	public:
		Entity( Level* the_level, int x, int y, int w, int h, int num_anims );
		virtual ~Entity( ){ }

		virtual void Update( float elapsed_ms );

		// Entities should call *one* of these before calling Update
		void WalkBasic( float speed );
		void WalkBouncy( float walk_speed, float jump_speed );

		void SetThePosition( int x, int y );
		void Draw( SDL_Surface* screen );

		bool IsVisible( ){ return (in_sight && !dead); }
		void Kill( ){ dead = true; }
	};
}

#endif



