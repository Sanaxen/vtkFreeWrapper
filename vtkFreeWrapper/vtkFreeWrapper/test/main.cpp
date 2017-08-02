/************************************************************
*
* vtkWrapperLIBを使った簡単なサンプルプログラム
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


// 3D sample データ
// OBJ形式 http://www.farfieldtechnology.com/download/
// PLY形式 http://www-graphics.stanford.edu/data/3Dscanrep/
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
	PointsView();		//点群表示

	PolylineView();		//ポリライン表示

	PolygonView();		//ポリゴン表示

	Picker();			// Picker（ピックによるアクターの削除)
	//exit(0);

	InteractorStyle();	//RubberBandによる拡大（マウスインタラクション）の例
	//exit(0);

	BoxWidget();	//BoxWidgetの例
#endif

#if 10
	xyplot();
#endif

#if IMPORT_TEST
	// ３Dデータインポート
	PLYView();	//PLYファイル表示
	OBJView();	//OBJファイル表示
	STLView();	//STLファイル表示
#endif

#if DICOM_TEST

	// DICOM スライスViewer
	dicom1("data\\CEREBRIX");

	// DICOM 3D可視化
	dicom2("data\\PANORAMIX", 0);
	dicom2("data\\PANORAMIX", 1);
#endif

	return 0;
}
#endif
