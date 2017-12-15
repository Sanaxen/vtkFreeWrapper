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
 * DICOM
 *
 */
#include "gmrVTKDICOM.hpp"

gmrVTKDICOM::gmrVTKDICOM()
{
	reader_ = vtkDICOMImageReader::New();
    skinExtractor_ = vtkContourFilter::New();
    skinNormals_ = vtkPolyDataNormals::New();
    skinMapper_ = vtkSmartPointer<vtkPolyDataMapper>::New();
	viewer_ = vtkImageViewer::New();
	actor_ = NULL;
	surface_ = vtkSmartPointer<vtkMarchingCubes>::New();



	range_[0] = 0.0;
	range_[1] = 255.0;
	FeatureAngle_ = 0.1;
	ZNum_ = 0;
	SampleDistance_ = 1.0;

	surface_On = 0;
	isovalue = -1.0E-32;

	AddRGBPoint(0, 0, 0.2, 0.5, 0.0);
	AddRGBPoint(50, 0, 0.2, 0.5, 0.05);
	AddRGBPoint(60, 238. / 255.0, 211. / 255.0, 193. / 255.0, 0.16);
	AddRGBPoint(100, 250. / 255.0, 242. / 255., 237. / 255., 0.2);
	AddRGBPoint(128, 250. / 255.0, 242. / 255., 237. / 255., 0.25);
	AddRGBPoint(200, 250. / 255.0, 242. / 255., 237. / 255., 0.25);
	AddRGBPoint(300, 250. / 255.0, 242. / 255., 237. / 255., 0.5);
	AddRGBPoint(500, 250. / 255.0, 242. / 255., 237. / 255., 1.0);
	AddRGBPoint(1000, 255. / 255.0, 185. / 255., 185. / 255., 1.0);
	AddRGBPoint(1150, 255. / 255.0, 185. / 255., 185. / 255., 1.0);

	//for (int i = 0; i < volumeColorSet.size(); i++)
	//{
	//	printf("%f,%f,%f,%f,%f\n", volumeColorSet[i].x[0], volumeColorSet[i].x[1], volumeColorSet[i].x[2], volumeColorSet[i].x[3], volumeColorSet[i].x[4]);
	//}
}

gmrVTKDICOM::~gmrVTKDICOM()
{
	if ( reader_ ) reader_->Delete();
	if ( skinExtractor_ ) skinExtractor_->Delete();
	if ( skinNormals_ ) skinNormals_->Delete();
	if ( skinMapper_ ) skinMapper_->Delete();
	if ( actor_ ) actor_->Delete();
	if ( viewer_ ) viewer_->Delete();
}

void gmrVTKDICOM::SetDirectoryName(char* DirectoryName)
{
    reader_->SetDirectoryName(DirectoryName);
	viewer_->SetInputData(reader_->GetOutput());
	
	reader_->Update();

	ZNum_ = viewer_->GetWholeZMax ();
}

