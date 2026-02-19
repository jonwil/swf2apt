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

// FILE: ImagePacker.cpp //////////////////////////////////////////////////////
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
// File name:  ImagePacker.cpp
//
// Created:    Colin Day, August 2001
//
// Desc:       Entry point for the image packer.  This program takes
//						 separate image files and combines them into a single 
//						 image as close as possible so that we can conserve texture
//						 memory
//
//-----------------------------------------------------------------------------
///////////////////////////////////////////////////////////////////////////////

// SYSTEM INCLUDES ////////////////////////////////////////////////////////////
#include <stdio.h>
#include <io.h>
#include <assert.h>
#include <iostream>

// USER INCLUDES //////////////////////////////////////////////////////////////
#include "Targa.h"
#include "Resource.h"
#include "ImagePacker.h"
#include "WinMain.h"
#include "argv.h"

// DEFINES ////////////////////////////////////////////////////////////////////

// PRIVATE TYPES //////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// PRIVATE DATA ///////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
char *gAppPrefix = "ip_";
static char s_ErrorMessage[520];
ImagePacker *TheImagePacker = NULL;

// PUBLIC DATA ////////////////////////////////////////////////////////////////

// PRIVATE PROTOTYPES /////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// PRIVATE FUNCTIONS //////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

// ImagePacker::createNewTexturePage ==========================================
/** Create a new texture page and add to the list */
//=============================================================================
TexturePage *ImagePacker::createNewTexturePage( const ICoord2D minSize )
{
	TexturePage *page;
	ICoord2D maxSize;

	maxSize.x = getTargetWidth() < minSize.x ? minSize.x : getTargetWidth();
	maxSize.y = getTargetHeight() < minSize.y ? minSize.y : getTargetHeight();

	// allocate new page
	page = new TexturePage( minSize, maxSize );
	if( page == NULL )
	{

		std::cerr << "Unable to allocate new texture page" << std::endl;
		return NULL;

	}  // end if

	// link page to list
	page->m_prev = NULL;
	page->m_next = m_pageList;
	if( m_pageList )
		m_pageList->m_prev = page;
	m_pageList = page;

	// add the tail pointer if this is the first page
	if( m_pageTail == NULL )
		m_pageTail = page;

	// we got a new page now
	m_pageCount++;

	// set page id as the current page count
	page->setID( m_pageCount );

	return page;

}  // end createNewTexturePage

// ImagePacker::validateImages ================================================
/** Check all the images in the image list, if any of them cannot be
	* processed we will flag them as so.  If we have some images that can't
	* be processed, we will warn the user of these images and ask them
	* whether or not to proceed.
	*
	* Returns TRUE to proceed
	* Returns FALSE to cancel build
	*/
//=============================================================================
Bool ImagePacker::validateImages( void )
{
	UnsignedInt i;
	ImageInfoClass *image;
	Bool errors = FALSE;
	Bool proceed = TRUE;

	// loop through all images
	for( i = 0; i < getImageCount(); i++ )
	{

		// get this image
		image = (*m_imageList)[ i ];

		// sanity
		if( image == NULL )
		{

			continue;  // should never happen

		}  // end if

		//
		// if this image is too big to fit in the target page size as a whole
		// then there is nothing we can do about it
		//
		if( image->m_size.x > getTargetWidth() ||
				image->m_size.y > getTargetHeight() )
		{

			BitSet( image->m_status, ImageInfoClass::TOOBIG );

		}  // end if

		//
		// if this image is not the right format we can't process it, at 
		// present we only understand 32 and 24 bit images
		//
		if( image->m_colorDepth != 32 && image->m_colorDepth != 24 )
		{
		
			errors = TRUE;
			BitSet( image->m_status, ImageInfoClass::INVALIDCOLORDEPTH );
			BitSet( image->m_status, ImageInfoClass::CANTPROCESS );
			
		}  // end if

	}  // end for i

	return proceed;

}  // end validateImages

// ImagePacker::packImages ====================================================
/** Pack all the images in the image list, starting from the top and
	* working from there */
//=============================================================================
Bool ImagePacker::packImages( void )
{
	UnsignedInt i;
	TexturePage *page = NULL;
	ImageInfoClass *image = NULL;

	//
	// first sanity check all images loaded, if there are images that cannot
	// be processed the user will be given a list of these and asked wether
	// or not to proceed
	//
	Bool proceed;
	proceed = validateImages();
	if( proceed == FALSE )
	{

		statusMessage( "Build Cancelled By User." );
		return FALSE;

	}  // end if

	// loop through all images
	for( i = 0; i < getImageCount(); i++ )
	{

		// update status
		sprintf( m_statusBuffer, "Fitting Image %d of %d.", i, getImageCount() );
		statusMessage( m_statusBuffer );
		 
		// get this image out of the list
		image = (*m_imageList)[ i ];

		// ignore images that we cannot process
		if( TestBit( image->m_status, ImageInfoClass::CANTPROCESS) )
			continue;

		bool gutter = (getGapMethod() & GAP_METHOD_GUTTER) != 0;

		if ((image->m_status & ImageInfoClass::TOOBIG) != 0)
			gutter = false;

		if (m_onlyPackOne)
		{
			page = NULL;
		}
		else
		{
			// try to put image on each page
			for( page = m_pageTail; page; page = page->m_prev )
			{
				if (m_keepDirsSeperate)
					if (strcmp(page->getFirstImage()->m_path, image->m_path))
						continue;

				if( page->addImage( image, gutter ) == TRUE )
					break;  // page added, stop trying to add into pages

			}  // end for page
		}

		// if image was not able to go on any existing page create a new page for it
		if( page == NULL )
		{

			page = createNewTexturePage( image->m_size );
			if( page == NULL )
				return FALSE;

			// try to add the image to this page
			if( page->addImage( image, gutter) == FALSE )
			{
				std::cerr << "Unable to add image '" << image->m_fullName << "' to a branch new page!" << std::endl;
				return FALSE;

			}  // end if

		}  // end if

	}  // end for i

	return TRUE;  // success

}  // end packImages

// ImagePacker::writeFinalTextures ============================================
/** Generate and write the final textures to the output directory
	* of the packed images along with a definition file for which images
	* are where on the page */
