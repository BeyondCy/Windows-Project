#pragma once


// CFlight �Ի���

class CFlight : public CDialogEx
{
	DECLARE_DYNAMIC(CFlight)

public:
	CFlight(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CFlight();

// �Ի�������
	enum { IDD = IDD_DIALOG_COMPANY };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	CListCtrl m_List;
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedButtonShow();
	afx_msg void OnBnClickedButtonAdd();
	afx_msg void OnBnClickedButtonDelete();
	afx_msg void OnRclickListFlight(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnDelete();
	CString m_Start;
	CString m_Arrive;
	afx_msg void OnBnClickedButtonFind();
	CString m_Flight;
	BOOL bOk_Place;
	BOOL bOk_Flight;
	afx_msg void OnBnClickedButtonFlight();
	afx_msg void OnBnClickedButtonOrder();
};
