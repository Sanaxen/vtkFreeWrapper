/*
 * VTK���ȒP�Ɂi�H�j�g�����߂̊ȒP�N���X���C�u����
 * Copyright (c) Sanaxen
 *
 *
 * Kitware Inc - Leaders in Visualization Technology 
 * Copyright (c) 1993-2006 Ken Martin, Will Schroeder, Bill Lorensen 
 * All rights reserved.
 *
 */
/*
 * �e���`
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

