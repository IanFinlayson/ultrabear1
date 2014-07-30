// App.cpp
// Copyright Ian Finlayson 2010
// This is part of UltraBear1 distributed under the MIT
// Implements the main
// application class

#include "App.h"
#include "Intro.h"
#include "MainMenu.h"
#include "Game.h"
#include "MapState.h"
#include "Won.h"
#include "Lost.h"
#include "Help.h"
#include "Story.h"
#include "Options.h"
#include "prefix.h"

#include "SimException.h"
#include <fstream>
#include <string>

Ultra1::App::App(bool fullscreen) : Sim::App(WIDTH, HEIGHT, fullscreen, "Ultra Bear 1", UBD_PREFIX "/images/icon.png") ,
                                                  sound_player(NUM_SOUNDS, NUM_MUSICS), text_writer(NUM_FONTS)
{
	// The order in which fonts and sounds are added matters!
	// They must coincide with the order in Constants.h!
	text_writer.AddFont( UBD_PREFIX "/fonts/FreeSans.ttf", 14 );
	text_writer.AddFont( UBD_PREFIX "/fonts/galapogo.ttf", 36 );
	text_writer.AddFont( UBD_PREFIX "/fonts/galapogo.ttf", 72 );
	text_writer.AddFont( UBD_PREFIX "/fonts/galapogo.ttf", 24 );

	// Add the filenames of our sound and music files
	sound_player.AddMusic( UBD_PREFIX "/music/1.ogg" );
	sound_player.AddMusic( UBD_PREFIX "/music/2.ogg" );
	sound_player.AddMusic( UBD_PREFIX "/music/3.ogg" );
	sound_player.AddMusic( UBD_PREFIX "/music/4.ogg" );
	sound_player.AddMusic( UBD_PREFIX "/music/5.ogg" );

	sound_player.AddSound( UBD_PREFIX "/sounds/button.wav" );
	sound_player.AddSound( UBD_PREFIX "/sounds/force.wav" );
	sound_player.AddSound( UBD_PREFIX "/sounds/jump.wav" );
	sound_player.AddSound( UBD_PREFIX "/sounds/coin.wav" );
	sound_player.AddSound( UBD_PREFIX "/sounds/armor.wav" );
	sound_player.AddSound( UBD_PREFIX "/sounds/kill.wav" );
	sound_player.AddSound( UBD_PREFIX "/sounds/die.wav" );
	sound_player.AddSound( UBD_PREFIX "/sounds/finish.wav" );
	sound_player.AddSound( UBD_PREFIX "/sounds/life.wav" );

	// We always want SDL to repeat keys...
	SDL_EnableKeyRepeat( SDL_DEFAULT_REPEAT_INTERVAL, SDL_DEFAULT_REPEAT_INTERVAL );

	stats.lives = 5;
	stats.coins = 0;
	stats.points = 0;
	stats.current_map = 1;
	stats.current_level = 1;
	stats.back_up = false;
	stats.stay = false;
	stats.moveon = false;
	stats.curr_level_next = 1;

	// We open the sound file to load previous sound/music settings...
	std::string home;
#ifdef WIN32
	home = getenv("USERPROFILE");
#else
	home = getenv("HOME");
#endif
  std::fstream file((home + "/.ultrabear1/config/sound.dat").c_str( ), std::ios::in );
	if(!file.is_open()) throw Sim::Exception("App constructor", "could not load sound preferences");
  int s, m;
	file >> s;
	file >> m;
	options.sound = (s == 1) ? true : false;
	options.music = (m == 1) ? true : false;
	file.close( );

	// We open the keys file to lad previous key configurations...
	std::fstream kfile((home + "/.ultrabear1/config/keys.dat").c_str( ), std::ios::in );
	if(!kfile.is_open()) throw Sim::Exception("App constructor", "could not load key preferences");
	int temp;
	kfile >> temp;
	options.left = (SDLKey)temp;
	kfile >> temp;
	options.right = (SDLKey)temp;
	kfile >> temp;
	options.up = (SDLKey)temp;
	kfile >> temp;
	options.down = (SDLKey)temp;
	kfile >> temp;
	options.jump = (SDLKey)temp;
	kfile >> temp;
	SDLKey dummy;
  dummy = (SDLKey)temp;  // we used to have a "dash" key, but it was worthless
	kfile >> temp;
	options.pause = (SDLKey)temp;
	kfile.close( );

	options.fullscreen = full = fullscreen;
	LoadAllSounds( );

	sound_player.SetMusicVolume( 80 );
}

// Load and play menu item sounds...
void Ultra1::App::SoundEnterMenu( )
{
	sound_player.DropEm( );
	LoadAllSounds( );

	sound_player.LoadMusic( MUS_1 );

	if( options.music )
		sound_player.PlayMusic( MUS_1 );
}

