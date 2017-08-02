#include "STLViewer.hpp"

STLViewer::STLViewer(const char* filename, int type)
{
	type_ = type;

	filename_ = filename;
	polygon_ = new gmrVTKImportSTL((char*)filename);
}

STLViewer::~STLViewer()
{
	delete polygon_;
}


STLPolylineViewer::STLPolylineViewer(const char* filename, int type, bool pointview)
{
	pointview_ = pointview;
	type_ = type;

	filename_ = filename;
	StlToPolyLine();
}

STLPolylineViewer::~STLPolylineViewer()
{
	for ( size_t i = 0; i < polyline_.size(); i++ )
	{
        delete polyline_[i];
	}
	for ( size_t i = 0; i < points_.size(); i++ )
	{
        delete points_[i];
	}
}

void STLPolylineViewer::StlToPolyLine()
{

	FILE* fp = fopen(filename_.c_str(), "r");
	if ( fp == NULL ){
		return;
	}

	char buf[256];
	char* p;
	double point[3][3];
	double endpoint[3];

#define TEMPSQR(x)	((x)*(x))

	int facetNum = 0;
	gmrVTKPolyline* poly = new gmrVTKPolyline;
	gmrVTKPoints* points;

	if ( pointview_) points = new gmrVTKPoints;


	while(fgets(buf, 256, fp) != NULL)
	{
		if ( (p = strstr(buf, "vertex")) == NULL ) continue;

		sscanf(p, "vertex %lf %lf %lf", point[0], point[0]+1, point[0]+2);

		fgets(buf, 256, fp);
		p = strstr(buf, "vertex");
		sscanf(p, "vertex %lf %lf %lf", point[1], point[1]+1, point[1]+2);

		fgets(buf, 256, fp);
		p = strstr(buf, "vertex");
		sscanf(p, "vertex %lf %lf %lf", point[2], point[2]+1, point[2]+2);

		facetNum++;

		if ( facetNum > 1 )
		{
			double dist = TEMPSQR(point[0][0] - endpoint[0])+TEMPSQR(point[0][1] - endpoint[1])+TEMPSQR(point[0][2] - endpoint[2]);
			if ( dist > 0.01*0.01 )
			{
				poly->SetPoint(endpoint);
				polyline_.push_back(poly);
		
				if ( this->pointview_)
				{
					points->SetPoint(endpoint);
					points_.push_back(points);
				}

				facetNum = 1;

				poly = new gmrVTKPolyline;
				if ( this->pointview_) points = new gmrVTKPoints;
			}
		}
		poly->SetPoint(point[0]);
		if ( this->pointview_) points->SetPoint(point[0]);

		endpoint[0] = point[1][0];
		endpoint[1] = point[1][1];
		endpoint[2] = point[1][2];
	}

end:	;

#undef TMPSQR

	fclose(fp);
}



STLViewerList::STLViewerList()
{
	render_ = new gmrVTKRender;
	render_->InteractorStyleTrackballCamera();
}


STLViewerList::~STLViewerList()
{
	for ( size_t i = 0; i < stllist_.size(); i++ )
	{
		if ( stllist_[i] ) delete stllist_[i];
	}
}

void STLViewerList::Render()
{
	for ( size_t i = 0; i < stllist_.size(); i++ )
	{
		render_->AddActor(stllist_[i]->GetData()->GetActor());
	}
	for ( size_t i = 0; i < stlpolylist_.size(); i++ )
	{
		for ( size_t j = 0; j < stlpolylist_[i]->GetPolyListNum(); j++ )
		{
			render_->AddActor(stlpolylist_[i]->GetData(j)->GetActor());
		}

		if ( this->stlpolylist_[i]->GetPointView() )
		{
			for ( size_t j = 0; j < stlpolylist_[i]->GetPointListNum(); j++ )
			{
				render_->AddActor(stlpolylist_[i]->GetVtxData(j)->GetActor());
			}
		}
	}
	render_->DefaultRun();
}

