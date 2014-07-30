// Options.cpp
// Copyright Ian Finlayson 2010
// This is part of UltraBear1 distributed under the MIT
// Implements the options screen

#include "App.h"
#include "Options.h"

#include "SimButton.h"
#include "SimImage.h"
#include "prefix.h"

namespace Ultra1
{
	// A CheckBox Kind of thingy...
	class ToggleButton
	{
	private:
		Sim::Button* checked;
		Sim::Button* unchecked;
		bool is_checked;
		Sim::Image* checkmark;

		Ultra1::App* theapp;

	public:
		ToggleButton( int x, int y, bool is_checked, Ultra1::App* app )
		{
			checkmark = new Sim::Image( UBD_PREFIX "/images/checkmark.png", 0, 0, 255 );

			checked = new Sim::Button( x, y, 40, 40, 1, 0, 0, 0, 10, 10 );
			checked->SetBackGround( checkmark->image );
			checked->SetForeGround( "", app->text_writer.GetFont(PLAIN_FONT_14), 0, 0, 0 );

			unchecked = new Sim::Button( x, y, 40, 40, 1, 0, 0, 0, 10, 10 );
			unchecked->SetBackGround( 128, 128, 255 );
			unchecked->SetForeGround( "", app->text_writer.GetFont(PLAIN_FONT_14), 0, 0, 0 );
			
			this->is_checked = is_checked;

			theapp = app;
		}
		~ToggleButton( )
		{
			delete checked;
			delete unchecked;
			delete checkmark;
		}
		void HandleMouseDown( int mx, int my )
		{
			if( is_checked )
				checked->HandleMouseDown( mx, my );
			else
				unchecked->HandleMouseDown( mx, my );
		}
		void HandleMouseUp( int mx, int my )
		{
			bool toggle = false;

			if( is_checked )
				toggle = checked->HandleMouseUp( mx, my );
			else
				toggle = unchecked->HandleMouseUp( mx, my );

			if( toggle )
			{
				theapp->PlaySound( BUTTON_NOISE );
				is_checked = !is_checked;
			}
		}
		void Draw( SDL_Surface* screen )
		{
			if( is_checked )
				checked->Draw( screen );
			else
				unchecked->Draw( screen );
		}
		bool IsChecked( )
		{
			return is_checked;
		}
	};

	// A button where, when you press it, you set its key value...
	class KeyButton
	{
	private:
		SDLKey key;
		Sim::Button* button;
		char* textbuffer;
		Ultra1::App* theapp;

