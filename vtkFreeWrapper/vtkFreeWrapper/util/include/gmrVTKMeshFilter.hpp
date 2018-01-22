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
 * Mesh Filter
 */
#ifndef _GMRVTKMESHFILTER_HPP
#define _GMRVTKMESHFILTER_HPP

#include "gmrVTK.hpp"
#include "gmrVTKDefs.hpp"

/** 
 * @brief Mesh Filter クラス
 *
 */

class gmr_EXPORT gmrVTKMeshFilter  : public gmrVTK
{

	vtkSmartPointer<vtkPolyDataMapper> PolyMapper_;
	vtkSmartPointer<vtkActor> PolyActor_;
	vtkPolyDataAlgorithm* poly_;

	double clean_tol;
	vtkSmartPointer<vtkScalarBarActor> curvatures_scalarBar_;
public:
	gmrVTKMeshFilter();
	virtual ~gmrVTKMeshFilter();

	void SetPoly(vtkPolyDataAlgorithm* poly)
	{
		poly_ = poly;
	}
	vtkPolyDataAlgorithm* GetPoly()
	{
		return poly_;
	}
	vtkSmartPointer<vtkPolyDataMapper> GetPolyMapper()
	{
		return PolyMapper_;
	}
	vtkSmartPointer<vtkActor> GetPolyActor()
	{
		return PolyActor_;
	}

	vtkSmartPointer<vtkScalarBarActor> Get_curvatures_scalarBar()
	{
		return curvatures_scalarBar_;
	}
	double min_curvature = 999999.0;
	double max_curvature = -999999.0;
	double av_curvature = 0.0;

	void SetCleanTol(double tol)
	{
		clean_tol = tol;
	}
	vtkSmartPointer<vtkCleanPolyData> CleanPoly(vtkAlgorithmOutput* poly, int& stat);
	vtkSmartPointer<vtkPolyDataConnectivityFilter> connectivityFilter(double r, int& stat);
	vtkSmartPointer<vtkCurvatures> curvaturesFilter(std::string& type, double scalarRange[2], int colorScheme, int& stat);
	vtkSmartPointer<vtkFillHolesFilter> FillHolesFilte(int holesize, int& stat);
	vtkSmartPointer<vtkDecimatePro> decimator(double target_reduction, double featureAngle, int& stat);
	vtkSmartPointer<vtkSmoothPolyDataFilter> SmoothFilter(int iter, double featureAngle, double factor, int& stat);
	vtkSmartPointer<vtkWindowedSincPolyDataFilter> WindowedSincPolyDataFilter(int iter, double featureAngle, double passBand, int& stat);

	vtkSmartPointer<vtkSurfaceReconstructionFilter> SurfaceReconstruction(vtkSmartPointer<vtkPoints>& points);
	vtkSmartPointer<vtkContourFilter> SurfaceReconstructionIsoValue(vtkSmartPointer<vtkPoints>& points, double isovalue);

	virtual vtkActor* GetActor();

};


inline int readPoints(char* xyz_fileName, vtkPoints* points, double sampling, std::mt19937& mt, std::uniform_real_distribution<double>& d_rand)
{
	FILE* fp = fopen(xyz_fileName, "r");
	if (fp == NULL)
	{
		char szFullPath[_MAX_PATH] = { '\0' };
		char *szFilePart;
		DWORD dwRet = GetFullPathNameA(xyz_fileName, _MAX_PATH, szFullPath, &szFilePart);
		if (fp == NULL)
		{
			printf("file open error,[%s]\n", szFullPath);
			if (strlen(szFullPath) >= _MAX_PATH || dwRet == 0)
			{
				printf("FullPathName failed.!\n");
			}
		}
	}
	if (fp == NULL) return -1;

	char buf[256];
	float x, y, z;
	int num = 0;
	while (fgets(buf, 256, fp) != NULL)
	{
		sscanf(buf, "%f %f %f", &x, &y, &z);
		if (d_rand(mt) < sampling)
		{
			points->InsertNextPoint(x, y, z);
			num++;
		}
	}
	fclose(fp);
	printf("read %d points\n", num);

	return 0;
}


#endif