//=============================================================================
void ImagePacker::writeFinalTextures( void )
{
	TexturePage *page;
	Bool errors = FALSE;
	char buffer[ 128 ];

	//
	// go through each page, let's start from the end of the list since
	// that's where we packed first, but it doesn't matter
	//
	for( page = m_pageTail; page; page = page->m_prev )
	{

		// update status message
		sprintf( buffer, "Generating texture #%d of %d.", 
						 page->getID(), m_pageCount );
		statusMessage( buffer );

		// generate the final texture for this page
		if( page->generateTexture() == FALSE )
		{
			
			errors = TRUE;
			continue;  // could not generate this page, but try to continue

		}  // end if

		//
		// write this page out to a file using the filename given by
		// the user and the texture page ID to keep it unique
		//
		if( page->writeFile( m_outputFile ) == FALSE )
		{

			errors = TRUE;
			continue;  // could not write page, but try to go on

		}  // end if

	}  // end for page

	// check for any errors and notify the user
	if( errors == TRUE )
	{
	}  // end if

}  // end writeFinalTextures

// sortImageCompare ===========================================================
/** Compare function for qsort
	* -1 item1 less than item2 
	*	0 item1 identical to item2 
	*	1 item1 greater than item2
	*/
//=============================================================================
static Int sortImageCompare( const void *aa, const void *bb )
{
	const ImageInfoClass **a = (const ImageInfoClass **)aa;
	const ImageInfoClass **b = (const ImageInfoClass **)bb;

	if( (*a)->m_area < (*b)->m_area )
		return 1;
	else if( (*a)->m_area > (*b)->m_area )
		return -1;
	else
		return 0;

}  // end sortImageCompare

// ImagePacker::sortImageList =================================================
/** Sort the image list */
//=============================================================================
void ImagePacker::sortImageList( void )
{
	// sort all images so that largest area ones are first
	UnsignedInt n = getImageCount();
	ImageInfoClass **imageListArray = new ImageInfoClass *[n];

	for (unsigned int i = 0;i < n;i++)
	{
		imageListArray[i] = (*m_imageList)[i];
	}

	qsort(imageListArray, n, sizeof(ImageInfoClass *), sortImageCompare);
	m_imageList->clear();
	m_imageList->reserve(n);

	for (unsigned int i = 0;i < n;i++)
	{
		m_imageList->push_back(imageListArray[i]);
	}

	delete imageListArray;

}  // end sortImageList

// ImagePacker::addImagesInDirectory ==========================================
/** Add all the images in the specified directory */
//=============================================================================
void ImagePacker::addImagesInDirectory( char *dir )
{

	// sanity
	if( dir == NULL )
		return;

	char currDir[ _MAX_PATH ];
	char filePath[ _MAX_PATH ];
	WIN32_FIND_DATA item;  // search item
	HANDLE hFile;  // handle for search resources
	Int len;

	// save the current directory
	GetCurrentDirectory( _MAX_PATH, currDir );

	// change into the directory
	SetCurrentDirectory( dir );

	// go through each item in the output directory		
	hFile = FindFirstFile( "*", &item);
	if( hFile != INVALID_HANDLE_VALUE )
	{  

		// if this is a file count it
		if( !(item.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) &&
				strcmp( item.cFileName, "." ) && 
				strcmp( item.cFileName, ".." ) )
		{

			len = strlen( item.cFileName );
			if( len > 4 && 
					item.cFileName[ len - 4 ] == '.' &&
					(item.cFileName[ len - 3 ] == 't' || item.cFileName[ len - 3 ] == 'T') &&
					(item.cFileName[ len - 2 ] == 'g' || item.cFileName[ len - 2 ] == 'G') &&
					(item.cFileName[ len - 1 ] == 'a' || item.cFileName[ len - 1 ] == 'A') )
			{

				sprintf( filePath, "%s%s", dir, item.cFileName );
				addImage( filePath );

			}  // end if

		}  // end if

		// find the rest of the files
		while( FindNextFile( hFile, &item ) != 0 )
		{

			// if this is a file count it
			if( !(item.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) &&
					strcmp( item.cFileName, "." ) && 
					strcmp( item.cFileName, ".." ) )
			{

				len = strlen( item.cFileName );
				if( len > 4 && 
						item.cFileName[ len - 4 ] == '.' &&
						(item.cFileName[ len - 3 ] == 't' || item.cFileName[ len - 3 ] == 'T') &&
						(item.cFileName[ len - 2 ] == 'g' || item.cFileName[ len - 2 ] == 'G') &&
						(item.cFileName[ len - 1 ] == 'a' || item.cFileName[ len - 1 ] == 'A') )
				{

					sprintf( filePath, "%s%s", dir, item.cFileName );
					addImage( filePath );

				}  // end if

			}  // end if

		}  // end while

		// close search
		FindClose( hFile );

	}  //end if, items found

	// restore our current directory
	SetCurrentDirectory( currDir );

}  // end addImagesInDirectory

// ImagePacker::resetPageList =================================================
/** Clear the page list */
//=============================================================================
void ImagePacker::resetPageList( void )
{
	TexturePage *next;

	while( m_pageList )
	{

		next = m_pageList->m_next;
		delete m_pageList;
		m_pageList = next;

	}  // end while

	m_pageTail = NULL;
	m_pageCount = 0;
	m_targetPreviewPage = 1;

}  // end resetPageList

// ImagePacker::resetImageDirectoryList =======================================
/** Clear the image directory list */
//=============================================================================
void ImagePacker::resetImageDirectoryList( void )
{
	ImageDirectory *next;

	while( m_dirList )
	{

		next = m_dirList->m_next;
		delete m_dirList;
		m_dirList = next;
			
	}  // end while

	m_dirCount = 0;
	m_imagesInDirs = 0;

}  // end resetImageDirectoryList

// ImagePacker::resetImageList ================================================
/** Clear the image list */
//=============================================================================
void ImagePacker::resetImageList( void )
{
	for (unsigned int i = 0; i < m_imageList->size();i++)
	{
		delete (*m_imageList)[i];
	}

	m_imageList->clear();

}  // end resetImageList

// ImagePacker::addDirectory ==================================================
/** Add the directory to the directory list, do not add it if it is already
	* in the directory list.  We want to have that sanity check so that
	* we can be assured that each image being added to the image list from
	* each directory will be unique and we therefore don't have to do
	* any further checking for duplicates */
