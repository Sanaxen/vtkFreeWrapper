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
		printf("cleanMesh obj_file [ -tol tolerance ] -o output\n");
		return -99;
	}
	vtkObject::SetGlobalWarningDisplay(0);

	double tol = 0.00001;
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
		else if (strcmp(argv[i], "-tol") == 0)
		{
			tol = atof(argv[i + 1]);
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
	if (tol < 0) tol = 1.0E-10;

	gmrVTKImportOBJ* polygon1 = new gmrVTKImportOBJ(file1);
	polygon1->Get()->Update();

	gmrVTKMeshFilter* meshFilter = new gmrVTKMeshFilter;
	meshFilter->SetPoly(polygon1->Get());

	meshFilter->SetCleanTol(tol);
	printf("CleanTol:%.16f\n", tol);

	vtkSmartPointer<vtkOutlineFilter> boundingBox = vtkSmartPointer<vtkOutlineFilter>::New();
	boundingBox->SetInputConnection(polygon1->Get()->GetOutputPort());
	boundingBox->Update();

	double* bounds = boundingBox->GetOutput()->GetBounds();
	printf("input object MinMax=(%f,%f,%f)-(%f,%f,%f)=(%f,%f,%f)!!\n", 
		bounds[0], bounds[2], bounds[4], bounds[1], bounds[3], bounds[5],
		(bounds[1] - bounds[0]), (bounds[3] - bounds[1]), (bounds[5] - bounds[2]));
	
	double di = (bounds[1] - bounds[0])*(bounds[1] - bounds[0]) + (bounds[3] - bounds[1])*(bounds[3] - bounds[1]) + (bounds[5] - bounds[2])*(bounds[5] - bounds[2]);
	di = sqrt(di);

	if (tol > di*0.05)
	{
		printf("tol(%.8f) Diagonal length:%.6f error!!\n", tol, di);
		FILE* fp = fopen("cleanMesh_Error.txt", "w");
		fprintf(fp, "input object MinMax=(%f,%f,%f)-(%f,%f,%f)=(%f,%f,%f)!!\n",
				bounds[0], bounds[2], bounds[4], bounds[1], bounds[3], bounds[5],
				(bounds[1] - bounds[0]), (bounds[3] - bounds[1]), (bounds[5] - bounds[2]));
		fprintf(fp, "tol(%.8f) Diagonal length:%.6f error!!\n", tol, di);
		fclose(fp);
		exit(2);
	}

	int stat = 0;
	vtkSmartPointer<vtkCleanPolyData> clean1 = meshFilter->CleanPoly(polygon1->Get()->GetOutputPort(), stat);
	if (stat != 0)
	{
		printf("clean error.\n");
		exit(2);
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
	return 0;
}