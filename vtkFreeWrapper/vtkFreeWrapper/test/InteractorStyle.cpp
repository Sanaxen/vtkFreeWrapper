/*
 * VTKを簡単に（？）使うための簡単クラスライブラリの使用例
 * Copyright (c) Sanaxen
 *
 */
/************************************************************
*
* vtkWrapperLIBを使った簡単なサンプルプログラム
*
* RubberBandによる拡大（マウスインタラクション）の例
*************************************************************/
/*
 * VTKを簡単に（？）使うための簡単クラスライブラリの使用例
 * Copyright (c) Sanaxen
 *
 */
#include "gmrVTKRender.hpp"
#include "gmrVTKImport.hpp"

#include "gmrVTKCommand.hpp"
#include "gmrVTKText.hpp"

#include <string>

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


void InteractorStyle()
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

	gmrVTKImportSTL* polygon = new gmrVTKImportSTL("data\\bunny.stl");

	gmrVTKRender* render = new gmrVTKRender;

	render->AddActor(text1->GetActor());
	render->AddActor(text2->GetActor());
	render->AddActor(polygon->GetActor());

	// コールバックの登録
	render->AddCallback(vtkCommand::KeyPressEvent, MyCallback::New());
	render->DefaultRun();
}
