// Flight.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "PassengerTicketSystem.h"
#include "Flight.h"
#include "afxdialogex.h"
#include "PassengerTicketSystemDlg.h"
#include "Common.h"
#include "ADDFLIGHT.h"
#include "CompanyOrder.h"
// CFlight �Ի���

IMPLEMENT_DYNAMIC(CFlight, CDialogEx)

CFlight::CFlight(CWnd* pParent /*=NULL*/)
	: CDialogEx(CFlight::IDD, pParent)
	, m_Start(_T(""))
	, m_Arrive(_T(""))
	, m_Flight(_T(""))
{

}

CFlight::~CFlight()
{
}

void CFlight::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST_FLIGHT, m_List);
	DDX_Text(pDX, IDC_EDIT_Start, m_Start);
	DDX_Text(pDX, IDC_EDIT_Arrive, m_Arrive);
	DDX_Text(pDX, IDC_EDIT_Flight, m_Flight);
}


BEGIN_MESSAGE_MAP(CFlight, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON_SHOW, &CFlight::OnBnClickedButtonShow)
	ON_BN_CLICKED(IDC_BUTTON_ADD, &CFlight::OnBnClickedButtonAdd)
	ON_BN_CLICKED(IDC_BUTTON_DELETE, &CFlight::OnBnClickedButtonDelete)
	ON_NOTIFY(NM_RCLICK, IDC_LIST_FLIGHT, &CFlight::OnRclickListFlight)
	ON_COMMAND(ID_DELETE, &CFlight::OnDelete)
	ON_BN_CLICKED(IDC_BUTTON_Find, &CFlight::OnBnClickedButtonFind)
	ON_BN_CLICKED(IDC_BUTTON_Flight, &CFlight::OnBnClickedButtonFlight)
	ON_BN_CLICKED(IDC_BUTTON_ORder, &CFlight::OnBnClickedButtonOrder)
END_MESSAGE_MAP()


// CFlight ��Ϣ�������


BOOL CFlight::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��

	m_List.SetExtendedStyle(LVS_EX_FULLROWSELECT);   //���˾䣬����list����һ��ȫ����
	m_List.InsertColumn(0,L"�����",LVCFMT_LEFT,100);
	m_List.InsertColumn(1,L"������",LVCFMT_LEFT,100);
	m_List.InsertColumn(2,L"�����",LVCFMT_LEFT,100);
	m_List.InsertColumn(3,L"����ʱ��",LVCFMT_LEFT,150);
	m_List.InsertColumn(4,L"����ʱ��",LVCFMT_LEFT,150);
	m_List.InsertColumn(5,L"�۸�",LVCFMT_LEFT,50);
	m_List.InsertColumn(6,L"ʣ��Ʊ��",LVCFMT_LEFT,100);
	m_List.InsertColumn(7,L"��Ա����",LVCFMT_LEFT,100);

	bOk_Flight=FALSE;
	bOk_Place = FALSE;

	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}


void CFlight::OnBnClickedButtonShow()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������

	m_List.DeleteAllItems();
	CCommon Common; 
	Common.read();
	
	for(int i = 0;i<Common.FlightCount;i++)
	{
		CString  FlightNum;
		CString  Start;
		CString  Arrive;
		CString  Time1;
		CString  Time2;
		CString  Price;
		CString  SeatLeft;
		CString  SeatNum;
		FlightNum =Common.Flight[i].FightNum;
		Start = Common.Flight[i].Start;
		Arrive= Common.Flight[i].Arrive;
		Time1 = Common.Flight[i].TimeStart;
		Time2 = Common.Flight[i].TimeArrive;
		Price.Format(L"%d",Common.Flight[i].Price);
		SeatLeft.Format(L"%d",Common.Flight[i].SeatLeft);
		SeatNum.Format(L"%d",Common.Flight[i].SeatNum);
		m_List.InsertItem(i,FlightNum);                                //Ĭ��Ϊ0��  �������в�������ж���������
		m_List.SetItemText(i,1,Start);      
		m_List.SetItemText(i,2,Arrive); 
		m_List.SetItemText(i,3,Time1); 
		m_List.SetItemText(i,4,Time2);
		m_List.SetItemText(i,5,Price);
		m_List.SetItemText(i,6,SeatLeft);
		m_List.SetItemText(i,7,SeatNum);
		m_List.SetItemData(i,Common.Flight[i].nDay);

	}

	
}


