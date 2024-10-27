if exist "C:\Program Files (x86)\Microsoft Visual Studio\2019\Professional\Common7\Tools\VsDevCmd.bat" (
	call "C:\Program Files (x86)\Microsoft Visual Studio\2019\Professional\Common7\Tools\VsDevCmd.bat"
)
if exist "C:\Program Files (x86)\Microsoft Visual Studio\2019\Community\Common7\Tools\VsDevCmd.bat" (
	call "C:\Program Files (x86)\Microsoft Visual Studio\2019\Community\Common7\Tools\VsDevCmd.bat"
)
:pause

rem MSBuildでビルドする
cd %~dp0

cd vtkFreeWrapper

set Pre_built_VTK=https://github.com/Sanaxen/vtkFreeWrapper/releases/download/v0.1/VTK9_4.7z

:bitsadmin /transfer getFile %Pre_built_VTK%  %~dp0VTK9_4.7z
curl -L %Pre_built_VTK%  -o VTK9_4.7z
pause

:1
tar -xvf ./VTK9_4.7z

pause
cd vtkFreeWrapper

echo "build start" > log.txt


:1
set build=.\vtkWrapperLib\vtkWrapperLib.sln
MSBuild %build% /t:clean;rebuild /p:Configuration=static_release;Platform="x64"
MSBuild %build% /t:build /p:Configuration=static_release;Platform="x64"
if %ERRORLEVEL% neq 0 (
    echo ErrorLevel:%ERRORLEVEL%
    echo ビルド失敗
    set errmsg="vtkWrapperLib"
    goto err
)
echo "vtkWrapperLib build success" >> log.txt

:2
set build=.\build\build.sln
MSBuild %build% /t:clean;rebuild /p:Configuration=release;Platform="x64"
MSBuild %build% /t:build /p:Configuration=release;Platform="x64"
if %ERRORLEVEL% neq 0 (
    echo ErrorLevel:%ERRORLEVEL%
    echo ビルド失敗
    set errmsg="build"
    goto err
)
echo "build build success" >> log.txt



echo "build finish" >> log.txt
