#pragma once
#include "afxwin.h"


// CPerson �Ի���

class CPerson : public CDialogEx
{
	DECLARE_DYNAMIC(CPerson)

public:
	CPerson(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CPerson();

// �Ի�������
	enum { IDD = IDD_DIALOG_Person };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	CComboBox m_FlightNum;
	CComboBox m_Sex;
//	CEdit m_Arrive;
//	CEdit m_ID;
//	CEdit m_Name;
	CString m_Seat;
	CString m_Arrive;
	CString m_ID;
	CString m_Name;
	CString m_Start;
	CString m_Time;
	CString m_WorkPlace;
	CString Temp;
//	CDateTimeCtrl m_Rate;
	COleDateTime m_Rate;
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedButtonBuy();
	BOOL bOk;
	CEdit m_SEAT;
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
};
