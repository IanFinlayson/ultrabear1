// Pickups.h
// Copyright Ian Finlayson 2010
// This is part of UltraBear1 distributed under the MIT
// Definition of all of our pickup classes

#ifndef PICKUPS_H
#define PICKUPS_H

#include "SimImage.h"
#include "Entity.h"

namespace Ultra1
{
	// Coin class
	class Coin : public Entity
	{
	private:
		static Sim::Image* image;	// Shared by all of the coins!

	public:
		Coin( Level* the_level );
		~Coin( );

		void Update( float elapsed_ms );
	};

	class Armor : public Entity
	{
	private:
		static Sim::Image* image;

	public:
		Armor( Level* the_level );
		~Armor( );

		void Update( float elapsed_ms );
	};

	class Force : public Entity
	{
	private:
		static Sim::Image* image;

	public:
		Force( Level* the_level );
		~Force( );

		void Update( float elapsed_ms );
	};

	class ExtraLife : public Entity
	{
	private:
		static Sim::Image* image;

	public:
		ExtraLife( Level* the_level );
		~ExtraLife( );

		void Update( float elapsed_ms );
	};
}

#endif



