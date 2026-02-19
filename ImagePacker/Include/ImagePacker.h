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

// FILE: ImagePacker.h ////////////////////////////////////////////////////////
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
// File name:  ImagePacker.h
//
// Created:    Colin Day, August 2001
//
// Desc:       Image packer tool
//
//-----------------------------------------------------------------------------
///////////////////////////////////////////////////////////////////////////////

#pragma once

#ifndef __IMAGEPACKER_H_
#define __IMAGEPACKER_H_

// SYSTEM INCLUDES ////////////////////////////////////////////////////////////
#include <windows.h>
#include <vector>
#include <string>
#include <map>

// USER INCLUDES //////////////////////////////////////////////////////////////
#include "BaseType.h"
#include "Targa.h"
#include "ImageDirectory.h"
#include "ImageInfo.h"
#include "TexturePage.h"

// FORWARD REFERENCES /////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// TYPE DEFINES ///////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
#define MAX_OUTPUT_FILE_LEN 512
#define DEFAULT_TARGET_SIZE 512

// ImagePacker ----------------------------------------------------------------
// Class interface for running the image packer */
//-----------------------------------------------------------------------------
class ImagePacker
{

public:
	
	enum
	{
		GAP_METHOD_EXTEND_RGB	= 0x00000001,  ///< extend RGB (no alpha) of image on all sides
		GAP_METHOD_GUTTER			= 0x00000002,  ///< put transparent gutter on right and bottom side of image
	};

	enum BatchModeEnum
	{
		BM_OFF,
		BM_PACK,
		BM_EXTRACT
	};

public:
	typedef std::vector<std::string> StringVector;
	
	ImagePacker( void );
	virtual ~ImagePacker( void );

	Bool init( void );  ///< initialize the system
	Bool process( void );  ///< run the process
	Bool extract( void );  ///< extract

	void setBatchMode( BatchModeEnum to ) { m_batchMode = to; }
	BatchModeEnum getBatchMode() const { return m_batchMode; }

	void setWindowHandle( HWND hWnd );  ///< set window handle for 'dialog' app
	HWND getWindowHandle( void );  ///< get window handle for 'dialog' app

	ICoord2D *getTargetSize( void );  ///< get target size
	Int getTargetWidth( void );  ///< get target width
	Int getTargetHeight( void );  ///< bet target height

	void statusMessage( char *message );  ///< set a status message

	UnsignedInt getImageCount( void );  ///< get image count
	ImageInfoClass *getImage( Int index );  ///< get image
	TexturePage *getFirstTexturePage( void );  ///< get first texture page

	UnsignedInt getPageCount( void );  ///< get the count of texutre pages

	void setTargetPreviewPage( Int page );  ///< set the target preview page to view
	Int getTargetPreviewPage( void );  ///< get the target preview page to view

	void setGutter( UnsignedInt size );  ///< set gutter size in pixels
	UnsignedInt getGutter( void );  ///< get gutter size in pixels
	void setGapMethod( UnsignedInt methodBit );  ///< set gap method option
	void clearGapMethod( UnsignedInt methodBit );  ///< clear gap method option
	UnsignedInt getGapMethod( void );  ///< get gap method option

	void setExtendAlpha( Bool extendAlpha );  ///< set extend alpha option
	Bool getExtendAlpha( void ) { return m_extendAlpha; }

	void setOutputAlpha( Bool outputAlpha );  ///< set output alpha option
	Bool getOutputAlpha( void );  ///< get output alpha option

	void setPreviewWindow( HWND window );  ///< assign preview window handle
	HWND getPreviewWindow( void );  ///< get the preview window handle

	void setUseTexturePreview( Bool use );  ///< use the real image data in preview
	Bool getUseTexturePreview( void );  ///< get texture preview option

	void setINICreate( Bool create );  ///< set create INI file option
	void setXMLCreate( Bool create );  ///< set create XML file option
	Bool createINIFile( void );  ///< get create INI option
	Bool createXMLFile( void );  ///< get create XML option

