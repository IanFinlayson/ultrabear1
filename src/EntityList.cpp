// EntityList.cpp
// Copyright Ian Finlayson 2010
// This is part of UltraBear1 distributed under the MIT

#include "SimFunctions.h"
#include "SimException.h"
#include "EntityList.h"

Ultra1::EntityList::EntityList( Level* the_level ) : entities(NULL)
{
	level = the_level;
	num_entities = the_level->GetEntityCount( );
	entities = new Entity*[num_entities];
	
	std::pair<int, int> position(0, 0);

	for( int i=0; i<num_entities; i++ )
	{
		switch( the_level->GetEntityType( i ) )
		{
/////////////////////////////////////////////////////////// North Pole
		case SNOWMAN:
			entities[i] = new SnowMan( the_level );
			position = the_level->GetEntityPosition( i );
			entities[i]->SetThePosition( 20*position.first, 20*position.second );
			break;
		case BIRD:
			entities[i] = new Bird( the_level );
			position = the_level->GetEntityPosition( i );
			entities[i]->SetThePosition( 20*position.first, 20*position.second );			
			break;
		case WALRUS_BOSS:
			entities[i] = new WalrusBoss( the_level );
			position = the_level->GetEntityPosition( i );
			entities[i]->SetThePosition( 20*position.first, 20*position.second );			
			break;

////////////////////////////////////////////////////////////////////////// Canada

		case BEAVER:
			entities[i] = new Beaver( the_level );
			position = the_level->GetEntityPosition( i );
			entities[i]->SetThePosition( 20*position.first, 20*position.second );			
			break;
		case MOOSE:
			entities[i] = new Moose( the_level );
			position = the_level->GetEntityPosition( i );
			entities[i]->SetThePosition( 20*position.first, 20*position.second );			
			break;
		case BEAVER_BOSS:
			entities[i] = new BeaverBoss( the_level );
			position = the_level->GetEntityPosition( i );
			entities[i]->SetThePosition( 20*position.first, 20*position.second );
			break;

//////////////////////////////////////////////////////////////////////////// Mississippi

		case RACCOON:
			entities[i] = new Raccoon( the_level );
			position = the_level->GetEntityPosition( i );
			entities[i]->SetThePosition( 20*position.first, 20*position.second );			
			break;
		case POSSOM:
			entities[i] = new Possom( the_level );
			position = the_level->GetEntityPosition( i );
			entities[i]->SetThePosition( 20*position.first, 20*position.second );			
			break;
		case POSSUM_BOSS:
			entities[i] = new PossomBoss( the_level );
			position = the_level->GetEntityPosition( i );
			entities[i]->SetThePosition( 20*position.first, 20*position.second );
			break;

////////////////////////////////////////////////////////////////////////////// Mexico

		case SNAKE:
			entities[i] = new Snake( the_level );
			position = the_level->GetEntityPosition( i );
			entities[i]->SetThePosition( 20*position.first, 20*position.second );			
			break;
		case CHIHUAHUA:
			entities[i] = new Chihuahua( the_level );
			position = the_level->GetEntityPosition( i );
			entities[i]->SetThePosition( 20*position.first, 20*position.second );			
			break;
		case CHIHUAHUA_BOSS:
			entities[i] = new ChihuahuaBoss( the_level );
			position = the_level->GetEntityPosition( i );
			entities[i]->SetThePosition( 20*position.first, 20*position.second );
			break;

/////////////////////////////////////////////////////////////////////////////// Andes

		case LEMMING:
			entities[i] = new Lemming( the_level );
			position = the_level->GetEntityPosition( i );
			entities[i]->SetThePosition( 20*position.first, 20*position.second );			
			break;
		case GOAT:
			entities[i] = new Goat( the_level );
			position = the_level->GetEntityPosition( i );
			entities[i]->SetThePosition( 20*position.first, 20*position.second );			
			break;
		case CHUPACABRA_BOSS:
			entities[i] = new ChupacabraBoss( the_level );
			position = the_level->GetEntityPosition( i );
			entities[i]->SetThePosition( 20*position.first, 20*position.second );
			break;

////////////////////////////////////////////////////////////////////////////// South Pole

		case PENGUIN:
			entities[i] = new Penguin( the_level );
			position = the_level->GetEntityPosition( i );
			entities[i]->SetThePosition( 20*position.first, 20*position.second );			
			break;
		case PENGUIN_BOSS:
			entities[i] = new PenguinBoss( the_level );
			position = the_level->GetEntityPosition( i );
			entities[i]->SetThePosition( 20*position.first, 20*position.second );
			break;

////////////////////////////////////////////////////////////////////////////// Pickups

		case COIN_PICKUP:
			entities[i] = new Coin( the_level );
			position = the_level->GetEntityPosition( i );
			entities[i]->SetThePosition( 20*position.first, 20*position.second );			
			break;
		case ARMOR_PICKUP:
			entities[i] = new Armor( the_level );
			position = the_level->GetEntityPosition( i );
			entities[i]->SetThePosition( 20*position.first, 20*position.second );	
			break;
		case FORCE_PICKUP:
			entities[i] = new Force( the_level );
			position = the_level->GetEntityPosition( i );
			entities[i]->SetThePosition( 20*position.first, 20*position.second );	
			break;
		case LIFE_PICKUP:
			entities[i] = new ExtraLife( the_level );
			position = the_level->GetEntityPosition( i );
			entities[i]->SetThePosition( 20*position.first, 20*position.second );	
			break;
		case FIREBALL_ENEMY:
			entities[i] = new FireBall( the_level );
			position = the_level->GetEntityPosition( i );
			entities[i]->SetThePosition( 20*position.first, 20*position.second );
			break;
		default:
			throw Sim::Exception( "EntityList Constructor", "Invalid Entity Code!" );
		}
	}
}

