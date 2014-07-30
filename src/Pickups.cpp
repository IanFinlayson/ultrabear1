// Pickups.cpp
// Copyright Ian Finlayson 2010
// This is part of UltraBear1 distributed under the MIT
// Implements the pickups

#include "Pickups.h"
#include "prefix.h"

// Coin class
Sim::Image* Ultra1::Coin::image = NULL;
Ultra1::Coin::Coin( Level* the_level ) : Entity( the_level, 0, 0, 20, 20, 1 )
{
	if( !image )
	{
		image = new Sim::Image( UBD_PREFIX "/images/coin.png", 0, 0, 255 );
	}

	AddAnimation( 0, 0, 3, true, image->image, 125, true );
	pickup = true;
}
Ultra1::Coin::~Coin( )
{
	if( image )
	{
		delete image;
		image = NULL;
	}
}
void Ultra1::Coin::Update( float elapsed_ms )
{
	// update position due to scrolling effect
	position[0] = position[0] + -level->GetScrollSpeed( )*elapsed_ms;
	SetPosition( (int)position[0], (int)position[1] );
	Sim::Sprite::Update( );
}





// Armor class
Sim::Image* Ultra1::Armor::image = NULL;
Ultra1::Armor::Armor( Level* the_level ) : Entity( the_level, 0, 0, 20, 20, 1 )
{
	if( !image )
	{
		image = new Sim::Image( UBD_PREFIX "/images/armor.png", 0, 0, 255 );
	}

	AddAnimation( 0, 0, 2, true, image->image, 125, true );
	pickup = true;
}
Ultra1::Armor::~Armor( )
{
	if( image )
	{
		delete image;
		image = NULL;
	}
}
void Ultra1::Armor::Update( float elapsed_ms )
{
	// update position due to scrolling effect
	position[0] = position[0] + -level->GetScrollSpeed( )*elapsed_ms;
	SetPosition( (int)position[0], (int)position[1] );
	Sim::Sprite::Update( );
}




// Force class
Sim::Image* Ultra1::Force::image = NULL;
Ultra1::Force::Force( Level* the_level ) : Entity( the_level, 0, 0, 20, 20, 1 )
{
	if( !image )
	{
		image = new Sim::Image( UBD_PREFIX "/images/force.png", 0, 0, 255 );
	}

	AddAnimation( 0, 0, 2, true, image->image, 125, true );
	pickup = true;
}
Ultra1::Force::~Force( )
{
	if( image )
	{
		delete image;
		image = NULL;
	}
}
void Ultra1::Force::Update( float elapsed_ms )
{
	// update position due to scrolling effect
	position[0] = position[0] + -level->GetScrollSpeed( )*elapsed_ms;
	SetPosition( (int)position[0], (int)position[1] );
	Sim::Sprite::Update( );
}






// ExtraLife class
Sim::Image* Ultra1::ExtraLife::image = NULL;
Ultra1::ExtraLife::ExtraLife( Level* the_level ) : Entity( the_level, 0, 0, 20, 20, 1 )
{
	if( !image )
	{
		image = new Sim::Image( UBD_PREFIX "/images/extralife.png", 0, 0, 255 );
	}

	AddAnimation( 0, 0, 2, true, image->image, 125, true );
	pickup = true;
}
Ultra1::ExtraLife::~ExtraLife( )
{
	if( image )
	{
		delete image;
		image = NULL;
	}
}
void Ultra1::ExtraLife::Update( float elapsed_ms )
{
	// update position due to scrolling effect
	position[0] = position[0] + -level->GetScrollSpeed( )*elapsed_ms;
	SetPosition( (int)position[0], (int)position[1] );
	Sim::Sprite::Update( );
}



