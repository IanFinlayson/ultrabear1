// Entity.cpp
// Copyright Ian Finlayson 2010
// This is part of UltraBear1 distributed under the MIT

#include "Entity.h"

Ultra1::Entity::Entity( Level* the_level, int x, int y, int w, int h, int num_anims ) : Sim::Sprite( x, y, w, h, num_anims )
{
	level = the_level;
	in_sight = false;

	width = w;
	height = h;

	in_sight = true;
	encountered = false;

	heading = LEFT;
	pickup = false;

	jumping = falling = dead = on_ground = false;
}

void Ultra1::Entity::SetThePosition( int x, int y )
{
	position[0] = static_cast<float>(x);
	position[1] = static_cast<float>(y);
}

void Ultra1::Entity::Draw( SDL_Surface* screen )
{
	if( in_sight && !dead )
		Sim::Sprite::Draw( screen );
}

// Walks forward and falls off edges
// Turns around when it hits somthing
void Ultra1::Entity::WalkBasic( float speed )
{
	if( heading == LEFT )
		velocity[0] = -speed;
	else
		velocity[0] = speed;
}

// Walks bouncing with every step
void Ultra1::Entity::WalkBouncy( float walk_speed, float jump_speed )
{
	if( heading == LEFT )
		velocity[0] = -walk_speed;
	else
		velocity[0] = walk_speed;

	if( on_ground )
	{
		jumping = true;
		velocity[1] = jump_speed;
	}
}


void Ultra1::Entity::Update( float elapsed_ms )
{
	if( dead ) return;

	if( ( (position[0] + GetPosition().w) > -30 ) && ( position[0] < 830 ) )
	{
		in_sight = true;
		encountered = true;
	}
	else
		in_sight = false;

	// If they fall off the edge...
	if( position[1] > 620 )
		dead = true;

	if( heading == LEFT )
		SetAnimation(0);
	else
		SetAnimation(1);

	if( (position[0] + level->GetTileX( )) < 0 )
	{
		// Entity is off the level...
		position[0] += 3;
		heading = RIGHT;
	}

	if( encountered )
	{
		if( GetNumAnims( ) == 2 )
		{
			int dir = heading ? 0 : 1;
			SetAnimation( dir );
		}

		// If we are jumping or falling, we fall...
		if( jumping || falling )
			velocity[1] += g*elapsed_ms;

		if( jumping && (velocity[1] > 0) )
		{
			jumping = false;
			falling = true;
		}

		if( pickup )
		{
			// We do not want the pickups to fall!
			velocity[0] = velocity[1] = 0.0f;
		}

		// update position based off intrinsic veloctiy
		position[0] = position[0] + velocity[0]*elapsed_ms;
		position[1] = position[1] + velocity[1]*elapsed_ms;

		// update position due to scrolling effect
		position[0] = position[0] + -level->GetScrollSpeed( )*elapsed_ms;

		SDL_Rect place;
		place.h = height;
		place.w = width;
		place.x = (int)position[0];
		place.y = (int)position[1];

		CardinalDirection collide_dir = level->Collide( &place, false );

		if( collide_dir == NORTH )
		{
			// Entity is North of some blocks...
			falling = false;
			jumping = false;

			velocity[1] = 0.0f;
			position[1] = float(((int)position[1] / 20)*20) + 1;
			on_ground = true;
		}
		else
		{
			if( !jumping )
				falling = true;
			
            on_ground = false;

			if( collide_dir == EAST )
			{
				// Entity is to the East of some blocks...
				position[0] += 3;
				heading = RIGHT;
			}
			else if( collide_dir == WEST )
			{
				// Entity is west of some blocks...
				position[0] -= 3;
				heading = LEFT;
			}
			else if( collide_dir == SOUTH )
			{
				// Entity is South of the blocks...
				position[1] += 2.0f;
				if( velocity[1] < 0 )
					velocity[1] = 0.0f;
				falling = true;
				jumping = false;
			}
			else if( collide_dir == DEAD )
			{
				dead = true;
			}
		}

		SetPosition( (int)position[0], (int)position[1] );
		Sim::Sprite::Update( );
	}
	else
	{
		// update position due to scrolling effect
		position[0] = position[0] + -level->GetScrollSpeed( )*elapsed_ms;
	}
}