//=============================================================================
void ImagePacker::addDirectory( char *path, Bool subDirs )
{
	char currDir[ _MAX_PATH ];
	char pathBuff[ _MAX_PATH ];
	WIN32_FIND_DATA item;  // search item
	HANDLE hFile;  // handle for search resources
	Int lastChar;
	Bool addQuote;

	// santiy
	if( path == NULL )
		return;

	lastChar = strlen( path ) - 1;
	addQuote = false;

	if (path[lastChar] == '"')
	{
		--lastChar;
		addQuote = true;
	}

	if (path[lastChar] != '\\')
	{
		strcpy(pathBuff, path);
		strcat(pathBuff, "\\");

		if (addQuote)
		{
			strcat(pathBuff, "\"");
		}

		path = pathBuff;
	}

	// check to see if path is already in list
	ImageDirectory *dir;
	for( dir = m_dirList; dir; dir = dir->m_next )
		if( stricmp( dir->m_path, path ) == 0 )
			return;  // already in list

	// save our current directory
	GetCurrentDirectory( _MAX_PATH, currDir );

	// set our directory to this one
	if( SetCurrentDirectory( path ) == 0 )
		return;  // directory does not exist

	// image is not in list, make a new entry and link to the list
	dir = new ImageDirectory;
	if( dir == NULL )
	{

		std::cerr << "Unable to allocate image directory" << std::endl;
		return;

	}  // end if

	// allocate space for the path
	dir->m_path = new char[ strlen( path ) + 1 ];
	strcpy( dir->m_path, path );

	// tie to list
	dir->m_prev = NULL;
	dir->m_next = m_dirList;
	if( m_dirList )
		m_dirList->m_prev = dir;
	m_dirList = dir;
	
	// increase our directory count
	m_dirCount++;

	// update status
	sprintf( m_statusBuffer, "Folder Added: %d.", m_dirCount );
	statusMessage( m_statusBuffer );

	int len = 0;

	// count how many image files are in this directory
	hFile = FindFirstFile( "*", &item);
	if( hFile != INVALID_HANDLE_VALUE )
	{  

		// if this is a file count it
		if( !(item.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) &&
				strcmp( item.cFileName, "." ) && 
				strcmp( item.cFileName, ".." ) )
		{

			len = strlen( item.cFileName );
			if( len > 4 && 
					item.cFileName[ len - 4 ] == '.' &&
					(item.cFileName[ len - 3 ] == 't' || item.cFileName[ len - 3 ] == 'T') &&
					(item.cFileName[ len - 2 ] == 'g' || item.cFileName[ len - 2 ] == 'G') &&
					(item.cFileName[ len - 1 ] == 'a' || item.cFileName[ len - 1 ] == 'A') )
				dir->m_imageCount++;

		}  // end if

		// find the rest of the files
		while( FindNextFile( hFile, &item ) != 0 )
		{

			// if this is a file count it
			if( !(item.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) &&
					strcmp( item.cFileName, "." ) && 
					strcmp( item.cFileName, ".." ) )
			{

				len = strlen( item.cFileName );
				if( len > 4 && 
						item.cFileName[ len - 4 ] == '.' &&
						(item.cFileName[ len - 3 ] == 't' || item.cFileName[ len - 3 ] == 'T') &&
						(item.cFileName[ len - 2 ] == 'g' || item.cFileName[ len - 2 ] == 'G') &&
						(item.cFileName[ len - 1 ] == 'a' || item.cFileName[ len - 1 ] == 'A') )
					dir->m_imageCount++;

			}  // end if

		}  // end while

		// close search
		FindClose( hFile );

	}  //end if, items found

	// add the image count of this directory to the total image count
	m_imagesInDirs += dir->m_imageCount;

	// if we are adding subdirectories add them all
	if( subDirs )
	{
		char subDir[ _MAX_PATH ];

		// go through each item in the output directory		
		hFile = FindFirstFile( "*", &item);
		if( hFile != INVALID_HANDLE_VALUE )
		{  

			// if this is a file count it
			if( (item.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) &&
					strcmp( item.cFileName, "." ) && 
					strcmp( item.cFileName, ".." ) )
			{

				sprintf( subDir, "%s%s\\", path, item.cFileName );
				addDirectory( subDir, subDirs );

			}  // end if

			// find the rest of the files
			while( FindNextFile( hFile, &item ) != 0 )
			{

				// if this is a file count it
				if( (item.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) &&
						strcmp( item.cFileName, "." ) && 
						strcmp( item.cFileName, ".." ) )
				{

					sprintf( subDir, "%s%s\\", path, item.cFileName );
					addDirectory( subDir, subDirs );

				}  // end if

			}  // end while

			// close search
			FindClose( hFile );

		}  //end if, items found

	}  // end if

	// restore our current directory
	SetCurrentDirectory( currDir );

}  // end addDirectory

// ImagePacker::addImage ======================================================
/** Add the image to the image list */
//=============================================================================
void ImagePacker::addImage( char *path )
{

	// sanity
	if( path == NULL )
		return;

	// allocate a new entry
	ImageInfoClass *info = new ImageInfoClass;
	if( info == NULL )
	{

		std::cerr << "Unable to allocation image path info" << std::endl;
		return;

	}  // end if

	// allocate space for the path
	Int len = strlen( path );
	info->m_fullName = new char[len + 1];
	strcpy(info->m_fullName, path);
	info->m_path = new char[ len + 1 ];
	strcpy( info->m_path, path );
	char *last = strrchr(info->m_path, '\\');

	if (*last)
	{
		*last = 0;
	}

	if( info->m_fullName == NULL )
	{

		MessageBox( NULL, "Unable to allcoate image path info", "Error",
								MB_OK | MB_ICONERROR );
		delete info;
		return;

	}  // end if

	// load just the header information from the targa
	m_targa->Load( info->m_fullName, 0, TRUE );

	// get the data we need out of the targa header
	info->m_colorDepth = m_targa->Header.PixelDepth;
	info->m_size.x = m_targa->Header.Width;
	info->m_size.y = m_targa->Header.Height;
	info->m_area = info->m_size.x * info->m_size.y;

	// save the filename only without path
	Int i;
	char *c;
	for( i = len - 1; i >= 0; i-- )
	{

		if( path[ i ] == '\\' )
		{
			c = &path[ i + 1 ];
			break;
		}

	}  // end for i

	Int nameLen = strlen( c );
	info->m_filenameOnly = new char[ nameLen + 1 ];
	strcpy( info->m_filenameOnly, c );

	info->m_filenameOnlyNoExt = new char[ nameLen - 4 + 1 ];
	strncpy( info->m_filenameOnlyNoExt, c, nameLen - 4 );
	info->m_filenameOnlyNoExt[ nameLen - 4 ] = '\0';

	// assign to array
	m_imageList->push_back(info);

	// update status
	sprintf( m_statusBuffer, "Loading Image %d of %d.", 
					 getImageCount(), m_imagesInDirs );
	statusMessage( m_statusBuffer );

}  // end addImage

