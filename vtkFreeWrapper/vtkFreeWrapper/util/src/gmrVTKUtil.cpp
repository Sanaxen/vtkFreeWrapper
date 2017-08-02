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

#include "gmrVTKUtil.hpp"

gmrVTKShellExecute::gmrVTKShellExecute()
{
	command_ = "";
}

gmrVTKShellExecute::~gmrVTKShellExecute()
{
}

int gmrVTKShellExecute::RunCommand()
{
	if ( command_ == "" ) return 1;
	int	stat;

	stat = -99;
#ifdef WIN32

	LPSTR comspec;
	LPSTR p;
	HINSTANCE	hinst;
	HANDLE		hnd;
	char	command[256];
	char envbuf[81];

	hnd = GetCurrentProcess();
	GetEnvironmentVariable("COMSPEC", envbuf, 80);
	if (*envbuf == '\0')
		comspec = "\\command.com";
	else
		comspec = envbuf;


	char tmp[256];
	strcpy( tmp, command_.c_str());
	p = tmp;
	while ((*p == ' ') || (*p == '\n') || (*p == '\r'))
		p++;

	if (*p == '\0') {
		strcpy(command, comspec);
	} else {
		strcpy(command, tmp);
	}

	hinst = ShellExecute( NULL,	"open", command, NULL, NULL, SW_SHOW);
	if ( hinst == NULL ){
		// メモリーが不十分で実行出来ません
		return -99;
	}
	stat = (int )hinst;

	if ( stat <= 32 ){
		stat = WinExec(command, SW_SHOWNORMAL);
		if (stat <= 32) {
			strcpy(command, comspec);
			strcat(command, " /c ");
			strcat(command, tmp);
			stat = WinExec(command, SW_SHOWNORMAL);
		}
	}

	switch( stat ){
	case SE_ERR_ASSOCINCOMPLETE:
		throw("関連付けされていないファイルのため実行出来ません");
		break;
	case SE_ERR_NOASSOC:
		throw("関連付けされていない拡張子");
		break;
	default:
		if ( stat <= 32 ){
			throw("関連付けが無いか実行可能なファイルではない");
		}
		break;
	}

#endif
	return stat;
}

void gmrVTKShellExecute::Run()
{
	try {
		RunCommand();
	}
	catch(...)
	{
		;//error
	}
}



