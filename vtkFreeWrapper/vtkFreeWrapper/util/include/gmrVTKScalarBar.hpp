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
 * �J���[�o�[�̍쐬
 *
 */
#ifndef _GMRVTKCOLORBAR_HPP
#define _GMRVTKCOLORBAR_HPP

#include "gmrVTK.hpp"
#include "gmrVTKDefs.hpp"

//
// Add a Color Bar legend in a different viewport.
//

/** 
 * @brief �J���[�o�[�N���X
 *
 */

class gmr_EXPORT gmrVTKScalaBar
{
	vtkScalarBarActor *colorBar_;
	vtkLookupTable* lockupTable_;
	vtkLookupTable* DefaultlockupTable_;

	double WidthFactor_;
	double HeightFactor_;
	double WidthPositionFactor_;
	double HeightPositionFactor_;

	vtkLookupTable* DefaultLookupTable();
	double ScalarMin_;
	double ScalarMax_;

public:
	gmrVTKScalaBar();
	virtual ~gmrVTKScalaBar();

	void SetLookupTable(vtkLookupTable* table)
	{
		if ( DefaultlockupTable_ ) DefaultlockupTable_->Delete();
		DefaultlockupTable_ = NULL;

		lockupTable_ = table;
	}

	/** �X�J���[�o�[�̖ڐ��i�ő�A�ŏ��j�ݒ�
	 *
	 * @param smin �ŏ�
	 * @param smax �ő�
	 *
	 */
	void SetScalarMinMax(double smin, double smax)
	{
		ScalarMin_ = smin;
		ScalarMax_ = smax;
	}

	/** ��ʉ������̒����ݒ�i��ʉ���1.0�Ƃ����ꍇ)
	 *
	 * @param [in] w �i��ʉ���1.0�Ƃ����ꍇ�̒���)
	 *
	 */
	void SetWidthFactor( double w)
	{
		WidthFactor_ = w;
	}

	/** ��ʏc�����̒����ݒ�i��ʏc��1.0�Ƃ����ꍇ)
	 *
	 * @param [in] h �i��ʏc��1.0�Ƃ����ꍇ�̒���)
	 *
	 */
	void SetHeightFactor( double h)
	{
		HeightFactor_ = h;
	}

	/** ��ʉ������̈ʒu�ݒ�i��ʉ�����:0�`�E:1.0�Ƃ����ꍇ)
	 *
	 * @param [in] x �i��ʉ�����:0�`�E:1.0�Ƃ����ꍇ�̈ʒu)
	 *
	 */
	void SetWidthPositionFactor( double x)
	{
		WidthPositionFactor_ = x;
	}

	/** ��ʏc�����̈ʒu�ݒ�i��ʏc����:0�`�E:1.0�Ƃ����ꍇ)
	 *
	 * @param [in] y �i��ʏc����:0�`�E:1.0�Ƃ����ꍇ�̈ʒu)
	 *
	 */
	void SetHeightPositionFactor(double y)
	{
		HeightPositionFactor_ = y;
	}

	/** �������\��
	 *
	 */
	void Horizontal()
	{
		colorBar_->SetOrientationToHorizontal();
	}

	/** �c�����\��
	 *
	 */
	void Vertical()
	{
		colorBar_->SetOrientationToVertical();
	}

	/** �J���[�o�[�̃^�C�g���ݒ�
	 *
	 * @param [in] title �J���[�o�[�̃^�C�g��
	 *
	 */
	void SetTitle( const char* title)
	{
		colorBar_->SetTitle( title);
	}

	/** ���x���e�L�X�g�̐F�ݒ�
	 * @param[in] r ��
	 * @param[in] g ��
	 * @param[in] b ��
	 *
	 */
	void LabelTextColor(double r, double g, double b)
	{
		colorBar_->GetLabelTextProperty()->SetColor(r, g, b);
	}

	/** �^�C�g���e�L�X�g�̐F�ݒ�
	 * @param[in] r ��
	 * @param[in] g ��
	 * @param[in] b ��
	 *
	 */
	void TitleTextColor(double r, double g, double b)
	{
		colorBar_->GetTitleTextProperty()->SetColor(r, g, b);
	}


	vtkTextProperty* GetTitleTextProperty()
	{
		return colorBar_->GetTitleTextProperty();
	}

	vtkTextProperty* GetLabelTextProperty()
	{
		return colorBar_->GetLabelTextProperty();
	}

	vtkLookupTable* GetLookupTable()
	{
		if ( lockupTable_ == NULL )
		{
			colorBar_->SetLookupTable(DefaultLookupTable());
		}
		return lockupTable_;
	}

	/** �A�N�^�[�̎擾
	 *
	 * @code
	 * gmrVTKScalaBar *colorBar = new gmrVTKScalaBar;
	 * ...
	 * double* scalar = new double[Num];
	 * for ( int i = 0; i < Num; i++){
	 *	p[0] = ...;
	 *	p[1] = ...;
	 *	p[2] = ...;
	 *	points->SetPoint(p);
	 *	scalar[i] = (double)i;
	 * }
	 * points->SetScalar(scalar);
	 * delete [] scalar;
	 *
	 * render->AddActor(colorBar->GetActor());
	 * @endcode
	 */
	vtkActor* GetActor()
	{
		if ( lockupTable_ == NULL )
		{
			colorBar_->SetLookupTable(DefaultLookupTable());
		}else{
			colorBar_->SetLookupTable(lockupTable_);
		}
		colorBar_->SetPosition(WidthPositionFactor_, HeightPositionFactor_);
		colorBar_->SetPosition2(WidthFactor_, HeightFactor_ );
		return (vtkActor*)colorBar_;
	}
};

#endif

