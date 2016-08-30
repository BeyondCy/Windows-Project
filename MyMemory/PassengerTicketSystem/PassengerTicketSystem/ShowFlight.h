#pragma once
#include "afxcmn.h"


// CShowFlight �Ի���

class CShowFlight : public CDialogEx
{
	DECLARE_DYNAMIC(CShowFlight)

public:
	CShowFlight(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CShowFlight();
	void CShowFlight::InitOrderMess();
	void CShowFlight::InitFlightList();

// �Ի�������
	enum { IDD = IDD_DIALOG_Infor };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	CListCtrl m_List;
	afx_msg void OnBnClickedButtonBooking();
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedButtonSurebuy();
	afx_msg void OnBnClickedButtonPrint();
	BOOL bOK;
	afx_msg void OnBnClickedButtonAll();
	CString m_Flight;
	CString m_Start;
	CString m_Arrive;
	BOOL bTrue;
	BOOL bOk_Place;
	BOOL bOk_Flight;
	BOOL IsGetMess;
	afx_msg void OnBnClickedButtonFind();
	afx_msg void OnBnClickedButton3();
	afx_msg void OnBnClickedButtonGet();
	afx_msg void OnHdnItemdblclickListFlight(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnNMDblclkListFlight(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
};
