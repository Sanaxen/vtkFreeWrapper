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
 * ポリゴンデータ出力（抽象クラス）
 */
#ifndef _GMRVTKEXPORT_HPP
#define _GMRVTKEXPORT_HPP

#include "gmrVTK.hpp"
#include "gmrVTKRender.hpp"
#include "gmrVTKDefs.hpp"

class gmrVTKExportSTL;
class gmrVTKExportPLY;
class gmrVTKExportOBJ;
class gmrVTKExportX3D;
class gmrVTKExportVRML;

/** 
 * @brief ポリゴンデータ出力（抽象クラス）
 *
 */

class gmr_EXPORT gmrVTKExport
{
	friend gmrVTKExportSTL;
	friend gmrVTKExportPLY;
	friend gmrVTKExportOBJ;
	friend gmrVTKExportX3D;
	friend gmrVTKExportVRML;


public:
	gmrVTKExport();
	virtual ~gmrVTKExport();
	void SaveFile( gmrVTKRender* renwin, char* filename);
	void SaveFile( vtkAlgorithmOutput* input, char* filename);
};

class gmr_EXPORT gmrVTKExportSTL: public gmrVTKExport
{
	vtkSTLWriter* stlWriter_;

public:
	/** コンストラクタ
	 *
	 */
	gmrVTKExportSTL();
	virtual ~gmrVTKExportSTL();

	/** ファイル保存
	 *
	 * @param [in] input データ->GetOutputPort()
	 * @param [in] filename エクスポートファイル名
	 */
	void SaveFile( vtkAlgorithmOutput* input, char* filename);
	vtkSTLWriter*Get() { return stlWriter_; }
};

class gmr_EXPORT gmrVTKExportPLY: public gmrVTKExport
{
	vtkPLYWriter* plyWriter_;
public:

	/** コンストラクタ
	 *
	 */
	gmrVTKExportPLY();
	virtual ~gmrVTKExportPLY();

	/** ファイル保存
	 *
	 * @param [in] input データ->GetOutputPort()
	 * @param [in] filename エクスポートファイル名
	 */
	void SaveFile( vtkAlgorithmOutput* input, char* filename, char* colro_name = NULL);
	vtkPLYWriter*Get() { return plyWriter_; }
};

class gmr_EXPORT gmrVTKExportOBJ: public gmrVTKExport
{
	vtkOBJExporter* vtkExporter_;
        
public:
	/** コンストラクタ
	 *
	 * @param [in] filename エクスポートファイル名
	 */
	gmrVTKExportOBJ();
	virtual ~gmrVTKExportOBJ();

	/** ファイル保存
	 *
	 * @param [in] renwin レンダリング（シーン）
	 * @param [in] filename エクスポートファイル名
	 */
	void SaveFile( gmrVTKRender* renwin, char* filename);

	vtkOBJExporter*Get() { return vtkExporter_; }

	inline int exportVertexColorOBJ(char* filename, vtkPolyData* poly, vtkSmartPointer<vtkPolyDataMapper>& Mapper, vtkSmartPointer<vtkActor>& Actor)
	{
		double opacity = Actor->GetProperty()->GetOpacity();
		vtkUnsignedCharArray* color_array = Mapper->MapScalars(opacity);
		if (color_array == NULL)
		{
			return 1;
		}

		int comp = color_array->GetNumberOfComponents();

		printf("GetNumberOfComponents:%d Name:[%s]\n", comp, color_array->GetName());
		printf("GetNumberOfValues:%lld %I64d\n", color_array->GetNumberOfValues(), color_array->GetNumberOfValues() / comp);

		vtkSmartPointer<vtkPoints> vertices = poly->GetPoints();
		vtkSmartPointer<vtkDataArray> verticesArray = vertices->GetData();

		long long numberOfVertices = vertices->GetNumberOfPoints();
		printf("numberOfVertices:%I64d\n", numberOfVertices);

		bool vertex_color_use = false;
		if (comp >= 3 && numberOfVertices == color_array->GetNumberOfValues() / comp)
		{
			vertex_color_use = true;
		}
		if (!vertex_color_use)
		{
			return 1;
		}
		FILE* fp = fopen(filename, "w");
		if (fp == NULL)
		{
			char szFullPath[_MAX_PATH] = { '\0' };
			char *szFilePart;
			DWORD dwRet = GetFullPathNameA(filename, _MAX_PATH, szFullPath, &szFilePart);
			if (fp == NULL)
			{
				printf("file open error,[%s]\n", szFullPath);
				if (strlen(szFullPath) >= _MAX_PATH || dwRet == 0)
				{
					printf("FullPathName failed.!\n");
				}
			}
		}

		if (fp == NULL) return -1;

		for (int i = 0; i < numberOfVertices; i++)
		{
			double x = verticesArray->GetComponent(i, 0);
			double y = verticesArray->GetComponent(i, 1);
			double z = verticesArray->GetComponent(i, 2);
			fprintf(fp, "v %f %f %f", x, y, z);
			fprintf(fp, " %.3f %.3f %.3f\n",
				color_array->GetComponent(i, 0),
				color_array->GetComponent(i, 1),
				color_array->GetComponent(i, 2));
		}
		int  numberOfFaces = poly->GetNumberOfCells();

		for (int i = 0; i < numberOfFaces; i++)
		{
			vtkSmartPointer<vtkIdList> face = vtkSmartPointer<vtkIdList>::New();
			poly->GetCellPoints(i, face);

			if (face->GetId(0) == face->GetId(1) || face->GetId(0) == face->GetId(2) || face->GetId(2) == face->GetId(1))
			{
				continue;
			}
			int f = face->GetNumberOfIds();
			if (f < 3)
			{
				printf("skipp Faces with fewer than 3 vertices.\n");
				continue;
			}
			fprintf(fp, "f");
			for (int j = 0; j < f; j++)
			{
				fprintf(fp, " %I64d", face->GetId(j) + 1);
			}
			fprintf(fp, "\n");
		}
		fclose(fp);

		return 0;
	}

