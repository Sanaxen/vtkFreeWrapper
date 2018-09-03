/************************************************************
*
* vtkWrapperLIBを使った簡単なサンプルプログラム
*
*************************************************************/

#include "MRI_view__.h"
#include "gmrVTK.hpp"
#include "gmrVTKLIBs.hpp"



//#include "execute.hpp"

/*
 * VTKを簡単に（？）使うための簡単クラスライブラリの使用例
 * Copyright (c) Sanaxen
 *
 */
#include "gmrVTKDICOM.hpp"
#include "gmrVTKCapture.hpp"
#include "gmrVTKOutline.hpp"

#include "gmrVTKCommand.hpp"
#include "gmrVTKText.hpp"
#include "gmrVTKExport.hpp"
#include "gmrVTKImport.hpp"
#include "gmrVTKPicker.hpp"
#include "gmrVTKPoints.hpp"
#include "gmrVTKPolyline.hpp"
#include "gmrVTKAxes.hpp"

#include "vtkBoxWidget.h"
#include "vtkTransform.h"
#include "vtkGPUVolumeRayCastMapper.h"

#include "vtkPolyDataPointPlacer.h"
#include "vtkTriangleFilter.h"
#include "vtkCleanPolyData.h"
#include "vtkPlanes.h"
#include "vtkDistanceWidget.h"
#include "vtkDistanceRepresentation3D.h"
#include "vtkDistanceRepresentation2D.h"
#include "vtkPointHandleRepresentation3D.h"
#include "vtkVolumePicker.h"

#include "vtkCaptionActor2D.h"

#include <string>

#include "vtkImageReader.h"
#include "vtkPolyDataReader.h"

#include <chrono>
#include "gmrVTKMeshFilter.hpp"

#ifndef STB_IMAGE_IMPLEMENTATION
#define STB_IMAGE_IMPLEMENTATION
#include "../stb/stb_image.h"
#endif

#include <vtkSliderWidget.h>
#include <vtkSliderRepresentation3D.h>
#include <vtkSliderRepresentation2D.h>

 // DICOM sample image sets
 // http://149.142.216.30/DICOM_FILES/Index.html

extern "C" void DICOM_SliceViewer(char* folderName, int capture)
{
	gmrVTKDICOM *reader = new gmrVTKDICOM;

	//    reader->SetDirectoryName("data\\PANORAMIX\\Abdomen 1ABD_PEL_AAA\\Abd-Pel w-c  3.0  B30f");
	reader->SetDirectoryName(folderName);
	reader->LoadImageData();

	if (capture)
	{
		//reader->GetImageViewer()->GetRenderWindow()->SetOffScreenRendering(1);
	}

	int znum = reader->GetZnum();

	for (int i = 0; i < znum; i++)
	{
		gmrVTKCaptureBMP* Capture = NULL;
		if (capture)
		{
			Capture = new gmrVTKCaptureBMP;
			Capture->SetInput(reader->GetImageViewer());
			Capture->SetFileName("Capture");
		}

		reader->ViewerZSlice(i, 400, 128);

		if (capture)
		{
			Capture->SetInput(reader->GetImageViewer());
			Capture->Capture(i);
			delete Capture;
		}
	}

	delete reader;
}


extern "C" void DICOM2BMP(char* dcm_files_folderName)
{
	char* folderName;

	folderName = dcm_files_folderName;

	// DICOM スライスViewer
	fprintf(stderr, "==> convert bitmap!!\n");
	DICOM_SliceViewer(folderName, 1);
	fprintf(stderr, "finish.\n");
}

vtkSmartPointer<vtkPolyDataPointPlacer> pointPlacer = 0;
vtkSmartPointer<vtkPointHandleRepresentation3D> handleRep = 0;
vtkSmartPointer<vtkDistanceRepresentation2D> distanceRep = 0;
vtkDistanceWidget* distanceWidget = 0;

int picker_flag = 0;
vtkVolumePicker* cellpicker = 0;

class pickPoint
{
public:
	pickPoint()
	{
		points = 0;
		lines = 0;
		sectionTextActor = 0;
	}
	double x, y;
	double pos[3];
	gmrVTKPoints* points;
	gmrVTKPolyline* lines;
	vtkCaptionActor2D* sectionTextActor;
};

std::vector<pickPoint> pickPointList;

gmrVTKPicker* picker = 0;

vtkBoxWidget *boxWidget = 0;
vtkBoxWidget *boxWidget2 = 0;
int RubberBandZoom_flag = 0;

class ErrorObserver : public vtkCommand
{
public:
	ErrorObserver() :
		Error(false),
		Warning(false),
		ErrorMessage(""),
		WarningMessage("") {}
	static ErrorObserver *New()
	{
		return new ErrorObserver;
	}
	bool GetError() const
	{
		return this->Error;
	}
	bool GetWarning() const
	{
		return this->Warning;
	}
	void Clear()
	{
		this->Error = false;
		this->Warning = false;
		this->ErrorMessage = "";
		this->WarningMessage = "";
	}
	virtual void Execute(vtkObject *vtkNotUsed(caller),
		unsigned long event,
		void *calldata)
	{
		switch (event)
		{
		case vtkCommand::ErrorEvent:
			ErrorMessage = static_cast<char *>(calldata);
			this->Error = true;
			break;
		case vtkCommand::WarningEvent:
			WarningMessage = static_cast<char *>(calldata);
			this->Warning = true;
			break;
		}
	}
	std::string GetErrorMessage()
	{
		return ErrorMessage;
	}
	std::string GetWarningMessage()
	{
		return WarningMessage;
	}
private:
	bool        Error;
	bool        Warning;
	std::string ErrorMessage;
	std::string WarningMessage;
};

////////////////////////////////////////////////////////////////////////////////////////
// KeyPressEventを拾うためのコールバック
class MyCallback : public gmrVTKCommand
{
public:
	MyCallback() { ; };

	static MyCallback *New() {
		return new MyCallback;
	}

	virtual void Execute(vtkObject *caller, unsigned long eventId, void*)
	{
		vtkRenderWindowInteractor *iren =
			reinterpret_cast<vtkRenderWindowInteractor*>(caller);

		char* key = iren->GetKeySym();

		if (std::string(key) == "d")
		{
			if (picker_flag)
			{
				printf("picker OFF\n");
				picker_flag = 0;
			}
			else
			{
				printf("picker ON\n");
				picker_flag = 1;
			}
		}
		if (std::string(key) == "D")
		{
			for (int i = 0; i < pickPointList.size(); i++)
			{
				this->GetRenderer()->RemoveActor(pickPointList[i].points->GetActor());
				if (pickPointList[i].lines)
				{
					this->GetRenderer()->RemoveActor(pickPointList[i].lines->GetActor());
					delete pickPointList[i].lines;
				}
				if (pickPointList[i].sectionTextActor)
				{
					this->GetRenderer()->RemoveActor(pickPointList[i].sectionTextActor);
					pickPointList[i].sectionTextActor->Delete();
				}

				delete pickPointList[i].points;
			}
			pickPointList.clear();
			this->GetRenderer()->GetRenderWindow()->Render();
		}

		// スペース・キーが押されたらRubberBandZoomにする
		if (std::string(key) == "space")
		{
			if (!RubberBandZoom_flag)
			{
				RubberBandZoom_flag = 1;
				this->GetRenderer()->InteractorStyleRubberBandZoom();
			}
			else
			{
				RubberBandZoom_flag = 0;
				this->GetRenderer()->InteractorStyleTrackballCamera();
			}
		}


		if (std::string(key) == "b" && boxWidget)
		{
			if (boxWidget->GetEnabled())
			{
				boxWidget->Off();
			}
			else
			{
				boxWidget->On();
			}
		}
		if (std::string(key) == "c" && boxWidget2)
		{
			if (boxWidget2->GetEnabled())
			{
				boxWidget2->Off();
			}
			else
			{
				boxWidget2->On();
			}
		}
		if (std::string(key) == "m" && distanceWidget)
		{
			if (distanceWidget->GetEnabled())
			{
				distanceWidget->Off();
				distanceWidget->Delete();
				distanceWidget = vtkDistanceWidget::New();
				distanceWidget->SetRepresentation(distanceRep);
				distanceWidget->SetInteractor(this->GetRenderer()->GetRenderWindowInteractor());
			}
			else
			{
				distanceWidget->On();
			}
		}
	}
};

