// Level.cpp
// Copyright Ian Finlayson 2010
// This is part of UltraBear1 distributed under the MIT
// Implements the Level

#include <fstream>
#include <sstream>
#include <SDL/SDL_image.h>
#include "SimException.h"
#include "SimFunctions.h"

#include "prefix.h"
#include "Constants.h"
#include "Level.h"

Ultra1::Level::Level( ) : tile_image( UBD_PREFIX "/images/blocks.png", 0, 0, 255 )
{
	back_image = NULL;

	blocks = NULL;
	entities = NULL;

	back_x = 0.0f;
	back_x_vel = 0.0f;

	tile_x = 0.0f;
	tile_x_vel = 0.0f;
}

Ultra1::Level::~Level( )
{
	if( back_image )
	{
		SDL_FreeSurface( back_image );
		back_image = NULL;
	}

	if( blocks )
	{
		delete [] blocks;
		blocks = NULL;
	}

	if( entities )
	{
		delete [] entities;
		entities = NULL;
	}
}

void Ultra1::Level::Load( const char* file_name )
{
	// Open the file...
	std::fstream file( file_name, std::ios::in | std::ios::binary );
  if(!file.is_open( )) throw Sim::Exception("Level loader", "could not open file");

	// Read the header...
	file.read( (char*)&header.bg_name, 23 );
	file.read( (char*)&header.music_index, 1 );
	file.read( (char*)&header.level_size, 2 );
	file.read( (char*)&header.num_entities, 2 );

	// Now we load the background image...
  std::string bg_name;
	if( back_image )
		SDL_FreeSurface( back_image );
	bg_name = UBD_PREFIX "/images/";
  bg_name = bg_name + ((const char*)header.bg_name);

	SDL_Surface* temp = IMG_Load( bg_name.c_str( ) );
	if( !temp )
	{
		std::string msg = "Image: ";
		msg += file_name;
		msg += " could not load";
		throw Sim::Exception( "Level::Load", (char*) msg.c_str() );
	}
	back_image = SDL_DisplayFormat( temp );
	SDL_FreeSurface( temp );
	
	// Allocate space for the blocks...
	if( blocks )
		delete [] blocks;
	blocks = new Uint8[ NUM_BLOCKS_PER_COLUM*header.level_size ];

	// Allocate space for the entities...
	if( entities )
		delete [] entities;
	entities = new Entity[ header.num_entities ];

	// Read in the blocks data...
	for( int i=0; i<header.level_size; i++ )
	{
		for( int j=0; j<NUM_BLOCKS_PER_COLUM; j++ )
		{
			// Read in the block...
			file.read( (char*) &blocks[i*NUM_BLOCKS_PER_COLUM + j], 1 );
		}
	}

	// Now we read in the entity data...
	for( int i=0; i<header.num_entities; i++ )
	{
		file.read( (char*) &entities[i].x, 2 );
		file.read( (char*) &entities[i].y, 1 );
		file.read( (char*) &entities[i].type, 1 );
	}

	file.close( );
}

void Ultra1::Level::Load( int map_number, int level_number )
{
  std::stringstream name;
	name << UBD_PREFIX "/levels/level" << map_number << level_number << ".ub1l";
	Load( name.str( ).c_str( ) );
}

void Ultra1::Level::Draw( SDL_Surface* screen )
{
	static SDL_Rect left = { 0, 0, 1, 600 };
	left.w = static_cast<int>( back_x );

	static SDL_Rect right = { 0, 0, 1, 600 };
	right.x = static_cast<int>( back_x );
	right.w = 800 - static_cast<int>( back_x );

	static SDL_Rect s_l = { 0, 0, 1, 600 };
	s_l.w = right.w;

	static SDL_Rect s_r = { 0, 0, 1, 600 };
	s_r.x = s_l.w;
	s_r.w = left.w;

	// Blit the background...
	SDL_BlitSurface( back_image, &left, screen, &s_r );
	SDL_BlitSurface( back_image, &right, screen, &s_l );


	// Now we are going to draw the blocks (layer 2)
	static SDL_Rect src = { 0, 0, 20, 20 };

	static SDL_Rect dest = { 0, 0, 20, 20 };

	float tile_x_temp = tile_x / 20.0f;

	for( int i=(int)tile_x_temp; i<tile_x_temp+40; i++ )
	{
		for( int j=0; j<NUM_BLOCKS_PER_COLUM; j++ )
		{
			if( blocks[i*NUM_BLOCKS_PER_COLUM + j] )
			{
				src.x = blocks[i*NUM_BLOCKS_PER_COLUM + j]*20;

				dest.x = (int)(((float)i - tile_x_temp)*(float)BLOCK_SIZE);
				dest.y = j*BLOCK_SIZE;

				SDL_BlitSurface( tile_image.image, &src, screen, &dest );
			}
		}
	}
}

