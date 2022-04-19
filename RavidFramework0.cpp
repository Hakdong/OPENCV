#include "stdafx.h"
#include "RavidFramework0.h"
#include "FormViewExample.h"
#include "EventHandlerExample.h"
#include "SequenceExample.h"
#include "CommonUtillfunc.h"
using namespace Ravid::Framework;

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

BEGIN_MESSAGE_MAP(CRavidFramework0, CWinAppEx)
	ON_COMMAND(ID_HELP, &CWinAppEx::OnHelp)


END_MESSAGE_MAP()

CRavidFramework0::CRavidFramework0()
{
}

CRavidFramework0 theApp;

BOOL CRavidFramework0::InitInstance()
{
	CWinAppEx::InitInstance();

	SetRegistryKey(_T("RavidFramework0"));

	CUIManager::AddEasyConfigurationView(RUNTIME_CLASS(CFormViewExample));

	bool bSettingMode = false;
	CFrameworkManager::Begin(_T("Settings"), bSettingMode);

	CUIManager::RunUIConfiguration(0);

	CEventHandlerExample* pEventHandler = new CEventHandlerExample;
	if (pEventHandler)
		CEventHandlerManager::AddEventHandler(pEventHandler);

	CFormViewExample FE;

	FE.InitValue();

	CSequenceExample* pSequence = new CSequenceExample;
	if(pSequence)
		CSequenceManager::RegisterSequence(pSequence);

	bool bOpened = false;
	for (int i = 0; i < CModelManager::GetModelInfoCount(); i++)
	{
		CModelInfo* pModel = CModelManager::GetModelInfo(i);

		if (!pModel)
			continue;

		if (pModel->IsOpen())
		{
			bOpened = true;
			break;
		}
	}

	if (!bOpened && CModelManager::GetModelInfoCount() > 0)
	{
		CModelManager::OpenModelInfo(CModelManager::GetModelInfo(0)->GetModelNumber());
	}

	if (!bSettingMode)
	{
		CFormViewExample* pFormView = dynamic_cast<CFormViewExample*>(CUIManager::FindView(typeid(CFormViewExample), 6));

		if (!pFormView)
			return false;

		pFormView->InitValue();
	}



	return true;
} 


