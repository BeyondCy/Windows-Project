
// PassengerTicketSystemDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "PassengerTicketSystem.h"
#include "PassengerTicketSystemDlg.h"
#include "afxdialogex.h"
#include "Login.h"
#include "Flight.h"
#include "Common.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���


class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// �Ի�������
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ʵ��
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CPassengerTicketSystemDlg �Ի���




CPassengerTicketSystemDlg::CPassengerTicketSystemDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CPassengerTicketSystemDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CPassengerTicketSystemDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CPassengerTicketSystemDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON_COMPANY, &CPassengerTicketSystemDlg::OnBnClickedButtonCompany)
END_MESSAGE_MAP()


// CPassengerTicketSystemDlg ��Ϣ�������

BOOL CPassengerTicketSystemDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();



	// ��������...���˵�����ӵ�ϵͳ�˵��С�

	// IDM_ABOUTBOX ������ϵͳ���Χ�ڡ�
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// ���ô˶Ի����ͼ�ꡣ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��
	
	// TODO: �ڴ���Ӷ���ĳ�ʼ������

//	CreateToolBar();

/*
	CButton* Temp; 
	HBITMAP  hBitmap;
	Temp =(CButton *)GetDlgItem(IDC_BUTTON_COMPANY);
	hBitmap =::LoadBitmap(::AfxGetInstanceHandle(),MAKEINTRESOURCE(IDB_BITMAP_COMPANY));
	Temp->SetBitmap(hBitmap);
*/
	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

void CPassengerTicketSystemDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CPassengerTicketSystemDlg::OnPaint()
{
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

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR CPassengerTicketSystemDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}
/*
void CPassengerTicketSystemDlg::CreateToolBar(void)
{
	if (!m_ToolBar.CreateEx(this, TBSTYLE_FLAT, WS_CHILD | WS_VISIBLE | CBRS_TOP
		| CBRS_GRIPPER | CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC) ||
		!m_ToolBar.LoadToolBar(IDR_TOOLBAR_MAIN))  //����һ��������  ������Դ
	{

		return;     
	}
	m_ToolBar.ModifyStyle(0, TBSTYLE_FLAT);    //Fix for WinXP
	m_ToolBar.LoadTrueColorToolBar
		(
		48,    //������ʹ�����
		IDB_BITMAP_MAIN,
		IDB_BITMAP_MAIN,
		IDB_BITMAP_MAIN
		);  //�����ǵ�λͼ��Դ�����
	RECT rt,rtMain;
	GetWindowRect(&rtMain);   //�õ��������ڵĴ�С
	rt.left=0;
	rt.top=0;
	rt.bottom=80;
	rt.right=rtMain.right-rtMain.left+10;
	m_ToolBar.MoveWindow(&rt,TRUE);

	m_ToolBar.SetButtonText(0,L"���չ�˾");     //��λͼ����������ļ�
	m_ToolBar.SetButtonText(1,L"�����繺Ʊ"); 
	m_ToolBar.SetButtonText(2,L"�û�����"); 
	m_ToolBar.SetButtonText(3,L"����"); 
	//m_ToolBar.SetButtonText(4,"�ļ�����"); 
	//m_ToolBar.SetButtonText(5,"��������"); 
	//m_ToolBar.SetButtonText(6,"��Ƶ����"); 
	//m_ToolBar.SetButtonText(7,"�������"); 
	//m_ToolBar.SetButtonText(8,"ע������"); 
	//m_ToolBar.SetButtonText(9,"��������"); 
	//m_ToolBar.SetButtonText(10,"���ɷ����"); 
	//m_ToolBar.SetButtonText(11,"����"); 
	RepositionBars(AFX_IDW_CONTROLBAR_FIRST,AFX_IDW_CONTROLBAR_LAST,0);  //��ʾ
}
*/




/*
void CPassengerTicketSystemDlg::SearchFromFlightNum()
{
	CHAR* p = "GT00";
	int i = 0;
	read();
	for(i=0;i<FlightCount;i++)
	{
		if(strcmp(Flight[i].FightNum,p)==0)
		{
			MessageBox(L"���Һ�����Ϣ�ɹ�",L"MADK");
			//�Ի�����ʾ������Ϣ
		
		}
	}

}

*/



void CPassengerTicketSystemDlg::OnBnClickedButtonCompany()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CFlight Flight;
	Flight.DoModal();
}
