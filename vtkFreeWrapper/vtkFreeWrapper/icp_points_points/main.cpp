#include "gmrVTKRender.hpp"
#include "gmrVTKImport.hpp"
#include "gmrVTKExport.hpp"

#include "gmrVTKMeshFilter.hpp"

#include "gmrVTK.hpp"

#include <vtkMatrix4x4.h>
#include <vtkTransform.h>
#include <vtkIterativeClosestPointTransform.h>
#include <vtkTransformPolyDataFilter.h>
#include <vtkLandmarkTransform.h>
#include <vtkVertexGlyphFilter.h>
#include "windows.h"

#define NO_LINK_LIBS
#include "gmrVTKLIBs.hpp"
#pragma comment( lib, "../../../vtkFreeWrapper/util/lib/Release/64bit/vtkWrapperLib.lib" )
#pragma comment( lib, "opengl32.lib" )
#pragma comment( lib, "vfw32.lib")

int main(int argc, char** argv)
{
	if (argc < 2)
	{
		printf("icp_points_points.exe -s xyz_file_src -t xyz_file_dst [-i Iterations -landmark sample_landmarks(0..1|1..N) -tol tolerance] -o output\n");
		return -99;
	}

	std::mt19937 mt;
	std::uniform_real_distribution<double> d_rand(0.0, 1.0);

	vtkObject::SetGlobalWarningDisplay(0);

	double sampling = 1.0;
	double sample_landmarks = 1.0;

	double tol = 0.01;
	int iter = 50;
	char* file1 = NULL;
	char* file2 = NULL;
	char* output = NULL;

	for (int i = 1; i < argc; i++)
	{
		if (strcmp(argv[i], "-o") == 0)
		{
			output = argv[i + 1];
			i++;
			continue;
		}
		else if (strcmp(argv[i], "-i") == 0)
		{
			iter = atoi(argv[i + 1]);
			i++;
			continue;
		}
		else if (strcmp(argv[i], "-tol") == 0)
		{
			tol = atof(argv[i + 1]);
			i++;
			continue;
		}
		if (strcmp(argv[i], "-landmark") == 0)
		{
			sample_landmarks = atof(argv[i + 1]);
			i++;
			continue;
		}
		if (strcmp(argv[i], "-smp") == 0)
		{
			sampling = atof(argv[i + 1]);
			i++;
			continue;
		}
		if (strcmp(argv[i], "-s") == 0)
		{
			file1 = argv[i+1];
			i++;
			continue;
		}
		if (strcmp(argv[i], "-t") == 0)
		{
			file2 = argv[i+1];
			i++;
			continue;
		}
	}
	if (file1 == NULL)
	{
		return -1;
	}
	if (file2 == NULL)
	{
		return -1;
	}
	if (iter <= 0)
	{
		return -2;
	}
	if (output == NULL)
	{
		return -3;
	}

	vtkSmartPointer<vtkPoints> points_src = vtkSmartPointer<vtkPoints>::New();
	vtkSmartPointer<vtkPoints> points_tgt = vtkSmartPointer<vtkPoints>::New();

	int stat = readPoints(file1, points_src, sampling, mt, d_rand);
	if (stat != 0)
	{
		printf("xyz (src) read error.\n");
		return -1;
	}
	stat = readPoints(file2, points_tgt, sampling, mt, d_rand);
	if (stat != 0)
	{
		printf("xyz (target) read error.\n");
		return -1;
	}


	//Create TestData
#if 0
	{
		vtkSmartPointer<vtkPoints> test_point = vtkSmartPointer<vtkPoints>::New();
		readPoints(file1, test_point, sampling, mt, d_rand);

		vtkSmartPointer<vtkPolyData> test_ply = vtkSmartPointer<vtkPolyData>::New();
		test_ply->SetPoints(test_point);

		vtkSmartPointer<vtkTransform> tra = vtkSmartPointer<vtkTransform>::New();
		//並進
		tra->Translate(0.02, 0.02, 0.02);//x, y, z方向の並進量
									  //回転
		tra->RotateWXYZ(90, 1, 1, 1);//回転軸と回転量を指定．
		tra->Update();
		vtkSmartPointer<vtkTransformPolyDataFilter> filter = vtkSmartPointer<vtkTransformPolyDataFilter>::New();

		filter->SetInputData(test_ply);//変換元のvtkPolyDataをセット．
		filter->SetTransform(tra);//変換をセット．．
		filter->Update();

		vtkPolyData* output_ply = filter->GetOutput();//変換後

		std::uniform_real_distribution<double> d_rand2(-0.001, 0.001);
		FILE* fp = fopen("points_dst.xyz", "w");
		if (fp == NULL)
		{
			char szFullPath[_MAX_PATH] = { '\0' };
			char *szFilePart;
			DWORD dwRet = GetFullPathNameA("points_dst.xyz", _MAX_PATH, szFullPath, &szFilePart);
			if (fp == NULL)
			{
				printf("file open error,[%s]\n", szFullPath);
				if (strlen(szFullPath) >= _MAX_PATH || dwRet == 0)
				{
					printf("FullPathName failed.!\n");
				}
			}
		}
		if (fp == NULL)
		{
			printf("%s open error.\n", output);
			return -10;
		}
		for (int i = 0; i < output_ply->GetNumberOfPoints(); i++)
		{
			double* p = output_ply->GetPoint(i);
			if (d_rand(mt) < 0.5)
			{
				fprintf(fp, "%f %f %f\n", p[0] + d_rand2(mt) + 0.05, p[1] + d_rand2(mt), p[2] + d_rand2(mt));
			}
		}
		fclose(fp);
		exit(0);
	}
#endif


	vtkSmartPointer<vtkPolyData> source = vtkSmartPointer<vtkPolyData>::New();
	vtkSmartPointer<vtkPolyData> target = vtkSmartPointer<vtkPolyData>::New();
	source->SetPoints(points_src);
	target->SetPoints(points_tgt);

	vtkSmartPointer<vtkVertexGlyphFilter> vertexFilter_src = vtkSmartPointer<vtkVertexGlyphFilter>::New();
	vertexFilter_src->SetInputData(source);
	vtkSmartPointer<vtkVertexGlyphFilter> vertexFilter_tgt = vtkSmartPointer<vtkVertexGlyphFilter>::New();
	vertexFilter_tgt->SetInputData(target);

	vertexFilter_src->Update();
	vertexFilter_tgt->Update();

	int sample_landmarksN = sample_landmarks*std::min(points_src->GetNumberOfPoints(), points_tgt->GetNumberOfPoints());
	if (sample_landmarks > 1.0) sample_landmarksN = sample_landmarks;
	printf("maximum number of landmarks sampled =%d\n", sample_landmarksN);

	vtkSmartPointer<vtkIterativeClosestPointTransform> icp = vtkSmartPointer<vtkIterativeClosestPointTransform>::New();
	//変換元(Source)と変換先(Target)を設定
	icp->SetSource(vertexFilter_src->GetOutput());
	icp->SetTarget(vertexFilter_tgt->GetOutput());
	icp->GetLandmarkTransform()->SetModeToRigidBody();
	icp->SetMaximumNumberOfIterations(iter);
	icp->SetMaximumNumberOfLandmarks(sample_landmarksN);
	icp->SetMaximumMeanDistance(tol);
	//icp->StartByMatchingCentroidsOn();
	icp->Modified();
	printf("IPC start.\n");
	icp->Update();
	printf("IPC end.\n");

	// Get the resulting transformation matrix (this matrix takes the source points to the target points)
	vtkSmartPointer<vtkMatrix4x4> m = icp->GetMatrix();
	std::cout << "The resulting matrix is: " << *m << std::endl;

	//計算される変換行列はSourceをTargetに変換する行列
	// Transform the source points by the ICP solution
	vtkSmartPointer<vtkTransformPolyDataFilter> icpTransformFilter =
		vtkSmartPointer<vtkTransformPolyDataFilter>::New();
	icpTransformFilter->SetInputData(source);
	icpTransformFilter->SetTransform(icp);
	icpTransformFilter->Update();

	vtkSmartPointer<vtkPoints> newPoints = icpTransformFilter->GetOutput()->GetPoints();

	FILE* fp_out = fopen(output, "w");
	{
		char szFullPath[_MAX_PATH] = { '\0' };
		char *szFilePart;
		DWORD dwRet = GetFullPathNameA(output, _MAX_PATH, szFullPath, &szFilePart);
		if (fp_out == NULL)
		{
			printf("file open error,[%s]\n", szFullPath);
			if (strlen(szFullPath) >= _MAX_PATH || dwRet == 0)
			{
				printf("FullPathName failed.!\n");
			}
		}
	}

	if (fp_out == NULL)
	{
		printf("%s open error.\n", output);
		return -10;
	}
	int num = newPoints->GetNumberOfPoints();
	for (int i = 0; i < num; i++)
	{
		double* p = newPoints->GetPoint(i);
		fprintf(fp_out, "%f %f %f\n", p[0], p[1], p[2]);
	}
	fclose(fp_out);

	return 0;
}