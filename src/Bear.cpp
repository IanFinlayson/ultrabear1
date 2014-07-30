// Bear.cpp
// Copyright Ian Finlayson 2010
// This is part of UltraBear1 distributed under the MIT

#include "Constants.h"
#include "Bear.h"
#include "SimFunctions.h"
#include "prefix.h"
#include <fstream>

Ultra1::Bear::Bear( Level* lev ) : Sim::Sprite( 0, HEIGHT - 40, 20, 40, 19 ), image( UBD_PREFIX "/images/bear.png", 0, 0, 255 )
{
	level = lev;

	// Get our flipped image...
	other = image.GetMirroredX( );

	AddAnimation( 0, 0, 3, true, image.image, 125, true, 1 );	   // Wlak right normal
	AddAnimation( 60, 0, 3, true, image.image, 125, true, 1 );   // Walk right w/ armor
	AddAnimation( 120, 0, 3, true, image.image, 125, true, 1 );   // Walk right w/ force field
	AddAnimation( 180, 0, 1, true, image.image, 125, false );  // Jump right normal
	AddAnimation( 200, 0, 1, true, image.image, 125, false );  // Jump right armor
	AddAnimation( 220, 0, 1, true, image.image, 125, false );  // Jump right force field
	AddAnimation( 240, 0, 1, true, image.image, 125, false );  // Fall right normal
	AddAnimation( 260, 0, 1, true, image.image, 125, false );  // Fall right armor
	AddAnimation( 280, 0, 1, true, image.image, 125, false );  // Fall right force field

	AddAnimation( 260, 0, 3, false, other.image, 125, true, 1 );  // Walk left normal
	AddAnimation( 200, 0, 3, false, other.image, 125, true, 1 );  // Walk left armor
	AddAnimation( 140, 0, 3, false, other.image, 125, true, 1 );  // Walk left force field
	AddAnimation( 120, 0, 1, true, other.image, 125, false );   // Jump left normal
	AddAnimation( 100, 0, 1, true, other.image, 125, false );   // Jump left armor
	AddAnimation( 80, 0, 1, true, other.image, 125, false );    // Jump left force field
	AddAnimation( 60, 0, 1, true, other.image, 125, false );	// Fall left normal
	AddAnimation( 40, 0, 1, true, other.image, 125, false );	// Fall left armor
	AddAnimation( 20, 0, 1, true, other.image, 125, false );	// Fall left force field
	
	AddAnimation( 300, 0, 1, true, image.image, 125, false );	// The 'dead' animation

	powers = NONE;
	direction = STILL;
	heading = RIGHT;

	SetAnimation( 0 );

	// We set Ultra Bear's position based on the height the level starts at...
	for( int i=0; i<NUM_BLOCKS_PER_COLUM; i++ )
	{
		if( level->GetBlock(i) )
		{
			SetPosition( 0, (i-2)*20 );
			break;
		}
	}

	position[0] = GetPosition( ).x;
	position[1] = GetPosition( ).y;

	bear_speed = NORMAL_BEAR_SPEED;

	jumping = false;
	falling = false;
	won = false;
	lost = false;
	dead = false;
	is_paused = false;
	pause_start = 0;
}

Ultra1::Bear::~Bear( )
{

}

void Ultra1::Bear::Die( )
{
	dead = true;
	velocity[0] = velocity[1] = 0.0f;
	
	// Turn off scrolling so enemies don't drift off the
	// screen after the bear dies!
	level->SetScroll( 0.0f );
}

void Ultra1::Bear::SetDirection( Direction dir )
{
	direction = dir;

	if( dir != STILL )
		heading = dir;
}

void Ultra1::Bear::Jump( Ultra1::App* app )
{
	if( falling || jumping )
		return;

	app->PlaySound( JUMP_NOISE );
	jumping = true;
	velocity[1] = -BEAR_JUMP_SPEED;
}

void Ultra1::Bear::Bounce( )
{
	jumping = true;
	velocity[1] = -100.0f;
}

void Ultra1::Bear::UnJump( )
{
	if( velocity[1] < 0.0f )
		velocity[1] *= .25f;

	jumping = false;
	falling = true;
}

void Ultra1::Bear::SetPause( bool pause )
{
	is_paused = pause;

	Sim::Sprite::SetPause( pause );
	
	if( pause )
		pause_start = SDL_GetTicks( );
	else
		time_got_force += ( SDL_GetTicks( ) - pause_start );
}