//BoxWidgetののコールバック
class vtkMyCallback2 : public gmrVTKCommand
{
public:
	static vtkMyCallback2 *New()
	{
		return new vtkMyCallback2;
	}
	virtual void Execute(vtkObject *caller, unsigned long, void*)
	{
		vtkTransform *t = vtkTransform::New();
		vtkBoxWidget *widget = reinterpret_cast<vtkBoxWidget*>(caller);
		widget->GetTransform(t);
		widget->GetProp3D()->SetUserTransform(t);
		t->Delete();
	}
};

bool surfaceRendering = false;

vtkSmartPointer<vtkPolyDataMapper> RCsurface_mapper;
vtkPolyDataMapper *RCskinMapper;
vtkGPUVolumeRayCastMapper* RCvolumeMapper;
//BoxWidgetののコールバック
class vtkMyCallback3 : public gmrVTKCommand
{
public:
	static vtkMyCallback3 *New()
	{
		return new vtkMyCallback3;
	}
	virtual void Execute(vtkObject *caller, unsigned long, void*)
	{
		vtkBoxWidget *widget = reinterpret_cast<vtkBoxWidget*>(caller);
		vtkPlanes *planes = vtkPlanes::New();

		//Get the planes of the box widget and apply them to the ray cast mapper
		widget->GetPlanes(planes);

		RCvolumeMapper->SetClippingPlanes(planes);
		if (surfaceRendering)
		{
			RCsurface_mapper->SetClippingPlanes(planes);
		}
		else
		{
			RCskinMapper->SetClippingPlanes(planes);
		}
	}
};

class MyCallbackPick : public gmrVTKCommand
{
	char buf[256];
	gmrVTKText* text;

public:
	MyCallbackPick() { text = NULL; };

	static MyCallbackPick *New() {
		return new MyCallbackPick;
	}

	virtual void Execute(vtkObject *caller, unsigned long eventId, void*)
	{
		printf("@picker_flag:%d\n", picker_flag);
		if (!picker_flag) return;

		vtkRenderWindowInteractor *iren =
			reinterpret_cast<vtkRenderWindowInteractor*>(caller);

		// Window Position
		double x = iren->GetEventPosition()[0];
		double y = iren->GetEventPosition()[1];

		printf("%f %f\n", x, y);

		// 3D Positon
		pickPoint wpos;
		double pos[3];

		wpos.x = x;
		wpos.y = y;
		int succed = cellpicker->Pick(x, y, 0, this->GetRenderer()->GetRenderer());
		cellpicker->GetPickPosition(wpos.pos);


		sprintf(buf, "X=%f Y=%f Z=%f (%d,%d)", wpos.pos[0], wpos.pos[1], wpos.pos[2], (int)(x), (int)(y));
		//sprintf(buf, "(%.3f,%.3f,%.3f)", wpos.pos[0], wpos.pos[1], wpos.pos[2]);

		//if (text == NULL) text = new gmrVTKText;
		//else {
		//	this->GetRenderer()->RemoveActor(text->GetActor());
		//}
		//text->SetText(buf);
		//text->SetPosition(5,200);
		//text->SetSize(13);

		double scalar[3] = { 1,1,1 };
		if (succed)
		{
			//text->SetColor(1, 1, 1);
			wpos.points = new gmrVTKPoints;

			wpos.points->SetSize(10);
			wpos.points->SetPoint(wpos.pos);
			wpos.points->SetDiffuseColor(1, 0, 0);
			//wpos.points->SetScalar(scalar);
			this->GetRenderer()->AddActor(wpos.points->GetActor());

			pickPointList.push_back(wpos);

			if (pickPointList.size() && pickPointList.size() % 2 == 0)
			{
				gmrVTKPolyline* poly = new gmrVTKPolyline;

				int n = pickPointList.size() - 1;

				poly->SetPoint(pickPointList[n].pos);
				poly->SetPoint(pickPointList[n - 1].pos);
				poly->SetSize(2);
				//poly->SetScalar(scalar);
				poly->SetDiffuseColor(0.0, 1.0, 0.0);

				pickPointList.pop_back();
				wpos.lines = poly;


				double dist =
					(pickPointList[n].pos[0] - pickPointList[n - 1].pos[0])*(pickPointList[n].pos[0] - pickPointList[n - 1].pos[0]) +
					(pickPointList[n].pos[1] - pickPointList[n - 1].pos[1])*(pickPointList[n].pos[1] - pickPointList[n - 1].pos[1]) +
					(pickPointList[n].pos[2] - pickPointList[n - 1].pos[2])*(pickPointList[n].pos[2] - pickPointList[n - 1].pos[2]);
				dist = sqrt(dist);

				char buf[256];

				// Caption
				wpos.sectionTextActor = vtkCaptionActor2D::New();

				double dx = (pickPointList[n].pos[0] + pickPointList[n - 1].pos[0]) / 2.0;
				double dy = (pickPointList[n].pos[1] + pickPointList[n - 1].pos[1]) / 2.0;
				double dz = (pickPointList[n].pos[2] + pickPointList[n - 1].pos[2]) / 2.0;

				sprintf(buf, "%.3f", dist);

				wpos.sectionTextActor->SetAttachmentPoint(dx, dy, dz);
				wpos.sectionTextActor->SetCaption(buf);
				wpos.sectionTextActor->BorderOff();
				wpos.sectionTextActor->LeaderOn();
				wpos.sectionTextActor->SetPadding(0);
				wpos.sectionTextActor->GetCaptionTextProperty()->SetJustificationToLeft();
				wpos.sectionTextActor->GetCaptionTextProperty()->ShadowOff();
				wpos.sectionTextActor->GetCaptionTextProperty()->ItalicOff();
				wpos.sectionTextActor->GetCaptionTextProperty()->SetFontFamilyToCourier();
				wpos.sectionTextActor->GetCaptionTextProperty()->SetFontSize(24);
				wpos.sectionTextActor->GetTextActor()->SetTextScaleModeToNone();
				pickPointList.push_back(wpos);



				//this->GetRenderer()->GetRenderer()->AddActor2D(wpos.sectionTextActor);

				this->GetRenderer()->AddActor(wpos.sectionTextActor);
				this->GetRenderer()->AddActor(poly->GetActor());
			}
		}
		else
		{
			//text->SetColor(0.5, 0.5, 0.5);
		}
		//text->SetColor(1, 0, 0);
		//this->GetRenderer()->AddActor(text->GetActor());
		this->GetRenderer()->GetRenderWindow()->Render();
	}
};

int DICOM_3DViewer_colorScheme = -1;
double DICOM_3DViewer_isoRange[2] = { -300.0, 300.0 };

extern "C" int GetDICOM_3DViewer_colorScheme()
{
	return DICOM_3DViewer_colorScheme;
}
extern "C" void SetDICOM_3DViewer_colorScheme(int scheme)
{
	DICOM_3DViewer_colorScheme = scheme;
}
extern "C" void SetDICOM_3DViewer_isoRange(double range[2])
{
	DICOM_3DViewer_isoRange[0] = range[0];
	DICOM_3DViewer_isoRange[1] = range[1];
}