	inline int exportVertexColorOBJ(char* filename, vtkPolyData* poly, vtkUnsignedCharArray* color_array)
	{

		int comp = color_array->GetNumberOfComponents();

		printf("GetNumberOfComponents:%d Name:[%s]\n", comp, color_array->GetName());
		printf("GetNumberOfValues:%lld %I64d\n", color_array->GetNumberOfValues(), color_array->GetNumberOfValues() / comp);

		vtkSmartPointer<vtkPoints> vertices = poly->GetPoints();
		vtkSmartPointer<vtkDataArray> verticesArray = vertices->GetData();

		long long numberOfVertices = vertices->GetNumberOfPoints();
		printf("numberOfVertices:%I64d\n", numberOfVertices);

		bool vertex_color_use = false;
		if (comp >= 3 && numberOfVertices == color_array->GetNumberOfValues() / comp)
		{
			vertex_color_use = true;
		}
		if (!vertex_color_use)
		{
			return 1;
		}
		FILE* fp = fopen(filename, "w");
		if (fp == NULL)
		{
			printf("file open error,[%s]\n", filename);
			if (strlen(filename) >= _MAX_PATH)
			{
				printf("file name length to long!\n");
			}
		}
		if (fp == NULL) return -1;

		for (int i = 0; i < numberOfVertices; i++)
		{
			double x = verticesArray->GetComponent(i, 0);
			double y = verticesArray->GetComponent(i, 1);
			double z = verticesArray->GetComponent(i, 2);
			fprintf(fp, "v %f %f %f", x, y, z);
			fprintf(fp, " %.3f %.3f %.3f\n",
				color_array->GetComponent(i, 0),
				color_array->GetComponent(i, 1),
				color_array->GetComponent(i, 2));
		}
		int  numberOfFaces = poly->GetNumberOfCells();

		for (int i = 0; i < numberOfFaces; i++)
		{
			vtkSmartPointer<vtkIdList> face = vtkSmartPointer<vtkIdList>::New();
			poly->GetCellPoints(i, face);

			if (face->GetId(0) == face->GetId(1) || face->GetId(0) == face->GetId(2) || face->GetId(2) == face->GetId(1))
			{
				continue;
			}
			int f = face->GetNumberOfIds();
			if (f < 3)
			{
				printf("skipp Faces with fewer than 3 vertices.\n");
				continue;
			}
			fprintf(fp, "f");
			for (int j = 0; j < f; j++)
			{
				fprintf(fp, " %I64d", face->GetId(j) + 1);
			}
			fprintf(fp, "\n");
		}
		fclose(fp);

		return 0;
	}

};

class gmr_EXPORT gmrVTKExportX3D: public gmrVTKExport
{
	vtkX3DExporter* vtkExporter_;
        
public:
	/** コンストラクタ
	 *
	 * @param [in] filename エクスポートファイル名
	 */
	gmrVTKExportX3D();
	virtual ~gmrVTKExportX3D();

	/** ファイル保存
	 *
	 * @param [in] renwin レンダリング（シーン）
	 * @param [in] filename エクスポートファイル名
	 */
	void SaveFile( gmrVTKRender* renwin, char* filename);

};

class gmr_EXPORT gmrVTKExportVRML: public gmrVTKExport
{
	vtkVRMLExporter* vtkExporter_;
        
public:
	/** コンストラクタ
	 *
	 * @param [in] filename エクスポートファイル名
	 */
	gmrVTKExportVRML();
	virtual ~gmrVTKExportVRML();

	/** ファイル保存
	 *
	 * @param [in] renwin レンダリング（シーン）
	 * @param [in] filename エクスポートファイル名
	 */
	void SaveFile( gmrVTKRender* renwin, char* filename);

};

#endif