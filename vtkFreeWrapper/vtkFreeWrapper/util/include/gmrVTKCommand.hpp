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
 * �R�[���o�b�N�̍쐬
 *
 */
#ifndef _GMRVTKCOMMAND_HPP
#define _GMRVTKCOMMAND_HPP

#include "gmrVTK.hpp"
#include "gmrVTKDefs.hpp"

class gmrVTKRender;
class gmrVTKPicker;

/** 
 * @brief  �R�[���o�b�N�E�x�[�X�N���X�̍쐬
 *
 */
class gmr_EXPORT gmrVTKCommand : public vtkCommand
{
public:
	gmrVTKCommand();
	virtual ~gmrVTKCommand();


	/** �R�[���o�b�N����������E�B���h�E�̐ݒ�
	 *
	 * @param [in] ren �E�B���h�E
	 *
	 */
    void SetRenderer(gmrVTKRender *ren);


	/** �R�[���o�b�N����������Pick���s���E�B���h�E�̐ݒ�
	 *
	 * @param [in] ren �E�B���h�E
	 * @param [in] picker �s�b�J�[
	 *
	 */
	void SetCondition(gmrVTKRender *ren, gmrVTKPicker *picker);

	/** �R�[���o�b�N����������E�B���h�E�̎擾
	 *
	 * @retval �R�[���o�b�N����������E�B���h�E
	 *
	 */
	gmrVTKRender* GetRenderer();


	/** �R�[���o�b�N����������s�b�J�[�̎擾
	 *
	 * @retval �R�[���o�b�N����������s�b�J�[
	 *
	 */
	gmrVTKPicker* GetPicker();

private:
    void SetPicker(gmrVTKPicker *picker);
	gmrVTKRender *ren_;
	gmrVTKPicker *picker_;

};


#endif