extern "C" void DICOM_3DViewer(char* folderName, int output, double sample_dist, double isovalue, char* outfile)
{
	gmrVTKText* text1 = new gmrVTKText;
	text1->SetText("space key =>RubberBandZoom on/off");
	text1->SetPosition(20, 140);
	text1->SetSize(15);
	text1->SetColor(1.0, 0.0, 0.0);

	gmrVTKText* text2 = new gmrVTKText;
	text2->SetText("---------------------");
	text2->SetPosition(20, 120);
	text2->SetSize(15);
	text2->SetColor(0, 1.0, 0.0);

	gmrVTKText* text3 = new gmrVTKText;
	text3->SetText("r key => resize box on/off");
	text3->SetPosition(20, 100);
	text3->SetSize(15);
	text3->SetColor(0, 1.0, 0.0);

	gmrVTKText* text4 = new gmrVTKText;
	text4->SetText("c key => cross section  box on/off");
	text4->SetPosition(20, 80);
	text4->SetSize(15);
	text4->SetColor(0, 1.0, 0.0);

	gmrVTKText* text5 = new gmrVTKText;
	text5->SetText("d key => measure on/off");
	text5->SetPosition(20, 60);
	text5->SetSize(15);
	text5->SetColor(0, 1.0, 0.0);

	gmrVTKText* text6 = new gmrVTKText;
	text6->SetText("D key => measure clear");
	text6->SetPosition(20, 40);
	text6->SetSize(15);
	text6->SetColor(0, 1.0, 0.0);

	gmrVTKText* text7 = new gmrVTKText;
	text7->SetText("m key => measure(2D) on/off");
	text7->SetPosition(20, 20);
	text7->SetSize(15);
	text7->SetColor(0, 1.0, 0.0);

	gmrVTKText* text8 = new gmrVTKText;
	text8->SetText("b key => box(3D-scaling)  box on/off");
	text8->SetPosition(20, 0);
	text8->SetSize(15);
	text8->SetColor(0, 1.0, 0.0);

	gmrVTKRender* render;
#if 10
	render = new gmrVTKRender;
#else
	int offscreen = 1;
	if (output)
	{
		render = new gmrVTKRender(offscreen);
	}
	else {
		render = new gmrVTKRender;
	}
#endif
	gmrVTKDICOM *reader = new gmrVTKDICOM;
	if (sample_dist > 0.0)
	{
		reader->SampleDistance() = sample_dist;
	}
	if (output != 100)
	{
		reader->surface_On = 1;
		reader->IsoValue() = isovalue;
	}

	vtkObject::SetGlobalWarningDisplay(0);
	vtkSmartPointer<ErrorObserver>  errorObserver =
		vtkSmartPointer<ErrorObserver>::New();
	render->GetRenderWindowInteractor()->AddObserver(vtkCommand::ErrorEvent, errorObserver);
	render->GetRenderWindowInteractor()->AddObserver(vtkCommand::WarningEvent, errorObserver);

	reader->GetDICOMImage()->AddObserver(vtkCommand::ErrorEvent, errorObserver);
	reader->GetDICOMImage()->AddObserver(vtkCommand::WarningEvent, errorObserver);

	char drive[_MAX_DRIVE];	// ドライブ名
	char dir[_MAX_DIR];		// ディレクトリ名
	char fname[_MAX_FNAME];	// ファイル名
	char ext[_MAX_EXT];		// 拡張子

	_splitpath(folderName, drive, dir, fname, ext);

	bool color_def = false;
	char colorset[256];
	sprintf(colorset, "%s%scolor.def", drive, dir);
	printf("colorset[%s]\n", colorset);

	FILE* fp = fopen(colorset, "r");
	if (fp == NULL)
	{
		char szFullPath[_MAX_PATH] = { '\0' };
		char *szFilePart;
		DWORD dwRet = GetFullPathNameA(colorset, _MAX_PATH, szFullPath, &szFilePart);
		if (fp == NULL)
		{
			printf("file open error,[%s]\n", szFullPath);
			if (strlen(szFullPath) >= _MAX_PATH || dwRet == 0)
			{
				printf("FullPathName failed.!\n");
			}
		}
	}
	if (fp == NULL)
	{
		printf("undefined [color.def]\n");
	}
	if (fp)
	{
		color_def = true;
		printf("load color.def\n");
		char buf[256];
		char colorset2[256];
		if (fgets(buf, 256, fp) != NULL)
		{
			strcpy(colorset2, buf);
			if (colorset2[strlen(colorset2) - 1] == '\n')
			{
				colorset2[strlen(colorset2) - 1] = '\0';
			}
		}
		fclose(fp);
		sprintf(colorset, "%s%s%s", drive, dir, colorset2);
		printf("colorset[%s]\n", colorset);

		fp = fopen(colorset, "r");
		if (fp == NULL)
		{
			char szFullPath[_MAX_PATH] = { '\0' };
			char *szFilePart;
			DWORD dwRet = GetFullPathNameA(colorset, _MAX_PATH, szFullPath, &szFilePart);
			if (fp == NULL)
			{
				printf("file open error,[%s]\n", szFullPath);
				if (strlen(szFullPath) >= _MAX_PATH || dwRet == 0)
				{
					printf("FullPathName failed.!\n");
				}
			}
		}
		if (fp)
		{
			printf("=>%s\n", colorset);
			reader->volumeColorSet.clear();
			char buf[256];
			while (fgets(buf, 256, fp) != NULL)
			{
				_volumeColorValue c;
				sscanf(buf, "%lf,%lf,%lf,%lf,%lf", c.x, c.x + 1, c.x + 2, c.x + 3, c.x + 4);
				reader->volumeColorSet.push_back(c);
			}
			fclose(fp);
			for (int i = 0; i < reader->volumeColorSet.size(); i++)
			{
				printf("%f,%f,%f,%f,%f\n", reader->volumeColorSet[i].x[0], reader->volumeColorSet[i].x[1], reader->volumeColorSet[i].x[2], reader->volumeColorSet[i].x[3], reader->volumeColorSet[i].x[4]);
			}
		}
	}

	//    reader->SetDirectoryName("data\\PANORAMIX\\Abdomen 1ABD_PEL_AAA\\Abd-Pel w-c  3.0  B30f");
	//    reader->SetDirectoryName("data");
	reader->SetDirectoryName(folderName);
	reader->LoadImageData();
	if (errorObserver->GetError())
	{
		//std::cout << "Caught error! " << errorObserver->GetErrorMessage();
		std::cout << "Error! " << "DICOM Image: Either a filename was not specified or the specified directory does not contain any DICOM images.";
		return;
	}
	if (reader->GetDICOMImage()->GetErrorCode())
	{
		return;
	}

	render->AddActor(text1->GetActor());
	render->AddActor(text2->GetActor());
	render->AddActor(text3->GetActor());
	render->AddActor(text4->GetActor());
	render->AddActor(text5->GetActor());
	render->AddActor(text6->GetActor());
	render->AddActor(text7->GetActor());
	render->AddActor(text8->GetActor());

	RCvolumeMapper = reader->GetVolumeMapper();
	RCskinMapper = reader->GetskinMapper();
	if (reader->surface_On)
	{
		surfaceRendering = true;
		RCsurface_mapper = reader->GetSurface_Mapper();
	}
	//vtkCamera *camera = vtkCamera::New();
	//camera->SetViewUp(1,0,0);
	//camera->SetPosition(0,1,0);
	//camera->SetFocalPoint(0,0,0);
	//camera->ComputeViewPlaneNormal();

	// Add Axes X-Y-Z
	gmrVTKAxes *axes = new gmrVTKAxes;
	axes->SetLength(10.0);
	axes->SetOrigin(-6.0, 2.0, -6.0);
	axes->SetRadius(0.05);
	axes->SymmetricOff();

	pointPlacer = vtkSmartPointer<vtkPolyDataPointPlacer>::New();
	pointPlacer->AddProp(reader->GetVolume());

	handleRep = vtkSmartPointer<vtkPointHandleRepresentation3D>::New();
	handleRep->SetHandleSize(50);
	handleRep->GetProperty()->SetColor(1., 0., 0.);
	handleRep->SetPointPlacer(pointPlacer);

	distanceRep = vtkSmartPointer<vtkDistanceRepresentation2D>::New();
	distanceRep->SetHandleRepresentation(handleRep);
	distanceRep->SetLabelFormat("%-#6.3g mm");

	distanceWidget = vtkDistanceWidget::New();
	distanceWidget->SetRepresentation(distanceRep);
	distanceWidget->SetInteractor(render->GetRenderWindowInteractor());

	if (output == 100)
	{
		render->AddActor(reader->GetVolume());
		if (reader->surface_On)
		{
			render->AddActor(reader->GetSurfaceActor());
		}
	}
	//render->GetRenderer()->SetActiveCamera(camera);
	//render->GetRenderer()->ResetCamera();

	if (output == 100)
	{
		/* empty */
	}
	else
	{

		if (reader->surface_On)
		{
			reader->GetSurfaceActor()->GetProperty()->SetColor(1, 1, 1);
			//if (reader->volumeColorSet.size() >= 2)
			//{
			//	printf("surface color set\n");
			//	for (int i = 1; i < reader->volumeColorSet.size(); ++i)
			//	{
			//		printf("%f -> [%f,%f]\n", reader->IsoValue(), reader->volumeColorSet[i - 1].x[0], reader->volumeColorSet[i].x[0]);
			//		if (reader->volumeColorSet[i-1].x[0] <= reader->IsoValue() && reader->volumeColorSet[i].x[0] > reader->IsoValue())
			//		{
			//			printf("==>%f -> [%f,%f]\n", reader->IsoValue(), reader->volumeColorSet[i - 1].x[0], reader->volumeColorSet[i].x[0]);
			//			reader->GetSurfaceActor()->GetProperty()->SetColor(reader->volumeColorSet[i].x[1], reader->volumeColorSet[i].x[2], reader->volumeColorSet[i].x[3]);
			//		}
			//	}
			//	if (reader->volumeColorSet[0].x[0] > reader->IsoValue())
			//	{
			//		reader->GetSurfaceActor()->GetProperty()->SetColor(reader->volumeColorSet[1].x[1]*0.7, reader->volumeColorSet[1].x[2] * 0.7, reader->volumeColorSet[1].x[3] * 0.7);
			//	}
			//	if (reader->volumeColorSet[reader->volumeColorSet.size()-1].x[0] < reader->IsoValue())
			//	{
			//		reader->GetSurfaceActor()->GetProperty()->SetColor(reader->volumeColorSet[reader->volumeColorSet.size() - 2].x[1]*0.7, reader->volumeColorSet[reader->volumeColorSet.size() - 2].x[2] * 0.7, reader->volumeColorSet[reader->volumeColorSet.size() - 2].x[3] * 0.7);
			//	}
			//}
			//else
			{
				reader->GetSurfaceActor()->GetProperty()->SetColor(240. / 255., 217. / 255., 202. / 255.);
				reader->GetSurfaceActor()->GetProperty()->SetSpecular(0.2);

				if (reader->IsoValue() > 50.0)
				{
					reader->GetSurfaceActor()->GetProperty()->SetColor(227. / 255., 114. / 255., 69. / 255.);
				}
				if (reader->IsoValue() > 100.0)
				{
					reader->GetSurfaceActor()->GetProperty()->SetColor(223. / 255., 135. / 255., 113. / 255.);
				}
				if (reader->IsoValue() > 200.0)
				{
					reader->GetSurfaceActor()->GetProperty()->SetColor(1, 1, 1);
				}
			}
			render->AddActor(reader->GetSurfaceActor());
		}
		else
		{
			reader->GetActor()->GetProperty()->SetColor(221. / 255., 207. / 255., 187. / 255.);
			//reader->GetActor()->GetProperty()->SetDiffuseColor(186./255., 248./255., 112./255.);
			render->AddActor(reader->GetActor());
		}

		gmrVTKOutline *outlineData = new gmrVTKOutline(NULL);
		outlineData->GetOutlineFilter()->SetInputConnection(reader->GetDICOMImage()->GetOutputPort());

		//render->AddActor( outlineData->GetActor());
	}

	if (output == 101)
	{
		//render->GetRenderer()->AddViewProp(reader->volume);
		render->AddActor(reader->GetVolume());
		if (reader->surface_On)
		{
			render->AddActor(reader->GetSurfaceActor());
		}
	}
	//render->SetBackgroundColor( 0.4, 0.4, 0.4 );
	render->SetBackgroundColor(0.004, 0.004, 0.004);
	render->GetRenderWindow()->SetWindowName("MRI viewer");

	if (output == 1 || output == 11)
	{
		gmrVTKExportOBJ* expoter = new gmrVTKExportOBJ();
		if (outfile != NULL)
		{
			double isoRange[2] = { DICOM_3DViewer_isoRange[0], DICOM_3DViewer_isoRange[1] };

			int colorScheme = DICOM_3DViewer_colorScheme;
			if (colorScheme < 0) colorScheme = 0;

			vtkSmartPointer<vtkColorSeries> colorSeries = vtkSmartPointer<vtkColorSeries>::New();
			colorSeries->SetColorScheme(colorScheme);
			std::cout << "Using color scheme #: "
				<< colorSeries->GetColorScheme() << " is "
				<< colorSeries->GetColorSchemeName() << std::endl;

			vtkSmartPointer<vtkColorTransferFunction> lut = vtkSmartPointer<vtkColorTransferFunction>::New();
			lut->SetColorSpaceToHSV();

			int numColors = colorSeries->GetNumberOfColors();
			for (int i = 0; i < numColors; i++)
			{
				vtkColor3ub color = colorSeries->GetColor(i);
				double dColor[3];
				dColor[0] = static_cast<double> (color[0]) / 255.0;
				dColor[1] = static_cast<double> (color[1]) / 255.0;
				dColor[2] = static_cast<double> (color[2]) / 255.0;
				double t = isoRange[0] + (isoRange[1] - isoRange[0])
					/ (numColors - 1) * i;
				lut->AddRGBPoint(t, dColor[0], dColor[1], dColor[2]);
			}


			printf("[%s]\n", outfile);
			vtkSmartPointer<vtkUnsignedCharArray> colors =
				vtkSmartPointer<vtkUnsignedCharArray>::New();
			colors->SetNumberOfComponents(3);
			colors->SetNumberOfTuples(reader->GetMesh()->GetPoints()->GetNumberOfPoints());
			colors->SetName("DicomColors");

			double rgb[3];
			if (DICOM_3DViewer_colorScheme < 0)
			{
				reader->GetSurfaceActor()->GetProperty()->GetColor(rgb[0], rgb[1], rgb[2]);
			}
			else
			{
				lut->GetColor(reader->IsoValue(), rgb);
			}
			for (int i = 0; i < reader->GetMesh()->GetPoints()->GetNumberOfPoints(); i++)
			{
				colors->SetComponent(i, 0, rgb[0] * 255);
				colors->SetComponent(i, 1, rgb[1] * 255);
				colors->SetComponent(i, 2, rgb[2] * 255);
			}
			reader->GetMesh()->GetPointData()->SetScalars(colors);
			reader->GetSurface_Mapper()->SetColorModeToDefault();

			std::string file = outfile;
			file += ".obj";
			int stat = expoter->exportVertexColorOBJ((char*)file.c_str(), reader->GetMesh(), colors);
			if (stat != 0)
			{
				expoter->SaveFile(render, outfile);
			}
		}
		else
			expoter->SaveFile(render, "aaa");
		delete expoter;
		if (output > 10) exit(0);
	}
	if (output == 2 || output == 12)
	{
		gmrVTKExportSTL* expoter = new gmrVTKExportSTL();
		if (outfile != NULL)
		{
			expoter->SaveFile(reader->GetSkin()->GetOutputPort(), outfile);
		}
		else
			expoter->SaveFile(reader->GetSkin()->GetOutputPort(), "aaaa.stl");
		if (output > 10) exit(0);
	}
	if (output == 3 || output == 13)
	{
		gmrVTKExportVRML* expoter = new gmrVTKExportVRML();
		if (outfile != NULL)
		{
			expoter->SaveFile(render, outfile);
		}
		else
			expoter->SaveFile(render, "aaa.wrl");
		delete expoter;
		if (output > 10) exit(0);
	}
	if (output == 4 || output == 14)
	{
		gmrVTKExportX3D* expoter = new gmrVTKExportX3D();
		if (outfile != NULL)
		{
			expoter->SaveFile(render, outfile);
		}
		else
			expoter->SaveFile(render, "aaa.x3d");
		delete expoter;
		if (output > 10) exit(0);
	}

	// コールバックの登録
	render->AddCallback(vtkCommand::KeyPressEvent, MyCallback::New());

	if (1/*output == 100 || output == 101*/)
	{
		if (output == 0)
		{
			boxWidget = vtkBoxWidget::New();
			boxWidget->SetInteractor(render->GetRenderWindowInteractor());
			boxWidget->SetPlaceFactor(1.25);

			if (reader->surface_On)
			{
				boxWidget->SetProp3D(reader->GetSurfaceActor());
			}
			else
			{
				boxWidget->SetProp3D(reader->GetActor());
			}

			boxWidget->PlaceWidget();
			vtkMyCallback2 *callback = vtkMyCallback2::New();
			boxWidget->AddObserver(vtkCommand::InteractionEvent, callback);
			boxWidget->On();
		}

		if (1)
		{
			//BoxWidget2
			boxWidget2 = vtkBoxWidget::New();
			boxWidget2->SetInteractor(render->GetRenderWindowInteractor());
			boxWidget2->SetPlaceFactor(1.25);
			boxWidget2->InsideOutOn();

			if (reader->surface_On)
			{
				boxWidget2->SetProp3D(reader->GetSurfaceActor());
			}
			else
			{
				boxWidget2->SetProp3D(reader->GetActor());
			}
			boxWidget2->PlaceWidget();
			vtkMyCallback3 *callback2 = vtkMyCallback3::New();
			boxWidget2->AddObserver(vtkCommand::InteractionEvent, callback2);
			boxWidget2->On();
		}
	}

	cellpicker = vtkVolumePicker::New();
	cellpicker->SetTolerance(1.0e-6);
	cellpicker->SetVolumeOpacityIsovalue(0.1);
	render->GetRenderWindowInteractor()->SetPicker(cellpicker);

	MyCallbackPick* callback = MyCallbackPick::New();
	render->AddCallback(vtkCommand::LeftButtonPressEvent, callback);
	picker_flag = 0;
	render->DefaultRun("DICOM");

}