void gmrVTKDICOM::LoadImageData()
{
	// [vtkContourFilter]の設定
	skinExtractor_->SetInputConnection(reader_->GetOutputPort());
    skinExtractor_->SetValue((int)range_[0], range_[1]);
	skinExtractor_->ComputeGradientsOn();

	// [vtkPolyDataNormals]の設定
	skinNormals_->SetInputConnection(skinExtractor_->GetOutputPort());
    skinNormals_->SetFeatureAngle(FeatureAngle_);

	// [vtkPolyDataMapper]の設定
	skinMapper_->SetInputConnection(skinNormals_->GetOutputPort());
    skinMapper_->ScalarVisibilityOff();
	//skinMapper_->ScalarVisibilityOn();

	if (surface_On)
	{
		printf("polygonizer.\n");
		surface_->SetInputConnection(reader_->GetOutputPort());
		surface_->ComputeNormalsOn();
		//surface_->ComputeScalarsOn();
		surface_->SetValue(0, isovalue);
		printf("isovalue:%f\n", isovalue);

		// Create polydata from iso-surface
		vtkSmartPointer<vtkPolyData> marched =
			vtkSmartPointer<vtkPolyData>::New();
		surface_->Update();
		marched->DeepCopy(surface_->GetOutput());
		std::cout << "Number of points: " << marched->GetNumberOfPoints() << std::endl;

		// Decimation to reduce the number of triangles
		vtkSmartPointer<vtkDecimatePro> decimator =
			vtkDecimatePro::New();
		decimator->SetInputData(marched);
		decimator->SetTargetReduction(0.05);
		decimator->SetPreserveTopology(1);
		decimator->Update();
		std::cout << "Decimation finished...." << std::endl;
		//// Smoothing
		//vtkSmartPointer<vtkSmoothPolyDataFilter> smoother = vtkSmartPointer<vtkSmoothPolyDataFilter>::New();
		//smoother->SetInputData(decimator->GetOutput());
		//smoother->SetNumberOfIterations(5);
		//smoother->SetFeatureAngle(60);
		//smoother->SetRelaxationFactor(0.05);
		//smoother->FeatureEdgeSmoothingOff();
		//std::cout << "Smoothing mesh finished...." << std::endl;

		//// Select the largest region
		//vtkSmartPointer<vtkPolyDataConnectivityFilter> connectivityFilter =
		//	vtkSmartPointer<vtkPolyDataConnectivityFilter>::New();
		//connectivityFilter->SetInputConnection(smoother->GetOutputPort());
		//connectivityFilter->ScalarConnectivityOff();
		//connectivityFilter->SetExtractionModeToLargestRegion();
		//connectivityFilter->Update();

		//// Create final polygon mesh
		mesh_ =	vtkSmartPointer<vtkPolyData>::New();
		mesh_->ShallowCopy(decimator->GetOutput());
		std::cout << "Number of points in the final polygon: " << mesh_->GetNumberOfPoints() << std::endl;

		surface_mapper_ = vtkSmartPointer<vtkPolyDataMapper>::New();
		surface_mapper_->SetInputData(mesh_);
		surface_mapper_->ScalarVisibilityOff();
		surface_actor_ = vtkSmartPointer<vtkActor>::New();
		surface_actor_->SetMapper(surface_mapper_);
	}



  vtkSmartPointer<vtkColorTransferFunction> volumeColor = vtkSmartPointer<vtkColorTransferFunction>::New();
#if 0
  // 新しい設定
  volumeColor->AddRGBPoint(0,   0.0, 0.0, 0.0);
  volumeColor->AddRGBPoint(50, 0.2, 0.2, 0.2);
  volumeColor->AddRGBPoint(64,  1.0, 0.52, 0.3);
  volumeColor->AddRGBPoint(190, 1.0, 1.0, 1.0);
  volumeColor->AddRGBPoint(220, 0.8, 0.8, 0.8);
#else
  //// 古い設定
  //volumeColor->AddRGBPoint(0, 0, 0.2, 0.5);
  //volumeColor->AddRGBPoint(50, 0,0.2,0.5);
  //volumeColor->AddRGBPoint(60, 238./255.0, 211./255.0, 193./255.0);
  //volumeColor->AddRGBPoint(100, 250. / 255.0, 242. / 255., 237. / 255.);
  //volumeColor->AddRGBPoint(128, 250. / 255.0, 242. / 255., 237. / 255.);
  //volumeColor->AddRGBPoint(200, 250. / 255.0, 242. / 255., 237. / 255.);
  //volumeColor->AddRGBPoint(300, 250. / 255.0, 242. / 255., 237. / 255.);
  //volumeColor->AddRGBPoint(500, 250. / 255.0, 242. / 255., 237. / 255.);
  //volumeColor->AddRGBPoint(1000, 255. / 255.0, 185. / 255., 185. / 255.);
  //volumeColor->AddRGBPoint(1150, 255. / 255.0, 185. / 255., 185. / 255.);

  for (int i = 0; i < this->volumeColorSet.size(); ++i)
  {
	  volumeColor->AddRGBPoint(this->volumeColorSet[i].x[0], this->volumeColorSet[i].x[1], this->volumeColorSet[i].x[2], this->volumeColorSet[i].x[3]);
  }
#endif

  // The opacity transfer function is used to control the opacity
  // of different tissue types.
  vtkSmartPointer<vtkPiecewiseFunction> volumeScalarOpacity = vtkSmartPointer<vtkPiecewiseFunction>::New();
#if 0
  // 新しい設定
  volumeScalarOpacity->AddPoint(0,	  0.0);
  volumeScalarOpacity->AddPoint(50, 0.2);
  volumeScalarOpacity->AddPoint(64,   0.5);
  volumeScalarOpacity->AddPoint(190,  0.6);
  volumeScalarOpacity->AddPoint(220,  0.7);
#else
  //// 古い設定
  //volumeScalarOpacity->AddPoint(0, 0.0);
  //volumeScalarOpacity->AddPoint(60, 0.05);
  //volumeScalarOpacity->AddPoint(80, 0.16);
  //volumeScalarOpacity->AddPoint(100, 0.2);
  //volumeScalarOpacity->AddPoint(128, 0.25);
  //volumeScalarOpacity->AddPoint(200, 0.25);
  //volumeScalarOpacity->AddPoint(300, 0.5);
  //volumeScalarOpacity->AddPoint(500, 1.0);
  //volumeScalarOpacity->AddPoint(1000, 1.0);
  //volumeScalarOpacity->AddPoint(1150, 1.0);
  for (int i = 0; i < this->volumeColorSet.size(); ++i)
  {
	  volumeScalarOpacity->AddPoint(this->volumeColorSet[i].x[0], this->volumeColorSet[i].x[4]);
  }
#endif

  // The gradient opacity function is used to decrease the opacity
  // in the "flat" regions of the volume while maintaining the opacity
  // at the boundaries between tissue types.  The gradient is measured
  // as the amount by which the intensity changes over unit distance.
  // For most medical data, the unit distance is 1mm.
  vtkSmartPointer<vtkPiecewiseFunction> volumeGradientOpacity = vtkSmartPointer<vtkPiecewiseFunction>::New();
  volumeGradientOpacity->AddPoint(0,    0.0);
  volumeGradientOpacity->AddPoint(80,   0.5);
  volumeGradientOpacity->AddPoint(100,  0.8);
  volumeGradientOpacity->AddPoint(128,  0.85);
  volumeGradientOpacity->AddPoint(200,  0.9);
  volumeGradientOpacity->AddPoint(500,  0.95);
  volumeGradientOpacity->AddPoint(1000, 0.98);
  volumeGradientOpacity->AddPoint(1150, 0.99);

  //volumeGradientOpacity->AddPoint(0, 0.0);
  //volumeGradientOpacity->AddPoint(90, 0.5);
  //volumeGradientOpacity->AddPoint(100, 1.0);


  // The VolumeProperty attaches the color and opacity functions to the
  // volume, and sets other volume properties.  The interpolation should
  // be set to linear to do a high-quality rendering.  The ShadeOn option
  // turns on directional lighting, which will usually enhance the
  // appearance of the volume and make it look more "3D".  However,
  // the quality of the shading depends on how accurately the gradient
  // of the volume can be calculated, and for noisy data the gradient
  // estimation will be very poor.  The impact of the shading can be
  // decreased by increasing the Ambient coefficient while decreasing
  // the Diffuse and Specular coefficient.  To increase the impact
  // of shading, decrease the Ambient and increase the Diffuse and Specular.
  vtkSmartPointer<vtkVolumeProperty> volumeProperty = vtkSmartPointer<vtkVolumeProperty>::New();
  volumeProperty->SetColor(volumeColor);
  volumeProperty->SetScalarOpacity(volumeScalarOpacity);
  //volumeProperty->SetGradientOpacity(volumeGradientOpacity);
  volumeProperty->SetInterpolationTypeToLinear();
  //volumeProperty->SetInterpolationTypeToNearest();
  volumeProperty->ShadeOn();
  volumeProperty->SetAmbient(0.3);
  volumeProperty->SetDiffuse(0.75);
  volumeProperty->SetSpecular(0.35);


  volume_ = vtkSmartPointer<vtkVolume>::New();
  volume_->SetProperty(volumeProperty);
#if 0
 //vtkVolumeRayCastMapper *volumemapper = vtkVolumeRayCastMapper::New();
 vtkFixedPointVolumeRayCastMapper *volumemapper = vtkFixedPointVolumeRayCastMapper::New();
       
  //vtkVolumeRayCastCompositeFunction *raycast = vtkVolumeRayCastCompositeFunction::New();
  //volumemapper->SetVolumeRayCastFunction(raycast);
  
 volumemapper->SetInputConnection(reader_->GetOutputPort());
  volumemapper->SetSampleDistance(0.1);
//  volumemapper->SetBlendModeToMaximumIntensity(); // ← これを呼ぶと表示が変になる
  volume->SetMapper(volumemapper);
#else
  volumemapper = vtkSmartPointer<vtkGPUVolumeRayCastMapper>::New();
//vtkOpenGLGPUVolumeRayCastMapper* volumemapper = vtkOpenGLGPUVolumeRayCastMapper::New();
  volumemapper->SetInputConnection(reader_->GetOutputPort());
  volumemapper->SetSampleDistance(SampleDistance_);
//  volumemapper->SetBlendModeToMaximumIntensity(); // ← これ呼ぶと表示が変になる
  volume_->SetMapper(volumemapper);

  //vtkSmartPointer<vtkPolyDataMapper> surface_mapper_;
  //surface_mapper_ = vtkSmartPointer<vtkPolyDataMapper>::New();

  //if (surface_On)
  //{
	 // //surface_->ComputeNormalsOn();
	 // //surface_->ComputeScalarsOn();
	 // //surface_mapper_->SetInputConnection(surface_->GetOutputPort());
	 // //surface_mapper_->ScalarVisibilityOff();

	 // //surface_actor_ = vtkSmartPointer<vtkActor>::New();
	 // //surface_actor_->SetMapper(surface_mapper_);
  //}

#endif
//vtkLODProp3D* LODProperty = vtkSmartPointer <vtkLODProp3D>::New();
  //int id = LODProperty->AddLOD(volumemapper, volumeProperty, 0.0);
  //LODProperty->SetLODLevel(id, 0.0);

  //this->viewer_->GetRenderer()->AddViewProp(LODProperty);
}

void gmrVTKDICOM::ViewerZSlice(int ZSlice, int colorWindow, int colorLevel)
{
	if ( ZSlice > ZNum_ ) return;

    viewer_->SetZSlice(ZSlice);
    viewer_->SetColorWindow(colorWindow);
    viewer_->SetColorLevel(colorLevel);
	viewer_->Render();
}

vtkActor* gmrVTKDICOM::GetActor()
{
	if ( actor_ == NULL )
	{
		actor_ = vtkActor::New();
		actor_->SetMapper(skinMapper_);
	}

	return actor_;
}




