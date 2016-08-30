// ShowFlight.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "PassengerTicketSystem.h"
#include "ShowFlight.h"
#include "afxdialogex.h"
#include "Person.h"
#include "Common.h"
#include "Tickets.h"
#include "Order.h"

// CShowFlight �Ի���

IMPLEMENT_DYNAMIC(CShowFlight, CDialogEx)

CShowFlight::CShowFlight(CWnd* pParent /*=NULL*/)
	: CDialogEx(CShowFlight::IDD, pParent)
	, m_Flight(_T(""))
	, m_Start(_T(""))
	, m_Arrive(_T(""))
{

}

CShowFlight::~CShowFlight()
{
}

void CShowFlight::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST_FLIGHT, m_List);
	DDX_Text(pDX, IDC_EDIT_Flight, m_Flight);
	DDX_Text(pDX, IDC_EDIT_Start, m_Start);
	DDX_Text(pDX, IDC_EDIT_Arrive, m_Arrive);
}


BEGIN_MESSAGE_MAP(CShowFlight, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON_BOOKING, &CShowFlight::OnBnClickedButtonBooking)
	ON_BN_CLICKED(IDC_BUTTON_SUREBUY, &CShowFlight::OnBnClickedButtonSurebuy)
	ON_BN_CLICKED(IDC_BUTTON_PRINT, &CShowFlight::OnBnClickedButtonPrint)
	ON_BN_CLICKED(IDC_BUTTON_ALL, &CShowFlight::OnBnClickedButtonAll)
	ON_BN_CLICKED(IDC_BUTTON_Find, &CShowFlight::OnBnClickedButtonFind)
	ON_BN_CLICKED(IDC_BUTTON3, &CShowFlight::OnBnClickedButton3)
	ON_BN_CLICKED(IDC_BUTTON_GET, &CShowFlight::OnBnClickedButtonGet)
	ON_NOTIFY(HDN_ITEMDBLCLICK, 0, &CShowFlight::OnHdnItemdblclickListFlight)
	ON_NOTIFY(NM_DBLCLK, IDC_LIST_FLIGHT, &CShowFlight::OnNMDblclkListFlight)
	ON_WM_CTLCOLOR()
END_MESSAGE_MAP()


// CShowFlight ��Ϣ�������


