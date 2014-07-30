// Game.cpp
// Copyright Ian Finlayson 2010
// This is part of UltraBear1 distributed under the MIT
// Runs the actual game...

#include <string>
#include <sstream>
#include <iostream>

#include "App.h"
#include "Game.h"
#include "Dusty.h"
#include "EntityList.h"

#include "SimTimer.h"
#include "SimException.h"

void Ultra1::DoDisplay( Ultra1::App* app, std::string& l, std::string& c, std::string& p )
{
	std::stringstream lifess, coinss, pointss;

	lifess << "Lives: " << app->stats.lives;
	coinss << "Coins: " << app->stats.coins;
	pointss << "Points: " << app->stats.points;

	l = lifess.str( );
	c = coinss.str( );
	p = pointss.str( );
}

Ultra1::StateNumber Ultra1::Game::Run( )
{
	SDL_ShowCursor( false );

	Level level;
	level.Load( app->stats.current_map, app->stats.current_level );

	app->SoundEnterGame( GetMusicIndex( app->stats.current_map, app->stats.current_level ) );

	Bear bear( &level );

	EntityList entities( &level );
	Dusty dust( &level );

	Sim::Timer ti;
	bool pause = false;

	std::string lifes, coins, points;
	DoDisplay( app, lifes, coins, points );

	Uint8 tr, tg, tb;
	if( level.IsDarkBackGround( ) )
	{
		tr = tg = tb = 255;
	}
	else
	{
		tr = tg = tb = 0;
	}

	// Basic Event loop for now...
	SDL_Event event;
	while( true )
	{
		if( SDL_PollEvent( &event ) )
		{
			if( event.type == SDL_QUIT )
				break;	// quit
			else if( event.type == SDL_KEYDOWN )
			{
				if( event.key.keysym.sym == SDLK_ESCAPE )
				{
					break;
				}
				else if( event.key.keysym.sym == app->options.left )
				{
					if( !pause )
						bear.SetDirection( LEFT );
				}
				else if( event.key.keysym.sym == app->options.right )
				{
					if( !pause )
						bear.SetDirection( RIGHT );
				}
				else if( event.key.keysym.sym == app->options.jump )
				{
					if( !pause )
					{
						bear.Jump( app );
					}
				}
				else if( event.key.keysym.sym == app->options.pause )
				{
					// Pause/Unpause the game
					pause = !pause;
					ti.SetPause( pause );

					bear.SetPause( pause );
					entities.SetPause( pause );
					dust.SetPause( pause );
				}
			}
			else if( event.type == SDL_KEYUP )
			{
				if( (event.key.keysym.sym == app->options.left) || (event.key.keysym.sym == app->options.right) )
				{
					bear.SetDirection( STILL );
				}
				else if( event.key.keysym.sym == app->options.jump )
				{
					if( !pause )
						bear.UnJump( );
				}
			}
		}

		app->Clear( 0, 0, 0 );	// Clear the screen

		ti.Update( );
		unsigned int ticks = ti.GetMSsinceLastFrame( );

		
		level.Update( ticks );
		bear.Update( ticks );
		entities.Update( ticks );
		dust.Update( ticks );

		if( bear.HasWon( ) )
		{
			// We wait until the bear is off the screen...
			app->PlaySound( FINISH_NOISE );
			bear.SetDirection( RIGHT );
			
			DoDisplay( app, lifes, coins, points );
			
			while( bear.GetPosition( ).x < 900 )
			{
				// Fixes Input bug..we must get rid of the events...
				SDL_PollEvent( &event );

				ti.Update( );
				ticks = ti.GetMSsinceLastFrame( );
				bear.Update( ticks );
				entities.Update( ticks );
				dust.Update( ticks );

				level.Draw( app->screen );
				bear.Draw( app->screen );
				entities.Draw( app->screen );
				dust.Draw( app->screen );

				// We add 5 point each frame so it goes up faster on fast computers, but points are ... well ... pointless
				app->stats.points += 5;
				DoDisplay( app, lifes, coins, points );
				app->text_writer.WriteText( app->screen, PLAIN_FONT_14, (char*)lifes.c_str( ), 10, 5, tr, tg, tb );
				app->text_writer.WriteText( app->screen, PLAIN_FONT_14, (char*)coins.c_str( ), 350, 5, tr, tg, tb );
				app->text_writer.WriteText( app->screen, PLAIN_FONT_14, (char*)points.c_str( ), 600, 5, tr, tg, tb );

				app->Flip( );
			}

			// Test if we won...
			if( (app->stats.current_level == 5)	&& (app->stats.current_map == 6) )
			{
				app->SoundEnterMenu( );
				app->FadeTo( 300 );
				return WON_STATE;
			}

			// Test if we unlocked a level...
			if( ((app->stats.current_map-1)*5 + (app->stats.current_level)) == app->stats.curr_level_next )
			{
				app->stats.curr_level_next++;
			
				app->stats.current_level++;
				app->stats.moveon = true;
				app->stats.back_up = false;
				if( app->stats.current_level == 6 )	// Move to next map...
				{
					app->stats.current_level = 1;
					app->stats.current_map++;
					app->stats.moveon = false;
					app->stats.back_up = false;
				}

				app->SoundEnterMenu( );
				app->FadeTo( 300 );
				return MAP_STATE;
			}
			else
			{
                // we already beat this level...
				app->stats.stay = true;
				app->stats.moveon = false;
				app->stats.back_up = false;

				app->SoundEnterMenu( );
				app->FadeTo( 300 );
				return MAP_STATE;
			}
		}
		else if( bear.HasLost( ) )
		{
			app->stats.stay = true;
			app->stats.moveon = false;
			app->stats.back_up = false;
			app->PlaySound( DIE_NOISE );

			app->stats.lives--;

			// We draw everything only to give the FadeTo function its starting poin!
			level.Draw( app->screen );
			bear.Draw( app->screen );
			entities.Draw( app->screen );
			dust.Draw( app->screen );
			// Now we write the stats display
			app->text_writer.WriteText( app->screen, PLAIN_FONT_14, (char*)lifes.c_str( ), 10, 5, tr, tg, tb );
			app->text_writer.WriteText( app->screen, PLAIN_FONT_14, (char*)coins.c_str( ), 350, 5, tr, tg, tb );
			app->text_writer.WriteText( app->screen, PLAIN_FONT_14, (char*)points.c_str( ), 600, 5, tr, tg, tb );

			app->Flip( );

			SDL_Delay( 2000 );

			if( app->stats.lives < 0 )
			{
				app->SoundEnterMenu( );
				app->FadeTo( 300 );
				return LOST_STATE;
			}
			else
			{
				app->SoundEnterMenu( );
				app->FadeTo( 300 );
				return MAP_STATE;
			}
		}

		// Test for bear-entity collisions...
		SDL_Rect temp_bear_pos_it = bear.GetPosition( );
		switch( entities.Collide( &temp_bear_pos_it, &dust , (bear.HasForce( ) || bear.HasArmor( )) ) )
		{
		case NO_COLLIDE:
			break;
		
		case NORTH:
			// ub killed somthin...
			app->PlaySound( KILL_NOISE );
			app->stats.points += 50;
			DoDisplay( app, lifes, coins, points );

			bear.Bounce( );
			break;
		
		case EAST:
		case WEST:
		case SOUTH:
			// Ub is attacked!
			if( bear.HasArmor( ) )
			{
				app->PlaySound( KILL_NOISE );
				bear.SetArmor( false );
				bear.Bounce( );
				app->stats.points += 50;
				DoDisplay( app, lifes, coins, points );
			}
			else if( bear.HasForce( ) )
			{
				app->PlaySound( KILL_NOISE );
				app->stats.points += 50;
				DoDisplay( app, lifes, coins, points );
			}
			else
			{
				// we draw him as the dead bear, and drop him from the screen....
				bear.SetAnimation( 18 );	// warning: brittle code!
				app->PlaySound( DIE_NOISE );
				bear.Die( );
				while( bear.GetPosition( ).y < 800 )
				{
					// Fixes Input bug..we must get rid of the events...
					SDL_PollEvent( &event );

					ti.Update( );
					ticks = ti.GetMSsinceLastFrame( );
					bear.Update( ticks );
					entities.Update( (int) (ticks/1.25f) );	// slow the entities down a tad..
					dust.Update( ticks );

					level.Draw( app->screen );
					bear.Draw( app->screen );
					entities.Draw( app->screen );
					dust.Draw( app->screen );
					// Now we write the stats display
					app->text_writer.WriteText( app->screen, PLAIN_FONT_14, (char*)lifes.c_str( ), 10, 5, tr, tg, tb );
					app->text_writer.WriteText( app->screen, PLAIN_FONT_14, (char*)coins.c_str( ), 350, 5, tr, tg, tb );
					app->text_writer.WriteText( app->screen, PLAIN_FONT_14, (char*)points.c_str( ), 600, 5, tr, tg, tb );

					app->Flip( );
				}

				app->stats.stay = true;
				app->stats.moveon = false;
				app->stats.back_up = false;
				
				app->stats.lives--;

				if( app->stats.lives < 0 )
				{
					app->SoundEnterMenu( );
					app->FadeTo( 300 );
					return LOST_STATE;
				}
				else
				{
					app->SoundEnterMenu( );
					app->FadeTo( 300 );
					return MAP_STATE;
				}
			}
			break;

		case DEAD:
		case WON:
			//wont happen...
			break;

		case GOT_COIN:
			// we got a coin
			app->PlaySound( COIN_NOISE );
			app->stats.coins++;

			if( app->stats.coins >= 100 )
			{
				app->stats.coins -= 100;
				app->stats.lives++;
				app->stats.points += 7;
			}

			app->stats.points += 5;
			DoDisplay( app, lifes, coins, points );
			break;

		case GOT_ARMOR:
			// we got armor
			app->PlaySound( ARMOR_NOISE );
			bear.SetArmor( true );
			break;

		case GOT_FORCE:
			// we got some force
			app->PlaySound( FORCE_NOISE );
			bear.SetForce( );
			break;

		case GOT_LIFE:
			// we got another life
			app->PlaySound( LIFE_NOISE );
			app->stats.lives++;
			app->stats.points += 100;
			DoDisplay( app, lifes, coins, points );
			break;
		}

		level.Draw( app->screen );
		bear.Draw( app->screen );
		entities.Draw( app->screen );
		dust.Draw( app->screen );


		// Now we write the stats display
		app->text_writer.WriteText( app->screen, PLAIN_FONT_14, (char*)lifes.c_str( ), 10, 5, tr, tg, tb );
		app->text_writer.WriteText( app->screen, PLAIN_FONT_14, (char*)coins.c_str( ), 350, 5, tr, tg, tb );
		app->text_writer.WriteText( app->screen, PLAIN_FONT_14, (char*)points.c_str( ), 600, 5, tr, tg, tb );

		app->Flip( );
	}


	bear.SetAnimation( 18 );	// warning: brittle code!
	app->PlaySound( DIE_NOISE );
	bear.Die( );
	while( bear.GetPosition( ).y < 800 )
	{
		// Fixes Input bug..we must get rid of the events...
		SDL_PollEvent( &event );

		ti.Update( );
		unsigned int ticks = ti.GetMSsinceLastFrame( );
		bear.Update( ticks );
		entities.Update( (int) (ticks/1.25f) );	// slow the entities down a tad..
		dust.Update( ticks );

		level.Draw( app->screen );
		bear.Draw( app->screen );
		entities.Draw( app->screen );
		dust.Draw( app->screen );
		// Now we write the stats display
		app->text_writer.WriteText( app->screen, PLAIN_FONT_14, (char*)lifes.c_str( ), 10, 5, tr, tg, tb );
		app->text_writer.WriteText( app->screen, PLAIN_FONT_14, (char*)coins.c_str( ), 350, 5, tr, tg, tb );
		app->text_writer.WriteText( app->screen, PLAIN_FONT_14, (char*)points.c_str( ), 600, 5, tr, tg, tb );

		app->Flip( );
	}

	SDL_ShowCursor( true );

	app->stats.stay = true;
	app->stats.moveon = false;
	app->stats.back_up = false;

	app->stats.lives--;

	// We draw everything only to give the FadeTo function its starting poin!
	level.Draw( app->screen );
	bear.Draw( app->screen );
	entities.Draw( app->screen );
	dust.Draw( app->screen );
	// Now we write the stats display
	app->text_writer.WriteText( app->screen, PLAIN_FONT_14, (char*)lifes.c_str( ), 10, 5, tr, tg, tb );
	app->text_writer.WriteText( app->screen, PLAIN_FONT_14, (char*)coins.c_str( ), 350, 5, tr, tg, tb );
	app->text_writer.WriteText( app->screen, PLAIN_FONT_14, (char*)points.c_str( ), 600, 5, tr, tg, tb );

	app->Flip( );

	if( app->stats.lives < 0 )
	{
		app->SoundEnterMenu( );
		app->FadeTo( 300 );
		return LOST_STATE;
	}
	else
	{
		app->SoundEnterMenu( );
		app->FadeTo( 300 );
		return MAP_STATE;
	}
}



