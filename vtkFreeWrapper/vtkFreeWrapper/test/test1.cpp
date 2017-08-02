#include "gmrVTKPolyline.hpp"
#include "gmrVTKRender.hpp"
#include "gmrVTKPoints.hpp"
#include "gmrVTKScalarBar.hpp"


class Poly
{
	gmrVTKPolyline* poly;
	double dist_min;
	double dist_max;

public:
	Poly(int n, double*scalar)
	{
		dist_min = 99999999.0;
		dist_max = -9999999999.0;
		double dst;
		double p[3];
		poly = new gmrVTKPolyline;
		for ( int i = 0; i <= n; i++){
			p[0] = 2.0*3.14*i/n;
			p[1] = sin(2.0*3.14*i/n);
			p[2] = cos(2.0*3.14*i/n); 
			poly->SetPoint(p);
			dst = sqrt(p[0]*p[0] + p[1]*p[1] + p[2]*p[2]);
			if ( dst < dist_min ) dist_min = dst;
			if ( dst > dist_max ) dist_max = dst;
			scalar[i] = dst;
		}
		poly->SetScalar(scalar);

	}

	double GetMin() const { return dist_min;};
	double GetMax() const { return dist_max;};

	gmrVTKPolyline* Get() { return poly; }
};




void test1 ()
{
	gmrVTKRender* render = new gmrVTKRender;
	double* scalar = new double[41];

	Poly* poly = new Poly(40, scalar);

	poly->Get()->SetSize(3);
	poly->Get()->SetDiffuseColor(0.2, 0.4, 0.8);

	// -- render both of the objects --

	render->AddActor(poly->Get()->GetActor());
	gmrVTKScalaBar *colorBar = new gmrVTKScalaBar;
	colorBar->Vertical();
	colorBar->LabelTextColor(0.9, 0.1, 0.1);
	colorBar->TitleTextColor(0.1, 0.1, 0.9);
	colorBar->SetTitle( "-Distance-" );

	colorBar->SetWidthPositionFactor(0.8);
	colorBar->SetScalarMinMax(poly->GetMin(), poly->GetMax());
	render->AddActor(colorBar->GetActor());

	render->DefaultRun();
}
