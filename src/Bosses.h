// Bosses.h
// Copyright Ian Finlayson 2010
// This is part of UltraBear1 distributed under the MIT
// Definition of all of our bosses

#ifndef BOSSES_H
#define BOSSES_H

#include "SimImage.h"
#include "Entity.h"

namespace Ultra1
{
	// These are just kinda stubs for now...
	class WalrusBoss : public Entity
	{
	private:
		static Sim::Image* image;

	public:
		WalrusBoss( Level* the_level );
		~WalrusBoss( );

		void Update( float elapsed_ms );
	};


	class BeaverBoss : public Entity
	{
	private:
		static Sim::Image* image;

	public:
		BeaverBoss( Level* the_level );
		~BeaverBoss( );

		void Update( float elapsed_ms );
	};


	class PossomBoss : public Entity
	{
	private:
		static Sim::Image* image;

	public:
		PossomBoss( Level* the_level );
		~PossomBoss( );

		void Update( float elapsed_ms );
	};


	class ChihuahuaBoss : public Entity
	{
	private:
		static Sim::Image* image;

	public:
		ChihuahuaBoss( Level* the_level );
		~ChihuahuaBoss( );

		void Update( float elapsed_ms );
	};



	class ChupacabraBoss : public Entity
	{
	private:
		static Sim::Image* image;

	public:
		ChupacabraBoss( Level* the_level );
		~ChupacabraBoss( );

		void Update( float elapsed_ms );
	};



	class PenguinBoss : public Entity
	{
	private:
		static Sim::Image* image;

	public:
		PenguinBoss( Level* the_level );
		~PenguinBoss( );

		void Update( float elapsed_ms );
	};

}

#endif




