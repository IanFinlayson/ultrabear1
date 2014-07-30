// Enemies.cpp
// Copyright Ian Finlayson 2010
// This is part of UltraBear1 distributed under the MIT
// Implements our enemy classes

#include "Enemies.h"
#include "prefix.h"

// SnowMan Class!
Sim::Image* Ultra1::SnowMan::image = NULL;
Sim::Image* Ultra1::SnowMan::other = NULL;
Ultra1::SnowMan::SnowMan( Level* the_level ) : Entity( the_level, 0, 0, 30, 40, 2 )
{
	if( !image )
	{
		image = new Sim::Image( UBD_PREFIX "/images/snowman.png", 0, 0, 255 );
		other = new Sim::Image( image->GetMirroredX( ) );
	}

	AddAnimation( 0, 0, 3, true, image->image, 125, true, 1 );
	AddAnimation( 0, 0, 3, false, other->image, 125, true, 1 );
}
Ultra1::SnowMan::~SnowMan( )
{
	if( image )
	{
		delete image;
		image = NULL;
	}
	if( other )
	{
		delete other;
		other = NULL;
	}
}
void Ultra1::SnowMan::Update( float elapsed_ms )
{
	WalkBouncy( 100.0f, -200.0f );
	Entity::Update( elapsed_ms );
}


// Bird class!
Sim::Image* Ultra1::Bird::image = NULL;
Ultra1::Bird::Bird( Level* the_level ) : Entity( the_level, 0, 0, 40, 21, 1 )
{
	if( !image )
	{
		image = new Sim::Image( UBD_PREFIX "/images/bird.png", 0, 0, 255 );
	}

	AddAnimation( 0, 0, 3, true, image->image, 125, true );
	velocity[0] = -200.0f;
}
Ultra1::Bird::~Bird( )
{
	if( image )
	{
		delete image;
		image = NULL;
	}
}
void Ultra1::Bird::Update( float elapsed_ms )
{
	// The bird does not use the normal update method...
	if( dead ) return;

	if( ((position[0] + GetPosition().w) > -30) && (position[0] < 830) )
		in_sight = true;
	else if( (position[0] + GetPosition().w <= -30) )
		dead = true;
	else
		in_sight = false;

	if( in_sight )
	{
		// update position based off intrinsic veloctiy
		position[0] = position[0] + velocity[0]*elapsed_ms;
		position[1] = position[1] + velocity[1]*elapsed_ms;

		// update position due to scrolling effect
		position[0] = position[0] + -level->GetScrollSpeed( )*elapsed_ms;
		SetPosition( (int)position[0], (int)position[1] );
		Sim::Sprite::Update( );
	}
	else
	{
		// update position due to scrolling effect
		position[0] = position[0] + -level->GetScrollSpeed( )*elapsed_ms;
	}
}

// Beaver class!
Sim::Image* Ultra1::Beaver::image = NULL;
Sim::Image* Ultra1::Beaver::other = NULL;
Ultra1::Beaver::Beaver( Level* the_level ) : Entity( the_level, 0, 0, 38, 42, 2 )
{
	if( !image )
	{
		image = new Sim::Image( UBD_PREFIX "/images/beaver.png", 0, 0, 255 );
		other = new Sim::Image( image->GetMirroredX( ) );
	}

	AddAnimation( 0, 0, 3, true, image->image, 125, true, 1 );
	AddAnimation( 0, 0, 3, false, other->image, 125, true, 1 );
}
Ultra1::Beaver::~Beaver( )
{
	if( image )
	{
		delete image;
		image = NULL;
	}
	if( other )
	{
		delete other;
		other = NULL;
	}
}
void Ultra1::Beaver::Update( float elapsed_ms )
{
	WalkBouncy( 150.0f, -30.0f );
	Entity::Update( elapsed_ms );
}

// Moose class!
Sim::Image* Ultra1::Moose::image = NULL;
Sim::Image* Ultra1::Moose::other = NULL;
Ultra1::Moose::Moose( Level* the_level ) : Entity( the_level, 0, 0, 55, 67, 2 )
{
	if( !image )
	{
		image = new Sim::Image( UBD_PREFIX "/images/moose.png", 0, 0, 255 );
		other = new Sim::Image( image->GetMirroredX( ) );
	}

	AddAnimation( 0, 0, 3, true, image->image, 125, true, 1 );
	AddAnimation( 0, 0, 3, false, other->image, 125, true, 1 );
}
Ultra1::Moose::~Moose( )
{
	if( image )
	{
		delete image;
		image = NULL;
	}
	if( other )
	{
		delete other;
		other = NULL;
	}
}
void Ultra1::Moose::Update( float elapsed_ms )
{
	WalkBasic( 200.0f );
	Entity::Update( elapsed_ms );
}
 
