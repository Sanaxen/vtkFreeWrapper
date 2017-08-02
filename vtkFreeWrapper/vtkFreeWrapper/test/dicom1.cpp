/*
 * VTKを簡単に（？）使うための簡単クラスライブラリの使用例
 * Copyright (c) Sanaxen
 *
 */
#include "gmrVTKDICOM.hpp"
#include "gmrVTKCapture.hpp"

// DICOM sample image sets
// http://149.142.216.30/DICOM_FILES/Index.html
void dicom1(char* folderName)
{
    gmrVTKDICOM *reader = new gmrVTKDICOM;
    
//    reader->SetDirectoryName("data\\PANORAMIX\\Abdomen 1ABD_PEL_AAA\\Abd-Pel w-c  3.0  B30f");
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
