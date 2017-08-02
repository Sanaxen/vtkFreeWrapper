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
 *
 * カラーバーの作成
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
 * @brief カラーバークラス
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

	/** スカラーバーの目盛（最大、最小）設定
	 *
	 * @param smin 最小
	 * @param smax 最大
	 *
	 */
	void SetScalarMinMax(double smin, double smax)
	{
		ScalarMin_ = smin;
		ScalarMax_ = smax;
	}

	/** 画面横方向の長さ設定（画面横を1.0とした場合)
	 *
	 * @param [in] w （画面横を1.0とした場合の長さ)
	 *
	 */
	void SetWidthFactor( double w)
	{
		WidthFactor_ = w;
	}

	/** 画面縦方向の長さ設定（画面縦を1.0とした場合)
	 *
	 * @param [in] h （画面縦を1.0とした場合の長さ)
	 *
	 */
	void SetHeightFactor( double h)
	{
		HeightFactor_ = h;
	}

	/** 画面横方向の位置設定（画面横を左:0～右:1.0とした場合)
	 *
	 * @param [in] x （画面横を左:0～右:1.0とした場合の位置)
	 *
	 */
	void SetWidthPositionFactor( double x)
	{
		WidthPositionFactor_ = x;
	}

	/** 画面縦方向の位置設定（画面縦を左:0～右:1.0とした場合)
	 *
	 * @param [in] y （画面縦を左:0～右:1.0とした場合の位置)
	 *
	 */
	void SetHeightPositionFactor(double y)
	{
		HeightPositionFactor_ = y;
	}

	/** 横方向表示
	 *
	 */
	void Horizontal()
	{
		colorBar_->SetOrientationToHorizontal();
	}

	/** 縦方向表示
	 *
	 */
	void Vertical()
	{
		colorBar_->SetOrientationToVertical();
	}

	/** カラーバーのタイトル設定
	 *
	 * @param [in] title カラーバーのタイトル
	 *
	 */
	void SetTitle( const char* title)
	{
		colorBar_->SetTitle( title);
	}

	/** ラベルテキストの色設定
	 * @param[in] r 赤
	 * @param[in] g 緑
	 * @param[in] b 青
	 *
	 */
	void LabelTextColor(double r, double g, double b)
	{
		colorBar_->GetLabelTextProperty()->SetColor(r, g, b);
	}

	/** タイトルテキストの色設定
	 * @param[in] r 赤
	 * @param[in] g 緑
	 * @param[in] b 青
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

	/** アクターの取得
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

