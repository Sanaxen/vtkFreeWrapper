/*
 * VTK���ȒP�Ɂi�H�j�g�����߂̊ȒP�N���X���C�u�����̎g�p��
 * Copyright (c) Sanaxen
 *
 */
#include "gmrVTKRender.hpp"
#include "gmrVTKImport.hpp"

// 3D sample �f�[�^
// PLY�`�� http://www-graphics.stanford.edu/data/3Dscanrep/

void PLYView ()
{
	printf("PLYView\n");
	gmrVTKImportPLY* polygon = new gmrVTKImportPLY("data\\dragon_vrip.ply");

	gmrVTKRender* render = new gmrVTKRender;

	render->AddActor(polygon->GetActor());
	render->InteractorStyleTrackballCamera();

	render->DefaultRun();
}
