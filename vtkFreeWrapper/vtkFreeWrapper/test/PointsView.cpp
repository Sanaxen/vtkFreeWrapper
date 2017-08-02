/************************************************************
*
* vtkWrapperLIBを使った簡単なサンプルプログラム
*
* 点群表示
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


void PointsView ()
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
	
	gmrVTKText* text2d = new gmrVTKText;
	text2d->SetText("AAAA");
	text2d->SetColor(0.0, 1.0, 0.0);
	text2d->SetSize(20);
	text2d->SetPosition(50, 50);
	render->AddActor(text2d->GetActor());
	//text2d->GetActor()->VisibilityOff();

	//render->DefaultRun();
	for (int i = 0; i < 360; ++i)
	{
		// Render the image and rotate the active camera by one degree
		render->Run();
		render->GetRenderer()->GetActiveCamera()->Azimuth(1);
		render->RemoveActor(text->GetActor());
		text->SetOrientation(i, 0, 0);
		render->AddActor( text->GetActor());
		if (i % 20 == 0) text2d->GetActor()->VisibilityOff();
		else text2d->GetActor()->VisibilityOn();

	}

	delete points;
}
