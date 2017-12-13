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
#include "gmrVTKMeshFilter.hpp"

gmrVTKMeshFilter::gmrVTKMeshFilter()
{
	poly_ = NULL;
	PolyMapper_ = vtkSmartPointer<vtkPolyDataMapper>::New();
	PolyActor_ = vtkSmartPointer<vtkActor>::New();
}

gmrVTKMeshFilter::~gmrVTKMeshFilter()
{
}

vtkActor* gmrVTKMeshFilter::GetActor()
{
	if (actor_ == NULL)
	{
		CreateMapper();
		actor_ = vtkActor::New();

		actor_->SetMapper(mapper_);
	}
	return actor_;
}


vtkSmartPointer<vtkCleanPolyData> gmrVTKMeshFilter::CleanPoly(vtkAlgorithmOutput* poly, int& stat)
{
	stat = 0;
	vtkSmartPointer<vtkCleanPolyData> clean1 = vtkSmartPointer<vtkCleanPolyData>::New();
	clean1->SetInputConnection(poly);
	clean1->SetTolerance(1.0E-8);
	clean1->PointMergingOn();
	clean1->SetOutputPointsPrecision(vtkAlgorithm::DOUBLE_PRECISION);
	clean1->Update();
	if (clean1->GetErrorCode())
	{
		printf("clean error.\n");
		stat =  -2;
	}
	return clean1;
}

vtkSmartPointer<vtkPolyDataConnectivityFilter> gmrVTKMeshFilter::connectivityFilter(double r, int& stat)
{
	if (poly_ == NULL)
	{
		stat = -99;
		return NULL;
	}

	stat = 0;
	vtkSmartPointer<vtkPolyDataConnectivityFilter> connectivityFilter = vtkSmartPointer<vtkPolyDataConnectivityFilter>::New();
	connectivityFilter->SetInputData(poly_->GetOutput());
	connectivityFilter->SetExtractionModeToAllRegions();
	connectivityFilter->SetOutputPointsPrecision(vtkAlgorithm::DOUBLE_PRECISION);
	connectivityFilter->Update();
	if (connectivityFilter->GetErrorCode())
	{
		printf("connectivityFilter error.\n");
		stat = -2;
		return NULL;
	}

	vtkIdTypeArray* regionSizes = connectivityFilter->GetRegionSizes();

	long maxSize = 0;
	for (int regions = 0; regions < connectivityFilter->GetNumberOfExtractedRegions(); regions++)
	{
		if (regionSizes->GetValue(regions) > maxSize)
		{
			maxSize = regionSizes->GetValue(regions);
		}
	}


	connectivityFilter->SetExtractionModeToSpecifiedRegions();
	for (int regions = 0; regions < connectivityFilter->GetNumberOfExtractedRegions(); regions++)
	{
		if (regionSizes->GetValue(regions) > maxSize * r)
		{
			connectivityFilter->AddSpecifiedRegion(regions);
		}
	}

	connectivityFilter->Update();
	return connectivityFilter;
}

