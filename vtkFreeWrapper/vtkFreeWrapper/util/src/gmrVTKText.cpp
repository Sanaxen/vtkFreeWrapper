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
 * Textクラス
 *
 */
#include "gmrVTKText.hpp"

gmrVTKText::gmrVTKText()
{
	actor_ = vtkTextActor::New();

	Size_ = 12.0;
	Color_[0] = 1.0;
	Color_[1] = 0.5;
	Color_[2] = 0.5;
	Color_[3] = 0.0;
	Position_[0] = 0;
	Position_[1] = 0;
}

gmrVTKText::~gmrVTKText()
{
	if ( actor_ ) actor_->Delete();
}

void gmrVTKText::SetText(const char* string)
{
	actor_->SetInput(string);
}


vtkActor* gmrVTKText::GetActor()
{
	if ( actor_ == NULL )
	{
		actor_ = vtkTextActor::New();
	}
	actor_->SetDisplayPosition(Position_[0], Position_[1]);

	actor_->GetTextProperty()->SetColor(Color_[0], Color_[1], Color_[2]);
	actor_->GetTextProperty()->SetFontSize(Size_);

	return (vtkActor*)actor_;
}
 

gmrVTKText3D::gmrVTKText3D()
{
	vectorText_ = vtkVectorText::New();
	mapper_ = vtkPolyDataMapper::New();

	actor_ = NULL;

	Size_[0] = 1.0;
	Size_[1] = 1.0;
	Size_[2] = 1.0;
	Color_[0] = 1.0;
	Color_[1] = 0.5;
	Color_[2] = 0.5;
	Color_[3] = 0.0;
	Position_[0] = 0;
	Position_[1] = 0;
	Position_[2] = 0;
	Orientation_[0] = 0;
	Orientation_[1] = 0;
	Orientation_[2] = 0;

}
gmrVTKText3D::~gmrVTKText3D()
{
	if ( vectorText_ ) vectorText_->Delete();
	if ( actor_ ) actor_->Delete();
	if ( mapper_ ) mapper_->Delete();
}

void gmrVTKText3D::SetText(const char* string)
{
	vectorText_->SetText(string);
	mapper_->SetInputConnection(vectorText_->GetOutputPort());
}


vtkActor* gmrVTKText3D::GetActor()
{
	if ( actor_ == NULL )
	{
		actor_ = vtkFollower::New();
		actor_->SetMapper(mapper_);
	}


	actor_->SetOrientation(Orientation_[0],Orientation_[1],Orientation_[2]);
	actor_->SetScale(Size_[0],Size_[1],Size_[2]);
	actor_->SetPosition(Position_[0],Position_[1],Position_[2]);
	actor_->GetProperty()->SetColor(Color_[0],Color_[1],Color_[2]);

	return actor_;
}
