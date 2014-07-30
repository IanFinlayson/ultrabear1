// Bear.h
// Copyright Ian Finlayson 2010
// This is part of UltraBear1 distributed under the MIT
// The Bear represents Ultra Bear himself
// It draws and checks collisions etc.

#ifndef ULTRA1_BEAR
#define ULTRA1_BEAR

#include "Level.h"
#include "App.h"

#include "SimImage.h"
#include "SimSprite.h"
#include "SimVector.h"

namespace Ultra1
{
	class Bear : public Sim::Sprite
	{
	private:
		Sim::Image image;	// Main image
		Sim::Image other;	// Main image rotated

		Direction direction;	// Either LEFT, RIGHT or STILL
		Direction heading;		// Either LEFT or RIGHT

		Power powers;		// Either NONE, ARMOR or FORCE

		Level* level;	// A pointer to the level so we can do collisions etc...

		// We use vector math rather than Sim::Sprite's built in stuff...
		Sim::Vector<float, 2> position;
		Sim::Vector<float, 2> velocity;

		float bear_speed;

		bool jumping, falling;
		bool won, lost;
		bool dead;
		bool is_paused;
		unsigned int pause_start;

		unsigned int time_got_force;
		static const unsigned int TIME_WITH_FORCE = 9000;	// 9 seconds
		bool had_armor;

	public:
		Bear( Level* lev );
		~Bear( );

		void Jump( Ultra1::App* app );
		void Bounce( );
		void UnJump( );
		void SetArmor( bool armor );
		void Die( );
		void SetForce( );
		void SetDirection( Direction dir );
		void Update( unsigned int elapsed_ms );

		void SetPause( bool pause );
		bool HasWon( ){return won;}
		bool HasLost( ){return lost;}
		bool HasArmor( ){ return (powers == ARMOR); }
		bool HasForce( ){ return (powers == FORCE); }

	};
}
#endif




