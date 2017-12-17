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

//adjust point positions using a windowed sinc function interpolation kernel
int main(int argc, char** argv)
{
	if (argc < 2)
	{
		printf("effect_relax.exe obj_file [ -a angle( angle < edge exists)  -i Iterations -passband value] -o output\n");
		return -99;
	}
	vtkObject::SetGlobalWarningDisplay(0);

	double passBand = 0.001;
	int iter = 10;
	double a = 120.0;
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
		else if (strcmp(argv[i], "-i") == 0)
		{
			iter = atoi(argv[i + 1]);
			i++;
			continue;
		}
		else if (strcmp(argv[i], "-passband") == 0)
		{
			passBand = atof(argv[i + 1]);
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

	gmrVTKMeshFilter* meshFilter = new gmrVTKMeshFilter;
	meshFilter->SetPoly(polygon1->Get());

	int stat = 0;
	//vtkSmartPointer<vtkCleanPolyData> clean1 = meshFilter->CleanPoly(polygon1->Get()->GetOutputPort(), stat);
	//if (stat != 0)
	//{
	//	printf("clean error.\n");
	//	return stat;
	//}

	//meshFilter->SetPoly(clean1);
	vtkSmartPointer<vtkWindowedSincPolyDataFilter> smooth = meshFilter->WindowedSincPolyDataFilter(iter, a, passBand, stat);
	if (stat != 0)
	{
		printf("clean error.\n");
		return stat;
	}
	//printf("============\n");


	meshFilter->GetPolyMapper()->SetInputConnection(smooth->GetOutputPort());
	meshFilter->GetPolyActor()->SetMapper(meshFilter->GetPolyMapper());

	gmrVTKRender* render = new gmrVTKRender;
	render->GetRenderer()->AddViewProp(meshFilter->GetPolyActor());


	gmrVTKExportOBJ* expoter = new gmrVTKExportOBJ();
	stat = expoter->exportVertexColorOBJ(output, smooth->GetOutput(), meshFilter->GetPolyMapper(), meshFilter->GetPolyActor());

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