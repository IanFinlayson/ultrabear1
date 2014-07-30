// Bosses.cpp
// Copyright Ian Finlayson 2010
// This is part of UltraBear1 distributed under the MIT

#include "prefix.h"
#include "Bosses.h"



// WalrusBoss class
Sim::Image* Ultra1::WalrusBoss::image = NULL;
Ultra1::WalrusBoss::WalrusBoss( Level* the_level ) : Entity( the_level, 0, 0, 100, 69, 1 )
{
	if( !image )
	{
		image = new Sim::Image( UBD_PREFIX "/images/walrus.png", 0, 0, 255 );
	}

	AddAnimation( 0, 0, 2, true, image->image, 125, true );
}
Ultra1::WalrusBoss::~WalrusBoss( )
{
	if( image )
	{
		delete image;
		image = NULL;
	}
}
void Ultra1::WalrusBoss::Update( float elapsed_ms )
{
	if( dead ) return;

	if( ((position[0] + GetPosition().w) > -30) && (position[0] < 830) )
		in_sight = true;
	else
		in_sight = false;

	if( in_sight )
	{
		// update position based off intrinsic veloctiy
		position[0] = position[0] + velocity[0]*elapsed_ms;
		position[1] = position[1] + velocity[1]*elapsed_ms;

		// Update velocity due to gravity...
		velocity[1] += (g*3)*elapsed_ms;

		// update position due to scrolling effect
		position[0] = position[0] + -level->GetScrollSpeed( )*elapsed_ms;
		
		if( position[1] > 380 )	// Keep em from falling!
			velocity[1] = -250.0f;

		SetPosition( (int)position[0], (int)position[1] );
		Sim::Sprite::Update( );
	}
	else
	{
		// update position due to scrolling effect
		position[0] = position[0] + -level->GetScrollSpeed( )*elapsed_ms;
	}
}











// BeaverBoss class
Sim::Image* Ultra1::BeaverBoss::image = NULL;
Ultra1::BeaverBoss::BeaverBoss( Level* the_level ) : Entity( the_level, 0, 0, 100, 58, 1 )
{
	if( !image )
	{
		image = new Sim::Image( UBD_PREFIX "/images/bigbeaver.png", 0, 0, 255 );
	}

	AddAnimation( 0, 0, 3, true, image->image, 125, true );
}
Ultra1::BeaverBoss::~BeaverBoss( )
{
	if( image )
	{
		delete image;
		image = NULL;
	}
}
void Ultra1::BeaverBoss::Update( float elapsed_ms )
{
	if( dead ) return;

	if( ((position[0] + GetPosition().w) > -30) && (position[0] < 830) )
		in_sight = true;
	else
		in_sight = false;

	if( in_sight )
	{
		// update position based off intrinsic veloctiy
		position[0] = position[0] + velocity[0]*elapsed_ms;
		position[1] = position[1] + velocity[1]*elapsed_ms;
		
		// Update velocity due to gravity...
		velocity[1] += (g*3)*elapsed_ms;

		// update position due to scrolling effect
		position[0] = position[0] + -level->GetScrollSpeed( )*elapsed_ms;
		
		if( position[1] > 445 )	// Keep em from falling!
			velocity[1] = -200.0f;

		SetPosition( (int)position[0], (int)position[1] );
		Sim::Sprite::Update( );
	}
	else
	{
		// update position due to scrolling effect
		position[0] = position[0] + -level->GetScrollSpeed( )*elapsed_ms;
	}
}











// PossomBoss class (ACTUALLY, NOW IT'S A GATOR!!!)
Sim::Image* Ultra1::PossomBoss::image = NULL;
Ultra1::PossomBoss::PossomBoss( Level* the_level ) : Entity( the_level, 0, 0, 96, 54, 1 )
{
	if( !image )
	{
		image = new Sim::Image( UBD_PREFIX "/images/gator.png", 0, 0, 255 );
	}

	AddAnimation( 0, 0, 3, true, image->image, 125, true );
}
Ultra1::PossomBoss::~PossomBoss( )
{
	if( image )
	{
		delete image;
		image = NULL;
	}
}
void Ultra1::PossomBoss::Update( float elapsed_ms )
{
	if( dead ) return;

	if( ((position[0] + GetPosition().w) > -30) && (position[0] < 830) )
		in_sight = true;
	else
		in_sight = false;

	if( in_sight )
	{
		// update position based off intrinsic veloctiy
		position[0] = position[0] + velocity[0]*elapsed_ms;
		position[1] = position[1] + velocity[1]*elapsed_ms;

		// Update velocity due to gravity...
		velocity[1] += (g*3)*elapsed_ms;

		// update position due to scrolling effect
		position[0] = position[0] + -level->GetScrollSpeed( )*elapsed_ms;
		
		if( position[1] > 90 )	// Keep em from falling!
			velocity[1] = -200.0f;

		SetPosition( (int)position[0], (int)position[1] );
		Sim::Sprite::Update( );
	}
	else
	{
		// update position due to scrolling effect
		position[0] = position[0] + -level->GetScrollSpeed( )*elapsed_ms;
	}
}











