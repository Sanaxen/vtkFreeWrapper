#include "gmrVTKRender.hpp"
#include "gmrVTKImport.hpp"
#include "gmrVTKExport.hpp"

#include <vtkCleanPolyData.h>
#include <vtkDecimatePro.h>
#include <vtkFillHolesFilter.h>

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
		printf("fillhole obj_file [-s hole_size] -o output\n");
		return -99;
	}
	vtkObject::SetGlobalWarningDisplay(0);
	
	double s = 0.1;
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
		else if (strcmp(argv[i], "-s") == 0)
		{
			s = atof(argv[i + 1]);
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
	if (s <= 0)
	{
		return -4;
	}

	gmrVTKImportOBJ* polygon1 = new gmrVTKImportOBJ(file1);
	polygon1->Get()->Update();

	vtkSmartPointer<vtkPolyData> input =
		vtkSmartPointer<vtkPolyData>::New();
	input->ShallowCopy(polygon1->Get()->GetOutput());


	vtkSmartPointer<vtkFillHolesFilter> fillholes =
		vtkFillHolesFilter::New();
	fillholes->SetInputData(polygon1->Get()->GetOutput());
	fillholes->SetHoleSize(s);
	fillholes->Update();
	if (fillholes->GetErrorCode())
	{
		printf("Fill Holes error.\n");
		return -2;
	}

	// Make the triangle windong order consistent
	vtkSmartPointer<vtkPolyDataNormals> normals =
		vtkSmartPointer<vtkPolyDataNormals>::New();
	normals->SetInputConnection(fillholes->GetOutputPort());
	normals->ConsistencyOn();
	normals->SplittingOff();
	normals->Update();

	// Restore the original normals
	normals->GetOutput()->GetPointData()->
		SetNormals(input->GetPointData()->GetNormals());

	vtkSmartPointer<vtkCleanPolyData> clean1 = vtkSmartPointer<vtkCleanPolyData>::New();
	clean1->SetInputConnection(normals->GetOutputPort());
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