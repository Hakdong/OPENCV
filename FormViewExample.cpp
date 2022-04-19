#include "stdafx.h"
#include "resource.h"
#include "FormViewExample.h"
#include "CommonUtillfunc.h"
IMPLEMENT_DYNCREATE(CFormViewExample, CRavidFormViewBase)

CFormViewExample::CFormViewExample()
	: CRavidFormViewBase(IDD_FORM_VIEW_EXAMPLE)

{

}

CFormViewExample::~CFormViewExample()
{
}

void CFormViewExample::DoDataExchange(CDataExchange* pDX)
{
	CRavidFormViewBase::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT1, m_editMinVal);
	DDX_Control(pDX, IDC_EDIT2, m_editMaxVal);
	DDX_Control(pDX, IDC_EDIT3, m_editDisVal);

}

BEGIN_MESSAGE_MAP(CFormViewExample, CRavidFormViewBase)
	ON_BN_CLICKED(IDC_SAVE, &CFormViewExample::OnBnClickedButSave)
END_MESSAGE_MAP()

#ifdef _DEBUG
void CFormViewExample::AssertValid() const
{
	CRavidFormViewBase::AssertValid();
}

#ifndef _WIN32_WCE
void CFormViewExample::Dump(CDumpContext& dc) const
{
	CRavidFormViewBase::Dump(dc);
}
#endif
#endif //_DEBUG


void CFormViewExample::OnBnClickedButSave()
{
	CModelInfo* pModel = CModelManager::GetModelInfo(0);

	if (!pModel)
		return;

	SType0ModelParam sData;

	if (!pModel->GetData(&sData, sizeof(SType0ModelParam)))
		return;

	CString strValue;
	double dNumber;


	m_editMinVal.GetWindowTextW(strValue);
	dNumber = _wtof(strValue);
	sData.minDiff = dNumber;

	m_editMaxVal.GetWindowTextW(strValue);
	dNumber = _wtof(strValue);
	sData.maxdiff = dNumber;

	m_editDisVal.GetWindowTextW(strValue);
	dNumber = _wtof(strValue);
	sData.Yoffset = dNumber;

	//////
	pModel->SaveData(&sData, sizeof(SType0ModelParam));
}
void CFormViewExample::InitValue()
{
	CModelInfo* pModel = CModelManager::GetModelInfo(0);

	if (!pModel)
		return;


	SType0ModelParam sData;

	

	if (!pModel->GetData(&sData, sizeof(SType0ModelParam)))
		return;


	UpdateData(true);
	CString strValue;

	strValue.Format(_T("%.2f"), sData.minDiff);
	m_editMinVal.SetWindowTextW(strValue);

	strValue.Format(_T("%.2f"), sData.maxdiff);
	m_editMaxVal.SetWindowTextW(strValue);

	strValue.Format(_T("%.2f"), sData.Yoffset);
	m_editDisVal.SetWindowTextW(strValue);
	UpdateData(false);
}