// ImagePacker::generateXMLFile ===============================================
/** Generate the XML image file definition for the final packed images */
//=============================================================================
Bool ImagePacker::generateXMLFile( Bool onDemand )
{
	FILE *fp;
	char filename[ _MAX_PATH ];

	// construct filename we'll use
	sprintf( filename, "%s%s.xml", m_outputDirectory, m_outputFile );

	// open the file
	fp = fopen( filename, "w" );
	if( fp == NULL )
	{
		std::cerr << "Cannot open XML file '" << filename << "' for writing." << std::endl;
		return FALSE;

	}  // end if

	// print header for file
	fprintf( fp, "<?xml version='1.0' encoding='UTF-8'?>\n" );
	fprintf( fp, "<!--" );
	fprintf( fp, " XML: %s\n", filename );
	fprintf( fp, " Directories:\n" );

	for ( ImageDirectory *dir = m_dirList; dir; dir = dir->m_next )
	{
		fprintf( fp, "    %s\n", dir->m_path );
	}

	fprintf( fp, " Extend RGB   : %s\n", ( m_gapMethod & GAP_METHOD_EXTEND_RGB ) != 0 ? "Yes" : "No" );
	fprintf( fp, " Gutter (%d)   : %s\n", m_gutterSize, ( m_gapMethod & GAP_METHOD_GUTTER ) != 0 ? "Yes" : "No" );
	fprintf( fp, " Alpha Channel: %s\n", m_outputAlpha ? "Yes" : "No" );
	fprintf( fp, " Compressed   : %s\n", m_compressTextures ? "Yes" : "No" );
	fprintf( fp, " Image Size   : %d x %d\n", m_targetSize.x, m_targetSize.y );
	fprintf( fp, " Keep Dirs Seperate: %s\n", m_keepDirsSeperate ? "Yes" : "No" );
	fprintf( fp, "-->\n" );
	fprintf( fp, "<AssetDeclaration xmlns=\"uri:ea.com:eala:asset\" xmlns:xsi=\"http://www.w3.org/2001/XMLSchema-instance\">\n\n" );

	//
	// loop through all the pages so that we write image definitions that
	// are on the same page close together in the file, note we're
	// going backwards through the page list because page 1 is at the 
	// tail and I want them to print out in number order, but it
	// doesn't really matter
	//
	TexturePage *page;
	ImageInfoClass *image;
	char packedTextureName[516];
	for( page = m_pageTail; page; page = page->m_prev )
	{

		// ignore texture pages that generated errors
		if( TestBit( page->m_status, TexturePage::PAGE_ERROR ) )
		{
			fprintf( fp, "\n<!-- ============ Warning!!!! Texture Page Error ============= -->\n\n" );
			continue;
		}

		memset( packedTextureName, 0, 516 );

		if ( m_fileNameZeroPad )
			sprintf( packedTextureName, "%s_%03d", m_outputFile, page->getID() );
		else
			sprintf( packedTextureName, "%s_%0d", m_outputFile, page->getID() );

		char *texName = strrchr( packedTextureName, '\\' );

		if ( !texName )
			texName = packedTextureName;
		else
			texName += 1;

		if ( !onDemand )
		{
			fprintf( fp, "\t<!-- Packed Texture: %s.tga -->\n", texName );
			fprintf( fp, "\t<Texture id=\"%s\" File=\"%s.tga\" OutputFormat=\"%s\" GenerateMipMaps=\"false\" AllowAutomaticResize=\"false\"/>\n\n", texName, texName, m_textureFormat );
		}
		else
		{
			fprintf( fp, "\t<!-- On Demand Texture: %s.tga -->\n", texName );
			fprintf( fp,	"\t<OnDemandTexture id=\"%s\" File=\"%s.tga\" OutputFormat=\"%s\" GenerateMipMaps=\"false\" AllowAutomaticResize=\"false\"/>\n\n", texName, texName, m_textureFormat );
		}

		// go through each image on this page
		for( image = page->getFirstImage(); 
				 image; 
				 image = image->m_nextPageImage )
		{

			if ( !onDemand )
				fprintf( fp, "\t<PackedTextureImage id=\"%s\" Texture=\"%s\" Rotated=\"%s\">\n", image->m_filenameOnlyNoExt, texName, ( image->m_status & ImageInfoClass::ROTATED90C ) != 0 ? "true" : "false" );
			else
				fprintf( fp, "\t<OnDemandTextureImage id=\"%s\" Texture=\"%s\" Rotated=\"%s\">\n", image->m_filenameOnlyNoExt, texName, ( image->m_status & ImageInfoClass::ROTATED90C ) != 0 ? "true" : "false" );

			fprintf( fp, "\t\t<Dimensions x=\"%d\" y=\"%d\"/>\n", image->m_size.x, image->m_size.y );
			fprintf( fp, "\t\t<Coords x=\"%d\" y=\"%d\"/>\n", image->m_pagePos.lo.x, image->m_pagePos.lo.y );
			fprintf( fp, "\t\t<TextureDimensions x=\"%d\" y=\"%d\"/>\n", page->getWidth(), page->getHeight() );

			if ( !onDemand )
				fprintf( fp, "\t</PackedTextureImage>\n" );
			else
				fprintf( fp, "\t</OnDemandTextureImage>\n" );

		}  // end for image

		fprintf( fp, "\n" );

	}  // end for page

	fprintf( fp, "</AssetDeclaration>" );

	// close the file
	fclose( fp );

	return TRUE;  // success

}  // end generateXMLFile

