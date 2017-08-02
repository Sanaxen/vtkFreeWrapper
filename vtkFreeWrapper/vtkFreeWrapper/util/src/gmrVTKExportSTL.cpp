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
 * STL形式
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