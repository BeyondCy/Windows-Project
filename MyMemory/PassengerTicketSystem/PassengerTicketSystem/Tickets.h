#pragma once


// CTickets �Ի���

class CTickets : public CDialogEx
{
	DECLARE_DYNAMIC(CTickets)

public:
	CTickets(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CTickets();

// �Ի�������
	enum { IDD = IDD_DIALOG_TICKETS };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	CString m_Read;
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
};
