#include "gmrVTKRender.hpp"
#include "gmrVTKImport.hpp"
#include "gmrVTKExport.hpp"
#include "gmrVTKCapture.hpp"
#include "gmrVTKText.hpp"


#include "gmrVTKMeshFilter.hpp"

#include "gmrVTK.hpp"

#define NO_LINK_LIBS
#include "gmrVTKLIBs.hpp"
#pragma comment( lib, "../../../vtkFreeWrapper/util/lib/Release/64bit/vtkWrapperLib.lib" )
#pragma comment( lib, "opengl32.lib" )
#pragma comment( lib, "vfw32.lib")

int exportVertexColorOBJ(char* filename, gmrVTKMeshFilter* meshFilter, vtkPolyDataAlgorithm* poly)
{
	FILE* fp = fopen(filename, "w");
	if (fp == NULL) return -1;

	double opacity = meshFilter->GetPolyActor()->GetProperty()->GetOpacity();
	vtkUnsignedCharArray* color_array = meshFilter->GetPolyMapper()->MapScalars(opacity);

	//vtkUnsignedCharArray* color_array = Mapper->GetColorMapColors();
	int comp = color_array->GetNumberOfComponents();

	printf("GetNumberOfComponents:%d Name:[%s]\n", comp, color_array->GetName());
	printf("GetNumberOfValues:%lld %I64d\n", color_array->GetNumberOfValues(), color_array->GetNumberOfValues() / comp);
	//for (int i = 0; i < color_array->GetNumberOfValues(); i++)
	//{
	//	printf("%d ", color_array->GetValue(i));
	//}


	vtkSmartPointer<vtkPoints> vertices = poly->GetOutput()->GetPoints();
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
	int  numberOfFaces = poly->GetOutput()->GetNumberOfCells();

	for (int i = 0; i < numberOfFaces; i++)
	{
		vtkSmartPointer<vtkIdList> face = vtkSmartPointer<vtkIdList>::New();
		poly->GetOutput()->GetCellPoints(i, face);

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
		printf("Curvatures obj_file [-t mean|gauss|max|min -range min max -cs color_scheme -no_render] -o output\n");
		return -99;
	}
	vtkObject::SetGlobalWarningDisplay(0);
	
	std::string type = "";
	int scalarRange_set = 0;
	int scheme = 15;
	int no_render = 0;
	int render_only = 0;

	double scalarRange[2];
	char* file1 = NULL;
	char* output = NULL;

	for (int i = 1; i < argc; i++)
	{
		if (strcmp(argv[i], "-t") == 0)
		{
			if (strcmp("mean", argv[i + 1]) == 0) type = argv[i + 1];
			if (strcmp("gauss", argv[i + 1]) == 0) type = argv[i + 1];
			if (strcmp("max", argv[i + 1]) == 0) type = argv[i + 1];
			if (strcmp("min", argv[i + 1]) == 0) type = argv[i + 1];
			i++;
			continue;
		}
		if (strcmp(argv[i], "-o") == 0)
		{
			output = argv[i + 1];
			i++;
			continue;
		}
		else if (strcmp(argv[i], "-no_render") == 0)
		{
			no_render = 1;
			render_only = 0;
		}
		else if (strcmp(argv[i], "-render_only") == 0)
		{
			no_render = 0;
			render_only = 1;
		}
		else if (strcmp(argv[i], "-cs") == 0)
		{
			scheme = atoi(argv[i + 1]);
			if (scheme < 0 || scheme > 60)
			{
				scheme = 15;
			}
			i++;
			continue;
		}
		else if (strcmp(argv[i], "-range") == 0)
		{
			scalarRange_set++;
			scalarRange[0] = atof(argv[i + 1]);
			i++;
			scalarRange[1] = atof(argv[i + 1]);
			i++;
			if (scalarRange[0] == scalarRange[1])
			{
				scalarRange_set = 0;
				printf("scalarRange auto!!\n");
			}
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

	int stat = 0;
	meshFilter->SetPoly(polygon1->Get());
	vtkSmartPointer<vtkCurvatures> curvaturesFilter = meshFilter->curvaturesFilter(type, scalarRange, scheme, stat);
	if (stat != 0)
	{
		return stat;
	}

	gmrVTKRender* render = new gmrVTKRender();

	render->AddActor(meshFilter->GetPolyActor());
	render->GetRenderer()->AddViewProp(meshFilter->Get_curvatures_scalarBar());

	gmrVTKText* text2d = new gmrVTKText;

	char testbuf[128];
	sprintf(testbuf, "max:%.3f min:%.3f ave:%.3f", meshFilter->max_curvature, meshFilter->min_curvature, meshFilter->av_curvature / curvaturesFilter->GetOutput()->GetPointData()->GetScalars()->GetNumberOfTuples());

	text2d->SetText(testbuf);
	text2d->SetColor(0.0, 0.0, 0.0);
	text2d->SetSize(15);
	text2d->SetPosition(20, 20);
	render->AddActor(text2d->GetActor());

	printf("render_only:%d\n", render_only);
	if (!render_only)
	{
		int stat = exportVertexColorOBJ(output, meshFilter, curvaturesFilter);

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

		//PLY export
		if (1)
		{
			gmrVTKExportPLY* plyexpoter = new gmrVTKExportPLY();
			char* p = strstr(output, ".obj");
			if (p) *p = '\0';
			p = strstr(output, ".OBJ");
			if (p) *p = '\0';

			std::string debug_file = output;
			debug_file += "_debug";

			char array_name[32];
			strcpy(array_name, curvaturesFilter->GetOutput()->GetPointData()->GetScalars()->GetName());

			int comp = curvaturesFilter->GetOutput()->GetPointData()->GetScalars()->GetNumberOfComponents();

			printf("GetNumberOfComponents:%d Name:[%s]\n", comp, array_name);

			plyexpoter->Get()->SetArrayName(array_name);
			plyexpoter->Get()->SetLookupTable(meshFilter->GetPolyMapper()->GetLookupTable());
			//plyexpoter->SaveFile(Mapper->GetOutputPort(), array_name, output);
			plyexpoter->SaveFile(curvaturesFilter->GetOutputPort(), array_name, (char*)debug_file.c_str());
			//plyexpoter->SaveFile(polygon1->Get()->GetOutputPort(), color_array->GetName(), output);
			delete plyexpoter;
		}
	}
	if (!no_render || render_only)
	{
#if 0
		char testbuf[128];
		vtkSmartPointer<vtkColorSeries> colorSeries = vtkSmartPointer<vtkColorSeries>::New();
		colorSeries->SetColorScheme(scheme);
		gmrVTKText* text2d = new gmrVTKText;

		sprintf(testbuf, "Using color scheme[%d][%s]", colorSeries->GetColorScheme(), colorSeries->GetColorSchemeName().c_str());

		render->Run();	//get Window size!!
		int* win_size = render->GetRenderWindow()->GetScreenSize();
		printf("%dx%d\n", win_size[0], win_size[1]);

		text2d->SetText(testbuf);
		text2d->SetColor(0.0, 0.0, 0.0);
		text2d->SetSize(15);
		text2d->SetPosition(10, win_size[1]-20);
		render->AddActor(text2d->GetActor());

		render->Run();
		render->GetRenderWindow()->SetWindowName("curvature");

		// Screenshot  
		vtkSmartPointer<vtkWindowToImageFilter> windowToImageFilter =
			vtkSmartPointer<vtkWindowToImageFilter>::New();
		windowToImageFilter->SetInput(render->GetRenderWindow());
		windowToImageFilter->SetMagnification(3);			//set the resolution of the output image (3 times the current resolution of vtk render window)
		windowToImageFilter->SetInputBufferTypeToRGBA();	//also record the alpha (transparency) channel
		windowToImageFilter->ReadFrontBufferOff();			// read from the back buffer
		windowToImageFilter->Update();
		vtkSmartPointer<vtkPNGWriter> writer =
			vtkSmartPointer<vtkPNGWriter>::New();

		char screenshotName[128];
		sprintf(screenshotName, "screenshot_colorScheme%02d.png", colorSeries->GetColorScheme());
		writer->SetFileName(screenshotName);
		writer->SetInputConnection(windowToImageFilter->GetOutputPort());
		writer->Write();
#endif
		render->DefaultRun("curvature");

	}

	delete meshFilter;
	delete polygon1;

}