extern "C" void DICOM2OBJ(char* dcm_files_folderName, int flg, double isovalue, char* outfile)
{
	char* folderName;

	folderName = dcm_files_folderName;

	int f = 10 * flg;

	// DICOM スライスViewer
	fprintf(stderr, "==> convert obj!!\n");

	char outfileName[512];
	char* outfile2 = outfile;
	if (outfile)
	{
		char drive[_MAX_DRIVE];	// ドライブ名
		char dir[_MAX_DIR];		// ディレクトリ名
		char fname[_MAX_FNAME];	// ファイル名
		char ext[_MAX_EXT];		// 拡張子

		_splitpath(outfile, drive, dir, fname, ext);
		if (strcmp(".obj", ext) == 0 || strcmp(".OBJ", ext) == 0)
		{
			strcpy(outfileName, outfile);
			sprintf(outfileName, "%s%s%s", drive, dir, fname);
			outfile2 = outfileName;
		}
	}

	DICOM_3DViewer(folderName, 1 + f, -1.0, isovalue, outfile2);
	fprintf(stderr, "finish.\n");
}
extern "C" void DICOM2STL(char* dcm_files_folderName, int flg, double isovalue, char* outfile)
{
	char* folderName;

	folderName = dcm_files_folderName;

	int f = 10 * flg;

	// DICOM スライスViewer
	fprintf(stderr, "==> convert STL!!\n");
	DICOM_3DViewer(folderName, 2 + f, -1.0, isovalue, outfile);
	fprintf(stderr, "finish.\n");
}

