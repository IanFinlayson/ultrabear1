// Fireworks.h
// Copyright Ian Finlayson 2010
// This is part of UltraBear1 distributed under the MIT
// Fireworks used in the won screen

#include <SDL/SDL.h>
#include <vector>

namespace Ultra1
{
	class Firework
	{
	private:
		static const float COLOR_DECAY_RATE;
		static const int INTENSITY = 300;

		float r, g, b;
		std::vector< std::pair<float, float> > pix;
		std::vector< std::pair<float, float> > vel;

	public:
		Firework( );

		void Render( SDL_Surface* screen );
		void Update( float elapsed_sec );
	};

	float randFloat( int lower, int upper );
}




