#ifndef _GMRVTKLIBS_HPP
#define _GMRVTKLIBS_HPP

//#define VTK_VER	510	//5.10
//#define VTK_VER	630	//6.3
//#define VTK_VER	700	//7.0
//#define VTK_VER	711	//7.1.1
//#define VTK_VER	811	//8.1.1
//#define VTK_VER	940	//9.4.1
#define VTK_VER	940	//9.4.0

#if VTK_VER == 510
#pragma comment( lib, "vtksys.lib")
#pragma comment( lib, "vtkzlib.lib")
#pragma comment( lib, "vtkjpeg.lib")
#pragma comment( lib, "vtkpng.lib")
#pragma comment( lib, "vtktiff.lib")
#pragma comment( lib, "vtkexpat.lib")
#pragma comment( lib, "vtkfreetype.lib")
#pragma comment( lib, "vtklibxml2.lib")
#pragma comment( lib, "vtkDICOMParser.lib")
#pragma comment( lib, "vtkproj4.lib")
#pragma comment( lib, "vtkverdict.lib")
#pragma comment( lib, "vtkNetCDF.lib")
#pragma comment( lib, "vtkmetaio.lib")
#pragma comment( lib, "vtksqlite.lib")
#pragma comment( lib, "vtkexoIIc.lib")
#pragma comment( lib, "vtkalglib.lib")
#pragma comment( lib, "vtkftgl.lib")
#pragma comment( lib, "vtkCommon.lib")
#pragma comment( lib, "vtkFiltering.lib")
#pragma comment( lib, "vtkImaging.lib")
#pragma comment( lib, "vtkGraphics.lib")
#pragma comment( lib, "vtkGenericFiltering.lib")
#pragma comment( lib, "vtkIO.lib")
#pragma comment( lib, "vtkRendering.lib")
#pragma comment( lib, "vtkVolumeRendering.lib")
#pragma comment( lib, "vtkHybrid.lib")
#pragma comment( lib, "vtkWidgets.lib")
#pragma comment( lib, "vtkInfovis.lib")
#pragma comment( lib, "vtkGeovis.lib")
#pragma comment( lib, "vtkViews.lib")
#endif

