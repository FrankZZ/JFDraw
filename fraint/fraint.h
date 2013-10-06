
// fraint.h : main header file for the fraint application
//
#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"       // main symbols


// CfraintApp:
// See fraint.cpp for the implementation of this class
//

class CfraintApp : public CWinAppEx
{
public:
	CfraintApp();

// Variables
public:
	static int CURRENT_SHAPE_TYPE;

// Overrides
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// Implementation

public:
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
	afx_msg void OnShapeRectangle();
//	afx_msg void OnShapeCircle();
	afx_msg void OnHelpAbout();
	afx_msg void OnShapeSelectortool();
	afx_msg void OnShapeCircle();
};

extern CfraintApp theApp;
