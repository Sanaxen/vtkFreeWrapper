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

gmrVTKExportX3D::gmrVTKExportX3D()
{
	vtkExporter_ = vtkX3DExporter::New();
}


gmrVTKExportX3D::~gmrVTKExportX3D()
{
	vtkExporter_->Delete();
}


void gmrVTKExportX3D::SaveFile( gmrVTKRender* renwin, char* filename)
{
	vtkExporter_->SetFileName(filename);
	vtkExporter_->SetRenderWindow(renwin->GetRenderWindow());
	vtkExporter_->SetBinary(0);
	vtkExporter_->Update();
	vtkExporter_->Write();
}

