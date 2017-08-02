/*
 * VTK���ȒP�Ɂi�H�j�g�����߂̊ȒP�N���X���C�u�����̎g�p��
 * Copyright (c) Sanaxen
 *
 */
/************************************************************
*
* vtkWrapperLIB���g�����ȒP�ȃT���v���v���O����
*
* BoxWidget�̗�
*************************************************************/
/*
 * VTK���ȒP�Ɂi�H�j�g�����߂̊ȒP�N���X���C�u�����̎g�p��
 * Copyright (c) Sanaxen
 *
 */
#include "gmrVTKRender.hpp"
#include "gmrVTKImport.hpp"

#include "gmrVTKCommand.hpp"
#include "gmrVTKText.hpp"

#include "vtkBoxWidget.h"
#include "vtkTransform.h"

#include <string>

// KeyPressEvent���E�����߂̃R�[���o�b�N
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

			// �X�y�[�X�E�L�[�������ꂽ��RubberBandZoom�ɂ���
			char* key = iren->GetKeySym();
			if ( std::string(key) == "space" )
			{
				this->GetRenderer()->InteractorStyleRubberBandZoom();
			}else{
				this->GetRenderer()->InteractorStyleTrackballCamera();
			}
		}
};


//BoxWidget�̂̃R�[���o�b�N
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

void BoxWidget()
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

	gmrVTKText* text3 = new gmrVTKText;
	text3->SetText("i key to bring a 3D widget");
	text3->SetPosition(20,320);
	text3->SetSize(20);
	text3->SetColor(0,1.0,1.0);

	gmrVTKImportSTL* polygon = new gmrVTKImportSTL("data\\bunny.stl");

	gmrVTKRender* render = new gmrVTKRender;

	render->AddActor(text1->GetActor());
	render->AddActor(text2->GetActor());
	render->AddActor(text3->GetActor());
	render->AddActor(polygon->GetActor());
	render->SetBackgroundColor( 0.1, 0.2, 0.4 );


	// �R�[���o�b�N�̓o�^
	render->AddCallback(vtkCommand::KeyPressEvent, MyCallback::New());

	//BoxWidget�̗�
	vtkBoxWidget *boxWidget = vtkBoxWidget::New();
	boxWidget->SetInteractor(render->GetRenderWindowInteractor());
	boxWidget->SetPlaceFactor(1.25);
	
	boxWidget->SetProp3D(polygon->GetActor());
	boxWidget->PlaceWidget();
	vtkMyCallback2 *callback = vtkMyCallback2::New();
	boxWidget->AddObserver(vtkCommand::InteractionEvent, callback);
	boxWidget->On();
	//////////////////////////////////////////////////////////////////////

	render->DefaultRun();
}
