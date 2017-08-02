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
 *
 * �R�[���o�b�N�E�x�[�X�N���X�̍쐬
 *
 */
#include "gmrVTKCommand.hpp"

gmrVTKCommand::gmrVTKCommand()
{
	ren_ = NULL;
	picker_ = NULL;
}

gmrVTKCommand::~gmrVTKCommand()
{
	ren_ = NULL;
	picker_ = NULL;
}

void gmrVTKCommand::SetRenderer(gmrVTKRender *ren)
{
    ren_ = ren;
}

void gmrVTKCommand::SetPicker(gmrVTKPicker *picker)
{
    picker_ = picker;
}

void gmrVTKCommand::SetCondition(gmrVTKRender *ren, gmrVTKPicker *picker)
{
	SetRenderer(ren);
	SetPicker(picker);
}


gmrVTKRender* gmrVTKCommand::GetRenderer()
{
	return ren_;
}

gmrVTKPicker* gmrVTKCommand::GetPicker()
{
	return picker_;
}