extern "C" void DICOM2VRML(char* dcm_files_folderName, int flg, double isovalue, char* outfile)
{
	char* folderName;

	folderName = dcm_files_folderName;

	int f = 10 * flg;

	// DICOM スライスViewer
	fprintf(stderr, "==> convert vrml!!\n");
	DICOM_3DViewer(folderName, 3 + f, -1.0, isovalue, outfile);
	fprintf(stderr, "finish.\n");
}

extern "C" void DICOM2X3D(char* dcm_files_folderName, int flg, double isovalue, char* outfile)
{
	char* folderName;

	folderName = dcm_files_folderName;

	int f = 10 * flg;

	// DICOM スライスViewer
	fprintf(stderr, "==> convert x3d!!\n");
	DICOM_3DViewer(folderName, 4 + f, -1.0, isovalue, outfile);
	fprintf(stderr, "finish.\n");
}



template <class T>
inline T* readImage(const char *filename, int&x, int&y)
{
	unsigned char *data = 0;
	int nbit;
	data = stbi_load(filename, &x, &y, &nbit, 0);
	if (data == NULL)
	{
		printf("image file[%s] read error.\n", filename);
		return NULL;
	}
	//printf("height %d   width %d \n", y, x);

	T *image = new T[x*y];

	//#pragma omp parallel for
	for (int i = 0; i<y; ++i) {
		for (int j = 0; j<x; ++j) {
			if (nbit == 1)	//8bit
			{
				int pos = (i*x + j);
				image[pos] = data[pos];
			}
			if (nbit == 2)	//16bit
			{
				int pos = (i*x + j);
				image[pos] = data[pos * 2 + 0];
			}
			if (nbit == 3)	//24
			{
				int pos = (i*x + j);
				image[pos] = data[pos * 3 + 0];
			}
			if (nbit == 4)	//32
			{
				int pos = (i*x + j);
				image[pos] = data[pos * 4 + 0];
			}
		}
	}
	stbi_image_free(data);

	return image;
}

bool Polygon_mapper_enable = false;
bool Volume_mapper_enable = false;

