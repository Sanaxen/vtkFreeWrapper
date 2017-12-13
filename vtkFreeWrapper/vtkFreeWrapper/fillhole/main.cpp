#include "gmrVTKRender.hpp"
#include "gmrVTKImport.hpp"
#include "gmrVTKExport.hpp"

#include "gmrVTKMeshFilter.hpp"

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

	gmrVTKMeshFilter* meshFilter = new gmrVTKMeshFilter;

	meshFilter->SetPoly(polygon1->Get());

	int stat;
	vtkSmartPointer<vtkFillHolesFilter> fillholes = meshFilter->FillHolesFilte(s, stat);
	if (stat != 0)
	{
		return stat;
	}
	vtkSmartPointer<vtkCleanPolyData> clean1 = meshFilter->CleanPoly(fillholes->GetOutputPort(), stat);
	if (stat != 0)
	{
		return stat;
	}

	vtkSmartPointer<vtkPolyDataMapper> Mapper = meshFilter->GetPolyMapper();

	Mapper->SetInputConnection(clean1->GetOutputPort());

	vtkSmartPointer<vtkActor> Actor = meshFilter->GetPolyActor();
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

	delete meshFilter;
	delete polygon1;
}