	Bool getOnlyPackOne( void );  ///< get only pack one option
	void setOnlyPackOne( Bool onlyPackOne );  ///< set only pack one option

	char *getOutputFile( void );  ///< get output filename

	void setCompressTextures( Bool compress );  ///< set compress textures option
	Bool getCompressTextures( void );  ///< get compress textures option

	void setOutputDirectory(const char *to);  ///< set output directory
	const char *getOutputDirectory( void );  ///< get output directory

	void onDialogInitialized(HWND dialog);  ///< on dialog initialized

	void setExtractFile(const char *extract);  ///< set extract file
	const char *getExtractFile();  ///< get extract file
	Bool fileNameZeroPad() const { return m_fileNameZeroPad; }
	Bool AllowRotate() const { return m_allowRotate; }

protected:
	bool loadINIFile();  ///< load INI file
	bool extractMappedTextures();  ///< extract mapped textures
	bool extractAndSaveTarga( ImageInfoClass &image, Targa &sourceTarga, char *outputDir );  ///< extract and save targa
	char *findTextureInDirs( const char *imageName );  ///< find texture in dirs

	void setTargetSize( Int width, Int height );  ///< set the size of the output target image

	void resetImageDirectoryList( void );  ///< clear the image directory list
	void resetImageList( void );  ///< clear the image list
	void resetPageList( void );  ///< clear the texture page list
	void addDirectory( char *path, Bool subDirs );  ///< add directory to directory list
	void addImagesInDirectory( char *dir );  ///< add all images from the specified directory
	void addImage( char *path );  ///< add image to image list
	Bool validateImages( void );  ///< validate that the loaded images can all be processed
	Bool packImages( void );  ///< do the packing
	void writeFinalTextures( void );  ///< write the packed textures

	Bool generateINIFile( void );  ///< generate the INI file for this image set
	Bool generateXMLFile( Bool onDemand );  ///< generate the XML file for this image set

	TexturePage *createNewTexturePage( ICoord2D minSize );  ///< create a new texture page

	void sortImageList( void );  ///< sort the image list
	bool extractProcess( char *fileName );  ///< extract process

	HWND m_hWnd;  ///< window handle for app
	ICoord2D m_targetSize;  ///< the target size
	Bool m_useSubFolders;  ///< use subfolders option
	char m_outputFile[ MAX_OUTPUT_FILE_LEN ];  ///< output filename 
	char m_outputDirectory[ _MAX_PATH ];  ///< destination for texture files
	char m_extractFile[ _MAX_PATH ];  ///< extract file

	ImageDirectory *m_dirList;  ///< the directory list
	UnsignedInt m_dirCount;  ///< length of dirList
	UnsignedInt m_imagesInDirs;  ///< number of images in all directories
	std::vector<ImageInfoClass *> *m_imageList;  ///< the image list
	char m_statusBuffer[ 1024 ];  ///< for printing status messages
	TexturePage *m_pageTail;  ///< end of the texture page list
	TexturePage *m_pageList;  ///< the final images generated from the packer
	UnsignedInt m_pageCount;  ///< length of page list
	UnsignedInt m_gapMethod;  ///< gap method option bits
	UnsignedInt m_gutterSize;  ///< gutter gaps between images in pixels
	Bool m_outputAlpha;  ///< final image files will have an alpha channel
	Bool m_sortImages;  ///< images will be sorted
	Bool m_keepDirsSeperate;  ///< dirs will be kept seperate
	Bool m_createINI;  ///< create the INI file from compressed image data
	Bool m_createXML;  ///< create the XML file from compressed image data
	Bool m_fileNameZeroPad;  ///< zero pad filename
	Bool m_allowRotate;  ///< allow rotate
	Bool m_extendAlpha;  ///< extend alpha
	Bool m_onlyPackOne;  ///< only pack one

