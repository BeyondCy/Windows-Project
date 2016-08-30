// CompanyOrder.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "PassengerTicketSystem.h"
#include "CompanyOrder.h"
#include "afxdialogex.h"
#include "Common.h"

// CCompanyOrder �Ի���

IMPLEMENT_DYNAMIC(CCompanyOrder, CDialogEx)

CCompanyOrder::CCompanyOrder(CWnd* pParent /*=NULL*/)
	: CDialogEx(CCompanyOrder::IDD, pParent)
	, m_CompanyOrder(_T(""))
{

}

CCompanyOrder::~CCompanyOrder()
{
}

void CCompanyOrder::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_AAAA, m_CompanyOrder);
}


BEGIN_MESSAGE_MAP(CCompanyOrder, CDialogEx)
END_MESSAGE_MAP()


// CCompanyOrder ��Ϣ�������


BOOL CCompanyOrder::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	CCommon Common;
	Common.readOrder();
	CString m_Temp = L"";
	for(int i =0;i<Common.OrderCount;i++)
	{
		
			m_Temp += L"�����ţ�";
			m_Temp +=Common.Order[i].OrderNum;
			m_Temp += L"     ";



			m_Temp +=L"�����:  ";
			m_Temp +=Common.Order[i].FightNum;
			m_Temp +=L"     ";


			if(Common.Order[i].IsGet==FALSE)
			{
				m_Temp +=L"��Ʊ����� δ��Ʊ";
				m_Temp +=L"\r\n";
			}
			else
			{
				m_Temp +=L"��Ʊ����� ����Ʊ";
				m_Temp +=L"\r\n";
			}
	}

	m_CompanyOrder = m_Temp;
	UpdateData(FALSE);

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��

	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}
