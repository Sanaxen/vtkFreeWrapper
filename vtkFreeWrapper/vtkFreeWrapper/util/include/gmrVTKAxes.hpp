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
 * XYZ軸の作成
 *
 */
#ifndef _GMRVTKAXES_HPP
#define _GMRVTKAXES_HPP

#include "gmrVTK.hpp"
#include "gmrVTKDefs.hpp"

/** 
 * @brief XYZ軸の作成クラス
 *
 */

class gmr_EXPORT gmrVTKAxes
{
	double axesScale_;
	double Radius_;
	double Origin_[3];
	bool Symmetric_;
	int NumberOfSides_;	//円柱近似多角形辺数

	vtkAxes *axes_;
	vtkTubeFilter *axesTubes_;
	vtkPolyDataMapper *axesMapper_;
	vtkActor *axesActor_;

	void Flush(void);

public:
	gmrVTKAxes();
	virtual ~gmrVTKAxes();

	/** 座標軸の原点設定
	 *
	 * @param [in] x X座標
	 * @param [in] y Y座標
	 * @param [in] z Z座標
	*/
	void SetOrigin( double x, double y, double z)
	{
		Origin_[0] = x;
		Origin_[1] = y;
		Origin_[2] = z;
	}

	/** 座標軸の長さ設定
	 *
	 * @param [in] len 座標軸の長さ
	 */
	void SetLength(double len)
	{
		axesScale_ = len;
	}

	/** 座標軸の円柱半径の設定
	 *
	 * @param [in] r 円柱半径
	 *
	 */
	void SetRadius( double r)
	{
		Radius_ = r;
	}

	/** 原点を中心に＋側、－側両方に軸を作成
	 *
	 */
	void SymmetricOn()
	{
		Symmetric_ = true;
	}

	/** 原点を中心に＋側片方に軸を作成
	 *
	 */
	void SymmetricOff()
	{
		Symmetric_ = false;
	}

	/** アクターの取得
	 *
	 */
	vtkActor* GetActor();

};

#endif