bool Ultra1::Level::IsDarkBackGround( )
{
	// Deep copy of the surface which is destroyed in scope...
	Sim::Image temp = back_image;

	// Test pixel taken from upper left corner...
	Uint32 test_pixel = temp.GetPixel( 0, 0 );

	// Get r-g-b representation...
	Uint8 r,g,b;
	SDL_GetRGB( test_pixel, back_image->format, &r, &g, &b );

	// If any of them are greater than 200, it is light...
	if( r > 200 )
		return false;
	if( g > 200 )
		return false;
	if( b > 200 )
		return false;

	return true;
}

void Ultra1::Level::SetScroll( float velocity )
{
	tile_x_vel = velocity;
	back_x_vel = tile_x_vel / PARRALAX_FACTOR;
}

void Ultra1::Level::Update( unsigned int elapsed_ms )
{
	if( tile_x <= (((static_cast<float>( header.level_size )*20.0f)-800.0f)) )
	{
		if( tile_x >= 0.0f )
		{
			// User not yet at end or start...
			tile_x += tile_x_vel * (static_cast<float>(elapsed_ms) / 1000.0f);
			back_x += back_x_vel * (static_cast<float>(elapsed_ms) / 1000.0f);
		}
		else
		{
			tile_x = 0.1f;
			tile_x_vel = 0.0f;

			back_x = 0.0f;
			back_x_vel = 0.0f;
		}
	}
	else
	{
		tile_x = (static_cast<float>( header.level_size )*20.0f - 0.1f) - 800.0f;
		tile_x_vel = 0.0f;

		back_x_vel = 0.0f;
	}

	// Make sure it loops around...
	if( back_x > 800.0f )
	{
		back_x -= 800.0f;
	}
	else if( back_x < 0.0f )
	{
		back_x += 800.0f;
	}
}

bool Ultra1::Level::LevelEnd( )
{
	if( tile_x <= (((static_cast<float>( header.level_size )*20.0f)-800.0f)-1.0f ) )
		return false;
	return true;
}

bool Ultra1::Level::LevelStart( )
{
	if( tile_x >= 1.0f )
		return false;

	return true;
}


Ultra1::CardinalDirection Ultra1::Level::Collide( SDL_Rect* entity_rect, bool ub )
{
	// First we test for being off the screen...
	// This is for Ultra Bear only...not the enemies!
	if( ub )
	{
		if( (entity_rect->y) < 0 )
			return NO_COLLIDE;
		else if( entity_rect->y > 600 )
			return DEAD;				// Entity has died...

		if( entity_rect->x < 0 )
			return EAST;
		else if( entity_rect->x > (799 - entity_rect->w) )
			return WON;								// Entity has passed level...
	}

	// These are block indices!
	int block_x_1 = (((int)tile_x)/20 + (entity_rect->x / 20));
	int block_x_2 = block_x_1 + (entity_rect->w / 20) + 1;

	// We only tests blocks around UB
	int block_y_1 = ((entity_rect->y-1) / 20);
	int block_y_2 = block_y_1 + (entity_rect->h / 20);

	static SDL_Rect block_pos = {0, 0, 20, 20};

	// We must test the sides before north, so we have a separate
	// variable for collisions to the north
	bool n_collide = false;
	bool s_collide = false;

	// For each x block around the entity
	for( int i=block_x_1; i<=block_x_2; i++ )
	{
		// For each y block around the entity
		for( int j=block_y_1; j<=block_y_2; j++ )
		{
			if( (j<0) || (j>29) )	// block out of bounds!
			{
				continue;	// back around!
			}

			// If the block is here
			if( blocks[i*NUM_BLOCKS_PER_COLUM + j] )
			{
				block_pos.x = i*BLOCK_SIZE - (int)tile_x;
				block_pos.y = j*BLOCK_SIZE;
				

				CardinalDirection dir = Sim::Collide( entity_rect, &block_pos );

				// If it's north or south, we still must keep going
				if( dir == NORTH )
					n_collide = true;
				else if( dir == SOUTH )
					s_collide = true;
				else if( dir != NO_COLLIDE )
					return dir;
			}
		}
	}

	// Return north/south or no collision
	if( n_collide )
		return NORTH;
	else if( s_collide )
		return SOUTH;
	else
		return NO_COLLIDE;
}








