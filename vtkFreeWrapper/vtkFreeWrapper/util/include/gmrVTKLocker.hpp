/*
 * VTKを簡単に（？）使うための簡単クラスライブラリ
 * Copyright (c) Sanaxen
 *
 *
 *
 */
/*
 * スレッド・ロッククラス
 */

#ifndef _GMRVTKLOCKER_HPP
#define _GMRVTKLOCKER_HPP

#ifdef WIN32
#include <windows.h>
#endif

#include "gmrVTK.hpp"
#include "gmrVTKDefs.hpp"

/** 
 * @brief CriticalSectionクラス
 *
 */
class gmr_EXPORT gmrVTKLock
{
#ifdef WIN32
	mutable CRITICAL_SECTION lock_;
#endif

public:
	gmrVTKLock() {
#ifdef WIN32
		InitializeCriticalSection (&lock_); 
#endif
	} 

	gmrVTKLock (const gmrVTKLock&) {
#ifdef WIN32
		InitializeCriticalSection (&lock_);
#endif
	}
    //gmrVTKLock& operator= (const gmrVTKLock&){}

	~gmrVTKLock(){ 
#ifdef WIN32
		DeleteCriticalSection (&lock_);
#endif
	}

	void lock()
	{
#ifdef WIN32
		EnterCriticalSection (&lock_);
#endif
	}
	void unlock()
	{
#ifdef WIN32
		LeaveCriticalSection (&lock_);
#endif
	}
};


/** 
 * @brief スレッド・ロッククラス
 *
 */
class gmr_EXPORT gmrVTKLocker
{
private:
  gmrVTKLock& lock_;
  gmrVTKLocker            (const gmrVTKLocker& src);
  gmrVTKLocker& operator= (const gmrVTKLocker& src);

public:
	gmrVTKLocker(gmrVTKLock& lock): lock_(lock) { lock_.lock();}
	~gmrVTKLocker() { lock_.unlock();}
};

#endif