void CShowFlight::OnBnClickedButtonBooking()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	m_List.DeleteColumn(7);
	m_List.InsertColumn(7,L"��Ա����",LVCFMT_LEFT,100);
	CPerson Person;
	CCommon Common;
	WCHAR Start[20] = {0};
	WCHAR Arrive[20] = {0};
	int nYear;
	int nMonth;
	int nDay;
	int i = 0;
	int j = 0;
	int n = 0;
	if(Person.DoModal()==IDOK)
	{
		MessageBox(L"Ԥ���ɹ�",L"");
		nYear = Person.m_Rate.GetYear();
		nMonth = Person.m_Rate.GetMonth();
		nDay = Person.m_Rate.GetDay();
	    //Common.savePerson();
		//Common.saveOrder();
		Common.readPerson();
		Common.read();
		Common.readOrder();
		WCHAR* Name;
		Name=Common.readUser();
		memcpy(Common.Passenger[Common.PersonCount].UserName,Name,40);
		wsprintf(Start,L"%s",Person.m_Start);
		wsprintf(Arrive,L"%s",Person.m_Arrive);
		
		
		for(i=0;i<Common.FlightCount;i++)
		{
			if(wcscmp(Common.Flight[i].Start,Start)==0&&wcscmp(Common.Flight[i].Arrive,Arrive)==0&&
				Common.Flight[i].nYear==nYear&&Common.Flight[i].nDay==nDay&&
				Common.Flight[i].nMonth==nMonth)
			{
				j = i;
				m_List.DeleteAllItems();
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
				bTrue = TRUE;
			}

		}
		
		if(bTrue==FALSE)
		{
			MessageBox(L"�޴˺��࣬������������Ϣ",L"������");
			return;
		}
		//CString Seat;
		//CString Price;
		CString mz = Common.Flight[j].FightNum ;
		CString MB = mz+Person.m_ID;
		wsprintf(Common.Passenger[Common.PersonCount].OrderNum,L"%s",MB);

		memcpy(Common.Order[Common.OrderCount].OrderNum,Common.Passenger[Common.PersonCount].OrderNum,56);//������Ϣ

		memcpy(Common.Passenger[Common.PersonCount].FightNum,Common.Flight[j].FightNum,16);

		memcpy(Common.Order[Common.OrderCount].FightNum,Common.Passenger[Common.PersonCount].FightNum,16);

		memcpy(Common.Passenger[Common.PersonCount].Arrive,Common.Flight[j].Arrive,40);
		memcpy(Common.Passenger[Common.PersonCount].Start,Common.Flight[j].Start,40);
		memcpy(Common.Passenger[Common.PersonCount].StartTime,Common.Flight[j].TimeStart,40);
		memcpy(Common.Passenger[Common.PersonCount].ArriveTime,Common.Flight[j].TimeArrive,40);
		wsprintf(Common.Passenger[Common.PersonCount].PassengerName,L"%s",Person.m_Name);
		wsprintf(Common.Passenger[Common.PersonCount].IDCard,L"%s",Person.m_ID);

		Common.Order[Common.OrderCount].IsGet = FALSE;
		Common.Passenger[Common.PersonCount].IsGet = FALSE;
		
	

		
		//Seat.Format(L"%d",Common.Flight[j].SeatLeft);
		wsprintf(Common.Passenger[Common.PersonCount].Seat,L"%d",Common.Flight[j].SeatLeft);
	//	Price.Format(L"%d",Common.Flight[j].Price);
		wsprintf(Common.Passenger[Common.PersonCount].Price,L"%d",Common.Flight[j].Price);

		

		wsprintf(Common.Passenger[Common.PersonCount].WorkPlace,L"%s",Person.m_WorkPlace);
		wsprintf(Common.Passenger[Common.PersonCount].Sex,L"%s",Person.Temp);

		Common.Passenger[Common.PersonCount].nDay = Common.Flight[j].nDay;

		Common.Flight[j].SeatLeft--;
		if(Common.Flight[j].SeatLeft<0)
		{
			MessageBox(L"�˺�������",L"");
			return;
		}
		Common.OrderCount++;
		Common.PersonCount++;

		Common.save();
		Common.savePerson();
		Common.saveOrder();
		bOK = TRUE;
	}
}


BOOL CShowFlight::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	bOK = FALSE;
	bTrue = FALSE;

	bOk_Flight =FALSE;
	bOk_Place =FALSE;

	IsGetMess = FALSE;

	m_List.SetExtendedStyle(LVS_EX_FULLROWSELECT);   //���˾䣬����list����һ��ȫ����
	m_List.InsertColumn(0,L"�����",LVCFMT_LEFT,100);
	m_List.InsertColumn(1,L"������",LVCFMT_LEFT,100);
	m_List.InsertColumn(2,L"�����",LVCFMT_LEFT,100);
	m_List.InsertColumn(3,L"����ʱ��",LVCFMT_LEFT,150);
	m_List.InsertColumn(4,L"����ʱ��",LVCFMT_LEFT,150);
	m_List.InsertColumn(5,L"�۸�",LVCFMT_LEFT,50);
	m_List.InsertColumn(6,L"ʣ��Ʊ��",LVCFMT_LEFT,100);
	m_List.InsertColumn(7,L"��Ա����",LVCFMT_LEFT,100);

	
	CDialogEx::SetBackgroundImage(IDB_BITMAP_Infor);
	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}


void CShowFlight::OnBnClickedButtonSurebuy()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	if(bOK==TRUE)
	{
		MessageBox(L"��Ʊ�ɹ�",L"��ϲ��");
	}
	else
	{
		MessageBox(L"���������빺Ʊ��Ϣ",L"������");
	}
	
}


