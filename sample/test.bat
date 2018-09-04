set LDM=.\bin\DICOM2bmp.exe

set RENDER=-vr -sample_dist 50 -iso 100
:set RENDER=-obj -o aaa.obj -target_reduction 0.8 -smooth 3

:%LDM% .\sliceImage -s 249 -base_name Capture
:goto end

%LDM% .\DICOM_DATA %RENDER%

:end
