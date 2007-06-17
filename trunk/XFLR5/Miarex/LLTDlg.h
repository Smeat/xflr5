/****************************************************************************

    CLLTDlg Class
    Copyright (C) 2005 Andr� Deperrois xflr5@yahoo.com

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

#pragma once

// LLTDlg.h : header file
//
#include "LLTThread.h"
#include "../Graph/Graph.h"

/////////////////////////////////////////////////////////////////////////////
// CLLTDlg dialog
  
class CLLTDlg : public CDialog
{
	friend class CLLTThread;
	friend class CMiarex;
	friend class CWOper;
// Construction
public:
	CLLTDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CLLTDlg)
	enum { IDD = IDD_ITERDLG };
	CButton	m_ctrlCancel;
	CButton	m_ctrlSkip;
	//}}AFX_DATA
 

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CLLTDlg)
	public:
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
private :
	bool EndSequence();
	bool m_bWarning;
	CStdioFile m_XFile;
	void SetFileHeader();
	void UpdateView(double Alpha);

	bool m_bSequence;
	bool m_bType4;
	int m_State;
	double m_Alpha;//Angle of Attack in �
	double m_AlphaMax;
	double m_DeltaAlpha;
	Graph m_IterGraph;
	CRect m_IterRect;
	CCurve* m_pIterCurve;

	CPoint m_DlgPos;

	CWing *m_pWing;//pointer to the geometry class of the wing 
	CWnd* m_pMiarex;
	CWnd *m_pFrame;
	CLLTThread *m_pWThread;

	// Generated message map functions
	//{{AFX_MSG(CLLTDlg)
	virtual BOOL OnInitDialog();
	virtual void OnCancel();
//	afx_msg void OnDestroy();
	afx_msg void OnSkip();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnTimer(UINT nIDEvent);
};

