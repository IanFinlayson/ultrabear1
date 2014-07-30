// SLDialogs.cpp
// Copyright Ian Finlayson 2010
// This is part of UltraBear1 distributed under the MIT
// Dialogs for saving and loading games...

#include <string>
#include <fstream>

#include "SimImage.h"
#include "SimButton.h"
#include "SimTextField.h"

#include "SLDialogs.h"
#include "prefix.h"

namespace Ultra1
{
	void Save( App* app, std::string name, int slot )
	{
		srand( SDL_GetTicks( ) );

		// Put out the name...
		char filename[64];
#ifdef WIN32
		sprintf( filename, "%s/.ultrabear1/games/%i.ub1g", getenv("USERPROFILE"), slot+1 );
#else
		sprintf( filename, "%s/.ultrabear1/games/%i.ub1g", getenv("HOME"), slot+1 );
#endif
		std::fstream file( filename, std::ios::out | std::ios::binary );

		// Construct the 25 char string...
		Uint8 buff[64];
		for( Uint8 i=0; i<name.size( ); i++ )
		{
			buff[i] = name[i];
		}
		for( size_t i=name.size( ); i<25; i++ )
		{
			buff[i] = 0;
		}

		// Write the name...
		for( int i=0; i<25; i++ )
		{
			file.write( (char*)(buff+i), 1 );
		}

		// Write 23 random bytes...
		for( int i=0; i<23; i++ )
		{
			Uint8 t = rand( ) % 255;
			file.write( (char*)&t, 1 );
		}

		// Write the lives...
		Sint32 lives = app->stats.lives;
		file.write( (char*)&lives, 4 );

		// Write 16 random bytes...
		for( int i=0; i<16; i++ )
		{
			Uint8 t = rand( ) % 255;
			file.write( (char*)&t, 1 );
		}

		// Write the coins...
		Sint32 coins = app->stats.coins;
		file.write( (char*)&coins, 4 );

		// Write 31 random bytes...
		for( int i=0; i<31; i++ )
		{
			Uint8 t = rand( ) % 255;
			file.write( (char*)&t, 1 );
		}

		// Write the points...
		Sint32 points = app->stats.points;
		file.write( (char*)&points, 4 );

		// Write 63 random bytes...
		for( int i=0; i<63; i++ )
		{
			Uint8 t = rand( ) % 255;
			file.write( (char*)&t, 1 );
		}

		// Write the curr map and level...
		Sint32 maplev = app->stats.current_map;
		file.write( (char*)&maplev, 4 );
		maplev = app->stats.current_level;
		file.write( (char*)&maplev, 4 );
		
		// Write 41 random bytes...
		for( int i=0; i<41; i++ )
		{
			Uint8 t = rand( ) % 255;
			file.write( (char*)&t, 1 );
		}

		// Write the curr next...
		Sint32 currnext = app->stats.curr_level_next;
		file.write( (char*)&currnext, 4 );

		// Write 27 random bytes...
		for( int i=0; i<27; i++ )
		{
			Uint8 t = rand( ) % 255;
			file.write( (char*)&t, 1 );
		}

		file.close( );
	}

	bool Load( App* app, int slot )
	{
		// Open the file
		char filename[64];
#ifdef WIN32
		sprintf( filename, "%s/.ultrabear1/games/%i.ub1g", getenv("USERPROFILE"), slot+1 );
#else
		sprintf( filename, "%s/.ultrabear1/games/%i.ub1g", getenv("HOME"), slot+1 );
#endif
		std::fstream file( filename, std::ios::in | std::ios::binary );

		Uint8 namebuffer[25];
		for( int i=0; i<25; i++ )
		{
			file.read( (char*)namebuffer+i, 1 );
		}

		if( strcmp((const char*)namebuffer, "Empty") == 0 )
		{
			return false;	// No data to load...
		}

		// 23 trash
		Uint8 trash;
		for( int i=0; i<23; i++ )
		{
			file.read( (char*)&trash, 1 );
		}

		// lives
		Sint32 lives;
		file.read( (char*)&lives, 4 );
		app->stats.lives = lives;

		// 16 trash
		for( int i=0; i<16; i++ )
		{
			file.read( (char*)&trash, 1 );
		}

		// coins
		Sint32 coins;
		file.read( (char*)&coins, 4 );
		app->stats.coins = coins;

		// 31 trash
		for( int i=0; i<31; i++ )
		{
			file.read( (char*)&trash, 1 );
		}

		// points
		Uint32 points;
		file.read( (char*)&points, 4 );
		app->stats.points = points;

		// 63 trash
		for( int i=0; i<63; i++ )
		{
			file.read( (char*)&trash, 1 );
		}

		// map and level...
		Sint32 maplev;
		file.read( (char*)&maplev, 4 );
		app->stats.current_map = maplev;
		file.read( (char*)&maplev, 4 );
		app->stats.current_level = maplev;

		// 41 trash
		for( int i=0; i<41; i++ )
		{
			file.read( (char*)&trash, 1 );
		}

		// points
		Sint32 currnext;
		file.read( (char*)&currnext, 4 );
		app->stats.curr_level_next = currnext;

		file.close( );

		// Do movement values...
		app->stats.back_up = false;
		app->stats.moveon = false;
		app->stats.stay = true;

		return true;
	}

