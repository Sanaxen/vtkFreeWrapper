/************************************************************
*
* vtkWrapperLIB���g�����ȒP�ȃT���v���v���O����
*
*************************************************************/

#include "main.hpp"
#include "gmrVTK.hpp"
#include "gmrVTKLIBs.hpp"

#include "execute.hpp"

#ifdef UNIT_TEST_EXE

// DICOM sample image sets
// http://149.142.216.30/DICOM_FILES/Index.html
#define DICOM_TEST 10


// 3D sample �f�[�^
// OBJ�`�� http://www.farfieldtechnology.com/download/
// PLY�`�� http://www-graphics.stanford.edu/data/3Dscanrep/
#define IMPORT_TEST 10

//#include "vtkAutoInit.h"
//VTK_MODULE_INIT(vtkRenderingOpenGL);
//VTK_MODULE_INIT(vtkInteractionStyle);
//VTK_MODULE_INIT(vtkRenderingFreeType);
//VTK_MODULE_INIT(vtkRenderingVolumeOpenGL);
//
void BoxWidget();

int main(int argc, char** argv)
{

#if 10
	PointsView();		//�_�Q�\��

	PolylineView();		//�|�����C���\��

	PolygonView();		//�|���S���\��

	Picker();			// Picker�i�s�b�N�ɂ��A�N�^�[�̍폜)
	//exit(0);

	InteractorStyle();	//RubberBand�ɂ��g��i�}�E�X�C���^���N�V�����j�̗�
	//exit(0);

	BoxWidget();	//BoxWidget�̗�
#endif

#if 10
	xyplot();
#endif

#if IMPORT_TEST
	// �RD�f�[�^�C���|�[�g
	PLYView();	//PLY�t�@�C���\��
	OBJView();	//OBJ�t�@�C���\��
	STLView();	//STL�t�@�C���\��
#endif

#if DICOM_TEST

	// DICOM �X���C�XViewer
	dicom1("data\\CEREBRIX");

	// DICOM 3D����
	dicom2("data\\PANORAMIX", 0);
	dicom2("data\\PANORAMIX", 1);
#endif

	return 0;
}
#endif
