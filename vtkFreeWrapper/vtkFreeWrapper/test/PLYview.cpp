/*
 * VTKを簡単に（？）使うための簡単クラスライブラリの使用例
 * Copyright (c) Sanaxen
 *
 */
#include "gmrVTKRender.hpp"
#include "gmrVTKImport.hpp"

// 3D sample データ
// PLY形式 http://www-graphics.stanford.edu/data/3Dscanrep/

void PLYView ()
{
	printf("PLYView\n");
	gmrVTKImportPLY* polygon = new gmrVTKImportPLY("data\\dragon_vrip.ply");

	gmrVTKRender* render = new gmrVTKRender;

	render->AddActor(polygon->GetActor());
	render->InteractorStyleTrackballCamera();

	render->DefaultRun();
}
