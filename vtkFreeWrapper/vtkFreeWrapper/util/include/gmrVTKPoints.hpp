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
 * �_��i�_�Q�j
 */
#ifndef _GMRVTKPOINTS_HPP
#define _GMRVTKPOINTS_HPP

#include "gmrVTK.hpp"

/** 
 * @brief �_��i�_�Q�j�N���X
 *
 */
class gmr_EXPORT gmrVTKPoints : public gmrVTK
{
public:
	gmrVTKPoints();
	virtual ~gmrVTKPoints();

	/** �_���W�̒ǉ�
	 *
	 * @param [in] point �_�̍��W�z��
	 *
	 */
	void SetPoint(double* point);

	/** �_���W�̒ǉ��I��
	 *
	 */
	virtual void Flush()
	{
		dataset_->InsertNextCell(VTK_VERTEX,idlist_);
		dataset_->SetPoints(points_);
	}

	virtual vtkActor* GetActor();

};

#endif