// ImagePacker::generateINIFile ===============================================
/** Generate the INI image file definition for the final packed images */
//=============================================================================
Bool ImagePacker::generateINIFile( void )
{
	FILE *fp;
	char filename[ _MAX_PATH ];

	// construct filename we'll use
	sprintf( filename, "%s%s.INI", m_outputDirectory, m_outputFile );

	// open the file
	fp = fopen( filename, "w" );
	if( fp == NULL )
	{
		std::cerr << "Cannot open INI file '" << filename << "' for writing." << std::endl;
		return FALSE;

	}  // end if

	// print header for file
	fprintf( fp, "; ------------------------------------------------------------\n" );
	fprintf( fp, "; Do NOT edit by hand, ImagePacker.exe auto generated INI file\n" );
	fprintf( fp, "; ------------------------------------------------------------\n" );
	fprintf( fp, "; INI: %s\n", filename );
	fprintf( fp, "; Directories:\n" );

	for ( ImageDirectory *dir = m_dirList; dir; dir = dir->m_next )
	{
		fprintf( fp, ";    %s\n", dir->m_path );
	}

	fprintf( fp, "; Extend RGB   : %s\n", (m_gapMethod & GAP_METHOD_EXTEND_RGB) != 0 ? "Yes" : "No" );
	fprintf( fp, "; Gutter (%d)   : %s\n", m_gutterSize, (m_gapMethod & GAP_METHOD_GUTTER) != 0 ? "Yes" : "No" );
	fprintf( fp, "; Alpha Channel: %s\n", m_outputAlpha ? "Yes" : "No" );
	fprintf( fp, "; Compressed   : %s\n", m_compressTextures ? "Yes" : "No" );
	fprintf( fp, "; Image Size   : %d x %d\n", m_targetSize.x, m_targetSize.y );
	fprintf( fp, "; Keep Dirs Seperate: %s\n", m_keepDirsSeperate ? "Yes" : "No" );
	fprintf( fp, "; ------------------------------------------------------------\n" );

	//
	// loop through all the pages so that we write image definitions that
	// are on the same page close together in the file, note we're
	// going backwards through the page list because page 1 is at the 
	// tail and I want them to print out in number order, but it
	// doesn't really matter
	//
	TexturePage *page;
	ImageInfoClass *image;
	for( page = m_pageTail; page; page = page->m_prev )
	{

		// ignore texture pages that generated errors
		if( TestBit( page->m_status, TexturePage::PAGE_ERROR ) )
		{
			fprintf( fp, "\n; ============ Warning!!!! Texure Page Error =================\n\n" );
			continue;
		}

		// go through each image on this page
		for( image = page->getFirstImage(); 
				 image; 
				 image = image->m_nextPageImage )
		{

			//
			// write the item definition, note when we output the texture coords
			// we add on to the right and bottom to include that pixel in the
			// texture calculations ... need to do this since we are using a zero
			// based region for the "filled regions" in the image packer
			//
			fprintf( fp, "MappedImage %s\n", image->m_filenameOnlyNoExt );

			if (m_fileNameZeroPad)
			{
				fprintf( fp, "  Texture = %s_%03d.tga\n", m_outputFile, page->getID() );
			}
			else
			{
				fprintf( fp, "  Texture = %s_%0d.tga\n", m_outputFile, page->getID() );
			}

			fprintf( fp, "  TextureWidth = %d\n", page->getWidth() );
			fprintf( fp, "  TextureHeight = %d\n", page->getHeight() );
			fprintf( fp, "  Coords = Left:%d Top:%d Right:%d Bottom:%d\n",
							 image->m_pagePos.lo.x, image->m_pagePos.lo.y,
							 image->m_pagePos.hi.x + 1, image->m_pagePos.hi.y + 1 );
			fprintf( fp, "  Status = %s\n", 
							 TestBit( image->m_status, ImageInfoClass::ROTATED90C ) ? 
												"ROTATED_90_CLOCKWISE" : "NONE" );
			fprintf( fp, "End\n\n" );

		}  // end for image

	}  // end for page

	fprintf( fp, "\n; EOF" );

	// close the file
	fclose( fp );

	return TRUE;  // success

}  // end generateINIFile

///////////////////////////////////////////////////////////////////////////////
// PUBLIC FUNCTIONS ///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

// ImagePacker::ImagePacker ===================================================
/** */
//=============================================================================
ImagePacker::ImagePacker( void )
{

	m_hWnd = NULL;
	m_targetSize.x = DEFAULT_TARGET_SIZE;
	m_targetSize.y = DEFAULT_TARGET_SIZE;
	m_useSubFolders = FALSE;
	strcpy( m_outputFile, "" );
	strcpy( m_outputDirectory, "" );
	strcpy( m_extractFile, "" );
	m_dirList = NULL;
	m_dirCount = 0;
	m_imagesInDirs = 0;
	m_imageList = new std::vector<ImageInfoClass *>;
	strcpy( m_statusBuffer, "" );
	m_pageList = NULL;
	m_pageTail = NULL;
	m_pageCount = 0;
	m_gapMethod = GAP_METHOD_EXTEND_RGB;
	m_gutterSize = 1;
	m_outputAlpha = TRUE;
	m_sortImages = TRUE;
	m_keepDirsSeperate = TRUE;
	m_createINI = TRUE;
	m_createXML = TRUE;
	m_onlyPackOne = FALSE;
	m_fileNameZeroPad = TRUE;
	m_allowRotate = TRUE;
	m_extendAlpha = FALSE;

	m_targetPreviewPage = 1;
	m_hWndPreview = NULL;
	m_showTextureInPreview = FALSE;

	m_targa = NULL;
	m_compressTextures = FALSE;
	m_batchMode = BM_OFF;

}  // end ImagePacker

// ImagePacker::~ImagePacker ==================================================
/** */
//=============================================================================
ImagePacker::~ImagePacker( void )
{

	// delete our lists
	resetImageDirectoryList();
	resetImageList();
	resetPageList();

	// delete our targa header loader
	if( m_targa )
		delete m_targa;

	delete m_imageList;

}  // end ~ImagePacker

