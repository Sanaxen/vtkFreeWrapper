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
 * 外部（ポリゴン）データ読み込み
 */
#include "gmrVTKImport.hpp"

gmrVTKImport::gmrVTKImport()
{
	actor_ = NULL;
	Size_ = 1.0;
	Color_[0] = 1.0;
	Color_[1] = 1.0;
	Color_[2] = 1.0;
	DiffuseColor_[0] = 0.3;
	DiffuseColor_[1] = 0.1;
	DiffuseColor_[2] = 0.95;

	Color_[3] = 0.0;
	DiffuseColor_[3] = 0.0;

	stlMapper_ = NULL;
	ImplicitDataSet_ = NULL;
}

gmrVTKImport::~gmrVTKImport()
{
	if ( stlMapper_ ) stlMapper_->Delete();
	if ( ImplicitDataSet_ ) ImplicitDataSet_->Delete();
	if ( actor_ ) actor_->Delete();
}

vtkActor* gmrVTKImport::GetActor()
{
	actor_->GetProperty()->SetColor(Color_[0],Color_[1],Color_[2]);
	actor_->GetProperty()->SetPointSize(Size_);
	actor_->GetProperty()->SetLineWidth(Size_);
	actor_->GetProperty()->SetDiffuseColor(DiffuseColor_[0],DiffuseColor_[1],DiffuseColor_[2]);

	return actor_;
}
