        workdir -+  
                 |-vtkFreeWrapper  
                 |-VTK-+  
                 |     |  
                 |     +- 32bit <--- no use!!  
                 |     |  
                 |     +- 64bit- release -+-- bin  
                 |     |                  |  
                 |     |                  +-- include -- vtk-#.#.# -- vtk*.h  
                 |     |                  |  
                 |     |                  +-- lib -- vtk-#.#.# -- vtk*.lib  
                 |     |                  |
                 |     |                  +-- include -- vtk-x -- vtk*.h  
                 |     |                  |  
                 |     |                  +-- lib -- vtk-x -- vtk*.lib  
                 |     +- build_setup.bat
