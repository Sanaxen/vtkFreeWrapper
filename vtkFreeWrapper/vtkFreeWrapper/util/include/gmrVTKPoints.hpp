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
 * 点列（点群）
 */
#ifndef _GMRVTKPOINTS_HPP
#define _GMRVTKPOINTS_HPP

#include "gmrVTK.hpp"

/** 
 * @brief 点列（点群）クラス
 *
 */
class gmr_EXPORT gmrVTKPoints : public gmrVTK
{
public:
	gmrVTKPoints();
	virtual ~gmrVTKPoints();

	/** 点座標の追加
	 *
	 * @param [in] point 点の座標配列
	 *
	 */
	void SetPoint(double* point);

	/** 点座標の追加終了
	 *
	 */
	virtual void Flush()
	{
		dataset_->InsertNextCell(VTK_VERTEX,idlist_);
		dataset_->SetPoints(points_);
	}

	virtual vtkActor* GetActor();

};

#endif

