/************************************************************
*
* vtkWrapperLIBを使った簡単なサンプルプログラム
*
*************************************************************/

#include "MRI_view.hpp"
#include "gmrVTK.hpp"
#include "gmrVTKLIBs.hpp"

#include "execute.hpp"

#ifdef MRI_TEST
int main(int argc, char** argv)
{
	char* folderName;
	
//	folderName = "data\\GOUDURIX\\GOUDURIX\\Specials 1_CORONARY_CTA_COMBI_SMH\\70 % 1.0  B30f";
//	folderName = "data\\PANORAMIX\\PANORAMIX\\Abdomen 1ABD_PEL_AAA\\Abd-Pel w-c  3.0  B30f";


#ifdef MRI_BMP_EXE
	if ( argc < 2 )
	{
		fprintf(stderr, "usage: DICOM2BMP.exe dcm-files-folderName\n");
		return 1;
	}
	folderName = argv[1];
	// DICOM スライスViewer
	fprintf(stderr, "==> convert bitmap!!\n");
	dicom1(folderName);
#endif

#ifdef MRI_VIEWER_EXE
	if ( argc < 2 )
	{
		fprintf(stderr, "usage: DICOMView.exe dcm-files-folderName\n");
		return 1;
	}
	folderName = argv[1];
	// DICOM 3D可視化
	dicom2(folderName);
#endif
	return 0;
}

#endif