Ultra1::EntityList::~EntityList( )
{
	if( entities )
		delete [] entities;
}

void Ultra1::EntityList::Draw( SDL_Surface* screen )
{
	for( int i=0; i<num_entities; i++ )
		entities[i]->Draw( screen );
}

void Ultra1::EntityList::Update( unsigned int elapsed_ms )
{
	float dt = elapsed_ms / 1000.0f;

	for( int i=0; i<num_entities; i++ )
		entities[i]->Update( dt );
}

void Ultra1::EntityList::SetPause( bool pause )
{
	for( int i=0; i<num_entities; i++ )
		entities[i]->SetPause( pause );
}

Ultra1::CardinalDirection Ultra1::EntityList::Collide( SDL_Rect* bear_pos, Dusty* dust, bool bear_force )
{
	CardinalDirection temp;

	for( int i=0; i<num_entities; i++ )
	{
		if( entities[i]->IsVisible( ) )		
		{
			SDL_Rect entity_curr_loc = entities[i]->GetPosition( );
			temp = Sim::Collide( bear_pos, &entity_curr_loc );
			
			if( temp == NO_COLLIDE )
				continue;

			if( (level->GetEntityType( i ) > PENGUIN_BOSS) && (level->GetEntityType( i ) != FIREBALL_ENEMY) )	// Its a pickup
			{
				entities[i]->Kill( );

				switch( level->GetEntityType( i ) )
				{
				case COIN_PICKUP:
					return GOT_COIN;
					break;

				case ARMOR_PICKUP:
					return GOT_ARMOR;
					break;

				case FORCE_PICKUP:
					return GOT_FORCE;
					break;

				case LIFE_PICKUP:
					return GOT_LIFE;
					break;
				}
			}
			else
			{
				if( (temp == NORTH) && (level->GetEntityType( i ) != FIREBALL_ENEMY) )
				{
					entities[i]->Kill( );
					dust->AddDust( entities[i]->GetPosition().x, entities[i]->GetPosition().y );
					return temp;
				}
				else if( level->GetEntityType( i ) == FIREBALL_ENEMY )
				{
					return EAST;
				}
				else if( bear_force )
				{
					entities[i]->Kill( );
					dust->AddDust( entities[i]->GetPosition().x, entities[i]->GetPosition().y );
					return temp;
				}
				else
				{
					return temp;
				}
			}
		}
	}

	return NO_COLLIDE;
}



