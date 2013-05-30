// T.h : main header file for the T application
//

#if !defined(AFX_T_H__2BF963E1_5048_45D6_8DD3_0B7B51F8DCAD__INCLUDED_)
#define AFX_T_H__2BF963E1_5048_45D6_8DD3_0B7B51F8DCAD__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CTApp:
// See T.cpp for the implementation of this class
//

class CTApp : public CWinApp
{
public:
	CTApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CTApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_T_H__2BF963E1_5048_45D6_8DD3_0B7B51F8DCAD__INCLUDED_)
