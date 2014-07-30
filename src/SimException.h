/********************************************************************
*	SimException.h				 Ian Finlayson 2005					*
*																	*
*	This class is a general exeption class used by SimLib			*
*																	*
********************************************************************/


#ifndef SIM_EXCEPTION
#define SIM_EXCEPTION

#include <cstring>

namespace Sim
{
	class Exception
	{
	private:
    static const int STR_SIZE = 256;
		char src[STR_SIZE];
		char reas[STR_SIZE];

	public:
		Exception(const char* source, const char* reason )
		{
			strcpy(src, source);
      strcpy(reas, reason);
		}
		void WriteError( );
	};
}

#endif



