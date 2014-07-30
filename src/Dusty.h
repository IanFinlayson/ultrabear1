// Dusty.h
// Copyright Ian Finlayson 2010
// This is part of UltraBear1 distributed under the MIT
// Dusty generates the dust clouds when an entity dies

#ifndef DUSTY_H
#define DUSTY_H

#include "SimImage.h"
#include "SimSprite.h"

#include "Level.h"

namespace Ultra1
{
	class Dusty
	{
	private:
		Sim::Image image;
		Sim::Sprite sprite;

		bool on;
		unsigned int start;
		unsigned int timer;
		Level* level;

	public:
		Dusty( Level* level );
		~Dusty( );

		void AddDust( int x, int y );
		void Update( unsigned int elapsed_ms );
		void Draw( SDL_Surface* screen );
		void SetPause( bool pause );
	};
}

#endif



