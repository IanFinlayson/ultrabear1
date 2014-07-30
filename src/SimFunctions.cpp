/********************************************************************
*	SimFunctions.cpp			 Ian Finlayson 2005					*
*																	*
*	Implementation of the disparate free functions in SimLib		*
********************************************************************/

#include "SimFunctions.h"


// this function is so freakin' deprecated
// Returns the direction from which a hits b

int Sim::Collide( SDL_Rect* a, SDL_Rect* b, int error )
{
	int lefA = a->x + error;
	int ritA = (a->x + a->w) - (2*error);
	int topA = a->y + error;
	int botA = (a->y + a->h) - (2*error);

	int lefB = b->x + error;
	int ritB = (b->x + b->w) - (2*error);
	int topB = b->y + error;
	int botB = (b->y + b->h) - (2*error);

	if( botA <= topB )
		return -1;
	if( topA >= botB )
		return -1;
	if( ritA <= lefB )
		return -1;
	if( lefA >= ritB )
		return -1;


	// Now we must check for where the collision happened...
	int hor_dist = ((lefA+ritA)/2) - ((lefB+ritB)/2);
	int ver_dist = ((topA+botA)/2) - ((topB+botB)/2);


	// The collsion is horizontal...
	if( abs(hor_dist) > abs(ver_dist) )
	{
		if( hor_dist <= 0 )
			return 2;
		else
			return 0;
	}
	else	// The collsion is vertical...
	{
		if( ver_dist < 0 )
			return 1;
		else
			return 3;
	}
}






