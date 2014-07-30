// Intro.cpp
// Copyright Ian Finlayson 2010
// This is part of UltraBear1 distributed under the MIT
// Implements the intro screen

#include "SimException.h"
#include "SimImage.h"

#include "App.h"
#include "Intro.h"
#include "prefix.h"

Ultra1::StateNumber Ultra1::Intro::Run( )
{
	SDL_Event event;

	// Clear the screen....
	app->Clear( 0, 0, 0 );
	app->Flip( );
	app->Clear( 0, 0, 0 );
	app->Flip( );

	// Time spent fading/staying...
	unsigned int TIME_FOR_FADE = 750;
	unsigned int TIME_FOR_STAY = 750;

	// If we are in fullscreen mode, we must wait for the screen to set???
	if( app->full )
	{
		SDL_ShowCursor( false );
		SDL_Delay( 750 );
	}

	// Load the image
	Sim::Image logo( UBD_PREFIX "/images/logo.png" );

	// Where we blit it too...
	SDL_Rect dest;
	dest.x = 141;
	dest.y = 100;
	dest.w = logo.image->w;
	dest.h = logo.image->h;

	unsigned int time_end = SDL_GetTicks( ) + TIME_FOR_FADE;

	while( time_end > SDL_GetTicks( ) )	//Fade in
	{
		if( SDL_PollEvent(&event) )
		{
			if( event.type == SDL_QUIT )
			{
				return QUIT_STATE;
			}
			else if( event.type == SDL_MOUSEBUTTONDOWN )
			{
				app->SoundEnterMenu( );
				return MENU_STATE;
			}
			else if( event.type == SDL_KEYDOWN )
			{
				app->SoundEnterMenu( );
				return MENU_STATE;
			}
		}

		float per_left =( (float)SDL_GetTicks() - time_end ) /(float)TIME_FOR_FADE;

		// Calculate the alpha value...
		SDL_SetAlpha( logo.image, SDL_SRCALPHA | SDL_RLEACCEL, (Uint8)(per_left*255.0f) );

		// Blit it too the screen
		app->Clear( 255, 255, 255 );
		SDL_BlitSurface( logo.image, NULL, app->screen, &dest );
		app->Flip( );
	}

	// Do the stay part...
	SDL_SetAlpha( logo.image, SDL_SRCALPHA | SDL_RLEACCEL, 255 );
	time_end = SDL_GetTicks( ) + TIME_FOR_STAY;
	while( time_end > SDL_GetTicks( ) )
	{
		if( SDL_PollEvent(&event) )
		{
			if( event.type == SDL_QUIT )
			{
				return QUIT_STATE;
			}
			else if( event.type == SDL_MOUSEBUTTONDOWN )
			{
				app->SoundEnterMenu( );
				return MENU_STATE;
			}
			else if( event.type == SDL_KEYDOWN )
			{
				app->SoundEnterMenu( );
				return MENU_STATE;
			}
		}

		app->Clear( 255, 255, 255 );
		SDL_BlitSurface( logo.image, NULL, app->screen, &dest );
		app->Flip( );
	}
	

	time_end = SDL_GetTicks( ) + TIME_FOR_FADE;

	while( time_end > SDL_GetTicks( ) )	//Fade out
	{
		if( SDL_PollEvent(&event) )
		{
			if( event.type == SDL_QUIT )
			{
				return QUIT_STATE;
			}
			else if( event.type == SDL_MOUSEBUTTONDOWN )
			{
				app->SoundEnterMenu( );
				return MENU_STATE;
			}
			else if( event.type == SDL_KEYDOWN )
			{
				app->SoundEnterMenu( );
				return MENU_STATE;
			}
		}

		float per_done = 1.0f - ( ( (float)SDL_GetTicks() - time_end ) /(float)TIME_FOR_FADE );

		//Calculate alpha
		SDL_SetAlpha( logo.image, SDL_SRCALPHA | SDL_RLEACCEL, (Uint8)(per_done*255.0f) );

		// Blit it...
		app->Clear( 255, 255, 255 );
		SDL_BlitSurface( logo.image, NULL, app->screen, &dest );
		app->Flip( );
	}

	// Clear the screen....
	app->Clear( 255, 255, 255 );
	app->Flip( );
	app->Clear( 255, 255, 255 );
	app->Flip( );

	if( app->full )
		SDL_ShowCursor( true );
	
	app->SoundEnterMenu( );
	return MENU_STATE;
}




