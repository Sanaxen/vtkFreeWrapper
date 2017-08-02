/************************************************************
*
* vtkWrapperLIBを使った簡単なサンプルプログラム
*
* X-Yプロッターの例
*************************************************************/
/*
 * VTKを簡単に（？）使うための簡単クラスライブラリの使用例
 * Copyright (c) Sanaxen
 *
 */
#include <math.h>
#include "gmrVTKXYPlot.hpp"
#include "gmrVTKRender.hpp"

void xyplot()
{
	gmrVTKRender* render = new gmrVTKRender;
	gmrVTKXYPlotData* plotdata;
	gmrVTKXYPlotter* xyploter = new gmrVTKXYPlotter;

	int i, DataSize = 100;

	plotdata = xyploter->CreatePlotData();
	plotdata->SetPlotColor(1,1,0);
	plotdata->SetLabel("Sqrt");
	for(i=0; i<DataSize; i++)
	{
		plotdata->SetXYData((double)i, sqrt((double)i));
	}
	plotdata->DataEnd();


	plotdata = xyploter->CreatePlotData();
	plotdata->SetPlotColor(0,1,0);
	plotdata->SetLabel("5*Sin");
	for(i=0; i<DataSize; i++)
	{
		plotdata->SetXYData((double)i, 5.0*sin((double)i));
	}
	plotdata->DataEnd();

	xyploter->DefaulRenderBackgroundColor(render);

	xyploter->SetTitle("2D Plotting TEST !!");
	xyploter->SetXTitle("X");
	xyploter->SetYTitle("F(x)");

	vtkTextProperty *TextProperty = vtkTextProperty::New();
	TextProperty->SetFontFamilyToTimes();

	xyploter->SetWidthPositionFactor(0.02);
	xyploter->SetHeightPositionFactor(0.1);
	xyploter->SetWidthFactor(0.9);
	xyploter->SetHeightFactor(0.9);

	xyploter->GetActor()->SetAxisLabelTextProperty(TextProperty);
	xyploter->GetActor()->SetTitleTextProperty(TextProperty);
	xyploter->GetActor()->SetLegendPosition(0.8,0.7);
	xyploter->GetActor()->SetLegendPosition2(0.1,0.1);
	xyploter->GetActor()->SetLabelFormat("%.2f");

	render->AddActor(xyploter->GetActor());

	int *size = render->GetRenderWindow()->GetScreenSize();
	render->SetSize(size[0]*8/10,size[1]*8/10);
	render->SetBackgroundColor(0.1,0.2,0.4);

	render->DefaultRun();
}

