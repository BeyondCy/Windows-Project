// Order.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "PassengerTicketSystem.h"
#include "Order.h"
#include "afxdialogex.h"
#include "Common.h"


// COrder �Ի���

IMPLEMENT_DYNAMIC(COrder, CDialogEx)

COrder::COrder(CWnd* pParent /*=NULL*/,WCHAR* Buffer)
	: CDialogEx(COrder::IDD, pParent)
	, m_Order(_T(""))
{
	szBuffer = Buffer;
	m_Temp = L"";
}

COrder::~COrder()
{
}

void COrder::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_ORDER, m_Order);
}


BEGIN_MESSAGE_MAP(COrder, CDialogEx)
	ON_WM_TIMER()
	ON_WM_CTLCOLOR()
END_MESSAGE_MAP()


// COrder ��Ϣ�������


BOOL COrder::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	CCommon Common;
	Common.readPerson();
	
	for(int i =0;i<Common.PersonCount;i++)
	{
		if(wcscmp(szBuffer,Common.Passenger[i].OrderNum)==0)
		{
			m_Temp +=L"             ******TICKET*****";
			m_Temp += L"\r\n";

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
		}
	}

	
	SetTimer(0,0,NULL);


	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}


void COrder::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ

	m_Order = m_Temp;
	UpdateData(FALSE);
	KillTimer(0);

	CDialogEx::OnTimer(nIDEvent);
}


HBRUSH COrder::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialogEx::OnCtlColor(pDC, pWnd, nCtlColor);

	// TODO:  �ڴ˸��� DC ���κ�����

	// TODO:  ���Ĭ�ϵĲ������軭�ʣ��򷵻���һ������



	UINT id = pWnd->GetDlgCtrlID();
	if(id == IDC_EDIT_ORDER)// || id == IDC_CHECK1)
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
