#include "gmrVTKRender.hpp"
#include "gmrVTKImport.hpp"
#include "gmrVTKExport.hpp"

#include <vtkCleanPolyData.h>
#include <vtkDecimatePro.h>

#include "gmrVTK.hpp"

#define NO_LINK_LIBS
#include "gmrVTKLIBs.hpp"
#pragma comment( lib, "../../../vtkFreeWrapper/util/lib/Release/64bit/vtkWrapperLib.lib" )

int main(int argc, char** argv)
{
	if (argc < 2)
	{
		printf("ply_to_obj obj_file -o output\n");
		return -99;
	}
	vtkObject::SetGlobalWarningDisplay(0);

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

	gmrVTKImportPLY* polygon1 = new gmrVTKImportPLY(file1);
	polygon1->Get()->Update();
	if (polygon1->Get()->GetErrorCode())
	{
		printf("ImportPLY error.\n");
		return -2;
	}

	vtkSmartPointer<vtkPolyDataMapper> Mapper = vtkSmartPointer<vtkPolyDataMapper>::New();

	Mapper->SetInputConnection(polygon1->Get()->GetOutputPort());

	vtkSmartPointer<vtkActor> Actor = vtkSmartPointer<vtkActor>::New();
	Actor->SetMapper(Mapper);

	gmrVTKRender* render = new gmrVTKRender;
	render->GetRenderer()->AddViewProp(Actor);

	gmrVTKExportOBJ* expoter = new gmrVTKExportOBJ();
	int stat = expoter->exportVertexColorOBJ(output, polygon1->Get()->GetOutput(), Mapper, Actor);

	if (stat != 0)
	{
		char* p = strstr(output, ".obj");
		if (p) *p = '\0';
		p = strstr(output, ".OBJ");
		if (p) *p = '\0';
		expoter->SaveFile(render, output);
	}
	delete expoter;
}