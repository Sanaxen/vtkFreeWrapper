#include "gmrVTKRender.hpp"
#include "gmrVTKImport.hpp"
#include "gmrVTKExport.hpp"

#include <vtkCleanPolyData.h>
#include <vtkDecimatePro.h>
#include <vtkSmoothPolyDataFilter.h>

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
		printf("smooth obj_file [ -a angle( angle < edge exists) -f factor(> 0 & < 1) -i Iterations ] -o output\n");
		return -99;
	}
	vtkObject::SetGlobalWarningDisplay(0);
	
	int iter = 1;
	double f = 0.05;
	double a = 25.0;	//deg
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
		else if (strcmp(argv[i], "-a") == 0)
		{
			a = atof(argv[i + 1]);
			i++;
			continue;
		}
		else if (strcmp(argv[i], "-f") == 0)
		{
			f = atof(argv[i + 1]);
			i++;
			continue;
		}
		else if (strcmp(argv[i], "-i") == 0)
		{
			iter = atoi(argv[i + 1]);
			i++;
			continue;
		}
		else if (file1 == NULL) file1 = argv[i];
	}
	if (file1 == NULL)
	{
		return -1;
	}
	if (iter <= 0)
	{
		return -2;
	}
	if (output == NULL)
	{
		return -3;
	}

	gmrVTKImportOBJ* polygon1 = new gmrVTKImportOBJ(file1);
	polygon1->Get()->Update();

	vtkSmartPointer<vtkSmoothPolyDataFilter> smooth =
		vtkSmoothPolyDataFilter::New();
	smooth->SetInputData(polygon1->Get()->GetOutput());
	smooth->SetNumberOfIterations(iter);
	smooth->SetFeatureAngle(a);
	smooth->SetRelaxationFactor(f);
	smooth->SetOutputPointsPrecision(vtkAlgorithm::DOUBLE_PRECISION);
	smooth->Update();
	if (smooth->GetErrorCode())
	{
		printf("smooth error.\n");
		return -2;
	}

	vtkSmartPointer<vtkCleanPolyData> clean1 = vtkSmartPointer<vtkCleanPolyData>::New();
	clean1->SetInputConnection(smooth->GetOutputPort());
	clean1->SetTolerance(1.0E-8);
	clean1->PointMergingOn();
	clean1->SetOutputPointsPrecision(vtkAlgorithm::DOUBLE_PRECISION);
	clean1->Update();
	if (clean1->GetErrorCode())
	{
		printf("clean error.\n");
		return -2;
	}


	vtkSmartPointer<vtkPolyDataMapper> Mapper = vtkSmartPointer<vtkPolyDataMapper>::New();

	Mapper->SetInputConnection(clean1->GetOutputPort());

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