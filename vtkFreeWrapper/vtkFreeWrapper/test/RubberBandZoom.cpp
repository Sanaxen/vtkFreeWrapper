#include <vtkConeSource.h>
#include <vtkPolyDataMapper.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkCamera.h>
#include <vtkActor.h>
#include <vtkRenderer.h>

#include "vtkInteractorStyleTrackballCamera.h"
#include "vtkInteractorStyleJoystickCamera.h"
#include "vtkInteractorStyleTerrain.h"
#include "vtkInteractorStyleRubberBandZoom.h"


int test3main( int type )
{
	int StyleId = 0; // Style for testing

	StyleId = type;     

	vtkInteractorStyle *style = NULL;

	switch(StyleId)
		{
		case 1:
		style = vtkInteractorStyleTrackballCamera::New();
		break;
		case 2:
		style = vtkInteractorStyleJoystickCamera::New();
		break;
		case 3:
		style = vtkInteractorStyleTerrain::New();
		break;
		case 4:
		style = vtkInteractorStyleRubberBandZoom::New();
		break;
		default:
		exit(0);   
		}
	 
	// Main staff
	vtkRenderer *ren = vtkRenderer::New();
	 
	vtkConeSource *cone = vtkConeSource::New();
	cone->SetHeight( 3.0 );
	cone->SetRadius( 1.0 );
	cone->SetResolution( 10 );
	 
	vtkPolyDataMapper *coneMapper = vtkPolyDataMapper::New();
	coneMapper->SetInput( cone->GetOutput() );

	vtkActor *coneActor = vtkActor::New();
	coneActor->SetMapper( coneMapper );

	ren->AddActor( coneActor );
	ren->SetBackground( 0.5, 0.5, 0.5 );

	vtkRenderWindow *renWin = vtkRenderWindow::New();
	renWin->AddRenderer( ren );
	renWin->SetSize( 300, 300 );

	vtkRenderWindowInteractor *iren = vtkRenderWindowInteractor::New();
	iren->SetRenderWindow(renWin);

	iren->SetInteractorStyle(style);

	iren->Initialize();
	iren->Start();
	iren->SetInteractorStyle(vtkInteractorStyleTrackballCamera::New());
	iren->Start();
	 
	cone->Delete();
	coneMapper->Delete();
	coneActor->Delete();
	ren->Delete();
	renWin->Delete();
	iren->Delete();

	return 0;
}