vtkSmartPointer<vtkCurvatures> gmrVTKMeshFilter::curvaturesFilter(std::string& type, double scalarRange[2], int colorScheme, int& stat)
{
	stat = 0;
	vtkSmartPointer<vtkCleanPolyData> clean1 = CleanPoly(poly_->GetOutputPort(), stat);
	if (stat != 0)
	{
		return NULL;
	}

	vtkSmartPointer<vtkCurvatures> curvaturesFilter = vtkSmartPointer<vtkCurvatures>::New();
	curvaturesFilter->SetInputConnection(clean1->GetOutputPort());
	if (type == "min") curvaturesFilter->SetCurvatureTypeToMinimum();
	if (type == "max") curvaturesFilter->SetCurvatureTypeToMaximum();
	if (type == "gauss") curvaturesFilter->SetCurvatureTypeToGaussian();
	if (type == "mean") curvaturesFilter->SetCurvatureTypeToMean();
	curvaturesFilter->Update();
	if (curvaturesFilter->GetErrorCode())
	{
		printf("curvatures error.\n");
		stat = -2;
		return NULL;
	}

	if (scalarRange[0] == scalarRange[1] )
	{
		curvaturesFilter->GetOutput()->GetScalarRange(scalarRange);
	}

	vtkSmartPointer<vtkColorSeries> colorSeries = vtkSmartPointer<vtkColorSeries>::New();
	colorSeries->SetColorScheme(colorScheme);
	std::cout << "Using color scheme #: "
		<< colorSeries->GetColorScheme() << " is "
		<< colorSeries->GetColorSchemeName() << std::endl;

	vtkSmartPointer<vtkColorTransferFunction> lut =	vtkSmartPointer<vtkColorTransferFunction>::New();
	lut->SetColorSpaceToHSV();

	int numColors = colorSeries->GetNumberOfColors();
	for (int i = 0; i < numColors; i++)
	{
		vtkColor3ub color = colorSeries->GetColor(i);
		double dColor[3];
		dColor[0] = static_cast<double> (color[0]) / 255.0;
		dColor[1] = static_cast<double> (color[1]) / 255.0;
		dColor[2] = static_cast<double> (color[2]) / 255.0;
		double t = scalarRange[0] + (scalarRange[1] - scalarRange[0])
			/ (numColors - 1) * i;
		lut->AddRGBPoint(t, dColor[0], dColor[1], dColor[2]);
	}


	vtkSmartPointer<vtkPolyDataMapper> Mapper = GetPolyMapper();

	Mapper->SetInputConnection(curvaturesFilter->GetOutputPort());
	Mapper->SetLookupTable(lut);
	Mapper->SetScalarRange(scalarRange);

	Mapper->ScalarVisibilityOn();
	Mapper->SetScalarModeToUsePointData();
	Mapper->SetColorModeToMapScalars();
	Mapper->Update();

	vtkSmartPointer<vtkActor> Actor = GetPolyActor();
	Actor->SetMapper(Mapper);

	vtkSmartPointer<vtkScalarBarActor> scalarBar =
		vtkSmartPointer<vtkScalarBarActor>::New();
	scalarBar->SetLookupTable(Mapper->GetLookupTable());
	scalarBar->SetTitle(
		curvaturesFilter->GetOutput()->GetPointData()->GetScalars()->GetName());
	scalarBar->SetNumberOfLabels(5);

	curvaturesFilter->Update();
	printf("%d\n", curvaturesFilter->GetOutput()->GetPointData()->GetScalars()->GetNumberOfComponents());
	printf("%d\n", curvaturesFilter->GetOutput()->GetPointData()->GetScalars()->GetNumberOfTuples());

	for (int i = 0; i < curvaturesFilter->GetOutput()->GetPointData()->GetScalars()->GetNumberOfTuples(); i++)
	{
		double c = curvaturesFilter->GetOutput()->GetPointData()->GetScalars()->GetComponent(i, 0);

		if (c < min_curvature) min_curvature = c;
		if (c > max_curvature) max_curvature = c;
		av_curvature += c;
	}
	return curvaturesFilter;
}

vtkSmartPointer<vtkFillHolesFilter> gmrVTKMeshFilter::FillHolesFilte(int holesize, int& stat)
{
	stat = 0;
	vtkSmartPointer<vtkPolyData> input =
		vtkSmartPointer<vtkPolyData>::New();
	input->ShallowCopy(poly_->GetOutput());


	vtkSmartPointer<vtkFillHolesFilter> fillholes =	vtkFillHolesFilter::New();
	fillholes->SetInputData(poly_->GetOutput());
	fillholes->SetHoleSize(holesize);
	fillholes->Update();
	if (fillholes->GetErrorCode())
	{
		printf("Fill Holes error.\n");
		stat = -2;
		return NULL;
	}

	// Make the triangle windong order consistent
	vtkSmartPointer<vtkPolyDataNormals> normals =
		vtkSmartPointer<vtkPolyDataNormals>::New();
	normals->SetInputConnection(fillholes->GetOutputPort());
	normals->ConsistencyOn();
	normals->SplittingOff();
	normals->Update();

	// Restore the original normals
	normals->GetOutput()->GetPointData()->SetNormals(input->GetPointData()->GetNormals());

	return fillholes;
}

vtkSmartPointer<vtkDecimatePro> gmrVTKMeshFilter::decimator(double target_reduction, double featureAngle, int& stat)
{
	stat = 0;
	vtkSmartPointer<vtkDecimatePro> decimator1 =vtkDecimatePro::New();
	decimator1->SetInputData(poly_->GetOutput());
	decimator1->SetTargetReduction(target_reduction);
	decimator1->SetPreserveTopology(1);
	decimator1->SetFeatureAngle(featureAngle);
	decimator1->SetOutputPointsPrecision(vtkAlgorithm::DOUBLE_PRECISION);
	decimator1->Update();
	if (decimator1->GetErrorCode())
	{
		printf("decimator error.\n");
		stat =  -2;
		return NULL;
	}

	return decimator1;
}

vtkSmartPointer<vtkSmoothPolyDataFilter> gmrVTKMeshFilter::SmoothFilter(int iter, double featureAngle, double factor, int& stat)
{
	stat = 0;
	vtkSmartPointer<vtkSmoothPolyDataFilter> smooth = vtkSmoothPolyDataFilter::New();
	smooth->SetInputData(poly_->GetOutput());
	smooth->SetNumberOfIterations(iter);
	smooth->SetFeatureAngle(featureAngle);
	smooth->SetRelaxationFactor(factor);
	smooth->SetOutputPointsPrecision(vtkAlgorithm::DOUBLE_PRECISION);
	smooth->Update();
	if (smooth->GetErrorCode())
	{
		printf("smooth error.\n");
		stat = -2;
		return NULL;
	}

	return smooth;
}