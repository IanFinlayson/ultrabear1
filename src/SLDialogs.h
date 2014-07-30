// SLDialogs.h
// Copyright Ian Finlayson 2010
// This is part of UltraBear1 distributed under the MIT
// Dialogs for saving and loading games...

#ifndef ULTRA1_SLDIALOGS
#define ULTRA1_SLDIALOGS

#include "App.h"

namespace Ultra1
{
	// Presents a Save Dialog for user
	bool SaveDialog( App* app );

	// Presents Load Dialog for user
	// Returns whether or not they chose to save
	bool LoadDialog( App* app );
}

#endif



