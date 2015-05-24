/****************************************************************************

	XDirectTileWidget Class
		Copyright (C) 2015 Andre Deperrois adeperrois@xflr5.com

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

#ifndef XDIRECTTILEWIDGET_H
#define XDIRECTTILEWIDGET_H

#include "graphtilewidget.h"
#include "foilwidget.h"
#include <QStackedWidget>
#include <QGridLayout>

class XDirectTileWidget : public GraphTileWidget
{
	Q_OBJECT

public:
	XDirectTileWidget(QWidget *pParent = NULL);
	~XDirectTileWidget();

public:
	void Connect();
	void adjustLayout();
	void setGraphList(QList<QGraph*>pGraphList, int nGraphs, int iGraphWidget, Qt::Orientation orientation =Qt::Horizontal);

    FoilWidget *foilWidget(){return m_pFoilWidget;}


private:
	void setupMainLayout();

//	QStackedWidget *m_pLegendStack;
	FoilWidget *m_pFoilWidget;


	QGridLayout *m_pMainGridLayout;
};

#endif // XDIRECTTILEWIDGET_H
