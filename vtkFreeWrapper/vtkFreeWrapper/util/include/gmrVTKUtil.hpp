/*
 * VTK���ȒP�Ɂi�H�j�g�����߂̊ȒP�N���X���C�u����
 * Copyright (c) BCFalcon
 *
 *
 * Kitware Inc - Leaders in Visualization Technology 
 * Copyright (c) 1993-2006 Ken Martin, Will Schroeder, Bill Lorensen 
 * All rights reserved.
 *
 */
#ifndef _GMRVTKUTIL_HPP
#define _GMRVTKUTIL_HPP

#include "gmrVTK.hpp"

#ifdef WIN32
#include <windows.h>
#endif

#include <string>

/** 
 * @brief Win32�R�}���h���s�N���X
 * - �֘A�t��������ꍇ�̓t�@�C���������Ŏ��s�����
 */
class gmr_EXPORT gmrVTKShellExecute
{

	/** �R�}���h���s
	 *
	 */
	int RunCommand();

public:
	std::string command_;

	gmrVTKShellExecute();
	gmrVTKShellExecute(const char* command)
	{
		command_ = command;
	}

	virtual ~gmrVTKShellExecute();

	/** ���s�R�}���h�̎w��i�֘A�t��������ꍇ�̓t�@�C�������w��j
	 *
	 * @param [in] command ���s�R�}���h�܂��͊֘A�t��������ꍇ�̓t�@�C����
	 *
	 */
	void SetCommand(const char* command)
	{
		command_ = command;
	}


	/** �R�}���h���s
	 *
	 */
	void Run();
};

#endif