// Raccoon class!
Sim::Image* Ultra1::Raccoon::image = NULL;
Sim::Image* Ultra1::Raccoon::other = NULL;
Ultra1::Raccoon::Raccoon( Level* the_level ) : Entity( the_level, 0, 0, 38, 42, 2 )
{
	if( !image )
	{
		image = new Sim::Image( UBD_PREFIX "/images/raccoon.png", 0, 0, 255 );
		other = new Sim::Image( image->GetMirroredX( ) );
	}

	AddAnimation( 0, 0, 2, true, image->image, 125, true, 1 );
	AddAnimation( 0, 0, 2, false, other->image, 125, true, 1 );
}
Ultra1::Raccoon::~Raccoon( )
{
	if( image )
	{
		delete image;
		image = NULL;
	}
	if( other )
	{
		delete other;
		other = NULL;
	}
}
void Ultra1::Raccoon::Update( float elapsed_ms )
{
	WalkBouncy( 165.0f, -70.0f );
	Entity::Update( elapsed_ms );
}


// Possom class!
Sim::Image* Ultra1::Possom::image = NULL;
Sim::Image* Ultra1::Possom::other = NULL;
Ultra1::Possom::Possom( Level* the_level ) : Entity( the_level, 0, 0, 35, 40, 2 )
{
	if( !image )
	{
		image = new Sim::Image( UBD_PREFIX "/images/possom.png", 0, 0, 255 );
		other = new Sim::Image( image->GetMirroredX( ) );
	}

	AddAnimation( 0, 0, 2, true, image->image, 125, true, 1 );
	AddAnimation( 0, 0, 2, false, other->image, 125, true, 1 );
}
Ultra1::Possom::~Possom( )
{
	if( image )
	{
		delete image;
		image = NULL;
	}
	if( other )
	{
		delete other;
		other = NULL;
	}
}
void Ultra1::Possom::Update( float elapsed_ms )
{
	WalkBasic( 200.0f );
	Entity::Update( elapsed_ms );
}



// Snake class!
Sim::Image* Ultra1::Snake::image = NULL;
Sim::Image* Ultra1::Snake::other = NULL;
Ultra1::Snake::Snake( Level* the_level ) : Entity( the_level, 0, 0, 40, 40, 2 )
{
	if( !image )
	{
		image = new Sim::Image( UBD_PREFIX "/images/snake.png", 0, 0, 255 );
		other = new Sim::Image( image->GetMirroredX( ) );
	}

	AddAnimation( 0, 0, 2, true, image->image, 125, true, 1 );
	AddAnimation( 0, 0, 2, false, other->image, 125, true, 1 );
}
Ultra1::Snake::~Snake( )
{
	if( image )
	{
		delete image;
		image = NULL;
	}
	if( other )
	{
		delete other;
		other = NULL;
	}
}
void Ultra1::Snake::Update( float elapsed_ms )
{
	WalkBouncy( 175.0f, -40.0f );
	Entity::Update( elapsed_ms );
}


// Chihuahua class
Sim::Image* Ultra1::Chihuahua::image = NULL;
Sim::Image* Ultra1::Chihuahua::other = NULL;
Ultra1::Chihuahua::Chihuahua( Level* the_level ) : Entity( the_level, 0, 0, 24, 40, 2 )
{
	if( !image )
	{
		image = new Sim::Image( UBD_PREFIX "/images/chihuahua.png", 0, 0, 255 );
		other = new Sim::Image( image->GetMirroredX( ) );
	}

	AddAnimation( 0, 0, 2, true, image->image, 125, true, 1 );
	AddAnimation( 0, 0, 2, false, other->image, 125, true, 1 );
}
Ultra1::Chihuahua::~Chihuahua( )
{
	if( image )
	{
		delete image;
		image = NULL;
	}
	if( other )
	{
		delete other;
		other = NULL;
	}
}
void Ultra1::Chihuahua::Update( float elapsed_ms )
{
	WalkBasic( 180.0f );
	Entity::Update( elapsed_ms );
}

