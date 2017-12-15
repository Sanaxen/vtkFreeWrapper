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
		printf("simply obj_file [-d target_reduction(0..1) -a angle( angle < edge exists)] -o output\n");
		return -99;
	}
	vtkObject::SetGlobalWarningDisplay(0);
	
	double d = 0.1;
	double a = 5.0;	//deg
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
		else if (strcmp(argv[i], "-d") == 0)
		{
			d = atof(argv[i + 1]);
			i++;
			continue;
		}
		else if (strcmp(argv[i], "-a") == 0)
		{
			a = atof(argv[i + 1]);
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
	if (d <= 0)
	{
		return -4;
	}
	if (d >= 1)
	{
		return -5;
	}

	gmrVTKImportOBJ* polygon1 = new gmrVTKImportOBJ(file1);
	polygon1->Get()->Update();

	gmrVTKMeshFilter* meshFilter = new gmrVTKMeshFilter;

	meshFilter->SetPoly(polygon1->Get());

	int stat;
	vtkSmartPointer<vtkDecimatePro> decimator1 = meshFilter->decimator(d, a, stat);

	if (stat != 0)
	{
		printf("decimator error.\n");
		return stat;
	}
	vtkSmartPointer<vtkCleanPolyData> clean1 = meshFilter->CleanPoly(decimator1->GetOutputPort(), stat);
	if (stat != 0)
	{
		printf("clean error.\n");
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