#if VTK_VER == 630
//#pragma comment( lib, "vtksys-6.3.lib")
//#pragma comment( lib, "vtkzlib-6.3.lib")
//#pragma comment( lib, "vtkjpeg-6.3.lib")
//#pragma comment( lib, "vtkpng-6.3.lib")
//#pragma comment( lib, "vtktiff-6.3.lib")
//#pragma comment( lib, "vtkexpat-6.3.lib")
//#pragma comment( lib, "vtkfreetype-6.3.lib")
//#pragma comment( lib, "vtklibxml2-6.3.lib")
//#pragma comment( lib, "vtkDICOMParser-6.3.lib")
//#pragma comment( lib, "vtkproj4-6.3.lib")
//#pragma comment( lib, "vtkverdict-6.3.lib")
//#pragma comment( lib, "vtkNetCDF-6.3.lib")
//#pragma comment( lib, "vtkmetaio-6.3.lib")
//#pragma comment( lib, "vtksqlite-6.3.lib")
//#pragma comment( lib, "vtkexoIIc-6.3.lib")
//#pragma comment( lib, "vtkalglib-6.3.lib")
//#pragma comment( lib, "vtkftgl-6.3.lib")
//
////#pragma comment( lib, "vtkCommon-6.3.lib")
//#pragma comment( lib, "vtkCommonCore-6.3.lib")
//#pragma comment( lib, "vtkCommonDataModel-6.3.lib")
//#pragma comment( lib, "vtkCommonExecutionModel-6.3.lib")
//#pragma comment( lib, "vtkCommonTransforms-6.3.lib")
//#pragma comment( lib, "vtkCommonMisc-6.3.lib")
//#pragma comment( lib, "vtkCommonSystem-6.3.lib")
//#pragma comment( lib, "vtkCommonColor-6.3.lib")
//#pragma comment( lib, "vtkCommonMath-6.3.lib")
//#pragma comment( lib, "vtkCommonComputationalGeometry-6.3.lib")
//#pragma comment( lib, "vtkCommonTransforms-6.3.lib")
//
//#pragma comment( lib, "vtkChartsCore-6.3.lib")
//
//
////#pragma comment( lib, "vtkFiltering-6.3.lib")
//#pragma comment( lib, "vtkFiltersCore-6.3.lib")
//#pragma comment( lib, "vtkFiltersExtraction-6.3.lib")
//#pragma comment( lib, "vtkFiltersGeneral-6.3.lib")
//#pragma comment( lib, "vtkFiltersGeneric-6.3.lib")
//#pragma comment( lib, "vtkFiltersGeometry-6.3.lib")
//#pragma comment( lib, "vtkFiltersModeling-6.3.lib")
//#pragma comment( lib, "vtkFiltersParallel-6.3.lib")
//#pragma comment( lib, "vtkFiltersParallelImaging-6.3.lib")
//#pragma comment( lib, "vtkFiltersSources-6.3.lib")
//#pragma comment( lib, "vtkFiltersTexture-6.3.lib")
//#pragma comment( lib, "vtkFiltersFlowPaths-6.3.lib")
//#pragma comment( lib, "vtkFiltersImaging-6.3.lib")
//#pragma comment( lib, "vtkFiltersSelection-6.3.lib")
//
//
////#pragma comment( lib, "vtkImaging-6.3.lib")
//#pragma comment( lib, "vtkInfovisCore-6.3.lib")
//#pragma comment( lib, "vtkInteractionImage-6.3.lib")
//#pragma comment( lib, "vtkInteractionStyle-6.3.lib")
//#pragma comment( lib, "vtkInteractionStyle-6.3.lib")
//#pragma comment( lib, "vtkInteractionWidgets-6.3.lib")
//
////#pragma comment( lib, "vtkGraphics-6.3.lib")
//
////#pragma comment( lib, "vtkGenericFiltering-6.3.lib")
//
////#pragma comment( lib, "vtkIO-6.3.lib")
//#pragma comment( lib, "vtkIOCore-6.3.lib")
//#pragma comment( lib, "vtkIOMovie-6.3.lib")
//#pragma comment( lib, "vtkIOImage-6.3.lib")
//#pragma comment( lib, "vtkIOGeometry-6.3.lib")
//#pragma comment( lib, "vtkIOPLY-6.3.lib")
//#pragma comment( lib, "vtkIOExport-6.3.lib")
//#pragma comment( lib, "vtkIOImport-6.3.lib")
//
////#pragma comment( lib, "vtkRendering-6.3.lib")
//#pragma comment( lib, "vtkRenderingCore-6.3.lib")
//#pragma comment( lib, "vtkRenderingAnnotation-6.3.lib")
//#pragma comment( lib, "vtkRenderingFreeType-6.3.lib")
//#pragma comment( lib, "vtkRenderingContextOpenGL-6.3.lib")
//#pragma comment( lib, "vtkRenderingContext2D-6.3.lib")
//#pragma comment( lib, "vtkRenderingOpenGL-6.3.lib")
//#pragma comment( lib, "vtkRenderingImage-6.3.lib")
//
////#pragma comment( lib, "vtkVolumeRendering-6.3.lib")
//#pragma comment( lib, "vtkRenderingVolume-6.3.lib")
//#pragma comment( lib, "vtkRenderingVolumeOpenGL-6.3.lib")
//
////#pragma comment( lib, "vtkHybrid-6.3.lib")
//
////#pragma comment( lib, "vtkWidgets-6.3.lib")
////#pragma comment( lib, "vtkInteractionWidgets-6.3.lib")
//
////#pragma comment( lib, "vtkInfovis-6.3.lib")
//#pragma comment( lib, "vtkInfovisCore-6.3.lib")
//
////#pragma comment( lib, "vtkGeovis-6.3.lib")
//#pragma comment( lib, "vtkGeovisCore-6.3.lib")
//
////#pragma comment( lib, "vtkViews-6.3.lib")
//#pragma comment( lib, "vtkViewsCore-6.3.lib")
//
//
//#pragma comment( lib, "vtkDICOMParser-6.3.lib")
//
//#pragma comment( lib, "vtkImagingColor-6.3.lib")
//#pragma comment( lib, "vtkImagingCore-6.3.lib")
//#pragma comment( lib, "vtkImagingMath-6.3.lib")
//#pragma comment( lib, "vtkImagingSources-6.3.lib")
#pragma comment( lib, "vtkalglib-6.3.lib")
#pragma comment( lib, "vtkChartsCore-6.3.lib")
#pragma comment( lib, "vtkCommonColor-6.3.lib")
#pragma comment( lib, "vtkCommonComputationalGeometry-6.3.lib")
#pragma comment( lib, "vtkCommonCore-6.3.lib")
#pragma comment( lib, "vtkCommonDataModel-6.3.lib")
#pragma comment( lib, "vtkCommonExecutionModel-6.3.lib")
#pragma comment( lib, "vtkCommonMath-6.3.lib")
#pragma comment( lib, "vtkCommonMisc-6.3.lib")
#pragma comment( lib, "vtkCommonSystem-6.3.lib")
#pragma comment( lib, "vtkCommonTransforms-6.3.lib")
#pragma comment( lib, "vtkDICOMParser-6.3.lib")
#pragma comment( lib, "vtkDomainsChemistry-6.3.lib")
#pragma comment( lib, "vtkexoIIc-6.3.lib")
#pragma comment( lib, "vtkexpat-6.3.lib")
#pragma comment( lib, "vtkFiltersAMR-6.3.lib")
#pragma comment( lib, "vtkFiltersCore-6.3.lib")
#pragma comment( lib, "vtkFiltersExtraction-6.3.lib")
#pragma comment( lib, "vtkFiltersFlowPaths-6.3.lib")
#pragma comment( lib, "vtkFiltersGeneral-6.3.lib")
#pragma comment( lib, "vtkFiltersGeneric-6.3.lib")
#pragma comment( lib, "vtkFiltersGeometry-6.3.lib")
#pragma comment( lib, "vtkFiltersHybrid-6.3.lib")
#pragma comment( lib, "vtkFiltersHyperTree-6.3.lib")
#pragma comment( lib, "vtkFiltersImaging-6.3.lib")
#pragma comment( lib, "vtkFiltersModeling-6.3.lib")
#pragma comment( lib, "vtkFiltersParallel-6.3.lib")
#pragma comment( lib, "vtkFiltersParallelImaging-6.3.lib")
#pragma comment( lib, "vtkFiltersProgrammable-6.3.lib")
#pragma comment( lib, "vtkFiltersSelection-6.3.lib")
#pragma comment( lib, "vtkFiltersSMP-6.3.lib")
#pragma comment( lib, "vtkFiltersSources-6.3.lib")
#pragma comment( lib, "vtkFiltersStatistics-6.3.lib")
#pragma comment( lib, "vtkFiltersTexture-6.3.lib")
#pragma comment( lib, "vtkFiltersVerdict-6.3.lib")
#pragma comment( lib, "vtkfreetype-6.3.lib")
#pragma comment( lib, "vtkftgl-6.3.lib")
#pragma comment( lib, "vtkGeovisCore-6.3.lib")
#pragma comment( lib, "vtkgl2ps-6.3.lib")
#pragma comment( lib, "vtkhdf5-6.3.lib")
#pragma comment( lib, "vtkhdf5_hl-6.3.lib")
#pragma comment( lib, "vtkImagingColor-6.3.lib")
#pragma comment( lib, "vtkImagingCore-6.3.lib")
#pragma comment( lib, "vtkImagingFourier-6.3.lib")
#pragma comment( lib, "vtkImagingGeneral-6.3.lib")
#pragma comment( lib, "vtkImagingHybrid-6.3.lib")
#pragma comment( lib, "vtkImagingMath-6.3.lib")
#pragma comment( lib, "vtkImagingMorphological-6.3.lib")
#pragma comment( lib, "vtkImagingSources-6.3.lib")
#pragma comment( lib, "vtkImagingStatistics-6.3.lib")
#pragma comment( lib, "vtkImagingStencil-6.3.lib")
#pragma comment( lib, "vtkInfovisCore-6.3.lib")
#pragma comment( lib, "vtkInfovisLayout-6.3.lib")
#pragma comment( lib, "vtkInteractionImage-6.3.lib")
#pragma comment( lib, "vtkInteractionStyle-6.3.lib")
#pragma comment( lib, "vtkInteractionWidgets-6.3.lib")
#pragma comment( lib, "vtkIOAMR-6.3.lib")
#pragma comment( lib, "vtkIOCore-6.3.lib")
#pragma comment( lib, "vtkIOEnSight-6.3.lib")
#pragma comment( lib, "vtkIOExodus-6.3.lib")
#pragma comment( lib, "vtkIOExport-6.3.lib")
#pragma comment( lib, "vtkIOGeometry-6.3.lib")
#pragma comment( lib, "vtkIOImage-6.3.lib")
#pragma comment( lib, "vtkIOImport-6.3.lib")
#pragma comment( lib, "vtkIOInfovis-6.3.lib")
#pragma comment( lib, "vtkIOLegacy-6.3.lib")
#pragma comment( lib, "vtkIOLSDyna-6.3.lib")
#pragma comment( lib, "vtkIOMINC-6.3.lib")
#pragma comment( lib, "vtkIOMovie-6.3.lib")
#pragma comment( lib, "vtkIONetCDF-6.3.lib")
#pragma comment( lib, "vtkIOParallel-6.3.lib")
#pragma comment( lib, "vtkIOParallelXML-6.3.lib")
#pragma comment( lib, "vtkIOPLY-6.3.lib")
#pragma comment( lib, "vtkIOSQL-6.3.lib")
#pragma comment( lib, "vtkIOVideo-6.3.lib")
#pragma comment( lib, "vtkIOXML-6.3.lib")
#pragma comment( lib, "vtkIOXMLParser-6.3.lib")
#pragma comment( lib, "vtkjpeg-6.3.lib")
#pragma comment( lib, "vtkjsoncpp-6.3.lib")
#pragma comment( lib, "vtklibxml2-6.3.lib")
#pragma comment( lib, "vtkmetaio-6.3.lib")
#pragma comment( lib, "vtkNetCDF-6.3.lib")
#pragma comment( lib, "vtkNetCDF_cxx-6.3.lib")
#pragma comment( lib, "vtkoggtheora-6.3.lib")
#pragma comment( lib, "vtkParallelCore-6.3.lib")
#pragma comment( lib, "vtkpng-6.3.lib")
#pragma comment( lib, "vtkproj4-6.3.lib")
#pragma comment( lib, "vtkRenderingAnnotation-6.3.lib")
#pragma comment( lib, "vtkRenderingContext2D-6.3.lib")
#pragma comment( lib, "vtkRenderingContextOpenGL-6.3.lib")
#pragma comment( lib, "vtkRenderingCore-6.3.lib")
#pragma comment( lib, "vtkRenderingFreeType-6.3.lib")
#pragma comment( lib, "vtkRenderingGL2PS-6.3.lib")
#pragma comment( lib, "vtkRenderingImage-6.3.lib")
#pragma comment( lib, "vtkRenderingLabel-6.3.lib")
#pragma comment( lib, "vtkRenderingLIC-6.3.lib")
#pragma comment( lib, "vtkRenderingLOD-6.3.lib")
#pragma comment( lib, "vtkRenderingOpenGL-6.3.lib")
#pragma comment( lib, "vtkRenderingVolume-6.3.lib")
#pragma comment( lib, "vtkRenderingVolumeOpenGL-6.3.lib")
#pragma comment( lib, "vtksqlite-6.3.lib")
#pragma comment( lib, "vtksys-6.3.lib")
#pragma comment( lib, "vtktiff-6.3.lib")
#pragma comment( lib, "vtkverdict-6.3.lib")
#pragma comment( lib, "vtkViewsContext2D-6.3.lib")
#pragma comment( lib, "vtkViewsCore-6.3.lib")
#pragma comment( lib, "vtkViewsInfovis-6.3.lib")
#pragma comment( lib, "vtkzlib-6.3.lib")

