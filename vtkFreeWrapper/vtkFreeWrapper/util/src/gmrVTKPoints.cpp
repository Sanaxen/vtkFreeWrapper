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
 * 点列（点群）
 */
#include "gmrVTKPoints.hpp"

gmrVTKPoints::gmrVTKPoints()
{
	Size_ = 1.0;
	Color_[0] = 0.1;
	Color_[1] = 0.1;
	Color_[2] = 0.0;
	DiffuseColor_[0] = 0.1;
	DiffuseColor_[1] = 0.1;
	DiffuseColor_[2] = 0.5;

	Color_[3] = 0.0;
	DiffuseColor_[3] = 0.0;
}

gmrVTKPoints::~gmrVTKPoints()
{

}

void gmrVTKPoints::SetPoint(double* point)
{
	vtkIdType id = points_->InsertNextPoint(point[0], point[1], point[2]);
	idlist_->InsertNextId(id);
}


vtkActor* gmrVTKPoints::GetActor()
{

	if ( actor_  == NULL ){
		CreateMapper();
		actor_ = vtkActor::New();

		actor_->SetMapper(mapper_);
	}

	actor_->GetProperty()->SetColor(Color_[0],Color_[1],Color_[2]);
	actor_->GetProperty()->SetPointSize(Size_);
	actor_->GetProperty()->SetDiffuseColor(DiffuseColor_[0],DiffuseColor_[1],DiffuseColor_[2]);

	return actor_;
}
 