// ImagePacker::init ==========================================================
/** Initialize the image packer system */
//=============================================================================
Bool ImagePacker::init( void )
{
	m_textureFormat = "";

	// allocate a targa to read the headers for the images
	m_targa = new Targa;
	if( m_targa == NULL )
	{
		
		std::cerr << "Unable to allocate targa header during init" << std::endl << "ImagePacker can't init, unable to create targa" << std::endl;
		return FALSE;

	}  // end if

	ArgvClass args;

	if ( args.Find( "-M" ) )
	{
		m_createINI = false;
		m_createXML = true;
	}

	if ( args.Find( "-H" ) )
	{
		m_onlyPackOne = true;
	}

	if ( args.Find( "-C" ) )
	{
		m_compressTextures = true;
	}

	if ( args.Find( "-S" ) )
	{
		m_useSubFolders = true;
	}

	if ( args.Find( "-K" ) )
	{
		m_keepDirsSeperate = false;
	}

	if ( args.Find( "-16" ) )
	{
		m_targetSize.x = 16;
		m_targetSize.y = 16;
	}
	if ( args.Find( "-32" ) )
	{
		m_targetSize.x = 32;
		m_targetSize.y = 32;
	}
	if ( args.Find( "-64" ) )
	{
		m_targetSize.x = 64;
		m_targetSize.y = 64;
	}
	if ( args.Find( "-128" ) )
	{
		m_targetSize.x = 128;
		m_targetSize.y = 128;
	}
	else if ( args.Find( "-256" ) )
	{
		m_targetSize.x = 256;
		m_targetSize.y = 256;
	}
	else if ( args.Find( "-512" ) )
	{
		m_targetSize.x = 512;
		m_targetSize.y = 512;
	}
	else if ( args.Find( "-1024" ) )
	{
		m_targetSize.x = 1024;
		m_targetSize.y = 1024;
	}
	else if ( args.Find( "-2048" ) )
	{
		m_targetSize.x = 2048;
		m_targetSize.y = 2048;
	}

	const char *gap = args.Find_Value( "-G" );

	if ( gap && *gap )
	{
		m_gutterSize = atoi( gap );

		if ( !m_gutterSize )
		{
			m_gutterSize = 1;
		}

		m_gapMethod |= GAP_METHOD_GUTTER;
	}
	else
	{
		if ( args.Find( "-G" ) )
		{
			m_gapMethod |= GAP_METHOD_GUTTER;
		}
		else
		{
			m_gapMethod &= ~GAP_METHOD_GUTTER;
		}
	}

	if ( args.Find( "-Z" ) )
	{
		m_fileNameZeroPad = false;
	}

	if ( args.Find( "-R" ) )
	{
		m_allowRotate = false;
	}

	m_textureFormat = args.Find_Value("-textureFormat");

	if ( args.Find( "-XA" ) )
	{
		m_gapMethod |= GAP_METHOD_EXTEND_RGB;
		m_extendAlpha = true;
	}
	else 
	{
		if ( args.Find( "-X" ) )
		{
			m_gapMethod &= ~GAP_METHOD_EXTEND_RGB;
		}
		else
		{
			m_gapMethod |= GAP_METHOD_EXTEND_RGB;
		}
	}
	
	if ( args.Find( "-A" ) )
	{
		m_outputAlpha = false;
	}
	else
	{
		m_outputAlpha = true;
	}

	const char *outputDir = args.Find_Value( "-O" );

	if (outputDir)
	{
		setOutputDirectory(outputDir);
	}

	args.Reset();

	while ( args.Find_Again( "-D" ) )
	{
		const char *directory = args.Get_Cur_Value( 2, 0 );
		char *buffer = new char[strlen( directory ) + 2];
		strcpy( buffer, directory );
		char *dir = strtok( buffer, ";" );

		while (dir)
		{
			char currDir[ _MAX_PATH ];

			if ( !strrchr( dir, ':' ) )
			{
				GetCurrentDirectory( _MAX_PATH, currDir );
				strcat( currDir, "\\" );
				strcat( currDir, dir );
			}
			else
			{
				strcpy( currDir, dir );
			}

			addDirectory( currDir, m_useSubFolders );
			std::string string( currDir );
			dir = strtok( 0, ";" );
		}

		delete[] buffer;
	}

	if ( args.Find( "-P" ) )
	{
		strcpy( m_outputFile, args.Get_Cur_Value( 2, 0 ) );
		setBatchMode( BM_PACK );
	}
	else if ( args.Find( "-E" ) )
	{
		const char *directory = args.Get_Cur_Value( 2, 0 );
		char *buffer = new char[strlen( directory ) + 2];
		strcpy( buffer, directory );

		char *dir = strtok( buffer, ";" );

		while (dir)
		{
			char currDir[ _MAX_PATH ];
			GetCurrentDirectory( _MAX_PATH, currDir);
			strcat( currDir, "\\" );
			strcat( currDir, dir );
			addDirectory( currDir, m_useSubFolders );
			dir = strtok( 0, ";" );
		}

		delete[] buffer;
		setBatchMode( BM_EXTRACT );
	}
	else
	{
		setBatchMode( BM_OFF );
	}

	if ( args.Find( "-U" ) )
	{
		m_sortImages = false;
	}

	return TRUE;

}  // end init

// ImagePacker::statusMessage =================================================
/** Status message for the program */
//=============================================================================
void ImagePacker::statusMessage( char *message )
{
}  // end statusMessage

// ImagePacker::process =======================================================
/** Run the packing process */
//=============================================================================
Bool ImagePacker::process( void )
{

	// build the output directory based on the base name of the output images
	char outputDirectory[ _MAX_PATH ];

	// subdir of output directory based on output image name
	strcpy(outputDirectory, m_outputDirectory);
	CreateDirectory(m_outputDirectory, NULL);

	// reset the contents of our image list and existing textures
	resetImageList();
	resetPageList();

	// set a status message
	statusMessage( "Gathering Image Information, Please Wait ..." );

	m_imageList->clear();

	// load our image list with all the art files from the specified directories
	ImageDirectory *dir;
	for( dir = m_dirList; dir; dir = dir->m_next )
		addImagesInDirectory( dir->m_path );

	// sort the images with the largest biggest images at the top of the list
	if ( m_sortImages )
		sortImageList();

	// pack all images
	if( packImages() )
	{

		// generate the actual final textures and write them out to the file
		writeFinalTextures();

		// generate the INI definition file if requested
		if( createINIFile() )
			generateINIFile();

		if( createXMLFile() )
			generateXMLFile(m_onlyPackOne);

		// all done
		sprintf( m_statusBuffer, "Image Packing Complete: '%d' Texture Pages Generated from '%d' Images in '%d' Folder(s)",
						 m_pageCount, getImageCount(), m_dirCount );
		statusMessage( m_statusBuffer );

	}  // end if

	strcpy(m_outputDirectory, outputDirectory);
	SetCurrentDirectory(m_outputDirectory);

	return TRUE;

}  // end process

void ImagePacker::setOutputDirectory(const char *to)
{
	if ( to && *to )
	{
		if (to[1] != ':')
		{
			GetCurrentDirectory( _MAX_PATH, m_outputDirectory );
			strcat( m_outputDirectory, "\\" );
			strcat( m_outputDirectory, to );
		}
		else
		{
			strcpy(m_outputDirectory, to);
		}
	}
	else
	{
		GetCurrentDirectory( _MAX_PATH, m_outputDirectory );
	}

	strcat( m_outputDirectory, "\\" );
	SendDlgItemMessage( TheImagePacker->getWindowHandle(), 1015, WM_SETTEXT, 0, (LPARAM)m_outputDirectory );
}

void ImagePacker::onDialogInitialized(HWND dialog)
{
	setOutputDirectory( NULL );

	while ( !m_commandLineDirectories.empty() )
	{
		std::string &string = m_commandLineDirectories.back();
		SendDlgItemMessage( dialog, 1002, LB_ADDSTRING, 0, (LPARAM)string.c_str() );
		m_commandLineDirectories.pop_back();
	}
}

bool ImagePacker::extractProcess(char *fileName)
{
	strcpy( m_extractFile, fileName );
	
	if ( !loadINIFile() )
	{
		std::cerr << "Error loading INI File" << std::endl;
		return false;
	}

	if ( !extractMappedTextures() )
	{
		std::cerr << "Error loading INI File" << std::endl;
		return false;
	}

	return true;
}

