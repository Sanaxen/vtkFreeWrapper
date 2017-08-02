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
		// �������[���s�\���Ŏ��s�o���܂���
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
		throw("�֘A�t������Ă��Ȃ��t�@�C���̂��ߎ��s�o���܂���");
		break;
	case SE_ERR_NOASSOC:
		throw("�֘A�t������Ă��Ȃ��g���q");
		break;
	default:
		if ( stat <= 32 ){
			throw("�֘A�t�������������s�\�ȃt�@�C���ł͂Ȃ�");
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