#endif

#if VTK_VER == 700
#pragma comment( lib, "vtkalglib-7.0.lib")
#pragma comment( lib, "vtkChartsCore-7.0.lib")
#pragma comment( lib, "vtkCommonColor-7.0.lib")
#pragma comment( lib, "vtkCommonComputationalGeometry-7.0.lib")
#pragma comment( lib, "vtkCommonCore-7.0.lib")
#pragma comment( lib, "vtkCommonDataModel-7.0.lib")
#pragma comment( lib, "vtkCommonExecutionModel-7.0.lib")
#pragma comment( lib, "vtkCommonMath-7.0.lib")
#pragma comment( lib, "vtkCommonMisc-7.0.lib")
#pragma comment( lib, "vtkCommonSystem-7.0.lib")
#pragma comment( lib, "vtkCommonTransforms-7.0.lib")
#pragma comment( lib, "vtkDICOMParser-7.0.lib")
#pragma comment( lib, "vtkDomainsChemistry-7.0.lib")
#pragma comment( lib, "vtkDomainsChemistryOpenGL2-7.0.lib")
#pragma comment( lib, "vtkexoIIc-7.0.lib")
#pragma comment( lib, "vtkexpat-7.0.lib")
#pragma comment( lib, "vtkFiltersAMR-7.0.lib")
#pragma comment( lib, "vtkFiltersCore-7.0.lib")
#pragma comment( lib, "vtkFiltersExtraction-7.0.lib")
#pragma comment( lib, "vtkFiltersFlowPaths-7.0.lib")
#pragma comment( lib, "vtkFiltersGeneral-7.0.lib")
#pragma comment( lib, "vtkFiltersGeneric-7.0.lib")
#pragma comment( lib, "vtkFiltersGeometry-7.0.lib")
#pragma comment( lib, "vtkFiltersHybrid-7.0.lib")
#pragma comment( lib, "vtkFiltersHyperTree-7.0.lib")
#pragma comment( lib, "vtkFiltersImaging-7.0.lib")
#pragma comment( lib, "vtkFiltersModeling-7.0.lib")
#pragma comment( lib, "vtkFiltersParallel-7.0.lib")
#pragma comment( lib, "vtkFiltersParallelImaging-7.0.lib")
#pragma comment( lib, "vtkFiltersProgrammable-7.0.lib")
#pragma comment( lib, "vtkFiltersSelection-7.0.lib")
#pragma comment( lib, "vtkFiltersSMP-7.0.lib")
#pragma comment( lib, "vtkFiltersSources-7.0.lib")
#pragma comment( lib, "vtkFiltersStatistics-7.0.lib")
#pragma comment( lib, "vtkFiltersTexture-7.0.lib")
#pragma comment( lib, "vtkFiltersVerdict-7.0.lib")
#pragma comment( lib, "vtkfreetype-7.0.lib")
#pragma comment( lib, "vtkGeovisCore-7.0.lib")
#pragma comment( lib, "vtkglew-7.0.lib")
#pragma comment( lib, "vtkhdf5-7.0.lib")
#pragma comment( lib, "vtkhdf5_hl-7.0.lib")
#pragma comment( lib, "vtkImagingColor-7.0.lib")
#pragma comment( lib, "vtkImagingCore-7.0.lib")
#pragma comment( lib, "vtkImagingFourier-7.0.lib")
#pragma comment( lib, "vtkImagingGeneral-7.0.lib")
#pragma comment( lib, "vtkImagingHybrid-7.0.lib")
#pragma comment( lib, "vtkImagingMath-7.0.lib")
#pragma comment( lib, "vtkImagingMorphological-7.0.lib")
#pragma comment( lib, "vtkImagingSources-7.0.lib")
#pragma comment( lib, "vtkImagingStatistics-7.0.lib")
#pragma comment( lib, "vtkImagingStencil-7.0.lib")
#pragma comment( lib, "vtkInfovisCore-7.0.lib")
#pragma comment( lib, "vtkInfovisLayout-7.0.lib")
#pragma comment( lib, "vtkInteractionImage-7.0.lib")
#pragma comment( lib, "vtkInteractionStyle-7.0.lib")
#pragma comment( lib, "vtkInteractionWidgets-7.0.lib")
#pragma comment( lib, "vtkIOAMR-7.0.lib")
#pragma comment( lib, "vtkIOCore-7.0.lib")
#pragma comment( lib, "vtkIOEnSight-7.0.lib")
#pragma comment( lib, "vtkIOExodus-7.0.lib")
#pragma comment( lib, "vtkIOExport-7.0.lib")
#pragma comment( lib, "vtkIOGeometry-7.0.lib")
#pragma comment( lib, "vtkIOImage-7.0.lib")
#pragma comment( lib, "vtkIOImport-7.0.lib")
#pragma comment( lib, "vtkIOInfovis-7.0.lib")
#pragma comment( lib, "vtkIOLegacy-7.0.lib")
#pragma comment( lib, "vtkIOLSDyna-7.0.lib")
#pragma comment( lib, "vtkIOMINC-7.0.lib")
#pragma comment( lib, "vtkIOMovie-7.0.lib")
#pragma comment( lib, "vtkIONetCDF-7.0.lib")
#pragma comment( lib, "vtkIOParallel-7.0.lib")
#pragma comment( lib, "vtkIOParallelXML-7.0.lib")
#pragma comment( lib, "vtkIOPLY-7.0.lib")
#pragma comment( lib, "vtkIOSQL-7.0.lib")
#pragma comment( lib, "vtkIOVideo-7.0.lib")
#pragma comment( lib, "vtkIOXML-7.0.lib")
#pragma comment( lib, "vtkIOXMLParser-7.0.lib")
#pragma comment( lib, "vtkjpeg-7.0.lib")
#pragma comment( lib, "vtkjsoncpp-7.0.lib")
#pragma comment( lib, "vtklibxml2-7.0.lib")
#pragma comment( lib, "vtkmetaio-7.0.lib")
#pragma comment( lib, "vtkNetCDF-7.0.lib")
#pragma comment( lib, "vtkNetCDF_cxx-7.0.lib")
#pragma comment( lib, "vtkoggtheora-7.0.lib")
#pragma comment( lib, "vtkParallelCore-7.0.lib")
#pragma comment( lib, "vtkpng-7.0.lib")
#pragma comment( lib, "vtkproj4-7.0.lib")
#pragma comment( lib, "vtkRenderingAnnotation-7.0.lib")
#pragma comment( lib, "vtkRenderingContext2D-7.0.lib")
#pragma comment( lib, "vtkRenderingContextOpenGL2-7.0.lib")
#pragma comment( lib, "vtkRenderingCore-7.0.lib")
#pragma comment( lib, "vtkRenderingFreeType-7.0.lib")
#pragma comment( lib, "vtkRenderingImage-7.0.lib")
#pragma comment( lib, "vtkRenderingLabel-7.0.lib")
#pragma comment( lib, "vtkRenderingLOD-7.0.lib")
#pragma comment( lib, "vtkRenderingOpenGL2-7.0.lib")
#pragma comment( lib, "vtkRenderingVolume-7.0.lib")
#pragma comment( lib, "vtkRenderingVolumeOpenGL2-7.0.lib")
#pragma comment( lib, "vtksqlite-7.0.lib")
#pragma comment( lib, "vtksys-7.0.lib")
#pragma comment( lib, "vtktiff-7.0.lib")
#pragma comment( lib, "vtkverdict-7.0.lib")
#pragma comment( lib, "vtkViewsContext2D-7.0.lib")
#pragma comment( lib, "vtkViewsCore-7.0.lib")
#pragma comment( lib, "vtkViewsInfovis-7.0.lib")
#pragma comment( lib, "vtkzlib-7.0.lib")
#endif

