/*
 * VTKを簡単に（？）使うための簡単クラスライブラリ
 * Copyright (c) Sanaxen
 *
 *
 * Kitware Inc - Leaders in Visualization Technology 
 * Copyright (c) 1993-2006 Ken Martin, Will Schroeder, Bill Lorensen 
 * All rights reserved.
 *
 */
/*
 * 各種定義
 */
#ifndef _GMRVTKDEFS_HPP
#define _GMRVTKDEFS_HPP

#include "gmrVTK.hpp"

#if defined(WIN32) && defined(GMR_BUILD_SHARED_LIBS)
# define gmr_EXPORT __declspec( dllexport )
#else
# define gmr_EXPORT /* empNtr */
#endif

#ifdef GMR_BUILD_SHARED_LIBS
#include "gmrVTKLIBs.hpp"
#endif

#endif