std::vector<vtkSmartPointer<vtkPolyDataMapper>> Polygon_mapper;
vtkSmartPointer<vtkActor> image3d_to_marching_cubes(char* dirName, vtkSmartPointer<vtkImageData>& vtk_image_data, double threshold, int smooth)
{
	auto start = std::chrono::system_clock::now();
	auto end = std::chrono::system_clock::now();
	auto execution_time = end - start;

	vtkSmartPointer<vtkMarchingCubes> vtk_marching_cubes = vtkSmartPointer<vtkMarchingCubes>::New();
	vtk_marching_cubes->SetInputData(vtk_image_data);
	vtk_marching_cubes->ComputeNormalsOn();

	vtk_marching_cubes->SetValue(0, threshold);

	start = std::chrono::system_clock::now();

	vtk_marching_cubes->Update();

	end = std::chrono::system_clock::now();
	execution_time = end - start;

	std::cout << "threshold: " << threshold << std::endl;
	std::cout << "time: " << std::chrono::duration_cast<std::chrono::microseconds>(execution_time).count() / 1000.0 << " msec." << std::endl;

	vtkSmartPointer<vtkPolyData> vtk_polydata = vtkSmartPointer<vtkPolyData>::New();
	vtk_polydata = vtk_marching_cubes->GetOutput();

	std::cout << "NumberOfPolys: ";
	std::cout.imbue(std::locale(""));
	std::cout << vtk_polydata->GetNumberOfPolys() << std::endl;
	std::cout << "NumberOfPoints: " << vtk_polydata->GetNumberOfPoints() << std::endl;
	std::cout.imbue(std::locale::classic());
	std::cout << "------------------------" << std::endl;

	vtkSmartPointer<vtkDecimatePro> decimator =
		vtkDecimatePro::New();
	decimator->SetInputData(vtk_polydata);
	decimator->SetTargetReduction(0.05);
	decimator->SetPreserveTopology(1);
	decimator->Update();
	std::cout << "Decimation finished...." << std::endl;

	vtkSmartPointer<vtkSmoothPolyDataFilter> smoothFilter =
		vtkSmartPointer<vtkSmoothPolyDataFilter>::New();
	if (smooth)
	{
		smoothFilter->SetInputConnection(decimator->GetOutputPort());
		smoothFilter->SetNumberOfIterations(15);
		smoothFilter->SetRelaxationFactor(0.1);
		smoothFilter->FeatureEdgeSmoothingOff();
		smoothFilter->BoundarySmoothingOn();
		smoothFilter->Update();
	}

	// Update normals on newly smoothed polydata
	vtkSmartPointer<vtkPolyDataNormals> normalGenerator = vtkSmartPointer<vtkPolyDataNormals>::New();
	if (smooth)
	{
		normalGenerator->SetInputConnection(smoothFilter->GetOutputPort());
		normalGenerator->ComputePointNormalsOn();
		normalGenerator->ComputeCellNormalsOn();
		normalGenerator->Update();
	}
	else
	{
		normalGenerator->SetInputData(vtk_polydata);
		normalGenerator->ComputePointNormalsOn();
		normalGenerator->ComputeCellNormalsOn();
		normalGenerator->Update();
	}


	vtkSmartPointer<vtkPolyDataMapper> mapper = vtkSmartPointer<vtkPolyDataMapper>::New();
	mapper->SetInputConnection(normalGenerator->GetOutputPort());
	mapper->ScalarVisibilityOff();

	vtkSmartPointer<vtkActor> actor = vtkSmartPointer<vtkActor>::New();
	actor->SetMapper(mapper);

	Polygon_mapper.push_back(mapper);
	Polygon_mapper_enable = true;
	return actor;
}

vtkSmartPointer<vtkGPUVolumeRayCastMapper> Volume_mapper;
std::vector<_volumeColorValue> volumeColorSet;
vtkSmartPointer<vtkVolume> image3d_to_marching_cubes_vol(char* colorset, char* dirName, vtkSmartPointer<vtkImageData>& vtk_image_data)
{
	FILE* fp = fopen(colorset, "r");

	if (fp)
	{
		printf("=>%s\n", colorset);
		volumeColorSet.clear();
		char buf[256];
		while (fgets(buf, 256, fp) != NULL)
		{
			_volumeColorValue c;
			sscanf(buf, "%lf,%lf,%lf,%lf,%lf", c.x, c.x + 1, c.x + 2, c.x + 3, c.x + 4);
			volumeColorSet.push_back(c);
		}
		fclose(fp);
		for (int i = 0; i < volumeColorSet.size(); i++)
		{
			printf("%f,%f,%f,%f,%f\n", volumeColorSet[i].x[0], volumeColorSet[i].x[1], volumeColorSet[i].x[2], volumeColorSet[i].x[3], volumeColorSet[i].x[4]);
		}
	}

	vtkSmartPointer<vtkColorTransferFunction> volumeColor = vtkSmartPointer<vtkColorTransferFunction>::New();
	for (int i = 0; i < volumeColorSet.size(); ++i)
	{
		volumeColor->AddRGBPoint(volumeColorSet[i].x[0], volumeColorSet[i].x[1], volumeColorSet[i].x[2], volumeColorSet[i].x[3]);
	}
	vtkSmartPointer<vtkPiecewiseFunction> volumeScalarOpacity = vtkSmartPointer<vtkPiecewiseFunction>::New();
	for (int i = 0; i < volumeColorSet.size(); ++i)
	{
		volumeScalarOpacity->AddPoint(volumeColorSet[i].x[0], volumeColorSet[i].x[4]);
	}

	vtkSmartPointer<vtkVolumeProperty> volumeProperty = vtkSmartPointer<vtkVolumeProperty>::New();
	volumeProperty->SetColor(volumeColor);
	volumeProperty->SetScalarOpacity(volumeScalarOpacity);
	volumeProperty->SetInterpolationTypeToLinear();
	volumeProperty->ShadeOn();
	volumeProperty->SetAmbient(0.3);
	volumeProperty->SetDiffuse(0.75);
	volumeProperty->SetSpecular(0.35);

	vtkSmartPointer<vtkVolume> volume;
	volume = vtkSmartPointer<vtkVolume>::New();
	volume->SetProperty(volumeProperty);

	vtkSmartPointer<vtkGPUVolumeRayCastMapper>volumemapper = vtkSmartPointer<vtkGPUVolumeRayCastMapper>::New();
	volumemapper->SetInputData(vtk_image_data);
	volumemapper->SetSampleDistance(0.1);

	vtkSmartPointer<vtkActor> actor = vtkSmartPointer<vtkActor>::New();
	volume->SetMapper(volumemapper);

	Volume_mapper = volumemapper;
	Volume_mapper_enable = true;
	return volume;
}

vtkSmartPointer<vtkVolume> image3d_to_marching_cubes_vol0(vtkSmartPointer<vtkImageData>& vtk_image_data, double threshold)
{
	std::vector<_volumeColorValue> volumeColorSet2 = volumeColorSet;
	for (int i = 0; i < volumeColorSet2.size(); i++)
	{
		if (volumeColorSet2[i].x[0] < threshold)
		{
			volumeColorSet2[i].x[4] = 0.0;
		}
	}

	vtkSmartPointer<vtkColorTransferFunction> volumeColor = vtkSmartPointer<vtkColorTransferFunction>::New();
	for (int i = 0; i < volumeColorSet2.size(); ++i)
	{
		volumeColor->AddRGBPoint(volumeColorSet2[i].x[0], volumeColorSet2[i].x[1], volumeColorSet2[i].x[2], volumeColorSet2[i].x[3]);
	}
	vtkSmartPointer<vtkPiecewiseFunction> volumeScalarOpacity = vtkSmartPointer<vtkPiecewiseFunction>::New();
	for (int i = 0; i < volumeColorSet2.size(); ++i)
	{
		volumeScalarOpacity->AddPoint(volumeColorSet2[i].x[0], volumeColorSet2[i].x[4]);
	}



	vtkSmartPointer<vtkVolumeProperty> volumeProperty = vtkSmartPointer<vtkVolumeProperty>::New();
	volumeProperty->SetColor(volumeColor);
	volumeProperty->SetScalarOpacity(volumeScalarOpacity);
	volumeProperty->SetInterpolationTypeToLinear();
	volumeProperty->ShadeOn();
	volumeProperty->SetAmbient(0.3);
	volumeProperty->SetDiffuse(0.75);
	volumeProperty->SetSpecular(0.35);

	vtkSmartPointer<vtkVolume> volume;
	volume = vtkSmartPointer<vtkVolume>::New();
	volume->SetProperty(volumeProperty);

	vtkSmartPointer<vtkGPUVolumeRayCastMapper>volumemapper = vtkSmartPointer<vtkGPUVolumeRayCastMapper>::New();
	volumemapper->SetInputData(vtk_image_data);
	volumemapper->SetSampleDistance(0.1);

	vtkSmartPointer<vtkActor> actor = vtkSmartPointer<vtkActor>::New();
	volume->SetMapper(volumemapper);

	Volume_mapper = volumemapper;
	return volume;
}

