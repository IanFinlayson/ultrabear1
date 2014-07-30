// Enemies.h
// Copyright Ian Finlayson 2010
// This is part of UltraBear1 distributed under the MIT
// Defines all of our enemy classes

#ifndef ENEMIES_H
#define ENEMIES_H

#include "SimImage.h"
#include "Entity.h"

// I should not have coded this with all different classes,
// but I do not feel like refactoring it...

namespace Ultra1
{
	// Seal
	class SnowMan : public Entity
	{
	private:
		static Sim::Image* image;
		static Sim::Image* other;

	public:
		SnowMan( Level* the_level );
		~SnowMan( );

		void Update( float elapsed_ms );
	};

	// A bird
	class Bird : public Entity
	{
	private:
		static Sim::Image* image;

	public:
		Bird( Level* the_level );
		~Bird( );

		void Update( float elapsed_ms );
	};

	// A beaver
	class Beaver : public Entity
	{
	private:
		static Sim::Image* image;
		static Sim::Image* other;

	public:
		Beaver( Level* the_level );
		~Beaver( );

		void Update( float elapsed_ms );
	};

	//A moose
	class Moose : public Entity
	{
	private:
			static Sim::Image* image;
			static Sim::Image* other;
	public:
		Moose( Level* the_level );
		~Moose( );

		void Update( float elapsed_ms );
	};

	// A raccoon
	class Raccoon : public Entity
	{
	private:
		static Sim::Image* image;
		static Sim::Image* other;

	public:
		Raccoon( Level* the_level );
		~Raccoon( );
	
		void Update( float elapsed_ms );
	};

	// An Possom
	class Possom : public Entity
	{
	private:
		static Sim::Image* image;
		static Sim::Image* other;

	public:
		Possom( Level*  the_level );
		~Possom( );

		void Update( float elapsed_ms );
	};

	// A snake
	class Snake : public Entity
	{
	private:
		static Sim::Image* image;
		static Sim::Image* other;

	public:
		Snake( Level* the_level );
		~Snake( );

		void Update( float elapsed_ms );
	};

	// A chihuahua
	class Chihuahua : public Entity
	{
	private:
		static Sim::Image* image;
		static Sim::Image* other;

	public:
		Chihuahua( Level* the_level );
		~Chihuahua( );

		void Update( float elapsed_ms );
	};

	// A lemming
	class Lemming : public Entity
	{
	private:
		static Sim::Image* image;
		static Sim::Image* other;

	public:
		Lemming( Level* the_level );
		~Lemming( );

		void Update( float elapsed_ms );
	};

	// A Goat
	class Goat : public Entity
	{
	private:
		static Sim::Image* image;
		static Sim::Image* other;

	public:
		Goat( Level* the_level );
		~Goat( );

		void Update( float elapsed_ms );
	};

	// The most feared of enemies, the Penguin
	class Penguin : public Entity
	{
	private:
		static Sim::Image* image;
		static Sim::Image* other;

	public:
		Penguin( Level* the_level );
		~Penguin( );

		void Update( float elapsed_ms );
	};

	// A fireball for the castle!
	class FireBall : public Entity
	{
	private:
		static Sim::Image* image;
		static Sim::Image* other;

	public:
		FireBall( Level* the_level );
		~FireBall( );

		void Update( float elapsed_ms );
	};



}
#endif




