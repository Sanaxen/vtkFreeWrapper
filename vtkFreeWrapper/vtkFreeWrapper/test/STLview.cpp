/*
 * VTKを簡単に（？）使うための簡単クラスライブラリの使用例
 * Copyright (c) Sanaxen
 *
 */
#include "gmrVTKRender.hpp"
#include "gmrVTKImport.hpp"

#include "gmrVTKScalarBar.hpp"

void STLView ()
{
	printf("STLView\n");
	gmrVTKImportSTL* polygon = new gmrVTKImportSTL("data\\bunny.stl");

	gmrVTKRender* render = new gmrVTKRender;

	render->InteractorStyleTrackballCamera();
	render->AddActor(polygon->GetActor());

	//render->DefaultRun();

	gmrVTKScalaBar* scalarBar = new gmrVTKScalaBar;
	scalarBar->SetScalarMinMax(0, 360);
	for (int i = 0; i < 360; i += 1)
	{
		// Render the image and rotate the active camera by one degree
		render->Run();
		render->GetRenderer()->GetActiveCamera()->Azimuth(1);
		render->GetRenderer()->GetActiveCamera()->Roll(1);

		double rgb[3];
		scalarBar->GetLookupTable()->GetColor((double)i, rgb);
		polygon->SetDiffuseColor(rgb[0], rgb[1], rgb[2]);

		render->RemoveActor(polygon->GetActor());
		render->AddActor(polygon->GetActor());
	}

}
