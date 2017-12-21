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
#ifndef _GMRVTK_HPP
#define _GMRVTK_HPP
#define _CRT_SECURE_NO_DEPRECATE
#include <iostream>
#include <random>

#include "vtkCellArray.h"
#include "vtkQuadric.h"
#include "vtkSampleFunction.h"
#include "vtkContourFilter.h"
#include "vtkOutlineFilter.h"
#include "vtkPolyDataMapper.h"
#include "vtkActor.h"
#include "vtkProperty.h"
#include "vtkRenderWindow.h"
#include "vtkRenderer.h"
#include "vtkRenderWindowInteractor.h"
#include "vtkImageData.h"
#include "vtkImplicitDataSet.h"
#include "vtkStructuredPoints.h"
#include "vtkUnstructuredGrid.h"
#include "vtkPointData.h"
#include "vtkDataSetMapper.h"
#include "vtkGlyph3D.h"
#include "vtkSphereSource.h"
#include "vtkPointSetAlgorithm.h"
#include "vtkPointSet.h"
#include "vtkVertex.h"
#include "vtkPoints.h"
#include "vtkPolyLine.h"
#include "vtkFloatArray.h"
#include "vtkSTLReader.h"
#include "vtkSphere.h"
#include "vtkClipPolyData.h"
#include "vtkPLY.h"
#include "vtkPLYReader.h"
#include "vtkInteractorStyleTrackballCamera.h"
#include "vtkInteractorStyleJoystickCamera.h"
#include "vtkInteractorStyleTerrain.h"
#include "vtkInteractorStyleRubberBandZoom.h"
//#include "vtk3DSImporter.h"

#include "vtkCamera.h"
#include "vtkOBJReader.h"
#include "vtkLookupTable.h"
#include "vtkImageMapToColors.h"
#include "vtkImageActor.h"
#include "vtkScalarBarActor.h"
#include "vtkLookupTable.h"
#include "vtkTextActor.h"
#include "vtkTextActor3D.h"
#include "vtkTextMapper.h"
#include "vtkTextProperty.h"
#include "vtkWarpScalar.h"
#include "vtkPolyDataNormals.h"

#include "vtkWindowToImageFilter.h"
#include "vtkImageViewer.h"
#include "vtkImageWriter.h" 
#include "vtkPNGWriter.h"
#include "vtkBMPWriter.h"
#include "vtkJPEGWriter.h"
#include "vtkAVIWriter.h"

#include "vtkFloatArray.h"
#include "vtkXYPlotActor.h"
#include "vtkDataObject.h"
#include "vtkFieldData.h"
#include "vtkProperty2D.h"

#include "vtkAxes.h"
#include "vtkTubeFilter.h"

#include "vtkVectorText.h"
#include "vtkFollower.h"
#include "vtkCaptionActor2D.h"

#include "vtkCommand.h"
#include "vtkPointPicker.h"
#include "vtkCellPicker.h"
#include "vtkWorldPointPicker.h"

#include <vtkSmartPointer.h>
#include <vtkGraphicsFactory.h>
//#include <vtkImagingFactory.h>

#include "vtkOBJExporter.h"
#include "vtkPLYWriter.h"
#include "vtkSTLWriter.h"
#include "vtkX3DExporter.h"
#include "vtkVRMLExporter.h"
#include "vtkVRMLImporter.h"

#include <vtkCleanPolyData.h>
#include <vtkDecimatePro.h>
#include <vtkPolyDataConnectivityFilter.h>

#include <vtkCurvatures.h>
#include <vtkColorSeries.h>
#include <vtkColorTransferFunction.h>

#include <vtkFillHolesFilter.h>
#include <vtkSmoothPolyDataFilter.h>
#include <vtkWindowedSincPolyDataFilter.h>

#include <vtkSurfaceReconstructionFilter.h>
#include <vtkReverseSense.h>

