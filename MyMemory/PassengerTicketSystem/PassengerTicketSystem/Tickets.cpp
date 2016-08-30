// Tickets.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "PassengerTicketSystem.h"
#include "Tickets.h"
#include "afxdialogex.h"
#include "Common.h"

// CTickets �Ի���
IMPLEMENT_DYNAMIC(CTickets, CDialogEx)

CTickets::CTickets(CWnd* pParent /*=NULL*/)
	: CDialogEx(CTickets::IDD, pParent)
	, m_Read(_T(""))
{

}

CTickets::~CTickets()
{
}

void CTickets::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_READ, m_Read);
}


BEGIN_MESSAGE_MAP(CTickets, CDialogEx)
	ON_WM_CTLCOLOR()
END_MESSAGE_MAP()


// CTickets ��Ϣ�������


BOOL CTickets::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��

	CString m_Temp = L"";
	WCHAR *szBuffer;
	WCHAR Temp[20] = {0};
	CCommon Common;
	Common.readPerson();
	szBuffer = Common.readUser();
	memcpy(Temp,szBuffer,40);
	for(int i=0;i<Common.PersonCount;i++)
	{
		if(wcscmp(Temp,Common.Passenger[i].UserName)==0)
		{
			m_Temp += L"�����ţ�";
			m_Temp +=Common.Passenger[i].OrderNum;
			m_Temp += L"\r\n";

			m_Temp += L"����:  ";
			m_Temp += Common.Passenger[i].PassengerName;
			m_Temp +=L"\r\n";

			m_Temp +=L"�Ա�  ";
			m_Temp +=Common.Passenger[i].Sex;
			m_Temp +=L"\r\n";

			m_Temp +=L"���֤�ţ�  ";
			m_Temp +=Common.Passenger[i].IDCard;
			m_Temp +=L"\r\n";

			m_Temp +=L"�����:  ";
			m_Temp +=Common.Passenger[i].FightNum;
			m_Temp +=L"\r\n";

			m_Temp +=L"Ʊ��:  ";
			m_Temp +=Common.Passenger[i].Price;
			m_Temp +=L"\r\n";

			m_Temp +=L"��λ��:  ";
			m_Temp +=Common.Passenger[i].Seat;
			m_Temp +=L"\r\n";

			m_Temp +=L"�����أ�";
			m_Temp +=Common.Passenger[i].Start;
			m_Temp +=L"        Ŀ�ĵ�:  ";
			m_Temp +=Common.Passenger[i].Arrive;
			m_Temp +=L"\r\n";

			m_Temp +=L"����ʱ�䣺  ";
			m_Temp +=Common.Passenger[i].StartTime;
			m_Temp +=L"    ����ʱ��:  ";
			m_Temp +=Common.Passenger[i].ArriveTime;
			m_Temp +=L"\r\n";

			if(Common.Passenger[i].IsGet==FALSE)
			{
				m_Temp +=L"��Ʊ��ȡ��δ��ȡ";
			}
			else
			{
				m_Temp +=L"��Ʊ��ȡ������ȡ";
			}
			m_Temp +=L"\r\n";
			m_Temp +=L"\r\n";
			m_Temp +=L"\r\n";


		}
		
	}
	//m_Tickets = m_Temp;
	if(m_Temp==L"")
	{
		m_Temp = L"�޶�����Ϣ";
	}
	m_Read = m_Temp;
	UpdateData(FALSE);

	//CDialogEx::SetBackgroundImage(IDB_BITMAP_GRAND);
	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}


HBRUSH CTickets::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialogEx::OnCtlColor(pDC, pWnd, nCtlColor);

	
	return hbr;
}
