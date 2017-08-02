/*
 * VTK���ȒP�Ɂi�H�j�g�����߂̊ȒP�N���X���C�u����
 * Copyright (c) Sanaxen
 *
 *
 * Kitware Inc - Leaders in Visualization Technology 
 * Copyright (c) 1993-2006 Ken Martin, Will Schroeder, Bill Lorensen 
 * All rights reserved.
 *
 */
/*
 * �O���i�|���S���j�f�[�^�ǂݍ���
 * Stanford PLY�`��
 */
#include "gmrVTKImport.hpp"

gmrVTKImportPLY::gmrVTKImportPLY(char* filename)
{
	PLY_ = NULL;
	LoadFile(filename);
}


gmrVTKImportPLY::~gmrVTKImportPLY()
{
	if ( PLY_ ) PLY_->Delete();
}


void gmrVTKImportPLY::LoadFile( char* filename)
{
	PLY_ = vtkPLYReader::New();
	PLY_->SetFileName( filename );
 
    stlMapper_ = vtkPolyDataMapper::New();
	stlMapper_->SetInputConnection(PLY_->GetOutputPort());
 
    actor_ = vtkActor ::New();
	actor_->SetMapper(stlMapper_);

 
    ImplicitDataSet_ = vtkImplicitDataSet::New();
	ImplicitDataSet_->SetDataSet( PLY_->GetOutput() );
}
