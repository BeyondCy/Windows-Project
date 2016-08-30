#pragma once
#include "PassengerTicketSystemDlg.h"

// CLogin �Ի���

class CLogin : public CDialogEx
{
	DECLARE_DYNAMIC(CLogin)

public:
	CLogin(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CLogin();

// �Ի�������
	enum { IDD = IDD_DIALOG_LOGIN };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	PUSER User;
	CString m_Name;
	CString m_Password;
	void ReadCompany();
	void CLogin::SaveCompany();
	void CLogin::ReadTravel();
	void CLogin::SaveTravel();
	void CLogin::ReadPerson();
	void CLogin::SavePerson();

	static int CompanyNum;
	static int UserNum;
	static int TravelNum;

	CHAR*  iTypeUser;
	WCHAR* UserName;

	BOOL m_Company;
	BOOL m_Person;
	BOOL m_Travel;
	afx_msg void OnBnClickedCheckPerson();
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedButtonRegister();
	bool IsTrue;
	afx_msg void OnPaint();
	afx_msg void OnBnClickedCancel();
	afx_msg void OnBnClickedButtonfix();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
};
