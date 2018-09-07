## DICOM2BMP.exe folderName [-option]  

## option  

# Volume rendering  
**-vr** *sample_distace(default 1.0)*  

# Polygon rendering  
**-3d**  

# Volume rendering & Polygon rendering  
**-3dvr**  

# export  
**-bmp**  (slice viewer && slice image export bitmap)  
**-obj** (polygon export OBJ)  
**-stl** (polygon export STL)  

# export option  
**-smooth** *smoothing Iteration*  
**-target_reduction** *resize(%) *  
**-iso** *isovalue*  
**-o** *output_filename*  

# import option  
**-s** *slice_image_num*  
**-base_name** *Parts other than numbers of consecutive file names*  
**-ext** *file extension(default=.bmp)
**-scale** *scale transform(default=1,1,1)

# Color
setting file '**color.def**'

**color.def example**
color_default.txt
**color_default.txt example** Line->iso,R,G,B,Alpha
0.000000,0.000000,0.200000,0.500000,0.000000
20.000000,0.200000,0.200000,0.200000,0.10000
50.000000,0.200000,0.200000,0.200000,0.20000
64.000000,0.980392,0.549020,0.329412,0.500000
190.000000,1.000000,0.925490,0.925490,0.600000
220.000000,0.800000,0.825490,0.825490,0.700000

**import image color**
setting file '**bmp_volume.txt**'
**bmp_volume.txt example** Line->iso,R,G,B,Alpha
0.000000,0.000000,0.200000,0.500000,0.000000
20.000000,0.200000,0.200000,0.200000,0.10000
50.000000,0.200000,0.200000,0.200000,0.20000
64.000000,0.980392,0.549020,0.329412,0.500000
190.000000,1.000000,0.925490,0.925490,0.600000
220.000000,0.800000,0.825490,0.825490,0.700000
221.
