
// AddSectionOfPatchDlg.h : ͷ�ļ�
//

#pragma once
#include "resource.h"
#include "afxwin.h"
#include "afxcmn.h"


// CAddSectionOfPatchDlg �Ի���
class CAddSectionOfPatchDlg : public CDialogEx
{
// ����
public:
	CAddSectionOfPatchDlg(CWnd* pParent = NULL);	// ��׼���캯��
	void CAddSectionOfPatchDlg::AddListInfo(CString strData);
// �Ի�������

	enum { IDD = IDD_ADDSECTIONOFPATCH_DIALOG  };

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
	CListCtrl m_List;
};
