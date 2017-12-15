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
 * �O���i�|���S���j�f�[�^�ǂݍ��݁i���ۃN���X�j
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
 * @brief �O���i�|���S���j�f�[�^�ǂݍ��݁i���ۃN���X�j
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

	/** �}�`�̃T�C�Y�̐ݒ�
	 *
	 * @param[in] size �s�N�Z���T�C�Y
	 */
	void SetSize(double size)
	{
		Size_ = size;
	}

	/** �}�`�̐F��ݒ肷��
	 *
	 * @param[in] r ��
	 * @param[in] g ��
	 * @param[in] b ��
	 */
	void SetColor(double r, double g, double b)
	{
		Color_[0] = r;
		Color_[1] = g;
		Color_[2] = b;
	}

	/** �}�`�̕\�ʊg�U���̐ݒ�
	 *
	 * @param[in] r ��
	 * @param[in] g ��
	 * @param[in] b ��
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
 * @brief �O���i�|���S���jSTL�f�[�^�ǂݍ���
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
	/** �R���X�g���N�^
	 *
	 * @param [in] filename �C���|�[�g�t�@�C����
	 */
	gmrVTKImportSTL(char* filename);
	virtual ~gmrVTKImportSTL();

	vtkSTLReader* Get()
	{
		return STL_;
	}
};

/** 
 * @brief �O���i�|���S���jStanford PLY�f�[�^�ǂݍ���
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

	/** �R���X�g���N�^
	 *
	 * @param [in] filename �C���|�[�g�t�@�C����
	 */
	gmrVTKImportPLY(char* filename);
	virtual ~gmrVTKImportPLY();
	vtkPLYReader* Get()
	{
		return PLY_;
	}

};

/** 
 * @brief �O���i�|���S���jOBJ�f�[�^�ǂݍ���
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
	/** �R���X�g���N�^
	 *
	 * @param [in] filename �C���|�[�g�t�@�C����
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
 * @brief �O���i�|���S���jVRML�f�[�^�ǂݍ���
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
	/** �R���X�g���N�^
	 *
	 * @param [in] filename �C���|�[�g�t�@�C����
	 */
	gmrVTKImportVRML(char* filename);
	virtual ~gmrVTKImportVRML();
	vtkVRMLImporter* Get()
	{
		return VRML_;
	}
};
#endif