#include "gmrVTKRender.hpp"
#include "gmrVTKImport.hpp"
#include "gmrVTKExport.hpp"

#include "gmrVTKMeshFilter.hpp"

#include "gmrVTK.hpp"
#include <random>

#define NO_LINK_LIBS
#include "gmrVTKLIBs.hpp"
#pragma comment( lib, "../../../vtkFreeWrapper/util/lib/Release/64bit/vtkWrapperLib.lib" )
#pragma comment( lib, "opengl32.lib" )
#pragma comment( lib, "vfw32.lib")

int readPoints(char* xyz_fileName, char* new_xyz_fileName, double sampling, std::mt19937& mt, std::uniform_real_distribution<double>& d_rand)
{
	FILE* fp = fopen(xyz_fileName, "r");
	if (fp == NULL) return -1;

	FILE* fp2 = fopen(new_xyz_fileName, "w");
	if (fp2 == NULL) return -1;

	char buf[256];
	float x, y, z;
	int num = 0;
	while (fgets(buf, 256, fp) != NULL)
	{
		sscanf(buf, "%f %f %f", &x, &y, &z);
		if (d_rand(mt) < sampling)
		{
			fprintf(fp2, "%f %f %f\n", x, y, z);
			num++;
		}
	}
	fclose(fp);
	printf("write %d points\n", num);

	return 0;
}

int main(int argc, char** argv)
{
	if (argc < 2)
	{
		printf("down_sampling xyz_file [-smp sampling[0, 1.0]] -o output\n");
		return -99;
	}
	std::mt19937 mt;
	std::uniform_real_distribution<double> d_rand(0.0, 1.0);


	double sampling = 1.0;
	char* file1 = NULL;
	char* output = NULL;

	for (int i = 1; i < argc; i++)
	{
		if (strcmp(argv[i], "-o") == 0)
		{
			output = argv[i + 1];
			i++;
			continue;
		}
		if (strcmp(argv[i], "-smp") == 0)
		{
			sampling = atof(argv[i + 1]);
			i++;
			continue;
		}
		else if (file1 == NULL) file1 = argv[i];
	}
	if (file1 == NULL)
	{
		return -1;
	}
	if (output == NULL)
	{
		return -3;
	}
	int stat = readPoints(file1, output, sampling, mt, d_rand);
	if (stat != 0)
	{
		printf("error.\n");
		return -1;
	}
}