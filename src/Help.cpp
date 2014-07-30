// Help.cpp
// Copyright Ian Finlayson 2010
// This is part of UltraBear1 distributed under the MIT
// Implements the help screen

#include "App.h"
#include "Help.h"

#include "SimButton.h"
#include "SimSprite.h"
#include "SimImage.h"
#include "prefix.h"

Ultra1::StateNumber Ultra1::HelpState::Run( )
{
	Sim::Image bg( UBD_PREFIX "/images/mountains.jpg" );	
	Sim::Image but( UBD_PREFIX "/images/button.png", 255, 0, 0 );
		
	Sim::Button menu( 0, 480, 450, 50, 3, 0, 0, 0, 40, 7, true );
	menu.SetBackGround( but.image );
	menu.SetForeGround( "Main Menu", app->text_writer.GetFont( GALAPOGO_36 ), 0, 0, 0 );
	
	Sim::Button quit( 0, 540, 450, 50, 3, 0, 0, 0, 40, 7, true );
	quit.SetBackGround( but.image );
	quit.SetForeGround( "Quit", app->text_writer.GetFont( GALAPOGO_36 ), 0, 0, 0 );

	Sim::Image bear_i( UBD_PREFIX "/images/bear.png", 0, 0, 255 );
	Sim::Sprite bear( 10, 130, 20, 40, 1 );
	bear.AddAnimation( 0, 0, 3, true, bear_i.image, 200, true );

	Sim::Image armor_i( UBD_PREFIX "/images/armor.png", 0, 0, 255 );
	Sim::Sprite armor( 10, 190, 20, 20, 1 );
	armor.AddAnimation( 0, 0, 2, true, armor_i.image, 125, false );

	Sim::Image force_i( UBD_PREFIX "/images/force.png", 0, 0, 255 );
	Sim::Sprite force( 10, 230, 20, 20, 1 );
	force.AddAnimation( 0, 0, 2, true, force_i.image, 125, false );

	Sim::Image life_i( UBD_PREFIX "/images/extralife.png", 0, 0, 255 );
	Sim::Sprite life( 10, 270, 20, 20, 1 );
	life.AddAnimation( 0, 0, 2, true, life_i.image, 125, false );

	Sim::Image coin_i( UBD_PREFIX "/images/coin.png", 0, 0, 255 );
	Sim::Sprite coin( 10, 310, 20, 20, 1 );
	coin.AddAnimation( 0, 0, 3, true, coin_i.image, 125, false );

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

		bear.Update( );
		armor.Update( );
		force.Update( );
		life.Update( );
		coin.Update( );

		app->Clear( 0, 0, 0 );
		SDL_BlitSurface( bg.image, NULL, app->screen, NULL );

		app->text_writer.WriteText( app->screen, GALAPOGO_72, "Help", 10, 0, 0, 0, 0 );

		// Write basic info at top...
		app->text_writer.WriteText( app->screen, PLAIN_FONT_14, "In this game, you must guide Ultra Bear to the South Pole by working through every level on the map.", 10, 65, 0, 0, 0 );
		app->text_writer.WriteText( app->screen, PLAIN_FONT_14, "To beat a level, you must move Ultra Bear to the right while avoiding all of the enemies. You can kill", 10, 82, 0, 0, 0 );
		app->text_writer.WriteText( app->screen, PLAIN_FONT_14, "enemies by bouncing on their heads. Here are a few things that you will encounter:", 10, 99, 0,0,0 );

		// Info beside UB and crew...
		app->text_writer.WriteText( app->screen, PLAIN_FONT_14, "Ultra Bear. This is the bear you must guide south. He is very Ultra.", 50, 139, 0, 0, 0 );
		app->text_writer.WriteText( app->screen, PLAIN_FONT_14, "Armor. This pickup will protect Ultra Bear from one blow by an enemy.", 50, 190, 0, 0, 0 );
		app->text_writer.WriteText( app->screen, PLAIN_FONT_14, "Force. This magic force field will eliminate all enemies Ultra Bear touches. It will wear off though.", 50, 230, 0, 0, 0 );
		app->text_writer.WriteText( app->screen, PLAIN_FONT_14, "Extra Life. This pickup will credit Ultra Bear with one extra life.", 50, 270, 0, 0, 0 );
		app->text_writer.WriteText( app->screen, PLAIN_FONT_14, "Coin. This pickup deposits one coin in Ultra Bear's account. Once he has 100, he can trade them in for an extra life.", 50, 310, 0, 0, 0 );
		app->text_writer.WriteText( app->screen, PLAIN_FONT_14, "The controls can be configured by clicking Options from the Main Menu", 10, 380, 0, 0, 0 );



		menu.Draw( app->screen );
		quit.Draw( app->screen );
		bear.Draw( app->screen );
		armor.Draw( app->screen );
		force.Draw( app->screen );
		life.Draw( app->screen );
		coin.Draw( app->screen );

		app->Flip( );
	}
}








