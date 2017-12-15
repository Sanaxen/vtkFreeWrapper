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
 * 外部（ポリゴン）データ読み込み
 * OBJ形式
 */
#include "gmrVTKImport.hpp"

gmrVTKImportOBJ::gmrVTKImportOBJ(char* filename)
{
	mat_color_use = false;
	OBJ_ = NULL;
	LoadFile(filename);
}


gmrVTKImportOBJ::~gmrVTKImportOBJ()
{
	if ( OBJ_ ) OBJ_->Delete();
}


void gmrVTKImportOBJ::LoadFile( char* filename)
{
	OBJ_ = vtkOBJReader::New();
	OBJ_->SetFileName( filename );
 
    stlMapper_ = vtkPolyDataMapper::New();
	stlMapper_->SetInputConnection(OBJ_->GetOutputPort());

	actor_ = vtkActor::New();
	actor_->SetMapper(stlMapper_);
	OBJ_->Update();

	vtkSmartPointer<vtkUnsignedCharArray> colors =
		vtkSmartPointer<vtkUnsignedCharArray>::New();
	colors->SetNumberOfComponents(3);
	colors->SetNumberOfTuples(OBJ_->GetOutput()->GetPoints()->GetNumberOfPoints());
	colors->SetName("Colors");

	FILE* fp = fopen(filename, "r");
	printf("vertex color start\n");
	if (fp != NULL)
	{
		printf("vertex color check\n");
		int ii = 0;
		bool vertex_color = true;
		char buf[256];
		while (fgets(buf, 256, fp) != NULL)
		{
			if (buf[0] == 'v' && buf[1] != 'n' && buf[1] != 't')
			{

			}
			else
			{
				continue;
			}
			double x, y, z, r, g, b;
			int n = sscanf(buf, "v %lf %lf %lf %lf %lf %lf", &x, &y, &z, &r, &g, &b);
			if (n != 6)
			{
				vertex_color = false;
				break;
			}
			if (r <= 1.0 && g <= 1.0 && b <= 1.0)
			{
				r *= 255.0;
				g *= 255.0;
				b *= 255.0;
			}
			colors->SetComponent(ii, 0, r);
			colors->SetComponent(ii, 1, g);
			colors->SetComponent(ii, 2, b);
			ii++;
		}
		fclose(fp);
		printf("vertex num:%d == %d\n", OBJ_->GetOutput()->GetPoints()->GetNumberOfPoints(), ii);

		if (vertex_color && OBJ_->GetOutput()->GetPoints()->GetNumberOfPoints() == ii)
		{
			OBJ_->GetOutput()->GetPointData()->SetScalars(colors);
			mat_color_use = true;
			mat_color[0] = colors->GetComponent(0, 0);
			mat_color[1] = colors->GetComponent(0, 1);
			mat_color[2] = colors->GetComponent(0, 2);
		}
	}
	OBJ_->Update();

	ImplicitDataSet_ = vtkImplicitDataSet::New();
	ImplicitDataSet_->SetDataSet(OBJ_->GetOutput());

}

