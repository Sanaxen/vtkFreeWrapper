#include "gmrVTKRender.hpp"
#include "gmrVTKImport.hpp"
#include "gmrVTKExport.hpp"

#include <vtkCleanPolyData.h>
#include <vtkDecimatePro.h>
#include <vtkCurvatures.h>
#include <vtkColorSeries.h>
#include <vtkColorTransferFunction.h>

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
		printf("Curvatures obj_file [-t mean|gauss|max|min -range min max] -o output\n");
		return -99;
	}
	vtkObject::SetGlobalWarningDisplay(0);
	
	int type = 0;
	int scalarRange_set = 0;
	double scalarRange[2];
	char* file1 = NULL;
	char* output = NULL;

	for (int i = 1; i < argc; i++)
	{
		if (strcmp(argv[i], "-t") == 0)
		{
			if (strcmp("mean", argv[i + 1]) == 0) type = 0;
			if (strcmp("gauss", argv[i + 1]) == 0) type = 1;
			if (strcmp("max", argv[i + 1]) == 0) type = 2;
			if (strcmp("min", argv[i + 1]) == 0) type = 3;
			i++;
			continue;
		}
		if (strcmp(argv[i], "-o") == 0)
		{
			output = argv[i + 1];
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

	vtkSmartPointer<vtkCleanPolyData> clean1 = vtkSmartPointer<vtkCleanPolyData>::New();
	clean1->SetInputConnection(polygon1->Get()->GetOutputPort());
	clean1->SetTolerance(1.0E-8);
	clean1->PointMergingOn();
	clean1->SetOutputPointsPrecision(vtkAlgorithm::DOUBLE_PRECISION);
	clean1->Update();
	if (clean1->GetErrorCode())
	{
		printf("clean error.\n");
		return -2;
	}

	vtkSmartPointer<vtkCurvatures> curvaturesFilter =
		vtkSmartPointer<vtkCurvatures>::New();
	curvaturesFilter->SetInputConnection(clean1->GetOutputPort());
	if (type == 3) curvaturesFilter->SetCurvatureTypeToMinimum();
	if (type == 2) curvaturesFilter->SetCurvatureTypeToMaximum();
	if ( type == 1 ) curvaturesFilter->SetCurvatureTypeToGaussian();
	if ( type == 0 ) curvaturesFilter->SetCurvatureTypeToMean();
	curvaturesFilter->Update();
	if (curvaturesFilter->GetErrorCode())
	{
		printf("curvatures error.\n");
		return -2;
	}

	if (!scalarRange_set)
	{
		curvaturesFilter->GetOutput()->GetScalarRange(scalarRange);
	}


	int scheme = 16;

	vtkSmartPointer<vtkColorSeries> colorSeries =
		vtkSmartPointer<vtkColorSeries>::New();
	colorSeries->SetColorScheme(scheme);
	std::cout << "Using color scheme #: "
		<< colorSeries->GetColorScheme() << " is "
		<< colorSeries->GetColorSchemeName() << std::endl;

	vtkSmartPointer<vtkColorTransferFunction> lut =
		vtkSmartPointer<vtkColorTransferFunction>::New();
	lut->SetColorSpaceToHSV();

	int numColors = colorSeries->GetNumberOfColors();
	for (int i = 0; i < numColors; i++)
	{
		vtkColor3ub color = colorSeries->GetColor(i);
		double dColor[3];
		dColor[0] = static_cast<double> (color[0]) / 255.0;
		dColor[1] = static_cast<double> (color[1]) / 255.0;
		dColor[2] = static_cast<double> (color[2]) / 255.0;
		double t = scalarRange[0] + (scalarRange[1] - scalarRange[0])
			/ (numColors - 1) * i;
		lut->AddRGBPoint(t, dColor[0], dColor[1], dColor[2]);
	}


	vtkSmartPointer<vtkPolyDataMapper> Mapper = vtkSmartPointer<vtkPolyDataMapper>::New();

	Mapper->SetInputConnection(curvaturesFilter->GetOutputPort());
	Mapper->SetLookupTable(lut);
	Mapper->SetScalarRange(scalarRange);

	Mapper->ScalarVisibilityOn();
	Mapper->SetScalarModeToUsePointData();
	Mapper->SetColorModeToMapScalars();

	vtkSmartPointer<vtkActor> Actor = vtkSmartPointer<vtkActor>::New();
	Actor->SetMapper(Mapper);

	vtkSmartPointer<vtkScalarBarActor> scalarBar =
		vtkSmartPointer<vtkScalarBarActor>::New();
	scalarBar->SetLookupTable(Mapper->GetLookupTable());
	scalarBar->SetTitle(
		curvaturesFilter->GetOutput()->GetPointData()->GetScalars()->GetName());
	scalarBar->SetNumberOfLabels(5);

	gmrVTKRender* render = new gmrVTKRender;
	render->GetRenderer()->AddViewProp(Actor);
	render->GetRenderer()->AddActor2D(scalarBar);

	curvaturesFilter->Update();
	gmrVTKExportOBJ* expoter = new gmrVTKExportOBJ();
	char* p = strstr(output, ".obj");
	if (p) *p = '\0';
	p = strstr(output, ".OBJ");
	if (p) *p = '\0';

	expoter->SaveFile(render, output);
	delete expoter;

	gmrVTKExportPLY* plyexpoter = new gmrVTKExportPLY();
	p = strstr(output, ".ply");
	if (p) *p = '\0';
	p = strstr(output, ".PLY");
	if (p) *p = '\0';

	//int size = curvaturesFilter->GetOutput()->GetNumberOfVerts();
	//vtkSmartPointer<vtkUnsignedCharArray>
	//color_array = vtkSmartPointer<vtkUnsignedCharArray>::New();
	//color_array->SetName("RGB");
	//color_array->SetNumberOfComponents(3);
	//color_array->SetNumberOfTuples(size);
	//for (int i = 0; i < size; i++)
	//{
	//	vtkDataArray* q = curvaturesFilter->GetPolyDataInput(0)->GetPointData()->GetScalars();
	//	color_array->SetValue(3 * i + 0, q[i].));
	//}
	double opacity = Actor->GetProperty()->GetOpacity();
	vtkUnsignedCharArray* color_array = Mapper->MapScalars(opacity);
	//vtkUnsignedCharArray* color_array = Mapper->GetColorMapColors();
	int comp = color_array->GetNumberOfComponents();

	printf("GetNumberOfComponents:%d\n", comp);

	char array_name[16];
	strcpy(array_name, "Colors");

	color_array->SetName(array_name);

	plyexpoter->Get()->SetArrayName(array_name);
	//plyexpoter->Get()->SetLookupTable(Mapper->GetLookupTable());
	//plyexpoter->SaveFile(Mapper->GetOutputPort(), array_name, output);
	//plyexpoter->SaveFile(curvaturesFilter->GetOutputPort(), array_name, output);
	plyexpoter->SaveFile(polygon1->Get()->GetOutputPort(), array_name, output);
	delete plyexpoter;
	

	render->DefaultRun();
}