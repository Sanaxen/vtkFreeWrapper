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
	printf("load end.\n");

	gmrVTKMeshFilter* meshFilter = new gmrVTKMeshFilter;

	meshFilter->SetPoly(polygon1->Get());

	int stat;
	vtkSmartPointer<vtkPolyDataConnectivityFilter> connectivityFilter = meshFilter->connectivityFilter(r, stat);
	if (stat != 0)
	{
		return stat;
	}
	vtkSmartPointer<vtkCleanPolyData> clean1 = meshFilter->CleanPoly(connectivityFilter->GetOutputPort(), stat);
	if (stat != 0)
	{
		return stat;
	}

	meshFilter->GetPolyMapper()->SetInputConnection(clean1->GetOutputPort());
	meshFilter->GetPolyActor()->SetMapper(meshFilter->GetPolyMapper());

	gmrVTKRender* render = new gmrVTKRender;
	render->GetRenderer()->AddViewProp(meshFilter->GetPolyActor());


	gmrVTKExportOBJ* expoter = new gmrVTKExportOBJ();
	stat = expoter->exportVertexColorOBJ(output, clean1->GetOutput(), meshFilter->GetPolyMapper(), meshFilter->GetPolyActor());

	if (stat != 0)
	{
		char* p = strstr(output, ".obj");
		if (p) *p = '\0';
		p = strstr(output, ".OBJ");
		if (p) *p = '\0';

		expoter->SaveFile(render, output);
	}
	delete expoter;

	delete meshFilter;
	delete polygon1;

}