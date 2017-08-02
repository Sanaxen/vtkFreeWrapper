/*
 * VTKを簡単に（？）使うための簡単クラスライブラリ
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
 * @brief キャプチャー基本クラス
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

	/** 出力対象の設定
	 *
	 */
	void SetInput(vtkWindow *input);

	/** 出力対象の設定
	 *
	 */
	void SetInput(vtkImageViewer* viewer);
	
	/** 出力対象の設定
	 *
	 */
	void SetInput(gmrVTKRender* renwin);

	/** 出力ファイル名の設定
	 *
	 * @param [in] filename 出力ファイル名
	 *
	 */
	void SetFileName( char* filename )
	{
		strcpy(FileName_, filename);
	}

	/** 出力ファイル名の取得
	 *
	 * @return 出力ファイル名
	 *
	 */
	char* GetFileName()
	{
		return FileName_;
	}

	/** 画面のキャプチャ
	 *
	 */
	void Capture();

	/** 画面のキャプチャ
	 *
	 * @param [in] index キャプチャ出力ファイルに付ける連番
	 */
	void Capture(int index);
};

/** 
 * @brief キャプチャーPNG形式クラス
 *
 */

class gmr_EXPORT gmrVTKCapturePNG : public gmrVTKCapture
{
public:
	gmrVTKCapturePNG();
	virtual ~gmrVTKCapturePNG();
};

/** 
 * @brief キャプチャーJPEG形式クラス 
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
 * @brief キャプチャーBMP形式クラス 
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
 * @brief キャプチャーAVI形式クラス 
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

	/** 出力対象の設定
	 *
	 */
	void SetInput(vtkWindow *input);

	/** 出力対象の設定
	 *
	 */
	void SetInput(vtkImageViewer* viewer);
	
	/** 出力対象の設定
	 *
	 */
	void SetInput(gmrVTKRender* renwin);


	/** 出力ファイル名の設定
	 *
	 * @param [in] filename 出力ファイル名
	 *
	 */
	void SetFileName( char* filename )
	{
		strcpy(FileName_, filename);
	}

	/** 出力ファイル名の取得
	 *
	 * @return 出力ファイル名
	 *
	 */
	char* GetFileName()
	{
		return FileName_;
	}

	/** 画面のキャプチャ開始
	 *
	 */
	void Start();

	/** 画面のキャプチャ開始
	 *
	 * @param [in] index キャプチャ出力ファイルに付ける連番
	 */
	void Start(int index);


	/** 画面をAVIファイルに書き込み
	 *
	 */
	void Write()
	{
		//gmrVTKLocker lock(lock_);
		WindowToImageFilter_->Modified();
		wrAVI_->Write();
	}


	/** 画面のキャプチャ終了
	 *
	 */
	void End()
	{
		wrAVI_->End();
	}

};
#endif