// ChihuahuaBoss class
Sim::Image* Ultra1::ChihuahuaBoss::image = NULL;
Ultra1::ChihuahuaBoss::ChihuahuaBoss( Level* the_level ) : Entity( the_level, 0, 0, 88, 69, 1 )
{
	if( !image )
	{
		image = new Sim::Image( UBD_PREFIX "/images/chihuahuaboss.png", 0, 0, 255 );
	}

	AddAnimation( 0, 0, 2, true, image->image, 100, true );
}
Ultra1::ChihuahuaBoss::~ChihuahuaBoss( )
{
	if( image )
	{
		delete image;
		image = NULL;
	}
}
void Ultra1::ChihuahuaBoss::Update( float elapsed_ms )
{
	static bool first = true;
	if( first )
	{
		position[0] += 80;
		first = false;
	}

	if( dead ) return;

	if( ((position[0] + GetPosition().w) > -30) && (position[0] < 830) )
		in_sight = true;
	else
		in_sight = false;

	static float timer = 2.0f;
	static bool dir = true;

	if( in_sight )
	{
		timer -= elapsed_ms;
		if( timer < 0 )
		{
			dir = !dir;
			timer = 2.0f;
		}

		if( dir )
			velocity[0] = -100.0f;
		else
			velocity[0] = 100.0f;


		// update position based off intrinsic veloctiy
		position[0] = position[0] + velocity[0]*elapsed_ms;
		position[1] = position[1] + velocity[1]*elapsed_ms;
		
		// Update velocity due to gravity...
		velocity[1] += (g*3)*elapsed_ms;

		// update position due to scrolling effect
		position[0] = position[0] + -level->GetScrollSpeed( )*elapsed_ms;
		
		if( position[1] > 420 )	// Keep em from falling!
			velocity[1] = -300.0f;

		SetPosition( (int)position[0], (int)position[1] );
		Sim::Sprite::Update( );
	}
	else
	{
		// update position due to scrolling effect
		position[0] = position[0] + -level->GetScrollSpeed( )*elapsed_ms;
	}
}










// ChupacabraBoss class
Sim::Image* Ultra1::ChupacabraBoss::image = NULL;
Ultra1::ChupacabraBoss::ChupacabraBoss( Level* the_level ) : Entity( the_level, 0, 0, 50, 75, 1 )
{
	if( !image )
	{
		image = new Sim::Image( UBD_PREFIX "/images/chupa.png", 0, 0, 255 );
	}

	AddAnimation( 0, 0, 3, true, image->image, 125, true );
}
Ultra1::ChupacabraBoss::~ChupacabraBoss( )
{
	if( image )
	{
		delete image;
		image = NULL;
	}
}
void Ultra1::ChupacabraBoss::Update( float elapsed_ms )
{
	static bool first = true;
	if( first )
	{
		position[0] += 70;
		first = false;
	}

	if( dead ) return;

	if( ((position[0] + GetPosition().w) > -30) && (position[0] < 830) )
		in_sight = true;
	else
		in_sight = false;

	static float timer = 1.5f;
	static bool dir = true;

	if( in_sight )
	{
		timer -= elapsed_ms;
		if( timer < 0 )
		{
			dir = !dir;
			timer = 1.5f;
		}

		if( dir )
			velocity[0] = -150.0f;
		else
			velocity[0] = 150.0f;


		// update position based off intrinsic veloctiy
		position[0] = position[0] + velocity[0]*elapsed_ms;
		position[1] = position[1] + velocity[1]*elapsed_ms;
		
		// Update velocity due to gravity...
		velocity[1] += (g*3)*elapsed_ms;

		// update position due to scrolling effect
		position[0] = position[0] + -level->GetScrollSpeed( )*elapsed_ms;
		
		if( position[1] > 350 )	// Keep em from falling!
			velocity[1] = -300.0f;

		SetPosition( (int)position[0], (int)position[1] );
		Sim::Sprite::Update( );
	}
	else
	{
		// update position due to scrolling effect
		position[0] = position[0] + -level->GetScrollSpeed( )*elapsed_ms;
	}
}






// PenguinBoss class
Sim::Image* Ultra1::PenguinBoss::image = NULL;
Ultra1::PenguinBoss::PenguinBoss( Level* the_level ) : Entity( the_level, 0, 0, 45, 85, 1 )
{
	if( !image )
	{
		image = new Sim::Image( UBD_PREFIX "/images/penguinking.png", 0, 0, 255 );
	}

	AddAnimation( 0, 0, 3, true, image->image, 125, true );
}
Ultra1::PenguinBoss::~PenguinBoss( )
{
	if( image )
	{
		delete image;
		image = NULL;
	}
}
void Ultra1::PenguinBoss::Update( float elapsed_ms )
{
	static bool first = true;
	if( first )
	{
		position[0] += 60;
		first = false;
	}

	if( dead ) return;

	if( ((position[0] + GetPosition().w) > -30) && (position[0] < 830) )
		in_sight = true;
	else
		in_sight = false;

	static float timer = 2.5f;
	static bool dir = true;

	if( in_sight )
	{
		timer -= elapsed_ms;
		if( timer < 0 )
		{
			dir = !dir;
			timer = 2.5f;
		}

		if( dir )
			velocity[0] = -250.0f;
		else
			velocity[0] = 250.0f;


		// update position based off intrinsic veloctiy
		position[0] = position[0] + velocity[0]*elapsed_ms;
		position[1] = position[1] + velocity[1]*elapsed_ms;
		
		// Update velocity due to gravity...
		velocity[1] += (g*3)*elapsed_ms;

		// update position due to scrolling effect
		position[0] = position[0] + -level->GetScrollSpeed( )*elapsed_ms;
		
		if( position[1] > 420 )	// Keep em from falling!
			velocity[1] = -300.0f;

		SetPosition( (int)position[0], (int)position[1] );
		Sim::Sprite::Update( );
	}
	else
	{
		// update position due to scrolling effect
		position[0] = position[0] + -level->GetScrollSpeed( )*elapsed_ms;
	}
}




