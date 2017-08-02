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
 * 形状包含BOXを作成する
 *
 */
#ifndef _GMRVTKOUTLINE_HPP
#define _GMRVTKOUTLINE_HPP

#include "gmrVTK.hpp"
#include "gmrVTKDefs.hpp"

/** 
 * @brief 形状包含BOX作成クラス
 *
 */
class gmr_EXPORT gmrVTKOutline
{
	vtkOutlineFilter *outline_;
	vtkUnstructuredGrid  *dataset_;

	vtkActor* actor_;
	vtkDataSetMapper *mapper_;
	void CreateMapper(void);

	double Size_;
	double Color_[4];
	double DiffuseColor_[4];

public:
	/** コンストラクタ
	 *
	 * @param [in] dataset データセットのポインタ
	 *
	 */
	gmrVTKOutline(vtkUnstructuredGrid  *dataset);
	virtual ~gmrVTKOutline();
	
	/** アクターの取得
	 *
	 */
	vtkActor* GetActor();

	vtkOutlineFilter* GetOutlineFilter()
	{
		return outline_;
	}
};

#endif