void CFlight::OnBnClickedButtonAdd()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������

		
		CADDFLIGHT AddFlight;
		if(AddFlight.DoModal()==IDOK)
		{
			CCommon Common;
			Common.read();
			int j =0;
			Common.FlightCount++;
			wsprintf(Common.Flight[Common.FlightCount-1].FightNum,L"%s",AddFlight.m_FlightNum);
		 
			wsprintf(Common.Flight[Common.FlightCount-1].Start,L"%s",AddFlight.m_Start);
			wsprintf(Common.Flight[Common.FlightCount-1].Arrive,L"%s",AddFlight.m_Arrive);
			int Year = AddFlight.m_StartDate.GetYear();
			int Month = AddFlight.m_StartDate.GetMonth();
			int Day = AddFlight.m_ArriveDate.GetDay();


			int Hour = AddFlight.m_StartTime.GetHour();
			int Min  = AddFlight.m_StartTime.GetMinute();
			int Sec = AddFlight.m_StartTime.GetSecond();

			Common.Flight[Common.FlightCount-1].nYear = Year;
			Common.Flight[Common.FlightCount-1].nMonth = Month;
			Common.Flight[Common.FlightCount-1].nDay = Day;

			CString StartTime;
			StartTime.Format(L"%d-%d-%d %d:%d:%d",Year,Month,Day,Hour,Min,Sec);

			wsprintf(Common.Flight[Common.FlightCount-1].TimeStart,L"%s",StartTime);

			int Year1 = AddFlight.m_ArriveDate.GetYear();
			int Month1 = AddFlight.m_ArriveDate.GetMonth();
			int Day1 = AddFlight.m_ArriveDate.GetDay();

			int Hour1 = AddFlight.m_ArriveTime.GetHour();
			int Min1  = AddFlight.m_ArriveTime.GetMinute();
			int Sec1 = AddFlight.m_ArriveTime.GetSecond();

			CString StartTime1;
			StartTime1.Format(L"%d-%d-%d %d:%d:%d",Year1,Month1,Day1,Hour1,Min1,Sec1);
			wsprintf(Common.Flight[Common.FlightCount-1].TimeArrive,L"%s",StartTime1);


			Common.Flight[Common.FlightCount-1].SeatLeft=Common.StringToInt(AddFlight.m_PersonNum);
			Common.Flight[Common.FlightCount-1].Price = Common.StringToInt(AddFlight.m_Price);
			Common.Flight[Common.FlightCount-1].SeatNum=Common.StringToInt(AddFlight.m_PersonNum);
			
			Common.save();//����

			MessageBox(L"�������ӳɹ�",L"");

		
		}
	
}



void CFlight::OnBnClickedButtonDelete()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	MessageBox(L"���Ҽ�ѡ�񺽰ಢɾ��",L"ɾ������");
}


void CFlight::OnRclickListFlight(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO: �ڴ���ӿؼ�֪ͨ����������

	CMenu	popup;
	popup.LoadMenu(IDR_MENU_DELETE);               //���ز˵���Դ
	CMenu*	pM = popup.GetSubMenu(0);                 //��ò˵�������
	CPoint	p;
	GetCursorPos(&p);
	int	count = pM->GetMenuItemCount();
	if (m_List.GetSelectedCount() == 0)         //���û��ѡ��
	{ 
		for (int i = 0;i<count;i++)
		{
			pM->EnableMenuItem(i, MF_BYPOSITION | MF_DISABLED | MF_GRAYED);          //�˵�ȫ�����
		}

	}
	pM->TrackPopupMenu(TPM_LEFTALIGN, p.x, p.y, this);
	*pResult = 0;
}


void CFlight::OnDelete()
{
	// TODO: �ڴ���������������
	
	CCommon Common;
	Common.read();
	Common.readPerson();
	Common.readOrder();
	CString  FlightNum;
	CString  Start;
	CString  Arrive;
	CString FlightMessage = L"�˺�����ȡ��";
	WCHAR FightNum1[8] = {0};  //�����
	WCHAR Start1[20] = {0};     //��ʼվ
	WCHAR Arrive1[20] = {0};    //�յ�վ
	int Day ;
	int iSelect = m_List.GetSelectionMark( );                   //���ѡ���������
	FlightNum = m_List.GetItemText(iSelect,0);          //ͨ��ѡ���е������������0���IP
	Start = m_List.GetItemText(iSelect,1);
	Arrive =  m_List.GetItemText(iSelect,2);
	Day = m_List.GetItemData(iSelect);
	wsprintf(FightNum1,L"%s",FlightNum);
	wsprintf(Start1,L"%s",Start);
	wsprintf(Arrive1,L"%s",Arrive);

	for(int i =0;i<Common.FlightCount;i++)
	{
		if(wcscmp(Common.Flight[i].FightNum,FightNum1)==0&&wcscmp(Common.Flight[i].Start,Start1)==0&&
			wcscmp(Common.Flight[i].Arrive,Arrive1)==0&&
			Common.Flight[i].nDay==Day)
		{
			Common.Flight[i] = Common.Flight[Common.FlightCount-1];
		}

	
	}

	for(int i =0;i<Common.PersonCount;i++)
	{
		if(wcscmp(Common.Passenger[i].Start,Start1)==0&&
			wcscmp(Common.Passenger[i].Arrive,Arrive1)==0&&Common.Passenger[i].nDay==Day&&
			wcscmp(Common.Passenger[i].FightNum,FightNum1)==0)
		{
			wsprintf(Common.Passenger[i].FightNum,L"%s",FlightMessage);
			wsprintf(Common.Passenger[i].Seat,L"%s",L"");
			wsprintf(Common.Passenger[i].StartTime,L"%s",L"");
			wsprintf(Common.Passenger[i].ArriveTime,L"%s",L"");

			for(int m=0;m<Common.OrderCount;m++)
			{
				if(wcscmp(Common.Order[m].OrderNum,Common.Passenger[i].OrderNum)==0)
				{
					Common.Order[m] = Common.Order[Common.OrderCount-1];
					Common.OrderCount--;
				}
			}

		}


	}
	Common.FlightCount--;
	Common.save();
	Common.savePerson();
	Common.saveOrder();
	m_List.DeleteItem(iSelect);                                 //ɾ������
	MessageBox(L"ɾ���ɹ�",L"�ɹ�");

	   
}


