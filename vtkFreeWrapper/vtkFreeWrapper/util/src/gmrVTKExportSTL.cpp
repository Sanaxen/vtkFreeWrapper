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
#include "gmrVTKExport.hpp"

gmrVTKExportSTL::gmrVTKExportSTL()
{
	stlWriter_ =  vtkSTLWriter::New();
}


gmrVTKExportSTL::~gmrVTKExportSTL()
{
	stlWriter_->Delete();
}

void gmrVTKExportSTL::SaveFile( vtkAlgorithmOutput* input, char* filename)
{
	stlWriter_->SetFileName(filename);
	stlWriter_->SetInputConnection(input);
	stlWriter_->Write();
}