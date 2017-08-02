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
 * Picker�̍쐬
 *
 */
#ifndef _GMRVTKPICKER_HPP
#define _GMRVTKPICKER_HPP

#include "gmrVTK.hpp"
#include "gmrVTKDefs.hpp"
#include "gmrVTKCommand.hpp"
#include "gmrVTKRender.hpp"


/** 
 * @brief gmrVTKCallbackPointPick�N���X
 * - PointPicker�p�̃T���v��callback�N���X
 */
class gmrVTKCallbackPointPick : public gmrVTKCommand
{
public:
        gmrVTKCallbackPointPick() {;};
        
		static gmrVTKCallbackPointPick *New() 
		{
			return new gmrVTKCallbackPointPick;
		}

        virtual void Execute(vtkObject *caller, unsigned long, void*);
};



/** 
 * @brief gmrVTKCallbackCellPick�N���X
 * - CellPicker�p�̃T���v��callback�N���X
 *
 */
class gmrVTKCallbackCellPick : public gmrVTKCommand
{
public:
        gmrVTKCallbackCellPick() {;};

        static gmrVTKCallbackCellPick *New() {
			return new gmrVTKCallbackCellPick; 
		}

        virtual void Execute(vtkObject *caller, unsigned long, void*);
};


/** 
 * @brief gmrVTKCallbackWorldPointPick�N���X
 * - WorldPointPick�p�̃T���v��callback�N���X
 *
 */
class gmrVTKCallbackWorldPointPick : public gmrVTKCommand
{
public:
        gmrVTKCallbackWorldPointPick() {;};

        static gmrVTKCallbackWorldPointPick *New() {
			return new gmrVTKCallbackWorldPointPick; 
		}

        virtual void Execute(vtkObject *caller, unsigned long, void*);
};

/** 
 * @brief Picker�N���X
 *
 */
class gmr_EXPORT gmrVTKPicker
{
	double tol_;			///< �s�b�N�E�g�������X

	gmrVTKRender* render_;

	vtkPicker* picker_;			///< �s�b�J�[
	gmrVTKCommand* callback_;	///< callback�N���X�ւ̃|�C���^�[

	double pos_[3];				///< �s�b�N�ʒu(��ʂ�X,Y,Z���W)
	double wpos_[3];			///< �s�b�N�ʒuX,Y,Z���E���W
	int pointId_;		///< �s�b�N�����_��ID(PointPicker(vtkCallbackPointPick�N���X)���擾�����l
	vtkActor* actor_;	///< �s�b�N����Actor�ւ̃|�C���^
	int succed_;		///< �s�b�N�ł��Ȃ������ꍇ=0

	void SetRender(gmrVTKRender* render);
	void SetPicker(vtkPicker* picker);
	void SetCallback(gmrVTKCommand* callback);

protected:

public:
	gmrVTKPicker();
	virtual ~gmrVTKPicker();

	void SetCondition(gmrVTKRender* render, vtkPicker* picker, gmrVTKCommand* callback);


	/** �s�b�N�����ʒu�ɂ�������̋L�^
	 *
	 */
	void SetPositionInfo(int succed, double* pos, double* wpos, int id, vtkActor* actor);

	/** �s�b�N�����ʒu�ɂ�������̎擾
	 *
	 */
	void GetPositionInfo(int& succed, double* pos, double* wpos, int& id, vtkActor** actor);



	/** vtkPicker�C���X�^���X�̎擾
	 *
	 * @retval vtkPicker�C���X�^���X
	 *
	 */
	vtkPicker* GetPicker()
	{
		return picker_;
	}


	/** gmrVTKCommand�C���X�^���X�̎擾
	 *
	 * @retval gmrVTKCommand�C���X�^���X
	 *
	 */
	gmrVTKCommand* GetCallback()
	{
		return callback_;
	}
};


/** 
 * @brief PointPicker�N���X
 *
 */
class gmr_EXPORT gmrVTKPointPicker : public gmrVTKPicker
{
public:
	gmrVTKPointPicker(gmrVTKRender* render);
	virtual ~gmrVTKPointPicker();
};


/** 
 * @brief CellPicker�N���X
 *
 */
class gmr_EXPORT gmrVTKCellPicker : public gmrVTKPicker
{
public:
	gmrVTKCellPicker(gmrVTKRender* render);
	virtual ~gmrVTKCellPicker();

};

/** 
 * @brief WorldPointPicker�N���X
 *
 */
class gmr_EXPORT gmrVTKWorldPointPicker : public gmrVTKPicker
{
public:
	gmrVTKWorldPointPicker(gmrVTKRender* render);
	virtual ~gmrVTKWorldPointPicker();

};

#endif