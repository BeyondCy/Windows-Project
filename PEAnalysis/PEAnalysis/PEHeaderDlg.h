#pragma once



// CPEHeaderDlg �Ի���

class CPEHeaderDlg : public CDialog
{
	DECLARE_DYNAMIC(CPEHeaderDlg)

public:
	CPEHeaderDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CPEHeaderDlg();
	CHAR*	m_FileData;
	VOID CPEHeaderDlg::CheckPEHeader();

// �Ի�������
	enum { IDD = IDD_DIALOG_PEHEADER };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()

	CString m_EditFileSign;

	CString m_EditNumberofSec;
	CString m_EditSizeOfOption;

	CString m_EditOptionMagic;
	CString m_EditOpEntry;
	CString m_EditOpBaseOfData;
	CString m_EditOpBaseOfCode;
	CString m_EditSectionAligment;
	CString m_EditFileAligment;
	CString m_EditOpNumOfDir;
	CString m_EditOpImageBase;

	CString	m_NumberofSection;
public:
	virtual BOOL OnInitDialog();
};
