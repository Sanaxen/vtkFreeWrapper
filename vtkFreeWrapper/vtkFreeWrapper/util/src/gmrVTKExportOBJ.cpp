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

gmrVTKExportOBJ::gmrVTKExportOBJ()
{
	vtkExporter_ = vtkOBJExporter::New();
}


gmrVTKExportOBJ::~gmrVTKExportOBJ()
{
	vtkExporter_->Delete();
}


void gmrVTKExportOBJ::SaveFile( gmrVTKRender* renwin, char* filename)
{
	vtkExporter_->SetRenderWindow(renwin->GetRenderWindow());
    vtkExporter_->SetFilePrefix(filename);
	vtkExporter_->Write();
}
