// Level.h
// Copyright Ian Finlayson 2010
// This is part of UltraBear1 distributed under the MIT
// Represents the Level information

#ifndef ULTRA1_LEVEL
#define ULTRA1_LEVEL

#include <SDL/SDL.h>
#include "SimImage.h"
#include <utility>

#include "Constants.h"

namespace Ultra1
{
	class Level
	{
	private:
		// Information for the level files...
		struct Header
		{
			Uint8 bg_name[32];	// The name of the background image
			Uint8 music_index;	// Which background music to play
			Uint16 level_size;	// Length of the level in blocks
			Uint16 num_entities;// Number of layer 3 entities
		};
		struct Entity
		{
			Uint16 x;   // The starting x position
			Uint8 y;    // The starting y position
			Uint8 type; // The type of entity
		};

		// Data...
		Header header;  // Contains the information
		SDL_Surface* back_image; // The background picture
		Sim::Image tile_image; // The tiles
		
		Uint8* blocks;		// Array of blocks.  All y=0 come first...
		Entity* entities;	// Array of entities

		// Scrolling stuff...
		float back_x;
		float back_x_vel;
		float tile_x;
		float tile_x_vel;

		void Load( const char* file_name );

	public:
		Level( );
		~Level( );

		void Load( int map_number, int level_number );
		void Draw( SDL_Surface* screen );
		void SetScroll( float velocity );	// Velocity should be UB's velocity...
		void Update( unsigned int elapsed_ms );

		Uint8 GetBlock( int i ){ return blocks[i]; }

		// Collision detection with the level...
		CardinalDirection Collide( SDL_Rect* entitiy_rect, bool ub=true );

		// Returns whether level has scrolled all it can scroll...
		bool LevelStart( );
		bool LevelEnd( );

		float GetTileX( ){ return tile_x; }
		float GetScrollSpeed( ){ return tile_x_vel; }

		// Tests the background image to see if it is dark...
		bool IsDarkBackGround( );

		// Used to get out the entities
		Uint16 GetEntityCount( ){ return header.num_entities; }
		Uint8 GetEntityType( int index ){ return entities[index].type; }
		std::pair<int, int> GetEntityPosition( int index ){ return std::pair<int, int>( entities[index].x, entities[index].y ); }
	};
}
#endif



