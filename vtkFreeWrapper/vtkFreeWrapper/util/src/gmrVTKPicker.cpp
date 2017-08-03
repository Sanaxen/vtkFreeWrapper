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
 *
 * Picker作成
 *
 */
#include "gmrVTKPicker.hpp"



void gmrVTKCallbackPointPick::Execute(vtkObject *caller, unsigned long, void*)
{
        vtkRenderWindowInteractor *iren =
				reinterpret_cast<vtkRenderWindowInteractor*>(caller);

        vtkPointPicker *picker = (vtkPointPicker *)iren->GetPicker();
        
		double x = iren->GetEventPosition()[0];
		double y = iren->GetEventPosition()[1];
		int succed = picker->Pick(x, y, 0, this->GetRenderer()->GetRenderer());
		int pointId = picker->GetPointId();
#if 0
		double winpos[3];
		double pos[3];
		winpos[0] = x;
		winpos[1] = y;
		winpos[2] = z;
		this->GetPicker()->SetPositionInfo(succed, pos, wpos, pointId, picker->GetActor());
#else
		double* pos = picker->GetPickPosition();
		double* winpos = picker->GetSelectionPoint();
		this->GetPicker()->SetPositionInfo(succed, winpos, pos, pointId, picker->GetActor());
#endif
}

void gmrVTKCallbackCellPick::Execute(vtkObject *caller, unsigned long, void*)
{
        vtkRenderWindowInteractor *iren =
				reinterpret_cast<vtkRenderWindowInteractor*>(caller);

        vtkCellPicker *picker = (vtkCellPicker *)iren->GetPicker();
        
		double x = iren->GetEventPosition()[0];
		double y = iren->GetEventPosition()[1];
		int succed =  picker->Pick(x, y, 0, this->GetRenderer()->GetRenderer());
		int pointId = ((vtkPointPicker *)picker)->GetPointId();

#if 0
		double winpos[3];
		double pos[3];
		winpos[0] = x;
		winpos[1] = y;
		winpos[2] = z;
		this->GetPicker()->SetPositionInfo(succed, pos, wpos, pointId, picker->GetActor());
#else
		double* pos = picker->GetPickPosition();
		double* winpos = picker->GetSelectionPoint();
		this->GetPicker()->SetPositionInfo(succed, winpos, pos, pointId, picker->GetActor());
#endif
		if ( succed != 0 && picker->GetActor())this->GetRenderer()->RemoveActor( picker->GetActor());
		iren->Render();
}

void gmrVTKCallbackWorldPointPick::Execute(vtkObject *caller, unsigned long, void*)
{
        vtkRenderWindowInteractor *iren =
				reinterpret_cast<vtkRenderWindowInteractor*>(caller);

        vtkWorldPointPicker *picker = (vtkWorldPointPicker *)iren->GetPicker();
        
		double x = iren->GetEventPosition()[0];
		double y = iren->GetEventPosition()[1];
		double z = 0.0;
		int succed = picker->Pick(x, y, z, this->GetRenderer()->GetRenderer());
		int pointId = ((vtkPointPicker *)picker)->GetPointId();

		double* pos = picker->GetPickPosition();
		double* winpos = picker->GetSelectionPoint();
		this->GetPicker()->SetPositionInfo(succed, winpos, pos, pointId, NULL);
}

gmrVTKPicker::gmrVTKPicker()
{
	picker_ = NULL;
	callback_ = NULL;
	tol_ = 0.01;
}


gmrVTKPicker::~gmrVTKPicker()
{
	picker_ = NULL;
	callback_ = NULL;
}

void gmrVTKPicker::SetRender(gmrVTKRender* render)
{
	render_ = render;
	render_->SetPiker(this);
}

void gmrVTKPicker::SetCallback(gmrVTKCommand* callback)
{
	callback_ = callback;
}

void gmrVTKPicker::SetPicker(vtkPicker* picker)
{
	picker_ = picker;
	picker_->SetTolerance(tol_);
}
void gmrVTKPicker::SetCondition(gmrVTKRender* render, vtkPicker* picker, gmrVTKCommand* callback)
{
	SetRender(render);
	SetPicker( picker);
	SetCallback( callback);
	callback->SetCondition( render, this );
}


void gmrVTKPicker::SetPositionInfo(int succed, double* pos, double* wpos, int id, vtkActor* actor)
{
	cout << "Actor: " << picker_->GetActor() << "\n";
	cout << "(" << pos[0] << ", " << pos[1] << ") " << "succed=" << succed << " PointId: " << id << endl;
	cout << "(" << wpos[0] << ", " << wpos[1] << ", " << wpos[2] << ") " << endl;
    cout << "============" << "\n";

	pos_[0] = pos[0];
	pos_[1] = pos[1];
	pos_[2] = pos[2];

	wpos_[0] = wpos[0];
	wpos_[1] = wpos[1];
	wpos_[2] = wpos[2];

	pointId_ = id;
	actor_ = actor;
}

void gmrVTKPicker::GetPositionInfo(int& succed, double* pos, double* wpos, int& id, vtkActor** actor)
{
	pos_[0] = pos[0];
	pos_[1] = pos[1];
	pos_[2] = pos[2];

	wpos_[0] = wpos[0];
	wpos_[1] = wpos[1];
	wpos_[2] = wpos[2];

	id = pointId_;
	if (actor ) *actor = actor_;
	succed_ = succed;
}
//////////////////////////////////////////////////////////////////////////////

gmrVTKPointPicker::gmrVTKPointPicker(gmrVTKRender* render)
{
	SetCondition(render, vtkPointPicker::New(), gmrVTKCallbackPointPick::New());
}


gmrVTKPointPicker::~gmrVTKPointPicker()
{
	if ( GetPicker() != NULL )	GetPicker()->Delete();
	if ( GetCallback() != NULL )	GetCallback()->Delete();;
}
//////////////////////////////////////////////////////////////////////////////


gmrVTKCellPicker::gmrVTKCellPicker(gmrVTKRender* render)
{
	SetCondition(render, vtkPointPicker::New(), gmrVTKCallbackCellPick::New());
}


gmrVTKCellPicker::~gmrVTKCellPicker()
{
	if ( GetPicker() != NULL )	GetPicker()->Delete();
	if ( GetCallback() != NULL )	GetCallback()->Delete();;
}
//////////////////////////////////////////////////////////////////////////////


gmrVTKWorldPointPicker::gmrVTKWorldPointPicker(gmrVTKRender* render)
{
	SetCondition(render, vtkPointPicker::New(), gmrVTKCallbackCellPick::New());
}


gmrVTKWorldPointPicker::~gmrVTKWorldPointPicker()
{
	if ( GetPicker() != NULL )	GetPicker()->Delete();
	if ( GetCallback() != NULL )	GetCallback()->Delete();;
}
//////////////////////////////////////////////////////////////////////////////
