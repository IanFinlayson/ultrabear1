// Fireworks.cpp
// Copyright Ian Finlayson 2010
// This is part of UltraBear1 distributed under the MIT
// Fireworks used in the won screen

#include "Fireworks.h"
#include <cmath>

// Used to decide whether or not to render a particle
bool dotInScreen( int x, int y, int w, int h )
{
	if( x < 0 )
		return false;
	if( x >= w )
		return false;
	if( y < 0 )
		return false;
	if( y >= h )
		return false;

	return true;
}


// from the SDL docs :)
void putpixel(SDL_Surface *surface, int x, int y, Uint32 pixel)
{
    int bpp = surface->format->BytesPerPixel;
    /* Here p is the address to the pixel we want to set */
    Uint8 *p = (Uint8 *)surface->pixels + y * surface->pitch + x * bpp;

    switch(bpp) {
    case 1:
        *p = pixel;
        break;

    case 2:
        *(Uint16 *)p = pixel;
        break;

    case 3:
        if(SDL_BYTEORDER == SDL_BIG_ENDIAN) {
            p[0] = (pixel >> 16) & 0xff;
            p[1] = (pixel >> 8) & 0xff;
            p[2] = pixel & 0xff;
        } else {
            p[0] = pixel & 0xff;
            p[1] = (pixel >> 8) & 0xff;
            p[2] = (pixel >> 16) & 0xff;
        }
        break;

    case 4:
        *(Uint32 *)p = pixel;
        break;
    }
}


// Used to get random floats in a range (uniform dist. not bell curve)
float Ultra1::randFloat( int lower, int upper )
{
	// base is in (0, 1)
	float base = rand( ) / (float)RAND_MAX;

	// now base covers same range as (lower,upper)
	base *= (upper-lower);

	// shift it
	return base + lower;
}


// Used to get a color for the firework
void randomColor( int& r, int& g, int& b )
{
	switch( rand( ) % 7 )
	{
	case 0:
		r = 200;	// Light red
		g = 50;
		b = 50;
		break;

	case 1:
		r = 130;	// Cyan
		g = 230;
		b = 230;
		break;

	case 2:			// Light Green
		r = 75;
		g = 250;
		b = 75;
		break;

	case 3:
		r = 215;	// Yellowish
		g = 215;
		b = 50;
		break;

	case 4:			// Orange
		r = 200;
		g = 128;
		b = 0;
		break;

	case 5:			// Silver
		r = 180;
		g = 180;
		b = 180;
		break;

	case 6:			// Purple
		r = 180;
		g = 120;
		b = 250;
		break;

	}
}


// Firework class
const float Ultra1::Firework::COLOR_DECAY_RATE = 100.0f;

Ultra1::Firework::Firework( )
{
	int br = 0, bg = 0, bb = 0;
	randomColor( br, bg, bb );
	r = (float)br;
	g = (float)bg;
	b = (float)bb;

	float x = randFloat( 10, 790 );
	float y = randFloat( 10, 400 );

	for( int i=0; i<INTENSITY; ++i )
	{
		pix.push_back( std::pair<float, float>(x, y) );

		// we must find a random velocity and convert it to cartesian
		float theta = randFloat(0, 360);
		float speed = randFloat(0, 45);

		vel.push_back( std::pair<float, float>(speed*cos(theta), speed*sin(theta)) );
	}
}

void Ultra1::Firework::Update( float elapsed_sec )
{
	r -= COLOR_DECAY_RATE * elapsed_sec;
	g -= COLOR_DECAY_RATE * elapsed_sec;
	b -= COLOR_DECAY_RATE * elapsed_sec;

	bool all = true;

	if( r < 0 )
		r = 0;
	else
		all = false;

	if( g < 0 )
		g = 0;
	else
		all = false;

	if( b < 0 )
		b = 0;
	else
		all = false;

	// Reinitialize the firework!
	if( all )
	{
		int br = 0, bg = 0, bb = 0;
		randomColor( br, bg, bb );
		r = (float)br;
		g = (float)bg;
		b = (float)bb;

		float x = randFloat( 10, 790 );
		float y = randFloat( 10, 400 );

		for( std::vector< std::pair<float, float> >::iterator i=pix.begin( ); i!=pix.end( ); ++i )
		{
			i->first = x;
			i->second = y;
		}
	}

	for( std::vector< std::pair<float, float> >::iterator i=pix.begin( ); i!=pix.end( ); ++i )
	{
		int index = (int)(i - pix.begin( ));

		i->first += vel[index].first*elapsed_sec;
		i->second += vel[index].second*elapsed_sec;
	}
}

void Ultra1::Firework::Render( SDL_Surface* screen )
{
	for( std::vector< std::pair<float, float> >::iterator i=pix.begin( ); i!=pix.end( ); ++i )
	{
		int x = (int)i->first;
		int y = (int)i->second;

		if( dotInScreen( x, y, screen->w, screen->h ) )
			putpixel( screen, x, y, SDL_MapRGB( screen->format, (int)r, (int)g, (int)b ) );
	}
}