//bool OnvtkSliderCallback_Execute = false;
class vtkSliderCallback : public vtkCommand
{
public:
	static vtkSliderCallback *New()
	{
		return new vtkSliderCallback;
	}
	virtual void Execute(vtkObject *caller, unsigned long, void*)
	{
		//if (OnvtkSliderCallback_Execute) return;
		vtkSliderWidget *sliderWidget =
			reinterpret_cast<vtkSliderWidget*>(caller);
		double threshold = static_cast<vtkSliderRepresentation *>(sliderWidget->GetRepresentation())->GetValue();

		//OnvtkSliderCallback_Execute = true;
		auto v = image3d_to_marching_cubes_vol0(*vtk_image_data_ptr, threshold);
		render->RemoveActor(*volume_actor_ptr);
		render->AddActor(v);
		volume_actor_ptr = &v;
		//OnvtkSliderCallback_Execute = false;

	}
	vtkSliderCallback() {}
	gmrVTKRender* render;
	vtkSmartPointer<vtkImageData>* vtk_image_data_ptr;
	vtkSmartPointer<vtkVolume>* volume_actor_ptr;
};

//BoxWidgetののコールバック
class vtkMyCallback4 : public gmrVTKCommand
{
public:
	static vtkMyCallback4 *New()
	{
		return new vtkMyCallback4;
	}
	virtual void Execute(vtkObject *caller, unsigned long, void*)
	{
		vtkBoxWidget *widget = reinterpret_cast<vtkBoxWidget*>(caller);
		vtkPlanes *planes = vtkPlanes::New();

		//Get the planes of the box widget and apply them to the ray cast mapper
		widget->GetPlanes(planes);

		if (Polygon_mapper_enable)
		{
			for ( int i = 0; i < Polygon_mapper.size(); i++)
			Polygon_mapper[i]->SetClippingPlanes(planes);
		}
		if (Volume_mapper_enable)
		{
			Volume_mapper->SetClippingPlanes(planes);
		}
	}
};

