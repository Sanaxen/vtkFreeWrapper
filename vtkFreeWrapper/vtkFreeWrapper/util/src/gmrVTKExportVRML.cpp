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