	public:
		KeyButton( int x, int y, SDLKey starting_key, Ultra1::App* app )
		{
			theapp = app;
			key = starting_key;
			textbuffer = new char[32];

			button = new Sim::Button( x, y, 100, 24, 0, 0, 0, 0, 5, 0 );
			button->SetBackGround( 200, 200, 200 );

			GetStr( key );
			button->SetForeGround( textbuffer, app->text_writer.GetFont(PLAIN_FONT_14), 0, 0, 0 );
		}
		~KeyButton( )
		{
			delete button;
			delete [] textbuffer;
		}
		bool GetStr( SDLKey thekey )
		{
			bool good = true;

			// normal letter....
			if( (thekey >= SDLK_a) && (thekey <= SDLK_z) )
			{
				textbuffer[0] = ((char)thekey - 32);
				textbuffer[1] = 0;
			}
			else if( (thekey >= SDLK_0) && (thekey <= SDLK_9) )
			{
				textbuffer[0] = ((char)thekey);
				textbuffer[1] = 0;
			}
			else if( (thekey >= SDLK_KP0) && (thekey <= SDLK_KP9) )
			{
				textbuffer[0] = 'K';
				textbuffer[0] = 'e';
				textbuffer[0] = 'y';
				textbuffer[0] = ' ';
				textbuffer[0] = 'P';
				textbuffer[0] = 'a';
				textbuffer[0] = 'd';
				textbuffer[0] = ' ';
				textbuffer[0] = ((char)thekey - 208);
				textbuffer[1] = 0;
			}
			else if( thekey == SDLK_BACKSPACE )
			{
				strcpy( textbuffer, "Backspace" );
			}
			else if( thekey == SDLK_TAB )
			{
				strcpy( textbuffer, "Tab" );
			}
			else if( thekey == SDLK_RETURN )
			{
				strcpy( textbuffer, "Enter" );
			}
			else if( thekey == SDLK_SPACE )
			{
				strcpy( textbuffer, "Space" );
			}
			else if( thekey == SDLK_COMMA )
			{
				strcpy( textbuffer, ",");
			}
			else if( thekey == SDLK_QUOTE )
			{
				strcpy( textbuffer, "'" );
			}
			else if( thekey == SDLK_MINUS )
			{
				strcpy( textbuffer, "-" );
			}
			else if( thekey == SDLK_PERIOD )
			{
				strcpy( textbuffer, "." );
			}
			else if( thekey == SDLK_SLASH )
			{
				strcpy( textbuffer, "/" );
			}
			else if( thekey == SDLK_SEMICOLON )
			{
				strcpy( textbuffer, ";" );
			}
			else if( thekey == SDLK_EQUALS )
			{
				strcpy( textbuffer, "=" );
			}
			else if( thekey == SDLK_LEFTBRACKET )
			{
				strcpy( textbuffer, "[" );
			}
			else if( thekey == SDLK_RIGHTBRACKET )
			{
				strcpy( textbuffer, "]" );
			}
			else if( thekey == SDLK_BACKSLASH )
			{
				strcpy( textbuffer, "\\" );
			}
			else if( thekey == SDLK_BACKQUOTE )
			{
				strcpy( textbuffer, "`" );
			}
			else if( thekey == SDLK_DELETE )
			{
				strcpy( textbuffer, "Delete" );
			}
			else if( thekey == SDLK_KP_PERIOD )
			{
				strcpy( textbuffer, "Key Pad ." );
			}
			else if( thekey == SDLK_KP_DIVIDE )
			{
				strcpy( textbuffer, "Key Pad /" );
			}
			else if( thekey == SDLK_KP_MULTIPLY )
			{
				strcpy( textbuffer, "Key Pad *" );
			}
			else if( thekey == SDLK_KP_MINUS )
			{
				strcpy( textbuffer, "Key Pad -" );
			}
			else if( thekey == SDLK_KP_PLUS )
			{
				strcpy( textbuffer, "Key Pad +" );
			}
			else if( thekey == SDLK_KP_ENTER )
			{
				strcpy( textbuffer, "Key Pad Enter" );
			}
			else if( thekey == SDLK_UP )
			{
				strcpy( textbuffer, "Up Arrow" );
			}
			else if( thekey == SDLK_DOWN )
			{
				strcpy( textbuffer, "Down Arrow" );
			}
			else if( thekey == SDLK_LEFT )
			{
				strcpy( textbuffer, "Left Arrow" );
			}
			else if( thekey == SDLK_RIGHT )
			{
				strcpy( textbuffer, "Right Arrow" );
			}
			else if( thekey == SDLK_INSERT )
			{
				strcpy( textbuffer, "Insert" );
			}
			else if( thekey == SDLK_HOME )
			{
				strcpy( textbuffer, "Home" );
			}
			else if( thekey == SDLK_END )
			{
				strcpy( textbuffer, "End" );
			}
			else if( thekey == SDLK_PAGEUP )
			{
				strcpy( textbuffer, "Page Up" );
			}
			else if( thekey == SDLK_PAGEDOWN )
			{
				strcpy( textbuffer, "Page Down" );
			}
			else if( thekey == SDLK_RSHIFT )
			{
				strcpy( textbuffer, "Right Shift" );
			}
			else if( thekey == SDLK_LSHIFT )
			{
				strcpy( textbuffer, "Left Shift" );
			}
			else if( thekey == SDLK_RCTRL )
			{
				strcpy( textbuffer, "Right Ctrl" );
			}
			else if( thekey == SDLK_LCTRL )
			{
				strcpy( textbuffer, "Left Ctrl" );
			}
			else if( thekey == SDLK_RALT )
			{
				strcpy( textbuffer, "Right Alt" );
			}
			else if( thekey == SDLK_LALT )
			{
				strcpy( textbuffer, "Left Alt" );
			}
			else
			{
				// Bad key...
				good = false;
			}

			return good;
		}
		void HandleMouseDown( int mx, int my )
		{
			button->HandleMouseDown( mx, my );
		}
		void HandleMouseUp( int mx, int my )
		{
			if( button->HandleMouseUp( mx, my ) )
			{
				// Time to change the key!
				button->ChangeBackColor( 255, 200, 200 );
				button->Draw( theapp->screen );
				theapp->Flip( );

				SDL_Event event;
				while( true )
				{
					if( SDL_PollEvent(&event) )
					{
						if( event.type == SDL_KEYDOWN )
						{
							// If the key is good, save it...
							if( GetStr( event.key.keysym.sym ) )
							{
								key = event.key.keysym.sym;
							}

							button->ChangeButtonText( textbuffer );

							button->ChangeBackColor( 200, 200, 200 );
							return;
						}
					}
				}
			}
		}
		void Draw( SDL_Surface* screen )
		{
			button->Draw( screen );
		}
		SDLKey GetValue( )
		{
			return key;
		}
	};
}


