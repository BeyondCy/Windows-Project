// ADDFLIGHT.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "PassengerTicketSystem.h"
#include "ADDFLIGHT.h"
#include "afxdialogex.h"
#include "Common.h"


// CADDFLIGHT �Ի���

IMPLEMENT_DYNAMIC(CADDFLIGHT, CDialogEx)

CADDFLIGHT::CADDFLIGHT(CWnd* pParent /*=NULL*/)
	: CDialogEx(CADDFLIGHT::IDD, pParent)
	, m_FlightNum(_T(""))
	, m_Start(_T(""))
	, m_Arrive(_T(""))
	, m_StartDate(COleDateTime::GetCurrentTime())
	, m_StartTime(COleDateTime::GetCurrentTime())
	, m_ArriveDate(COleDateTime::GetCurrentTime())
	, m_ArriveTime(COleDateTime::GetCurrentTime())
	, m_PersonNum(_T(""))
	, m_Price(_T(""))
{

}

CADDFLIGHT::~CADDFLIGHT()
{
}

void CADDFLIGHT::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_FlightNum, m_FlightNum);
	DDX_Text(pDX, IDC_EDIT_Start, m_Start);
	DDX_Text(pDX, IDC_EDIT_Arrive, m_Arrive);
	DDX_DateTimeCtrl(pDX, IDC_DATETIMEPICKER1, m_StartDate);
	DDX_DateTimeCtrl(pDX, IDC_DATETIMEPICKER2, m_StartTime);
	DDX_DateTimeCtrl(pDX, IDC_DATETIMEPICKER3, m_ArriveDate);
	DDX_DateTimeCtrl(pDX, IDC_DATETIMEPICKER4, m_ArriveTime);
	DDX_Text(pDX, IDC_EDIT_PersonNum, m_PersonNum);
	DDX_Text(pDX, IDC_EDIT_Price, m_Price);
}


BEGIN_MESSAGE_MAP(CADDFLIGHT, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON_ADD, &CADDFLIGHT::OnBnClickedButtonAdd)
	ON_WM_CTLCOLOR()
END_MESSAGE_MAP()


// CADDFLIGHT ��Ϣ�������




void CADDFLIGHT::OnBnClickedButtonAdd()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������

	UpdateData(TRUE);
	if(m_FlightNum==L"")
	{
		MessageBox(L"�����뺽���",L"");
		return;
	}
	else if (m_FlightNum.GetLength()!=6)
	{
		MessageBox(L"��������λ�����");
		return;
	}
	else if(m_Start==L"")
		{
			MessageBox(L"�����������",L"");
		}
		else if(m_Arrive==L"")
		{
			MessageBox(L"������Ŀ�ĵ�",L"");
			return;
		}
		else if(m_Price==L"")
		{
			MessageBox(L"������۸�",L"");
			return;
		}
		else if(m_PersonNum==L"")
		{
			MessageBox(L"��������Ա����",L"");
			return;
		}
	CCommon Common;
	int j = 0;
	int nDay = 0;
	Common.read();
	wsprintf(Common.Flight[Common.FlightCount].FightNum,L"%s",m_FlightNum);
	wsprintf(Common.Flight[Common.FlightCount].Start,L"%s",m_Start);
	wsprintf(Common.Flight[Common.FlightCount].Arrive,L"%s",m_Arrive);
	nDay = m_StartDate.GetDay();
	for(j=0;j<Common.FlightCount;j++)   
		while(wcscmp(Common.Flight[j].FightNum,Common.Flight[Common.FlightCount].FightNum)==0&&
			wcscmp(Common.Flight[j].Start,Common.Flight[Common.FlightCount].Start)==0&&
			wcscmp(Common.Flight[j].Arrive,Common.Flight[Common.FlightCount].Arrive)==0&&
			nDay == Common.Flight[j].nDay)   
		{   
			MessageBox(L"\n�˺����Ѿ�����!!!���ʵ����������...",L"������");
			//Common.Flight[FlightCount-1].FightNum;     //���¶�ȡ����
			return;
		}  

	CDialogEx::OnOK();
}


HBRUSH CADDFLIGHT::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialogEx::OnCtlColor(pDC, pWnd, nCtlColor);

	// TODO:  �ڴ˸��� DC ���κ�����

	// TODO:  ���Ĭ�ϵĲ������軭�ʣ��򷵻���һ������


	UINT id = pWnd->GetDlgCtrlID();
	if(id == IDC_STATIC||id==IDC_BUTTON_ADD)// || id == IDC_CHECK1)
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


BOOL CADDFLIGHT::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	CDialogEx::SetBackgroundImage(IDB_BITMAP_Flight);
	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}