	Int m_targetPreviewPage;  ///< preview page we're looking at
	HWND m_hWndPreview;  ///< the preview window
	Bool m_showTextureInPreview;  ///< show actual texture in preview window
	
	Targa *m_targa;  ///< targa for loading file headers
	Bool m_compressTextures;  ///< compress the final textures
	BatchModeEnum m_batchMode;  ///< batch mode
	StringVector m_commandLineDirectories;
	std::map<std::string,unsigned int> m_textureImageCount;
	const char *m_textureFormat;
};

///////////////////////////////////////////////////////////////////////////////
// INLINING ///////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
inline void ImagePacker::setTargetSize( Int width, Int height ) { m_targetSize.x = width; m_targetSize.y = height; }
inline ICoord2D *ImagePacker::getTargetSize( void ) { return &m_targetSize; }
inline Int ImagePacker::getTargetWidth( void ) { return m_targetSize.x; }
inline Int ImagePacker::getTargetHeight( void ) { return m_targetSize.y; }
inline void ImagePacker::setWindowHandle( HWND hWnd ) { m_hWnd = hWnd; }
inline HWND ImagePacker::getWindowHandle( void ) { return m_hWnd; }
inline UnsignedInt ImagePacker::getImageCount( void ) { return m_imageList->size(); }
inline ImageInfoClass *ImagePacker::getImage( Int index ) { return (*m_imageList)[ index ]; }
inline void ImagePacker::setTargetPreviewPage( Int page ) { m_targetPreviewPage = page; }
inline Int ImagePacker::getTargetPreviewPage( void ) { return m_targetPreviewPage; }
inline UnsignedInt ImagePacker::getPageCount( void ) { return m_pageCount; }
inline void ImagePacker::setPreviewWindow( HWND window ) { m_hWndPreview = window; }
inline HWND ImagePacker::getPreviewWindow( void ) { return m_hWndPreview; }
inline void ImagePacker::setGutter( UnsignedInt size ) { m_gutterSize = size; }
inline UnsignedInt ImagePacker::getGutter( void ) { return m_gutterSize; }
inline void ImagePacker::setOutputAlpha( Bool outputAlpha ) { m_outputAlpha = outputAlpha; }
inline Bool ImagePacker::getOutputAlpha( void ) { return m_outputAlpha; }
inline TexturePage *ImagePacker::getFirstTexturePage( void ) { return m_pageList; }
inline void ImagePacker::setUseTexturePreview( Bool use ) { m_showTextureInPreview = use; }
inline Bool ImagePacker::getUseTexturePreview( void ) { return m_showTextureInPreview; }
inline void ImagePacker::setINICreate( Bool create ) { m_createINI = create; };
inline void ImagePacker::setXMLCreate( Bool create ) { m_createXML = create; };
inline Bool ImagePacker::createINIFile( void ) { return m_createINI; }
inline Bool ImagePacker::createXMLFile( void ) { return m_createXML; }
inline char *ImagePacker::getOutputFile( void ) { return m_outputFile; }
inline void ImagePacker::setCompressTextures( Bool compress ) { m_compressTextures = compress; }
inline Bool ImagePacker::getCompressTextures( void ) { return m_compressTextures; }
inline void ImagePacker::setGapMethod( UnsignedInt methodBit ) { BitSet( m_gapMethod, methodBit ); }
inline void ImagePacker::clearGapMethod( UnsignedInt methodBit ) { BitClear( m_gapMethod, methodBit ); }
inline UnsignedInt ImagePacker::getGapMethod( void ) { return m_gapMethod; }
inline const char *ImagePacker::getOutputDirectory( void ) { return m_outputDirectory; }

///////////////////////////////////////////////////////////////////////////////
// EXTERNALS //////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
extern ImagePacker *TheImagePacker;

#endif // __IMAGEPACKER_H_

