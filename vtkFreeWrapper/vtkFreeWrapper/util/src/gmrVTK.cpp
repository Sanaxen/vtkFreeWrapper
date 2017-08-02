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
#include "gmrVTK.hpp"

gmrVTK::gmrVTK()
{
	points_ = vtkPoints::New();
	dataset_ = vtkUnstructuredGrid::New();
	idlist_ = vtkIdList::New();
	points_->SetDataType(VTK_DOUBLE);
	mapper_ = NULL;
	actor_ = NULL;

	Size_ = 1.0;
	Color_[0] = 0.1;
	Color_[1] = 0.1;
	Color_[2] = 0.0;
	DiffuseColor_[0] = 0.1;
	DiffuseColor_[1] = 0.1;
	DiffuseColor_[2] = 0.5;

	Color_[3] = 0.0;
	DiffuseColor_[3] = 0.0;
	Scalar_ = NULL;
	WarpScalar_ = NULL;

	ScalarMin_ = 0;
	ScalarMax_ = 0;
}

gmrVTK::~gmrVTK()
{
	if ( points_ ) points_->Delete();
	if ( dataset_ ) dataset_->Delete();
	if ( idlist_ ) idlist_->Delete();
	if ( actor_ ) actor_->Delete();
	if ( mapper_ ) mapper_->Delete();

	if ( Scalar_ != NULL )
	{
		Scalar_->Delete();
	}
	if ( WarpScalar_ != NULL )
	{
		WarpScalar_->Delete();
	}
}


void gmrVTK::SetScalar( double* scalar )
{
	Flush();

	if ( Scalar_ != NULL )
	{
		Scalar_->Delete();
	}
	int num = GetDataNum();

	Scalar_ = vtkFloatArray::New();
	Scalar_->SetNumberOfTuples(num);
	dataset_->GetPointData()->SetScalars(Scalar_);

	ScalarMax_ = -9999999999999.0;
	ScalarMin_ = 9999999999999.0;
	for ( int i = 0; i < num; i++ )
	{
		Scalar_->SetValue(this->idlist_->GetId(i), scalar[i]);
		if ( scalar[i] < ScalarMin_ ) ScalarMin_ = scalar[i];
		if ( scalar[i] > ScalarMax_ ) ScalarMax_ = scalar[i];
	}
	WarpScalar_ = vtkWarpScalar::New();
	WarpScalar_->SetInputData(dataset_);
}


void gmrVTK::CreateMapper()
{
	Flush();

	mapper_ = vtkDataSetMapper::New();
	if ( Scalar_ )
	{
		mapper_->SetInputData(WarpScalar_->GetOutput());
		mapper_->ScalarVisibilityOn();
		WarpScalar_->Update();
		WarpScalar_->SetScaleFactor(1.0/(double)GetDataNum());

		double tmp[2];
		dataset_->GetScalarRange(tmp);
		mapper_->SetScalarRange(tmp[0],tmp[1]);

	}else
	{
		mapper_->SetInputData(dataset_);
	}

	mapper_->Update();
}


 