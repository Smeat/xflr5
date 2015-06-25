/****************************************************************************

	Frame Class
	Copyright (C) 2007-2013 Andre Deperrois adeperrois@xflr5.com

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
 
/** @file This file implements the Frame class used in the definition of Body objects */
 
#ifndef FRAME_H
#define FRAME_H

#include "CVector.h"
#include <QDataStream>
#include <QList>

/**
*@class Frame This class defines a frame in the yz plane, on which the body surface is built. 
 * This is similar to the way a real life body is designed and built.
 * The Frame's points may be used indiferently by a spline-type or a flat-panel-type body.
 * The Frmae's points are defined from bottom to top, i.e. for crescending z values, and for the body's left (port) side. 
  * The x-value of the control points is unused, the frame's position is defined by the variable m_Position.
*/
class Frame
{
public:
	Frame(int nCtrlPts=0);

	void    appendPoint(CVector const& Pt);
	void    copyFrame(Frame *pFrame);
	void    copyPoints(QList<CVector> *pPointList);
	double  height();
	int     isPoint(CVector const &Point, double const &ZoomFactor);
	void    insertPoint(int n);
	void    insertPoint(int n, const CVector &Pt);
	int     insertPoint(CVector const &Real, int iAxis);
	CVector Point(int iPt) {return m_CtrlPoint.at(iPt);}
	int     PointCount() {return m_CtrlPoint.size();}
	bool    removePoint(int n);
	void    rotateFrameY(double Angle);
	bool    serializeFrame(QDataStream &ar, bool bIsStoring);
	void    setPosition(CVector Pos);
	void    setuPosition(double u);
	void    setvPosition(double v);
	void    setwPosition(double w);
	double  zPos();

	CVector & position(){return m_Position;}
	CVector &selectedPoint(){return m_CtrlPoint[s_iSelect];}

	QList <CVector> m_CtrlPoint;	/**< the array of points which define the frame.  */
	static int s_iHighlight;               /**< the point over which the mouse hovers, or -1 if none */
	static int s_iSelect;                  /**< the selected pointed, i.e. the last point on which the user has clicked, or -1 if none */
	CVector m_Position;             /**< the translation vector for the Frame's origin */
};


#endif

