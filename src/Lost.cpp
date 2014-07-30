// Menu.cpp
// Copyright Ian Finlayson 2010
// This is part of UltraBear1 distributed under the MIT
// Implements the Lost screen

#include "App.h"
#include "Lost.h"

#include "SimButton.h"

Ultra1::StateNumber Ultra1::LostState::Run( )
{
	SDL_Color fore = {128, 128, 255, 0};
	SDL_Color back = {0, 0, 0, 0};

	SDL_Surface* msg = TTF_RenderText_Shaded( app->text_writer.GetFont( GALAPOGO_36 ), "YOU HAVE LOST", fore, back );

	SDL_Rect dest;
	dest.x = 290;
	dest.y = 230;
	dest.w = msg->w;
	dest.h = msg->h;

	const unsigned int TIME_FOR_FADE = 250;
	const unsigned int TIME_FOR_STAY = 1750;

	unsigned int time_end = SDL_GetTicks( ) + TIME_FOR_FADE;

	while( time_end > SDL_GetTicks( ) )	//Fade in
	{
		float per_left =( (float)SDL_GetTicks() - time_end ) /(float)TIME_FOR_FADE;

		SDL_SetAlpha( msg, SDL_SRCALPHA | SDL_RLEACCEL, (Uint8)(per_left*255) );

		SDL_FillRect( app->screen, NULL, SDL_MapRGB( app->screen->format, 0, 0, 0 ) );
		SDL_BlitSurface( msg, NULL, app->screen, &dest );
		SDL_Flip( app->screen );
	}

	// Do the stay part...
	SDL_SetAlpha( msg, SDL_SRCALPHA | SDL_RLEACCEL, 255 );
	SDL_FillRect( app->screen, NULL, SDL_MapRGB( app->screen->format, 0, 0, 0 ) );
	SDL_BlitSurface( msg, NULL, app->screen, &dest );
	SDL_Flip( app->screen );
	SDL_Delay( TIME_FOR_STAY );


	time_end = SDL_GetTicks( ) + TIME_FOR_FADE;

	while( time_end > SDL_GetTicks( ) )	//Fade out
	{
		float per_done = 1.0f - ( ( (float)SDL_GetTicks() - time_end ) /(float)TIME_FOR_FADE );

		SDL_SetAlpha( msg, SDL_SRCALPHA | SDL_RLEACCEL, (Uint8)(per_done*255) );

		SDL_FillRect( app->screen, NULL, SDL_MapRGB( app->screen->format, 0, 0, 0 ) );
		SDL_BlitSurface( msg, NULL, app->screen, &dest );
		SDL_Flip( app->screen );
	}

	SDL_FreeSurface( msg );

	return MENU_STATE;
}