void CShowFlight::OnBnClickedButtonPrint()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CTickets Tickets;
	Tickets.DoModal();

}


void CShowFlight::OnBnClickedButtonAll()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	m_List.DeleteColumn(7);
	m_List.InsertColumn(7,L"��Ա����",LVCFMT_LEFT,100);
	m_List.DeleteAllItems();
	CCommon Common;
	Common.read();
	for(int i=0;i<Common.FlightCount;i++)
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


void CShowFlight::OnBnClickedButtonFind()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	m_List.DeleteColumn(7);
	m_List.InsertColumn(7,L"��Ա����",LVCFMT_LEFT,100);
	UpdateData(TRUE);
	bOk_Place =FALSE;
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
	int m = 1;
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

			for(int n=0;n<m;n++)
			{
				m_List.InsertItem(n,FlightNum);                                //Ĭ��Ϊ0��  �������в�������ж���������
				m_List.SetItemText(n,1,Start);      
				m_List.SetItemText(n,2,Arrive); 
				m_List.SetItemText(n,3,Time1); 
				m_List.SetItemText(n,4,Time2);
				m_List.SetItemText(n,5,Price);
				m_List.SetItemText(n,6,SeatLeft);
				m_List.SetItemText(n,7,SeatNum);
				m_List.SetItemData(n,Common.Flight[i].nDay);
			}
			bOk_Place =TRUE;
		}


	}
	if(bOk_Place==FALSE)
	{
		MessageBox(L"δ�ҵ�����������",L"");
		return;
	}
}


void CShowFlight::OnBnClickedButton3()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	m_List.DeleteColumn(7);
	m_List.InsertColumn(7,L"��Ա����",LVCFMT_LEFT,100);
	UpdateData(TRUE);
	bOk_Flight =FALSE;
	if(m_Flight==L"")
	{
		MessageBox(L"�����뺽��Ų�ѯ",L"");
		return;
	}


	WCHAR Flight[20] = {0};


	wsprintf(Flight,L"%s",m_Flight);

	int m = 1;

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

			for(int n=0;n<m;n++)
			{
				m_List.InsertItem(n,FlightNum);                                //Ĭ��Ϊ0��  �������в�������ж���������
				m_List.SetItemText(n,1,Start);      
				m_List.SetItemText(n,2,Arrive); 
				m_List.SetItemText(n,3,Time1); 
				m_List.SetItemText(n,4,Time2);
				m_List.SetItemText(n,5,Price);
				m_List.SetItemText(n,6,SeatLeft);
				m_List.SetItemText(n,7,SeatNum);
				m_List.SetItemData(n,Common.Flight[i].nDay);
			}
			bOk_Flight =TRUE;
	
		}

	}
	if(bOk_Flight==FALSE)
	{
		MessageBox(L"δ�ҵ��õ��ں���",L"");
		return;
	}
}


