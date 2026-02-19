/*
**	Command & Conquer Generals Zero Hour(tm)
**	Copyright 2025 Electronic Arts Inc.
**
**	This program is free software: you can redistribute it and/or modify
**	it under the terms of the GNU General Public License as published by
**	the Free Software Foundation, either version 3 of the License, or
**	(at your option) any later version.
**
**	This program is distributed in the hope that it will be useful,
**	but WITHOUT ANY WARRANTY; without even the implied warranty of
**	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
**	GNU General Public License for more details.
**
**	You should have received a copy of the GNU General Public License
**	along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

// FILE: WinMain.cpp //////////////////////////////////////////////////////////
//-----------------------------------------------------------------------------
//                                                                          
//                       Westwood Studios Pacific.                          
//                                                                          
//                       Confidential Information                           
//                Copyright (C) 2001 - All Rights Reserved                  
//                                                                          
//-----------------------------------------------------------------------------
//
// Project:    ImagePacker
//
// File name:  WinMain.cpp
//
// Created:    Colin Day, August 2001
//
// Desc:       Application entry point for the image packer tool
//
//-----------------------------------------------------------------------------
///////////////////////////////////////////////////////////////////////////////

// SYSTEM INCLUDES ////////////////////////////////////////////////////////////
#include <windows.h>
#include <stdlib.h>

// USER INCLUDES //////////////////////////////////////////////////////////////
#include "BaseType.h"
#include "ImagePacker.h"
#include "Resource.h"
#include "argv.h"

// DEFINES ////////////////////////////////////////////////////////////////////

// PRIVATE TYPES //////////////////////////////////////////////////////////////

// PRIVATE DATA ///////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// PUBLIC DATA ////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

// PRIVATE PROTOTYPES /////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// PRIVATE FUNCTIONS //////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// PUBLIC FUNCTIONS ///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

// WinMain ====================================================================
/** Application entry point */
//=============================================================================
int main(int argc, char *argv[])
{
	ArgvClass::Init(GetCommandLine());
	ArgvClass args;

	// allocate a new image packer system
	TheImagePacker = new ImagePacker;
	if( TheImagePacker == NULL )
		return 0;

	// initialize the system
	if( TheImagePacker->init() == FALSE )
	{

		delete TheImagePacker;
		TheImagePacker = NULL;
		return 0;

	}  // end if

	switch ( TheImagePacker->getBatchMode() )
	{
	case ImagePacker::BM_PACK:
	default:
		TheImagePacker->process();
		break;
	case ImagePacker::BM_EXTRACT:
		TheImagePacker->extract();
		break;
	}

	// delete the image packer
	delete TheImagePacker;
	TheImagePacker = NULL;
	ArgvClass::Free();

	// all done
	return 0;

}  // end WinMain
