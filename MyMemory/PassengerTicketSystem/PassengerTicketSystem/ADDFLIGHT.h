#pragma once
#include "atlcomtime.h"


// CADDFLIGHT �Ի���

class CADDFLIGHT : public CDialogEx
{
	DECLARE_DYNAMIC(CADDFLIGHT)

public:
	CADDFLIGHT(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CADDFLIGHT();

// �Ի�������
	enum { IDD = IDD_DIALOG_ADDFLIGHT };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	CString m_FlightNum;
	CString m_Start;
	CString m_Arrive;
	COleDateTime m_StartDate;
	COleDateTime m_StartTime;
	COleDateTime m_ArriveDate;
	COleDateTime m_ArriveTime;
	CString m_PersonNum;
	CString m_Price;
	afx_msg void OnBnClickedButtonAdd();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	virtual BOOL OnInitDialog();
};
