/*
 * VTK���ȒP�Ɂi�H�j�g�����߂̊ȒP�N���X���C�u����
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
 * XY�v���b�^�[�̍쐬
 *
 */
#ifndef _GMRVTKXYPLOT_HPP
#define _GMRVTKXYPLOT_HPP

#include "gmrVTK.hpp"
#include "gmrVTKDefs.hpp"
#include "gmrVTKRender.hpp"

#include <vector>
#include <string>


/** 
 * @brief XY�v���b�g�f�[�^�N���X
 *
 */
class gmr_EXPORT gmrVTKXYPlotData
{
	vtkFloatArray *xCoords_;
	vtkFloatArray *yCoords_;
	vtkFieldData *curve_;
	vtkDataObject *plot_;
	double PlotColor_[4];

	bool LabelSet_;
	std::string Label_;


public:
	gmrVTKXYPlotData();
	virtual ~gmrVTKXYPlotData();

	/**  XY�v���b�g�f�[�^�擾
	 *
	 */
	vtkDataObject* GetPlotData()
	{
		return plot_;
	}

	bool isLabelSet() { return LabelSet_;}

	/** XY�v���b�g�̃��x���ݒ�
	 *
	 * @param [in] label XY�v���b�g�̃��x��
	 *
	 */
	void SetLabel( char* label)
	{
		LabelSet_ = true;
		Label_ = label;
	}

	std::string GetLabel()
	{
		return Label_;
	}

	

	/** XY�v���b�g�̕`��J���[�̐ݒ�
	 *
	 * @param[in] r ��
	 * @param[in] g ��
	 * @param[in] b ��
	 */
	void SetPlotColor(double r, double g, double b)
	{
		PlotColor_[0] = r;
		PlotColor_[1] = g;
		PlotColor_[2] = b;
	}
	void GetPlotColor(double color[3])
	{
		color[0] = PlotColor_[0];
		color[1] = PlotColor_[1];
		color[2] = PlotColor_[2];
	}

	/** XY�v���b�g�̃f�[�^�̐ݒ�
	 *
	 * @param [in] x X�l
	 * @param [in] y Y�l
	 *
	 */
	void SetXYData(double x, double y);

	/** XY�v���b�g�̃f�[�^�ݒ�I��
	 *
	 */
	void DataEnd();
};


/** 
 * @brief XY�v���b�^�[�N���X
 *
 */
class gmr_EXPORT gmrVTKXYPlotter
{
	std::vector<gmrVTKXYPlotData*> plotList_;
	vtkXYPlotActor *xyplot_;

	void CreateActor();
	double XRange_[2];
	double YRange_[2];
	int PointSize_;

	double WidthFactor_;
	double HeightFactor_;
	double WidthPositionFactor_;
	double HeightPositionFactor_;

public:
	gmrVTKXYPlotter();
	virtual ~gmrVTKXYPlotter();

	/** �V�K��XY�v���b�g�f�[�^�����i�ǉ�)
	 *
	 */
	gmrVTKXYPlotData* CreatePlotData();


	/** �A�N�^�[�̎擾
	 *
	 */
	vtkXYPlotActor* GetActor()
	{
		CreateActor();
		
		xyplot_ -> GetProperty() -> SetPointSize(PointSize_);
		xyplot_ -> SetXRange(XRange_[0],XRange_[1]);
		xyplot_ -> SetYRange(YRange_[0],YRange_[1]);
		xyplot_ -> SetPosition(WidthPositionFactor_,HeightPositionFactor_);
		xyplot_ -> SetPosition2(WidthFactor_, HeightFactor_);

		return xyplot_;
	}

	void DefaulRenderBackgroundColor(gmrVTKRender* ren)
	{
		ren->SetBackgroundColor(0.1,0.2,0.4);
	}


	/** �v���b�g�_�̃T�C�Y�ݒ�
	 *
	 * @param [in] size �v���b�g�_�̃T�C�Y
	 *
	 */
	void SetPointSize(int size)
	{
		PointSize_ = size;
	}

	/** �v���b�g�̓_��\������
	 *
	 */
	void PlotPointsOn()
	{
		GetActor() -> PlotPointsOn();
	}
	
	/** �v���b�g�̐܂����\������
	 *
	 */
	void PlotLinesOn()
	{
		GetActor() -> PlotLinesOn();
	}

	/** �v���b�g�̓_��\�����Ȃ�
	 *
	 */
	void PlotPointsOff()
	{
		GetActor() -> PlotPointsOff();
	}
	
	/** �v���b�g�̐܂����\�����Ȃ�
	 *
	 */
	void PlotLinesOff()
	{
		xyplot_ -> PlotLinesOff();
	}

	/** �v���b�^�[�̃^�C�g����ݒ肷��
	 *
	 * @param [in] title �v���b�^�[�̃^�C�g��
	 *
	 */
	void SetTitle( char* title)
	{
         GetActor()->SetTitle(title);
	}

	/** �v���b�^�[��X���^�C�g����ݒ肷��
	 *
	 * @param [in] title �v���b�^�[��X���^�C�g��
	 *
	 */
	void SetXTitle( char* title)
	{
         GetActor()->SetXTitle(title);
	}

	/** �v���b�^�[��Y���^�C�g����ݒ肷��
	 *
	 * @param [in] title �v���b�^�[��Y���^�C�g��
	 *
	 */
	void SetYTitle( char* title)
	{
         GetActor()->SetYTitle(title);
	}

	/** ��ʉ������̒����ݒ�i��ʉ���1.0�Ƃ����ꍇ)
	 *
	 * @param [in] w �i��ʉ���1.0�Ƃ����ꍇ�̒���)
	 *
	 */
	void SetWidthFactor( double w)
	{
		WidthFactor_ = w;
	}

	/** ��ʏc�����̒����ݒ�i��ʏc��1.0�Ƃ����ꍇ)
	 *
	 * @param [in] h �i��ʏc��1.0�Ƃ����ꍇ�̒���)
	 *
	 */
	void SetHeightFactor( double h)
	{
		HeightFactor_ = h;
	}

	/** ��ʉ������̈ʒu�ݒ�i��ʉ�����:0�`�E:1.0�Ƃ����ꍇ)
	 *
	 * @param [in] x �i��ʉ�����:0�`�E:1.0�Ƃ����ꍇ�̈ʒu)
	 *
	 */
	void SetWidthPositionFactor( double x)
	{
		WidthPositionFactor_ = x;
	}

	/** ��ʏc�����̈ʒu�ݒ�i��ʏc����:0�`�E:1.0�Ƃ����ꍇ)
	 *
	 * @param [in] y �i��ʏc����:0�`�E:1.0�Ƃ����ꍇ�̈ʒu)
	 *
	 */
	void SetHeightPositionFactor(double y)
	{
		HeightPositionFactor_ = y;
	}

};


#endif