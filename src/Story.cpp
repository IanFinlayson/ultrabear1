// Story.cpp
// Copyright Ian Finlayson 2010
// This is part of UltraBear1 distributed under the MIT

#include "App.h"
#include "Story.h"

#include "SimButton.h"
#include "SimImage.h"
#include "prefix.h"
#include <vector>
#include <fstream>


Ultra1::StateNumber Ultra1::StoryState::Run( )
{
	Sim::Image but( UBD_PREFIX "/images/button.png", 255, 0, 0 );
	Sim::Image bg( UBD_PREFIX "/images/icehills.jpg" );
	
	Sim::Button menu( 0, 480, 450, 50, 3, 0, 0, 0, 40, 7, true );
	menu.SetBackGround( but.image );
	menu.SetForeGround( "Main Menu", app->text_writer.GetFont( GALAPOGO_36 ), 0, 0, 0 );
	
	Sim::Button quit( 0, 540, 450, 50, 3, 0, 0, 0, 40, 7, true );
	quit.SetBackGround( but.image );
	quit.SetForeGround( "Quit", app->text_writer.GetFont( GALAPOGO_36 ), 0, 0, 0 );

	// Get the stroy from a file...
	std::fstream file( UBD_PREFIX "/config/story.dat", std::ios::in );
	
	std::vector<std::string> lines;

	std::string temp;
	getline( file, temp );

	while( !file.eof( ) )
	{
		lines.push_back( temp );
		getline( file, temp );
	}

	SDL_Event event;
	while( true )
	{
		while( SDL_PollEvent(&event) )
		{
			if( event.type == SDL_QUIT )
			{
				app->FadeTo( 100 );
				return QUIT_STATE;
			}
			else if( event.type == SDL_KEYDOWN )
			{
				if( event.key.keysym.sym == SDLK_ESCAPE )
				{
					app->FadeTo( 100 );
					return MENU_STATE;
				}
			}
			else if( event.type == SDL_MOUSEBUTTONDOWN )
			{
				menu.HandleMouseDown( event.button.x, event.button.y );
				quit.HandleMouseDown( event.button.x, event.button.y );
			}
			else if( event.type == SDL_MOUSEBUTTONUP )
			{
				if( menu.HandleMouseUp( event.button.x, event.button.y ) )
				{
					app->PlaySound( BUTTON_NOISE );
					app->FadeTo( 100 );
					return MENU_STATE;
				}
				
				if( quit.HandleMouseUp( event.button.x, event.button.y ) )
				{
					app->PlaySound( BUTTON_NOISE );
					app->FadeTo( 100 );
					return QUIT_STATE;
				}
			}
		}

		app->Clear( 0, 0, 0 );
		SDL_BlitSurface( bg.image, NULL, app->screen, NULL );

		app->text_writer.WriteText( app->screen, GALAPOGO_72, "Story", 635, 0, 0, 0, 0 );

		// Draw story text...
		for( Uint32 i=0; i<lines.size( ); i++ )
		{
			app->text_writer.WriteText( app->screen, PLAIN_FONT_14, (char*)lines[i].c_str( ), 5, 15 + i*20, 0, 0, 0 );
		}

		menu.Draw( app->screen );
		quit.Draw( app->screen );

		app->Flip( );
	}
}