	// The group of buttons that have the names written on them...
	class NameButtons
	{
	private:
		Sim::Button* buttons[10];	// Representation

		typedef char Name[128];
		Name names[10];		// The name of the save slot...

		int current_selection;

	public:
		NameButtons( App* app )
		{

			// For each slot
			for( int i=0; i<10; i++ )
			{

				// Open the file to read the name...
				char filename[256];
#ifdef WIN32
				sprintf( filename, "%s/.ultrabear1/games/%i.ub1g", getenv("USERPROFILE"), i+1 );
#else
				sprintf( filename, "%s/.ultrabear1/games/%i.ub1g", getenv("HOME"), i+1 );
#endif
				std::fstream file( filename, std::ios::in | std::ios::binary );

				// Read the name out...
				Uint8 temp = 1;
				int j = 0;
				while( temp && (j<25) )
				{
					file.read( (char*)&temp, 1 );

					names[i][j] = temp;

					j++;
				}
			}
			
			// Construct the buttons
			for( int i=0; i<10; i++ )
			{
				buttons[i] = new Sim::Button( 120, 107+i*28, 560, 25, 0, 0, 0, 0, 1, 0 );
				buttons[i]->SetBackGround( 200, 200, 200 );
				buttons[i]->SetForeGround( names[i], app->text_writer.GetFont( PLAIN_FONT_14 ), 0, 0, 0 );
			}

			// First is selected...
			current_selection = 0;
		}
		~NameButtons( )
		{
			for( int i=0; i<10; i++ )
				delete buttons[i];

		}
		std::string GetSelectedText( )
		{
			std::string sel_name = names[current_selection];
			return sel_name;			
		}
		int GetSlotChosen( )
		{
			return current_selection;
		}
		void OnMouseDown( int mx, int my )
		{
			for( int i=0; i<10; i++ )
			{
				buttons[i]->HandleMouseDown( mx, my );
			}
		}
		bool OnMouseUp( int mx, int my )
		{
			for( int i=0; i<10; i++ )
			{
				if( buttons[i]->HandleMouseUp( mx, my ) )
				{
					current_selection = i;
					return true;
				}
			}

			return false;
		}
		bool OnKeyDown( SDLKey key )	// returns true if enter was hit...
		{
			if( key == SDLK_UP )
			{
				current_selection--;
				if( current_selection < 0 )
				{
					current_selection = 9;
				}
			}
			else if( key == SDLK_DOWN )
			{
				current_selection = (current_selection + 1) % 10;
			}
			
			return (key == SDLK_RETURN);
		}
		void Draw( SDL_Surface* screen )
		{
			// We show it is selected by changing its color!
			buttons[current_selection]->ChangeBackColor( 75, 75, 250 );

			for( int i=0; i<10; i++ )
			{
				buttons[i]->Draw( screen );
			}
			
			buttons[current_selection]->ChangeBackColor( 200, 200, 200 );
		}

	};
}


