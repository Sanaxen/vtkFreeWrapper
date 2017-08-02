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
 * XYプロッターの作成
 *
 */
#ifndef _GMRVTKXYPLOT_HPP
#define _GMRVTKXYPLOT_HPP

#include "gmrVTK.hpp"
#include "gmrVTKDefs.hpp"
#include "gmrVTKRender.hpp"

#include <vector>
#include <string>


/** 
 * @brief XYプロットデータクラス
 *
 */
class gmr_EXPORT gmrVTKXYPlotData
{
	vtkFloatArray *xCoords_;
	vtkFloatArray *yCoords_;
	vtkFieldData *curve_;
	vtkDataObject *plot_;
	double PlotColor_[4];

	bool LabelSet_;
	std::string Label_;


public:
	gmrVTKXYPlotData();
	virtual ~gmrVTKXYPlotData();

	/**  XYプロットデータ取得
	 *
	 */
	vtkDataObject* GetPlotData()
	{
		return plot_;
	}

	bool isLabelSet() { return LabelSet_;}

	/** XYプロットのラベル設定
	 *
	 * @param [in] label XYプロットのラベル
	 *
	 */
	void SetLabel( char* label)
	{
		LabelSet_ = true;
		Label_ = label;
	}

	std::string GetLabel()
	{
		return Label_;
	}

	

	/** XYプロットの描画カラーの設定
	 *
	 * @param[in] r 赤
	 * @param[in] g 緑
	 * @param[in] b 青
	 */
	void SetPlotColor(double r, double g, double b)
	{
		PlotColor_[0] = r;
		PlotColor_[1] = g;
		PlotColor_[2] = b;
	}
	void GetPlotColor(double color[3])
	{
		color[0] = PlotColor_[0];
		color[1] = PlotColor_[1];
		color[2] = PlotColor_[2];
	}

	/** XYプロットのデータの設定
	 *
	 * @param [in] x X値
	 * @param [in] y Y値
	 *
	 */
	void SetXYData(double x, double y);

	/** XYプロットのデータ設定終了
	 *
	 */
	void DataEnd();
};


/** 
 * @brief XYプロッタークラス
 *
 */
class gmr_EXPORT gmrVTKXYPlotter
{
	std::vector<gmrVTKXYPlotData*> plotList_;
	vtkXYPlotActor *xyplot_;

	void CreateActor();
	double XRange_[2];
	double YRange_[2];
	int PointSize_;

	double WidthFactor_;
	double HeightFactor_;
	double WidthPositionFactor_;
	double HeightPositionFactor_;

public:
	gmrVTKXYPlotter();
	virtual ~gmrVTKXYPlotter();

	/** 新規のXYプロットデータ生成（追加)
	 *
	 */
	gmrVTKXYPlotData* CreatePlotData();


	/** アクターの取得
	 *
	 */
	vtkXYPlotActor* GetActor()
	{
		CreateActor();
		
		xyplot_ -> GetProperty() -> SetPointSize(PointSize_);
		xyplot_ -> SetXRange(XRange_[0],XRange_[1]);
		xyplot_ -> SetYRange(YRange_[0],YRange_[1]);
		xyplot_ -> SetPosition(WidthPositionFactor_,HeightPositionFactor_);
		xyplot_ -> SetPosition2(WidthFactor_, HeightFactor_);

		return xyplot_;
	}

	void DefaulRenderBackgroundColor(gmrVTKRender* ren)
	{
		ren->SetBackgroundColor(0.1,0.2,0.4);
	}


	/** プロット点のサイズ設定
	 *
	 * @param [in] size プロット点のサイズ
	 *
	 */
	void SetPointSize(int size)
	{
		PointSize_ = size;
	}

	/** プロットの点を表示する
	 *
	 */
	void PlotPointsOn()
	{
		GetActor() -> PlotPointsOn();
	}
	
	/** プロットの折れ線を表示する
	 *
	 */
	void PlotLinesOn()
	{
		GetActor() -> PlotLinesOn();
	}

	/** プロットの点を表示しない
	 *
	 */
	void PlotPointsOff()
	{
		GetActor() -> PlotPointsOff();
	}
	
	/** プロットの折れ線を表示しない
	 *
	 */
	void PlotLinesOff()
	{
		xyplot_ -> PlotLinesOff();
	}

	/** プロッターのタイトルを設定する
	 *
	 * @param [in] title プロッターのタイトル
	 *
	 */
	void SetTitle( char* title)
	{
         GetActor()->SetTitle(title);
	}

	/** プロッターのX軸タイトルを設定する
	 *
	 * @param [in] title プロッターのX軸タイトル
	 *
	 */
	void SetXTitle( char* title)
	{
         GetActor()->SetXTitle(title);
	}

	/** プロッターのY軸タイトルを設定する
	 *
	 * @param [in] title プロッターのY軸タイトル
	 *
	 */
	void SetYTitle( char* title)
	{
         GetActor()->SetYTitle(title);
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

};


#endif