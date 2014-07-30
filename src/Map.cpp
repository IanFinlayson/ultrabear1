// Map.cpp
// Copyright Ian Finlayson 2010
// This is part of UltraBear1 distributed under the MIT

#include <fstream>
#include <sstream>
#include "Map.h"
#include "prefix.h"
#include "SimException.h"

Ultra1::Map::Map( int map_number, int current_next_beat ) : level_dot(0,0,20,20,1), level_lock(0,0,20,20,1), dot_image(UBD_PREFIX "/images/dot.png",0,0,255), lock_image(UBD_PREFIX "/images/lock.png",0,0,255)
{
	// Load the appropriate image
  std::stringstream fname1;
	fname1 << (UBD_PREFIX "/maps/map") << map_number << ".jpg";
	image = new Sim::Image( fname1.str( ).c_str( ) );

	// now we load the level data
  std::stringstream fname2;
	fname2 << (UBD_PREFIX "/maps/map") << map_number << ".ub1m";
	std::fstream file( fname2.str( ).c_str( ), std::ios::in );
	if(!file.is_open( ))
  {
    std::stringstream ss;
    ss << "Could not load map '" << fname2.str( ) << "' file";
    throw Sim::Exception("Map constructor", ss.str( ).c_str( ));
  }

  for( int i=0; i<7; i++ )
	{
		file >> info[i].x;
		file >> info[i].y;
		file >> info[i].next;
	}
	file.close( );

	this->map_number = map_number;
	this->current_next_beat = current_next_beat;

	// Set up the sprites
	level_dot.AddAnimation( 0, 0, 5, true, dot_image.image, 125, false );
	level_lock.AddAnimation( 0, 0, 5, true, lock_image.image, 125, false );
}

Ultra1::Map::~Map( )
{
	if( image )
		delete image;
}

void Ultra1::Map::Update( unsigned int elapsed_ms )
{
  /* banish warnings */
  elapsed_ms = 0;
	level_dot.Update( );
	level_lock.Update( );
}

void Ultra1::Map::Draw( SDL_Surface* screen )
{
	SDL_BlitSurface( image->image, NULL, screen, NULL );

	for( int i=1; i<6; i++ )
	{
		if( ((map_number - 1)*5 + i) <= current_next_beat )
		{
			level_dot.SetPosition( info[i].x - 10, info[i].y - 10 );		
			level_dot.Draw( screen );
		}
		else
		{
			level_lock.SetPosition( info[i].x - 10, info[i].y - 10 );		
			level_lock.Draw( screen );
		}
	}
}








