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
 *
 * カラーバーの作成
 *
 */
#include "gmrVTKScalarBar.hpp"

gmrVTKScalaBar::gmrVTKScalaBar()
{
	colorBar_ = vtkScalarBarActor::New();
	
	lockupTable_ =NULL;
	DefaultlockupTable_ = NULL;
	WidthFactor_ = 0.15;
	HeightFactor_ = 0.9;
	WidthPositionFactor_ = 0.7;
	HeightPositionFactor_ = 0.1;
	colorBar_->SetOrientationToVertical();
	colorBar_->SetTitle( "title");

	ScalarMin_ = 0.0;
	ScalarMax_ = 255.0;
}

gmrVTKScalaBar::~gmrVTKScalaBar()
{
	colorBar_->Delete();
	if ( DefaultlockupTable_ )  DefaultlockupTable_->Delete();
	DefaultlockupTable_ = NULL;
}

vtkLookupTable * gmrVTKScalaBar::DefaultLookupTable()
{

    vtkLookupTable *lut = vtkLookupTable::New();
	lut->SetNumberOfTableValues( 256 );
	DefaultlockupTable_ = lut;
	lockupTable_ = lut;
	lut->SetTableRange(ScalarMin_,ScalarMax_);
	lut->SetNumberOfColors( 255 );
	lut->Build();
	return lut;
}

