#pragma once


// COrder �Ի���

class COrder : public CDialogEx
{
	DECLARE_DYNAMIC(COrder)

public:
	COrder(CWnd* pParent = NULL,WCHAR* Buffer=NULL);   // ��׼���캯��
	virtual ~COrder();

// �Ի�������
	enum { IDD = IDD_DIALOG_ORDER };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	CString m_Order;
	WCHAR* szBuffer;
	CString m_Temp;
	virtual BOOL OnInitDialog();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
};
