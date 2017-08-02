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
 * �|���S���i���ʑ́j
 */
#ifndef _GMRVTKPOLYGON_HPP
#define _GMRVTKPOLYGON_HPP

#include "gmrVTK.hpp"
#include "gmrVTKDefs.hpp"

/** 
 * @brief �|���S���i���ʑ́j�N���X
 *
 */

class gmr_EXPORT gmrVTKPolygon  : public gmrVTK
{
	int vertexNum_;
	vtkIdType* Indextable_;

public:
	gmrVTKPolygon();
	virtual ~gmrVTKPolygon();


	/** �O�p�`�̐ݒ�
	 *
	 * @param [in] vtx1 ���_1�̃C���f�b�N�X
	 * @param [in] vtx2 ���_2�̃C���f�b�N�X
	 * @param [in] vtx3 ���_3�̃C���f�b�N�X
	 */
	void SetTriangle(int vtx1, int vtx2, int vtx3);

	/** ���_�̐ݒ�
	 *
	 * @param [in] index ���_�̃C���f�b�N�X�l
	 * @param [in] vtx1 ���_�̍��W�z��[3]
	 *
	 */
	void SetVertex(int index, double* vtx1);

	/** ���_���̐ݒ�
	 *
	 * @param [in] num ���_��
	 *
	 */
	void SetVertexNum( int num )
	{
		vertexNum_ = num;
		Indextable_ = new vtkIdType[num];
	}

	/** ���_���W�̎擾
	 *
	 * @param [in] index ���_�̃C���f�b�N�X
	 * @param [out] vtx ���_�̍��W�z��
	 *
	 */
	void GetVertex(int index, double vtx[3])
	{
		points_->GetPoint(Indextable_[index],vtx);
	}


	/** ���ʑ̐ݒ�I��
	 *
	 */
	virtual void Flush()
	{
		dataset_->SetPoints(points_);
		dataset_->ComputeBounds();
	}
	
	virtual vtkActor* GetActor();

};

#endif