bool Ultra1::SaveDialog( App* app )
{
	Sim::Image back = app->screen;
	Sim::Image but( UBD_PREFIX "/images/buttonsmall.png", 255, 0, 0 );

	SDL_Rect barea = {99, 49, 602, 452};
	SDL_Rect sarea = {100, 50, 600, 450};

	NameButtons buts( app );

	Sim::Button save( 100, 450, 217, 35, 3, 0, 0, 0, 10, 3, true );
	save.SetBackGround( but.image );
	save.SetForeGround( "Save", app->text_writer.GetFont( GALAPOGO_24 ), 0, 0, 0 );
	
	Sim::Button cancel( 320, 450, 217, 35, 3, 0, 0, 0, 10, 3, true );
	cancel.SetBackGround( but.image );
	cancel.SetForeGround( "Cancel", app->text_writer.GetFont( GALAPOGO_24 ), 0, 0, 0 );

	Sim::TextField text( 120, 400, 560, 30, 1, 0, 0, 0, app->text_writer.GetFont(PLAIN_FONT_14), 24, 220, 220, 255, 0, 0, 0, 1, 0, "", false );

	// Set normal typing repeat rate
	SDL_EnableKeyRepeat( SDL_DEFAULT_REPEAT_DELAY, SDL_DEFAULT_REPEAT_INTERVAL );

	// Fool the text field into accepting focus...
	text.HandleMouseDown( 124, 405 );
	text.HandleMouseUp( 124, 405 );

	text.SetText( buts.GetSelectedText( ) );

	SDL_Event event;
	while( true )
	{
		if( SDL_PollEvent(&event) )
		{
			if( event.type == SDL_MOUSEBUTTONDOWN )
			{
				buts.OnMouseDown( event.button.x, event.button.y );
				save.HandleMouseDown( event.button.x, event.button.y );
				cancel.HandleMouseDown( event.button.x, event.button.y );
				text.HandleMouseDown( event.button.x, event.button.y );
			}
			else if( event.type == SDL_MOUSEBUTTONUP )
			{
				// User clicked a name...set the text to this ones text...
				if( buts.OnMouseUp( event.button.x, event.button.y ) )
				{
					// Clear the textfield if empty....set text if not
					if( buts.GetSelectedText( ) == "Empty" )
						text.SetText( "" );
					else
						text.SetText( buts.GetSelectedText( ) );

					// Give it focus...
					text.HandleMouseDown( 124, 405 );
					text.HandleMouseUp( 124, 405 );
				}
				else if( save.HandleMouseUp( event.button.x, event.button.y ) )
				{
					app->PlaySound( BUTTON_NOISE );
					Save( app, text.GetText( ), buts.GetSlotChosen( ) );
					
					// Reset very fast repeat rate...
					SDL_EnableKeyRepeat( SDL_DEFAULT_REPEAT_INTERVAL, SDL_DEFAULT_REPEAT_INTERVAL );
					return true;
				}
				else if( cancel.HandleMouseUp( event.button.x, event.button.y ) )
				{
					app->PlaySound( BUTTON_NOISE );
					// Reset very fast repeat rate...
					SDL_EnableKeyRepeat( SDL_DEFAULT_REPEAT_INTERVAL, SDL_DEFAULT_REPEAT_INTERVAL );
					return false;	
				}
				else
				{
					text.HandleMouseUp( event.button.x, event.button.y );
				}
			}
			else if( event.type == SDL_KEYDOWN )
			{
				if( (event.key.keysym.sym == SDLK_UP) || (event.key.keysym.sym == SDLK_DOWN) )
				{
					buts.OnKeyDown( event.key.keysym.sym );
					
					// Clear the textfield if empty....set text if not
					if( buts.GetSelectedText( ) == "Empty" )
						text.SetText( "" );
					else
						text.SetText( buts.GetSelectedText( ) );
					
					// Give it focus...
					text.HandleMouseDown( 124, 405 );
					text.HandleMouseUp( 124, 405 );
				}
				else if( text.HandleKeyDown( event.key.keysym ) )
				{
					// User hit Enter...Lets Save it!
					Save( app, text.GetText( ), buts.GetSlotChosen( ) );

					// Reset very fast repeat rate...
					SDL_EnableKeyRepeat( SDL_DEFAULT_REPEAT_INTERVAL, SDL_DEFAULT_REPEAT_INTERVAL );
					return true;
				}
			}
		}

		app->Clear( 0, 0, 0 );
		
		// Whatever was on the screen...
		SDL_BlitSurface( back.image, NULL, app->screen, NULL );

		// The shaded region in the center
		SDL_FillRect( app->screen, &barea, SDL_MapRGB( app->screen->format, 0, 0, 0 ) );
		SDL_FillRect( app->screen, &sarea, SDL_MapRGB( app->screen->format, 175, 175, 255 ) );

		app->text_writer.WriteText( app->screen, GALAPOGO_36, "Save Game", 110, 52, 0, 0, 0 );
		buts.Draw( app->screen );
		save.Draw( app->screen );
		cancel.Draw( app->screen );
		text.Draw( app->screen );

		app->Flip( );
	}

	// Reset very fast repeat rate...
	SDL_EnableKeyRepeat( SDL_DEFAULT_REPEAT_INTERVAL, SDL_DEFAULT_REPEAT_INTERVAL );
  return false;
}

