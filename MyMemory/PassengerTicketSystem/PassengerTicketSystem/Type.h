#pragma once
#include "afxwin.h"


// CType �Ի���

class CType : public CDialogEx
{
	DECLARE_DYNAMIC(CType)

public:
	CType(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CType();

// �Ի�������
	enum { IDD = IDD_DIALOG_Fix };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	CString m_Type;
	CString m_Name;
	CString m_Old;
	CString m_New;
	BOOL bOk;
	afx_msg void OnBnClickedButtonSure();
	virtual BOOL OnInitDialog();
	CComboBox m_TYPE;
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
};
