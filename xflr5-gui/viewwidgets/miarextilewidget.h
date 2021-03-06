/****************************************************************************

	MiarexTileWidget Class
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

#ifndef MIAREXTILEWIDGET_H
#define MIAREXTILEWIDGET_H

#include "graphtilewidget.h"
#include "wingwidget.h"
#include <QGridLayout>

class MiarexTileWidget : public GraphTileWidget
{
	Q_OBJECT

public:
	MiarexTileWidget(QWidget *pParent = NULL);
	~MiarexTileWidget();

public:
	void connectSignals();
	void adjustLayout();
	void setMiarexGraphList(XFLR5::enumMiarexViews miarexView, QList<QGraph*>pGraphList, int nGraphs, int iGraphWidget=-1, Qt::Orientation orientation =Qt::Horizontal);
	WingWidget *pWingWidget(){return m_pWingWidget;}

private:
	void setupMainLayout();

private slots:
	void onSplitterMoved(int pos, int index);

private:
	XFLR5::enumMiarexViews &miarexView(){return m_MiarexView;}

	WingWidget *m_pWingWidget;
	QGridLayout *m_pMainGridLayout;
};

#endif // MIAREXTILEWIDGET_H
