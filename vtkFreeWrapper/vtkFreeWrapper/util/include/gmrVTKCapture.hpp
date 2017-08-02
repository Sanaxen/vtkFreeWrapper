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
#ifndef _GMRVTKCAPTURE_HPP
#define _GMRVTKCAPTURE_HPP

#include "gmrVTK.hpp"
#include "gmrVTKDefs.hpp"
#include "gmrVTKRender.hpp"
#include "gmrVTKLocker.hpp"

/** 
 * @brief �L���v�`���[��{�N���X
 *
 */

class gmr_EXPORT gmrVTKCapture
{
protected:
	char FileName_[260];
	char Exten[32];
	vtkWindowToImageFilter *WindowToImageFilter_;
	vtkImageWriter* wr_;
	gmrVTKLock lock_;


public:
	gmrVTKCapture();

	virtual ~gmrVTKCapture();

	/** �o�͑Ώۂ̐ݒ�
	 *
	 */
	void SetInput(vtkWindow *input);

	/** �o�͑Ώۂ̐ݒ�
	 *
	 */
	void SetInput(vtkImageViewer* viewer);
	
	/** �o�͑Ώۂ̐ݒ�
	 *
	 */
	void SetInput(gmrVTKRender* renwin);

	/** �o�̓t�@�C�����̐ݒ�
	 *
	 * @param [in] filename �o�̓t�@�C����
	 *
	 */
	void SetFileName( char* filename )
	{
		strcpy(FileName_, filename);
	}

	/** �o�̓t�@�C�����̎擾
	 *
	 * @return �o�̓t�@�C����
	 *
	 */
	char* GetFileName()
	{
		return FileName_;
	}

	/** ��ʂ̃L���v�`��
	 *
	 */
	void Capture();

	/** ��ʂ̃L���v�`��
	 *
	 * @param [in] index �L���v�`���o�̓t�@�C���ɕt����A��
	 */
	void Capture(int index);
};

/** 
 * @brief �L���v�`���[PNG�`���N���X
 *
 */

class gmr_EXPORT gmrVTKCapturePNG : public gmrVTKCapture
{
public:
	gmrVTKCapturePNG();
	virtual ~gmrVTKCapturePNG();
};

/** 
 * @brief �L���v�`���[JPEG�`���N���X 
 * 
 *
 */
class gmr_EXPORT gmrVTKCaptureJPEG : public gmrVTKCapture
{
public:
	gmrVTKCaptureJPEG();
	virtual ~gmrVTKCaptureJPEG();
};

/** 
 * @brief �L���v�`���[BMP�`���N���X 
 * 
 *
 */
class gmr_EXPORT gmrVTKCaptureBMP : public gmrVTKCapture
{
public:
	gmrVTKCaptureBMP();
	virtual ~gmrVTKCaptureBMP();
};


/** 
 * @brief �L���v�`���[AVI�`���N���X 
 * 
 *
 */
class gmr_EXPORT gmrVTKCaptureAVI
{
protected:
	char FileName_[260];
	char Exten[32];
	vtkWindowToImageFilter *WindowToImageFilter_;

	vtkImageWriter* wr_;
	gmrVTKLock lock_;
	vtkAVIWriter* wrAVI_;
public:
	gmrVTKCaptureAVI();
	virtual ~gmrVTKCaptureAVI();

	/** �o�͑Ώۂ̐ݒ�
	 *
	 */
	void SetInput(vtkWindow *input);

	/** �o�͑Ώۂ̐ݒ�
	 *
	 */
	void SetInput(vtkImageViewer* viewer);
	
	/** �o�͑Ώۂ̐ݒ�
	 *
	 */
	void SetInput(gmrVTKRender* renwin);


	/** �o�̓t�@�C�����̐ݒ�
	 *
	 * @param [in] filename �o�̓t�@�C����
	 *
	 */
	void SetFileName( char* filename )
	{
		strcpy(FileName_, filename);
	}

	/** �o�̓t�@�C�����̎擾
	 *
	 * @return �o�̓t�@�C����
	 *
	 */
	char* GetFileName()
	{
		return FileName_;
	}

	/** ��ʂ̃L���v�`���J�n
	 *
	 */
	void Start();

	/** ��ʂ̃L���v�`���J�n
	 *
	 * @param [in] index �L���v�`���o�̓t�@�C���ɕt����A��
	 */
	void Start(int index);


	/** ��ʂ�AVI�t�@�C���ɏ�������
	 *
	 */
	void Write()
	{
		//gmrVTKLocker lock(lock_);
		WindowToImageFilter_->Modified();
		wrAVI_->Write();
	}


	/** ��ʂ̃L���v�`���I��
	 *
	 */
	void End()
	{
		wrAVI_->End();
	}

};
#endif


