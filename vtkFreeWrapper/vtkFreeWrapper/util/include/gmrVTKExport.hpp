/*
 * VTK���ȒP�Ɂi�H�j�g�����߂̊ȒP�N���X���C�u����
 * Copyright (c) Sanaxen
 *
 *
 * Kitware Inc - Leaders in Visualization Technology 
 * Copyright (c) 1993-2006 Ken Martin, Will Schroeder, Bill Lorensen 
 * All rights reserved.
 *
 */
/*
 * �|���S���f�[�^�o�́i���ۃN���X�j
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
 * @brief �|���S���f�[�^�o�́i���ۃN���X�j
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
	/** �R���X�g���N�^
	 *
	 */
	gmrVTKExportSTL();
	virtual ~gmrVTKExportSTL();

	/** �t�@�C���ۑ�
	 *
	 * @param [in] input �f�[�^->GetOutputPort()
	 * @param [in] filename �G�N�X�|�[�g�t�@�C����
	 */
	void SaveFile( vtkAlgorithmOutput* input, char* filename);
	vtkSTLWriter*Get() { return stlWriter_; }
};

class gmr_EXPORT gmrVTKExportPLY: public gmrVTKExport
{
	vtkPLYWriter* plyWriter_;
public:

	/** �R���X�g���N�^
	 *
	 */
	gmrVTKExportPLY();
	virtual ~gmrVTKExportPLY();

	/** �t�@�C���ۑ�
	 *
	 * @param [in] input �f�[�^->GetOutputPort()
	 * @param [in] filename �G�N�X�|�[�g�t�@�C����
	 */
	void SaveFile( vtkAlgorithmOutput* input, char* filename);
	void SaveFile(vtkAlgorithmOutput* input, char* colro_name, char* filename);
	vtkPLYWriter*Get() { return plyWriter_; }
};

class gmr_EXPORT gmrVTKExportOBJ: public gmrVTKExport
{
	vtkOBJExporter* vtkExporter_;
        
public:
	/** �R���X�g���N�^
	 *
	 * @param [in] filename �G�N�X�|�[�g�t�@�C����
	 */
	gmrVTKExportOBJ();
	virtual ~gmrVTKExportOBJ();

	/** �t�@�C���ۑ�
	 *
	 * @param [in] renwin �����_�����O�i�V�[���j
	 * @param [in] filename �G�N�X�|�[�g�t�@�C����
	 */
	void SaveFile( gmrVTKRender* renwin, char* filename);

	vtkOBJExporter*Get() { return vtkExporter_; }
};

class gmr_EXPORT gmrVTKExportX3D: public gmrVTKExport
{
	vtkX3DExporter* vtkExporter_;
        
public:
	/** �R���X�g���N�^
	 *
	 * @param [in] filename �G�N�X�|�[�g�t�@�C����
	 */
	gmrVTKExportX3D();
	virtual ~gmrVTKExportX3D();

	/** �t�@�C���ۑ�
	 *
	 * @param [in] renwin �����_�����O�i�V�[���j
	 * @param [in] filename �G�N�X�|�[�g�t�@�C����
	 */
	void SaveFile( gmrVTKRender* renwin, char* filename);

};

class gmr_EXPORT gmrVTKExportVRML: public gmrVTKExport
{
	vtkVRMLExporter* vtkExporter_;
        
public:
	/** �R���X�g���N�^
	 *
	 * @param [in] filename �G�N�X�|�[�g�t�@�C����
	 */
	gmrVTKExportVRML();
	virtual ~gmrVTKExportVRML();

	/** �t�@�C���ۑ�
	 *
	 * @param [in] renwin �����_�����O�i�V�[���j
	 * @param [in] filename �G�N�X�|�[�g�t�@�C����
	 */
	void SaveFile( gmrVTKRender* renwin, char* filename);

};

#endif