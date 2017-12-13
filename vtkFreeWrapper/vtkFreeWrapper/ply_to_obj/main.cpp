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

int exportVertexColorOBJ(char* filename, vtkPolyData* poly, vtkSmartPointer<vtkPolyDataMapper>& Mapper, vtkSmartPointer<vtkActor>& Actor)
{
	FILE* fp = fopen(filename, "w");
	if (fp == NULL) return -1;

	double opacity = Actor->GetProperty()->GetOpacity();
	vtkUnsignedCharArray* color_array = Mapper->MapScalars(opacity);

	//vtkUnsignedCharArray* color_array = Mapper->GetColorMapColors();
	int comp = color_array->GetNumberOfComponents();

	printf("GetNumberOfComponents:%d Name:[%s]\n", comp, color_array->GetName());
	printf("GetNumberOfValues:%lld %I64d\n", color_array->GetNumberOfValues(), color_array->GetNumberOfValues() / comp);
	//for (int i = 0; i < color_array->GetNumberOfValues(); i++)
	//{
	//	printf("%d ", color_array->GetValue(i));
	//}


	vtkSmartPointer<vtkPoints> vertices = poly->GetPoints();
	vtkSmartPointer<vtkDataArray> verticesArray = vertices->GetData();

	long long numberOfVertices = vertices->GetNumberOfPoints();
	printf("numberOfVertices:%I64d\n", numberOfVertices);

	if (comp >= 3 && numberOfVertices == color_array->GetNumberOfValues() / comp)
	{
		for (int i = 0; i < numberOfVertices; i++)
		{
			double x = verticesArray->GetComponent(i, 0);
			double y = verticesArray->GetComponent(i, 1);
			double z = verticesArray->GetComponent(i, 2);
			fprintf(fp, "v %f %f %f", x, y, z);
			fprintf(fp, " %.3f %.3f %.3f\n",
				color_array->GetComponent(i, 0),
				color_array->GetComponent(i, 1),
				color_array->GetComponent(i, 2));
		}
	}
	else
	{
		for (int i = 0; i < numberOfVertices; i++)
		{
			double x = verticesArray->GetComponent(i, 0);
			double y = verticesArray->GetComponent(i, 1);
			double z = verticesArray->GetComponent(i, 2);
			fprintf(fp, "v %f %f %f\n", x, y, z);
		}
	}
	int  numberOfFaces = poly->GetNumberOfCells();

	for (int i = 0; i < numberOfFaces; i++)
	{
		vtkSmartPointer<vtkIdList> face = vtkSmartPointer<vtkIdList>::New();
		poly->GetCellPoints(i, face);

		if (face->GetId(0) == face->GetId(1) || face->GetId(0) == face->GetId(2) || face->GetId(2) == face->GetId(1))
		{
			continue;
		}
		int f = face->GetNumberOfIds();
		if (f < 3)
		{
			printf("skipp Faces with fewer than 3 vertices.\n");
			continue;
		}
		fprintf(fp, "f");
		for (int j = 0; j < f; j++)
		{
			fprintf(fp, " %I64d", face->GetId(j) + 1);
		}
		fprintf(fp, "\n");
	}
	fclose(fp);

	return 0;
}

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

	int stat = exportVertexColorOBJ(output, polygon1->Get()->GetOutput(), Mapper, Actor);

	if (stat != 0)
	{
		gmrVTKExportOBJ* expoter = new gmrVTKExportOBJ();
		char* p = strstr(output, ".obj");
		if (p) *p = '\0';
		p = strstr(output, ".OBJ");
		if (p) *p = '\0';


		expoter->SaveFile(render, output);
		delete expoter;
	}
}