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
 * ポリライン（折れ線）
 */
#include "gmrVTKPolyline.hpp"

gmrVTKPolyline::gmrVTKPolyline()
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

gmrVTKPolyline::~gmrVTKPolyline()
{
}

void gmrVTKPolyline::SetPoint(double* point)
{
	vtkIdType id = points_->InsertNextPoint(point[0], point[1], point[2]);
	idlist_->InsertNextId(id);
}



vtkActor* gmrVTKPolyline::GetActor()
{
	if ( actor_  == NULL ){
		CreateMapper();
		actor_ = vtkActor::New();

		actor_->SetMapper(mapper_);
	}

	actor_->GetProperty()->SetColor(Color_[0],Color_[1],Color_[2]);
	actor_->GetProperty()->SetPointSize(Size_);
	actor_->GetProperty()->SetLineWidth(Size_);
	actor_->GetProperty()->SetDiffuseColor(DiffuseColor_[0],DiffuseColor_[1],DiffuseColor_[2]);

	return actor_;
}
 