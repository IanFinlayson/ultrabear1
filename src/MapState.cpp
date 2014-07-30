// MapState.cpp
// Copyright Ian Finlayson 2010
// This is part of UltraBear1 distributed under the MIT
// Implements the map game state

#include <iostream>
#include <SDL/SDL.h>
#include "SimTimer.h"
#include "SimException.h"
#include "SimVector.h"
#include "SimButton.h"

#include "App.h"
#include "MapState.h"
#include "Map.h"
#include "SLDialogs.h"
#include "prefix.h"


void MoveBear( Sim::Sprite* the_bear, Ultra1::App* app, Ultra1::Map* the_map, int map1, int map2, Sim::Button& b1, Sim::Button& b2 )
{
	int x1 = the_map->info[map1].x - 10;
	int y1 = the_map->info[map1].y - 35;

	int x2 = the_map->info[map2].x - 10;
	int y2 = the_map->info[map2].y - 35;

	the_bear->SetPosition(  x1, y1 );
	
	Sim::Vector<float, 2> velocity;
	float speed = 300.0f;

	velocity[0] = (float)( x2 - x1);
	velocity[1] = (float)( y2 - y1);

	// Adjust the bear's direction...
	if( velocity[0] > 0 )
		the_bear->SetAnimation( 0 );
	else
		the_bear->SetAnimation( 1 );
	
	// We calculate the time needed to take the bear there...
	float dist = sqrt( (velocity[0]*velocity[0]) + (velocity[1]*velocity[1]) );
    float time = (dist / speed);
	
	// seconds -> miliseconds
	time *= 1000.0f;

	unsigned int timer = SDL_GetTicks( );

	velocity.Normalize( );
	velocity[0] = velocity[0] * speed;
	velocity[1] = velocity[1] * speed;

	the_bear->SetMovement( velocity[0], velocity[1] );

	Sim::Timer ti;
	SDL_Event e;
	while( (SDL_GetTicks( ) - timer) < time )
	{
		// Check for horizontal overshoot...
		if( velocity[0] > 0 )	// going ->
		{
			if( the_bear->GetPosition( ).x > x2 )
				break;
		}
		else	// goin  <-
		{
			if( the_bear->GetPosition( ).x < x2 )
				break;
		}
		
		// Check for vertical overshoot...
		if( velocity[1] > 0 )	// going   \/
		{
			if( the_bear->GetPosition( ).y > y2 )
				break;
		}
		else	// goin  ^
		{
			if( the_bear->GetPosition( ).y < y2 )
				break;
		}

		SDL_PollEvent(&e);
		ti.Update( );
		the_bear->Update( );
		the_map->Update( ti.GetMSsinceLastFrame( ) );

		app->Clear( 0, 0, 0 );
		the_map->Draw( app->screen );
		the_bear->Draw( app->screen );
		b1.Draw( app->screen );
		b2.Draw( app->screen );
		app->Flip( );
	}

	the_bear->SetPosition( x2, y2 );
	the_bear->SetMovement( 0.0f, 0.0f );
}

