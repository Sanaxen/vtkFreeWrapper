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
 * ポリゴン（多面体）
 */
#ifndef _GMRVTKPOLYGON_HPP
#define _GMRVTKPOLYGON_HPP

#include "gmrVTK.hpp"
#include "gmrVTKDefs.hpp"

/** 
 * @brief ポリゴン（多面体）クラス
 *
 */

class gmr_EXPORT gmrVTKPolygon  : public gmrVTK
{
	int vertexNum_;
	vtkIdType* Indextable_;

public:
	gmrVTKPolygon();
	virtual ~gmrVTKPolygon();


	/** 三角形の設定
	 *
	 * @param [in] vtx1 頂点1のインデックス
	 * @param [in] vtx2 頂点2のインデックス
	 * @param [in] vtx3 頂点3のインデックス
	 */
	void SetTriangle(int vtx1, int vtx2, int vtx3);

	/** 頂点の設定
	 *
	 * @param [in] index 頂点のインデックス値
	 * @param [in] vtx1 頂点の座標配列[3]
	 *
	 */
	void SetVertex(int index, double* vtx1);

	/** 頂点数の設定
	 *
	 * @param [in] num 頂点数
	 *
	 */
	void SetVertexNum( int num )
	{
		vertexNum_ = num;
		Indextable_ = new vtkIdType[num];
	}

	/** 頂点座標の取得
	 *
	 * @param [in] index 頂点のインデックス
	 * @param [out] vtx 頂点の座標配列
	 *
	 */
	void GetVertex(int index, double vtx[3])
	{
		points_->GetPoint(Indextable_[index],vtx);
	}


	/** 多面体設定終了
	 *
	 */
	virtual void Flush()
	{
		dataset_->SetPoints(points_);
		dataset_->ComputeBounds();
	}
	
	virtual vtkActor* GetActor();

};

#endif