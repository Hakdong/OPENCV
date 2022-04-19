#pragma once
#include "stdafx.h"
using namespace Ravid::Framework;

class CFormViewExample : public CRavidFormViewBase
{
	DECLARE_DYNCREATE(CFormViewExample)

public:
	CFormViewExample();
	virtual ~CFormViewExample();


#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_FORM_VIEW_EXAMPLE };
#endif
#ifdef _DEBUG
	virtual void AssertValid() const;
#ifndef _WIN32_WCE
	virtual void Dump(CDumpContext& dc) const;
#endif
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);


	DECLARE_MESSAGE_MAP()

public:


	afx_msg void CFormViewExample::OnBnClickedButSave();
	void CFormViewExample::InitValue();


	CEdit m_editMinVal;
	CEdit m_editMaxVal;
	CEdit m_editDisVal;

};
