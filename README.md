# vtkFreeWrapper

## What's New
- between two points in 3D image of volume rendering  
<img src="https://github.com/Sanaxen/vtkFreeWrapper/blob/master/images/3.png"/>  

## Image Examples
<img src="https://github.com/Sanaxen/vtkFreeWrapper/blob/master/images/1.png"/>  
<img src="https://github.com/Sanaxen/vtkFreeWrapper/blob/master/images/2.png"/>  

## Code Examples1
2D image

```cpp
#include "gmrVTKDICOM.hpp"
#include "gmrVTKCapture.hpp"

void dicom1(char* folderName)
{
    gmrVTKDICOM *reader = new gmrVTKDICOM;
    
    reader->SetDirectoryName(folderName);
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
}
```

 ## Code Examples1
3D image

void dicom2(char* folderName, int VolumeRenderring)
 {
 	gmrVTKRender* render = new gmrVTKRender;
    gmrVTKDICOM *reader = new gmrVTKDICOM;
    
    reader->SetDirectoryName(folderName);
    reader->LoadImageData();

	render->AddActor( reader->GetActor());

	if (VolumeRenderring)
	{
		render->AddActor(reader->GetVolume());
	}

	render->SetBackgroundColor( 0.1, 0.2, 0.4 );

	render->DefaultRun();
}
```


Visual Studio 2015 C ++ and VTK-7.1.1  

