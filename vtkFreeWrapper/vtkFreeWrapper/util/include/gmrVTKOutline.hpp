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
 * �`����BOX���쐬����
 *
 */
#ifndef _GMRVTKOUTLINE_HPP
#define _GMRVTKOUTLINE_HPP

#include "gmrVTK.hpp"
#include "gmrVTKDefs.hpp"

/** 
 * @brief �`����BOX�쐬�N���X
 *
 */
class gmr_EXPORT gmrVTKOutline
{
	vtkOutlineFilter *outline_;
	vtkUnstructuredGrid  *dataset_;

	vtkActor* actor_;
	vtkDataSetMapper *mapper_;
	void CreateMapper(void);

	double Size_;
	double Color_[4];
	double DiffuseColor_[4];

public:
	/** �R���X�g���N�^
	 *
	 * @param [in] dataset �f�[�^�Z�b�g�̃|�C���^
	 *
	 */
	gmrVTKOutline(vtkUnstructuredGrid  *dataset);
	virtual ~gmrVTKOutline();
	
	/** �A�N�^�[�̎擾
	 *
	 */
	vtkActor* GetActor();

	vtkOutlineFilter* GetOutlineFilter()
	{
		return outline_;
	}
};

#endif