void CShowFlight::OnBnClickedButtonGet()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	m_List.DeleteColumn(7);
	m_List.InsertColumn(7,L"�Ƿ�ȡƱ",LVCFMT_LEFT,100);
	m_List.DeleteAllItems();
	WCHAR *szBuffer;
	WCHAR Temp[20] = {0};
	CCommon Common;
	Common.readPerson();
	szBuffer = Common.readUser();
	memcpy(Temp,szBuffer,40);
	int m = 1;
	for(int i=0;i<Common.PersonCount;i++)
	{
		if(wcscmp(Temp,Common.Passenger[i].UserName)==0)
		{
			CString  FlightNum;
			CString  Start;
			CString  Arrive;
			CString  Time1;
			CString  Time2;
			CString  Price;
			CString  SeatLeft;
			CString  IsGet;
			FlightNum =Common.Passenger[i].FightNum;
			Start = Common.Passenger[i].Start;
			Arrive= Common.Passenger[i].Arrive;
			Time1 = Common.Passenger[i].StartTime;
			Time2 = Common.Passenger[i].ArriveTime;
			Price = Common.Passenger[i].Price;
			SeatLeft = Common.Passenger[i].Seat;
			
			if(Common.Passenger[i].IsGet==FALSE)
			{
				IsGet = L"δ��ȡ";
			}
			else
			{
				IsGet = L"����ȡ";
			}
			for(int n=0;n<m;n++)
			{
				m_List.InsertItem(n,FlightNum);                                //Ĭ��Ϊ0��  �������в�������ж���������
				m_List.SetItemText(n,1,Start);      
				m_List.SetItemText(n,2,Arrive); 
				m_List.SetItemText(n,3,Time1); 
				m_List.SetItemText(n,4,Time2);
				m_List.SetItemText(n,5,Price);
				m_List.SetItemText(n,6,SeatLeft);
				m_List.SetItemText(n,7,IsGet);
				m_List.SetItemData(n,Common.Passenger[i].nDay);
			}
			for(int j=0;j<Common.PersonCount;j++)
			{
				if(Common.Passenger[j].IsGet==FALSE)
				{
					IsGetMess = TRUE;
				}
			}
		}
	
	}
	if(IsGetMess==TRUE)
	{
		MessageBox(L"�������ѡ��˫����ȡ��Ʊ",L"");
	}
	else
	{
		MessageBox(L"���޿���ȡ��Ʊ",L"");
	}
	
}


void CShowFlight::OnHdnItemdblclickListFlight(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMHEADER phdr = reinterpret_cast<LPNMHEADER>(pNMHDR);
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	
	*pResult = 0;
}


void CShowFlight::OnNMDblclkListFlight(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CCommon Common;
	Common.readPerson();
	Common.readOrder();
	CString  FlightNum;
	CString  Start;
	CString  Arrive;
	WCHAR FightNum1[8] = {0};  //�����
	WCHAR Start1[20] = {0};     //��ʼվ
	WCHAR Arrive1[20] = {0};    //�յ�վ
	int Day ;
	int n;
	int iSelect = m_List.GetSelectionMark( );                   //���ѡ���������
	FlightNum = m_List.GetItemText(iSelect,0);          //ͨ��ѡ���е������������0���IP
	Start = m_List.GetItemText(iSelect,1);
	Arrive =  m_List.GetItemText(iSelect,2);
	Day = m_List.GetItemData(iSelect);
	wsprintf(FightNum1,L"%s",FlightNum);
	wsprintf(Start1,L"%s",Start);
	wsprintf(Arrive1,L"%s",Arrive);


	for(int i =0;i<Common.PersonCount;i++)
	{
		if(wcscmp(Common.Passenger[i].Start,Start1)==0&&
			wcscmp(Common.Passenger[i].Arrive,Arrive1)==0&&Common.Passenger[i].nDay==Day&&
			wcscmp(Common.Passenger[i].FightNum,FightNum1)==0)
		{
			Common.Passenger[i].IsGet=TRUE;

			for(int m=0;m<Common.OrderCount;m++)
			{
				if(wcscmp(Common.Order[m].OrderNum,Common.Passenger[i].OrderNum)==0)
				{
					Common.Order[m].IsGet = TRUE;
					n=m;
				}
			}
		}


	}
	
	Common.saveOrder();
	Common.savePerson();

	COrder Order(NULL,Common.Order[n].OrderNum);
	Order.DoModal();

	MessageBox(L"ȡƱ�ɹ�",L"�ɹ�");



	
	*pResult = 0;
}


HBRUSH CShowFlight::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialogEx::OnCtlColor(pDC, pWnd, nCtlColor);

	// TODO:  �ڴ˸��� DC ���κ�����

	// TODO:  ���Ĭ�ϵĲ������軭�ʣ��򷵻���һ������

	UINT id = pWnd->GetDlgCtrlID();
	if(id == IDC_STATIC||id==IDC_LIST_FLIGHT||id==IDC_BUTTON_Find||id==IDC_BUTTON3)// || id == IDC_CHECK1)
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
