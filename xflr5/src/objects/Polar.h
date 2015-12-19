/****************************************************************************

    Polar Class
	Copyright (C) 2003-2015 Andre Deperrois adeperrois@xflr5.com

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

/** 
 * @file
 * This file implements the Polar class for the 2D analysis of Foil objects
 *
 */


#ifndef POLAR_H
#define POLAR_H

#include <objects/linestyle.h>
#include "OpPoint.h"
#include <QList>

/**
*@brief
 * This class defines the polar object for the 2D analysis of foils
 *
	The class stores both the analysis parameters and the analysis results.
	Each instance of this class is uniquely associated to an instance of a Foil object.
*/
class Polar
{
	friend class MainFrame;
	friend class QMiarex;
	friend class QXDirect;
	friend class BatchDlg;
	friend class BatchThreadDlg;
	friend class XFoilTask;
	friend class XFoilAnalysisDlg;
	friend class FoilPolarDlg;
	friend class EditPlrDlg;
	friend class ObjectPropsDlg;
	friend class XFoil;
	friend class FoilWidget;


public:
	Polar();
	void addOpPointData(OpPoint *pOpPoint);

	void addXFoilData(void* ptrXFoil);

	void addPoint(double Alpha, double Cd, double Cdp, double Cl, double Cm,
				  double Xtr1, double Xtr2, double HMom, double Cpmn, double Reynolds, double XCp);
	void exportPolar(QTextStream &out, XFLR5::enumTextFileType FileType, bool bDataOnly=false);
	void getPolarProperties(QString &PolarProperties, bool bData=false);
	void resetPolar();

	bool serialize(QDataStream &ar, bool bIsStoring);
	bool serializePolarXFL(QDataStream &ar, bool bIsStoring);

	void copySpecification(Polar *pPolar);
	void copyPolar(Polar *pPolar);

	bool isVisible(){return m_polarStyle.m_bIsVisible;}

	void replaceOppDataAt(int pos, OpPoint *pOpp);
	void insertOppDataAt(int pos, OpPoint *pOpp);
	void removePoint(int i);

	double getCm0();
	double getZeroLiftAngle();
	void getAlphaLimits(double &amin, double &amax);
	void getClLimits(double &Clmin, double &Clmax);
	void getLinearizedCl(double &Alpha0, double &slope);

	QString foilName() {return m_FoilName;}
	QString polarName() {return m_PlrName;}

	XFLR5::enumPolarType polarType() {return m_PolarType;}
	void setPolarType(XFLR5::enumPolarType type);

	void setFoilName(QString newFoilName) {m_FoilName = newFoilName;}
	void setPolarName(QString newPolarName) {m_PlrName = newPolarName;}

	void setAutoPolarName();

	LineStyle &lineStyle() {return m_polarStyle;}
	QColor &polarColor()   {return m_polarStyle.m_Color;}
	int &polarStyle()      {return m_polarStyle.m_Style;}
	int &polarWidth()      {return m_polarStyle.m_Width;}
	bool &bIsVisible()     {return m_polarStyle.m_bIsVisible;}
	int &points()     {return m_polarStyle.m_PointStyle;}

	static QString getAutoPolarName(XFLR5::enumPolarType polarType, double Re, double Mach, double NCrit, double ASpec=0.0);
	static QString variableName(int iVar);
	static Polar *curPolar() {return s_pCurPolar;}
	static Polar *getPolar(void* pFoilPtr, QString PolarName);
	static Polar *getPolar(QString m_FoilName, QString PolarName);
	static void setCurPolar(Polar *pPolar) {s_pCurPolar = pPolar;}
	static void deletePolar(Polar *pPolar);
	static void addPolar(Polar *pPolar);

public:

	QList <double> m_Alpha;             /**< the array of aoa values, in degrees */
	QList <double> m_Cl;                /**< the array of lift coefficients */
	QList <double> m_XCp;               /**< the array of centre of pressure positions */
	QList <double> m_Cd;                /**< the array of drag coefficients */
	QList <double> m_Cdp;               /**< the array of Cdp ? */
	QList <double> m_Cm;                /**< the array of pitching moment coefficients */
	QList <double> m_XTr1;              /**< the array of transition points on the top surface */
	QList <double> m_XTr2;              /**< the array of transition points on the top surface */
	QList <double> m_HMom;              /**< the array of flap hinge moments */
	QList <double> m_Cpmn;              /**< the array of Cpmn ? */
	QList <double> m_ClCd;              /**< the array of glide ratios */
	QList <double> m_Cl32Cd;            /**< the array of power factors*/
	QList <double> m_RtCl;              /**< the array of aoa values */
	QList <double> m_Re;                /**< the array of Re coefficients */

	static QList <void *> s_oaPolar;   /**< The array of void pointers to the foil Polar objects. */

private:
	static Polar* s_pCurPolar;         /**< a static pointer to the currently selected foil polar */

	QString m_PlrName;                  /**< the Polar's name, used for references */
	QString m_FoilName;                 /**< the name of the parent Foil to which this Polar object is attached */

	LineStyle m_polarStyle;

	//Analysis specification
	XFLR5::enumPolarType m_PolarType;          /**< the Polar type */
	int m_ReType;                       /**< the type of Reynolds number input, cf. XFoil documentation */
	int m_MaType;                       /**< the type of Mach number input, cf. XFoil documentation */
	double m_ASpec;                     /**< the specified aoa in the case of Type 4 polars */
	double m_Mach;                      /**< the Mach number */
	double m_ACrit;                     /**< the transition criterion */
	double m_XTop;                      /**< the point of forced transition on the upper surface */
	double m_XBot;                      /**< the point of forced transition on the lower surface */

public:
	double m_Reynolds;                  /**< the Reynolds number for a type 4 analysis */

};

#endif