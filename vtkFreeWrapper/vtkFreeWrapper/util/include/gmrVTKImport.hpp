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
 * 外部（ポリゴン）データ読み込み（抽象クラス）
 */
#ifndef _GMRVTKIMPORT_HPP
#define _GMRVTKIMPORT_HPP

#include "gmrVTK.hpp"
#include "gmrVTKDefs.hpp"

class gmrVTKImportSTL;
class gmrVTKImportPLY;
class gmrVTKImportOBJ;
class gmrVTKImportVRML;

/** 
 * @brief 外部（ポリゴン）データ読み込み（抽象クラス）
 *
 */

class gmr_EXPORT gmrVTKImport
{
	friend gmrVTKImportSTL;
	friend gmrVTKImportPLY;
	friend gmrVTKImportOBJ;
	friend gmrVTKImportVRML;

	vtkActor* actor_;
	double Size_;
	double Color_[4];
	double DiffuseColor_[4];
	vtkPolyDataMapper *stlMapper_;
	vtkImplicitDataSet* ImplicitDataSet_;

	virtual void LoadFile(char* filename) = 0;

public:
	gmrVTKImport();
	virtual ~gmrVTKImport();

	/** 図形のサイズの設定
	 *
	 * @param[in] size ピクセルサイズ
	 */
	void SetSize(double size)
	{
		Size_ = size;
	}

	/** 図形の色を設定する
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

	/** 図形の表面拡散光の設定
	 *
	 * @param[in] r 赤
	 * @param[in] g 緑
	 * @param[in] b 青
	 */
	void SetDiffuseColor(double r, double g, double b)
	{
		DiffuseColor_[0] = r;
		DiffuseColor_[1] = g;
		DiffuseColor_[2] = b;
	}
	void GetDiffuseColor(double& r, double& g, double& b)
	{
		r = DiffuseColor_[0];
		g = DiffuseColor_[1];
		b = DiffuseColor_[2];
	}
	vtkActor* GetActor();

};

/** 
 * @brief 外部（ポリゴン）STLデータ読み込み
 *
 @note sample code
 @code
	gmrVTKImportSTL* polygon = new gmrVTKImportSTL("data\\bunny.stl");

	gmrVTKRender* render = new gmrVTKRender;

	render->InteractorStyleTrackballCamera();
	render->AddActor(polygon->GetActor());

	gmrVTKScalaBar* scalarBar = new gmrVTKScalaBar;
	scalarBar->SetScalarMinMax(0, 360);
	for (int i = 0; i < 360; i += 1)
	{
		// Render the image and rotate the active camera by one degree
		render->Run();
		render->GetRenderer()->GetActiveCamera()->Azimuth(1);
		render->GetRenderer()->GetActiveCamera()->Roll(1);

		double rgb[3];
		scalarBar->GetLookupTable()->GetColor((double)i, rgb);
		polygon->SetDiffuseColor(rgb[0], rgb[1], rgb[2]);

		render->RemoveActor(polygon->GetActor());
		render->AddActor(polygon->GetActor());
	} 
	@endcode
 */

class gmr_EXPORT gmrVTKImportSTL: public gmrVTKImport
{
	void LoadFile( char* filename);
	vtkSTLReader* STL_;

public:
	/** コンストラクタ
	 *
	 * @param [in] filename インポートファイル名
	 */
	gmrVTKImportSTL(char* filename);
	virtual ~gmrVTKImportSTL();

	vtkSTLReader* Get()
	{
		return STL_;
	}
};

/** 
 * @brief 外部（ポリゴン）Stanford PLYデータ読み込み
 *
 @note sample code
 @code
	gmrVTKImportPLY* polygon = new gmrVTKImportPLY("data\\dragon_vrip.ply");

	gmrVTKRender* render = new gmrVTKRender;

	render->InteractorStyleTrackballCamera();
	render->AddActor(polygon->GetActor());

	render->DefaultRun(); 
 @endcode
 */
class gmr_EXPORT gmrVTKImportPLY: public gmrVTKImport
{
	void LoadFile( char* filename);
	vtkPLYReader* PLY_;

public:

	/** コンストラクタ
	 *
	 * @param [in] filename インポートファイル名
	 */
	gmrVTKImportPLY(char* filename);
	virtual ~gmrVTKImportPLY();
	vtkPLYReader* Get()
	{
		return PLY_;
	}

};

/** 
 * @brief 外部（ポリゴン）OBJデータ読み込み
 *
 @note sample code
 @code
 	gmrVTKImportOBJ* polygon = new gmrVTKImportOBJ("data\\Sculpture._obj");

	gmrVTKRender* render = new gmrVTKRender;

	render->InteractorStyleTrackballCamera();
	render->AddActor(polygon->GetActor());

	render->DefaultRun();
 @endcode
 */
class gmr_EXPORT gmrVTKImportOBJ: public gmrVTKImport
{
	void LoadFile( char* filename);
	vtkOBJReader* OBJ_;

public:
	/** コンストラクタ
	 *
	 * @param [in] filename インポートファイル名
	 */
	gmrVTKImportOBJ(char* filename);
	virtual ~gmrVTKImportOBJ();

	vtkOBJReader* Get()
	{
		return OBJ_;
	}

	bool mat_color_use;
	double mat_color[3];
};

/** 
 * @brief 外部（ポリゴン）VRMLデータ読み込み
 *
 @note sample code
 @code
 	gmrVTKImportVRML* polygon = new gmrVTKImportVRML("data\\Sculpture.wrl");

	gmrVTKRender* render = new gmrVTKRender;

	render->InteractorStyleTrackballCamera();
	render->AddActor(polygon->GetActor());

	render->DefaultRun();
 @endcode
 */
class gmr_EXPORT gmrVTKImportVRML: public gmrVTKImport
{
	void LoadFile( char* filename);
	vtkVRMLImporter* VRML_;

public:
	/** コンストラクタ
	 *
	 * @param [in] filename インポートファイル名
	 */
	gmrVTKImportVRML(char* filename);
	virtual ~gmrVTKImportVRML();
	vtkVRMLImporter* Get()
	{
		return VRML_;
	}
};
#endif