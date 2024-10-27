#include "gmrVTKRender.hpp"
#include "gmrVTKImport.hpp"
#include "gmrVTKExport.hpp"
#include "gmrVTKPoints.hpp"

#include "gmrVTKMeshFilter.hpp"

#include "gmrVTK.hpp"
#include <random>

#define NO_LINK_LIBS
#include "gmrVTKLIBs.hpp"
#pragma comment( lib, "../../../vtkFreeWrapper/util/lib/Release/64bit/vtkWrapperLib.lib" )

int main(int argc, char** argv)
{
	if (argc < 2)
	{
		printf("polygonFit xyz_file [-iso isovale -smp sampling[0, 1.0]] -o output\n");
		return -99;
	}
	std::mt19937 mt;
	std::uniform_real_distribution<double> d_rand(0.0, 1.0);

	vtkObject::SetGlobalWarningDisplay(0);
	
	double sampling = 1.0;
	double isovale = 0.0;
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
		if (strcmp(argv[i], "-iso") == 0)
		{
			isovale = atof(argv[i + 1]);
			i++;
			continue;
		}
		if (strcmp(argv[i], "-smp") == 0)
		{
			sampling = atof(argv[i + 1]);
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
	gmrVTKMeshFilter* meshFilter = new gmrVTKMeshFilter;

	vtkSmartPointer<vtkPoints> points = vtkSmartPointer<vtkPoints>::New();

	int stat = readPoints(file1, points, sampling, mt, d_rand);
	if (stat != 0)
	{
		printf("xyz read error.\n");
		return -1;
	}

	vtkSmartPointer<vtkContourFilter> contourFilter = meshFilter->SurfaceReconstructionIsoValue(points, isovale);

	meshFilter->GetPolyMapper()->SetInputConnection(contourFilter->GetOutputPort());
	meshFilter->GetPolyActor()->SetMapper(meshFilter->GetPolyMapper());
	//printf("aaaaaaaaaaaa\n");

	gmrVTKRender* render = new gmrVTKRender;
	render->GetRenderer()->AddViewProp(meshFilter->GetPolyActor());
	//printf("bbbbbbbbbb\n");


	gmrVTKExportOBJ* expoter = new gmrVTKExportOBJ();
	//printf("cccccccccc\n");
	{
		char* p = strstr(output, ".obj");
		if (p) *p = '\0';
		p = strstr(output, ".OBJ");
		if (p) *p = '\0';

		expoter->SaveFile(render, output);
		//printf("ddddddddddddd\n");
	}
	delete expoter;
}