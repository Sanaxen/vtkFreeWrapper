/*
 * VTKを簡単に（？）使うための簡単クラスライブラリ
 * Copyright (c) Sanaxen
 *
 *
 * Kitware Inc - Leaders in Visualization Technology 
 * Copyright (c) 1993-2006 Ken Martin, Will Schroeder, Bill Lorensen 
 * All rights reserved.
 *
 */
/*
 *
 * XYプロッターの作成
 *
 */
#include "gmrVTKXYPlot.hpp"

gmrVTKXYPlotData::gmrVTKXYPlotData()
{
	curve_ = NULL;
	plot_ = NULL;

	PlotColor_[0] = 1;
	PlotColor_[1] = 1;
	PlotColor_[2] = 0;
	PlotColor_[0] = 0;

	xCoords_ = vtkFloatArray::New();
	yCoords_ = vtkFloatArray::New();
	
	//xCoords_->SetNumberOfComponents(1);
	//yCoords_->SetNumberOfComponents(1);

	LabelSet_ = false;
}

gmrVTKXYPlotData::~gmrVTKXYPlotData()
{
	if ( xCoords_ ) xCoords_->Delete();
	if ( yCoords_ ) yCoords_->Delete();
	if ( curve_ ) curve_->Delete();
	if ( plot_ ) curve_->Delete();

	xCoords_ = NULL;
	yCoords_ = NULL;
	curve_ = NULL;
	plot_ = NULL;
}

void gmrVTKXYPlotData::SetXYData(double x, double y)
{
	xCoords_->InsertNextValue((float)x);
	yCoords_->InsertNextValue((float)y);
}

void gmrVTKXYPlotData::DataEnd()
{
	curve_  = vtkFieldData::New();

	curve_->AllocateArrays(2);
	curve_->AddArray(xCoords_);
	curve_->AddArray(yCoords_);
	
	plot_ = vtkDataObject::New();

	plot_->SetFieldData(curve_);
	//plot_->Update();
}



gmrVTKXYPlotter::gmrVTKXYPlotter()
{
	xyplot_ = NULL;


	XRange_[0] = 0.0;
	XRange_[1] = 0.0;
	YRange_[0] = 0.0;
	YRange_[1] = 0.0;

	PointSize_ = 5;

	WidthFactor_ = 0.15;
	HeightFactor_ = 0.9;
	WidthPositionFactor_ = 0.9;
	HeightPositionFactor_ = 0.9;

}

gmrVTKXYPlotter::~gmrVTKXYPlotter()
{
	if ( xyplot_ ) xyplot_->Delete();
	xyplot_ = NULL;

	for ( size_t i = 0; i < plotList_.size(); i++ )
	{
		delete plotList_[i];
	}
	plotList_.clear();
}

gmrVTKXYPlotData* gmrVTKXYPlotter::CreatePlotData()
{
	gmrVTKXYPlotData* plot = new gmrVTKXYPlotData;
	plotList_.push_back(plot);
	return plot;
}


void gmrVTKXYPlotter::CreateActor()
{
	if ( xyplot_ != NULL ) return;

	xyplot_ = vtkXYPlotActor::New();

	//Default
	xyplot_ -> LegendOn();
	
	for ( size_t i = 0; i < plotList_.size(); i++ )
	{
		xyplot_ -> AddDataObjectInput(plotList_[i]->GetPlotData());
	}

	xyplot_ -> SetDataObjectXComponent(0,0);
	for ( size_t i = 0; i < plotList_.size(); i++ )
	{
		xyplot_ -> SetDataObjectYComponent((int)i,1);
	}

	double color[3];
	for ( size_t i = 0; i < plotList_.size(); i++ )
	{
		plotList_[i]->GetPlotColor(color);
		xyplot_->SetPlotColor((int)i, color[0],color[1],color[2]);

		if (  plotList_[i]->isLabelSet() )
		{
			xyplot_->SetPlotLabel((int)i, plotList_[i]->GetLabel().c_str());
		}
	}

	xyplot_ -> GetPositionCoordinate()->SetValue(0,0.0,0);
	xyplot_ -> GetPosition2Coordinate()->SetValue(1,1,0);
	xyplot_ -> PlotPointsOn();
	xyplot_ -> PlotLinesOn();
}








