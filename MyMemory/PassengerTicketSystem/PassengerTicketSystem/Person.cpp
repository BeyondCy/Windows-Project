// Person.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "PassengerTicketSystem.h"
#include "Person.h"
#include "afxdialogex.h"
#include "Common.h"

// CPerson �Ի���

IMPLEMENT_DYNAMIC(CPerson, CDialogEx)

CPerson::CPerson(CWnd* pParent /*=NULL*/)
	: CDialogEx(CPerson::IDD, pParent)
{

	m_Seat = _T("");
	m_Arrive = _T("");
	m_ID = _T("");
	m_Name = _T("");
	m_Start = _T("");
	m_Time = _T("");
	m_WorkPlace = _T("");
	m_Rate = COleDateTime::GetCurrentTime();
}

CPerson::~CPerson()
{
}

void CPerson::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO_FlightNum, m_FlightNum);
	DDX_Control(pDX, IDC_COMBO_Sex, m_Sex);
	//  DDX_Control(pDX, IDC_EDIT_Arrive, m_Arrive);
	//  DDX_Control(pDX, IDC_EDIT_ID, m_ID);
	//  DDX_Control(pDX, IDC_EDIT_NAME, m_Name);
	DDX_Text(pDX, IDC_EDIT_Seat, m_Seat);
	DDX_Text(pDX, IDC_EDIT_Arrive, m_Arrive);
	DDX_Text(pDX, IDC_EDIT_ID, m_ID);
	DDX_Text(pDX, IDC_EDIT_NAME, m_Name);
	DDX_Text(pDX, IDC_EDIT_Start, m_Start);
	//DDX_Text(pDX, IDC_EDIT_Time, m_Time);
	DDX_Text(pDX, IDC_EDIT_WorkPlace, m_WorkPlace);
	//  DDX_Control(pDX, IDC_DATETIMEPICKER_Rate, m_Rate);
	DDX_DateTimeCtrl(pDX, IDC_DATETIMEPICKER_Rate, m_Rate);
	DDX_Control(pDX, IDC_EDIT_Seat, m_SEAT);
}


BEGIN_MESSAGE_MAP(CPerson, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON_BUY, &CPerson::OnBnClickedButtonBuy)
	ON_WM_CTLCOLOR()
END_MESSAGE_MAP()


// CPerson ��Ϣ�������


BOOL CPerson::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	m_Sex.AddString(L"��");
	m_Sex.AddString(L"Ů");
	m_Sex.SetWindowText(L"��");

	m_FlightNum.AddString(L"MF8484"); //�人-����
	m_FlightNum.AddString(L"CA8211"); //�人-����
	m_FlightNum.AddString(L"MF8235");
	m_FlightNum.SetWindowText(L"MF8484");//����-����

	m_FlightNum.ShowWindow(FALSE);
	m_SEAT.ShowWindow(FALSE);

	bOk = FALSE;

	//CDialogEx::SetBackgroundImage(IDB_BITMAP_USER1);
	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}


void CPerson::OnBnClickedButtonBuy()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	UpdateData(TRUE);
	bOk = FALSE;
	if(m_Name==L"")
	{
		MessageBox(L"����������",L"������");
		return;
	}
	if(m_WorkPlace==L"")
	{

		MessageBox(L"�����빤����λ",L"������");
		return;
	}

	if(m_ID.GetLength()!=18)
	{
		MessageBox(L"��������ȷ�����֤����",L"������");
		return ;
	}
	
	if(m_Start==L"")
	{
		MessageBox(L"�����������",L"������");
		return;
	}
	if(m_Arrive==L"")
	{

		MessageBox(L"������Ŀ�ĵ�",L"������");
		return;
	}
	m_Sex.GetWindowText(Temp);
	
	
	CCommon Common;
	int j = 0;
	int nDay = 0;
	Common.read();
	Common.readPerson();
	wsprintf(Common.Flight[Common.FlightCount].Start,L"%s",m_Start);
	wsprintf(Common.Flight[Common.FlightCount].Arrive,L"%s",m_Arrive);
	wsprintf(Common.Passenger[Common.PersonCount].Start,L"%s",m_Start);
	wsprintf(Common.Passenger[Common.PersonCount].Arrive,L"%s",m_Arrive);
	wsprintf(Common.Passenger[Common.PersonCount].PassengerName,L"%s",m_Name);
	nDay = m_Rate.GetDay();
	for(j=0;j<Common.PersonCount;j++)
	{
		if(wcscmp(Common.Passenger[j].Start,Common.Passenger[Common.PersonCount].Start)==0&&
			wcscmp(Common.Passenger[j].Arrive,Common.Passenger[Common.PersonCount].Arrive)==0&&
			nDay == Common.Passenger[j].nDay&&wcscmp(Common.Passenger[j].PassengerName,Common.Passenger[Common.PersonCount].PassengerName)==0)
		{
			MessageBox(L"�Բ���һ������ÿ���˲���ͬʱ������Ʊ",L"");
			return;
		}
	}
	for(j=0;j<Common.FlightCount;j++)   
		if(wcscmp(Common.Flight[j].Start,Common.Flight[Common.FlightCount].Start)==0&&
			wcscmp(Common.Flight[j].Arrive,Common.Flight[Common.FlightCount].Arrive)==0&&
			nDay == Common.Flight[j].nDay)   
		{   
			//MessageBox(L"\n�˺����Ѿ�����!!!���ʵ����������...",L"������");
			//Common.Flight[FlightCount-1].FightNum;     //���¶�ȡ����
			bOk = TRUE;
		}  


	
	if(bOk==FALSE)
	{
		MessageBox(L"û����Ӧʱ��ĺ��࣬���ѯ���ڶ�Ʊ",L"");
		return;
	}
	
	CDialogEx::OnOK();
	
	
}


HBRUSH CPerson::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialogEx::OnCtlColor(pDC, pWnd, nCtlColor);

	// TODO:  �ڴ˸��� DC ���κ�����

	// TODO:  ���Ĭ�ϵĲ������軭�ʣ��򷵻���һ������


	UINT id = pWnd->GetDlgCtrlID();
	if(id == IDC_STATIC||id==IDC_BUTTON_BUY)// || id == IDC_CHECK1)
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
