#pragma once


#include "MyList.h"
#include "Common.h"

typedef struct _COLUMNSTRUCT
{
	WCHAR*		szTitle;
	UINT				nWidth;
}COLUMNSTRUCT;
// CPETableDlg �Ի���

class CPETableDlg : public CDialog
{
	DECLARE_DYNAMIC(CPETableDlg)

public:
	CPETableDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CPETableDlg();

	ULONG_PTR CPETableDlg:: RVAToOffset(PIMAGE_NT_HEADERS NTHeader, ULONG_PTR ulRVA)   ;
	VOID
		CPETableDlg::ShowPeTable(CHAR* FileData,PETYPE PeType);
	VOID
		CPETableDlg::ShowDataDirTable(CHAR* szFileData,PETYPE PeType);
	VOID
		CPETableDlg::ShowSectionTable(CHAR* szFileData,PETYPE PeType);
	PIMAGE_SECTION_HEADER
		GetSectionHeaderFromRva(ULONG RVA,PIMAGE_NT_HEADERS NtHeader);  //�ж�RVA�����Ǹ��ڱ���;
	PVOID CPETableDlg::GetDirectoryAddr(PUCHAR AddressBase,USHORT DirectoryIndex,
		ULONG_PTR* ulSize,ULONG_PTR* ulDiff,BOOLEAN IsFile);

	VOID
		CPETableDlg::ShowImportTable(CHAR*	szFileData,PETYPE PeType);

	VOID
		CPETableDlg::ShowExportTable(CHAR*	szFileData,PETYPE PeType);


	VOID
		CPETableDlg::ShowRelocTable(CHAR*	szFileData,PETYPE PeType);


// �Ի�������
	enum { IDD = IDD_DIALOG_TABLE };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	CListCtrl m_ListTable;
	CString m_GroupStatic;
	CString m_Table1;
	CString m_Table2;
	CString m_Table3;
	CString m_Table4;
	CString m_EditTable1;
	CString m_EditTable2;
	CString m_EditTable3;
	CString m_EditTable4;
};

DWORD RVATwoOffset(PIMAGE_NT_HEADERS32 NTHeader, ULONG ulRVA)   ;
ULONG_PTR RVATwoOffset64(PIMAGE_NT_HEADERS64 NTHeader, ULONG_PTR ulRVA)   ;