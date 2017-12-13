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

	double min_curvature = 999999.0;
	double max_curvature = -999999.0;
	double av_curvature = 0.0;

	vtkSmartPointer<vtkCleanPolyData> CleanPoly(vtkAlgorithmOutput* poly, int& stat);
	vtkSmartPointer<vtkPolyDataConnectivityFilter> connectivityFilter(double r, int& stat);
	vtkSmartPointer<vtkCurvatures> curvaturesFilter(std::string& type, double scalarRange[2], int colorScheme, int& stat);
	vtkSmartPointer<vtkFillHolesFilter> FillHolesFilte(int holesize, int& stat);
	vtkSmartPointer<vtkDecimatePro> decimator(double target_reduction, double featureAngle, int& stat);
	vtkSmartPointer<vtkSmoothPolyDataFilter> SmoothFilter(int iter, double featureAngle, double factor, int& stat);

	virtual vtkActor* GetActor();

};

#endif