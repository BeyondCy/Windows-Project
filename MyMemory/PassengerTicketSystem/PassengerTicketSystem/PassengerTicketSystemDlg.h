
// PassengerTicketSystemDlg.h : ͷ�ļ�
//

#pragma once

typedef struct _USER_
{
	char LoginName[20];
	char Password[20];
}USER,*PUSER;

// CPassengerTicketSystemDlg �Ի���
class CPassengerTicketSystemDlg : public CDialogEx
{
// ����
public:
	CPassengerTicketSystemDlg(CWnd* pParent = NULL);	// ��׼���캯��
	void CPassengerTicketSystemDlg::read();
	void CPassengerTicketSystemDlg::save();
	void CPassengerTicketSystemDlg::SearchFromFlightNum();
	CHAR* iTypeUser;
//	CTrueColorToolBar m_ToolBar; 
	
	
//	void CPassengerTicketSystemDlg::CreateToolBar(void);
// �Ի�������
	enum { IDD = IDD_PASSENGERTICKETSYSTEM_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButtonCompany();
};
