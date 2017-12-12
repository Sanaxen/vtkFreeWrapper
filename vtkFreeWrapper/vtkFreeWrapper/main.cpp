#include "gmrVTKRender.hpp"
#include "gmrVTKImport.hpp"
#include "gmrVTKExport.hpp"

#include <vtkCleanPolyData.h>
#include <vtkDecimatePro.h>
#include <vtkPolyDataConnectivityFilter.h>

#include "gmrVTK.hpp"

#define NO_LINK_LIBS
#include "gmrVTKLIBs.hpp"
#pragma comment( lib, "../../../vtkFreeWrapper/util/lib/Release/64bit/vtkWrapperLib.lib" )
#pragma comment( lib, "opengl32.lib" )
#pragma comment( lib, "vfw32.lib")

int main(int argc, char** argv)
{
	if (argc < 2)
	{
		printf("clean_small_objects obj_file [-r ratio (0..1)] -o output\n");
		return -99;
	}
	vtkObject::SetGlobalWarningDisplay(0);
	
	double r = 0.005;
	char* file1 = NULL;
	char* output = NULL;

	for (int i = 1; i < argc; i++)
	{
		if (strcmp(argv[i], "-o") == 0)
		{
			output = argv[i + 1];
			i++;
			continue;
		}
		else if (strcmp(argv[i], "-r") == 0)
		{
			r = atof(argv[i + 1]);
			i++;
			continue;
		}
		else if (file1 == NULL) file1 = argv[i];
	}
	if (file1 == NULL)
	{
		return -1;
	}
	if (output == NULL)
	{
		return -3;
	}
	if (r <= 0)
	{
		return -4;
	}
	if (r >= 1)
	{
		return -5;
	}

	gmrVTKImportOBJ* polygon1 = new gmrVTKImportOBJ(file1);
	polygon1->Get()->Update();

	vtkSmartPointer<vtkPolyDataConnectivityFilter> connectivityFilter =
		vtkPolyDataConnectivityFilter::New();
	connectivityFilter->SetInputData(polygon1->Get()->GetOutput());
	connectivityFilter->SetExtractionModeToAllRegions();
	connectivityFilter->SetOutputPointsPrecision(vtkAlgorithm::DOUBLE_PRECISION);
	connectivityFilter->Update();
	if (connectivityFilter->GetErrorCode())
	{
		printf("connectivityFilter error.\n");
		return -2;
	}

	vtkSmartPointer<vtkCleanPolyData> clean1 = vtkSmartPointer<vtkCleanPolyData>::New();
	clean1->SetInputConnection(connectivityFilter->GetOutputPort());
	clean1->SetTolerance(1.0E-8);
	clean1->PointMergingOn();
	clean1->SetOutputPointsPrecision(vtkAlgorithm::DOUBLE_PRECISION);
	clean1->Update();
	if (clean1->GetErrorCode())
	{
		printf("clean error.\n");
		return -2;
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

	vtkSmartPointer<vtkPolyDataMapper> Mapper = vtkSmartPointer<vtkPolyDataMapper>::New();

	Mapper->SetInputConnection(connectivityFilter->GetOutputPort());

	vtkSmartPointer<vtkActor> Actor = vtkSmartPointer<vtkActor>::New();
	Actor->SetMapper(Mapper);

	gmrVTKRender* render = new gmrVTKRender;
	render->GetRenderer()->AddViewProp(Actor);


	gmrVTKExportOBJ* expoter = new gmrVTKExportOBJ();
	char* p = strstr(output, ".obj");
	if (p) *p = '\0';
	p = strstr(output, ".OBJ");
	if (p) *p = '\0';

	expoter->SaveFile(render, output);
	delete expoter;
}