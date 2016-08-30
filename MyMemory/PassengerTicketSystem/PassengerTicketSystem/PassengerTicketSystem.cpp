
// PassengerTicketSystem.cpp : ����Ӧ�ó��������Ϊ��
//

#include "stdafx.h"
#include "PassengerTicketSystem.h"
#include "PassengerTicketSystemDlg.h"
#include "Login.h"
#include "Flight.h"
#include "Person.h"
#include "Welcome.h"
#include "Common.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CPassengerTicketSystemApp

BEGIN_MESSAGE_MAP(CPassengerTicketSystemApp, CWinApp)
	ON_COMMAND(ID_HELP, &CWinApp::OnHelp)
END_MESSAGE_MAP()


// CPassengerTicketSystemApp ����

CPassengerTicketSystemApp::CPassengerTicketSystemApp()
{
	// ֧����������������
	m_dwRestartManagerSupportFlags = AFX_RESTART_MANAGER_SUPPORT_RESTART;

	// TODO: �ڴ˴���ӹ�����룬
	// ��������Ҫ�ĳ�ʼ�������� InitInstance ��
}


// Ψһ��һ�� CPassengerTicketSystemApp ����

CPassengerTicketSystemApp theApp;


// CPassengerTicketSystemApp ��ʼ��

BOOL CPassengerTicketSystemApp::InitInstance()
{
	// ���һ�������� Windows XP �ϵ�Ӧ�ó����嵥ָ��Ҫ
	// ʹ�� ComCtl32.dll �汾 6 ����߰汾�����ÿ��ӻ���ʽ��
	//����Ҫ InitCommonControlsEx()�����򣬽��޷��������ڡ�
	INITCOMMONCONTROLSEX InitCtrls;
	InitCtrls.dwSize = sizeof(InitCtrls);
	// ��������Ϊ��������Ҫ��Ӧ�ó�����ʹ�õ�
	// �����ؼ��ࡣ
	InitCtrls.dwICC = ICC_WIN95_CLASSES;
	InitCommonControlsEx(&InitCtrls);

	CWinApp::InitInstance();


	

	AfxEnableControlContainer();

	// ���� shell ���������Է��Ի������
	// �κ� shell ����ͼ�ؼ��� shell �б���ͼ�ؼ���
	CShellManager *pShellManager = new CShellManager;

	// ��׼��ʼ��
	// ���δʹ����Щ���ܲ�ϣ����С
	// ���տ�ִ���ļ��Ĵ�С����Ӧ�Ƴ�����
	// ����Ҫ���ض���ʼ������
	// �������ڴ洢���õ�ע�����
	// TODO: Ӧ�ʵ��޸ĸ��ַ�����
	// �����޸�Ϊ��˾����֯��
	SetRegistryKey(_T("Ӧ�ó��������ɵı���Ӧ�ó���"));


	CLogin LoginDlg;
	if(LoginDlg.DoModal()==IDOK)
	{
		if(LoginDlg.iTypeUser=="���չ�˾")
		{
			CFlight Flight;
			Flight.DoModal();
		}
		if(LoginDlg.iTypeUser=="������")
		{

			WCHAR Name[20] = {0};
			wsprintf(Name,L"%s",LoginDlg.m_Name);
			CCommon Common;
			Common.saveUser(Name);

		
			CWelcome Welcome;
			Welcome.DoModal();
		}
		if(LoginDlg.iTypeUser=="����")
		{
			WCHAR Name[20] = {0};
			wsprintf(Name,L"%s",LoginDlg.m_Name);
			CCommon Common;
			Common.saveUser(Name);

			CWelcome Welcome;
			Welcome.DoModal();
		}
	}


	
	
	return FALSE;
}


/*
CPassengerTicketSystemDlg dlg;
m_pMainWnd = &dlg;
INT_PTR nResponse = dlg.DoModal();

if (nResponse == IDOK)
{
	// TODO: �ڴ˷��ô����ʱ��
	//  ��ȷ�������رնԻ���Ĵ���
}
else if (nResponse == IDCANCEL)
{
	// TODO: �ڴ˷��ô����ʱ��
	//  ��ȡ�������رնԻ���Ĵ���
}

// ɾ�����洴���� shell ��������
if (pShellManager != NULL)
{
	delete pShellManager;
}

// ���ڶԻ����ѹرգ����Խ����� FALSE �Ա��˳�Ӧ�ó���
//  ����������Ӧ�ó������Ϣ�á�
	}
	*/