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
#include "gmrVTKExport.hpp"

gmrVTKExportVRML::gmrVTKExportVRML()
{
	vtkExporter_ = vtkVRMLExporter::New();
}


gmrVTKExportVRML::~gmrVTKExportVRML()
{
	vtkExporter_->Delete();
}


void gmrVTKExportVRML::SaveFile( gmrVTKRender* renwin, char* filename)
{
	vtkExporter_->SetFileName(filename);
	vtkExporter_->SetRenderWindow(renwin->GetRenderWindow());
	vtkExporter_->Update();
	vtkExporter_->Write();
}