// Loads all sound effects!
void Ultra1::App::LoadAllSounds( )
{
	sound_player.LoadSound( BUTTON_NOISE );
	sound_player.LoadSound( FORCE_NOISE );
	sound_player.LoadSound( JUMP_NOISE );
	sound_player.LoadSound( COIN_NOISE );
	sound_player.LoadSound( ARMOR_NOISE );
	sound_player.LoadSound( KILL_NOISE );
	sound_player.LoadSound( DIE_NOISE );
	sound_player.LoadSound( FINISH_NOISE );
	sound_player.LoadSound( LIFE_NOISE );
}

void Ultra1::App::PlaySound( int index )
{
	if( options.sound )
		sound_player.PlaySound( index );
}

// Load and play game sounds (music according to index)
void Ultra1::App::SoundEnterGame( int index )
{
	sound_player.DropEm( );
	LoadAllSounds( );

	sound_player.LoadMusic( index - 1 );

	if( options.music )
		sound_player.PlayMusic( index - 1 );
}

Ultra1::App::~App( )
{
}

// Saves the players options...
void Ultra1::App::PlayerOptions::Save( )
{
  	std::string home;
#ifdef WIN32
	home = getenv("USERPROFILE");
#else
	home = getenv("HOME");
#endif
	std::fstream ffile((home + "/.ultrabear1/config/screen.dat").c_str( ), std::ios::out );
  if(!ffile.is_open( )) throw Sim::Exception("Save", "Could not write to screen file");
	if( fullscreen )
		ffile << 1 << std::endl;
	else
		ffile << 0 << std::endl;
	ffile.close( );

	std::fstream sfile((home + "/.ultrabear1/config/sound.dat").c_str( ), std::ios::out );
  if(!sfile.is_open( )) throw Sim::Exception("Save", "Could not write to sound file");
	if( sound )
		sfile << 1 << std::endl;
	else
		sfile << 0 << std::endl;
	if( music )
		sfile << 1 << std::endl;
	else
		sfile << 0 << std::endl;
	sfile.close( );

	std::fstream kfile((home + "/.ultrabear1/config/keys.dat").c_str( ), std::ios::out );
  if(!kfile.is_open( )) throw Sim::Exception("Save", "Could not write to keys file");
	kfile << left << std::endl;
	kfile << right << std::endl;
	kfile << up << std::endl;
	kfile << down << std::endl;
	kfile << jump << std::endl;
	kfile << 0 << std::endl;
	kfile << pause << std::endl;
	kfile.close( );

}

// Runs the Game...
void Ultra1::App::Run( )
{
	// All of the game states we could be in...
	Intro intro( this );
	MainMenu menu( this );
	Game game( this );
	MapState map_state( this );
	WonState won( this );
	LostState lost( this );
	HelpState help( this );
	StoryState story( this );
	OptionsState options( this );

	// Must be entered into array in same order as the const values...
	GameState* states[] = { &intro, &menu, &game, &map_state, &won, &lost, &help, &story, &options };

	// We start in the intro...
	StateNumber current_state = INTRO_STATE;

	while( current_state != QUIT_STATE )
	{
		// Run the current state and assign the next state to it...
		current_state = states[current_state]->Run( );
	}
}


void Ultra1::App::FadeTo( int ms, int r, int g, int b )
{
	// Make a deep copy of the screen
	Sim::Image bg = screen;

	unsigned int time_end = SDL_GetTicks( ) + ms;

	while( time_end > SDL_GetTicks( ) )	//Fade out
	{
		float per_done = 1.0f - ( ( (float)SDL_GetTicks() - time_end ) /(float)ms );

		//Calculate alpha
		SDL_SetAlpha( bg.image, SDL_SRCALPHA | SDL_RLEACCEL, (Uint8)(per_done*255.0f) );

		// Blit it...
		Clear( r, g, b );
		SDL_BlitSurface( bg.image, NULL, screen, NULL );
		Flip( );
	}

	// Clear to the color...
	Clear( r, g, b );
	Flip( );
}


int Ultra1::GetMusicIndex( int map, int level )
{
	switch( map*10 + level )
	{
	case 11:
		return 1;
	case 12:
		return 2;
	case 13:
		return 3;
	case 14:
		return 2;
	case 15:
		return 2;

	case 21:
		return 3;
	case 22:
		return 3;
	case 23:
		return 2;
	case 24:
		return 3;
	case 25:
		return 1;

	case 31:
		return 2;
	case 32:
		return 3;
	case 33:
		return 2;
	case 34:
		return 2;
	case 35:
		return 3;

	case 41:
		return 3;
	case 42:
		return 2;
	case 43:
		return 3;
	case 44:
		return 1;
	case 45:
		return 2;
	
	case 51:
		return 3;
	case 52:
		return 2;
	case 53:
		return 3;
	case 54:
		return 2;
	case 55:
		return 3;

	case 61:
		return 2;
	case 62:
		return 3;
	case 63:
		return 1;
	case 64:
		return 3;
	case 65:
		return 4;

	default:
		throw Sim::Exception( "Song Matcher", "Bad level" );
	}
}




