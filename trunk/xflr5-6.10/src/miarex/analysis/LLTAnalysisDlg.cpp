/****************************************************************************

    LLTAnalysisDlg Class
	Copyright (C) 2009 Andre Deperrois adeperrois@xflr5.com

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

#include <math.h>
#include <QApplication>
#include <QDir>
#include <QDateTime>
#include <QTimer>
#include <QDesktopWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QKeyEvent>
#include <QtDebug>

#include "LLTAnalysisDlg.h"
#include "../Objects3D.h"
#include "../../misc/Settings.h"



void *LLTAnalysisDlg::s_pPrePost3D;
void *LLTAnalysisDlg::s_pMiarex;
QPoint LLTAnalysisDlg::s_Position;


/**
*The public constructor
*/
LLTAnalysisDlg::LLTAnalysisDlg(QWidget *pParent, LLTAnalysis *pLLTAnalysis) : QDialog(pParent)
{
	setWindowTitle(tr("LLT Analysis"));

	SetupLayout();

	m_pLLT = pLLTAnalysis;

	m_pIterGraph = m_pGraphWidget->graph();
	m_pIterGraph->CopySettings(&Settings::s_RefGraph, false);
	m_pIterGraph->SetXTitle(tr("Iterations"));
	m_pIterGraph->SetYTitle("");

	m_pIterGraph->SetAuto(true);

	m_pIterGraph->SetMargin(40);

	m_pIterGraph->SetXMajGrid(true, QColor(120,120,120),2,1);
	m_pIterGraph->SetYMajGrid(true, QColor(120,120,120),2,1);

	m_pIterGraph->SetXMin(0.0);
	m_pIterGraph->SetXMax(50);
	m_pIterGraph->SetYMin(0.0);
	m_pIterGraph->SetYMax(1.0);
	m_pIterGraph->SetType(1);

	m_pIterGraph->SetYTitle("|Da|");


	m_bCancel     = false;
	m_bFinished   = false;

	m_LegendPlace.rx() = 0;
	m_LegendPlace.ry() = 0;

	m_pXFile       = NULL;

	m_pLLT->m_pGraph = m_pIterGraph;
}



/**
*Initializes the dialog and its associated data.
*/
void LLTAnalysisDlg::initDialog()
{
	m_pctrlTextOutput->setFont(Settings::s_TableFont);

	QString FileName = QDir::tempPath() + "/XFLR5.log";
	m_pXFile = new QFile(FileName);
	if (!m_pXFile->open(QIODevice::WriteOnly | QIODevice::Text)) m_pXFile = NULL;

	SetFileHeader();

	if(m_pXFile) m_pLLT->m_OutStream.setDevice(m_pXFile);

	m_pIterGraph->DeleteCurves();

	m_pIterGraph->SetXMin(0.0);
	m_pIterGraph->SetXMax((double)LLTAnalysis::s_IterLim);
	m_pIterGraph->SetX0(0.0);
	m_pIterGraph->SetXUnit((int)(LLTAnalysis::s_IterLim/10.0));

	m_pIterGraph->SetY0(0.0);
	m_pIterGraph->SetYMin(0.0);
	m_pIterGraph->SetYMax(1.0);

}



/** Overrides and handles the keyPressEvent sent by Qt */
void LLTAnalysisDlg::keyPressEvent(QKeyEvent *event)
{
	switch (event->key())
	{
		case Qt::Key_Escape:
		{
			OnCancelAnalysis();
			event->accept();
			return;
		}
		default:
			event->ignore();
	}
}



/** The user has requested the cancellation of the analysis*/
void LLTAnalysisDlg::OnCancelAnalysis()
{
	m_bCancel = true;

	if(m_pXFile->isOpen()) m_pXFile->close();

	if(m_bFinished) accept();
}




/**
*Clears the content of the graph's curve prior to the start of the calculation of the next operating point.
*/
void LLTAnalysisDlg::ResetCurves()
{
	Curve*pCurve;
	pCurve = m_pIterGraph->GetCurve(0);
	if(pCurve) pCurve->clear();
	pCurve = m_pIterGraph->GetCurve(1);
	if(pCurve) pCurve->clear();

}



/**
* Initializes the header of the log file
*/
void LLTAnalysisDlg::SetFileHeader()
{
	if(!m_pXFile) return;
	QTextStream out(m_pXFile);
	out << "\n";
	out << VERSIONNAME;
	out << "\n";

	QDateTime dt = QDateTime::currentDateTime();
	QString str = dt.toString("dd.MM.yyyy  hh:mm:ss");

	out << str;
	out << "\n___________________________________\n\n";
}

/**
* Initializes the interface of the dialog box
*/
void LLTAnalysisDlg::SetupLayout()
{
	QDesktopWidget desktop;
	QRect r = desktop.geometry();
//	setMinimumHeight(r.height()*2/3);
	setMinimumWidth((int)(r.width()*2.0/5.0));

	m_pctrlTextOutput = new QTextEdit;
	QFont outFont;
	outFont.setStyleHint(QFont::TypeWriter);
	outFont.setFamily(outFont.defaultFamily());
	outFont.setPointSize(9);
	m_pctrlTextOutput->setFont(outFont);
	m_pctrlTextOutput->setReadOnly(true);
	m_pctrlTextOutput->setLineWrapMode(QTextEdit::NoWrap);
	m_pctrlTextOutput->setWordWrapMode(QTextOption::NoWrap);
	m_pctrlTextOutput->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Expanding);

	m_pGraphWidget = new GraphWidget;
	m_pGraphWidget->setMinimumHeight(r.height()/3);
	m_pGraphWidget->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Maximum);

	m_pGraphWidget->showLegend(true);


	m_pctrlCancel = new QPushButton(tr("Cancel"));
	connect(m_pctrlCancel, SIGNAL(clicked()), this, SLOT(OnCancelAnalysis()));


	QVBoxLayout *mainLayout = new QVBoxLayout;
	{
		mainLayout->addWidget(m_pctrlTextOutput);
		mainLayout->addWidget(m_pGraphWidget,2);
		mainLayout->addWidget(m_pctrlCancel);
	}
	setLayout(mainLayout);
}


