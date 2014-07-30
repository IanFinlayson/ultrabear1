// App.h
// Copyright Ian Finlayson 2010
// This is part of UltraBear1 distributed under the MIT
// This is the application
// class for Ultra1 Bear 1.0

#ifndef ULTRA1_APP
#define ULTRA1_APP

#include "SimApp.h"
#include "SimTextWriter.h"
#include "SimSoundPlayer.h"

#include "Constants.h"
#include "GameState.h"

namespace Ultra1
{
	class App : public Sim::App
	{
	private:
		Sim::SoundPlayer sound_player;
	public:
		// sound stuff...
		void LoadAllSounds( );
		void PlaySound( int index );
		void SoundEnterMenu( );
		void SoundEnterGame( int index );

		// text stuff...
		Sim::TextWriter text_writer;

		// Players Stats and data
		struct PlayerStats
		{
			int lives;
			int coins;
			unsigned int points;

			int current_map;
			bool back_up;
			int current_level;
			bool stay;
			bool moveon;
			bool came_from_main;

			int curr_level_next;	// Next level player must beat to move on (1-30)
		}stats;

		struct PlayerOptions
		{
			bool fullscreen;
			bool sound;
			bool music;

			SDLKey left;
			SDLKey right;
			SDLKey up;
			SDLKey down;

			SDLKey jump;
			SDLKey pause;

			void Save( );
		}options;

		bool full;

		App( bool fullscreen );
		~App( );

		// Our real main
		void Run( );
		void FadeTo( int ms=1000, int r=0, int g=0, int b=0 );
	};
}

#endif




