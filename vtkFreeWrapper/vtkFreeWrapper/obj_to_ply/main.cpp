#include "gmrVTKRender.hpp"
#include "gmrVTKImport.hpp"
#include "gmrVTKExport.hpp"

#include <vtkCleanPolyData.h>
#include <vtkDecimatePro.h>

#include "gmrVTK.hpp"

#define NO_LINK_LIBS
#include "gmrVTKLIBs.hpp"
#pragma comment( lib, "../../../vtkFreeWrapper/util/lib/Release/64bit/vtkWrapperLib.lib" )
#pragma comment( lib, "opengl32.lib" )
#pragma comment( lib, "vfw32.lib")

#pragma comment( lib, "ws2_32.lib")
#pragma comment( lib, "Psapi.lib")
#pragma comment( lib, "Dbghelp.lib")


int main(int argc, char** argv)
{
	if (argc < 2)
	{
		printf("obj_to_ply obj_file -o output\n");
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

	gmrVTKImportOBJ* polygon1 = new gmrVTKImportOBJ(file1);
	polygon1->Get()->Update();
	if (polygon1->Get()->GetErrorCode())
	{
		printf("ImportOBJ error.\n");
		return -2;
	}

	vtkSmartPointer<vtkPolyDataMapper> Mapper = vtkSmartPointer<vtkPolyDataMapper>::New();

	Mapper->SetInputConnection(polygon1->Get()->GetOutputPort());

	vtkSmartPointer<vtkActor> Actor = vtkSmartPointer<vtkActor>::New();
	Actor->SetMapper(Mapper);

	gmrVTKRender* render = new gmrVTKRender;
	render->GetRenderer()->AddViewProp(Actor);

	gmrVTKExportPLY* expoter = new gmrVTKExportPLY();
	
	char* vtx_color_name = NULL;
	if (polygon1->Get()->GetOutput()->GetPointData()->GetScalars())
	{
		vtx_color_name = polygon1->Get()->GetOutput()->GetPointData()->GetScalars()->GetName();
		printf("Scalars!! [%s]\n", vtx_color_name);
	}
	else
	{
		printf("not Scalars!!\n");
	}

	expoter->SaveFile(polygon1->Get()->GetOutputPort(), output, vtx_color_name);
	delete expoter;
}