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

	FILE* fp = fopen(file1, "r");
	if (fp == NULL)
	{
		return -3;
	}

	gmrVTKExportPLY* expoter = new gmrVTKExportPLY();

	vtkSmartPointer<vtkUnsignedCharArray> colors =
		vtkSmartPointer<vtkUnsignedCharArray>::New();
	colors->SetNumberOfComponents(3);
	colors->SetNumberOfTuples(polygon1->Get()->GetOutput()->GetPoints()->GetNumberOfPoints());
	colors->SetName("Colors");

	int ii = 0;
	bool vertex_color = true;
	char buf[256];
	while (fgets(buf, 256, fp) != NULL)
	{
		if (buf[0] != 'v') continue;
		double x, y, z, r, g, b;
		int n = sscanf(buf, "v %lf %lf %lf %lf %lf %lf", &x, &y, &z, &r, &g, &b);
		if (n != 6)
		{
			vertex_color = false;
			break;
		}
		colors->SetComponent(ii, 0, r);
		colors->SetComponent(ii, 1, g);
		colors->SetComponent(ii, 2, b);
		ii++;
	}
	fclose(fp);
	printf("vertex num:%d == %d\n", polygon1->Get()->GetOutput()->GetPoints()->GetNumberOfPoints(), ii);

	if (vertex_color)
	{
		polygon1->Get()->GetOutput()->GetPointData()->SetScalars(colors);
		expoter->SaveFile(polygon1->Get()->GetOutputPort(), "Colors", output);
	}
	else
	{
		expoter->SaveFile(polygon1->Get()->GetOutputPort(), output);
	}
	delete expoter;
}