// This function presents the user with the option of
// saving if they tried to quit.
// returns whether or not they want to save.
bool SaveOption( Ultra1::App* app )
{
	Sim::Image back = app->screen;
	Sim::Image but( UBD_PREFIX "/images/buttonsmall.png", 255, 0, 0 );

	SDL_Rect barea = {149, 149, 502, 252};
	SDL_Rect sarea = {150, 150, 500, 250};


	Sim::Button save( 150, 357, 217, 35, 3, 0, 0, 0, 10, 3, true );
	save.SetBackGround( but.image );
	save.SetForeGround( "Save", app->text_writer.GetFont( Ultra1::GALAPOGO_24 ), 0, 0, 0 );
	
	Sim::Button quit( 420, 357, 217, 35, 3, 0, 0, 0, 10, 3, true );
	quit.SetBackGround( but.image );
	quit.SetForeGround( "Quit", app->text_writer.GetFont( Ultra1::GALAPOGO_24 ), 0, 0, 0 );


	SDL_Event event;
	while( true )
	{
		if( SDL_PollEvent(&event) )
		{
			if( event.type == SDL_MOUSEBUTTONDOWN )
			{
				save.HandleMouseDown( event.button.x, event.button.y );
				quit.HandleMouseDown( event.button.x, event.button.y );
			}
			else if( event.type == SDL_MOUSEBUTTONUP )
			{
				if( save.HandleMouseUp( event.button.x, event.button.y ) )
				{
					app->PlaySound( Ultra1::BUTTON_NOISE );
					return true;
				}
				else if( quit.HandleMouseUp( event.button.x, event.button.y ) )
				{
					app->PlaySound( Ultra1::BUTTON_NOISE );
					return false;	
				}
			}
		}

		app->Clear( 0, 0, 0 );
		
		// Whatever was on the screen...
		SDL_BlitSurface( back.image, NULL, app->screen, NULL );

		// The shaded region in the center
		SDL_FillRect( app->screen, &barea, SDL_MapRGB( app->screen->format, 0, 0, 0 ) );
		SDL_FillRect( app->screen, &sarea, SDL_MapRGB( app->screen->format, 175, 175, 255 ) );

		app->text_writer.WriteText( app->screen, Ultra1::GALAPOGO_36, "Warning", 155, 150, 0, 0, 0 );
		app->text_writer.WriteText( app->screen, Ultra1::PLAIN_FONT_14, "You have not saved recently. If you don't all progress will be lost.", 155, 190, 0, 0, 0 );
		app->text_writer.WriteText( app->screen, Ultra1::PLAIN_FONT_14, "Would you like to save before quitting?", 155, 320, 0, 0, 0 );
	
		save.Draw( app->screen );
		quit.Draw( app->screen );

		app->Flip( );
	}
}


