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
 * OBJ�`��
 */
#include "gmrVTKImport.hpp"

gmrVTKImportOBJ::gmrVTKImportOBJ(char* filename)
{
	OBJ_ = NULL;
	LoadFile(filename);
}


gmrVTKImportOBJ::~gmrVTKImportOBJ()
{
	if ( OBJ_ ) OBJ_->Delete();
}


void gmrVTKImportOBJ::LoadFile( char* filename)
{
	OBJ_ = vtkOBJReader::New();
	OBJ_->SetFileName( filename );
 
    stlMapper_ = vtkPolyDataMapper::New();
	stlMapper_->SetInputConnection(OBJ_->GetOutputPort());

    actor_ = vtkActor ::New();
	actor_->SetMapper(stlMapper_);

 
    ImplicitDataSet_ = vtkImplicitDataSet::New();
	ImplicitDataSet_->SetDataSet( OBJ_->GetOutput() );
}

