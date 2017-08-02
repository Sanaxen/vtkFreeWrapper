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
 * Pickerの作成
 *
 */
#ifndef _GMRVTKPICKER_HPP
#define _GMRVTKPICKER_HPP

#include "gmrVTK.hpp"
#include "gmrVTKDefs.hpp"
#include "gmrVTKCommand.hpp"
#include "gmrVTKRender.hpp"


/** 
 * @brief gmrVTKCallbackPointPickクラス
 * - PointPicker用のサンプルcallbackクラス
 */
class gmrVTKCallbackPointPick : public gmrVTKCommand
{
public:
        gmrVTKCallbackPointPick() {;};
        
		static gmrVTKCallbackPointPick *New() 
		{
			return new gmrVTKCallbackPointPick;
		}

        virtual void Execute(vtkObject *caller, unsigned long, void*);
};



/** 
 * @brief gmrVTKCallbackCellPickクラス
 * - CellPicker用のサンプルcallbackクラス
 *
 */
class gmrVTKCallbackCellPick : public gmrVTKCommand
{
public:
        gmrVTKCallbackCellPick() {;};

        static gmrVTKCallbackCellPick *New() {
			return new gmrVTKCallbackCellPick; 
		}

        virtual void Execute(vtkObject *caller, unsigned long, void*);
};


/** 
 * @brief gmrVTKCallbackWorldPointPickクラス
 * - WorldPointPick用のサンプルcallbackクラス
 *
 */
class gmrVTKCallbackWorldPointPick : public gmrVTKCommand
{
public:
        gmrVTKCallbackWorldPointPick() {;};

        static gmrVTKCallbackWorldPointPick *New() {
			return new gmrVTKCallbackWorldPointPick; 
		}

        virtual void Execute(vtkObject *caller, unsigned long, void*);
};

/** 
 * @brief Pickerクラス
 *
 */
class gmr_EXPORT gmrVTKPicker
{
	double tol_;			///< ピック・トレランス

	gmrVTKRender* render_;

	vtkPicker* picker_;			///< ピッカー
	gmrVTKCommand* callback_;	///< callbackクラスへのポインター

	double pos_[3];				///< ピック位置(画面のX,Y,Z座標)
	double wpos_[3];			///< ピック位置X,Y,Z世界座標
	int pointId_;		///< ピックした点のID(PointPicker(vtkCallbackPointPickクラス)が取得した値
	vtkActor* actor_;	///< ピックしたActorへのポインタ
	int succed_;		///< ピックできなかった場合=0

	void SetRender(gmrVTKRender* render);
	void SetPicker(vtkPicker* picker);
	void SetCallback(gmrVTKCommand* callback);

protected:

public:
	gmrVTKPicker();
	virtual ~gmrVTKPicker();

	void SetCondition(gmrVTKRender* render, vtkPicker* picker, gmrVTKCommand* callback);


	/** ピックした位置における情報の記録
	 *
	 */
	void SetPositionInfo(int succed, double* pos, double* wpos, int id, vtkActor* actor);

	/** ピックした位置における情報の取得
	 *
	 */
	void GetPositionInfo(int& succed, double* pos, double* wpos, int& id, vtkActor** actor);



	/** vtkPickerインスタンスの取得
	 *
	 * @retval vtkPickerインスタンス
	 *
	 */
	vtkPicker* GetPicker()
	{
		return picker_;
	}


	/** gmrVTKCommandインスタンスの取得
	 *
	 * @retval gmrVTKCommandインスタンス
	 *
	 */
	gmrVTKCommand* GetCallback()
	{
		return callback_;
	}
};


/** 
 * @brief PointPickerクラス
 *
 */
class gmr_EXPORT gmrVTKPointPicker : public gmrVTKPicker
{
public:
	gmrVTKPointPicker(gmrVTKRender* render);
	virtual ~gmrVTKPointPicker();
};


/** 
 * @brief CellPickerクラス
 *
 */
class gmr_EXPORT gmrVTKCellPicker : public gmrVTKPicker
{
public:
	gmrVTKCellPicker(gmrVTKRender* render);
	virtual ~gmrVTKCellPicker();

};

/** 
 * @brief WorldPointPickerクラス
 *
 */
class gmr_EXPORT gmrVTKWorldPointPicker : public gmrVTKPicker
{
public:
	gmrVTKWorldPointPicker(gmrVTKRender* render);
	virtual ~gmrVTKWorldPointPicker();

};

#endif