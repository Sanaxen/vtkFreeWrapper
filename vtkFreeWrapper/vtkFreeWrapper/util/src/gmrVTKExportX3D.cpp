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
/*
 * 外部（ポリゴン）データ読み込み
 * OBJ形式
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