#include "gmrVTKDefs.hpp"

//#include "vtkAutoInit.h"
////VTK_MODULE_INIT(vtkRenderingOpenGL);
////VTK_MODULE_INIT(vtkInteractionStyle);
////VTK_MODULE_INIT(vtkRenderingFreeType);
//#define vtkRenderingCore_AUTOINIT 4(vtkInteractionStyle,vtkRenderingFreeType,vtkRenderingFreeTypeOpenGL,vtkRenderingOpenGL)
//#define vtkRenderingVolume_AUTOINIT 1(vtkRenderingVolumeOpenGL)

//VTK6.3
//#include "vtkAutoInit.h"
//VTK_MODULE_INIT(vtkRenderingOpenGL);
//VTK_MODULE_INIT(vtkInteractionStyle);
//VTK_MODULE_INIT(vtkRenderingFreeType);
//VTK_MODULE_INIT(vtkRenderingVolumeOpenGL);

//VTK7.0
#include "vtkAutoInit.h"
VTK_MODULE_INIT(vtkRenderingOpenGL2);
VTK_MODULE_INIT(vtkInteractionStyle);
VTK_MODULE_INIT(vtkRenderingFreeType);
VTK_MODULE_INIT(vtkRenderingVolumeOpenGL2);

/** 
 * @brief �x�[�X�N���X�i��{�}�`�j
 *
 */
class gmr_EXPORT gmrVTK
{
protected:
	vtkIndent ind_;
	vtkUnstructuredGrid  *dataset_;
	vtkIdList *idlist_;
	vtkPoints *points_;

	vtkActor* actor_;
	vtkDataSetMapper *mapper_;
	virtual void CreateMapper();

	vtkFloatArray* Scalar_;
	vtkWarpScalar* WarpScalar_;

	double Size_;
	double Color_[4];
	double DiffuseColor_[4];
	double ScalarMin_;
	double ScalarMax_;
public:
	gmrVTK();
	virtual ~gmrVTK();

	/** ��{�}�`�̃T�C�Y�̐ݒ�
	 *
	 * @param[in] size �s�N�Z���T�C�Y
	 */
	void SetSize(double size)
	{
		Size_ = size;
	}

	/** ��{�}�`�̐F��ݒ肷��
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

	/** ��{�}�`�̕\�ʊg�U���̐ݒ�
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

	/** �f�[�^�Z�b�g�̎擾
	 *
	 * @return �f�[�^�Z�b�g
	 *
	 */
	vtkUnstructuredGrid* GetDataSet(void) const 
	{
		return dataset_;
	}

	/** �ݒ肳��Ă����{�}�`���̎擾
	 *
	 * @return ��{�}�`��
	 */
	int GetDataNum() const
	{
		return points_->GetNumberOfPoints();
		//return dataset_->GetNumberOfPoints();
	}

	/** �f�[�^�Z�b�g�̒ǉ��I��
	 *
	 */
	virtual void Flush(){ ;}

	/** �A�N�^�[�̎擾
	 *
	 */
	virtual vtkActor* GetActor() = 0;


	/** �X�J���[�̐ݒ�
	 *
	 * @param [in] scalar �X�J���[�z��
	 */
	void SetScalar( double* scalar );
	
	/** �X�J���[�̍ŏ��l
	 *
	 * @return �X�J���[�̍ŏ��l
	 */
	double GetScalarMin() const
	{
		return ScalarMin_;
	}

	/** �X�J���[�̍ő�l
	 *
	 * @return �X�J���[�̍ő�l
	 */
	double GetScalarMax() const
	{
		return ScalarMax_;
	}


	vtkProperty* GetProperty()
	{
		return GetActor()->GetProperty();
	}
	
	vtkWarpScalar* GetWarpScalar()
	{
		return WarpScalar_;
	}

	vtkDataSetMapper* GetMapper()
	{
		return mapper_;
	}

};

#endif