/**
* Launches the analysis.
* At this stage, the dialogbox has been setup and initialized.
* The LLTAnalysis object has been created and the input data has been loaded.
* Depending on the type of polar, the method launches either a loop over aoa or velocity values.
*/
void LLTAnalysisDlg::Analyze()
{
	if(!m_pLLT->m_pWing || !m_pLLT->m_pWPolar) return;
	//all set to launch the analysis

	m_pctrlCancel->setText(tr("Cancel"));
	m_bCancel     = false;
	m_bFinished   = false;


	QTimer *pTimer = new QTimer;
	connect(pTimer, SIGNAL(timeout()), this, SLOT(OnProgress()));
	pTimer->setInterval(100);
	pTimer->start();

	m_pctrlTextOutput->clear();

	QString strange;
	strange = 	m_pLLT->m_pWing->WingName()+"\n";
	UpdateOutput(strange);
	strange = m_pLLT->m_pWPolar->polarName()+"\n";
	UpdateOutput(strange);

	strange = tr("Launching analysis....")+"\n\n";
	UpdateOutput(strange);
	strange = QString(tr("Max iterations     = %1")+"\n").arg(LLTAnalysis::s_IterLim);
	UpdateOutput(strange);
	strange = QString(tr("Alpha precision    = %1 deg")+"\n").arg(LLTAnalysis::s_CvPrec,0,'f',6);
	UpdateOutput(strange);
	strange = QString(tr("Number of stations = %1")+"\n").arg(LLTAnalysis::s_NLLTStations);
	UpdateOutput(strange);
	strange = QString(tr("Relaxation factor  = %1")+"\n\n").arg(LLTAnalysis::s_RelaxMax,0,'f',1);
	UpdateOutput(strange);

	m_pIterGraph->ResetLimits();
	m_pIterGraph->SetXMax((double)LLTAnalysis::s_IterLim);
	m_pIterGraph->SetYMinGrid(false, true, QColor(100,100,100), 2, 1, 4);

	m_pLLT->initializeAnalysis();

	m_pLLT->loop();

	pTimer->stop();

	m_pLLT->m_OutStream.flush();

	for(int iPOpp=0; iPOpp<m_pLLT->m_PlaneOppList.size(); iPOpp++)
	{
        Objects3D::InsertPOpp(m_pLLT->m_PlaneOppList.at(iPOpp));
	}

	m_bFinished = true;
	strange = "\n_________\n"+tr("Analysis completed");
	if(m_pLLT->m_bWarning)     strange += tr(" ...some points are outside the flight envelope");
	else if(m_pLLT->m_bError)  strange += tr(" ...some points are unconverged");

	strange+= "\n";

	m_pLLT->traceLog(strange);
	OnProgress();
	m_pctrlCancel->setText(tr("Close"));
	m_pXFile->close();
}


/**
* Updates the graph widget. Called after each iteration of the LLTAnalysis. 
* Time consuming, but it's necessary to provide the user with visual feedback on the progress of the analysis
*/
void LLTAnalysisDlg::UpdateView()
{
	m_pGraphWidget->update();
	repaint();
}

/**Updates the progress of the analysis in the slider widget */
void LLTAnalysisDlg::OnProgress()
{
	if(m_pLLT->m_OutMessage.length())
	{
		m_pctrlTextOutput->insertPlainText(m_pLLT->m_OutMessage);
		m_pctrlTextOutput->textCursor().movePosition(QTextCursor::End);
		m_pctrlTextOutput->ensureCursorVisible();
	}
	m_pLLT->m_OutMessage.clear();
	m_pGraphWidget->update();
}


/**
* Updates the text output in the dialog box and the log file.
*@param strong the text message to append to the output widget and to the log file.
*/
void LLTAnalysisDlg::UpdateOutput(QString &strong)
{
	m_pctrlTextOutput->insertPlainText(strong);
	m_pctrlTextOutput->ensureCursorVisible();
	WriteString(strong);
}


/**
* Appends a string to the log file
*@param strong the text message to append to the log file.
*/
void LLTAnalysisDlg::WriteString(QString &strong)
{
	if(!m_pXFile) return;
	if(!m_pXFile->isOpen()) return;
	QTextStream ds(m_pXFile);
	ds << strong;
}


/** 
* Appends a point to the curve in the graph widget 
* @param x the x-value of the point to be appended
* @param x the y-value of the point to be appended
*/
void LLTAnalysisDlg::UpdateGraph(int x, double y)
{
	Curve *pCurve = m_pIterGraph->GetCurve(0);
	if(pCurve) pCurve->AppendPoint((double)x,y);
	UpdateView();
}




void LLTAnalysisDlg::showEvent(QShowEvent *event)
{
	move(s_Position);
	event->accept();
}

void LLTAnalysisDlg::hideEvent(QHideEvent *event)
{
	s_Position = pos();
	event->accept();
}




