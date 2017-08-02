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
 * ポリライン（折れ線）
 */
#ifndef _GMRVTKPOLYLINE_HPP
#define _GMRVTKPOLYLINE_HPP

#include "gmrVTK.hpp"
#include "gmrVTKDefs.hpp"

/** 
 * @brief ポリライン（折れ線）クラス
 *
 */

class gmr_EXPORT gmrVTKPolyline  : public gmrVTK
{
public:
	gmrVTKPolyline();
	virtual ~gmrVTKPolyline();

	/** 折れ線の構成点追加設定
	 *
	 * @param [in] point 構成点座標配列
	 *
	 */
	void SetPoint(double* point);
	

	/** 折れ線の構成点設定終了
	 *
	 */
	virtual void Flush()
	{
		dataset_->InsertNextCell(VTK_POLY_LINE,idlist_);
		dataset_->SetPoints(points_);
	}
	virtual vtkActor* GetActor();


};

#endif
