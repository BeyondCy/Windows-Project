// Welcome.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "PassengerTicketSystem.h"
#include "Welcome.h"
#include "afxdialogex.h"
#include "ShowFlight.h"
#include "Return.h"
#include "Tickets.h"


// CWelcome �Ի���

IMPLEMENT_DYNAMIC(CWelcome, CDialogEx)

CWelcome::CWelcome(CWnd* pParent /*=NULL*/)
	: CDialogEx(CWelcome::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	m_Welcome = _T("");
}

CWelcome::~CWelcome()
{
}

void CWelcome::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_STATIC_WELCOME, m_Welcome);
	DDX_Control(pDX, IDC_STATIC_WELCOME, m_CWelcome);
}


BEGIN_MESSAGE_MAP(CWelcome, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON_Purse, &CWelcome::OnBnClickedButtonPurse)
	ON_BN_CLICKED(IDC_BUTTON_Refunf, &CWelcome::OnBnClickedButtonRefunf)
	ON_BN_CLICKED(IDC_BUTTON_MyMes, &CWelcome::OnBnClickedButtonMymes)
	ON_WM_PAINT()
	ON_WM_CTLCOLOR()
END_MESSAGE_MAP()


// CWelcome ��Ϣ�������


BOOL CWelcome::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	CString  Welcome;
	 Welcome    +=L"     ��ӭ����������Ԥ��ϵͳ��\r\n";
	 Welcome	+=L"       ����һ���߳�Ϊ������\r\n\r\n\r\n";
	Welcome  +=L"��ϵͳ�����棬���ĳɣ�ʩ������������Ȩ����Υ�߱ؾ�\r\n";
	m_Welcome = Welcome;
	UpdateData(FALSE);
	

	CDialogEx::SetBackgroundImage(IDB_BITMAP_Welcome);
	//m_CWelcome.ShowWindow(FALSE);

	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}


void CWelcome::OnBnClickedButtonPurse()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CShowFlight showflight;
	showflight.DoModal();
}


void CWelcome::OnBnClickedButtonRefunf()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CReturn RETURN;
	RETURN.DoModal();

}


void CWelcome::OnBnClickedButtonMymes()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CTickets Ticket;
	Ticket.DoModal();
}


void CWelcome::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	// TODO: �ڴ˴������Ϣ����������
	// ��Ϊ��ͼ��Ϣ���� CDialogEx::OnPaint()
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}



}


HBRUSH CWelcome::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialogEx::OnCtlColor(pDC, pWnd, nCtlColor);

	// TODO:  �ڴ˸��� DC ���κ�����

	// TODO:  ���Ĭ�ϵĲ������軭�ʣ��򷵻���һ������


	

	UINT id = pWnd->GetDlgCtrlID();
	if(id == IDC_STATIC_WELCOME||id==IDC_BUTTON_MyMes||id==IDC_BUTTON_Purse||id==IDC_BUTTON_Refunf)// || id == IDC_CHECK1)
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
