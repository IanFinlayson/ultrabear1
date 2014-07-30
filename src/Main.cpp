// Main.cpp
// Copyright Ian Finlayson 2010
// This is part of UltraBear1 distributed under the MIT
// This file contains main

#ifdef WIN32
#include <windows.h>
#else
#include <sys/stat.h>
#endif

#include <exception>
#include <string>
#include <fstream>
#include <iostream>
#include <stdlib.h>
#include "SimException.h"
#include "App.h"
#include "prefix.h"

bool file_exists(const std::string& path)
{
#ifdef WIN32
	return false;  // CopyFile checks for us...
#else
  struct stat buff;
  if(stat(path.c_str( ), &buff) != 0)
    return false;

  return true;
#endif
}

void copy_file(const std::string& name)
{
  /* ensure directories are there... */
#ifdef WIN32
	std::string home = getenv("USERPROFILE");
	CreateDirectory((home + "/.ultrabear1").c_str( ), NULL);
	CreateDirectory((home + "/.ultrabear1/config").c_str( ), NULL);
	CreateDirectory((home + "/.ultrabear1/games").c_str( ), NULL);

	std::string src = UBD_PREFIX "/";
	src += name;

	std::string dest = home + "/.ultrabear1/" + name;

	CopyFile(src.c_str( ), dest.c_str( ), TRUE);
#else
  system("mkdir ~/.ultrabear1 1>/dev/null 2>/dev/null");
  system("mkdir ~/.ultrabear1/config 1>/dev/null 2>/dev/null");
  system("mkdir ~/.ultrabear1/games 1>/dev/null 2>/dev/null");
  system((("cp " UBD_PREFIX "/") + name + " ~/.ultrabear1/" + name).c_str( ));
#endif
}


// if user prefs in the home directory are not there, copy the
// default ones from /usr/share/ultrabear1 before running
void ensure_prefs_exist( )
{
  std::string home;
#ifdef WIN32
  home = getenv("USERPROFILE");
#else
  home = getenv("HOME");
#endif

  if(!file_exists(home + "/.ultrabear1/config/keys.dat"))
    copy_file("config/keys.dat");

  if(!file_exists(home + "/.ultrabear1/config/screen.dat"))
    copy_file("config/screen.dat");

  if(!file_exists(home + "/.ultrabear1/config/sound.dat"))
    copy_file("config/sound.dat");


  if(!file_exists(home + "/.ultrabear1/games/1.ub1g"))
    copy_file("games/1.ub1g");
  if(!file_exists(home + "/.ultrabear1/games/2.ub1g"))
    copy_file("games/2.ub1g");
  if(!file_exists(home + "/.ultrabear1/games/3.ub1g"))
    copy_file("games/3.ub1g");
  if(!file_exists(home + "/.ultrabear1/games/4.ub1g"))
    copy_file("games/4.ub1g");
  if(!file_exists(home + "/.ultrabear1/games/5.ub1g"))
    copy_file("games/5.ub1g");
  if(!file_exists(home + "/.ultrabear1/games/6.ub1g"))
    copy_file("games/6.ub1g");
  if(!file_exists(home + "/.ultrabear1/games/7.ub1g"))
    copy_file("games/7.ub1g");
  if(!file_exists(home + "/.ultrabear1/games/8.ub1g"))
    copy_file("games/8.ub1g");
  if(!file_exists(home + "/.ultrabear1/games/9.ub1g"))
    copy_file("games/9.ub1g");
  if(!file_exists(home + "/.ultrabear1/games/10.ub1g"))
    copy_file("games/10.ub1g");
}


// Create the app and run it...
int main( int argc, char** argv )
{
  /* i hate warnings :) */
  if(argc > 4) printf(argv[1]);
 	try
	{
    ensure_prefs_exist( );

		// We open the config file to see if they want fullscreen
    std::string home;
#ifdef WIN32
    home = getenv("USERPROFILE");
#else
    home = getenv("HOME");
#endif
		std::fstream file((home + "/.ultrabear1/config/screen.dat").c_str( ), std::ios::in );
    if(!file.is_open( ))
      throw Sim::Exception("main", "Could not open screen preferences");
		int full;
		file >> full;
		file.close( );
		bool fullscreen = (full == 0) ? false : true;

		Ultra1::App app( fullscreen );

		app.Run( );
	}
	catch( Sim::Exception exc )
	{
		exc.WriteError( );
	}
	catch( std::exception exc )
	{
		Sim::Exception e( "Unkown", (char*)exc.what( ) );
		e.WriteError( );
	}
	catch( ... )
	{
		Sim::Exception e( "Unkown", "An unkown error has occurred" );
		e.WriteError( );
	}

	return 0;
}