bool Ultra1::LoadDialog( App* app )
{
	// Set normal typing repeat rate
	SDL_EnableKeyRepeat( SDL_DEFAULT_REPEAT_DELAY, SDL_DEFAULT_REPEAT_INTERVAL );

	Sim::Image back = app->screen;
	Sim::Image but( UBD_PREFIX "/images/buttonsmall.png", 255, 0, 0 );

	SDL_Rect barea = {99, 49, 602, 452};
	SDL_Rect sarea = {100, 50, 600, 450};

	NameButtons buts( app );

	Sim::Button load( 100, 450, 217, 35, 3, 0, 0, 0, 10, 3, true );
	load.SetBackGround( but.image );
	load.SetForeGround( "Load", app->text_writer.GetFont( GALAPOGO_24 ), 0, 0, 0 );
	
	Sim::Button cancel( 320, 450, 217, 35, 3, 0, 0, 0, 10, 3, true );
	cancel.SetBackGround( but.image );
	cancel.SetForeGround( "Cancel", app->text_writer.GetFont( GALAPOGO_24 ), 0, 0, 0 );

	SDL_Event event;
	while( true )
	{
		if( SDL_PollEvent(&event) )
		{
			if( event.type == SDL_MOUSEBUTTONDOWN )
			{
				buts.OnMouseDown( event.button.x, event.button.y );
				load.HandleMouseDown( event.button.x, event.button.y );
				cancel.HandleMouseDown( event.button.x, event.button.y );
			}
			else if( event.type == SDL_MOUSEBUTTONUP )
			{
				buts.OnMouseUp( event.button.x, event.button.y );
				
				if( load.HandleMouseUp( event.button.x, event.button.y ) )
				{
					app->PlaySound( BUTTON_NOISE );
					// Reset very fast repeat rate...
					SDL_EnableKeyRepeat( SDL_DEFAULT_REPEAT_INTERVAL, SDL_DEFAULT_REPEAT_INTERVAL );
					return Load( app, buts.GetSlotChosen( ) );
				}
				if( cancel.HandleMouseUp( event.button.x, event.button.y ) )
				{
					app->PlaySound( BUTTON_NOISE );
					// Reset very fast repeat rate...
					SDL_EnableKeyRepeat( SDL_DEFAULT_REPEAT_INTERVAL, SDL_DEFAULT_REPEAT_INTERVAL );
					return false;	
				}
			}
			else if( event.type == SDL_KEYDOWN )
			{
				if( buts.OnKeyDown( event.key.keysym.sym ) )
				{
					// Reset very fast repeat rate...
					SDL_EnableKeyRepeat( SDL_DEFAULT_REPEAT_INTERVAL, SDL_DEFAULT_REPEAT_INTERVAL );

					// User selected one...
					return Load( app, buts.GetSlotChosen( ) );
				}
			}
		}

		app->Clear( 0, 0, 0 );
		
		// Whatever was on the screen...
		SDL_BlitSurface( back.image, NULL, app->screen, NULL );

		// The shaded region in the center
		SDL_FillRect( app->screen, &barea, SDL_MapRGB( app->screen->format, 0, 0, 0 ) );
		SDL_FillRect( app->screen, &sarea, SDL_MapRGB( app->screen->format, 175, 175, 255 ) );

		app->text_writer.WriteText( app->screen, GALAPOGO_36, "Load Game", 110, 52, 0, 0, 0 );
		buts.Draw( app->screen );
		load.Draw( app->screen );
		cancel.Draw( app->screen );

		app->Flip( );
	}

	
	// Reset very fast repeat rate...
	SDL_EnableKeyRepeat( SDL_DEFAULT_REPEAT_INTERVAL, SDL_DEFAULT_REPEAT_INTERVAL );

	return true;
}




