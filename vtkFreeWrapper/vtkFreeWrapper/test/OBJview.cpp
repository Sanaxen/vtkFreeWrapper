/*
 * VTK���ȒP�Ɂi�H�j�g�����߂̊ȒP�N���X���C�u�����̎g�p��
 * Copyright (c) Sanaxen
 *
 */
#include "gmrVTKRender.hpp"
#include "gmrVTKImport.hpp"

// 3D sample �f�[�^
// OBJ�`�� http://www.farfieldtechnology.com/download/
void OBJView ()
{
	printf("OBJView\n");
	gmrVTKImportOBJ* polygon = new gmrVTKImportOBJ("data\\dragon_vrip.obj");

	gmrVTKRender* render = new gmrVTKRender;

	render->AddActor(polygon->GetActor());
	render->InteractorStyleTrackballCamera();

	render->DefaultRun();
}
