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
 * ポリゴンデータ出力（抽象クラス）
 */
#ifndef _GMRVTKEXPORT_HPP
#define _GMRVTKEXPORT_HPP

#include "gmrVTK.hpp"
#include "gmrVTKRender.hpp"
#include "gmrVTKDefs.hpp"

class gmrVTKExportSTL;
class gmrVTKExportPLY;
class gmrVTKExportOBJ;
class gmrVTKExportX3D;
class gmrVTKExportVRML;

/** 
 * @brief ポリゴンデータ出力（抽象クラス）
 *
 */

class gmr_EXPORT gmrVTKExport
{
	friend gmrVTKExportSTL;
	friend gmrVTKExportPLY;
	friend gmrVTKExportOBJ;
	friend gmrVTKExportX3D;
	friend gmrVTKExportVRML;


public:
	gmrVTKExport();
	virtual ~gmrVTKExport();
	void SaveFile( gmrVTKRender* renwin, char* filename);
	void SaveFile( vtkAlgorithmOutput* input, char* filename);
};

class gmr_EXPORT gmrVTKExportSTL: public gmrVTKExport
{
	vtkSTLWriter* stlWriter_;

public:
	/** コンストラクタ
	 *
	 */
	gmrVTKExportSTL();
	virtual ~gmrVTKExportSTL();

	/** ファイル保存
	 *
	 * @param [in] input データ->GetOutputPort()
	 * @param [in] filename エクスポートファイル名
	 */
	void SaveFile( vtkAlgorithmOutput* input, char* filename);
	vtkSTLWriter*Get() { return stlWriter_; }
};

class gmr_EXPORT gmrVTKExportPLY: public gmrVTKExport
{
	vtkPLYWriter* plyWriter_;
public:

	/** コンストラクタ
	 *
	 */
	gmrVTKExportPLY();
	virtual ~gmrVTKExportPLY();

	/** ファイル保存
	 *
	 * @param [in] input データ->GetOutputPort()
	 * @param [in] filename エクスポートファイル名
	 */
	void SaveFile( vtkAlgorithmOutput* input, char* filename);
	void SaveFile(vtkAlgorithmOutput* input, char* colro_name, char* filename);
	vtkPLYWriter*Get() { return plyWriter_; }
};

class gmr_EXPORT gmrVTKExportOBJ: public gmrVTKExport
{
	vtkOBJExporter* vtkExporter_;
        
public:
	/** コンストラクタ
	 *
	 * @param [in] filename エクスポートファイル名
	 */
	gmrVTKExportOBJ();
	virtual ~gmrVTKExportOBJ();

	/** ファイル保存
	 *
	 * @param [in] renwin レンダリング（シーン）
	 * @param [in] filename エクスポートファイル名
	 */
	void SaveFile( gmrVTKRender* renwin, char* filename);

	vtkOBJExporter*Get() { return vtkExporter_; }
};

class gmr_EXPORT gmrVTKExportX3D: public gmrVTKExport
{
	vtkX3DExporter* vtkExporter_;
        
public:
	/** コンストラクタ
	 *
	 * @param [in] filename エクスポートファイル名
	 */
	gmrVTKExportX3D();
	virtual ~gmrVTKExportX3D();

	/** ファイル保存
	 *
	 * @param [in] renwin レンダリング（シーン）
	 * @param [in] filename エクスポートファイル名
	 */
	void SaveFile( gmrVTKRender* renwin, char* filename);

};

class gmr_EXPORT gmrVTKExportVRML: public gmrVTKExport
{
	vtkVRMLExporter* vtkExporter_;
        
public:
	/** コンストラクタ
	 *
	 * @param [in] filename エクスポートファイル名
	 */
	gmrVTKExportVRML();
	virtual ~gmrVTKExportVRML();

	/** ファイル保存
	 *
	 * @param [in] renwin レンダリング（シーン）
	 * @param [in] filename エクスポートファイル名
	 */
	void SaveFile( gmrVTKRender* renwin, char* filename);

};

#endif