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
#include "gmrVTKExport.hpp"

gmrVTKExportPLY::gmrVTKExportPLY()
{
	plyWriter_ =  vtkPLYWriter::New();
}


gmrVTKExportPLY::~gmrVTKExportPLY()
{
	plyWriter_->Delete();
}

void gmrVTKExportPLY::SaveFile( vtkAlgorithmOutput* input, char* filename)
{
	plyWriter_->SetFileName(filename);
	plyWriter_->SetInputConnection(input);
	plyWriter_->Write();
}