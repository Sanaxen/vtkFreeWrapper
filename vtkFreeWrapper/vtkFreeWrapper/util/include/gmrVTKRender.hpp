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
 * �����_�����O�E�N���X
 *
 */
#ifndef _GMRVTKRENDER_HPP
#define _GMRVTKRENDER_HPP

#include "gmrVTK.hpp"
#include "gmrVTKDefs.hpp"

class gmrVTKCommand;
class gmrVTKPicker;

/** 
 * @brief �����_�����O�N���X
 *
 */

class gmr_EXPORT gmrVTKRender
{
	vtkRenderer *ren_;
	vtkRenderWindow *renWin_;
	vtkRenderWindowInteractor *iren_;
	vtkInteractorStyle *style_;

	double BackgroundColor_[4];	///< �w�i�F
	int Size_[2];				///< �E�C���h�E�T�C�Y

	void Initialize();
	bool InputRenderWindow_;

	gmrVTKPicker* picker_;		///< Pikcer

	/** �I�t�X�N���[�������_�����O�E�Z�b�g�A�b�v
	 * Setup offscreen rendering
	 */
	void OffScreenSetup();

public:

	gmrVTKRender(int offscreen = 0);
	gmrVTKRender(vtkRenderWindow *renWin);
	
	virtual ~gmrVTKRender();

	/** �����_�����OWindow�T�C�Y�̐ݒ�
	 *
	 * @param [in] xsize ���̃T�C�Y
	 * @param [in] ysize �c�̃T�C�Y
	 *
	 */
	void SetSize(int xsize, int ysize)
	{
		Size_[0] = xsize;
		Size_[1] = ysize;
	}

	/** �����_�����OWindow�̃o�b�N�O���E���h�J���[�̐ݒ�
	 *
	 * @param[in] r ��
	 * @param[in] g ��
	 * @param[in] b ��
	 */
	void SetBackgroundColor(double r, double g, double b)
	{
		BackgroundColor_[0] = r;
		BackgroundColor_[1] = g;
		BackgroundColor_[2] = b;
	}

	/** vtkRenderWindow�C���X�^���X�̎擾
	 *
	 * @retval vtkRenderWindow�C���X�^���X
	 *
	 */
	vtkRenderWindow* GetRenderWindow()
	{
		return renWin_;
	}
	
	/** vtkRenderer�C���X�^���X�̎擾
	 *
	 * @retval vtkRenderer�C���X�^���X
	 *
	 */
	vtkRenderer* GetRenderer()
	{
		return ren_;
	}

	/** vtkRenderWindowInteractor�C���X�^���X�̎擾
	 *
	 * @retval vtkRenderWindowInteractor�C���X�^���X
	 *
	 */
	vtkRenderWindowInteractor* GetRenderWindowInteractor()
	{
		return iren_;
	}

	/** ���݂̃}�E�X�C���^���N�V����(vtkInteractorStyle�C���X�^���X)�̎擾
	 *
	 */
	vtkInteractorStyle* GetInteractorStyle()
	{
		return style_;
	}

	/** TrackballCamera(�}�E�X�ɂ��J�����ړ���])�ɂ��i�}�E�X�C���^���N�V�����j
	 *
	 */
	void InteractorStyleTrackballCamera(void);

	/** RubberBand�ɂ��g��i�}�E�X�C���^���N�V�����j
	 *
	 */
	void InteractorStyleRubberBandZoom(void);

	/** �A�N�^�[�̒ǉ�
	 *
	 */
	void AddActor(vtkActor* actor);
	void AddActor(vtkImageActor* actor);
	void AddActor(vtkXYPlotActor* actor);
	void AddActor(vtkVolume* actor);
	void AddActor(vtkTextActor* actor);

	/** �A�N�^�[�̎��O��
	 *
	 */
	void RemoveActor(vtkProp* actor);
	void RemoveActor(vtkActor* actor);
	void RemoveActor(vtkImageActor* actor);
	void RemoveActor(vtkXYPlotActor* actor);
	void RemoveActor(vtkTextActor* actor);

	/** �����_�����O�J�n
	 *
	 */
	void Run();
	

	/** �}�E�X�C���^���N�V�����̊J�n
	 *
	 */
	void MouseInteractionStart();
	

	/** �����_�����O�J�n
	 *  - �}�E�X�C���^���N�V�����݂�
	 */
	void DefaultRun();


	/** Picker�g�p
	 *
	 * @param [in] picker �g�p����Picker
	 *
	 * @code
	 * gmrVTKRender* render;
	 * ...
	 * gmrVTKPointPicker* picker = new gmrVTKPointPicker(render);
	 * render->SetPiker(picker);
	 * render->PickerOn();
	 * render->DefaultRun();
	 * @endcode
	 */
	void SetPiker(gmrVTKPicker* picker);


	/** pick�����L���ɂ���
	 *
	 * @code
	 * gmrVTKRender* render;
	 * ...
	 * gmrVTKPointPicker* picker = new gmrVTKPointPicker(render);
	 * render->SetPiker(picker);
	 * render->PickerOn();
	 * render->DefaultRun();
	 * @endcode
	 */
	void PickerOn();


	/** pick����𖳌��ɂ���
	 * @code
	 * gmrVTKRender* render;
	 * ...
	 * gmrVTKPointPicker* picker = new gmrVTKPointPicker(render);
	 * render->SetPiker(picker);
	 * render->PickerOn();
	 * render->DefaultRun();
	 * ...
	 * render->PickerOff();
	 * @endcode
	 */
	void PickerOff();


	/** gmrVTKPicker�C���X�^���X�̎擾
	 *
	 * @retval gmrVTKPicker�C���X�^���X
	 *
	 */
	gmrVTKPicker* GetPicker();

	/** �R�[���o�b�N�̐ݒ�
	 *
	 * @param [in] id �C�x���gID
	 * @param [in] callback �R�[���o�b�N�E�N���X�̃C���X�^���X
	 *
	 */
	void AddCallback(vtkCommand::EventIds id, gmrVTKCommand* callback);


	/** �R�[���o�b�N�̎��O��
	 *
	 * @param [in] callback �R�[���o�b�N�E�N���X�̃C���X�^���X
	 *
	 */
	void RemoveCallback(gmrVTKCommand* callback);

	void SetOffScreenRendering(int OnOff)
	{
		renWin_->SetOffScreenRendering( OnOff ); 
	}
};

#endif