// Lemming class
Sim::Image* Ultra1::Lemming::image = NULL;
Sim::Image* Ultra1::Lemming::other = NULL;
Ultra1::Lemming::Lemming( Level* the_level ) : Entity( the_level, 0, 0, 29, 40, 2 )
{
	if( !image )
	{
		image = new Sim::Image( UBD_PREFIX "/images/lemming.png", 0, 0, 255 );
		other = new Sim::Image( image->GetMirroredX( ) );
	}

	AddAnimation( 0, 0, 2, true, image->image, 125, true, 1 );
	AddAnimation( 0, 0, 2, false, other->image, 125, true, 1 );
}
Ultra1::Lemming::~Lemming( )
{
	if( image )
	{
		delete image;
		image = NULL;
	}
	if( other )
	{
		delete other;
		other = NULL;
	}
}
void Ultra1::Lemming::Update( float elapsed_ms )
{
	WalkBouncy( 200.0f, -30.0f );
	Entity::Update( elapsed_ms );
}



// Goat class
Sim::Image* Ultra1::Goat::image = NULL;
Sim::Image* Ultra1::Goat::other = NULL;
Ultra1::Goat::Goat( Level* the_level ) : Entity( the_level, 0, 0, 55, 65, 2 )
{
	if( !image )
	{
		image = new Sim::Image( UBD_PREFIX "/images/goat.png", 0, 0, 255 );
		other = new Sim::Image( image->GetMirroredX( ) );
	}

	AddAnimation( 0, 0, 3, true, image->image, 125, true, 1 );
	AddAnimation( 0, 0, 3, false, other->image, 125, true, 1 );
}
Ultra1::Goat::~Goat( )
{
	if( image )
	{
		delete image;
		image = NULL;
	}
	if( other )
	{
		delete other;
		other = NULL;
	}
}
void Ultra1::Goat::Update( float elapsed_ms )
{
	WalkBasic( 180.0f );
	Entity::Update( elapsed_ms );
}

// Penguin class
Sim::Image* Ultra1::Penguin::image = NULL;
Sim::Image* Ultra1::Penguin::other = NULL;
Ultra1::Penguin::Penguin( Level* the_level ) : Entity( the_level, 0, 0, 24, 40, 2 )
{
	if( !image )
	{
		image = new Sim::Image( UBD_PREFIX "/images/penguin.png", 0, 0, 255 );
		other = new Sim::Image( image->GetMirroredX( ) );
	}

	AddAnimation( 0, 0, 3, true, image->image, 125, true, 1 );
	AddAnimation( 0, 0, 3, false, other->image, 125, true, 1 );
}
Ultra1::Penguin::~Penguin( )
{
	if( image )
	{
		delete image;
		image = NULL;
	}
	if( other )
	{
		delete other;
		other = NULL;
	}
}
void Ultra1::Penguin::Update( float elapsed_ms )
{
	WalkBouncy( 250.0f, -50.0f );
	Entity::Update( elapsed_ms );
}





// FireBall class
Sim::Image* Ultra1::FireBall::image = NULL;
Sim::Image* Ultra1::FireBall::other = NULL;

Ultra1::FireBall::FireBall( Level* the_level ) : Entity( the_level, 0, 0, 20, 30, 2 )
{
	if( !image )
	{
		image = new Sim::Image( UBD_PREFIX "/images/fireball.png", 0, 0, 255 );
		other = new Sim::Image( image->GetMirroredY( ) );
	}

	AddAnimation( 0, 0, 3, true, image->image, 125, true, 1 );
	AddAnimation( 0, 0, 3, true, other->image, 125, true, 1 );

	velocity[1] = -200;
}
Ultra1::FireBall::~FireBall( )
{
	if( image )
	{
		delete image;
		image = NULL;
	}
	if( other )
	{
		delete other;
		other = NULL;
	}
}


float absf(float x)
{
	if( x <= 0)
		return -x;
	else
		return x;
}

void Ultra1::FireBall::Update( float elapsed_ms )
{
	// The bird does not use the normal update method...
	if( dead ) return;

	if( ((position[0] + GetPosition().w) > -30) && (position[0] < 830) )
		in_sight = true;
	else
		in_sight = false;


	// update position based off intrinsic veloctiy
	position[0] = position[0] + velocity[0]*elapsed_ms;
	position[1] = position[1] + velocity[1]*elapsed_ms;

	// update position due to scrolling effect
	position[0] = position[0] + -level->GetScrollSpeed( )*elapsed_ms;

	// Create up/down behaviour
	if( position[1] < 300 )
	{
		velocity[1] = absf(velocity[1]);
		SetAnimation( 1 );
	}
	else if( position[1] > 650 )
	{
		velocity[1] = -absf(velocity[1]);
		SetAnimation( 0 );
	}

	SetPosition( (int)position[0], (int)position[1] );
	
	if( in_sight )
	{
		Sim::Sprite::Update( );
	}
}


