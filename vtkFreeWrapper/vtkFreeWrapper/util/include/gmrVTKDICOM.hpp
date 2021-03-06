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
#ifndef _GMRVTKDICOM_HPP
#define _GMRVTKDICOM_HPP

#include "gmrVTK.hpp"
#include "gmrVTKDefs.hpp"
#include "gmrVTKRender.hpp"
#include "vtkDICOMImageReader.h"
#include "vtkMarchingCubes.h"

#include "vtkRenderWindow.h"
#include "vtkCamera.h"
#include "vtkPiecewiseFunction.h "
#include "vtkVolumeProperty.h"
#include "vtkRenderer.h"
#include "vtkDICOMImageReader.h"
#include "vtkRenderWindowInteractor.h"

//VTK_VER > 810
//#include "vtkVolumeRayCastCompositeFunction.h"
//#include "vtkVolumeRayCastMapper.h"

#include "vtkFixedPointVolumeRayCastMapper.h"
#include "vtkColorTransferFunction.h"
#include "vtkProp.h"
#include "vtkImageData.h"
#include "vtkSmartPointer.h"
#include "vtkPoints.h"
#include "vtkWin32RenderWindowInteractor.h"
#include "vtkGPUVolumeRayCastMapper.h"
#include "vtkOpenGLGPUVolumeRayCastMapper.h"
#include "vtkLODProp3D.h"
#include "vtkDecimatePro.h"
#include "vtkSmoothPolyDataFilter.h"
#include "vtkPolyDataConnectivityFilter.h"

/** 
 * @brief DICOM Viewerクラス
 *
 *
	@note sample code
	@code

	gmrVTKRender* render = new gmrVTKRender;
	gmrVTKDICOM *reader = new gmrVTKDICOM;

	reader->SetDirectoryName("data\\PANORAMIX\\Abdomen 1ABD_PEL_AAA\\Abd-Pel w-c  3.0  B30f");
	reader->LoadImageData();

	render->AddActor( reader->GetActor());

	gmrVTKOutline *outlineData = new gmrVTKOutline(NULL);
	outlineData->GetOutlineFilter()->SetInputConnection(reader->GetDICOMImage()->GetOutputPort());
	render->AddActor( outlineData->GetActor());

	render->DefaultRun();
	@endcode
 */
class _volumeColorValue
{
public:
	double x[5];	// x[0]:iso x[1]:R x[2]:G x[3]:B x[4]:α

};
class gmr_EXPORT gmrVTKDICOM
{
    vtkDICOMImageReader *reader_;
	vtkContourFilter *skinExtractor_;
    vtkPolyDataNormals *skinNormals_;
	vtkActor* actor_;
	vtkImageViewer *viewer_;

	double range_[2];
	double FeatureAngle_;

	int ZNum_;

	//Iso surface
	double isovalue;
	vtkSmartPointer<vtkMarchingCubes> surface_;
	vtkSmartPointer<vtkPolyDataMapper> surface_mapper_;
	vtkSmartPointer<vtkActor> surface_actor_;
	vtkSmartPointer<vtkPolyData> mesh_;

	//Volume polygon
	vtkSmartPointer<vtkPolyDataMapper> skinMapper_;

	vtkSmartPointer<vtkVolume> volume_;
	vtkSmartPointer<vtkGPUVolumeRayCastMapper> volumemapper;
	double SampleDistance_;


public:
	int surface_On;


	double& IsoValue()
	{
		return isovalue;
	}

	double& SampleDistance()
	{
		return SampleDistance_;
	}

	vtkSmartPointer<vtkVolume>& GetVolume()
	{
		return volume_;
	}

	vtkSmartPointer<vtkPolyDataMapper>& GetskinMapper()
	{
		return skinMapper_;
	}

	vtkSmartPointer<vtkGPUVolumeRayCastMapper>& GetVolumeMapper()
	{
		return volumemapper;
	}
	vtkSmartPointer<vtkPolyDataMapper>& GetSurface_Mapper()
	{
		return surface_mapper_;
	}

	vtkSmartPointer<vtkActor>& GetSurfaceActor()
	{
		return surface_actor_;
	}

	vtkSmartPointer<vtkPolyData>& GetMesh()
	{
		return mesh_;
	}

	std::vector<_volumeColorValue> volumeColorSet;
	void AddRGBPoint(double xx, double r, double g, double b, double alp)
	{
		_volumeColorValue c;
		c.x[0] = xx;
		c.x[1] = r;
		c.x[2] = g;
		c.x[3] = b;
		c.x[4] = alp;
		volumeColorSet.push_back(c);
	}

	gmrVTKDICOM();
	virtual ~gmrVTKDICOM();

	/** DICOMファイルのあるディレクトリの設定
	 *
	 * @param [in] DirectoryName ディレクトリ名
	 *
	 */
	void SetDirectoryName(char* DirectoryName);

	/** DICOMイメージデータの全読み込み
	 *
	 */
	void LoadImageData();

	/** DICOMイメージデータのスライス表示
	 *
	 * @param [in] ZSlice Z層インデックス
	 * @param [in] colorWindow colorWindow数
	 * @param [in] colorLevel 閾値color
	 *
	@note sample code
	@code
		gmrVTKDICOM *reader = new gmrVTKDICOM;
	    
		reader->SetDirectoryName("data\\PANORAMIX\\Abdomen 1ABD_PEL_AAA\\Abd-Pel w-c  3.0  B30f");
		reader->LoadImageData();

		int znum = reader->GetZnum();

		for (int i=0;i<=znum;i++)
		{
			gmrVTKCaptureBMP* Capture = new gmrVTKCaptureBMP;
			Capture->SetInput(reader->GetImageViewer());
			Capture->SetFileName("Capture");

			reader->ViewerZSlice(i, 400, 128);
			Capture->SetInput(reader->GetImageViewer());
			Capture->Capture(i);
			delete Capture;
		}

		delete reader; 
		@endcode
	 */
	void ViewerZSlice(int ZSlice, int colorWindow, int colorLevel);

	vtkActor* GetActor();

	vtkDICOMImageReader* GetDICOMImage()
	{
		return reader_;
	}

	/** スライス数の取得
	 *
	 * @return スライス数
	 *
	 */
	int GetZnum()
	{
		return ZNum_;
	}

	vtkImageViewer* GetImageViewer()
	{
		return viewer_;
	}

	vtkContourFilter* GetSkin()
	{
		return skinExtractor_;
	}
};

#endif


