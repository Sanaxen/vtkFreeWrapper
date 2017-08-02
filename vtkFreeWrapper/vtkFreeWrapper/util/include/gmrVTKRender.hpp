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
/*
 * レンダリング・クラス
 *
 */
#ifndef _GMRVTKRENDER_HPP
#define _GMRVTKRENDER_HPP

#include "gmrVTK.hpp"
#include "gmrVTKDefs.hpp"

class gmrVTKCommand;
class gmrVTKPicker;

/** 
 * @brief レンダリングクラス
 *
 */

class gmr_EXPORT gmrVTKRender
{
	vtkRenderer *ren_;
	vtkRenderWindow *renWin_;
	vtkRenderWindowInteractor *iren_;
	vtkInteractorStyle *style_;

	double BackgroundColor_[4];	///< 背景色
	int Size_[2];				///< ウインドウサイズ

	void Initialize();
	bool InputRenderWindow_;

	gmrVTKPicker* picker_;		///< Pikcer

	/** オフスクリーンレンダリング・セットアップ
	 * Setup offscreen rendering
	 */
	void OffScreenSetup();

public:

	gmrVTKRender(int offscreen = 0);
	gmrVTKRender(vtkRenderWindow *renWin);
	
	virtual ~gmrVTKRender();

	/** レンダリングWindowサイズの設定
	 *
	 * @param [in] xsize 横のサイズ
	 * @param [in] ysize 縦のサイズ
	 *
	 */
	void SetSize(int xsize, int ysize)
	{
		Size_[0] = xsize;
		Size_[1] = ysize;
	}

	/** レンダリングWindowのバックグラウンドカラーの設定
	 *
	 * @param[in] r 赤
	 * @param[in] g 緑
	 * @param[in] b 青
	 */
	void SetBackgroundColor(double r, double g, double b)
	{
		BackgroundColor_[0] = r;
		BackgroundColor_[1] = g;
		BackgroundColor_[2] = b;
	}

	/** vtkRenderWindowインスタンスの取得
	 *
	 * @retval vtkRenderWindowインスタンス
	 *
	 */
	vtkRenderWindow* GetRenderWindow()
	{
		return renWin_;
	}
	
	/** vtkRendererインスタンスの取得
	 *
	 * @retval vtkRendererインスタンス
	 *
	 */
	vtkRenderer* GetRenderer()
	{
		return ren_;
	}

	/** vtkRenderWindowInteractorインスタンスの取得
	 *
	 * @retval vtkRenderWindowInteractorインスタンス
	 *
	 */
	vtkRenderWindowInteractor* GetRenderWindowInteractor()
	{
		return iren_;
	}

	/** 現在のマウスインタラクション(vtkInteractorStyleインスタンス)の取得
	 *
	 */
	vtkInteractorStyle* GetInteractorStyle()
	{
		return style_;
	}

	/** TrackballCamera(マウスによるカメラ移動回転)による（マウスインタラクション）
	 *
	 */
	void InteractorStyleTrackballCamera(void);

	/** RubberBandによる拡大（マウスインタラクション）
	 *
	 */
	void InteractorStyleRubberBandZoom(void);

	/** アクターの追加
	 *
	 */
	void AddActor(vtkActor* actor);
	void AddActor(vtkImageActor* actor);
	void AddActor(vtkXYPlotActor* actor);
	void AddActor(vtkVolume* actor);
	void AddActor(vtkTextActor* actor);

	/** アクターの取り外し
	 *
	 */
	void RemoveActor(vtkProp* actor);
	void RemoveActor(vtkActor* actor);
	void RemoveActor(vtkImageActor* actor);
	void RemoveActor(vtkXYPlotActor* actor);
	void RemoveActor(vtkTextActor* actor);

	/** レンダリング開始
	 *
	 */
	void Run();
	

	/** マウスインタラクションの開始
	 *
	 */
	void MouseInteractionStart();
	

	/** レンダリング開始
	 *  - マウスインタラクション在り
	 */
	void DefaultRun();


	/** Picker使用
	 *
	 * @param [in] picker 使用するPicker
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


	/** pick操作を有効にする
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


	/** pick操作を無効にする
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


	/** gmrVTKPickerインスタンスの取得
	 *
	 * @retval gmrVTKPickerインスタンス
	 *
	 */
	gmrVTKPicker* GetPicker();

	/** コールバックの設定
	 *
	 * @param [in] id イベントID
	 * @param [in] callback コールバック・クラスのインスタンス
	 *
	 */
	void AddCallback(vtkCommand::EventIds id, gmrVTKCommand* callback);


	/** コールバックの取り外し
	 *
	 * @param [in] callback コールバック・クラスのインスタンス
	 *
	 */
	void RemoveCallback(gmrVTKCommand* callback);

	void SetOffScreenRendering(int OnOff)
	{
		renWin_->SetOffScreenRendering( OnOff ); 
	}
};

#endif