#if VTK_VER == 711
#pragma comment( lib, "vtkalglib-7.1.lib")
#pragma comment( lib, "vtkChartsCore-7.1.lib")
#pragma comment( lib, "vtkCommonColor-7.1.lib")
#pragma comment( lib, "vtkCommonComputationalGeometry-7.1.lib")
#pragma comment( lib, "vtkCommonCore-7.1.lib")
#pragma comment( lib, "vtkCommonDataModel-7.1.lib")
#pragma comment( lib, "vtkCommonExecutionModel-7.1.lib")
#pragma comment( lib, "vtkCommonMath-7.1.lib")
#pragma comment( lib, "vtkCommonMisc-7.1.lib")
#pragma comment( lib, "vtkCommonSystem-7.1.lib")
#pragma comment( lib, "vtkCommonTransforms-7.1.lib")
#pragma comment( lib, "vtkDICOMParser-7.1.lib")
#pragma comment( lib, "vtkDomainsChemistry-7.1.lib")
#pragma comment( lib, "vtkDomainsChemistryOpenGL2-7.1.lib")
#pragma comment( lib, "vtkexoIIc-7.1.lib")
#pragma comment( lib, "vtkexpat-7.1.lib")
#pragma comment( lib, "vtkFiltersAMR-7.1.lib")
#pragma comment( lib, "vtkFiltersCore-7.1.lib")
#pragma comment( lib, "vtkFiltersExtraction-7.1.lib")
#pragma comment( lib, "vtkFiltersFlowPaths-7.1.lib")
#pragma comment( lib, "vtkFiltersGeneral-7.1.lib")
#pragma comment( lib, "vtkFiltersGeneric-7.1.lib")
#pragma comment( lib, "vtkFiltersGeometry-7.1.lib")
#pragma comment( lib, "vtkFiltersHybrid-7.1.lib")
#pragma comment( lib, "vtkFiltersHyperTree-7.1.lib")
#pragma comment( lib, "vtkFiltersImaging-7.1.lib")
#pragma comment( lib, "vtkFiltersModeling-7.1.lib")
#pragma comment( lib, "vtkFiltersParallel-7.1.lib")
#pragma comment( lib, "vtkFiltersParallelImaging-7.1.lib")
#pragma comment( lib, "vtkFiltersProgrammable-7.1.lib")
#pragma comment( lib, "vtkFiltersSelection-7.1.lib")
#pragma comment( lib, "vtkFiltersSMP-7.1.lib")
#pragma comment( lib, "vtkFiltersSources-7.1.lib")
#pragma comment( lib, "vtkFiltersStatistics-7.1.lib")
#pragma comment( lib, "vtkFiltersTexture-7.1.lib")
#pragma comment( lib, "vtkFiltersVerdict-7.1.lib")
#pragma comment( lib, "vtkfreetype-7.1.lib")
#pragma comment( lib, "vtkGeovisCore-7.1.lib")
#pragma comment( lib, "vtkglew-7.1.lib")
#pragma comment( lib, "vtkhdf5-7.1.lib")
#pragma comment( lib, "vtkhdf5_hl-7.1.lib")
#pragma comment( lib, "vtkImagingColor-7.1.lib")
#pragma comment( lib, "vtkImagingCore-7.1.lib")
#pragma comment( lib, "vtkImagingFourier-7.1.lib")
#pragma comment( lib, "vtkImagingGeneral-7.1.lib")
#pragma comment( lib, "vtkImagingHybrid-7.1.lib")
#pragma comment( lib, "vtkImagingMath-7.1.lib")
#pragma comment( lib, "vtkImagingMorphological-7.1.lib")
#pragma comment( lib, "vtkImagingSources-7.1.lib")
#pragma comment( lib, "vtkImagingStatistics-7.1.lib")
#pragma comment( lib, "vtkImagingStencil-7.1.lib")
#pragma comment( lib, "vtkInfovisCore-7.1.lib")
#pragma comment( lib, "vtkInfovisLayout-7.1.lib")
#pragma comment( lib, "vtkInteractionImage-7.1.lib")
#pragma comment( lib, "vtkInteractionStyle-7.1.lib")
#pragma comment( lib, "vtkInteractionWidgets-7.1.lib")
#pragma comment( lib, "vtkIOAMR-7.1.lib")
#pragma comment( lib, "vtkIOCore-7.1.lib")
#pragma comment( lib, "vtkIOEnSight-7.1.lib")
#pragma comment( lib, "vtkIOExodus-7.1.lib")
#pragma comment( lib, "vtkIOExport-7.1.lib")
#pragma comment( lib, "vtkIOGeometry-7.1.lib")
#pragma comment( lib, "vtkIOImage-7.1.lib")
#pragma comment( lib, "vtkIOImport-7.1.lib")
#pragma comment( lib, "vtkIOInfovis-7.1.lib")
#pragma comment( lib, "vtkIOLegacy-7.1.lib")
#pragma comment( lib, "vtkIOLSDyna-7.1.lib")
#pragma comment( lib, "vtkIOMINC-7.1.lib")
#pragma comment( lib, "vtkIOMovie-7.1.lib")
#pragma comment( lib, "vtkIONetCDF-7.1.lib")
#pragma comment( lib, "vtkIOParallel-7.1.lib")
#pragma comment( lib, "vtkIOParallelXML-7.1.lib")
#pragma comment( lib, "vtkIOPLY-7.1.lib")
#pragma comment( lib, "vtkIOSQL-7.1.lib")
#pragma comment( lib, "vtkIOVideo-7.1.lib")
#pragma comment( lib, "vtkIOXML-7.1.lib")
#pragma comment( lib, "vtkIOXMLParser-7.1.lib")
#pragma comment( lib, "vtkjpeg-7.1.lib")
#pragma comment( lib, "vtkjsoncpp-7.1.lib")
#pragma comment( lib, "vtklibxml2-7.1.lib")
#pragma comment( lib, "vtkmetaio-7.1.lib")
#pragma comment( lib, "vtkNetCDF-7.1.lib")
#pragma comment( lib, "vtkNetCDF_cxx-7.1.lib")
#pragma comment( lib, "vtkoggtheora-7.1.lib")
#pragma comment( lib, "vtkParallelCore-7.1.lib")
#pragma comment( lib, "vtkpng-7.1.lib")
#pragma comment( lib, "vtkproj4-7.1.lib")
#pragma comment( lib, "vtkRenderingAnnotation-7.1.lib")
#pragma comment( lib, "vtkRenderingContext2D-7.1.lib")
#pragma comment( lib, "vtkRenderingContextOpenGL2-7.1.lib")
#pragma comment( lib, "vtkRenderingCore-7.1.lib")
#pragma comment( lib, "vtkRenderingFreeType-7.1.lib")
#pragma comment( lib, "vtkRenderingImage-7.1.lib")
#pragma comment( lib, "vtkRenderingLabel-7.1.lib")
#pragma comment( lib, "vtkRenderingLOD-7.1.lib")
#pragma comment( lib, "vtkRenderingOpenGL2-7.1.lib")
#pragma comment( lib, "vtkRenderingVolume-7.1.lib")
#pragma comment( lib, "vtkRenderingVolumeOpenGL2-7.1.lib")
#pragma comment( lib, "vtksqlite-7.1.lib")
#pragma comment( lib, "vtksys-7.1.lib")
#pragma comment( lib, "vtktiff-7.1.lib")
#pragma comment( lib, "vtkverdict-7.1.lib")
#pragma comment( lib, "vtkViewsContext2D-7.1.lib")
#pragma comment( lib, "vtkViewsCore-7.1.lib")
#pragma comment( lib, "vtkViewsInfovis-7.1.lib")
#pragma comment( lib, "vtkzlib-7.1.lib")
#endif

