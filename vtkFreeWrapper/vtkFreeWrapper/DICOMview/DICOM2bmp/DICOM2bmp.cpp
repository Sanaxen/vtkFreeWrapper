/************************************************************
*
* vtkWrapperLIBを使った簡単なサンプルプログラム
*
*************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../MRI_view__.h"
//#include "gmrVTKLIBs.hpp"

#ifdef _WIN64
#ifdef _DEBUG
#pragma comment( lib, "../../Debug/64bit/DICOMview.lib")
#else
#pragma comment( lib, "../../Release/64bit/DICOMview.lib")
#endif
#else
#ifdef _DEBUG
#pragma comment( lib, "../../Debug/32bit/DICOMview.lib")
#else
#pragma comment( lib, "../../Release/32bit/DICOMview.lib")
#endif
#endif

int main(int argc, char** argv)
{
	char* folderName;
	
	if ( argc < 2 )
	{
		fprintf(stderr, "usage: DICOM2BMP.exe dcm-files-folderName [-option]\n");
		fprintf(stderr, "option\n");
		fprintf(stderr, "-3d [isovalue]=> 3D viewer\n");
		fprintf(stderr, "-vr [1.0] [isovalue]=> volume render.\n\tsample_distace(default 1.0)\n");
		fprintf(stderr, "-bmp => slice viewer && bitmap capture\n");
		fprintf(stderr, "-obj [isovalue]=> obj convert\n");
		fprintf(stderr, "-stl [isovalue]=> stl convert\n");
		fprintf(stderr, "no option => slice viewer\n");
		return 1;
	}
	folderName = argv[1];

	double isovalue = -1.0E32;
	double sample_dist = -1.0;
	if ( argc >= 3 && argv[2][0] == '-' && strcmp(argv[2]+1, "3d") == 0  )
	{
		fprintf(stderr, "==> 3d viewer!!\n");
		if (argc == 4) isovalue = atof(argv[3]);
		DICOM_3DViewer(folderName, 0, sample_dist, isovalue);
		return 0;
	}
	if ( argc >= 3 && argv[2][0] == '-' && strcmp(argv[2]+1, "vr") == 0  )
	{
		sample_dist = 1.0;
		fprintf(stderr, "==> volume render viewer!!\n");
		if (argc >= 4) sample_dist = atof(argv[3]);
		if (argc == 5) isovalue = atof(argv[4]);
		DICOM_3DViewer(folderName, 100, sample_dist, isovalue);
		return 0;
	}
	if (argc >= 3 && argv[2][0] == '-' && strcmp(argv[2] + 1, "3dvr") == 0)
	{
		sample_dist = 1.0;
		fprintf(stderr, "==> volume render & 3d viewer!!\n");
		if (argc >= 4) sample_dist = atof(argv[3]);
		if (argc == 5) isovalue = atof(argv[4]);
		DICOM_3DViewer(folderName, 101, sample_dist, isovalue);
		return 0;
	}

	if ( argc == 3 && argv[2][0] == '-' && strcmp(argv[2]+1, "bmp") == 0 )
	{
		fprintf(stderr, "==> bitmap!!\n");
		DICOM2BMP(folderName);
		fprintf(stderr, "==> convert bitmap!!\n");
		return 0;
	}

	if ( argc >= 3 && argv[2][0] == '-' && strcmp(argv[2]+1, "obj-") == 0 )
	{
		fprintf(stderr, "==> obj!!\n");
		if (argc >= 4) isovalue = atof(argv[3]);
		DICOM2OBJ(folderName, 1, isovalue);
		fprintf(stderr, "==> convert obj!!\n");
		return 0;
	}
	if ( argc >= 3 && argv[2][0] == '-' && strcmp(argv[2]+1, "obj") == 0 )
	{
		fprintf(stderr, "==> obj!!\n");
		if (argc >= 4) isovalue = atof(argv[3]);
		DICOM2OBJ(folderName, 0, isovalue);
		fprintf(stderr, "==> convert obj!!\n");
		return 0;
	}


	if ( argc >= 3 && argv[2][0] == '-' && strcmp(argv[2]+1, "stl-") == 0 )
	{
		fprintf(stderr, "==> stl!!\n");
		if (argc >= 4) isovalue = atof(argv[3]);
		DICOM2STL(folderName, 1, isovalue);
		fprintf(stderr, "==> convert stl!!\n");
		return 0;
	}
	if ( argc >= 3 && argv[2][0] == '-' && strcmp(argv[2]+1, "stl") == 0 )
	{
		fprintf(stderr, "==> stl!!\n");
		if (argc >= 4) isovalue = atof(argv[3]);
		DICOM2STL(folderName, 0, isovalue);
		fprintf(stderr, "==> convert stl!!\n");
		return 0;
	}


	if ( argc >= 3 && argv[2][0] == '-' && strcmp(argv[2]+1, "wrl-") == 0 )
	{
		fprintf(stderr, "==> wrl!!\n");
		if (argc >= 4) isovalue = atof(argv[3]);
		DICOM2VRML(folderName, 1, isovalue);
		fprintf(stderr, "==> convert x3d!!\n");
		return 0;
	}
	if ( argc >= 3 && argv[2][0] == '-' && strcmp(argv[2]+1, "wrl") == 0 )
	{
		fprintf(stderr, "==> wrl!!\n");
		if (argc >= 4) isovalue = atof(argv[3]);
		DICOM2VRML(folderName, 0, isovalue);
		fprintf(stderr, "==> convert x3d!!\n");
		return 0;
	}



	if ( argc >= 3 && argv[2][0] == '-' && strcmp(argv[2]+1, "x3d-") == 0 )
	{
		fprintf(stderr, "==> x3d!!\n");
		if (argc >= 4) isovalue = atof(argv[3]);
		DICOM2X3D(folderName, 1, isovalue);
		fprintf(stderr, "==> convert x3d!!\n");
		return 0;
	}
	if ( argc >= 3 && argv[2][0] == '-' && strcmp(argv[2]+1, "x3d") == 0 )
	{
		fprintf(stderr, "==> x3d!!\n");
		if (argc >= 4) isovalue = atof(argv[3]);
		DICOM2X3D(folderName, 0, isovalue);
		fprintf(stderr, "==> convert x3d!!\n");
		return 0;
	}

	DICOM_SliceViewer(folderName, 0);
	
	return 0;
}
