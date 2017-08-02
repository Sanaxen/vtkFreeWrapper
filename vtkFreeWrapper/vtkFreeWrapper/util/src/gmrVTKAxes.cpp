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
 * XYZ軸の作成
 *
 */
#include "gmrVTKAxes.hpp"

gmrVTKAxes::gmrVTKAxes()
{
	Origin_[0] = 0.0;
	Origin_[1] = 0.0;
	Origin_[2] = 0.0;
	Radius_ = 1.0;
	axesScale_ = 10.0;
	Symmetric_ = true;
	NumberOfSides_ = 10;

	axes_ = vtkAxes::New();
	axesTubes_ = vtkTubeFilter::New();
	axesMapper_ = vtkPolyDataMapper::New();
	axesActor_ = vtkActor::New();
}

gmrVTKAxes::~gmrVTKAxes()
{
	axes_->Delete();
	axesTubes_->Delete();
	axesMapper_->Delete();
	axesActor_->Delete();
}

void gmrVTKAxes::Flush(void)
{
    axes_->SetOrigin(Origin_[0], Origin_[1], Origin_[2]);
    axes_->SetScaleFactor(axesScale_);
	axes_->SetSymmetric(Symmetric_);

    axesTubes_->SetInputConnection(axes_->GetOutputPort());
    axesTubes_->SetRadius(Radius_);
    axesTubes_->SetNumberOfSides(NumberOfSides_);

    axesMapper_->SetInputConnection(axesTubes_->GetOutputPort());
    axesActor_->SetMapper(axesMapper_);

	axes_->Update();
}


vtkActor* gmrVTKAxes::GetActor()
{
	Flush();
	return axesActor_;
}

