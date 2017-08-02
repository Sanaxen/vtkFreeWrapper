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
 * 形状包含BOXを作成する
 *
 */
#include "gmrVTKOutline.hpp"

gmrVTKOutline::gmrVTKOutline(vtkUnstructuredGrid  *dataset)
{
	actor_ = NULL;
	outline_ = vtkOutlineFilter::New();
	dataset_ = dataset;
	
	DiffuseColor_[0] = 1.0;
	DiffuseColor_[1] = 1.0;
	DiffuseColor_[2] = 0.0;

	outline_->SetInputData(dataset_);
}

gmrVTKOutline::~gmrVTKOutline()
{
	mapper_->Delete();
	actor_->Delete();
	outline_->Delete();
}

void gmrVTKOutline::CreateMapper(void)
{
	mapper_ = vtkDataSetMapper::New();
	mapper_->SetInputData(outline_->GetOutput());
}

vtkActor* gmrVTKOutline::GetActor()
{
	CreateMapper();
	if ( actor_ == NULL )
	{
		actor_ = vtkActor::New();
	}
	actor_->SetMapper(mapper_);

	actor_->GetProperty()->SetColor(Color_[0],Color_[1],Color_[2]);
	actor_->GetProperty()->SetPointSize(Size_);
	actor_->GetProperty()->SetDiffuseColor(DiffuseColor_[0],DiffuseColor_[1],DiffuseColor_[2]);

	return actor_;
}