void CFlight::OnBnClickedButtonFind()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	UpdateData(TRUE);
	bOk_Place = FALSE;
	if(m_Start==L"")
	{
		MessageBox(L"�����������",L"");
		return;
	}
	else
	{
		if(m_Arrive==L"")
		{
			MessageBox(L"������Ŀ�ĵ�",L"");
			return;
		}
	}


	WCHAR Start[20] = {0};
	WCHAR Arrive[20] = {0};

	wsprintf(Start,L"%s",m_Start);
	wsprintf(Arrive,L"%s",m_Arrive);


	m_List.DeleteAllItems();
	CCommon Common; 
	Common.read();
	int n =0;
	for(int i = 0;i<Common.FlightCount;i++)
	{
		if(wcscmp(Common.Flight[i].Start,Start)==0&&wcscmp(Common.Flight[i].Arrive,Arrive)==0)
		{
			CString  FlightNum;
			CString  Start;
			CString  Arrive;
			CString  Time1;
			CString  Time2;
			CString  Price;
			CString  SeatLeft;
			CString  SeatNum;
			FlightNum =Common.Flight[i].FightNum;
			Start = Common.Flight[i].Start;
			Arrive= Common.Flight[i].Arrive;
			Time1 = Common.Flight[i].TimeStart;
			Time2 = Common.Flight[i].TimeArrive;
			Price.Format(L"%d",Common.Flight[i].Price);
			SeatLeft.Format(L"%d",Common.Flight[i].SeatLeft);
			SeatNum.Format(L"%d",Common.Flight[i].SeatNum);

			
				m_List.InsertItem(n,FlightNum);                                //Ĭ��Ϊ0��  �������в�������ж���������
				m_List.SetItemText(n,1,Start);      
				m_List.SetItemText(n,2,Arrive); 
				m_List.SetItemText(n,3,Time1); 
				m_List.SetItemText(n,4,Time2);
				m_List.SetItemText(n,5,Price);
				m_List.SetItemText(n,6,SeatLeft);
				m_List.SetItemText(n,7,SeatNum);
				m_List.SetItemData(n,Common.Flight[i].nDay);
			
				n++;
			bOk_Place = TRUE;

		}
		

	}

	if(bOk_Place==FALSE)
	{
		MessageBox(L"δ�ҵ�����������",L"");
		return;
	}

}


void CFlight::OnBnClickedButtonFlight()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	UpdateData(TRUE);
	bOk_Flight = FALSE;
	if(m_Flight==L"")
	{
		MessageBox(L"�����뺽��Ų�ѯ",L"");
		return;
	}


	WCHAR Flight[20] = {0};
	

	wsprintf(Flight,L"%s",m_Flight);
	
	int n = 0;

	m_List.DeleteAllItems();
	CCommon Common; 
	Common.read();

	for(int i = 0;i<Common.FlightCount;i++)
	{
		if(wcscmp(Common.Flight[i].FightNum,Flight)==0)
		{
			CString  FlightNum;
			CString  Start;
			CString  Arrive;
			CString  Time1;
			CString  Time2;
			CString  Price;
			CString  SeatLeft;
			CString  SeatNum;
			FlightNum =Common.Flight[i].FightNum;
			Start = Common.Flight[i].Start;
			Arrive= Common.Flight[i].Arrive;
			Time1 = Common.Flight[i].TimeStart;
			Time2 = Common.Flight[i].TimeArrive;
			Price.Format(L"%d",Common.Flight[i].Price);
			SeatLeft.Format(L"%d",Common.Flight[i].SeatLeft);
			SeatNum.Format(L"%d",Common.Flight[i].SeatNum);

			
				m_List.InsertItem(n,FlightNum);                                //Ĭ��Ϊ0��  �������в�������ж���������
				m_List.SetItemText(n,1,Start);      
				m_List.SetItemText(n,2,Arrive); 
				m_List.SetItemText(n,3,Time1); 
				m_List.SetItemText(n,4,Time2);
				m_List.SetItemText(n,5,Price);
				m_List.SetItemText(n,6,SeatLeft);
				m_List.SetItemText(n,7,SeatNum);
				m_List.SetItemData(n,Common.Flight[i].nDay);
			n++;
			bOk_Flight =TRUE;
		}

	}
	if(bOk_Flight==FALSE)
	{
		MessageBox(L"δ�ҵ��õ��ں���",L"");

		return;
	}
}

void CFlight::OnBnClickedButtonOrder()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CCompanyOrder CompanyOrder;
	CompanyOrder.DoModal();
}
