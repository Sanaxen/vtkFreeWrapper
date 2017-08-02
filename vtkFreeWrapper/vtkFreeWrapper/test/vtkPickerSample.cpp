#include "vtkActor.h"
#include "vtkCamera.h"
#include "vtkCellArray.h"
#include "vtkFloatArray.h"
#include "vtkPointData.h"
#include "vtkPoints.h"
#include "vtkPolyData.h"
#include "vtkPolyDataMapper.h"
#include "vtkRenderWindow.h"
#include "vtkRenderWindowInteractor.h"
#include "vtkRenderer.h"
#include "vtkCommand.h"
#include "vtkPointPicker.h"
#include "vtkCellPicker.h"
#include "vtkSphereSource.h"
#include "vtkProperty.h"

#include <stdio.h>

class vtkMyCallback : public vtkCommand
{
public:
        vtkMyCallback() { ;};
        static vtkMyCallback *New() { return new vtkMyCallback; }

        virtual void Execute(vtkObject *caller, unsigned long, void*)
        {
                vtkRenderWindowInteractor *iren =
						reinterpret_cast<vtkRenderWindowInteractor*>(caller);

                vtkPointPicker *picker = (vtkPointPicker *)iren->GetPicker();
                
				cout << picker << " " << m_picker << "\n";

				int x = iren->GetEventPosition()[0];
				int y = iren->GetEventPosition()[1];
				int succed = m_picker->Pick(x, y, 0, m_ren);
				int pointId = m_picker->GetPointId();

				picker->GetPickedPositions();
				cout << "(" << x << ", " << y << ") " << "succed=" << succed << " PointId: " << 
				pointId << endl;
				cout << "PointId: " << picker->GetPointId() << "\n";
                cout << "============" << "\n";

        }
        void SetRenderer(vtkRenderer *ren)
        {
            m_ren = ren;
        }
       void SetPicker(vtkPointPicker *picker)
        {
            m_picker = picker;
        }

private:
		vtkRenderer *m_ren;
		vtkPointPicker * m_picker;

};

class vtkMyCallback2 : public vtkCommand
{
public:
        vtkMyCallback2() {;};
        static vtkMyCallback2 *New() { return new vtkMyCallback2; }

        virtual void Execute(vtkObject *caller, unsigned long, void*)
        {
                vtkRenderWindowInteractor *iren =
						reinterpret_cast<vtkRenderWindowInteractor*>(caller);

                vtkCellPicker *picker = (vtkCellPicker *)iren->GetPicker();
                
				cout << "Actor: " << picker->GetActor() << "\n";

				int x = iren->GetEventPosition()[0];
				int y = iren->GetEventPosition()[1];
				int succed = m_picker->Pick(x, y, 0, m_ren);
				int pointId = m_picker->GetPointId();

				picker->GetPickedPositions();
				cout << "(" << x << ", " << y << ") " << "succed=" << succed << " PointId: " << 
				pointId << endl;
                cout << "============" << "\n";

				if (picker->GetActor())m_ren->RemoveActor( picker->GetActor());
				iren->Render();
        }
        void SetRenderer(vtkRenderer *ren)
        {
            m_ren = ren;
        }
       void SetPicker(vtkPointPicker *picker)
        {
            m_picker = picker;
        }

private:
		vtkRenderer *m_ren;
		vtkPointPicker * m_picker;
};


int test2main(void)
{
        int i;
        static float x[8][3]={{0,0,0}, {1,0,0}, {1,1,0}, {0,1,0},
                {0,0,1}, {1,0,1}, {1,1,1}, {0,1,1}};
        static vtkIdType pts[6][4]={{0,1,2,3}, {4,5,6,7}, {0,1,5,4},
                {1,2,6,5}, {2,3,7,6}, {3,0,4,7}};

        // We'll create the building blocks of polydata including data =attributes.
        vtkPolyData *cube = vtkPolyData::New();
        vtkPoints *points = vtkPoints::New();
        vtkCellArray *polys = vtkCellArray::New();
        vtkFloatArray *scalars = vtkFloatArray::New();

        // Load the point, cell, and data attributes.
        for (i=0; i<8; i++) points->InsertPoint(i,x[i]);
        for (i=0; i<6; i++) polys->InsertNextCell(4,pts[i]);
        for (i=0; i<8; i++) scalars->InsertTuple1(i,i);

        // We now assign the pieces to the vtkPolyData.
        cube->SetPoints(points);
        cube->SetPolys(polys);
        cube->GetPointData()->SetScalars(scalars);

        // Now we'll look at it.
        vtkPolyDataMapper *cubeMapper =  vtkPolyDataMapper::New();
        cubeMapper->SetInput(cube);
        cubeMapper->SetScalarRange(0,7);
        vtkActor *cubeActor =  vtkActor::New();
        cubeActor->SetMapper(cubeMapper);

        // The usual rendering stuff.
        vtkCamera *camera =  vtkCamera::New();
        camera->SetPosition(1,1,1);
        camera->SetFocalPoint(0,0,0);

        vtkRenderer *renderer =  vtkRenderer::New();
        vtkRenderWindow *renWin =  vtkRenderWindow::New();
        renWin->AddRenderer(renderer);

        vtkRenderWindowInteractor *iren = vtkRenderWindowInteractor::New();
        iren->SetRenderWindow(renWin);

        renderer->AddActor(cubeActor);
        renderer->SetActiveCamera(camera);
        renderer->ResetCamera();
        renderer->SetBackground(1,1,1);

        renWin->SetSize(300,300);

        // create marker for pick
        vtkSphereSource *sphere =  vtkSphereSource::New();
        sphere->SetThetaResolution(8); sphere->SetPhiResolution(8);
        sphere->SetRadius(0.1);
        vtkPolyDataMapper *sphereMapper =  vtkPolyDataMapper::New();
        sphereMapper->SetInput(sphere->GetOutput());
        vtkActor *sphereActor =  vtkActor::New();
        sphereActor->SetMapper(sphereMapper);
        sphereActor->GetProperty()->SetColor(1,0,0);
        //sphereActor->PickableOff();

        renderer->AddActor(sphereActor);

        // start renderer
        renWin->Render();

        // init picker
        vtkPointPicker *picker =  vtkPointPicker::New();
        picker->SetTolerance(0.01);
        iren->SetPicker(picker);

        // init callback
        vtkMyCallback *callback =  vtkMyCallback::New();
        callback->SetSelectionActor(sphereActor);
		callback->SetRenderer(renderer);
		callback->SetPicker(picker);
        iren->AddObserver(vtkCommand::LeftButtonPressEvent, callback);

		// start interaction
        iren->Start();
        iren->RemoveObserver(callback);

        vtkCellPicker *picker2 =  vtkCellPicker::New();
        picker2->SetTolerance(0.01);
        iren->SetPicker(picker2);

        // init callback
        vtkMyCallback2 *callback2 =  vtkMyCallback2::New();
		callback2->SetRenderer(renderer);
		callback2->SetPicker((vtkPointPicker*)picker2);

        iren->AddObserver(vtkCommand::LeftButtonPressEvent, callback2);
		// start interaction
        iren->Start();
        iren->RemoveObserver(callback2);

		
		// Clean up
        cube->Delete();
        points->Delete();
        polys->Delete();
        scalars->Delete();
        cubeMapper->Delete();
        cubeActor->Delete();
        camera->Delete();
        sphere->Delete();
        sphereMapper->Delete();
        sphereActor->Delete();
        picker->Delete();
        renderer->Delete();
        renWin->Delete();
        iren->Delete();
        callback->Delete();

        return 0;
}



