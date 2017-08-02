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

gmrVTKImportVRML::gmrVTKImportVRML(char* filename)
{
	VRML_ = NULL;
	LoadFile(filename);
}


gmrVTKImportVRML::~gmrVTKImportVRML()
{
	if ( VRML_ ) VRML_->Delete();
}


void gmrVTKImportVRML::LoadFile( char* filename)
{
	//VRML_ = vtkVRMLImporter::New();
	//VRML_->SetFileName( filename );
 //
 //   stlMapper_ = vtkPolyDataMapper::New();
	//stlMapper_->SetInput(VRML_->GetOutput());
 //
 //   actor_ = vtkActor ::New();
	//actor_->SetMapper(stlMapper_);

 //
 //   ImplicitDataSet_ = vtkImplicitDataSet::New();
	//ImplicitDataSet_->SetDataSet( VRML_->GetOutput() );
}

