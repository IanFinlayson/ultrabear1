/********************************************************************
*	SimException.cpp			 Ian Finlayson 2005					*
*																	*
*	Implements SimException											*
*																	*
********************************************************************/

#include "SimException.h"
#include <iostream>

void Sim::Exception::WriteError( )
{			
  std::cerr << "Error Ocurred in............" << src << std::endl
		<< "Error Happened because......" << reas << std::endl << std::endl;
}



