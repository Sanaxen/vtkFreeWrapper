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
 * レンダリング・クラス
 *
 */
#include "gmrVTKRender.hpp"
#include "gmrVTKPicker.hpp"
#include "gmrVTKCommand.hpp"


void gmrVTKRender::Initialize()
{
	iren_ = NULL;
	renWin_ = NULL;
	style_ = NULL;

	ren_ = vtkRenderer::New();
	Size_[0] = 500;
	Size_[1] = 500;
	BackgroundColor_[0] = 1;
	BackgroundColor_[1] = 1;
	BackgroundColor_[2] = 1;
	BackgroundColor_[3] = 0;
	InputRenderWindow_ = false;
	picker_ = NULL;
}

gmrVTKRender::gmrVTKRender(vtkRenderWindow *renWin)
{
	Initialize();
	iren_ = vtkRenderWindowInteractor::New();
	iren_->SetRenderWindow(renWin);
	renWin_ = renWin;
	InputRenderWindow_ = true;
	InteractorStyleTrackballCamera(); // デフォルトのカメラの動きを設定
}


gmrVTKRender::gmrVTKRender(int offscreen)
{
	Initialize();
	renWin_ = vtkRenderWindow::New();
	if ( offscreen )
	{
		OffScreenSetup();
		renWin_->SetOffScreenRendering( 1 ); 
	}

	renWin_->AddRenderer(ren_);

	iren_ = vtkRenderWindowInteractor::New();
	iren_->SetRenderWindow(renWin_);
	InteractorStyleTrackballCamera(); // デフォルトのカメラの動きを設定
}

gmrVTKRender::~gmrVTKRender()
{
	ren_->Delete();
	if( !InputRenderWindow_ && renWin_) renWin_->Delete();
	if( iren_) iren_->Delete();
	if( style_) style_->Delete();
}

void gmrVTKRender::AddActor(vtkVolume* actor)
{
	ren_->AddActor(actor);
}
void gmrVTKRender::AddActor(vtkActor* actor)
{
	ren_->AddActor(actor);
}
void gmrVTKRender::AddActor(vtkImageActor* actor)
{
	ren_->AddActor(actor);
}
void gmrVTKRender::AddActor(vtkXYPlotActor* actor)
{
	ren_->AddActor2D(actor);
}
void gmrVTKRender::AddActor(vtkTextActor* actor)
{
	ren_->AddActor2D(actor);
}
void gmrVTKRender::AddActor(vtkCaptionActor2D* actor)
{
	ren_->AddActor2D(actor);
}

void gmrVTKRender::RemoveActor(vtkProp* actor)
{
	ren_->RemoveActor(actor);
}
void gmrVTKRender::RemoveActor(vtkActor* actor)
{
	ren_->RemoveActor(actor);
}
void gmrVTKRender::RemoveActor(vtkXYPlotActor* actor)
{
	ren_->RemoveActor2D(actor);
}
void gmrVTKRender::RemoveActor(vtkImageActor* actor)
{
	ren_->RemoveActor(actor);
}
void gmrVTKRender::RemoveActor(vtkTextActor* actor)
{
	ren_->RemoveActor2D(actor);
}
void gmrVTKRender::RemoveActor(vtkCaptionActor2D* actor)
{
	ren_->RemoveActor2D(actor);
}


void gmrVTKRender::InteractorStyleTrackballCamera(void)
{
	if ( style_ ) style_->Delete();
	style_ = vtkInteractorStyleTrackballCamera::New();
	iren_->SetInteractorStyle(style_);
}

void gmrVTKRender::InteractorStyleRubberBandZoom(void)
{
	if ( style_ ) style_->Delete();
	style_ = vtkInteractorStyleRubberBandZoom::New();
	iren_->SetInteractorStyle(style_);
}

void gmrVTKRender::MouseInteractionStart()
{
	iren_->Initialize();
	// begin mouse interaction
	iren_->Start();
}

void gmrVTKRender::Run(char* title)
{
	ren_->SetBackground(BackgroundColor_[0], BackgroundColor_[1], BackgroundColor_[2]);

	// render an image (lights and cameras are created automatically)
	renWin_->SetSize(Size_[0],Size_[1]);
	renWin_->Render();
	if (title) renWin_->SetWindowName(title);

}

void gmrVTKRender::DefaultRun(char* title)
{
	Run();
	if (title) renWin_->SetWindowName(title);
	MouseInteractionStart();
}


void gmrVTKRender::AddCallback(vtkCommand::EventIds id, gmrVTKCommand* callback)
{
	callback->SetRenderer(this);
	this->GetRenderWindowInteractor()->AddObserver(id, (vtkCommand*)callback);
}

void gmrVTKRender::RemoveCallback(gmrVTKCommand* callback)
{
	if ( callback != NULL )
	{
		iren_->RemoveObserver((vtkCommand*)callback);
	}
}

void gmrVTKRender::SetPiker(gmrVTKPicker* picker)
{
	picker_ = picker;
	iren_->SetPicker(picker_->GetPicker());
}

void gmrVTKRender::PickerOn()
{
	if (  picker_ == NULL) return;

	AddCallback(vtkCommand::LeftButtonPressEvent, picker_->GetCallback());
}

void gmrVTKRender::PickerOff()
{
	if (  picker_ == NULL) return;
	RemoveCallback(picker_->GetCallback());
	picker_ = NULL;
}

gmrVTKPicker* gmrVTKRender::GetPicker()
{
	return picker_;
}

void gmrVTKRender::OffScreenSetup()
{

  // Setup offscreen rendering
  //vtkSmartPointer<vtkGraphicsFactory> graphics_factory = 
  //  vtkSmartPointer<vtkGraphicsFactory>::New();
  //graphics_factory->SetOffScreenOnlyMode( 1);
  //graphics_factory->SetUseMesaClasses( 1 );
 
  //vtkSmartPointer<vtkImagingFactory> imaging_factory = 
  //  vtkSmartPointer<vtkImagingFactory>::New();
  //imaging_factory->SetUseMesaClasses( 1 ); 
}

