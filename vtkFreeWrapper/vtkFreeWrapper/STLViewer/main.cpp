#include "gmrVTK.hpp"
#include "gmrVTKLIBs.hpp"
#include "STLViewer.hpp"


void getColor(char* arg, double* r, double* g, double* b)
{

	sscanf(arg, "%lf,%lf,%lf", r, g, b);
}
void getSize(char* arg, int* w, int* h)
{

	sscanf(arg, "%d,%d", w, h);
}


int main( int argc, char** argv)
{
	if ( argc < 2 ){
		printf("Usage: STLViewer {[-c r,g,b] [-l [-p]] STLFilename }...\n");
		printf("===== option ======\n");
		printf("-l STLFilenameが折れ線データ（頂点１と頂点２が同一座標)の集合\n");
		printf("-p STLFilenameが折れ線データの時、構成点も表示する\n");
		printf("-ls STLFilenameが折れ線データの時、線の太さを指定\n");
		printf("-ps STLFilenameが折れ線データの時、構成点の大きさを指定\n");
		printf("-pc STLFilenameが折れ線データの時、構成点のRGBカラーの設定\n");
		printf("-c RGBカラーの設定 -c r,g,b で指定する(r,g,bは0.0以上を指定)\n");
		printf("-back 背景カラーの設定 -back r,g,b で指定する(r,g,bは0.0以上を指定)\n");
		printf("-size ウインドウサイズの設定 -size w,h で指定する(w,hは10以上を指定)\n");
		return 1;
	}
	STLViewerList* list = new STLViewerList;

	list->GetRender()->SetSize(640,640);

	int type;
	bool vtxview;
	bool color_default;
	double r, g, b;
	double pointcolor[3];
	double linesize = 1.0;
	double pointsize = 1.0;

	color_default = true;
	vtxview = false;
	type = STL_POLYGON_TYPE;

	for ( int i = 1; i < argc; i++ )
	{

		if ( std::string(argv[i]) == "-l" )
		{
			type = STL_POLYLINE_TYPE;
			continue;
		}


		if ( std::string(argv[i]) == "-c" )
		{
			color_default = false;

			i++;
			getColor(argv[i], &r, &g, &b);
			continue;
		}
		if ( std::string(argv[i]) == "-pc" )
		{
			color_default = false;

			i++;
			getColor(argv[i], pointcolor, pointcolor+1, pointcolor+2);
			continue;
		}

		if ( std::string(argv[i]) == "-p" )
		{
			vtxview = true;
			continue;
		}
		if ( std::string(argv[i]) == "-ls" )
		{
			i++;
			linesize = atof(argv[i]);
			continue;
		}
		if ( std::string(argv[i]) == "-ps" )
		{
			i++;
			pointsize = atof(argv[i]);
			continue;
		}
		if ( std::string(argv[i]) == "-back" )
		{
			i++;
			double c[3];
			getColor(argv[i], c, c+1, c+2);
			list->GetRender()->SetBackgroundColor(c[0], c[1], c[2]);
			continue;
		}
		if ( std::string(argv[i]) == "-size" )
		{
			i++;
			int c[3];
			getSize(argv[i], c, c+1);
			list->GetRender()->SetSize(c[0], c[1]);
			continue;
		}



		if ( type == STL_POLYGON_TYPE )
		{
			if ( color_default )
			{
				r = (double)rand()/RAND_MAX;
				g = (double)rand()/RAND_MAX;
				b = (double)rand()/RAND_MAX;
			}

			STLViewer* stl = new STLViewer(argv[i], type );
			stl->GetData()->SetDiffuseColor(r, g, b);
			list->Add(stl);
		}else
		{
			if ( color_default )
			{
				r = (double)rand()/RAND_MAX;
				g = (double)rand()/RAND_MAX;
				b = (double)rand()/RAND_MAX;
			}

			STLPolylineViewer* stl = new STLPolylineViewer(argv[i], type, vtxview );

			stl->SetDiffuseColor(r, g, b);
			stl->SetPointDiffuseColor(pointcolor[0],pointcolor[1],pointcolor[2]);
			stl->SetLineSize(linesize);
			stl->SetPointSize(pointsize);
			list->Add(stl);
		}

		vtxview = false;
		type = STL_POLYGON_TYPE;
		linesize = 1.0;
		pointsize = 1.0;
		color_default = true;
	}

	list->Render();

	delete list;

	return 0;
}