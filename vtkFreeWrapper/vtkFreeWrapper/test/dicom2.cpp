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

#include "vtkBoxWidget.h"
#include "vtkTransform.h"

#include <string>

// DICOM sample image sets
// http://149.142.216.30/DICOM_FILES/Index.html

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

 void dicom2(char* folderName, int vr)
 {
 	gmrVTKText* text1 = new gmrVTKText;
	text1->SetText("space key =>RubberBandZoom");
	text1->SetPosition(20,400);
	text1->SetSize(20);
	text1->SetColor(1.0,0.0,0.0);

	gmrVTKText* text2 = new gmrVTKText;
	text2->SetText("no space key => default");
	text2->SetPosition(20,360);
	text2->SetSize(20);
	text2->SetColor(0,1.0,0.0);

 	gmrVTKRender* render = new gmrVTKRender;
    gmrVTKDICOM *reader = new gmrVTKDICOM;
    
//    reader->SetDirectoryName("data\\PANORAMIX\\Abdomen 1ABD_PEL_AAA\\Abd-Pel w-c  3.0  B30f");
//    reader->SetDirectoryName("data");
    reader->SetDirectoryName(folderName);
    reader->LoadImageData();

	render->AddActor(text1->GetActor());
	render->AddActor(text2->GetActor());
	render->AddActor( reader->GetActor());

	gmrVTKOutline *outlineData = new gmrVTKOutline(NULL);
	outlineData->GetOutlineFilter()->SetInputConnection(reader->GetDICOMImage()->GetOutputPort());
	render->AddActor( outlineData->GetActor());

	if (vr)
	{
		//render->GetRenderer()->AddViewProp(reader->volume);
		render->AddActor(reader->GetVolume());
	}

	render->SetBackgroundColor( 0.1, 0.2, 0.4 );

	// コールバックの登録
	render->AddCallback(vtkCommand::KeyPressEvent, MyCallback::New());

	if (!vr)
	{
		//BoxWidget
		vtkBoxWidget *boxWidget = vtkBoxWidget::New();
		boxWidget->SetInteractor(render->GetRenderWindowInteractor());
		boxWidget->SetPlaceFactor(1.25);

		boxWidget->SetProp3D(reader->GetActor());
		boxWidget->PlaceWidget();
		vtkMyCallback2 *callback = vtkMyCallback2::New();
		boxWidget->AddObserver(vtkCommand::InteractionEvent, callback);
		boxWidget->On();
	}
	render->DefaultRun();
	
}
