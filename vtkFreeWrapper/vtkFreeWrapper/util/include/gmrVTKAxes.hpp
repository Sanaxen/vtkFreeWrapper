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
 * XYZ���̍쐬
 *
 */
#ifndef _GMRVTKAXES_HPP
#define _GMRVTKAXES_HPP

#include "gmrVTK.hpp"
#include "gmrVTKDefs.hpp"

/** 
 * @brief XYZ���̍쐬�N���X
 *
 */

class gmr_EXPORT gmrVTKAxes
{
	double axesScale_;
	double Radius_;
	double Origin_[3];
	bool Symmetric_;
	int NumberOfSides_;	//�~���ߎ����p�`�Ӑ�

	vtkAxes *axes_;
	vtkTubeFilter *axesTubes_;
	vtkPolyDataMapper *axesMapper_;
	vtkActor *axesActor_;

	void Flush(void);

public:
	gmrVTKAxes();
	virtual ~gmrVTKAxes();

	/** ���W���̌��_�ݒ�
	 *
	 * @param [in] x X���W
	 * @param [in] y Y���W
	 * @param [in] z Z���W
	*/
	void SetOrigin( double x, double y, double z)
	{
		Origin_[0] = x;
		Origin_[1] = y;
		Origin_[2] = z;
	}

	/** ���W���̒����ݒ�
	 *
	 * @param [in] len ���W���̒���
	 */
	void SetLength(double len)
	{
		axesScale_ = len;
	}

	/** ���W���̉~�����a�̐ݒ�
	 *
	 * @param [in] r �~�����a
	 *
	 */
	void SetRadius( double r)
	{
		Radius_ = r;
	}

	/** ���_�𒆐S�Ɂ{���A�|�������Ɏ����쐬
	 *
	 */
	void SymmetricOn()
	{
		Symmetric_ = true;
	}

	/** ���_�𒆐S�Ɂ{���Е��Ɏ����쐬
	 *
	 */
	void SymmetricOff()
	{
		Symmetric_ = false;
	}

	/** �A�N�^�[�̎擾
	 *
	 */
	vtkActor* GetActor();

};

#endif



