/************************************************************
*
* vtkWrapperLIBを使った簡単なサンプルプログラム
*
* ポリライン表示
*************************************************************/
/*
 * VTKを簡単に（？）使うための簡単クラスライブラリの使用例
 * Copyright (c) Sanaxen
 *
 */
#include "gmrVTKPolyline.hpp"
#include "gmrVTKRender.hpp"

void PolylineView ()
{
	gmrVTKPolyline* poly = new gmrVTKPolyline;

	poly->SetSize(3);
	poly->SetDiffuseColor(0.2, 0.4, 0.8);


	double p[3];
	int n = 1000;

	double* scalar = new double[n];
	for ( int i = 0; i < n; i++){
		p[0] = (double)sin(5.0*3.14*i/n);
		p[1] = (double)cos(5.0*3.14*i/n);
		p[2] = (double)5.0*cos(1.0*i/n);
		poly->SetPoint(p);
		
		scalar[i] = (double)i;

	}
	poly->SetScalar(scalar);
	delete [] scalar;


	// -- render both of the objects --
	gmrVTKRender* render = new gmrVTKRender;

	render->AddActor(poly->GetActor());

	render->DefaultRun();
}