void Ultra1::Bear::Update( unsigned int elapsed_ms )
{
	// If wer'e dead, we just want to fall off the screen....
	if( dead )
	{
		velocity[1] += g*(elapsed_ms / 1000.0f);
		position[0] = position[0] + (velocity[0]*(elapsed_ms / 1000.0f));
		position[1] = position[1] + (velocity[1]*(elapsed_ms / 1000.0f));

		if( velocity[1] > MAX_FALL_SPEED )
			velocity[1] = MAX_FALL_SPEED;

		SetPosition( (int)position[0], (int)position[1] );

		// Call the super class method...
		Sim::Sprite::Update( );
		return;
	}

	// check if it's time to lose force
	if( powers == FORCE )
	{
		// If were paused, we want to keep the force longer...
		if( is_paused )
		{
			; // Do nothing
		}

		else if( (SDL_GetTicks( ) - time_got_force) > TIME_WITH_FORCE )
		{
			if( had_armor )
				powers = ARMOR;
			else
				powers = NONE;
		}
	}

	static SDL_Rect bear_pos = {0,0,20,40};

	if( direction == STILL )
	{
		Sim::Sprite::SetPause( true );
		velocity[0] = 0;

		level->SetScroll( 0.0f );
	}
	else	// We are moving...
	{
		Sim::Sprite::SetPause( false );

		// If the bear is moving the level right...
		if( (position[0] > RIGHT_SCROLL_BARRIOR) && (direction == RIGHT) )
		{
			// He reached the last screen-ful...
			if( level->LevelEnd( ) )
			{
				velocity[0] = bear_speed;
				level->SetScroll( 0.0f );
			}
			else
			{
				velocity[0] = 0.0f;
				level->SetScroll( bear_speed );
			}
		}
		// Bear is moving the screen left
		else if( (position[0] < LEFT_SCROLL_BARRIOR) && (direction == LEFT) )
		{
			// He reached the first screenful
			if( level->LevelStart( ) )
			{
				velocity[0] = -bear_speed;
				level->SetScroll( 0.0f );
			}
			else
			{
				level->SetScroll( -bear_speed );
				velocity[0] = 0.0f;
			}
		}
		// Bear is moving right, but not moving the screen...
		else if( direction == RIGHT )
		{
			velocity[0] = bear_speed;
			level->SetScroll( 0.0f );
		}
		// Bear is moving left but not moving the screen
		else if( direction == LEFT )
		{
			velocity[0] = -bear_speed;
			level->SetScroll( 0.0f );
		}
	}

	if( jumping )
		SetAnimation( (heading*9) + powers + 3 );
	else if( falling )
		SetAnimation( (heading*9) + powers + 6 );
	else
		SetAnimation( (heading*9) + powers );

	static float time;
	time = elapsed_ms / 1000.0f;

	// If we are jumping or falling, we fall...
	if( jumping || falling )
		velocity[1] += g*time;

	if( jumping && (velocity[1] > 0) )
	{
		jumping = false;
		falling = true;
	}

	position[0] = position[0] + velocity[0]*time;
	position[1] = position[1] + velocity[1]*time;

	if( velocity[1] > MAX_FALL_SPEED )
		velocity[1] = MAX_FALL_SPEED;

	bear_pos.x = (int)position[0];
	bear_pos.y = (int)position[1];

	CardinalDirection collide_dir = level->Collide( &bear_pos );
	
	if( collide_dir == NORTH )
	{
		// Ultra Bear is North of some blocks...
		falling = false;
		jumping = false;

		velocity[1] = 0.0f;
		position[1] = float(((int)position[1] / 20)*20) + 1;
	}
	else
	{
		if( !jumping )
			falling = true;

		if( collide_dir == EAST )
		{
			// Ultra Bear is to the East of some blocks...
			position[0] += 3;
			velocity[0] = 0.0f;

			direction = STILL;
		}
		else if( collide_dir == WEST )
		{
			// Ultra Bear is west of some blocks...
			position[0] -= 3;
			velocity[0] = 0.0f;

			direction = STILL;
		}
		else if( collide_dir == SOUTH )
		{
			// Ultra Bear is South of the blocks...
			position[1] += 2.0f;
			if( velocity[1] < 0 )
				velocity[1] = 0.0f;
			falling = true;
			jumping = false;
		}
		else if( collide_dir == DEAD )
		{
			// TODO: Subtract a life from UB
			lost = true;
		}
		else if( collide_dir == WON )
		{
			// TODO: Handle this logic...
			won = true;
		}
	}

	SetPosition( (int)position[0], (int)position[1] );

	// Call the super class method...
	Sim::Sprite::Update( );
}


void Ultra1::Bear::SetArmor( bool armor )
{
	if( powers == FORCE )
		had_armor = true;
	else
		powers = armor ? ARMOR : NONE;
}

void Ultra1::Bear::SetForce( )
{
	if( powers == FORCE )
		; // Do Nothing
	else if( powers == ARMOR )
		had_armor = true;
	else
		had_armor = false;

	powers = FORCE;

	time_got_force = SDL_GetTicks( );
}




