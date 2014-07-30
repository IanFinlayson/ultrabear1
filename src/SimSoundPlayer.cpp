/********************************************************************
*	SimSoundPlayer.cpp			 Ian Finlayson 2005					*
*																	*
*	Implementation of Sim::SoundPlayer								*
*																	*
********************************************************************/

#include "SimSoundPlayer.h"
#include "SimException.h"

Sim::SoundPlayer::SoundPlayer( int numSounds, int numMusics )
{
	Mix_OpenAudio( AUDIO_RATE, AUDIO_FORMAT, AUDIO_CHANNELS, AUDIO_BUFFERS );

	num_musics = numMusics;
	num_sounds = numSounds;

	musics = new Mix_Music*[ num_musics ];
	sounds = new Mix_Chunk*[ num_sounds ];

	music_names = new std::string[num_musics];
	sound_names = new std::string[num_sounds];

	// Set em to NULL
	for( int i=0; i<num_musics; i++ )
	{
		musics[i] = NULL;
	}
	for( int i=0; i<num_sounds; i++ )
	{
		sounds[i] = NULL;
	}

	music_playing = false;

	SetMusicVolume( 127 );
	SetSoundVolume( 127 );
}

Sim::SoundPlayer::~SoundPlayer( )
{
	if( music_playing )
	{
		Mix_HaltMusic( );
	}

	for( int i=0; i<num_sounds; i++ )
	{
		if( sounds[i] )
		{
			Mix_FreeChunk( sounds[i] );
			sounds[i] = NULL;
		}
	}

	for( int i=0; i<num_musics; i++ )
	{
		if( musics[i] )
		{
			Mix_FreeMusic( musics[i] );
			musics[i] = NULL;
		}
	}

	delete [] sounds;
	delete [] musics;

	delete [] music_names;
	delete [] sound_names;

	Mix_HaltChannel( -1 );

	Mix_CloseAudio( );
}

int Sim::SoundPlayer::AddMusic( const char* file_name )
{
	static int curr_music = -1;

	curr_music++;

	music_names[ curr_music ] = file_name;

    return curr_music;
}

int Sim::SoundPlayer::AddSound( const char* file_name )
{
	static int curr_sound = -1;

	curr_sound++;

	sound_names[ curr_sound ] = file_name;

	return curr_sound;
}

void Sim::SoundPlayer::LoadMusic( int music_index )
{
	if( musics[music_index] )
	{
		Mix_FreeMusic( musics[music_index] );
		musics[music_index] = NULL;
	}

	musics[music_index] = Mix_LoadMUS( music_names[music_index].c_str( ) );

	if( musics[music_index] == NULL )
	{
		throw Sim::Exception( "AddMusic", "Music can't load" );
	}
}

void Sim::SoundPlayer::LoadSound( int sound_index )
{
	if( sounds[sound_index] )
	{
		Mix_FreeChunk( sounds[sound_index] );
		sounds[sound_index] = NULL;
	}

	sounds[sound_index] = Mix_LoadWAV( sound_names[sound_index].c_str( ) );

	if( sounds[sound_index] == NULL )
	{
		throw Sim::Exception( "AddSound", "Sound could not load" );
	}
}

void Sim::SoundPlayer::DropEm( )
{
	for( int i=0; i<num_sounds; i++ )
	{
		if( sounds[i] )
		{
			Mix_FreeChunk( sounds[i] );
			sounds[i] = NULL;
		}
	}

	for( int i=0; i<num_musics; i++ )
	{
		if( musics[i] )
		{
			Mix_FreeMusic( musics[i] );
			musics[i] = NULL;
		}
	}
}

void Sim::SoundPlayer::PlayMusic( int music_index, int times )
{
	if( music_playing )
	{
		Mix_HaltMusic( );
	}

	if( musics[music_index] )
		Mix_PlayMusic( musics[ music_index ], times );
}

void Sim::SoundPlayer::PlaySound( int sound_index, int loops )
{
	if( sounds[sound_index] )
		Mix_PlayChannel( -1, sounds[ sound_index ], loops );
}

void Sim::SoundPlayer::StopMusic( )
{
	if( music_playing )
	{
		Mix_HaltMusic( );

		music_playing = false;
	}
}

void Sim::SoundPlayer::SetMusicPause( bool pause )
{
	if( pause )
	{
		Mix_PauseMusic( );
	}
	else
	{
		Mix_ResumeMusic( );
	}
}

void Sim::SoundPlayer::SetMusicVolume( int music_vol )
{
	Mix_VolumeMusic( music_vol );
}

void Sim::SoundPlayer::SetSoundVolume( int sound_vol )
{
	Mix_Volume( -1, sound_vol );
}



