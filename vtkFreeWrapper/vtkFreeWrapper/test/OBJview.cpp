/*
 * VTKを簡単に（？）使うための簡単クラスライブラリの使用例
 * Copyright (c) Sanaxen
 *
 */
#include "gmrVTKRender.hpp"
#include "gmrVTKImport.hpp"

// 3D sample データ
// OBJ形式 http://www.farfieldtechnology.com/download/
void OBJView ()
{
	printf("OBJView\n");
	gmrVTKImportOBJ* polygon = new gmrVTKImportOBJ("data\\dragon_vrip.obj");

	gmrVTKRender* render = new gmrVTKRender;

	render->AddActor(polygon->GetActor());
	render->InteractorStyleTrackballCamera();

	render->DefaultRun();
}
