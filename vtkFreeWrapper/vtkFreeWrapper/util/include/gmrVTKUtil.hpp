/*
 * VTKを簡単に（？）使うための簡単クラスライブラリ
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
 * @brief Win32コマンド実行クラス
 * - 関連付けがある場合はファイル名だけで実行される
 */
class gmr_EXPORT gmrVTKShellExecute
{

	/** コマンド実行
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

	/** 実行コマンドの指定（関連付けがある場合はファイル名を指定）
	 *
	 * @param [in] command 実行コマンドまたは関連付けがある場合はファイル名
	 *
	 */
	void SetCommand(const char* command)
	{
		command_ = command;
	}


	/** コマンド実行
	 *
	 */
	void Run();
};

#endif