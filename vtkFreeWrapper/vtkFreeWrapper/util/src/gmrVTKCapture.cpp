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
 * 画面Capture
 *
 */
#include "gmrVTKCapture.hpp"

gmrVTKCapture::gmrVTKCapture()
{
	WindowToImageFilter_ = vtkWindowToImageFilter::New();
	wr_ = NULL;
	Exten[0] = '\0';
	FileName_[0] = '\0';
}

void gmrVTKCapture::SetInput(vtkImageViewer* viewer)
{
	WindowToImageFilter_->SetInput(viewer->GetRenderWindow() );
}

void gmrVTKCapture::SetInput(gmrVTKRender* renwin)
{
	WindowToImageFilter_->SetInput(renwin->GetRenderWindow() );
}

void gmrVTKCapture::SetInput(vtkWindow *input)
{
	WindowToImageFilter_->SetInput(input);
}

gmrVTKCapture::~gmrVTKCapture()
{
	WindowToImageFilter_->Delete();
}


void gmrVTKCapture::Capture()
{

	if ( wr_ == NULL ) return;

	char file[260];

	gmrVTKLocker lock(lock_);
	wr_->SetInputConnection(WindowToImageFilter_->GetOutputPort());

	sprintf( file, "%s.%s", GetFileName(), Exten);
	wr_->SetFileName(file);
	
	WindowToImageFilter_->Modified();
	wr_->Write();
}

void gmrVTKCapture::Capture(int index)
{
	if ( wr_ == NULL ) return;

	char file[260];

	gmrVTKLocker lock(lock_);

	wr_->SetInputConnection(WindowToImageFilter_->GetOutputPort());

	sprintf( file, "%s%03d.%s", GetFileName(), index, Exten);
	wr_->SetFileName(file);

	WindowToImageFilter_->Modified();
	wr_->Write();
}
////////////////////////////////////////////////////////////////////////////////////



gmrVTKCapturePNG::gmrVTKCapturePNG()
{
	wr_ = vtkPNGWriter::New();
	strcpy(Exten, "png");
}

gmrVTKCapturePNG::~gmrVTKCapturePNG()
{
	wr_->Delete();
}
////////////////////////////////////////////////////////////////////////////////////

gmrVTKCaptureJPEG::gmrVTKCaptureJPEG()
{
	wr_ = vtkJPEGWriter::New();
	strcpy(Exten, "jpg");
}

gmrVTKCaptureJPEG::~gmrVTKCaptureJPEG()
{
	wr_->Delete();
}
////////////////////////////////////////////////////////////////////////////////////

gmrVTKCaptureBMP::gmrVTKCaptureBMP()
{
	wr_ = vtkBMPWriter::New();
	strcpy(Exten, "bmp");
}

gmrVTKCaptureBMP::~gmrVTKCaptureBMP()
{
	wr_->Delete();
}
////////////////////////////////////////////////////////////////////////////////////


gmrVTKCaptureAVI::gmrVTKCaptureAVI()
{
	WindowToImageFilter_ = vtkWindowToImageFilter::New();
	wrAVI_ = vtkAVIWriter::New();
	strcpy(Exten, "avi");
	FileName_[0] = '\0';
}

gmrVTKCaptureAVI::~gmrVTKCaptureAVI()
{
	wrAVI_->Delete();
	WindowToImageFilter_->Delete();
}

void gmrVTKCaptureAVI::Start()
{
	char file[260];

	gmrVTKLocker lock(lock_);

	wrAVI_->SetInputConnection(WindowToImageFilter_->GetOutputPort());
	sprintf( file, "%s.%s", GetFileName(), Exten);
	wrAVI_->SetFileName(file);
	wrAVI_->Start();
}

void gmrVTKCaptureAVI::Start(int index)
{
	char file[260];

	gmrVTKLocker lock(lock_);

	wrAVI_->SetInputConnection(WindowToImageFilter_->GetOutputPort());

	sprintf( file, "%s%03d.%s", GetFileName(), index, Exten);
	wrAVI_->SetFileName(file);
	wrAVI_->Start();
}


void gmrVTKCaptureAVI::SetInput(gmrVTKRender* renwin)
{

	WindowToImageFilter_->SetInput(renwin->GetRenderWindow() );
}

void gmrVTKCaptureAVI::SetInput(vtkWindow *input)
{
	WindowToImageFilter_->SetInput(input);
}
