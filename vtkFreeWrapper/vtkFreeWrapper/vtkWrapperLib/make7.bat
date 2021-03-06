call "%VS71COMNTOOLS%vsvars32.bat"

set cdopt=/I "../util/include" /I "\VTK\Debug\include\vtk-5.0" /D "WIN32" /D "_DEBUG" /D "_LIBS" /D "_MBCS" /Gm /EHsc /RTC1 /MTd /Fo"Debug/" /Fd"Debug/vc70.pdb" /W3 /nologo /c /Wp64 /ZI /TP

set ldopt=/OUT:"Debug/vtkWrapperLib.lib" /NOLOGO


set cropt=/I "../util/include" /I "\VTK\Release\include\vtk-5.0" /D "WIN32" /D "NDEBUG" /D "_LIBS" /D "_MBCS" /FD /EHsc /MT /GS /Fo"Release/" /Fd"Release/vc70.pdb" /W3 /nologo /c /Wp64 /Zi /TP

set lropt=/OUT:"Release/vtkWrapperLib.lib" /NOLOGO

cd \vtkFreeWrapper\vtkWrapperLib
set src=\vtkFreeWrapper\util\src

cl %cdopt% %src%\*.cpp > log.txt
lib %ldopt% Debug\*.obj >> log.txt

cl %cropt% %src%\*.cpp >> log.txt
lib %lropt% Release\*.obj >> log.txt

cd \vtkFreeWrapper\vtkWrapperLib

call rcopy Release
call dcopy Debug

