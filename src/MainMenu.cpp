// Menu.cpp
// Copyright Ian Finlayson 2010
// This is part of UltraBear1 distributed under the MIT
// Implements the in-game main menu...

#include "App.h"
#include "MainMenu.h"
#include "SLDialogs.h"

#include "SimButton.h"
#include "SimImage.h"
#include "prefix.h"

Ultra1::StateNumber Ultra1::MainMenu::Run( )
{
	SDL_ShowCursor( true );

	SDL_Event event;

	Sim::Image bg( UBD_PREFIX "/images/default.jpg" );
	Sim::Image bear( UBD_PREFIX "/images/bigbear.png", 0, 0, 255 );
	Sim::Image but( UBD_PREFIX "/images/button.png", 255, 0, 0 );

	SDL_Rect bear_pos = {20, 70, bear.image->w, bear.image->h};

	Sim::Button new_game( 300, 100, 450, 50, 3, 0,0,0, 40, 7, true );
	new_game.SetBackGround( but.image );
	new_game.SetForeGround( "New Game", app->text_writer.GetFont(GALAPOGO_36), 0, 0, 0 );

	Sim::Button load_game( 300, 160, 450, 50, 3, 0,0,0, 40, 7, true );
	load_game.SetBackGround( but.image );
	load_game.SetForeGround( "Load Game", app->text_writer.GetFont(GALAPOGO_36), 0, 0, 0 );

	Sim::Button help( 300, 220, 450, 50, 3, 0,0,0, 40, 7, true );
	help.SetBackGround( but.image );
	help.SetForeGround( "Help", app->text_writer.GetFont(GALAPOGO_36), 0, 0, 0 );

	Sim::Button options( 300,280, 450, 50, 3, 0,0,0, 40, 7, true );
	options.SetBackGround( but.image );
	options.SetForeGround( "Options", app->text_writer.GetFont(GALAPOGO_36), 0, 0, 0 );

	Sim::Button story( 300, 340, 450, 50, 3, 0,0,0, 40, 7, true );
	story.SetBackGround( but.image );
	story.SetForeGround( "Story", app->text_writer.GetFont(GALAPOGO_36), 0, 0, 0 );

	Sim::Button quit( 300, 400, 450, 50, 3, 0,0,0, 40, 7, true );
	quit.SetBackGround( but.image );
	quit.SetForeGround( "Quit", app->text_writer.GetFont(GALAPOGO_36), 0, 0, 0 );

//	Sim::Button quit( 300, 460, 450, 50, 3, 0,0,0, 40, 7, true );
//	quit.SetBackGround( but.image );
//	quit.SetForeGround( "Quit", app->text_writer.GetFont(GALAPOGO_36), 0, 0, 0 );

	while( true )
	{
		if( SDL_PollEvent(&event) )
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
					return QUIT_STATE;
				}
			}
			else if( event.type == SDL_MOUSEBUTTONDOWN )
			{
				new_game.HandleMouseDown( event.button.x, event.button.y );
				load_game.HandleMouseDown( event.button.x, event.button.y );
				help.HandleMouseDown( event.button.x, event.button.y );
				options.HandleMouseDown( event.button.x, event.button.y );
				story.HandleMouseDown( event.button.x, event.button.y );
				quit.HandleMouseDown( event.button.x, event.button.y );
			}
			else if( event.type == SDL_MOUSEBUTTONUP )
			{
				if( new_game.HandleMouseUp( event.button.x, event.button.y ) )	// new game
				{
					app->PlaySound( BUTTON_NOISE );
					// Default values for app...
					app->stats.lives = 5;
					app->stats.coins = 0;
					app->stats.points = 0;
					app->stats.current_map = 1;
					app->stats.current_level = 1;
					app->stats.back_up = false;
					app->stats.stay = false;
					app->stats.moveon = false;
					app->stats.curr_level_next = 1;
					app->stats.came_from_main = true;


					app->FadeTo( 100 );
					return MAP_STATE;
				}
				else if( load_game.HandleMouseUp( event.button.x, event.button.y ) )	// load game
				{
					app->PlaySound( BUTTON_NOISE );
					if( LoadDialog( app ) )
					{
						app->stats.came_from_main = true;

						app->FadeTo( 100 );
						return MAP_STATE;
					}
				}
				else if( help.HandleMouseUp( event.button.x, event.button.y ) )		//help
				{
					app->PlaySound( BUTTON_NOISE );
					app->FadeTo( 100 );
					return HELP_STATE;	
				}
				else if( options.HandleMouseUp( event.button.x, event.button.y ) )	// options
				{
					app->PlaySound( BUTTON_NOISE );
					app->FadeTo( 100 );
					return OPTIONS_STATE;
				}
				else if( story.HandleMouseUp( event.button.x, event.button.y ) )		// story
				{
					app->PlaySound( BUTTON_NOISE );
					app->FadeTo( 100 );
					return STORY_STATE;
				}
				else if( quit.HandleMouseUp( event.button.x, event.button.y ) )		// quit
				{
					app->PlaySound( BUTTON_NOISE );
					app->FadeTo( 100 );
					return QUIT_STATE;
				}
			}
		}

		app->Clear( 255, 255, 255 );

		SDL_BlitSurface( bg.image, NULL, app->screen, NULL );
		SDL_BlitSurface( bear.image, NULL, app->screen, &bear_pos );
		app->text_writer.WriteText( app->screen, GALAPOGO_72, "Main Menu", 310, 20, 0,0,0 );

		new_game.Draw( app->screen );
		load_game.Draw( app->screen );
		help.Draw( app->screen );
		options.Draw( app->screen );
		story.Draw( app->screen );
		quit.Draw( app->screen );

		app->Flip( );
	}

	app->FadeTo( 300 );
	return MAP_STATE;
}





