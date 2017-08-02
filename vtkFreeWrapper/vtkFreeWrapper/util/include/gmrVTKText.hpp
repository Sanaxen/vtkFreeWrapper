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
 * Textクラス
 */
#ifndef _GMRVTKTEXT_HPP
#define _GMRVTKTEXT_HPP

#include "gmrVTK.hpp"
#include "gmrVTKDefs.hpp"

/** 
 * @brief Textクラス
 *
 */

class gmr_EXPORT gmrVTKText
{
	vtkTextProperty *TextProperty_;

	vtkTextActor* actor_;
	vtkTextMapper *mapper_;

	double Size_;
	double Color_[4];
	int Position_[2];

public:
	gmrVTKText();
	virtual ~gmrVTKText();

	/** 文字列の設定
	 *
	 * @param [in] string 文字列
	 *
	 */
	void SetText(const char* string);
	void SetText(const std::string& string)
	{
		SetText(string.c_str());
	}

	/** 文字列の大きさ設定
	 *
	 * @param [in] size 文字列の大きさ
	 *
	 */
	void SetSize(double size)
	{
		Size_ = size;
	}

	/** 文字列の表示位置設定
	 *
	 * @param [in] x 横方向の位置
	 * @param [in] y 縦方向の位置
	 *
	 */
	void SetPosition( int x, int y)
	{
		Position_[0] = x;
		Position_[1] = y;
	}

	/** 文字の色設定
	 *
	 * @param[in] r 赤
	 * @param[in] g 緑
	 * @param[in] b 青
	 */
	void SetColor(double r, double g, double b)
	{
		Color_[0] = r;
		Color_[1] = g;
		Color_[2] = b;
	}

	/** アクターの取得
	 *
	 */
	virtual vtkActor* GetActor();


	vtkTextProperty* GetTextProperty()
	{
		return TextProperty_;
	}

	vtkProperty* GetProperty()
	{
		return GetActor()->GetProperty();
	}

};

/** 
 * @brief 3DTextクラス
 *
 */
class gmr_EXPORT gmrVTKText3D
{
	vtkFollower* actor_;
	vtkPolyDataMapper *mapper_;
	vtkVectorText* vectorText_;

	double Size_[3];
	double Color_[4];
	double Position_[3];
	double Orientation_[3];

public:
	gmrVTKText3D();
	virtual ~gmrVTKText3D();

	/** 文字列の設定
	 *
	 * @param [in] string 文字列
	 *
	 */
	void SetText(const char* string);
	void SetText(const std::string& string)
	{
		SetText(string.c_str());
	}
	
	/** 文字列の大きさ設定
	 *
	 * @param [in] sizex X方向
	 * @param [in] sizey Y方向
	 * @param [in] sizez Z方向
	 *
	 */
	void SetSize(double sizex, double sizey, double sizez)
	{
		Size_[0] = sizex;
		Size_[1] = sizey;
		Size_[2] = sizez;
	}

	/** 文字列の表示位置設定
	 *
	 * @param [in] x X座標
	 * @param [in] y Y座標
	 * @param [in] z Z座標
	 *
	 */
	void SetPosition( double x, double y, double z)
	{
		Position_[0] = x;
		Position_[1] = y;
		Position_[2] = z;
	}

	/** 文字列の表示角度設定
	 *
	 * @param [in] x X軸回転角度
	 * @param [in] y Y軸回転角度
	 * @param [in] z Z軸回転角度
	 *
	 */
	void SetOrientation( double x, double y, double z)
	{
		Orientation_[0] = x;
		Orientation_[1] = y;
		Orientation_[2] = z;
	}

	/** 文字の色設定
	 *
	 * @param[in] r 赤
	 * @param[in] g 緑
	 * @param[in] b 青
	 */
	void SetColor(double r, double g, double b)
	{
		Color_[0] = r;
		Color_[1] = g;
		Color_[2] = b;
	}

	/** アクターの取得
	 *
	 */
	vtkActor* GetActor();
};
#endif