bool ImagePacker::extract()
{
	resetImageList();
	resetPageList();

	WIN32_FIND_DATA item;
	HANDLE hFile;
	bool ret = true;
	char currDir[ _MAX_PATH ];
	char fileNameWithPath[ _MAX_PATH ];
	ImageDirectory *dir;

	GetCurrentDirectory(MAX_PATH, currDir);

	for ( dir = m_dirList; dir; dir = dir->m_next )
	{
		if ( !SetCurrentDirectory( dir->m_path ) )
		{
			continue;
		}
			
		hFile = FindFirstFile( "*", &item );

		if ( hFile != INVALID_HANDLE_VALUE )
		{
			int len = 0;

			if( !(item.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) &&
					strcmp( item.cFileName, "." ) && 
					strcmp( item.cFileName, ".." ) )
			{
				len = strlen(item.cFileName);

				if ( len > 4 && item.cFileName[len - 4] == '.' && (item.cFileName[len - 3] == 'i' || item.cFileName[len - 3] == 'I') && (item.cFileName[len - 2] == 'n' || item.cFileName[len - 2] == 'N') && (item.cFileName[len - 1] == 'i' || item.cFileName[len - 1] == 'I') )
				{
					GetCurrentDirectory( _MAX_PATH, fileNameWithPath );
					strcat( fileNameWithPath, "\\" );
					strcat( fileNameWithPath, item.cFileName );
					ret = ret && extractProcess( fileNameWithPath );
				}
			}
			
			while ( FindNextFile(hFile, &item) )
			{
				if( !(item.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) &&
						strcmp( item.cFileName, "." ) && 
						strcmp( item.cFileName, ".." ) )
				{
					len = strlen(item.cFileName);

					if ( len > 4 && item.cFileName[len - 4] == '.' && (item.cFileName[len - 3] == 'i' || item.cFileName[len - 3] == 'I') && (item.cFileName[len - 2] == 'n' || item.cFileName[len - 2] == 'N') && (item.cFileName[len - 1] == 'i' || item.cFileName[len - 1] == 'I') )
					{
						GetCurrentDirectory(MAX_PATH, fileNameWithPath );
						strcat( fileNameWithPath, "\\" );
						strcat( fileNameWithPath, item.cFileName );
						ret = ret && extractProcess( fileNameWithPath );
					}
				}
			}

			FindClose( hFile );
		}
	}

	SetCurrentDirectory( currDir );
	return ret;
}

bool ImagePacker::loadINIFile()
{
	FILE *fp = m_extractFile[0] ? fopen( m_extractFile, "r" ) : NULL;

	if (!fp)
	{
		sprintf( s_ErrorMessage, "Cannot open INI file '%s' for writing AGEOIWHG.", m_extractFile );
		return false;
	}

	char buffer[1024];
	const char *tokenSep = " \n\r\t=:";;
	std::vector<ImageInfoClass *> imageVector;

	while ( fgets( buffer, 1024, fp ) )
	{
		char *mappedImage = strtok( buffer, tokenSep );

		if ( !mappedImage || strcmp( mappedImage, "MappedImage" ) )
		{
			continue;
		}

		ImageInfoClass *info = new ImageInfoClass;

		if ( !info )
		{
			strcpy( s_ErrorMessage, "Unable to allocate image info" );
			return false;
		}

		char *imageName = strtok( 0, tokenSep );

		if ( !imageName )
		{
			sprintf( s_ErrorMessage, "Unable to find ImageName for record #%d", imageVector.size() + 1 );
			return false;
		}

		info->m_origFileNameBase = new char[strlen( imageName ) + 1];
		strcpy( info->m_origFileNameBase, imageName );
		bool textureFound = true;

		while ( fgets( buffer, 1024, fp ) )
		{
			char *field = strtok( buffer, tokenSep );

			if ( !strcmp( field, "End" ) )
			{
				break;
			}

			if ( !strcmp( field, "Texture" ) )
			{
				char *textureName = strtok( 0, tokenSep );

				if ( !textureName )
				{
					sprintf( s_ErrorMessage, "%s Does not have a valid value for Texture", info->m_filenameOnlyNoExt );
					return false;
				}

				info->m_fullName = findTextureInDirs( textureName );

				if ( !info->m_fullName )
				{
					textureFound = false;
				}
				else
				{
					char *charPtr = strrchr( info->m_fullName, '\\' );

					if ( !charPtr )
					{
						sprintf( s_ErrorMessage, "int32_ternal Error: File not complete path: %s", info->m_fullName );
						return false;
					}

					info->m_filenameOnly = new char[strlen( charPtr ) + 1];
					strcpy( info->m_filenameOnly, charPtr + 1 );
					info->m_filenameOnlyNoExt = new char[strlen( charPtr ) + 1];
					strcpy( info->m_filenameOnlyNoExt, charPtr + 1 );
					charPtr = strchr( info->m_filenameOnlyNoExt, '.' );

					if ( charPtr )
					{
						*charPtr = 0;
					}
				}

				continue;
			}
			
			if ( !strcmp( field, "TextureWidth" ) )
			{
				continue;
			}

			if ( !strcmp( field, "TextureHeight" ) )
			{
				continue;
			}

			if ( !strcmp( field, "Coords" ) )
			{
				for ( int lp = 0; lp < 4; lp++ )
				{
					char *locStr = strtok( 0, tokenSep );
					char *valueStr = strtok( 0, tokenSep );

					if ( !locStr || !valueStr )
					{
						sprintf( s_ErrorMessage, "%s Does not have a valid value for Coord", info->m_filenameOnlyNoExt );
						return false;
					}

					int value = atoi( valueStr );

					if ( !strcmp( locStr, "Left" ) )
					{
						info->m_pagePos.lo.x = value;
					}
					else if ( !strcmp( locStr, "Right" ) )
					{
						info->m_pagePos.hi.x = value - 1;
					}
					else if ( !strcmp( locStr, "Top" ) )
					{
						info->m_pagePos.lo.y = value;
					}
					else if ( !strcmp( locStr, "Bottom" ) )
					{
						info->m_pagePos.hi.y = value - 1;
					}
					else
					{
						sprintf( s_ErrorMessage, "%s Does not have a valid value for Coord", info->m_filenameOnlyNoExt );
						return false;
					}
				}

				continue;
			}

			if (!strcmp( field, "Status" ) )
			{
				char *valueStr = strtok( 0, tokenSep );

				if ( !strcmp( valueStr, "ROTATED_90_CLOCKWISE" ) )
				{
					info->m_status |= ImageInfoClass::ROTATED90C;
				}

				continue;
			}

			sprintf( s_ErrorMessage, "%s Has unrecognized token : \"%s\"", info->m_filenameOnlyNoExt, field );
			return false;
		}

		if ( textureFound )
		{
			imageVector.push_back( info );
			info->m_size.x = info->m_pagePos.hi.x - info->m_pagePos.lo.x + 1;
			info->m_size.y = info->m_pagePos.hi.y - info->m_pagePos.lo.y + 1;
			info->m_area = info->m_size.x * info->m_size.y;
			setTargetSize( info->m_pagePos.hi.x - info->m_pagePos.lo.x, info->m_pagePos.hi.y - info->m_pagePos.lo.y );
			std::string texturePath( info->m_fullName );
			std::map<std::string,unsigned int>::iterator it = m_textureImageCount.find( texturePath );

			if ( it != m_textureImageCount.end()	)
			{
				unsigned int count = it->second;
				m_textureImageCount[texturePath] = count + 1;
			}
			else
			{
				m_textureImageCount[texturePath] = 0;
			}
		}
		else
		{
			delete info;
		}
	}

	m_imageList->clear();

	for ( unsigned int i = 0; i < imageVector.size(); i++ )
	{
		m_imageList->push_back( imageVector[i] );
	}
	
	fclose( fp );
	return true;
}