// Runs the MapState
Ultra1::StateNumber Ultra1::MapState::Run( )
{
	bool just_saved;
	if( app->stats.came_from_main )
		just_saved = true;
	else
		just_saved = false;

	app->stats.came_from_main = false;

	SDL_ShowCursor( true );
	Map the_map( app->stats.current_map, app->stats.curr_level_next );

	Sim::Sprite bear( 0, 0, 20, 40, 2 );
	Sim::Image bear_image( UBD_PREFIX "/images/bear.png", 0, 0, 255 );
	Sim::Image bear_image_reversed( bear_image.GetMirroredX( ) );

	Sim::Image but( UBD_PREFIX "/images/buttonsmall.png", 255, 0, 0 );
	
	Sim::Button save( 0, 520, 217, 35, 3, 0, 0, 0, 10, 3, true );
	save.SetBackGround( but.image );
	save.SetForeGround( "Save", app->text_writer.GetFont( GALAPOGO_24 ), 0, 0, 0 );
	
	Sim::Button menu( 0, 560, 217, 35, 3, 0, 0, 0, 10, 3, true );
	menu.SetBackGround( but.image );
	menu.SetForeGround( "Main Menu", app->text_writer.GetFont( GALAPOGO_24 ), 0, 0, 0 );

	bear.AddAnimation( 0, 0, 3, true, bear_image.image, 250, true, 1 );
	bear.AddAnimation( 260, 0, 3, false, bear_image_reversed.image, 250, true, 1 );

	if( app->stats.stay )
	{
		app->stats.stay = false;
		bear.SetPosition( the_map.info[app->stats.current_level].x - 10, the_map.info[app->stats.current_level].y - 35 );
	}
	else if( app->stats.moveon )
	{
		app->stats.moveon = false;

		MoveBear( &bear, app, &the_map, app->stats.current_level-1, app->stats.current_level, menu, save );
	}
	else if( !app->stats.back_up )
	{
		MoveBear( &bear, app, &the_map, 0, 1, menu, save );
	}
	else
	{
		app->stats.back_up = false;
		MoveBear( &bear, app, &the_map, 6, 5, menu, save );
		app->stats.current_level = 5;
	}

	// Used to make UB go back or forward in the map progression...
	bool go_next = false;
	bool go_prev = false;

	SDL_Event event;
	Sim::Timer ti;
	unsigned int ticks = 0;

	while( true )
	{
		while( SDL_PollEvent( &event ) )
		{
			if( event.type == SDL_QUIT )
			{
				// we need to check if they have just saved or not!
				if( !just_saved )
				{
					if( SaveOption( app ) )
					{
						if( SaveDialog( app ) )
						{
							app->FadeTo( 100 );
							return MENU_STATE;
						}
						// else they hit cancel so don't Quit!
					}
					else
					{
						app->FadeTo( 100 );
						return MENU_STATE;
					}
				}
				else
				{
					app->FadeTo( 100 );
					return MENU_STATE;
				}
			}
			else if( event.type == SDL_MOUSEBUTTONDOWN )
			{
				save.HandleMouseDown( event.button.x, event.button.y );
				menu.HandleMouseDown( event.button.x, event.button.y );
			}
			else if( event.type == SDL_MOUSEBUTTONUP )
			{
				if( save.HandleMouseUp( event.button.x, event.button.y ) )
				{
					app->PlaySound( BUTTON_NOISE );
					just_saved = SaveDialog( app );
				}
				else if( menu.HandleMouseUp( event.button.x, event.button.y ) )
				{
					app->PlaySound( BUTTON_NOISE );
					// we need to check if they have just saved or not!
					if( !just_saved )
					{
						if( SaveOption( app ) )
						{
							if( SaveDialog( app ) )
							{
								app->FadeTo( 100 );
								return MENU_STATE;
							}
							// else they hit cancel so don't Quit!
						}
						else
						{
							app->FadeTo( 100 );
							return MENU_STATE;
						}
					}
					else
					{
						app->FadeTo( 100 );
						return MENU_STATE;
					}
				}
			}
			else if( (event.type == SDL_KEYDOWN) )
			{
				if( event.key.keysym.sym == app->options.left )
				{
					if( the_map.info[app->stats.current_level].next == WEST )
					{
						if( ((app->stats.current_map-1)*5 + (app->stats.current_level+1)) > app->stats.curr_level_next )
							continue;

						app->stats.current_level++;

						if( app->stats.current_level == 6 ) // We are going to the next map!
						{
							if( app->stats.current_map == 6 )
							{
								app->stats.current_level--;
								continue;
							}

							go_next = true;
						}

						MoveBear( &bear, app, &the_map, app->stats.current_level-1, app->stats.current_level, menu, save );
					}
					else if( the_map.info[app->stats.current_level-1].next == EAST )	// go back
					{
						if( (app->stats.current_level == 1) && (app->stats.current_map == 1) )
							continue;

						app->stats.current_level--;

						if( app->stats.current_level == 0 ) // We are going to a previous map
						{
							go_prev = true;
						}
 
						MoveBear( &bear, app, &the_map, app->stats.current_level+1, app->stats.current_level, menu, save );
					}
				}
				else if( event.key.keysym.sym == app->options.right )
				{
					if( the_map.info[app->stats.current_level].next == EAST )
					{
						if( ((app->stats.current_map-1)*5 + (app->stats.current_level+1)) > app->stats.curr_level_next )
							continue;

						app->stats.current_level++;

						if( app->stats.current_level == 6 ) // We are going to the next map!
						{
							if( app->stats.current_map == 6 )
							{
								app->stats.current_level--;
								continue;
							}

							go_next = true;
						}

						MoveBear( &bear, app, &the_map, app->stats.current_level-1, app->stats.current_level, menu, save );
					}
					else if( the_map.info[app->stats.current_level-1].next == WEST )	// go back
					{
						if( (app->stats.current_level == 1) && (app->stats.current_map == 1) )
							continue;

						app->stats.current_level--;
						
						if( app->stats.current_level == 0 ) // We are going to a previous level
						{
							go_prev = true;
						}
 
						MoveBear( &bear, app, &the_map, app->stats.current_level+1, app->stats.current_level, menu, save );
					}
				}
				else if( event.key.keysym.sym == app->options.up )
				{
					if( the_map.info[app->stats.current_level].next == NORTH )
					{
						if( ((app->stats.current_map-1)*5 + (app->stats.current_level+1)) > app->stats.curr_level_next )
							continue;

						app->stats.current_level++;
						
						if( app->stats.current_level == 6 ) // We are going to the next map!
						{
							if( app->stats.current_map == 6 )
							{
								app->stats.current_level--;
								continue;
							}

							go_next = true;
						}

						MoveBear( &bear, app, &the_map, app->stats.current_level-1, app->stats.current_level, menu, save );
					}
					else if( the_map.info[app->stats.current_level-1].next == SOUTH )	// go back
					{
						if( (app->stats.current_level == 1) && (app->stats.current_map == 1) )
							continue;

						app->stats.current_level--;
						
						if( app->stats.current_level == 0 ) // We are going to a previous level
						{
							go_prev = true;
						}
 
						MoveBear( &bear, app, &the_map, app->stats.current_level+1, app->stats.current_level, menu, save );
					}
				}
				else if( event.key.keysym.sym == app->options.down )
				{
					if( the_map.info[app->stats.current_level].next == SOUTH )
					{
						if( ((app->stats.current_map-1)*5 + (app->stats.current_level+1)) > app->stats.curr_level_next )
							continue;

						app->stats.current_level++;

						if( app->stats.current_level == 6 ) // We are going to the next map!
						{
							if( app->stats.current_map == 6 )
							{
								app->stats.current_level--;
								continue;
							}

							go_next = true;
						}

						MoveBear( &bear, app, &the_map, app->stats.current_level-1, app->stats.current_level, menu, save );
					}
					else if( the_map.info[app->stats.current_level-1].next == NORTH )	// go back
					{
						if( (app->stats.current_level == 1) && (app->stats.current_map == 1) )
							continue;

						app->stats.current_level--;
						
						if( app->stats.current_level == 0 ) // We are going to a previous level
						{
							go_prev = true;
						}
 
						MoveBear( &bear, app, &the_map, app->stats.current_level+1, app->stats.current_level, menu, save );
					}
				}
				else if( event.key.keysym.sym == SDLK_RETURN )
				{
					// Put the current level into the app and begin
					app->FadeTo( 100 );
					return GAME_STATE;
				}
				else if( event.key.keysym.sym == SDLK_ESCAPE )
				{
					// we need to check if they have just saved or not!
					if( !just_saved )
					{
						if( SaveOption( app ) )
						{
							if( SaveDialog( app ) )
							{
								app->FadeTo( 100 );
								return MENU_STATE;
							}
							// else they hit cancel so don't Quit!
						}
						else
						{
							app->FadeTo( 100 );
							return MENU_STATE;
						}
					}
					else
					{
						app->FadeTo( 100 );
						return MENU_STATE;
					}
				}
			}
		}
		
		ti.Update( );
		ticks = ti.GetMSsinceLastFrame( );


		if( go_prev )
		{
			go_prev = false;

			if( app->stats.current_map == 1 )
			{
				;// error cannot go back!
			}
			else
			{
				app->stats.current_map--;
				app->stats.current_level = 5;
				app->stats.back_up = true;
				return MAP_STATE;
			}
		}
		if( go_next )
		{
			go_next = false;

			if( app->stats.current_map == 6 )
			{
				// We won!
				app->stats.current_level = app->stats.current_map = 1;
				return WON_STATE;
			}
			else
			{
				app->stats.current_map++;
				app->stats.current_level = 1;
				app->stats.back_up = false;
				return MAP_STATE;
			}
		}

		bear.Update( );
		the_map.Update( ticks );

		app->Clear( 0, 0, 0 );
		the_map.Draw( app->screen );
		bear.Draw( app->screen );

		save.Draw( app->screen );
		menu.Draw( app->screen );

		app->Flip( );
	}
}


