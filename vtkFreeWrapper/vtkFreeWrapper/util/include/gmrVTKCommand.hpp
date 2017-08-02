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
 * コールバックの作成
 *
 */
#ifndef _GMRVTKCOMMAND_HPP
#define _GMRVTKCOMMAND_HPP

#include "gmrVTK.hpp"
#include "gmrVTKDefs.hpp"

class gmrVTKRender;
class gmrVTKPicker;

/** 
 * @brief  コールバック・ベースクラスの作成
 *
 */
class gmr_EXPORT gmrVTKCommand : public vtkCommand
{
public:
	gmrVTKCommand();
	virtual ~gmrVTKCommand();


	/** コールバックが反応するウィンドウの設定
	 *
	 * @param [in] ren ウィンドウ
	 *
	 */
    void SetRenderer(gmrVTKRender *ren);


	/** コールバックが反応するPickを行うウィンドウの設定
	 *
	 * @param [in] ren ウィンドウ
	 * @param [in] picker ピッカー
	 *
	 */
	void SetCondition(gmrVTKRender *ren, gmrVTKPicker *picker);

	/** コールバックが反応するウィンドウの取得
	 *
	 * @retval コールバックが反応するウィンドウ
	 *
	 */
	gmrVTKRender* GetRenderer();


	/** コールバックが反応するピッカーの取得
	 *
	 * @retval コールバックが反応するピッカー
	 *
	 */
	gmrVTKPicker* GetPicker();

private:
    void SetPicker(gmrVTKPicker *picker);
	gmrVTKRender *ren_;
	gmrVTKPicker *picker_;

};


#endif