extern "C" int loadSliceImages(char* dir_name, char* base_name, int n_slice, int smooth, double* isovalue)
{
	if (n_slice <= 0) return -1;
	const char* voxel_raw = "voxel.raw";
	char filename[640];


	sprintf(filename, "%s\\%s%03d.bmp", dir_name, base_name, 0);
	printf("initial load:[%s]\n", filename);

	int image_width = 0;
	int image_height = 0;
	unsigned short* tmp = readImage<unsigned short>(filename, image_width, image_height);
	delete[] tmp;
	const int image_slice = n_slice;

	printf("image_width:%d image_height:%d\n", image_width, image_height);
	printf("image_slice:%d\n", image_slice);

	FILE* fp = fopen(voxel_raw, "wb");
	for (int z = 0; z < image_slice; ++z)
	{
		sprintf(filename, "%s\\%s%03d.bmp", dir_name, base_name, z);
		printf("                    \rload:[%d/%d]", (z + 1), image_slice);

		unsigned short* tmp = readImage<unsigned short>(filename, image_width, image_height);
#if 0
		for (int y = 0; y < image_height; ++y)
		{
			for (int x = 0; x < image_width; ++x)
			{
				int pos = y*image_width + x;
				fwrite(&tmp[pos], sizeof(unsigned short), 1, fp);
			}
		}
#else
		fwrite(tmp, sizeof(unsigned short), image_height*image_width, fp);
#endif
		delete[] tmp;
	}
	printf("\n");
	fclose(fp);

	const int total_voxels = image_width * image_height * image_slice;

	vtkSmartPointer<vtkImageReader> vtk_image_reader = vtkSmartPointer<vtkImageReader>::New();
	vtk_image_reader->SetDataScalarType(VTK_UNSIGNED_SHORT);
	vtk_image_reader->SetFileDimensionality(3);
	vtk_image_reader->SetDataExtent(0, image_width - 1, 0, image_height - 1, 0, image_slice - 1);
	vtk_image_reader->FileLowerLeftOn();
	//vtk_image_reader->SetDataByteOrderToBigEndian();
	vtk_image_reader->SetFileName(voxel_raw);
	vtk_image_reader->Update();

	vtkSmartPointer<vtkImageData> vtk_image_data = vtkSmartPointer<vtkImageData>::New();
	vtk_image_data->SetSpacing(1, 1, 1);
	vtk_image_data = vtk_image_reader->GetOutput();

	std::cout.imbue(std::locale(""));
	std::cout << "NumberOfPoints: " << vtk_image_data->GetNumberOfPoints() << std::endl;
	std::cout.imbue(std::locale::classic());

	double bounds[6];
	vtk_image_data->GetBounds(bounds);
	for (unsigned int i = 0; i < 6; i += 2)
	{
		double range = bounds[i + 1] - bounds[i];
		bounds[i] = bounds[i] - .1 * range;
		bounds[i + 1] = bounds[i + 1] + .1 * range;
	}

	auto start = std::chrono::system_clock::now();
	auto end = std::chrono::system_clock::now();
	auto execution_time = end - start;
	//for (int z = 0; z < image_slice; ++z) {
	//  for (int y = 0; y < image_height; ++y) {
	//    for (int x = 0; x < image_width; ++x) {
	//      const auto voxel = *(static_cast<short*>(vtk_image_data->GetScalarPointer(x, y, z)));
	//      std::cout << voxel << ", ";
	//    }
	//  }
	//}
	//std::cout << std::endl;

	const std::vector<double> thresholds{ 10.0, 100.0, 255.0 };
	const std::vector<double> opacity{ 1, 1, 1 };

	struct color
	{
		double r, g, b;
	};
	const std::vector<struct color> colors{
		{ 255.0, 202.0, 202.0 },
		{ 120.0, 37.0, 22.0 },
		{ 215.0, 215.0, 210.0 }
	};
	gmrVTKRender* render = new gmrVTKRender;
	render->InteractorStyleTrackballCamera();

	std::vector<vtkSmartPointer<vtkActor>> actors;
	if (isovalue != NULL)
	{
		for (int i = 0; i < thresholds.size()-1; i++)
		{
#if 10
			if (*isovalue >= thresholds[i] && *isovalue <= thresholds[i+1])
			{
				continue;
			}
			double threshold = *isovalue;
#else
			double threshold = thresholds[i];
#endif
			vtkSmartPointer<vtkActor>actor = image3d_to_marching_cubes(dir_name, vtk_image_data, threshold, smooth);

			actor->GetProperty()->SetDiffuseColor(colors[i].r / 255.0, colors[i].g / 255.0, colors[i].b / 255.0);
			//actor->GetProperty()->SetColor(0.2, 0.2, 0.2);
			actor->GetProperty()->SetOpacity(opacity[i]);
			actors.push_back(actor);

			render->AddActor(actor);
		}
		gmrVTKExportOBJ* expoter = new gmrVTKExportOBJ();
		expoter->SaveFile(render, "voxel.obj");
	}

	vtkSmartPointer<vtkVolume> volume_actor;
	if (isovalue == NULL)
	{
		char* colorset = ".\\bmp_volume.txt";
		volume_actor = image3d_to_marching_cubes_vol(colorset, dir_name, vtk_image_data);
		render->AddActor(volume_actor);
	}



	gmrVTKText* text1 = new gmrVTKText;
	text1->SetText("space key =>RubberBandZoom on/off");
	text1->SetPosition(20, 140);
	text1->SetSize(15);
	text1->SetColor(1.0, 0.0, 0.0);

	gmrVTKText* text2 = new gmrVTKText;
	text2->SetText("=======================================");;
	text2->SetPosition(20, 120);
	text2->SetSize(15);
	text2->SetColor(0, 1.0, 0.0);

	gmrVTKText* text3 = new gmrVTKText;
	text3->SetText("r key => resize box on/off");
	text3->SetPosition(20, 100);
	text3->SetSize(15);
	text3->SetColor(0, 1.0, 0.0);

	gmrVTKText* text4 = new gmrVTKText;
	text4->SetText("c key => cross section  box on/off");
	text4->SetPosition(20, 80);
	text4->SetSize(15);
	text4->SetColor(0, 1.0, 0.0);

	gmrVTKText* text5 = new gmrVTKText;
	text5->SetText("d key => measure on/off");
	text5->SetPosition(20, 60);
	text5->SetSize(15);
	text5->SetColor(0, 1.0, 0.0);

	gmrVTKText* text6 = new gmrVTKText;
	text6->SetText("D key => measure clear");
	text6->SetPosition(20, 40);
	text6->SetSize(15);
	text6->SetColor(0, 1.0, 0.0);

	gmrVTKText* text7 = new gmrVTKText;
	text7->SetText("m key => measure(2D) on/off");
	text7->SetPosition(20, 20);
	text7->SetSize(15);
	text7->SetColor(0, 1.0, 0.0);

	gmrVTKText* text8 = new gmrVTKText;
	text8->SetText("b key => box(3D-scaling)  box on/off");
	text8->SetPosition(20, 0);
	text8->SetSize(15);
	text8->SetColor(0, 1.0, 0.0);



	render->AddActor(text1->GetActor());
	render->AddActor(text2->GetActor());
	render->AddActor(text3->GetActor());
	render->AddActor(text4->GetActor());
	render->AddActor(text5->GetActor());
	render->AddActor(text6->GetActor());
	render->AddActor(text7->GetActor());
	render->AddActor(text8->GetActor());


	if (Volume_mapper_enable)
	{
		pointPlacer = vtkSmartPointer<vtkPolyDataPointPlacer>::New();
		pointPlacer->AddProp(volume_actor);

		handleRep = vtkSmartPointer<vtkPointHandleRepresentation3D>::New();
		handleRep->SetHandleSize(50);
		handleRep->GetProperty()->SetColor(1., 0., 0.);
		handleRep->SetPointPlacer(pointPlacer);

		distanceRep = vtkSmartPointer<vtkDistanceRepresentation2D>::New();
		distanceRep->SetHandleRepresentation(handleRep);
		distanceRep->SetLabelFormat("%-#6.3g mm");

		distanceWidget = vtkDistanceWidget::New();
		distanceWidget->SetRepresentation(distanceRep);
		distanceWidget->SetInteractor(render->GetRenderWindowInteractor());
	}

	// コールバックの登録
	render->AddCallback(vtkCommand::KeyPressEvent, MyCallback::New());

	if (1/*output == 100 || output == 101*/)
	{
		if (1)
		{
			boxWidget = vtkBoxWidget::New();
			boxWidget->SetInteractor(render->GetRenderWindowInteractor());
			boxWidget->SetPlaceFactor(1.25);

			if (Polygon_mapper_enable)
			{
				for (int i = 0; i < actors.size(); i++)
					boxWidget->SetProp3D(actors[i]);
			}
			if (Volume_mapper_enable)
			{
				boxWidget->SetProp3D(volume_actor);
			}

			boxWidget->PlaceWidget();
			vtkMyCallback2 *callback = vtkMyCallback2::New();
			boxWidget->AddObserver(vtkCommand::InteractionEvent, callback);
			boxWidget->On();
		}

		if (1)
		{
			//BoxWidget2
			boxWidget2 = vtkBoxWidget::New();
			boxWidget2->SetInteractor(render->GetRenderWindowInteractor());
			boxWidget2->SetPlaceFactor(1.25);
			boxWidget2->InsideOutOn();

			if (Polygon_mapper_enable)
			{
				for (int i = 0; i < actors.size(); i++)
					boxWidget2->SetProp3D(actors[i]);
			}
			if (Volume_mapper_enable)
			{
				boxWidget2->SetProp3D(volume_actor);
			}
			boxWidget2->PlaceWidget();
			vtkMyCallback4 *callback2 = vtkMyCallback4::New();
			boxWidget2->AddObserver(vtkCommand::InteractionEvent, callback2);
			boxWidget2->On();
		}
	}

	cellpicker = vtkVolumePicker::New();
	cellpicker->SetTolerance(1.0e-6);
	cellpicker->SetVolumeOpacityIsovalue(0.1);
	render->GetRenderWindowInteractor()->SetPicker(cellpicker);

	MyCallbackPick* callback = MyCallbackPick::New();
	render->AddCallback(vtkCommand::LeftButtonPressEvent, callback);
	picker_flag = 0;


#if 10
	if (Volume_mapper_enable)
	{
		//vtkSmartPointer<vtkSliderRepresentation3D> sliderRep =
		//	vtkSmartPointer<vtkSliderRepresentation3D>::New();

		vtkSmartPointer<vtkSliderRepresentation2D> sliderRep =
			vtkSmartPointer<vtkSliderRepresentation2D>::New();

		sliderRep->SetMinimumValue(0.0);
		sliderRep->SetMaximumValue(255.0);
		sliderRep->SetValue(0.0);
		sliderRep->SetTitleText("test");
		//sliderRep->GetPoint1Coordinate()->SetCoordinateSystemToWorld();
		//sliderRep->GetPoint1Coordinate()->SetValue(-4, 6, 0);
		//sliderRep->GetPoint2Coordinate()->SetCoordinateSystemToWorld();
		//sliderRep->GetPoint2Coordinate()->SetValue(4, 6, 0);
		//sliderRep->GetPoint1Coordinate()->SetCoordinateSystemToNormalizedViewport();
		//sliderRep->GetPoint1Coordinate()->SetValue(20, 160, 0);
		//sliderRep->GetPoint2Coordinate()->SetCoordinateSystemToNormalizedViewport();
		//sliderRep->GetPoint2Coordinate()->SetValue(120, 160, 0);
		//sliderRep->SetSliderLength(0.075);
		//sliderRep->SetSliderWidth(0.05);
		//sliderRep->SetEndCapLength(0.05);

		// Set color properties:
		// Change the color of the knob that slides
		sliderRep->GetSliderProperty()->SetColor(1, 0, 0);
		// Change the color of the text indicating what the slider controls
		sliderRep->GetTitleProperty()->SetColor(1, 1, 1);
		// Change the color of the text displaying the value
		sliderRep->GetLabelProperty()->SetColor(1, 1, 1);
		// Change the color of the knob when the mouse is held on it
		sliderRep->GetSelectedProperty()->SetColor(0, 1, 0);//green
		// Change the color of the bar
		sliderRep->GetTubeProperty()->SetColor(1, 1, 0);//yellow
		// Change the color of the ends of the bar
		sliderRep->GetCapProperty()->SetColor(1, 1, 0);//yellow

		sliderRep->GetPoint1Coordinate()->SetCoordinateSystemToDisplay();
		sliderRep->GetPoint1Coordinate()->SetValue(20, 460, 0);
		sliderRep->GetPoint2Coordinate()->SetCoordinateSystemToDisplay();
		sliderRep->GetPoint2Coordinate()->SetValue(220, 460, 0);


		vtkSmartPointer<vtkSliderWidget> sliderWidget =
			vtkSmartPointer<vtkSliderWidget>::New();
		sliderWidget->SetInteractor(render->GetRenderWindowInteractor());
		sliderWidget->SetRepresentation(sliderRep);
		sliderWidget->SetAnimationModeToAnimate();
		sliderWidget->EnabledOn();

		vtkSmartPointer<vtkSliderCallback> slider_callback =
			vtkSmartPointer<vtkSliderCallback>::New();

		slider_callback->render = render;
		slider_callback->vtk_image_data_ptr = &vtk_image_data;
		slider_callback->volume_actor_ptr = &volume_actor;
		sliderWidget->AddObserver(vtkCommand::InteractionEvent, slider_callback);
	}
#endif

	render->SetBackgroundColor(0, 0, 0);
	render->DefaultRun();
	//delete expoter;

	return 0;
}
