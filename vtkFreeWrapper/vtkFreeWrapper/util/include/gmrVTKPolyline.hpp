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
 * �|�����C���i�܂���j
 */
#ifndef _GMRVTKPOLYLINE_HPP
#define _GMRVTKPOLYLINE_HPP

#include "gmrVTK.hpp"
#include "gmrVTKDefs.hpp"

/** 
 * @brief �|�����C���i�܂���j�N���X
 *
 */

class gmr_EXPORT gmrVTKPolyline  : public gmrVTK
{
public:
	gmrVTKPolyline();
	virtual ~gmrVTKPolyline();

	/** �܂���̍\���_�ǉ��ݒ�
	 *
	 * @param [in] point �\���_���W�z��
	 *
	 */
	void SetPoint(double* point);
	

	/** �܂���̍\���_�ݒ�I��
	 *
	 */
	virtual void Flush()
	{
		dataset_->InsertNextCell(VTK_POLY_LINE,idlist_);
		dataset_->SetPoints(points_);
	}
	virtual vtkActor* GetActor();


};

#endif
