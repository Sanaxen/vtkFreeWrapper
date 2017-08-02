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

#include <string>
// DICOM sample image sets
// http://149.142.216.30/DICOM_FILES/Index.html

extern "C" void DICOM_SliceViewer(char* folderName, int capture)
{
    gmrVTKDICOM *reader = new gmrVTKDICOM;
    
//    reader->SetDirectoryName("data\\PANORAMIX\\Abdomen 1ABD_PEL_AAA\\Abd-Pel w-c  3.0  B30f");
    reader->SetDirectoryName(folderName);
    reader->LoadImageData();

	if ( capture )
	{
		reader->GetImageViewer()->GetRenderWindow()->SetOffScreenRendering(1);
	}

    int znum = reader->GetZnum();

	for (int i=0;i<=znum;i++)
    {
		gmrVTKCaptureBMP* Capture = NULL;
		if ( capture )
		{
			Capture = new gmrVTKCaptureBMP;
			Capture->SetInput(reader->GetImageViewer());
			Capture->SetFileName("Capture");
		}

		reader->ViewerZSlice(i, 400, 128);
		
		if ( capture )
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

vtkBoxWidget *boxWidget = 0;
vtkBoxWidget *boxWidget2 = 0;
////////////////////////////////////////////////////////////////////////////////////////
// KeyPressEventを拾うためのコールバック
class MyCallback : public gmrVTKCommand
{
public:
        MyCallback() {;};

        static MyCallback *New() {
			return new MyCallback; 
		}

        virtual void Execute(vtkObject *caller, unsigned long eventId, void*)
		{
			vtkRenderWindowInteractor *iren =
					reinterpret_cast<vtkRenderWindowInteractor*>(caller);

			// スペース・キーが押されたらRubberBandZoomにする
			char* key = iren->GetKeySym();
			if ( std::string(key) == "space" )
			{
				this->GetRenderer()->InteractorStyleRubberBandZoom();
			}else{
				this->GetRenderer()->InteractorStyleTrackballCamera();
			}

			if ( std::string(key) == "b" && boxWidget)
			{
				if ( boxWidget->GetEnabled() )
				{
					boxWidget->Off();
				}else
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
    { return new vtkMyCallback2; }
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

extern "C" void DICOM_3DViewer(char* folderName, int output, double sample_dist, double isovalue)
 {
 	gmrVTKText* text1 = new gmrVTKText;
	text1->SetText("space key =>RubberBandZoom");
	text1->SetPosition(20,400);
	text1->SetSize(15);
	text1->SetColor(1.0,0.0,0.0);

	gmrVTKText* text2 = new gmrVTKText;
	text2->SetText("no space key => default");
	text2->SetPosition(20,380);
	text2->SetSize(15);
	text2->SetColor(0,1.0,0.0);

	gmrVTKText* text3 = new gmrVTKText;
	text3->SetText("r key => resize box on/off");
	text3->SetPosition(20,360);
	text3->SetSize(15);
	text3->SetColor(0,1.0,0.0);

	gmrVTKText* text4= new gmrVTKText;
	text4->SetText("c key => cross section  box on/off");
	text4->SetPosition(20, 340);
	text4->SetSize(15);
	text4->SetColor(0, 1.0, 0.0);

	gmrVTKText* text5 = new gmrVTKText;
	text5->SetText("m key => measure on/off");
	text5->SetPosition(20, 320);
	text5->SetSize(15);
	text5->SetColor(0, 1.0, 0.0);

	gmrVTKRender* render;
#if 10
	render = new gmrVTKRender;
#else
	int offscreen = 1;
	if ( output )
	{
		render = new gmrVTKRender(offscreen);
	}else{
		render = new gmrVTKRender;
	}
#endif
    gmrVTKDICOM *reader = new gmrVTKDICOM;
	if (sample_dist > 0.0)
	{
		reader->SampleDistance() = sample_dist;
	}
	if (isovalue > -1.0E-8)
	{
		reader->surface_On = 1;
		reader->IsoValue() = isovalue;
	}
    
	char colorset[256];
	sprintf(colorset, "color.def");
	FILE* fp = fopen(colorset, "r");
	if (fp)
	{
		printf("load color.def\n");
		char buf[256];
		if (fgets(buf, 256, fp) != NULL)
		{
			strcpy(colorset, buf);
			if (colorset[strlen(colorset) - 1] == '\n')
			{
				colorset[strlen(colorset) - 1] = '\0';
			}
		}
		fclose(fp);

		fp = fopen(colorset, "r");
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

	render->AddActor(text1->GetActor());
	render->AddActor(text2->GetActor());
	render->AddActor(text3->GetActor());
	render->AddActor(text4->GetActor());
	render->AddActor(text5->GetActor());

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

	if ( output == 100 )
	{
		render->AddActor( reader->GetVolume());
		if (reader->surface_On)
		{
			render->AddActor(reader->GetSurfaceActor());
		}
	}
	//render->GetRenderer()->SetActiveCamera(camera);
	//render->GetRenderer()->ResetCamera();

	if ( output == 100 )
	{
		/* empty */
	}else
	{
		
		if (reader->surface_On)
		{
			reader->GetSurfaceActor()->GetProperty()->SetColor(240. / 255., 217. / 255., 202. / 255.);
			reader->GetSurfaceActor()->GetProperty()->SetSpecular(0.2);
			
			if (reader->IsoValue() > 50.0)
			{
				reader->GetSurfaceActor()->GetProperty()->SetColor(227. / 255., 66.0 / 255., 111. / 255.);
			}
			if (reader->IsoValue() > 100.0)
			{
				reader->GetSurfaceActor()->GetProperty()->SetColor(223. / 255., 135. / 255., 113. / 255.);
			}
			if (reader->IsoValue() > 200.0)
			{
				reader->GetSurfaceActor()->GetProperty()->SetColor(1, 1, 1);
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
	render->SetBackgroundColor( 0.004, 0.004, 0.004 );
	render->GetRenderWindow()->SetWindowName("MRI viewer");

	if ( output== 1 || output == 11 )
	{
		gmrVTKExportOBJ* expoter = new gmrVTKExportOBJ();
		expoter->SaveFile(render, "aaa");
		delete expoter;
		if ( output > 10 ) exit(0);
	}
	if ( output== 2 || output == 12 )
	{
		gmrVTKExportSTL* expoter = new gmrVTKExportSTL();
		expoter->SaveFile(reader->GetSkin()->GetOutputPort(), "aaaa.stl");
		if ( output > 10 ) exit(0);
	}
	if ( output== 3 || output == 13 )
	{
		gmrVTKExportVRML* expoter = new gmrVTKExportVRML();
		expoter->SaveFile(render, "aaa.wrl");
		delete expoter;
		if ( output > 10 ) exit(0);
	}
	if ( output== 4 || output == 14 )
	{
		gmrVTKExportX3D* expoter = new gmrVTKExportX3D();
		expoter->SaveFile(render, "aaa.x3d");
		delete expoter;
		if ( output > 10 ) exit(0);
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
	render->DefaultRun();
	
}

 extern "C" void DICOM2OBJ(char* dcm_files_folderName, int flg, double isovalue)
 {
	char* folderName;

	folderName = dcm_files_folderName;

	int f = 10*flg;

	// DICOM スライスViewer
	fprintf(stderr, "==> convert obj!!\n");
	DICOM_3DViewer(folderName, 1+f, -1.0, isovalue);
	fprintf(stderr, "finish.\n");
}
 extern "C" void DICOM2STL(char* dcm_files_folderName, int flg, double isovalue)
 {
	char* folderName;

	folderName = dcm_files_folderName;

	int f = 10*flg;

	// DICOM スライスViewer
	fprintf(stderr, "==> convert STL!!\n");
	DICOM_3DViewer(folderName, 2+f, -1.0, isovalue);
	fprintf(stderr, "finish.\n");
}

 extern "C" void DICOM2VRML(char* dcm_files_folderName, int flg, double isovalue)
{
	char* folderName;

	folderName = dcm_files_folderName;

	int f = 10*flg;

	// DICOM スライスViewer
	fprintf(stderr, "==> convert vrml!!\n");
	DICOM_3DViewer(folderName, 3+f, -1.0, isovalue);
	fprintf(stderr, "finish.\n");
}

 extern "C" void DICOM2X3D(char* dcm_files_folderName, int flg, double isovalue)
 {
	char* folderName;

	folderName = dcm_files_folderName;

	int f = 10*flg;

	// DICOM スライスViewer
	fprintf(stderr, "==> convert x3d!!\n");
	DICOM_3DViewer(folderName, 4+f, -1.0, isovalue);
	fprintf(stderr, "finish.\n");
}
