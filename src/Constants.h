// Constants.h
// Copyright Ian Finlayson 2010
// This is part of UltraBear1 distributed under the MIT
// Key values used by all classes

#ifndef ULTRA1_CONSTS
#define ULTRA1_CONSTS

namespace Ultra1
{
	// Window constants
	const int WIDTH = 800;
	const int HEIGHT = 600;

	// Game State Constants
	typedef int StateNumber;
	const StateNumber INTRO_STATE = 0;
	const StateNumber MENU_STATE = 1;
	const StateNumber GAME_STATE = 2;
	const StateNumber MAP_STATE = 3;
	const StateNumber WON_STATE = 4;
	const StateNumber LOST_STATE = 5;
	const StateNumber HELP_STATE = 6;
	const StateNumber STORY_STATE = 7;
	const StateNumber OPTIONS_STATE = 8;
	const StateNumber QUIT_STATE = 9;

	// Font constants
	const int NUM_FONTS = 4;
	const int PLAIN_FONT_14 = 0;
	const int GALAPOGO_36 = 1;
	const int GALAPOGO_72 = 2;
	const int GALAPOGO_24 = 3;

	// Music constants
	const int NUM_MUSICS = 7;
	const int MUS_1 = 0;
	const int MUS_2 = 1;
	const int MUS_3 = 2;
	const int MUS_4 = 3;
	const int MUS_5 = 4;
	const int MUS_6 = 5;
	const int MUS_7 = 6;


	// Sound constants
	const int NUM_SOUNDS = 10;
	const int BUTTON_NOISE = 0;
	const int FORCE_NOISE = 1;
	const int JUMP_NOISE = 2;
	const int COIN_NOISE = 3;
	const int ARMOR_NOISE = 4;
	const int KILL_NOISE = 5;
	const int DIE_NOISE = 6;
	const int FINISH_NOISE = 7;
	const int LIFE_NOISE = 8;

	// Level Constants
	const float PARRALAX_FACTOR = 2.0f;
	const int BLOCK_SIZE = 20;	// 20x20
	const int NUM_BLOCKS_PER_COLUM = HEIGHT / BLOCK_SIZE;
	const int NUM_BLOCKS_PER_ROW = WIDTH / BLOCK_SIZE;
	const int LEFT_SCROLL_BARRIOR = 375;
	const int RIGHT_SCROLL_BARRIOR = 425;

	// Directional values for Level
	typedef int Direction;
	const Direction STILL = -1;
	const Direction RIGHT = 0;
	const Direction LEFT = 1;

	// Directional Values for map...Also what Sim::Collide returns!
	// Note that if you * by 90, you get angles....
	typedef int CardinalDirection;
	const CardinalDirection NO_COLLIDE = -1;
	const CardinalDirection EAST = 0;
	const CardinalDirection NORTH = 1;
	const CardinalDirection WEST = 2;
	const CardinalDirection SOUTH = 3;
	// I know these are not directions per se, but Level::Collide returns them...
	const CardinalDirection DEAD = 4;
	const CardinalDirection WON = 5;
	const CardinalDirection GOT_COIN = 6;
	const CardinalDirection GOT_ARMOR = 7;
	const CardinalDirection GOT_FORCE = 8;
	const CardinalDirection GOT_LIFE = 9;

	// Ultra Bear's powers
	typedef int Power;
	const Power NONE = 0;
	const Power ARMOR = 1;
	const Power FORCE = 2;

	// Bear speeds (pixels per second)
	const float NORMAL_BEAR_SPEED = 180.0f;   // these speeds must now be the same since we have no more "dash"
	const float FAST_BEAR_SPEED   = 180.0f;
	const float BEAR_JUMP_SPEED   = 400.0f;

	// Gravitational constant...
	const float g = 400.0f;	// Measured in pixels per second squared...
	const float MAX_FALL_SPEED = 500.0f;


	typedef unsigned char EntityNumber;
	const EntityNumber SNOWMAN = 0;
	const EntityNumber BIRD = 1;
	const EntityNumber WALRUS_BOSS = 2;

	const EntityNumber BEAVER = 3;
	const EntityNumber MOOSE = 4;
	const EntityNumber BEAVER_BOSS = 5;

	const EntityNumber RACCOON = 6;
	const EntityNumber POSSOM = 7;
	const EntityNumber POSSUM_BOSS = 8;

	const EntityNumber SNAKE = 9;
	const EntityNumber CHIHUAHUA = 10;
	const EntityNumber CHIHUAHUA_BOSS = 11;

	const EntityNumber LEMMING = 12;
	const EntityNumber GOAT = 13;
	const EntityNumber CHUPACABRA_BOSS = 14;

	const EntityNumber PENGUIN = 15;
	const EntityNumber PENGUIN_BOSS = 16;

	const EntityNumber COIN_PICKUP = 17;
	const EntityNumber ARMOR_PICKUP = 18;
	const EntityNumber FORCE_PICKUP = 19;
	const EntityNumber LIFE_PICKUP = 20;
	const EntityNumber FIREBALL_ENEMY = 21;

	int GetMusicIndex( int map, int level );
}

#endif




