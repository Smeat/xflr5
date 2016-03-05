
/****************************************************************************

	GLLightDlg class
	Copyright (C) 2009 Andre Deperrois xflr5@yahoo.com

	This program is free software; you can redistribute it and/or modify
	it under the terms of the GNU General Public License as published by
	the Free Software Foundation; either version 2 of the License, or
	(at your option) any later version.

	This program is distributed in the hope that it will be useful,
	but WITHOUT ANY WARRANTY; without even the implied warranty of
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
	GNU General Public License for more details.

	You should have received a copy of the GNU General Public License
	along with this program; if not, write to the Free Software
	Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA

*****************************************************************************/


#ifndef GLLIGHTDLG_H
#define GLLIGHTDLG_H

#include <QDialog>
#include <QCheckBox>
#include <QLabel>
#include <QPushButton>
#include <QSlider>
#include <QSettings>
#include "DoubleEdit.h"

struct Light
{
	float m_Ambient, m_Diffuse, m_Specular;
	float m_Red, m_Green, m_Blue;
	float m_X, m_Y, m_Z;
	bool m_bIsLightOn;
};


struct Material
{
	float m_Ambient, m_Diffuse, m_Specular;
	int m_iShininess;
};

struct Attenuation
{
	float m_Constant, m_Linear, m_Quadratic;
};


class GLLightDlg : public QDialog
{
	Q_OBJECT
	friend class QMiarex;
	friend class GL3Widget;

public:
    GLLightDlg(QWidget *pParent=NULL);
	void apply();
	void readParams(void);
	void setDefaults();
	void setModelSize(double span);
	void setParams(void);
	void setgl3Widget(void*pgl3Widget) {m_pgl3Widget = pgl3Widget;}

	QSize minimumSizeHint() const;
	QSize sizeHint() const;

	static bool loadSettings(QSettings *pSettings);
	static bool saveSettings(QSettings *pSettings);

	static bool isLightOn() {return s_Light.m_bIsLightOn;}
	static void setLightOn(bool bLight) {s_Light.m_bIsLightOn = bLight;}

private:
	void setupLayout();
	void showEvent(QShowEvent *event);
	void setEnabled();
	void setLabels();

private slots:
	void onChanged();
	void onDefaults();
	void onLight();

private:
	QSlider *m_pctrlRed, *m_pctrlGreen, *m_pctrlBlue;
	QSlider *m_pctrlLightAmbient, *m_pctrlLightDiffuse, *m_pctrlLightSpecular;
	QSlider *m_pctrlXLight, *m_pctrlYLight, *m_pctrlZLight;
	QSlider *m_pctrlMatAmbient, *m_pctrlMatDiffuse, *m_pctrlMatSpecular, *m_pctrlMatShininess;

	QCheckBox *m_pctrlLight;
	QLabel *m_pctrlLightAmbientLabel, *m_pctrlLightDiffuseLabel, *m_pctrlLightSpecularLabel;
	QLabel *m_pctrlposXValue, *m_pctrlposYValue, *m_pctrlposZValue;
	QLabel *m_pctrlLightRed, *m_pctrlLightGreen, *m_pctrlLightBlue;
	QLabel *m_pctrlMatAmbientLabel, *m_pctrlMatDiffuseLabel, *m_pctrlMatSpecularLabel, *m_pctrlMatShininessLabel;

	QPushButton *m_pctrlDefaults, *m_pctrlClose;

	DoubleEdit *m_pctrlConstantAttenuation , *m_pctrlLinearAttenuation , *m_pctrlQuadAttenuation ;
	QLabel *m_pctrlAttenuation;


private:
	void *m_pgl3Widget;

	static Light s_Light;
	static Material s_Material;
	static Attenuation s_Attenuation;

	double m_ModelSize;

};

#endif // GLLIGHTDLG_H

