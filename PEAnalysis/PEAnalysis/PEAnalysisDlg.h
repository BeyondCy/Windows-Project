
// PEAnalysisDlg.h : ͷ�ļ�
//

#pragma once
#include "PeCheckFunc.h"
#include "afxcmn.h"
#include "PEHeaderDlg.h"
#include "PETableDlg.h"
// CPEAnalysisDlg �Ի���
class CPEAnalysisDlg : public CDialogEx
{
// ����
public:
	CPEAnalysisDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_PEANALYSIS_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��

	TCHAR				m_FilePath[1024];
	CString				m_strFilePath;
	CHAR*				m_szFileData;
	ULONG				m_ulLow;
	PETYPE				PeType;


	CPEHeaderDlg		m_PeHeaderDlg;
	CPETableDlg			m_PeTableDlg;

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
	CString m_EditFilePath;
	afx_msg void OnDropFiles(HDROP hDropInfo);
	CString m_EditFileType;
	CTabCtrl m_TabMain;
	afx_msg void OnTcnSelchangeTabMain(NMHDR *pNMHDR, LRESULT *pResult);
};
