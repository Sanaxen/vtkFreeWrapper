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
 * Text�N���X
 */
#ifndef _GMRVTKTEXT_HPP
#define _GMRVTKTEXT_HPP

#include "gmrVTK.hpp"
#include "gmrVTKDefs.hpp"

/** 
 * @brief Text�N���X
 *
 */

class gmr_EXPORT gmrVTKText
{
	vtkTextProperty *TextProperty_;

	vtkTextActor* actor_;
	vtkTextMapper *mapper_;

	double Size_;
	double Color_[4];
	int Position_[2];

public:
	gmrVTKText();
	virtual ~gmrVTKText();

	/** ������̐ݒ�
	 *
	 * @param [in] string ������
	 *
	 */
	void SetText(const char* string);
	void SetText(const std::string& string)
	{
		SetText(string.c_str());
	}

	/** ������̑傫���ݒ�
	 *
	 * @param [in] size ������̑傫��
	 *
	 */
	void SetSize(double size)
	{
		Size_ = size;
	}

	/** ������̕\���ʒu�ݒ�
	 *
	 * @param [in] x �������̈ʒu
	 * @param [in] y �c�����̈ʒu
	 *
	 */
	void SetPosition( int x, int y)
	{
		Position_[0] = x;
		Position_[1] = y;
	}

	/** �����̐F�ݒ�
	 *
	 * @param[in] r ��
	 * @param[in] g ��
	 * @param[in] b ��
	 */
	void SetColor(double r, double g, double b)
	{
		Color_[0] = r;
		Color_[1] = g;
		Color_[2] = b;
	}

	/** �A�N�^�[�̎擾
	 *
	 */
	virtual vtkActor* GetActor();


	vtkTextProperty* GetTextProperty()
	{
		return TextProperty_;
	}

	vtkProperty* GetProperty()
	{
		return GetActor()->GetProperty();
	}

};

/** 
 * @brief 3DText�N���X
 *
 */
class gmr_EXPORT gmrVTKText3D
{
	vtkFollower* actor_;
	vtkPolyDataMapper *mapper_;
	vtkVectorText* vectorText_;

	double Size_[3];
	double Color_[4];
	double Position_[3];
	double Orientation_[3];

public:
	gmrVTKText3D();
	virtual ~gmrVTKText3D();

	/** ������̐ݒ�
	 *
	 * @param [in] string ������
	 *
	 */
	void SetText(const char* string);
	void SetText(const std::string& string)
	{
		SetText(string.c_str());
	}
	
	/** ������̑傫���ݒ�
	 *
	 * @param [in] sizex X����
	 * @param [in] sizey Y����
	 * @param [in] sizez Z����
	 *
	 */
	void SetSize(double sizex, double sizey, double sizez)
	{
		Size_[0] = sizex;
		Size_[1] = sizey;
		Size_[2] = sizez;
	}

	/** ������̕\���ʒu�ݒ�
	 *
	 * @param [in] x X���W
	 * @param [in] y Y���W
	 * @param [in] z Z���W
	 *
	 */
	void SetPosition( double x, double y, double z)
	{
		Position_[0] = x;
		Position_[1] = y;
		Position_[2] = z;
	}

	/** ������̕\���p�x�ݒ�
	 *
	 * @param [in] x X����]�p�x
	 * @param [in] y Y����]�p�x
	 * @param [in] z Z����]�p�x
	 *
	 */
	void SetOrientation( double x, double y, double z)
	{
		Orientation_[0] = x;
		Orientation_[1] = y;
		Orientation_[2] = z;
	}

	/** �����̐F�ݒ�
	 *
	 * @param[in] r ��
	 * @param[in] g ��
	 * @param[in] b ��
	 */
	void SetColor(double r, double g, double b)
	{
		Color_[0] = r;
		Color_[1] = g;
		Color_[2] = b;
	}

	/** �A�N�^�[�̎擾
	 *
	 */
	vtkActor* GetActor();
};
#endif

