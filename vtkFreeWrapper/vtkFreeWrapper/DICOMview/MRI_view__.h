#ifndef _MRI_VIEW__H

#define _MRI_VIEW__H

#if defined(WIN32) && defined(TEST2_EXPORTS)
# define MRI_VIEW_EXPORT __declspec( dllexport )
#else
# define MRI_VIEW_EXPORT /* emptyr */
#endif

extern "C"
{
MRI_VIEW_EXPORT void DICOM_SliceViewer(char* folderName, int capture);
MRI_VIEW_EXPORT void DICOM_3DViewer(char* folderName, int output, double sample_dist, double isovalue, char* outfile);

MRI_VIEW_EXPORT void DICOM2BMP(char* dcm_files_folderName);
MRI_VIEW_EXPORT void DICOM2OBJ(char* dcm_files_folderName, int flg, double isovalue, char* outfile);
MRI_VIEW_EXPORT void DICOM2STL(char* dcm_files_folderName, int flg, double isovalue, char* outfile);
MRI_VIEW_EXPORT void DICOM2VRML(char* dcm_files_folderName, int flg, double isovalue, char* outfile);
MRI_VIEW_EXPORT void DICOM2X3D(char* dcm_files_folderName, int flg, double isovalue, char* outfile);
};


#endif