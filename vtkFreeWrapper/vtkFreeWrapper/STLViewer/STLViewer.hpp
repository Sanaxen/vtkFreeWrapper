#ifndef _STLVIEWER_HPP

#define _STLVIEWER_HPP

#include "gmrVTKRender.hpp"
#include "gmrVTKImport.hpp"
#include "gmrVTKPolyline.hpp"
#include "gmrVTKPoints.hpp"

#include <string>
#include <vector>

#define	STL_POLYGON_TYPE	0
#define	STL_POLYLINE_TYPE	1


class STLViewer
{
	gmrVTKImportSTL* polygon_;

	std::string filename_;
	int type_;
public:
	STLViewer(const char* filename, int type);
	virtual ~STLViewer();

	gmrVTKImportSTL* GetData()
	{
		return polygon_;
	}
	int GetType() const { return type_;}
};


class STLPolylineViewer
{
	std::vector<gmrVTKPolyline*> polyline_;
	std::vector<gmrVTKPoints*> points_;

	std::string filename_;
	int type_;
	bool pointview_;

	void StlToPolyLine();
public:
	STLPolylineViewer(const char* filename, int type, bool pointview);
	virtual ~STLPolylineViewer();


	bool GetPointView() const { return pointview_; }

	gmrVTKPolyline* GetData(size_t index)
	{
		return polyline_[index];
	}

	gmrVTKPoints* GetVtxData(size_t index)
	{
		return points_[index];
	}

	size_t GetPolyListNum() const
	{
		return polyline_.size();
	}

	size_t GetPointListNum() const 
	{
		return points_.size();
	}

	void SetDiffuseColor(double r, double g, double b)
	{
		for ( size_t k = 0; k < GetPolyListNum(); k++ )
		{
			GetData(k)->SetDiffuseColor(r, g, b);
		}

		if ( ! pointview_ ) return;

		for ( size_t k = 0; k < GetPointListNum(); k++ )
		{
			GetVtxData(k)->SetDiffuseColor(r, g, b);
		}
	}

	void SetPointDiffuseColor(double r, double g, double b)
	{
		if ( ! pointview_ ) return;

		for ( size_t k = 0; k < GetPointListNum(); k++ )
		{
			GetVtxData(k)->SetDiffuseColor(r, g, b);
		}
	}

	void SetLineSize(double size)
	{
		for ( size_t k = 0; k < GetPolyListNum(); k++ )
		{
			GetData(k)->SetSize(size);
		}
	}
	void SetPointSize(double size)
	{
		if ( ! pointview_ ) return;

		for ( size_t k = 0; k < GetPointListNum(); k++ )
		{
			GetVtxData(k)->SetSize(size);
		}
	}


	int GetType() const { return type_;}
};


class STLViewerList
{
	gmrVTKRender* render_;
	std::vector<STLViewer*> stllist_;
	std::vector<STLPolylineViewer*> stlpolylist_;

public:
	STLViewerList();
	virtual ~STLViewerList();

	void Add(STLViewer* stl)
	{
		stllist_.push_back(stl);
	}

	void Add(STLPolylineViewer* stl)
	{
		stlpolylist_.push_back(stl);
	}

	gmrVTKRender* GetRender()
	{
		return render_;
	}

	void Render();
};



#endif

