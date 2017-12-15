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
 * Stanford PLY形式
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

void gmrVTKExportPLY::SaveFile( vtkAlgorithmOutput* input, char* filename, char* color_name)
{

	if (color_name == NULL)
	{
		plyWriter_->SetFileName(filename);
		plyWriter_->SetInputConnection(input);
		plyWriter_->SetColorModeToDefault();
		plyWriter_->Update();
		plyWriter_->Write();
	}
	else
	{
		plyWriter_->SetInputConnection(input);
		plyWriter_->SetFileTypeToASCII();
		plyWriter_->SetColorModeToDefault();
		plyWriter_->SetArrayName(color_name);
		plyWriter_->SetFileName(filename);
		//plyWriter_->Update();
		plyWriter_->Write();
	}
}

