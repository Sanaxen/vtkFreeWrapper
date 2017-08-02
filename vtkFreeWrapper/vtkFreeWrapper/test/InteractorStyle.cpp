/*
 * VTK���ȒP�Ɂi�H�j�g�����߂̊ȒP�N���X���C�u�����̎g�p��
 * Copyright (c) Sanaxen
 *
 */
/************************************************************
*
* vtkWrapperLIB���g�����ȒP�ȃT���v���v���O����
*
* RubberBand�ɂ��g��i�}�E�X�C���^���N�V�����j�̗�
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

	// �R�[���o�b�N�̓o�^
	render->AddCallback(vtkCommand::KeyPressEvent, MyCallback::New());
	render->DefaultRun();
}