#if VTK_VER == 811
#pragma comment( lib, "vtkalglib-8.1.lib")
#pragma comment( lib, "vtkChartsCore-8.1.lib")
#pragma comment( lib, "vtkCommonColor-8.1.lib")
#pragma comment( lib, "vtkCommonComputationalGeometry-8.1.lib")
#pragma comment( lib, "vtkCommonCore-8.1.lib")
#pragma comment( lib, "vtkCommonDataModel-8.1.lib")
#pragma comment( lib, "vtkCommonExecutionModel-8.1.lib")
#pragma comment( lib, "vtkCommonMath-8.1.lib")
#pragma comment( lib, "vtkCommonMisc-8.1.lib")
#pragma comment( lib, "vtkCommonSystem-8.1.lib")
#pragma comment( lib, "vtkCommonTransforms-8.1.lib")
#pragma comment( lib, "vtkDICOMParser-8.1.lib")
#pragma comment( lib, "vtkDomainsChemistry-8.1.lib")
#pragma comment( lib, "vtkDomainsChemistryOpenGL2-8.1.lib")
#pragma comment( lib, "vtkexoIIc-8.1.lib")
#pragma comment( lib, "vtkexpat-8.1.lib")
#pragma comment( lib, "vtkFiltersAMR-8.1.lib")
#pragma comment( lib, "vtkFiltersCore-8.1.lib")
#pragma comment( lib, "vtkFiltersExtraction-8.1.lib")
#pragma comment( lib, "vtkFiltersFlowPaths-8.1.lib")
#pragma comment( lib, "vtkFiltersGeneral-8.1.lib")
#pragma comment( lib, "vtkFiltersGeneric-8.1.lib")
#pragma comment( lib, "vtkFiltersGeometry-8.1.lib")
#pragma comment( lib, "vtkFiltersHybrid-8.1.lib")
#pragma comment( lib, "vtkFiltersHyperTree-8.1.lib")
#pragma comment( lib, "vtkFiltersImaging-8.1.lib")
#pragma comment( lib, "vtkFiltersModeling-8.1.lib")
#pragma comment( lib, "vtkFiltersParallel-8.1.lib")
#pragma comment( lib, "vtkFiltersParallelImaging-8.1.lib")
#pragma comment( lib, "vtkFiltersProgrammable-8.1.lib")
#pragma comment( lib, "vtkFiltersSelection-8.1.lib")
#pragma comment( lib, "vtkFiltersSMP-8.1.lib")
#pragma comment( lib, "vtkFiltersSources-8.1.lib")
#pragma comment( lib, "vtkFiltersStatistics-8.1.lib")
#pragma comment( lib, "vtkFiltersTexture-8.1.lib")
#pragma comment( lib, "vtkFiltersVerdict-8.1.lib")
#pragma comment( lib, "vtkfreetype-8.1.lib")
#pragma comment( lib, "vtkGeovisCore-8.1.lib")
#pragma comment( lib, "vtkglew-8.1.lib")
#pragma comment( lib, "vtkhdf5-8.1.lib")
#pragma comment( lib, "vtkhdf5_hl-8.1.lib")
#pragma comment( lib, "vtkImagingColor-8.1.lib")
#pragma comment( lib, "vtkImagingCore-8.1.lib")
#pragma comment( lib, "vtkImagingFourier-8.1.lib")
#pragma comment( lib, "vtkImagingGeneral-8.1.lib")
#pragma comment( lib, "vtkImagingHybrid-8.1.lib")
#pragma comment( lib, "vtkImagingMath-8.1.lib")
#pragma comment( lib, "vtkImagingMorphological-8.1.lib")
#pragma comment( lib, "vtkImagingSources-8.1.lib")
#pragma comment( lib, "vtkImagingStatistics-8.1.lib")
#pragma comment( lib, "vtkImagingStencil-8.1.lib")
#pragma comment( lib, "vtkInfovisCore-8.1.lib")
#pragma comment( lib, "vtkInfovisLayout-8.1.lib")
#pragma comment( lib, "vtkInteractionImage-8.1.lib")
#pragma comment( lib, "vtkInteractionStyle-8.1.lib")
#pragma comment( lib, "vtkInteractionWidgets-8.1.lib")
#pragma comment( lib, "vtkIOAMR-8.1.lib")
#pragma comment( lib, "vtkIOCore-8.1.lib")
#pragma comment( lib, "vtkIOEnSight-8.1.lib")
#pragma comment( lib, "vtkIOExodus-8.1.lib")
#pragma comment( lib, "vtkIOExport-8.1.lib")
#pragma comment( lib, "vtkIOGeometry-8.1.lib")
#pragma comment( lib, "vtkIOImage-8.1.lib")
#pragma comment( lib, "vtkIOImport-8.1.lib")
#pragma comment( lib, "vtkIOInfovis-8.1.lib")
#pragma comment( lib, "vtkIOLegacy-8.1.lib")
#pragma comment( lib, "vtkIOLSDyna-8.1.lib")
#pragma comment( lib, "vtkIOMINC-8.1.lib")
#pragma comment( lib, "vtkIOMovie-8.1.lib")
#pragma comment( lib, "vtkIONetCDF-8.1.lib")
#pragma comment( lib, "vtkIOParallel-8.1.lib")
#pragma comment( lib, "vtkIOParallelXML-8.1.lib")
#pragma comment( lib, "vtkIOPLY-8.1.lib")
#pragma comment( lib, "vtkIOSQL-8.1.lib")
#pragma comment( lib, "vtkIOVideo-8.1.lib")
#pragma comment( lib, "vtkIOXML-8.1.lib")
#pragma comment( lib, "vtkIOXMLParser-8.1.lib")
#pragma comment( lib, "vtkjpeg-8.1.lib")
#pragma comment( lib, "vtkjsoncpp-8.1.lib")
#pragma comment( lib, "vtklibxml2-8.1.lib")
#pragma comment( lib, "vtkmetaio-8.1.lib")
#pragma comment( lib, "vtkNetCDF-8.1.lib")
//#pragma comment( lib, "vtkNetCDF_cxx-8.1.lib")
#pragma comment( lib, "vtkoggtheora-8.1.lib")
#pragma comment( lib, "vtkParallelCore-8.1.lib")
#pragma comment( lib, "vtkpng-8.1.lib")
#pragma comment( lib, "vtkproj4-8.1.lib")
#pragma comment( lib, "vtkRenderingAnnotation-8.1.lib")
#pragma comment( lib, "vtkRenderingContext2D-8.1.lib")
#pragma comment( lib, "vtkRenderingContextOpenGL2-8.1.lib")
#pragma comment( lib, "vtkRenderingCore-8.1.lib")
#pragma comment( lib, "vtkRenderingFreeType-8.1.lib")
#pragma comment( lib, "vtkRenderingImage-8.1.lib")
#pragma comment( lib, "vtkRenderingLabel-8.1.lib")
#pragma comment( lib, "vtkRenderingLOD-8.1.lib")
#pragma comment( lib, "vtkRenderingOpenGL2-8.1.lib")
#pragma comment( lib, "vtkRenderingVolume-8.1.lib")
#pragma comment( lib, "vtkRenderingVolumeOpenGL2-8.1.lib")
#pragma comment( lib, "vtksqlite-8.1.lib")
#pragma comment( lib, "vtksys-8.1.lib")
#pragma comment( lib, "vtktiff-8.1.lib")
#pragma comment( lib, "vtkverdict-8.1.lib")
#pragma comment( lib, "vtkViewsContext2D-8.1.lib")
#pragma comment( lib, "vtkViewsCore-8.1.lib")
#pragma comment( lib, "vtkViewsInfovis-8.1.lib")
#pragma comment( lib, "vtkzlib-8.1.lib")
#endif

