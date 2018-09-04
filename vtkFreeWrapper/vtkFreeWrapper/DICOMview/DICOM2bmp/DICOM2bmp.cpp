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
#pragma comment( lib, "../../x64/Debug/DICOMview.lib")
#else
#pragma comment( lib, "../../x64/Release/DICOMview.lib")
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
	char* outfile = NULL;

	if ( argc < 2 )
	{
		fprintf(stderr, "usage: DICOM2BMP.exe dcm-files-folderName [-option]\n");
		fprintf(stderr, "option\n");
		fprintf(stderr, "-3d => 3D viewer\n");
		fprintf(stderr, "-vr => volume render.\n\tsample_distace(default 1.0)\n");
		fprintf(stderr, "-bmp => slice viewer && bitmap capture\n");
		fprintf(stderr, "-obj => obj convert\n");
		fprintf(stderr, "-stl => stl convert\n");
		fprintf(stderr, "-iso isovalue\n");
		fprintf(stderr, "-sample_dist sample_dist\n");
		fprintf(stderr, "-o filename\n");

		fprintf(stderr, "-smooth smoothing_itr => output mesh only\n");
		fprintf(stderr, "-target_reduction resize(%%) => output mesh only\n");
		fprintf(stderr, "-s slice_image_num\n");
		fprintf(stderr, "-base_name image_base_name\n");
		fprintf(stderr, "no option => slice viewer\n");
		return 1;
	}
	folderName = argv[1];

#define POLYGON_VIEW			1
#define VOLUME_VIEW				2
#define POLYGON_VOLUME_VIEW		3
#define BITMAP_VIEW				4
#define EXPORT_OBJ				5
#define EXPORT_STL				6
#define EXPORT_WRL				7
#define EXPORT_X3D				8

	double isovalue = 0.0;// -1.0E32;
	double sample_dist = -1.0;
	double targetReduction = 0.05;

	char* base_name = NULL;
	int slice_image_num = -1;
	bool isovalue_set = false;

	int export_and_view = 0;
	int mode = -1;
	for (int i = 2; i < argc; ++i)
	{
		if (strcmp("-smooth", argv[i]) == 0)
		{
			setSmoothing(atoi(argv[i + 1]));
			i++;
			continue;
		}
		if (strcmp("-target_reduction", argv[i]) == 0)
		{
			targetReduction = atof(argv[i + 1]);
			i++;
			continue;
		}
		if (strcmp("-base_name", argv[i]) == 0)
		{
			base_name = argv[i + 1];
			i++;
			continue;
		}
		if (strcmp("-s", argv[i]) == 0)
		{
			slice_image_num = atoi(argv[i+1]);
			i++;
			continue;
		}

		if (strcmp("-3dvr", argv[i]) == 0)
		{
			mode = POLYGON_VOLUME_VIEW;
			continue;
		}
		if (strcmp("-3d", argv[i]) == 0)
		{
			mode = POLYGON_VIEW;
			continue;
		}
		if (strcmp("-vr", argv[i]) == 0)
		{
			mode = VOLUME_VIEW;
			continue;
		}
		if (strcmp("-bmp", argv[i]) == 0)
		{
			mode = BITMAP_VIEW;
			continue;
		}
		if (strcmp("-obj", argv[i]) == 0)
		{
			mode = EXPORT_OBJ;
			continue;
		}
		if (strcmp("-obj-", argv[i]) == 0)
		{
			mode = EXPORT_OBJ;
			export_and_view = 1;
			continue;
		}
		if (strcmp("-stl", argv[i]) == 0)
		{
			mode = EXPORT_STL;
			continue;
		}
		if (strcmp("-stl-", argv[i]) == 0)
		{
			mode = EXPORT_STL;
			export_and_view = 1;
			continue;
		}
		if (strcmp("-iso", argv[i]) == 0)
		{
			isovalue_set = true;
			isovalue = atof(argv[i + 1]);
			i++;
			continue;
		}
		if (strcmp("-sample_dist", argv[i]) == 0)
		{
			sample_dist = atof(argv[i + 1]);
			i++;
			continue;
		}
		if (strcmp("-o", argv[i]) == 0)
		{
			outfile = argv[i + 1];
			i++;
			continue;
		}

	}

	if (slice_image_num > 0)
	{
		double* iso = NULL;
		if (isovalue_set) iso = &isovalue;

		return loadSliceImages(folderName, base_name, slice_image_num, getSmoothing(), iso, targetReduction);

	}
	setTargetReduction(targetReduction);
	if ( mode == POLYGON_VIEW)
	{
		fprintf(stderr, "==> 3d viewer!!\n");
		DICOM_3DViewer(folderName, 0, sample_dist, isovalue, outfile);
		return 0;
	}
	if (mode == VOLUME_VIEW)
	{
		fprintf(stderr, "==> volume render viewer!!\n");
		DICOM_3DViewer(folderName, 100, sample_dist, isovalue, outfile);
		return 0;
	}
	if (mode == POLYGON_VOLUME_VIEW)
	{
		fprintf(stderr, "==> volume render & 3d viewer!!\n");
		DICOM_3DViewer(folderName, 101, sample_dist, isovalue, outfile);
		return 0;
	}

	if ( mode == BITMAP_VIEW)
	{
		try
		{
		fprintf(stderr, "==> bitmap!!\n");
		DICOM2BMP(folderName);
		fprintf(stderr, "==> convert bitmap!!\n");
		}
		catch (...)
		{

		}
		return 0;
	}

	if ( mode == EXPORT_OBJ)
	{
		fprintf(stderr, "==> obj!!\n");
		DICOM2OBJ(folderName, export_and_view, isovalue, outfile);
		fprintf(stderr, "==> convert obj!!\n");
		return 0;
	}

	if ( mode == EXPORT_STL )
	{
		fprintf(stderr, "==> stl!!\n");
		DICOM2STL(folderName, export_and_view, isovalue, outfile);
		fprintf(stderr, "==> convert stl!!\n");
		return 0;
	}


	if ( mode == EXPORT_WRL)
	{
		fprintf(stderr, "==> wrl!!\n");
		DICOM2VRML(folderName, export_and_view, isovalue, outfile);
		fprintf(stderr, "==> convert wrl!!\n");
		return 0;
	}
	if ( mode == EXPORT_X3D )
	{
		fprintf(stderr, "==> x3d!!\n");
		DICOM2X3D(folderName, 0, isovalue, outfile);
		fprintf(stderr, "==> convert x3d!!\n");
		return 0;
	}



	if ( argc >= 3 && argv[2][0] == '-' && strcmp(argv[2]+1, "x3d-") == 0 )
	{
		fprintf(stderr, "==> x3d!!\n");
		DICOM2X3D(folderName, 1, isovalue, outfile);
		fprintf(stderr, "==> convert x3d!!\n");
		return 0;
	}
	if ( argc >= 3 && argv[2][0] == '-' && strcmp(argv[2]+1, "x3d") == 0 )
	{
		fprintf(stderr, "==> x3d!!\n");
		DICOM2X3D(folderName, 0, isovalue, outfile);
		fprintf(stderr, "==> convert x3d!!\n");
		return 0;
	}

	DICOM_SliceViewer(folderName, 0);
	
	return 0;
}
