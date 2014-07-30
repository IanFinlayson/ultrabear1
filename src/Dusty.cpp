// Dusty.cpp
// Copyright Ian Finlayson 2010
// This is part of UltraBear1 distributed under the MIT

#include "prefix.h"
#include "Dusty.h"

Ultra1::Dusty::Dusty( Level* level ) : image( UBD_PREFIX "/images/dust.png", 0, 0, 255 ), sprite( 0, 0, 40, 40, 1 )
{
	sprite.AddAnimation( 0, 0, 3, true, image.image, 200, false, 2 );
    on = false;
	timer = 0;

	SDL_SetAlpha( image.image, SDL_RLEACCEL | SDL_SRCALPHA, 125 );

	this->level = level;

}

Ultra1::Dusty::~Dusty( )
{
}


void Ultra1::Dusty::AddDust( int x, int y )
{
	start = SDL_GetTicks( );
	timer = start;
	on = true;
	sprite.SetPosition( x, y );
	sprite.SetDx( 0.0f );
	sprite.Update( );
	sprite.SetPause( false );
}

void Ultra1::Dusty::SetPause( bool pause )
{
	sprite.SetPause( pause );
}

void Ultra1::Dusty::Update( unsigned int elapsed_ms )
{
	if( on )
	{
		timer += elapsed_ms;

		if( (timer - start) > 375 )
		{
			sprite.SetPause( true );
			on = false;
		}

		sprite.SetDx( -level->GetScrollSpeed( ) );

		sprite.Update( );
	}
}

void Ultra1::Dusty::Draw( SDL_Surface* screen )
{
	if( on )
		sprite.Draw( screen );

}




