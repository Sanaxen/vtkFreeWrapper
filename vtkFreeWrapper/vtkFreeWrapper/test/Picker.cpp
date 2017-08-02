/************************************************************
*
* vtkWrapperLIBを使った簡単なサンプルプログラム
*
* 点群表示（ピックを使用 ピックされたActorを削除します）
*************************************************************/
/*
 * VTKを簡単に（？）使うための簡単クラスライブラリの使用例
 * Copyright (c) Sanaxen
 *
 */
#include "gmrVTKPoints.hpp"
#include "gmrVTKRender.hpp"
#include "gmrVTKScalarBar.hpp"

#include "gmrVTKText.hpp"
#include "gmrVTKPicker.hpp"
#include <stdlib.h>

// コールバック
class MyCallbackTest : public gmrVTKCommand
{
	char buf[256];
	gmrVTKText* text;

public:
        MyCallbackTest() { text = NULL;};

        static MyCallbackTest *New() {
			return new MyCallbackTest;; 
		}

        virtual void Execute(vtkObject *caller, unsigned long eventId, void*)
		{
			vtkRenderWindowInteractor *iren =
					reinterpret_cast<vtkRenderWindowInteractor*>(caller);

			// Window Position
			double x = iren->GetEventPosition()[0];
			double y = iren->GetEventPosition()[1];

			vtkPicker * picker = this->GetPicker()->GetPicker();
			int succed =  picker->Pick(x, y, 0, this->GetRenderer()->GetRenderer());
			int pointId = ((vtkPointPicker *)picker)->GetPointId();
			
			// 3D Positon
			double* wpos = picker->GetPickPosition();
			double* pos = picker->GetSelectionPoint();
			
			sprintf(buf, "X=%f Y=%f Z=%f (%d,%d)", wpos[0], wpos[1], wpos[2], (int)(pos[0]), (int)(pos[1]));
			
			if ( text == NULL ) text = new gmrVTKText;
			else{
				this->GetRenderer()->RemoveActor(text->GetActor());
			}
			text->SetText(buf);
			text->SetPosition(5,400);
			text->SetSize(13);
			if ( succed ) text->SetColor(0,0,1);
			else text->SetColor(1,0,0);
			this->GetRenderer()->AddActor(text->GetActor());
		}
};

void Picker ()
{
	gmrVTKPoints* points = new gmrVTKPoints;
	double p[3];
	points->SetSize(3);

	gmrVTKRender* render = new gmrVTKRender;

	//
	// Add a Color Bar
	gmrVTKScalaBar *colorBar = new gmrVTKScalaBar;
	colorBar->Vertical();
	colorBar->LabelTextColor(0.9, 0.1, 0.1);
	colorBar->TitleTextColor(0.1, 0.1, 0.9);
	colorBar->SetTitle( "level" );

	colorBar->SetWidthPositionFactor(0.8);


	double* scalar = new double[100];
	for ( int i = 0; i < 100; i++){
		p[0] = (double)i;
		p[1] = (double)i*2.0;
		p[2] = (double)i*3.0;
		points->SetPoint(p);
		scalar[i] = (double)i;
	}
	points->SetScalar(scalar);
	delete [] scalar;


	render->AddActor(colorBar->GetActor());
	render->AddActor(points->GetActor());

	gmrVTKText3D* text = new gmrVTKText3D;
	text->SetText("Points!!");
	text->SetSize(50, 50, 50);
	text->SetColor(1, 1, 1);
	text->SetPosition(50, 100, 150);
	render->AddActor( text->GetActor());
	
#if 0
	gmrVTKWorldPointPicker* wldpicker = new gmrVTKWorldPointPicker(render);
	render->SetPiker(wldpicker);
	render->PickerOn();
	render->DefaultRun();
	render->PickerOff();
	delete wldpicker;
#endif

	// PickしたActorを削除する
	gmrVTKText* text1 = new gmrVTKText;
	text1->SetText("Pick =>Remove Actor!!");
	text1->SetPosition(20,400);
	text1->SetSize(20);
	render->AddActor( text1->GetActor());

	gmrVTKCellPicker* cellpicker = new gmrVTKCellPicker(render);
	render->SetPiker(cellpicker);
	render->PickerOn();
	render->DefaultRun();
	render->PickerOff();

	delete cellpicker;
	//////////////////////////////////////////////////////////////////
	render->RemoveActor(text1->GetActor());
	render->AddActor(points->GetActor());
	render->AddActor(text->GetActor());

	vtkPointPicker* pointpicker = vtkPointPicker::New();
	gmrVTKPicker* picker = new gmrVTKPicker;

	MyCallbackTest* callback = MyCallbackTest::New();
	picker->SetCondition(render, pointpicker, callback);
	render->AddCallback(vtkCommand::LeftButtonPressEvent, callback);
	render->PickerOn();
	render->DefaultRun();
	render->PickerOff();

	pointpicker->Delete();
	callback->Delete();;

	delete picker;
	delete render;
	delete points;
}
