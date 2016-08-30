// Type.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "PassengerTicketSystem.h"
#include "Type.h"
#include "afxdialogex.h"
#include "Login.h"


// CType �Ի���

IMPLEMENT_DYNAMIC(CType, CDialogEx)

CType::CType(CWnd* pParent /*=NULL*/)
	: CDialogEx(CType::IDD, pParent)
	, m_Type(_T(""))
	, m_Name(_T(""))
	, m_Old(_T(""))
	, m_New(_T(""))
{
	bOk = FALSE;
}

CType::~CType()
{
}

void CType::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_CBString(pDX, IDC_COMBO_Type, m_Type);
	DDX_Text(pDX, IDC_EDIT_NAME, m_Name);
	DDX_Text(pDX, IDC_EDIT_Old, m_Old);
	DDX_Text(pDX, IDC_EDIT_New, m_New);
	DDX_Control(pDX, IDC_COMBO_Type, m_TYPE);
}


BEGIN_MESSAGE_MAP(CType, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON_Sure, &CType::OnBnClickedButtonSure)
	ON_WM_CTLCOLOR()
END_MESSAGE_MAP()


// CType ��Ϣ�������


void CType::OnBnClickedButtonSure()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	UpdateData(TRUE);
	CLogin  Login;
	char Name[20]={0};
	char PassWordOld[20]={0};
	char PassWordNew[20] = {0};
	wcstombs(Name,m_Name,20);
	wcstombs(PassWordOld,m_Old,20);
	wcstombs(PassWordNew,m_New,20);
	int i =0;
	if(m_Name==L"")
	{
		MessageBox(L"�������û���",L"������");
		return;
	}
	CString Temp;
	m_TYPE.GetWindowText(Temp);
	if(Temp==L"���չ�˾")
	{
		//	MessageBox(L"a",L"s");
		Login.ReadCompany();

		for(i=0;i<Login.CompanyNum;i++)
		{
			if(strcmp(Login.User[i].LoginName,Name)==0)
			{
			   bOk = TRUE;
			}
		}
		if(bOk==TRUE)
		{
			for(i=0;i<Login.CompanyNum;i++)
			{
				if(strcmp(Login.User[i].LoginName,Name)==0&&strcmp(Login.User[i].Password,PassWordOld)==0)
				{
					if(strcmp(PassWordNew,PassWordOld)==0)
					{
						MessageBox(L"�����벻���������һ��",L"������");
						return ;
					}

					strcpy(Login.User[i].Password,PassWordNew);

					Login.SaveCompany();
					MessageBox(L"�޸ĳɹ�",L"�ɹ�");

					
				}
			}
		}
		else
		{
			MessageBox(L"�޴��û�",L"������");
			return;
		}
	
	}


	if(Temp==L"������")
	{
		//	MessageBox(L"a",L"s");
		//Login.SaveTravel();
		Login.ReadTravel();

		for(i=0;i<Login.TravelNum;i++)
		{
			if(strcmp(Login.User[i].LoginName,Name)==0)
			{
				bOk = TRUE;
			}
		}
		if(bOk==TRUE)
		{
			for(i=0;i<Login.TravelNum;i++)
			{
				if(strcmp(Login.User[i].LoginName,Name)==0&&strcmp(Login.User[i].Password,PassWordOld)==0)
				{
					if(strcmp(PassWordNew,PassWordOld)==0)
					{
						MessageBox(L"�����벻���������һ��",L"������");
						return ;
					}

					strcpy(Login.User[i].Password,PassWordNew);

					Login.SaveTravel();
					MessageBox(L"�޸ĳɹ�",L"�ɹ�");


				}
			}
		}
		else
		{
			MessageBox(L"�޴��û�",L"������");
			return;
		}

	}

	if(Temp==L"�����û�")
	{
		//	MessageBox(L"a",L"s");
		Login.ReadPerson();

		for(i=0;i<Login.UserNum;i++)
		{
			if(strcmp(Login.User[i].LoginName,Name)==0)
			{
				bOk = TRUE;
			}
		}
		if(bOk==TRUE)
		{
			for(i=0;i<Login.UserNum;i++)
			{
				if(strcmp(Login.User[i].LoginName,Name)==0&&strcmp(Login.User[i].Password,PassWordOld)==0)
				{
					if(strcmp(PassWordNew,PassWordOld)==0)
					{
						MessageBox(L"�����벻���������һ��",L"������");
						return ;
					}

					strcpy(Login.User[i].Password,PassWordNew);

					Login.SavePerson();
					MessageBox(L"�޸ĳɹ�",L"�ɹ�");


				}
			}
		}
		else
		{
			MessageBox(L"�޴��û�",L"������");
			return;
		}

	}

	CDialogEx::OnOK();
}


BOOL CType::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��

	m_TYPE.AddString(L"���չ�˾");
	m_TYPE.AddString(L"������");
	m_TYPE.AddString(L"�����û�");
	m_TYPE.SetWindowText(L"�����û�");


	CDialogEx::SetBackgroundImage(IDB_BITMAP_GRAND);
	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}


HBRUSH CType::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialogEx::OnCtlColor(pDC, pWnd, nCtlColor);

	// TODO:  �ڴ˸��� DC ���κ�����

	// TODO:  ���Ĭ�ϵĲ������軭�ʣ��򷵻���һ������


	UINT id = pWnd->GetDlgCtrlID();
	if(id == IDC_STATIC||id==IDC_COMBO_Type)// || id == IDC_CHECK1)
	{
		pDC->SetBkMode(TRANSPARENT);

		CRect rc;
		pWnd->GetWindowRect(&rc);
		ScreenToClient(&rc);

		CDC* dc = GetDC();

		pDC->BitBlt(0,0,rc.Width(),rc.Height(),dc,rc.left,rc.top,SRCCOPY);	//�Ѹ����ڱ���ͼƬ�Ȼ�����ť��

		ReleaseDC(dc);

		hbr = (HBRUSH) ::GetStockObject(NULL_BRUSH);
	}	
	return hbr;
}