Ultra1::StateNumber Ultra1::OptionsState::Run( )
{
	ToggleButton fulls( 180, 85, app->options.fullscreen, app );
	ToggleButton sound( 180, 130, app->options.sound, app );
	ToggleButton music( 180, 175, app->options.music, app );

	Sim::Image but( UBD_PREFIX "/images/button.png", 255, 0, 0 );
	Sim::Image bg( UBD_PREFIX "/images/bergs.jpg" );
	
	Sim::Button menu( 0, 480, 450, 50, 3, 0, 0, 0, 40, 7, true );
	menu.SetBackGround( but.image );
	menu.SetForeGround( "Main Menu", app->text_writer.GetFont( GALAPOGO_36 ), 0, 0, 0 );
	
	Sim::Button quit( 0, 540, 450, 50, 3, 0, 0, 0, 40, 7, true );
	quit.SetBackGround( but.image );
	quit.SetForeGround( "Quit", app->text_writer.GetFont( GALAPOGO_36 ), 0, 0, 0 );

	KeyButton kleft( 450, 105, app->options.left, app );
	KeyButton kright( 450, 135, app->options.right, app );
	KeyButton kup( 450, 165, app->options.up, app );
	KeyButton kdown( 450, 195, app->options.down, app );
	KeyButton kjump( 450, 225, app->options.jump, app );
	KeyButton kpause( 450, 255, app->options.pause, app );

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
				sound.HandleMouseDown( event.button.x, event.button.y );
				fulls.HandleMouseDown( event.button.x, event.button.y );
				music.HandleMouseDown( event.button.x, event.button.y );

				kleft.HandleMouseDown( event.button.x, event.button.y );
				kright.HandleMouseDown( event.button.x, event.button.y );
				kup.HandleMouseDown( event.button.x, event.button.y );
				kdown.HandleMouseDown( event.button.x, event.button.y );
				kjump.HandleMouseDown( event.button.x, event.button.y );
				kpause.HandleMouseDown( event.button.x, event.button.y );

				menu.HandleMouseDown( event.button.x, event.button.y );
				quit.HandleMouseDown( event.button.x, event.button.y );
			}
			else if( event.type == SDL_MOUSEBUTTONUP )
			{
				sound.HandleMouseUp( event.button.x, event.button.y );
				fulls.HandleMouseUp( event.button.x, event.button.y );
				music.HandleMouseUp( event.button.x, event.button.y );

				kleft.HandleMouseUp( event.button.x, event.button.y );
				kright.HandleMouseUp( event.button.x, event.button.y );
				kup.HandleMouseUp( event.button.x, event.button.y );
				kdown.HandleMouseUp( event.button.x, event.button.y );
				kjump.HandleMouseUp( event.button.x, event.button.y );
				kpause.HandleMouseUp( event.button.x, event.button.y );

				if( menu.HandleMouseUp( event.button.x, event.button.y ) )
				{
					app->options.fullscreen = fulls.IsChecked( );
          if(fulls.IsChecked( )) {
            SDL_WM_ToggleFullScreen(SDL_GetVideoSurface( ));
          }
					app->options.music = music.IsChecked( );
					app->options.sound = sound.IsChecked( );

					app->options.left = kleft.GetValue( );
					app->options.right = kright.GetValue( );
					app->options.up = kup.GetValue( );
					app->options.down = kdown.GetValue( );

					app->options.jump = kjump.GetValue( );
					app->options.pause = kpause.GetValue( );

					app->PlaySound( BUTTON_NOISE );
					app->SoundEnterMenu( );

					app->options.Save( );

					app->FadeTo( 100 );
					return MENU_STATE;
				}
				
				if( quit.HandleMouseUp( event.button.x, event.button.y ) )
				{
					app->options.fullscreen = fulls.IsChecked( );
					app->options.music = music.IsChecked( );
					app->options.sound = sound.IsChecked( );

					app->options.left = kleft.GetValue( );
					app->options.right = kright.GetValue( );
					app->options.up = kup.GetValue( );
					app->options.down = kdown.GetValue( );

					app->options.jump = kjump.GetValue( );
					app->options.pause = kpause.GetValue( );

					app->PlaySound( BUTTON_NOISE );
					app->SoundEnterMenu( );

					app->options.Save( );

					app->FadeTo( 100 );
					return QUIT_STATE;
				}
			}
		}

		app->Clear( 0, 0, 0 );

		SDL_BlitSurface( bg.image, NULL, app->screen, NULL );
		
		app->text_writer.WriteText( app->screen, GALAPOGO_72, "Options", 10, -5, 0, 0, 0 );
		app->text_writer.WriteText( app->screen, GALAPOGO_36, "Fullscreen", 10, 85, 0, 0, 0 );
		app->text_writer.WriteText( app->screen, GALAPOGO_36, "Sound", 10, 130, 0, 0, 0 );
		app->text_writer.WriteText( app->screen, GALAPOGO_36, "Music", 10, 175, 0, 0, 0 );

		app->text_writer.WriteText( app->screen, GALAPOGO_36, "Controls", 400, 65, 0, 0, 0 );
		app->text_writer.WriteText( app->screen, PLAIN_FONT_14, "Left", 400, 105, 0, 0, 0 );
		app->text_writer.WriteText( app->screen, PLAIN_FONT_14, "Right", 400, 135, 0, 0, 0 );
		app->text_writer.WriteText( app->screen, PLAIN_FONT_14, "Up", 400, 165, 0, 0, 0 );
		app->text_writer.WriteText( app->screen, PLAIN_FONT_14, "Down", 400, 195, 0, 0, 0 );
		app->text_writer.WriteText( app->screen, PLAIN_FONT_14, "Jump", 400, 225, 0, 0, 0 );
		app->text_writer.WriteText( app->screen, PLAIN_FONT_14, "Pause", 400, 255, 0, 0, 0 );

//		app->text_writer.WriteText( app->screen, PLAIN_FONT_14, "For Fullscreen to take effect, you must restart the game.", 10, 300, 0, 0, 0 );
		app->text_writer.WriteText( app->screen, PLAIN_FONT_14, "To change the keys, click on the key button, then press the desired key.", 10, 320, 0, 0, 0 );
		app->text_writer.WriteText( app->screen, PLAIN_FONT_14, "Your settings will be saved.", 10, 340, 0, 0, 0 );

		kleft.Draw( app->screen );
		kright.Draw( app->screen );
		kup.Draw( app->screen );
		kdown.Draw( app->screen );
		kjump.Draw( app->screen );
		kpause.Draw( app->screen );

		sound.Draw( app->screen );
		fulls.Draw( app->screen );
		music.Draw( app->screen );


		menu.Draw( app->screen );
		quit.Draw( app->screen );

		app->Flip( );

	}
}






