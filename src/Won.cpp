// Won.cpp
// Copyright Ian Finlayson 2010
// This is part of UltraBear1 distributed under the MIT
// Implements the won screen...

#include "SimTimer.h"
#include "SimImage.h"
#include "SimSprite.h"
#include "SimButton.h"

#include "App.h"
#include "Won.h"
#include "Fireworks.h"
#include "prefix.h"


Ultra1::StateNumber Ultra1::WonState::Run( )
{
	SDL_ShowCursor( true );
	SDL_Event event;
	std::vector<Firework> fs( 25 );
	Sim::Timer timer;

	Sim::Image bear_i( UBD_PREFIX "/images/bear.png", 0, 0, 255 );
	Sim::Image other_i( bear_i.GetMirroredX( ) );
	Sim::Image ground( UBD_PREFIX "/images/ground.png" );
	SDL_Rect ground_place = {0, 600 - ground.image->h, 800, ground.image->h};

	Sim::Sprite bear( 10, 480, 20, 40, 2 );
	bear.AddAnimation( 0, 0, 3, true, bear_i.image, 125, true );
	bear.AddAnimation( 260, 0, 3, false, other_i.image, 125, true, 1 );
	bear.SetDx( 200.0 );

	// Buttons
	Sim::Image but( UBD_PREFIX "/images/buttonsmall.png", 255, 0, 0 );
	
	Sim::Button quit( 230, 540, 217, 35, 3, 0, 0, 0, 10, 3, true );
	quit.SetBackGround( but.image );
	quit.SetForeGround( "Quit", app->text_writer.GetFont( GALAPOGO_24 ), 0, 0, 0 );
	
	Sim::Button menu( 0, 540, 217, 35, 3, 0, 0, 0, 10, 3, true );
	menu.SetBackGround( but.image );
	menu.SetForeGround( "Main Menu", app->text_writer.GetFont( GALAPOGO_24 ), 0, 0, 0 );

	// skip past a few seconds so they are not
	// synchronized!
	for( unsigned int i=0; i<fs.size( ); ++i )
	{
		fs[i].Update( 2.0 );
	}


	while( true )
	{
		while( SDL_PollEvent(&event) )
		{
			if( event.type == SDL_QUIT )
			{
				return QUIT_STATE;
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
					return MENU_STATE;
				}
				else if( quit.HandleMouseUp( event.button.x, event.button.y ) )
				{
					app->PlaySound( BUTTON_NOISE );
					return QUIT_STATE;
				}
			}
		}

		app->Clear( 0, 0, 0 );

		timer.Update( );

		// Update bear
		bear.Update( );
		if( bear.GetPosition( ).x > 780 )
		{
			bear.SetDx( -200.0 );
			bear.SetAnimation( 1 );
		}
		else if( bear.GetPosition( ).x < 20 )
		{
			bear.SetDx( 200.0 );
			bear.SetAnimation( 0 );
		}

		SDL_BlitSurface( ground.image, NULL, app->screen, &ground_place );
		bear.Draw( app->screen );

		float sex = timer.GetMSsinceLastFrame( ) / 1000.0f;
		for( unsigned int i=0; i<fs.size( ); ++i )
		{
			fs[i].Update( sex );
			fs[i].Render( app->screen );
		}

		app->text_writer.WriteText( app->screen, GALAPOGO_72, "Congratsulations!", 10, 10, 128, 128, 255 );

		app->text_writer.WriteText( app->screen, PLAIN_FONT_14, "You have successfully helped Ultra Bear south."
			" You led him to the Evil Penguin Kings castle and walked away victorious.", 10, 100, 255, 255, 255 );
		
		app->text_writer.WriteText( app->screen, PLAIN_FONT_14, "No longer will smart ass people be able to"
			" point out that there are no polar bears in Antarctica and that they dont", 10, 125, 255, 255, 255 );

		app->text_writer.WriteText( app->screen, PLAIN_FONT_14, "encounter penguins. Because you did it! This is"
			" going to be huge for you. This will improve your whole life. Not many", 10, 150, 255, 255, 255 );

		app->text_writer.WriteText( app->screen, PLAIN_FONT_14, "people have beaten this game. Of course, not"
			" many have tried, but it is still quite impressive.", 10, 175, 255, 255, 255 );


		app->text_writer.WriteText( app->screen, PLAIN_FONT_14, "After spending a relaxing week in Antarctica,"
			" Ultra Bear hijacked a sea plane and promptly crashed it into the ocean.", 10, 225, 255, 255, 255 );

		app->text_writer.WriteText( app->screen, PLAIN_FONT_14, "Then he began the long walk home. He was going"
			" to bring the Evil Penguin Kings crown back back as a souvenir, but", 10, 250, 255, 255, 255 );

		app->text_writer.WriteText( app->screen, PLAIN_FONT_14, "he had to pawn it in Calcutta for food money.", 10, 275, 255, 255, 255 );


		app->text_writer.WriteText( app->screen, PLAIN_FONT_14, "Look out for Ultra Bear in future games from Simian Studios!", 10, 325, 255, 255, 255 );

		menu.Draw( app->screen );
		quit.Draw( app->screen );

		app->Flip( );
	}

	
	return MENU_STATE;
}









