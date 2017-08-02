#ifndef _MAIN_HPP
#define _MAIN_HPP

#include "gmrVTKLIBs.hpp"

//void xyplot();
void PointsView ();
void PolylineView ();
void PolygonView ();
void OBJView ();
void PLYView ();
void STLView ();

void dicom1(char* folderName);
void dicom2(char* folderName, int vr);

//void Picker ();
//void InteractorStyle();
//void BoxWidget();

#endif