#if VTK_VER == 820
//#pragma comment( lib, "vtkalglib-8.2.lib")
#pragma comment( lib, "vtkChartsCore-8.2.lib")
#pragma comment( lib, "vtkCommonColor-8.2.lib")
#pragma comment( lib, "vtkCommonComputationalGeometry-8.2.lib")
#pragma comment( lib, "vtkCommonCore-8.2.lib")
#pragma comment( lib, "vtkCommonDataModel-8.2.lib")
#pragma comment( lib, "vtkCommonExecutionModel-8.2.lib")
#pragma comment( lib, "vtkCommonMath-8.2.lib")
#pragma comment( lib, "vtkCommonMisc-8.2.lib")
#pragma comment( lib, "vtkCommonSystem-8.2.lib")
#pragma comment( lib, "vtkCommonTransforms-8.2.lib")
#pragma comment( lib, "vtkDICOMParser-8.2.lib")
#pragma comment( lib, "vtkDomainsChemistry-8.2.lib")
#pragma comment( lib, "vtkDomainsChemistryOpenGL2-8.2.lib")
//#pragma comment( lib, "vtkexoIIc-8.2.lib")
#pragma comment( lib, "vtkexpat-8.2.lib")
#pragma comment( lib, "vtkFiltersAMR-8.2.lib")
#pragma comment( lib, "vtkFiltersCore-8.2.lib")
#pragma comment( lib, "vtkFiltersExtraction-8.2.lib")
#pragma comment( lib, "vtkFiltersFlowPaths-8.2.lib")
#pragma comment( lib, "vtkFiltersGeneral-8.2.lib")
#pragma comment( lib, "vtkFiltersGeneric-8.2.lib")
#pragma comment( lib, "vtkFiltersGeometry-8.2.lib")
#pragma comment( lib, "vtkFiltersHybrid-8.2.lib")
#pragma comment( lib, "vtkFiltersHyperTree-8.2.lib")
#pragma comment( lib, "vtkFiltersImaging-8.2.lib")
#pragma comment( lib, "vtkFiltersModeling-8.2.lib")
#pragma comment( lib, "vtkFiltersParallel-8.2.lib")
#pragma comment( lib, "vtkFiltersParallelImaging-8.2.lib")
#pragma comment( lib, "vtkFiltersProgrammable-8.2.lib")
#pragma comment( lib, "vtkFiltersSelection-8.2.lib")
#pragma comment( lib, "vtkFiltersSMP-8.2.lib")
#pragma comment( lib, "vtkFiltersSources-8.2.lib")
#pragma comment( lib, "vtkFiltersStatistics-8.2.lib")
#pragma comment( lib, "vtkFiltersTexture-8.2.lib")
#pragma comment( lib, "vtkFiltersVerdict-8.2.lib")
#pragma comment( lib, "vtkfreetype-8.2.lib")
#pragma comment( lib, "vtkGeovisCore-8.2.lib")
#pragma comment( lib, "vtkglew-8.2.lib")
#pragma comment( lib, "vtkhdf5-8.2.lib")
#pragma comment( lib, "vtkhdf5_hl-8.2.lib")
#pragma comment( lib, "vtkImagingColor-8.2.lib")
#pragma comment( lib, "vtkImagingCore-8.2.lib")
#pragma comment( lib, "vtkImagingFourier-8.2.lib")
#pragma comment( lib, "vtkImagingGeneral-8.2.lib")
#pragma comment( lib, "vtkImagingHybrid-8.2.lib")
#pragma comment( lib, "vtkImagingMath-8.2.lib")
#pragma comment( lib, "vtkImagingMorphological-8.2.lib")
#pragma comment( lib, "vtkImagingSources-8.2.lib")
#pragma comment( lib, "vtkImagingStatistics-8.2.lib")
#pragma comment( lib, "vtkImagingStencil-8.2.lib")
#pragma comment( lib, "vtkInfovisCore-8.2.lib")
#pragma comment( lib, "vtkInfovisLayout-8.2.lib")
#pragma comment( lib, "vtkInteractionImage-8.2.lib")
#pragma comment( lib, "vtkInteractionStyle-8.2.lib")
#pragma comment( lib, "vtkInteractionWidgets-8.2.lib")
#pragma comment( lib, "vtkIOAMR-8.2.lib")
#pragma comment( lib, "vtkIOCore-8.2.lib")
#pragma comment( lib, "vtkIOEnSight-8.2.lib")
#pragma comment( lib, "vtkIOExodus-8.2.lib")
#pragma comment( lib, "vtkIOExport-8.2.lib")
#pragma comment( lib, "vtkIOGeometry-8.2.lib")
#pragma comment( lib, "vtkIOImage-8.2.lib")
#pragma comment( lib, "vtkIOImport-8.2.lib")
#pragma comment( lib, "vtkIOInfovis-8.2.lib")
#pragma comment( lib, "vtkIOLegacy-8.2.lib")
#pragma comment( lib, "vtkIOLSDyna-8.2.lib")
#pragma comment( lib, "vtkIOMINC-8.2.lib")
#pragma comment( lib, "vtkIOMovie-8.2.lib")
#pragma comment( lib, "vtkIONetCDF-8.2.lib")
#pragma comment( lib, "vtkIOParallel-8.2.lib")
#pragma comment( lib, "vtkIOParallelXML-8.2.lib")
#pragma comment( lib, "vtkIOPLY-8.2.lib")
#pragma comment( lib, "vtkIOSQL-8.2.lib")
#pragma comment( lib, "vtkIOVideo-8.2.lib")
#pragma comment( lib, "vtkIOXML-8.2.lib")
#pragma comment( lib, "vtkIOXMLParser-8.2.lib")
#pragma comment( lib, "vtkjpeg-8.2.lib")
#pragma comment( lib, "vtkjsoncpp-8.2.lib")
#pragma comment( lib, "vtklibxml2-8.2.lib")
#pragma comment( lib, "vtkmetaio-8.2.lib")
#pragma comment( lib, "vtkNetCDF-8.2.lib")
//#pragma comment( lib, "vtkNetCDF_cxx-8.2.lib")
//#pragma comment( lib, "vtkoggtheora-8.2.lib")
#pragma comment( lib, "vtkParallelCore-8.2.lib")
#pragma comment( lib, "vtkpng-8.2.lib")
//#pragma comment( lib, "vtkproj4-8.2.lib")
#pragma comment( lib, "vtkRenderingAnnotation-8.2.lib")
#pragma comment( lib, "vtkRenderingContext2D-8.2.lib")
#pragma comment( lib, "vtkRenderingContextOpenGL2-8.2.lib")
#pragma comment( lib, "vtkRenderingCore-8.2.lib")
#pragma comment( lib, "vtkRenderingFreeType-8.2.lib")
#pragma comment( lib, "vtkRenderingImage-8.2.lib")
#pragma comment( lib, "vtkRenderingLabel-8.2.lib")
#pragma comment( lib, "vtkRenderingLOD-8.2.lib")
#pragma comment( lib, "vtkRenderingOpenGL2-8.2.lib")
#pragma comment( lib, "vtkRenderingVolume-8.2.lib")
#pragma comment( lib, "vtkRenderingVolumeOpenGL2-8.2.lib")
#pragma comment( lib, "vtksqlite-8.2.lib")
#pragma comment( lib, "vtksys-8.2.lib")
#pragma comment( lib, "vtktiff-8.2.lib")
#pragma comment( lib, "vtkverdict-8.2.lib")
#pragma comment( lib, "vtkViewsContext2D-8.2.lib")
#pragma comment( lib, "vtkViewsCore-8.2.lib")
#pragma comment( lib, "vtkViewsInfovis-8.2.lib")
#pragma comment( lib, "vtkzlib-8.2.lib")
#endif

