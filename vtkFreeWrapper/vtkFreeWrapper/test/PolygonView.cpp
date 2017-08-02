/************************************************************
*
* vtkWrapperLIBを使った簡単なサンプルプログラム
*
* ポリゴン表示
*************************************************************/
/*
 * VTKを簡単に（？）使うための簡単クラスライブラリの使用例
 * Copyright (c) Sanaxen
 *
 */

#include "gmrVTKPolygon.hpp"
#include "gmrVTKOutline.hpp"
#include "gmrVTKRender.hpp"
#include "gmrVTKScalarBar.hpp"
#include "gmrVTKAxes.hpp"
#include "gmrVTKCapture.hpp"
#include "gmrVTKText.hpp"
#include "gmrVTKUtil.hpp"

void PolygonView ()
{

	gmrVTKPolygon* polygon = new gmrVTKPolygon;

	FILE *fp = fopen("data\\srfrecn.ply2", "r");
	char buf[256];
	int	vtxnum;
	int	trinum;

	fgets(buf, 256, fp);
	sscanf(buf, "%d", &vtxnum );

	fgets(buf, 256, fp);
	sscanf(buf, "%d", &trinum );
	double vtx[3];
	double* scalar;

	// 頂点数を設定
	polygon->SetVertexNum(vtxnum);
	scalar = new double [vtxnum];
	int i;

	//頂点の読み込みと座標値の重心
	double c[3]={0,0,0};
	for ( i = 0; i < vtxnum; i++ ){
		fgets(buf, 256, fp);
		sscanf(buf, "%lf %lf %lf", vtx, vtx+1, vtx+2);
		polygon->SetVertex(i, vtx);
		c[0] += vtx[0];
		c[1] += vtx[1];
		c[2] += vtx[2];
	}
	// 重心を求める
	c[0] /= (double)vtxnum;
	c[1] /= (double)vtxnum;
	c[2] /= (double)vtxnum;

	// 各頂点と重心までの距離をスカラーに割り当てる
	double rmin = 9999999999999;
	double rmax = -9999999999999;
	for ( i = 0; i < vtxnum; i++ ){
		polygon->GetVertex(i, vtx);
		scalar[i] = sqrt((c[0]-vtx[0])*(c[0]-vtx[0])+(c[1]-vtx[1])*(c[1]-vtx[1])+(c[2]-vtx[2])*(c[2]-vtx[2]));
		if ( rmin < scalar[i] ) rmin = scalar[i]; 
		if ( rmax > scalar[i] ) rmax = scalar[i]; 
	}

	// ファセットの読み込み
	int	iid[3];
	int dmy;
	for ( i = 0; i < trinum; i++ ){
		fgets(buf, 256, fp);
		sscanf(buf, "%d %d %d %d", &dmy, iid, iid+1, iid+2);
		for ( int j = 0; j < 3; j++ ){
			polygon->SetTriangle(iid[0], iid[1], iid[2]);
		}
	}
	fclose(fp);

	polygon->SetScalar(scalar);
	delete [] scalar;

	//
	// Add a Color Bar
	gmrVTKScalaBar *colorBar = new gmrVTKScalaBar;
	colorBar->Vertical();
	colorBar->LabelTextColor(0.9, 0.1, 0.1);
	colorBar->TitleTextColor(0.1, 0.1, 0.9);
	colorBar->SetTitle( "level" );

	colorBar->SetScalarMinMax(polygon->GetScalarMin(),polygon->GetScalarMax());

	colorBar->SetWidthPositionFactor(0.8);


	gmrVTKOutline *outline = new gmrVTKOutline(polygon->GetDataSet());
	gmrVTKRender* render = new gmrVTKRender;

	render->AddActor(polygon->GetActor());
	render->AddActor(outline->GetActor());
	render->AddActor(colorBar->GetActor());

	// Add Axes X-Y-Z
    gmrVTKAxes *axes = new gmrVTKAxes;
	axes->SetLength(10.0);
	axes->SetOrigin(-6.0, 2.0, -6.0);
	axes->SetRadius(0.05);
	axes->SymmetricOff();
	
	render->AddActor(axes->GetActor());

	render->InteractorStyleTrackballCamera();

	render->DefaultRun();

	gmrVTKText* text1 = new gmrVTKText;
	text1->SetText("creating movie!!");
	text1->SetPosition(20,400);
	text1->SetSize(20);

	gmrVTKText* text2 = new gmrVTKText;
	text2->SetText(" polygon.avi");
	text2->SetPosition(200,400);
	text2->SetSize(20);
	text2->SetColor(0,0,1.0);

	// AVI動画で画面を録画します
	gmrVTKCaptureAVI* avi = new gmrVTKCaptureAVI;
	avi->SetFileName("polygon");
	avi->SetInput(render);

	// 録画開始
	avi->Start();

	int count = 0;
	bool textOn = false;
	for (i = 0; i < 360; i += 3)
	{
		if ( count > 10 ) count = 0;
		if ( count == 0 ) textOn = !textOn;
		if ( textOn )
		{
			render->AddActor(text1->GetActor());
			render->AddActor(text2->GetActor());
		}else{
			render->RemoveActor(text1->GetActor());
			render->RemoveActor(text2->GetActor());
		}
		count++;

		// Render the image and rotate the active camera by one degree
		render->Run();
		render->GetRenderer()->GetActiveCamera()->Azimuth(3);
		avi->Write();
	}
	// 録画終了
	avi->End();

	delete avi;

	// 録画した動画AVIを再生
	gmrVTKShellExecute exec("polygon.avi");
	exec.Run();
}
