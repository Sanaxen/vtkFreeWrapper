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
 * ポリゴン（多面体）
 */
#include "gmrVTKPolygon.hpp"

gmrVTKPolygon::gmrVTKPolygon()
{
	Size_ = 1.0;
	Color_[0] = 1.0;
	Color_[1] = 1.0;
	Color_[2] = 1.0;
	DiffuseColor_[0] = 1.0;
	DiffuseColor_[1] = 1.0;
	DiffuseColor_[2] = 1.0;

	Color_[3] = 0.0;
	DiffuseColor_[3] = 0.0;
	vertexNum_ = 0;

}

gmrVTKPolygon::~gmrVTKPolygon()
{
	if ( vertexNum_ ) delete Indextable_;
}


void gmrVTKPolygon::SetTriangle(int vtx1, int vtx2, int vtx3)
{
	if ( vertexNum_ == 0) throw("vertexNum_ == 0");

	vtkIdList* idlist;

	idlist = vtkIdList::New();
	idlist->Initialize();

	idlist->InsertNextId(Indextable_[vtx1]);
	idlist->InsertNextId(Indextable_[vtx2]);
	idlist->InsertNextId(Indextable_[vtx3]);
	
	dataset_->InsertNextCell(VTK_TRIANGLE,idlist);
	idlist->Delete();
}

void gmrVTKPolygon::SetVertex(int index, double* vtx1)
{
	vtkIdType id = points_->InsertNextPoint(vtx1[0], vtx1[1], vtx1[2]);
	idlist_->InsertNextId(id);
	Indextable_[index] = id;
}

vtkActor* gmrVTKPolygon::GetActor()
{
	if ( actor_  == NULL )
	{
		CreateMapper();
		actor_ = vtkActor::New();

		actor_->SetMapper(mapper_);
	}

	actor_->GetProperty()->SetColor(Color_[0],Color_[1],Color_[2]);
	actor_->GetProperty()->SetPointSize(Size_);
	actor_->GetProperty()->SetLineWidth(Size_);
	actor_->GetProperty()->SetDiffuseColor(DiffuseColor_[0],DiffuseColor_[1],DiffuseColor_[2]);

	return actor_;
}
 