#if VTK_VER == 940
#pragma comment( lib, "vtkcgns-9.4.lib")
#pragma comment( lib, "vtkChartsCore-9.4.lib")
#pragma comment( lib, "vtkCommonColor-9.4.lib")
#pragma comment( lib, "vtkCommonComputationalGeometry-9.4.lib")
#pragma comment( lib, "vtkCommonCore-9.4.lib")
#pragma comment( lib, "vtkCommonDataModel-9.4.lib")
#pragma comment( lib, "vtkCommonExecutionModel-9.4.lib")
#pragma comment( lib, "vtkCommonMath-9.4.lib")
#pragma comment( lib, "vtkCommonMisc-9.4.lib")
#pragma comment( lib, "vtkCommonSystem-9.4.lib")
#pragma comment( lib, "vtkCommonTransforms-9.4.lib")
#pragma comment( lib, "vtkDICOMParser-9.4.lib")
#pragma comment( lib, "vtkDomainsChemistry-9.4.lib")
#pragma comment( lib, "vtkDomainsChemistryOpenGL2-9.4.lib")
#pragma comment( lib, "vtkdoubleconversion-9.4.lib")
#pragma comment( lib, "vtkexodusII-9.4.lib")
#pragma comment( lib, "vtkexpat-9.4.lib")
#pragma comment( lib, "vtkFiltersAMR-9.4.lib")
#pragma comment( lib, "vtkFiltersCellGrid-9.4.lib")
#pragma comment( lib, "vtkFiltersCore-9.4.lib")
#pragma comment( lib, "vtkFiltersExtraction-9.4.lib")
#pragma comment( lib, "vtkFiltersFlowPaths-9.4.lib")
#pragma comment( lib, "vtkFiltersGeneral-9.4.lib")
#pragma comment( lib, "vtkFiltersGeneric-9.4.lib")
#pragma comment( lib, "vtkFiltersGeometry-9.4.lib")
#pragma comment( lib, "vtkFiltersGeometryPreview-9.4.lib")
#pragma comment( lib, "vtkFiltersHybrid-9.4.lib")
#pragma comment( lib, "vtkFiltersHyperTree-9.4.lib")
#pragma comment( lib, "vtkFiltersImaging-9.4.lib")
#pragma comment( lib, "vtkFiltersModeling-9.4.lib")
#pragma comment( lib, "vtkFiltersParallel-9.4.lib")
#pragma comment( lib, "vtkFiltersParallelImaging-9.4.lib")
#pragma comment( lib, "vtkFiltersPoints-9.4.lib")
#pragma comment( lib, "vtkFiltersProgrammable-9.4.lib")
#pragma comment( lib, "vtkFiltersReduction-9.4.lib")
#pragma comment( lib, "vtkFiltersSelection-9.4.lib")
#pragma comment( lib, "vtkFiltersSMP-9.4.lib")
#pragma comment( lib, "vtkFiltersSources-9.4.lib")
#pragma comment( lib, "vtkFiltersStatistics-9.4.lib")
#pragma comment( lib, "vtkFiltersTemporal-9.4.lib")
#pragma comment( lib, "vtkFiltersTensor-9.4.lib")
#pragma comment( lib, "vtkFiltersTexture-9.4.lib")
#pragma comment( lib, "vtkFiltersTopology-9.4.lib")
#pragma comment( lib, "vtkFiltersVerdict-9.4.lib")
#pragma comment( lib, "vtkfmt-9.4.lib")
#pragma comment( lib, "vtkfreetype-9.4.lib")
#pragma comment( lib, "vtkGeovisCore-9.4.lib")
#pragma comment( lib, "vtkgl2ps-9.4.lib")
#pragma comment( lib, "vtkglad-9.4.lib")
#pragma comment( lib, "vtkhdf5-9.4.lib")
#pragma comment( lib, "vtkhdf5_hl-9.4.lib")
#pragma comment( lib, "vtkImagingColor-9.4.lib")
#pragma comment( lib, "vtkImagingCore-9.4.lib")
#pragma comment( lib, "vtkImagingFourier-9.4.lib")
#pragma comment( lib, "vtkImagingGeneral-9.4.lib")
#pragma comment( lib, "vtkImagingHybrid-9.4.lib")
#pragma comment( lib, "vtkImagingMath-9.4.lib")
#pragma comment( lib, "vtkImagingMorphological-9.4.lib")
#pragma comment( lib, "vtkImagingSources-9.4.lib")
#pragma comment( lib, "vtkImagingStatistics-9.4.lib")
#pragma comment( lib, "vtkImagingStencil-9.4.lib")
#pragma comment( lib, "vtkInfovisCore-9.4.lib")
#pragma comment( lib, "vtkInfovisLayout-9.4.lib")
#pragma comment( lib, "vtkInteractionImage-9.4.lib")
#pragma comment( lib, "vtkInteractionStyle-9.4.lib")
#pragma comment( lib, "vtkInteractionWidgets-9.4.lib")
#pragma comment( lib, "vtkIOAMR-9.4.lib")
#pragma comment( lib, "vtkIOAsynchronous-9.4.lib")
#pragma comment( lib, "vtkIOCellGrid-9.4.lib")
#pragma comment( lib, "vtkIOCesium3DTiles-9.4.lib")
#pragma comment( lib, "vtkIOCGNSReader-9.4.lib")
#pragma comment( lib, "vtkIOChemistry-9.4.lib")
#pragma comment( lib, "vtkIOCityGML-9.4.lib")
#pragma comment( lib, "vtkIOCONVERGECFD-9.4.lib")
#pragma comment( lib, "vtkIOCore-9.4.lib")
#pragma comment( lib, "vtkIOEngys-9.4.lib")
#pragma comment( lib, "vtkIOEnSight-9.4.lib")
#pragma comment( lib, "vtkIOERF-9.4.lib")
#pragma comment( lib, "vtkIOExodus-9.4.lib")
#pragma comment( lib, "vtkIOExport-9.4.lib")
#pragma comment( lib, "vtkIOExportGL2PS-9.4.lib")
#pragma comment( lib, "vtkIOExportPDF-9.4.lib")
#pragma comment( lib, "vtkIOFDS-9.4.lib")
#pragma comment( lib, "vtkIOFLUENTCFF-9.4.lib")
#pragma comment( lib, "vtkIOGeometry-9.4.lib")
#pragma comment( lib, "vtkIOHDF-9.4.lib")
#pragma comment( lib, "vtkIOImage-9.4.lib")
#pragma comment( lib, "vtkIOImport-9.4.lib")
#pragma comment( lib, "vtkIOInfovis-9.4.lib")
#pragma comment( lib, "vtkIOIOSS-9.4.lib")
#pragma comment( lib, "vtkIOLegacy-9.4.lib")
#pragma comment( lib, "vtkIOLSDyna-9.4.lib")
#pragma comment( lib, "vtkIOMINC-9.4.lib")
#pragma comment( lib, "vtkIOMotionFX-9.4.lib")
#pragma comment( lib, "vtkIOMovie-9.4.lib")
#pragma comment( lib, "vtkIONetCDF-9.4.lib")
#pragma comment( lib, "vtkIOOggTheora-9.4.lib")
#pragma comment( lib, "vtkIOParallel-9.4.lib")
#pragma comment( lib, "vtkIOParallelXML-9.4.lib")
#pragma comment( lib, "vtkIOPLY-9.4.lib")
#pragma comment( lib, "vtkIOSegY-9.4.lib")
#pragma comment( lib, "vtkIOSQL-9.4.lib")
#pragma comment( lib, "vtkioss-9.4.lib")
#pragma comment( lib, "vtkIOTecplotTable-9.4.lib")
#pragma comment( lib, "vtkIOVeraOut-9.4.lib")
#pragma comment( lib, "vtkIOVideo-9.4.lib")
#pragma comment( lib, "vtkIOXML-9.4.lib")
#pragma comment( lib, "vtkIOXMLParser-9.4.lib")
#pragma comment( lib, "vtkjpeg-9.4.lib")
#pragma comment( lib, "vtkjsoncpp-9.4.lib")
#pragma comment( lib, "vtkkissfft-9.4.lib")
#pragma comment( lib, "vtklibharu-9.4.lib")
#pragma comment( lib, "vtklibproj-9.4.lib")
#pragma comment( lib, "vtklibxml2-9.4.lib")
#pragma comment( lib, "vtkloguru-9.4.lib")
#pragma comment( lib, "vtklz4-9.4.lib")
#pragma comment( lib, "vtklzma-9.4.lib")
#pragma comment( lib, "vtkmetaio-9.4.lib")
#pragma comment( lib, "vtknetcdf-9.4.lib")
#pragma comment( lib, "vtkogg-9.4.lib")
#pragma comment( lib, "vtkParallelCore-9.4.lib")
#pragma comment( lib, "vtkParallelDIY-9.4.lib")
#pragma comment( lib, "vtkpng-9.4.lib")
#pragma comment( lib, "vtkpugixml-9.4.lib")
#pragma comment( lib, "vtkRenderingAnnotation-9.4.lib")
#pragma comment( lib, "vtkRenderingCellGrid-9.4.lib")
#pragma comment( lib, "vtkRenderingContext2D-9.4.lib")
#pragma comment( lib, "vtkRenderingContextOpenGL2-9.4.lib")
#pragma comment( lib, "vtkRenderingCore-9.4.lib")
#pragma comment( lib, "vtkRenderingFreeType-9.4.lib")
#pragma comment( lib, "vtkRenderingGL2PSOpenGL2-9.4.lib")
#pragma comment( lib, "vtkRenderingHyperTreeGrid-9.4.lib")
#pragma comment( lib, "vtkRenderingImage-9.4.lib")
#pragma comment( lib, "vtkRenderingLabel-9.4.lib")
#pragma comment( lib, "vtkRenderingLICOpenGL2-9.4.lib")
#pragma comment( lib, "vtkRenderingLOD-9.4.lib")
#pragma comment( lib, "vtkRenderingOpenGL2-9.4.lib")
#pragma comment( lib, "vtkRenderingSceneGraph-9.4.lib")
#pragma comment( lib, "vtkRenderingUI-9.4.lib")
#pragma comment( lib, "vtkRenderingVolume-9.4.lib")
#pragma comment( lib, "vtkRenderingVolumeOpenGL2-9.4.lib")
#pragma comment( lib, "vtkRenderingVtkJS-9.4.lib")
#pragma comment( lib, "vtksqlite-9.4.lib")
#pragma comment( lib, "vtksys-9.4.lib")
#pragma comment( lib, "vtkTestingCore-9.4.lib")
#pragma comment( lib, "vtkTestingRendering-9.4.lib")
#pragma comment( lib, "vtktheora-9.4.lib")
#pragma comment( lib, "vtktiff-9.4.lib")
#pragma comment( lib, "vtktoken-9.4.lib")
#pragma comment( lib, "vtkverdict-9.4.lib")
#pragma comment( lib, "vtkViewsContext2D-9.4.lib")
#pragma comment( lib, "vtkViewsCore-9.4.lib")
#pragma comment( lib, "vtkViewsInfovis-9.4.lib")
#pragma comment( lib, "vtkWrappingTools-9.4.lib")
#pragma comment( lib, "vtkzlib-9.4.lib")
#endif

#ifndef NO_LINK_LIBS
#ifdef _WIN64
#ifdef _DEBUG
#pragma comment( lib, "../../vtkFreeWrapper/util/lib/Debug/64bit/vtkWrapperLib.lib" )
#else
#pragma comment( lib, "../../vtkFreeWrapper/util/lib/Release/64bit/vtkWrapperLib.lib" )
#endif
#else
#ifdef _DEBUG
#pragma comment( lib, "../../vtkFreeWrapper/util/lib/Debug/32bit/vtkWrapperLib.lib" )
#else
#pragma comment( lib, "../../vtkFreeWrapper/util/lib/Release/32bit/vtkWrapperLib.lib" )
#endif
#endif
#endif

#ifdef WIN32
#pragma comment( lib, "opengl32.lib" )
#pragma comment( lib, "vfw32.lib")

#if VTK_VER == 940
#pragma comment( lib, "ws2_32.lib")
#pragma comment( lib, "Psapi.lib")
#pragma comment( lib, "Dbghelp.lib")
#endif

#endif

#endif
