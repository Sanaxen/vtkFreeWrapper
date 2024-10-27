#include "gmrVTKRender.hpp"
#include "gmrVTKImport.hpp"
#include "gmrVTKExport.hpp"

#include <vtkBooleanOperationPolyDataFilter.h>
#include <vtkCleanPolyData.h>
#include <vtkDecimatePro.h>
#include <vtkTransform.h>
#include <vtkTransformFilter.h>

#include "gmrVTK.hpp"

#define NO_LINK_LIBS
#include "gmrVTKLIBs.hpp"
#pragma comment( lib, "../../../vtkFreeWrapper/util/lib/Release/64bit/vtkWrapperLib.lib" )

//vtkMath.cxx  #define VTK_MAX_ROTATIONS 20 -> 50

int main(int argc, char** argv)
{
	vtkObject::SetGlobalWarningDisplay(0);
	if (argc < 2)
	{
		printf("SolidBooleanSolver -[i,d,u] obj_file1 obj_file2 -o output\n");
		return -99;
	}

	int op = -1;
	char* file1 = NULL;
	char* file2 = NULL;
	char* output = NULL;

	for (int i = 1; i < argc; i++)
	{
		if (strcmp(argv[i], "-i") == 0) op = 1;
		else if (strcmp(argv[i], "-u") == 0) op = 2;
		else if (strcmp(argv[i], "-d") == 0) op = 3;
		else if (strcmp(argv[i], "-o") == 0)
		{
			output = argv[i + 1];
			i++;
			continue;
		}
		else if (file1 == NULL) file1 = argv[i];
		else if (file2 == NULL) file2 = argv[i];
	}
	if (file1 == NULL || file2 == NULL)
	{
		return -1;
	}
	if (op == -1)
	{
		return -2;
	}
	if (output == NULL)
	{
		return -3;
	}

	gmrVTKImportOBJ* polygon1 = new gmrVTKImportOBJ(file1);
	gmrVTKImportOBJ* polygon2 = new gmrVTKImportOBJ(file2);

	polygon1->Get()->Update();
	polygon2->Get()->Update();

	vtkSmartPointer<vtkCleanPolyData> clean1 = vtkSmartPointer<vtkCleanPolyData>::New();
	clean1->SetInputConnection(polygon1->Get()->GetOutputPort());
	clean1->SetTolerance(1.0E-8);
	clean1->PointMergingOn();
	clean1->SetOutputPointsPrecision(vtkAlgorithm::DOUBLE_PRECISION);
	clean1->Update();
	if (clean1->GetErrorCode())
	{
		printf("clean error.\n");
		return -2;
	}
	vtkSmartPointer<vtkCleanPolyData> clean2 = vtkSmartPointer<vtkCleanPolyData>::New();
	clean2->SetInputConnection(polygon2->Get()->GetOutputPort());
	clean2->SetTolerance(1.0E-8);
	clean2->PointMergingOn();
	clean2->SetOutputPointsPrecision(vtkAlgorithm::DOUBLE_PRECISION);
	clean2->Update();
	if (clean2->GetErrorCode())
	{
		printf("clean error.\n");
		return -2;
	}

	vtkSmartPointer<vtkBooleanOperationPolyDataFilter> booleanOperation =
		vtkSmartPointer<vtkBooleanOperationPolyDataFilter>::New();
	
	booleanOperation->DebugOn();
	booleanOperation->SetTolerance(1.0e-10);
	//booleanOperation->ReorientDifferenceCellsOn();
	if (booleanOperation->GetErrorCode())
	{
		printf("booleanOperation error.\n");
		return -1;
	}

	if (op == 1) booleanOperation->SetOperationToIntersection();
	if (op == 2) booleanOperation->SetOperationToUnion();
	if (op == 3) booleanOperation->SetOperationToDifference();

	try
	{
		booleanOperation->SetInputData(0, clean1->GetOutput());
		booleanOperation->SetInputData(1, clean2->GetOutput());
		//booleanOperation->SetOutputPointsPrecision(vtkAlgorithm::DOUBLE_PRECISION);
		booleanOperation->Update();
	}
	catch (...)
	{
		printf("booleanOperation error.\n");
		return -2;
	}
	if (booleanOperation->GetErrorCode())
	{
		printf("booleanOperation error.\n");
		return -2;
	}

	gmrVTKRender* render = new gmrVTKRender;
#if 10
	try
	{
		vtkSmartPointer<vtkPolyDataMapper> booleanOperationMapper =
			vtkSmartPointer<vtkPolyDataMapper>::New();

		booleanOperationMapper->SetInputConnection(booleanOperation->GetOutputPort());
		booleanOperationMapper->ScalarVisibilityOff();

		vtkSmartPointer<vtkActor> booleanOperationActor =
			vtkSmartPointer<vtkActor>::New();
		booleanOperationActor->SetMapper(booleanOperationMapper);


		//render->GetRenderer()->AddViewProp(booleanOperationActor);
		render->AddActor(booleanOperationActor);
		
	}
	catch (...)
	{
		printf("booleanOperation error.\n");
		return -10;
	}
#endif
	if (booleanOperation->GetOutput()->GetPolys()->GetNumberOfCells() == 0)
	{
		return -10;
	}
	render->DefaultRun("");


	gmrVTKExportOBJ* expoter = new gmrVTKExportOBJ();
	char* p = strstr(output, ".obj");
	if (p) *p = '\0';
	p = strstr(output, ".OBJ");
	if (p) *p = '\0';

	expoter->SaveFile(render, output);
	delete expoter;
}