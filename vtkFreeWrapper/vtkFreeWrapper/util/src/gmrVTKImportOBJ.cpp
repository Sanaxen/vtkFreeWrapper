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
#include "gmrVTKImport.hpp"

gmrVTKImportOBJ::gmrVTKImportOBJ(char* filename)
{
	OBJ_ = NULL;
	LoadFile(filename);
}


gmrVTKImportOBJ::~gmrVTKImportOBJ()
{
	if ( OBJ_ ) OBJ_->Delete();
}


void gmrVTKImportOBJ::LoadFile( char* filename)
{
	OBJ_ = vtkOBJReader::New();
	OBJ_->SetFileName( filename );
 
    stlMapper_ = vtkPolyDataMapper::New();
	stlMapper_->SetInputConnection(OBJ_->GetOutputPort());

    actor_ = vtkActor ::New();
	actor_->SetMapper(stlMapper_);

 
    ImplicitDataSet_ = vtkImplicitDataSet::New();
	ImplicitDataSet_->SetDataSet( OBJ_->GetOutput() );
}

