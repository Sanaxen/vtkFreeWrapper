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
	plyWriter_->SetColorModeToDefault();
	//plyWriter_->SetColorModeToUniformCellColor();
	//plyWriter_->SetColorModeToUniformPointColor();
	plyWriter_->Update();
	plyWriter_->Write();
}

void gmrVTKExportPLY::SaveFile(vtkAlgorithmOutput* input, char* color_name, char* filename)
{
	plyWriter_->SetInputConnection(input);
	plyWriter_->SetFileTypeToASCII();
	plyWriter_->SetColorModeToDefault();
	//plyWriter_->SetColorModeToUniformCellColor();
	//plyWriter_->SetColorModeToUniformPointColor();
	//plyWriter_->SetColorModeToUniformColor();
	plyWriter_->SetArrayName(color_name);
	plyWriter_->SetFileName(filename);
	plyWriter_->Update();
	plyWriter_->Write();
}