// Register.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "PassengerTicketSystem.h"
#include "Register.h"
#include "afxdialogex.h"


// CRegister �Ի���

IMPLEMENT_DYNAMIC(CRegister, CDialogEx)

CRegister::CRegister(CWnd* pParent /*=NULL*/)
	: CDialogEx(CRegister::IDD, pParent)
{

	m_Name = _T("");
	m_Password = _T("");
}

CRegister::~CRegister()
{
}

void CRegister::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_USER, m_Name);
	DDX_Text(pDX, IDC_EDIT_PASSWORD, m_Password);
	DDX_Control(pDX, IDC_COMBO_USER, m_ComBoUser);
}


BEGIN_MESSAGE_MAP(CRegister, CDialogEx)
	ON_BN_CLICKED(IDOK, &CRegister::OnBnClickedOk)
	ON_WM_PAINT()
	ON_WM_CTLCOLOR()
END_MESSAGE_MAP()


// CRegister ��Ϣ�������


void CRegister::OnBnClickedOk()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	UpdateData(TRUE);
	char Name[20]={0};
	char PassWord[20]={0};
	wcstombs(Name,m_Name,20);
	wcstombs(PassWord,m_Password,20);
	int i =0;
	if(m_Name==L""||m_Password==L"")
	{
		MessageBox(L"������������Ϣ",L"������");
		return;
	}
	CString Temp;
	m_ComBoUser.GetWindowText(Temp);
	if(Temp==L"���չ�˾ע��")
	{
	//	MessageBox(L"a",L"s");
		Login.ReadCompany();
		for(i=0;i<Login.CompanyNum;i++)
		{
			if(strcmp(Login.User[i].LoginName,Name)==0)
			{
				MessageBox(L"���û���ע��",L"������");
				return;
			}
		}
		Login.CompanyNum++;
	
		strcpy(Login.User[Login.CompanyNum-1].LoginName,Name);
		strcpy(Login.User[Login.CompanyNum-1].Password,PassWord);
		Login.SaveCompany();
	}
	

	if(Temp==L"������ע��")
	{
		//	MessageBox(L"a",L"s");
		//Login.SaveTravel();
		Login.ReadTravel();
		for(i=0;i<Login.TravelNum;i++)
		{
			if(strcmp(Login.User[i].LoginName,Name)==0)
			{
				MessageBox(L"���û���ע��",L"������");
				return;
			}
		}
		Login.TravelNum++;

		strcpy(Login.User[Login.TravelNum-1].LoginName,Name);
		strcpy(Login.User[Login.TravelNum-1].Password,PassWord);
		Login.SaveTravel();
	}

	if(Temp==L"�����û�ע��")
	{
		//	MessageBox(L"a",L"s");
		Login.ReadPerson();
		for(i=0;i<Login.UserNum;i++)
		{
			if(strcmp(Login.User[i].LoginName,Name)==0)
			{
				MessageBox(L"���û���ע��",L"������");
				return;
			}
		}
		Login.UserNum++;

		strcpy(Login.User[Login.UserNum-1].LoginName,Name);
		strcpy(Login.User[Login.UserNum-1].Password,PassWord);
		Login.SavePerson();
	}
	CDialogEx::OnOK();
}


BOOL CRegister::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��

	m_ComBoUser.AddString(L"���չ�˾ע��");
	m_ComBoUser.AddString(L"������ע��");
	m_ComBoUser.AddString(L"�����û�ע��");
	m_ComBoUser.SetWindowText(L"�����û�ע��");

	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}


void CRegister::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	// TODO: �ڴ˴������Ϣ����������
	// ��Ϊ��ͼ��Ϣ���� CDialogEx::OnPaint()
	CDC *pDC;
  	pDC=GetDC();
  	CRect rect;
  	GetClientRect(&rect);
 	 CBitmap wtj_bitmap;
 	 CDC dcMemory;
 
 	 wtj_bitmap.LoadBitmap(IDB_BITMAP_Reg);
 	 BITMAP bmInfo;
  	wtj_bitmap.GetObject(sizeof(bmInfo),&bmInfo);
  	dcMemory.CreateCompatibleDC(pDC);
   	dcMemory.FillSolidRect(&rect,RGB(255,0,0));
  	dcMemory.SelectObject(&wtj_bitmap);
 

  	pDC->StretchBlt(0,0,
  	 rect.Width(),rect.Height(),
  	 &dcMemory,
 	  0,0,
  	 bmInfo.bmWidth,bmInfo.bmHeight,
  	 SRCCOPY);

 	 ReleaseDC(pDC);

}


HBRUSH CRegister::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialogEx::OnCtlColor(pDC, pWnd, nCtlColor);

	// TODO:  �ڴ˸��� DC ���κ�����

	// TODO:  ���Ĭ�ϵĲ������軭�ʣ��򷵻���һ������

	UINT id = pWnd->GetDlgCtrlID();
	if(id == IDC_STATIC)// || id == IDC_CHECK1)
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
