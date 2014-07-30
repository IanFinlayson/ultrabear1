/********************************************************************
*	SimSoundPlayer.h			 Ian Finlayson 2005					*
*																	*
*	This class provides an easy way to play sound and music			*
*																	*
********************************************************************/

#ifndef SIM_SOUNDPLAYER
#define SIM_SOUNDPLAYER

#include <string>
#include <SDL/SDL_mixer.h>

namespace Sim
{
	class SoundPlayer
	{
	private:

		//Quality and stuff constants...
		static const int AUDIO_RATE			= 22050;
		static const int AUDIO_FORMAT		= AUDIO_S16;
		static const int AUDIO_CHANNELS		= 2;
		static const int AUDIO_BUFFERS		= 4096;

		Mix_Chunk** sounds;			// Array of sounds
		Mix_Music** musics;			// Array of musics
		std::string* sound_names;	// Array of file names
		std::string* music_names;	// Array of file names

		int num_sounds;
		int num_musics;

		bool music_playing;

	public:
		
		SoundPlayer( int numSounds, int numMusics );
		~SoundPlayer( );

		int AddMusic( const char* file_name );
		int AddSound( const char* file_name );

		void LoadMusic( int music_index );
		void LoadSound( int sound_index );
		void DropEm( );

		void PlayMusic( int music_index, int times = -1 );
		void PlaySound( int sound_index, int loops = 0 );

		void StopMusic( );
		void SetMusicPause( bool pause );

		void SetMusicVolume( int music_vol );	// Must be 0 to 127
		void SetSoundVolume( int sound_vol );
	};
}

#endif