bool ImagePacker::extractMappedTextures()
{
	bool success = true;
	Targa *source = NULL;
	char *sourceName = NULL;

	if ( !getImageCount() )
	{
		return success;
	}

	char outputDirectory[ _MAX_PATH ];
	strcpy( outputDirectory, m_outputDirectory );
	CreateDirectory( m_outputDirectory, NULL );
	char *extractName = strrchr( m_extractFile, '\\' );

	if ( !extractName )
	{
		sprintf( s_ErrorMessage, "%s Is not a valid file to extract to", m_extractFile );
		return false;
	}

	strcat( m_outputDirectory, extractName + 1 );

	char *dot = strrchr( m_outputDirectory, '.' );

	if ( dot )
	{
		*dot = 0;
	}

	strcat( m_outputDirectory, "\\" );
	CreateDirectory( m_outputDirectory, NULL );
	char outputDirectoryWithINI[ _MAX_PATH ];

	for (unsigned int lp = 0; lp < getImageCount(); lp++)
	{
		strcpy( outputDirectoryWithINI, m_outputDirectory );
		ImageInfoClass *info = (*m_imageList)[lp];

		if ( !source || strcmp( sourceName, info->m_fullName ) )
		{
			sourceName = info->m_fullName;

			if ( source )
			{
				delete source;
			}

			source = new Targa;
			source->Load( sourceName, TGAF_IMAGE, false );
		}

		std::string texturePath( info->m_fullName );

		std::map<std::string,unsigned int>::iterator it = m_textureImageCount.find( texturePath );

		if (it != m_textureImageCount.end() && it->second > 1)
		{
			strcat( outputDirectoryWithINI, info->m_filenameOnlyNoExt );
			strcat( outputDirectoryWithINI, "\\" );
			CreateDirectory( outputDirectoryWithINI, NULL );
		}

		if ( !extractAndSaveTarga( *info, *source, outputDirectoryWithINI ) )
		{
			success = false;
			break;
		}
	}

	if ( source )
	{
		delete source;
	}

	strcpy( m_outputDirectory, outputDirectory );
	return success;
}

bool ImagePacker::extractAndSaveTarga(ImageInfoClass &image,Targa &sourceTarga,char *outputDir)
{
	char *sourceBuffer = sourceTarga.GetImage();

	if ( !sourceBuffer )
	{
		sprintf( s_ErrorMessage, "int32_ternal Error: Source has no data." );
		return false;
	}

	int bpp = (sourceTarga.Header.PixelDepth + 7) >> 3;
	int bufferSize = image.m_size.x * image.m_size.y * bpp;
	char *destBuffer = (char *)malloc( bufferSize );
	memset( destBuffer, 31, bufferSize );
	Targa destTarga;
	destTarga.SetImage( destBuffer );
	destTarga.Header.ImageType = 2;
	destTarga.Header.Width = image.m_size.x;
	destTarga.Header.Height = image.m_size.y;
	destTarga.Header.PixelDepth = sourceTarga.Header.PixelDepth;
	int startX = image.m_pagePos.lo.x;
	int startY = image.m_pagePos.lo.y;

	for (int y = 0; y < image.m_size.y; y++)
	{
		char *src = sourceBuffer + bpp * (startX + (sourceTarga.Header.Height - (y + startY + 1)) * sourceTarga.Header.Width);
		char *dst = destBuffer + (image.m_size.y - (y + 1)) * image.m_size.x * bpp;

		for (int x = 0; x < image.m_size.x; x++)
		{
			dst[3] = src[0];
			dst[2] = src[1];
			dst[1] = src[2];

			if (bpp == 4)
			{
				dst[0] = src[3];
			}

			src += bpp;
			dst += bpp;
		}
	}

	char filePath[ _MAX_PATH ];
	sprintf( filePath, "%s%s.tga", outputDir, image.m_origFileNameBase );
	destTarga.Save( filePath, TGAF_IMAGE, false );
	return true;
}

char *ImagePacker::findTextureInDirs(const char *imageName)
{
	char currDir[ _MAX_PATH ];
	WIN32_FIND_DATA item;
	HANDLE hFile;
	char *retFilename;
	ImageDirectory *dir;

	GetCurrentDirectory( _MAX_PATH, currDir );
	retFilename = NULL;

	for ( dir = m_dirList; dir; dir = dir->m_next )
	{
		SetCurrentDirectory( dir->m_path );
		hFile = FindFirstFile( imageName, &item );
		
		if (hFile == INVALID_HANDLE_VALUE)
		{
			continue;
		}

		retFilename = new char[ _MAX_PATH ];
		strcpy( retFilename, dir->m_path );
		strcat( retFilename, item.cFileName );
		break;
	}

	if ( !retFilename )
	{
		char extractDir[ _MAX_PATH ];

		strcpy( extractDir, m_extractFile );
		char *pathOnly = strrchr( extractDir, '\\' );

		if (pathOnly)
		{
			pathOnly[1] = 0;
			SetCurrentDirectory( extractDir );
			hFile = FindFirstFile( imageName, &item );

			if ( hFile != INVALID_HANDLE_VALUE )
			{
				retFilename = new char[ _MAX_PATH ];
				strcpy( retFilename, extractDir );
				strcat( retFilename, item.cFileName );
			}
		}
	}

	SetCurrentDirectory( currDir );
	return retFilename;
}

HANDLE MyCreateFile(LPCSTR lpFileName, DWORD dwDesiredAccess, DWORD dwShareMode, LPSECURITY_ATTRIBUTES lpSecurityAttributes, DWORD dwCreationDisposition, DWORD dwFlagsAndAttributes, HANDLE hTemplateFile)
{
	return CreateFile(lpFileName, dwDesiredAccess, dwShareMode, lpSecurityAttributes, dwCreationDisposition, dwFlagsAndAttributes, hTemplateFile);
}
