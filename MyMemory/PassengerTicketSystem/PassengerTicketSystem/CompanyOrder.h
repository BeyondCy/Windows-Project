#pragma once


// CCompanyOrder �Ի���

class CCompanyOrder : public CDialogEx
{
	DECLARE_DYNAMIC(CCompanyOrder)

public:
	CCompanyOrder(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CCompanyOrder();

// �Ի�������
	enum { IDD = IDD_DIALOG_CompanyOrder };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	CString m_CompanyOrder;
	virtual BOOL OnInitDialog();
};
