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
 * STL�`��
 */
#include "gmrVTKImport.hpp"

gmrVTKImportSTL::gmrVTKImportSTL(char* filename)
{
	STL_ = NULL;
	LoadFile(filename);
}


gmrVTKImportSTL::~gmrVTKImportSTL()
{
	if ( STL_ ) STL_->Delete();
}


void gmrVTKImportSTL::LoadFile( char* filename)
{
	STL_ = vtkSTLReader::New();
	STL_->SetFileName( filename );
 
    stlMapper_ = vtkPolyDataMapper::New();
	stlMapper_->SetInputConnection(STL_->GetOutputPort());

    actor_ = vtkActor ::New();
	actor_->SetMapper(stlMapper_);

 
    ImplicitDataSet_ = vtkImplicitDataSet::New();
	ImplicitDataSet_->SetDataSet( STL_->GetOutput() );
}
