// Login.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "PassengerTicketSystem.h"
#include "Login.h"
#include "afxdialogex.h"
#include "Register.h"
#include "Common.h"
#include "Type.h"

int CLogin::CompanyNum = 0;
int CLogin:: UserNum = 0;
int CLogin::TravelNum = 0;

// CLogin �Ի���

IMPLEMENT_DYNAMIC(CLogin, CDialogEx)

CLogin::CLogin(CWnd* pParent /*=NULL*/)
	: CDialogEx(CLogin::IDD, pParent)
{

	m_Name = _T("");
	m_Password = _T("");
	User = new USER[MAXNUM];
	IsTrue = false;
}

CLogin::~CLogin()
{
	delete[] User;
}

void CLogin::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	//  DDX_Control(pDX, IDC_EDIT_NAME, m_Name);
	//  DDX_Control(pDX, IDC_EDIT_PASSWORD, m_Password);
	DDX_Text(pDX, IDC_EDIT_NAME, m_Name);
	DDX_Text(pDX, IDC_EDIT_PASSWORD, m_Password);

	DDX_Check(pDX, IDC_CHECK_Company, m_Company);
	DDX_Check(pDX, IDC_CHECK_Person, m_Person);
	DDX_Check(pDX, IDC_CHECK_Travel, m_Travel);
}


BEGIN_MESSAGE_MAP(CLogin, CDialogEx)
	ON_BN_CLICKED(IDC_CHECK_Person, &CLogin::OnBnClickedCheckPerson)
	ON_BN_CLICKED(IDOK, &CLogin::OnBnClickedOk)
	ON_BN_CLICKED(IDC_BUTTON_Register, &CLogin::OnBnClickedButtonRegister)
	ON_WM_PAINT()
	ON_BN_CLICKED(IDCANCEL, &CLogin::OnBnClickedCancel)
	ON_BN_CLICKED(IDC_BUTTONFix, &CLogin::OnBnClickedButtonfix)
	ON_WM_CTLCOLOR()
END_MESSAGE_MAP()


// CLogin ��Ϣ�������


void CLogin::OnBnClickedCheckPerson()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
}


BOOL CLogin::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��

//	CDialogEx::SetBackgroundImage(IDB_BITMAP_Enter);

	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}


void CLogin::OnBnClickedOk()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	UpdateData(true);
	int i =0;
	char Name[20]={0};
	char PassWord[20]={0};
	wcstombs(Name,m_Name,20);
	wcstombs(PassWord,m_Password,20);
	if(m_Name==L"")
	{
		MessageBox(L"�������û���",L"�û���Ϊ��");
		return ;
	}
	if(m_Password==L"")
	{
		MessageBox(L"����������",L"����Ϊ��");
		return ;
	}
	
	if(m_Company==FALSE&&m_Travel==FALSE&&m_Person==FALSE)
	{
		MessageBox(L"��ѡ���û���½��ʽ",L"������");
		return ;
	}
	if((m_Company==TRUE&&m_Person==TRUE)||(m_Company==TRUE&&m_Travel==TRUE)||(m_Person==TRUE&&m_Travel==TRUE)
		||(m_Company==TRUE&&m_Person==TRUE&&m_Travel==TRUE))
	{
		MessageBox(L"����ͬʱѡ������û����͵�½",L"������");
		return ;
	}
	if(m_Company==TRUE)
	{
		ReadCompany();
		for(i=0;i<CompanyNum;i++)
		{
			if(strcmp(User[i].LoginName,Name)==0&&strcmp(User[i].Password,PassWord)==0)
			{
				iTypeUser = "���չ�˾";
				UserName = (WCHAR*)Name;
				CDialogEx::OnOK();
				IsTrue = true;
			}
		}
		if(IsTrue==false)
		{
			MessageBox(L"�û������������",L"������");
		}
		
		return ;

	}

	if(m_Travel==TRUE)
	{
		ReadTravel();
		for(i=0;i<TravelNum;i++)
		{
			if(strcmp(User[i].LoginName,Name)==0&&strcmp(User[i].Password,PassWord)==0)
			{
				iTypeUser = "������";
				UserName = (WCHAR*)Name;
				CDialogEx::OnOK();
				IsTrue = true;
			}
		}
		if(IsTrue==false)
		{
			MessageBox(L"�û������������",L"������");
		}

		return ;

	}

	if(m_Person==TRUE)
	{
		ReadPerson();
		for(i=0;i<UserNum;i++)
		{
			if(strcmp(User[i].LoginName,Name)==0&&strcmp(User[i].Password,PassWord)==0)
			{
				iTypeUser = "����";
				UserName = (WCHAR*)Name;
				CDialogEx::OnOK();
				IsTrue = true;
			}
		}
		if(IsTrue==false)
		{
			MessageBox(L"�û������������",L"������");
		}

		return ;

	}
	

}

void CLogin::OnBnClickedButtonRegister()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CRegister Register;
	Register.DoModal();
}






void CLogin::SaveCompany()//����ģ�����   
{   int i = 0;
FILE *fp,*fp1;//�����ļ�ָ��   
if((fp=fopen("���չ�˾�û�.doc","wb"))==NULL)//���ļ����ж��Ƿ����     
{   
	MessageBox(L"�����ļ�ʧ��!\n\n",L"������");//��ӡ������ʾ   
	getchar();   
	return;   
}   
if((fp1=fopen("���չ�˾�û���.doc","wb"))==NULL)//���ļ����ж��Ƿ����     
{   
	MessageBox(L"�����ļ�ʧ��!\n\n",L"������");//��ӡ������ʾ  
	getchar();   
	return;   
}   
for(i=0;i<CompanyNum;i++)   
	if(fwrite(&User[i],sizeof(_USER_),1,fp)==0)//���ļ�д�����ݣ����ж��Ƿ����   
		MessageBox(L"���ļ���������ʧ��!\n\n",L"������");   
fprintf(fp1,"%d",CompanyNum);   
fclose(fp);//�ر��ļ�   
fclose(fp1);//�ر��ļ�   
}   
/*
void CLogin::InputFlight()
{
	int j =0;
	CompanyNum++;
	strcpy(Flight[CompanyNum-1].FightNum,"FASS");
	for(j=0;j<CompanyNum-1;j++)   
		while(Flight[j].FightNum==Flight[CompanyNum-1].FightNum)   
		{   
			MessageBox(L"\n�˺����Ѿ�����!!!���ʵ����������...",L"������");
			Flight[FlightCount-1].FightNum;     //���¶�ȡ����
		}   
		strcpy(Flight[CompanyNum-1].Start,"����");
		strcpy(Flight[CompanyNum-1].Arrive,"����");

		strcpy(Flight[CompanyNum-1].Time,"5015.5.21");
		Flight[CompanyNum-1].SeatNum=200;

		SaveCompany();//����

}*/



void CLogin::ReadCompany()//���ļ���ȡ��Ϣģ��   
{   

	int i =0;
	FILE *fp,*fp1;//�����ļ�ָ��   
	if((fp=fopen("���չ�˾�û�.doc","rb"))==NULL)//���ļ������ж��Ƿ����   
	{   
	//	MessageBox(L"û�д��û��ļ�,��ע��",L"������");//��ӡ������ʾ   
	//	getchar();   
		return ;
	}   
	if((fp1=fopen("���չ�˾�û���.doc","rb"))==NULL)//���ļ����ж��Ƿ����     
	{   
	//	MessageBox(L"û�д��û��ļ�,��ע��!\n\n",L"������");//��ӡ������ʾ   
	//	getchar();   
		return;   
	}   
	fscanf(fp1,"%d",&CompanyNum);   
	fclose(fp1);//�ر��ļ�   

	for(i=0;i<CompanyNum;i++)    
	{   
		fread(&User[i],sizeof(_USER_),1,fp);//���ļ��ж�ȡ��Ϣ   

	}   
	fclose(fp);//�ر��ļ�   
}   




void CLogin::ReadTravel()//���ļ���ȡ��Ϣģ��   
{   

	int i =0;
	FILE *fp,*fp1;//�����ļ�ָ��   
	if((fp=fopen("�������û�.doc","rb"))==NULL)//���ļ������ж��Ƿ����   
	{   
		//	MessageBox(L"û�д��û��ļ�,��ע��",L"������");//��ӡ������ʾ   
		//	getchar();   
		return ;
	}   
	if((fp1=fopen("�������û���.doc","rb"))==NULL)//���ļ����ж��Ƿ����     
	{   
		//	MessageBox(L"û�д��û��ļ�,��ע��!\n\n",L"������");//��ӡ������ʾ   
		//	getchar();   
		return;   
	}   
	fscanf(fp1,"%d",&TravelNum);   
	fclose(fp1);//�ر��ļ�   

	for(i=0;i<TravelNum;i++)    
	{   
		fread(&User[i],sizeof(_USER_),1,fp);//���ļ��ж�ȡ��Ϣ   

	}   
	fclose(fp);//�ر��ļ�   
}   



void CLogin::SaveTravel()//����ģ�����   
{   int i = 0;
FILE *fp,*fp1;//�����ļ�ָ��   
if((fp=fopen("�������û�.doc","wb"))==NULL)//���ļ����ж��Ƿ����     
{   
	MessageBox(L"�����ļ�ʧ��!\n\n",L"������");//��ӡ������ʾ   
	getchar();   
	return;   
}   
if((fp1=fopen("�������û���.doc","wb"))==NULL)//���ļ����ж��Ƿ����     
{   
	MessageBox(L"�����ļ�ʧ��!\n\n",L"������");//��ӡ������ʾ  
	getchar();   
	return;   
}   
for(i=0;i<TravelNum;i++)   
	if(fwrite(&User[i],sizeof(_USER_),1,fp)==0)//���ļ�д�����ݣ����ж��Ƿ����   
		MessageBox(L"���ļ���������ʧ��!\n\n",L"������");   
fprintf(fp1,"%d",TravelNum);   
fclose(fp);//�ر��ļ�   
fclose(fp1);//�ر��ļ�   
}   




void CLogin::ReadPerson()//���ļ���ȡ��Ϣģ��   
{   

	int i =0;
	FILE *fp,*fp1;//�����ļ�ָ��   
	if((fp=fopen("�����û�.doc","rb"))==NULL)//���ļ������ж��Ƿ����   
	{   
		//	MessageBox(L"û�д��û��ļ�,��ע��",L"������");//��ӡ������ʾ   
		//	getchar();   
		return ;
	}   
	if((fp1=fopen("�����û���.doc","rb"))==NULL)//���ļ����ж��Ƿ����     
	{   
		//	MessageBox(L"û�д��û��ļ�,��ע��!\n\n",L"������");//��ӡ������ʾ   
		//	getchar();   
		return;   
	}   
	fscanf(fp1,"%d",&UserNum);   
	fclose(fp1);//�ر��ļ�   

	for(i=0;i<UserNum;i++)    
	{   
		fread(&User[i],sizeof(_USER_),1,fp);//���ļ��ж�ȡ��Ϣ   

	}   
	fclose(fp);//�ر��ļ�   
}   



void CLogin::SavePerson()//����ģ�����   
{   int i = 0;
FILE *fp,*fp1;//�����ļ�ָ��   
if((fp=fopen("�����û�.doc","wb"))==NULL)//���ļ����ж��Ƿ����     
{   
	MessageBox(L"�����ļ�ʧ��!\n\n",L"������");//��ӡ������ʾ   
	getchar();   
	return;   
}   
if((fp1=fopen("�����û���.doc","wb"))==NULL)//���ļ����ж��Ƿ����     
{   
	MessageBox(L"�����ļ�ʧ��!\n\n",L"������");//��ӡ������ʾ  
	getchar();   
	return;   
}   
for(i=0;i<UserNum;i++)   
	if(fwrite(&User[i],sizeof(_USER_),1,fp)==0)//���ļ�д�����ݣ����ж��Ƿ����   
		MessageBox(L"���ļ���������ʧ��!\n\n",L"������");   
fprintf(fp1,"%d",UserNum);   
fclose(fp);//�ر��ļ�   
fclose(fp1);//�ر��ļ�   
}   



void CLogin::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	// TODO: �ڴ˴������Ϣ����������
	// ��Ϊ��ͼ��Ϣ���� CDialogEx::OnPaint()
	CDC *pDC;
  	pDC=GetDC();
  	CRect rect;
  	GetClientRect(&rect);
 	 CBitmap wtj_bitmap;
 	 CDC dcMemory;
 
 	 wtj_bitmap.LoadBitmap(IDB_BITMAP_Enter);
 	 BITMAP bmInfo;
  	wtj_bitmap.GetObject(sizeof(bmInfo),&bmInfo);
  	dcMemory.CreateCompatibleDC(pDC);
   	dcMemory.FillSolidRect(&rect,RGB(255,0,0));
  	dcMemory.SelectObject(&wtj_bitmap);
 

  	pDC->StretchBlt(0,0,
  	 rect.Width(),rect.Height(),
  	 &dcMemory,
 	  0,0,
  	 bmInfo.bmWidth,bmInfo.bmHeight,
  	 SRCCOPY);

 	 ReleaseDC(pDC);
	 
}


void CLogin::OnBnClickedCancel()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CDialogEx::OnCancel();
}


void CLogin::OnBnClickedButtonfix()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CType Type;
	Type.DoModal();
}


HBRUSH CLogin::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialogEx::OnCtlColor(pDC, pWnd, nCtlColor);

	// TODO:  �ڴ˸��� DC ���κ�����

	// TODO:  ���Ĭ�ϵĲ������軭�ʣ��򷵻���һ������



	UINT id = pWnd->GetDlgCtrlID();
	if(id == IDC_STATIC||id ==IDC_CHECK_Company||id==IDC_CHECK_Person||id==IDC_CHECK_Travel||id==IDC_BUTTON_Register
		||id==IDOK||id==IDC_BUTTONFix)// || id == IDC_CHECK1)
	{
		pDC->SetBkMode(TRANSPARENT);

		CRect rc;
		pWnd->GetWindowRect(&rc);
		ScreenToClient(&rc);

		CDC* dc = GetDC();

		pDC->BitBlt(0,0,rc.Width(),rc.Height(),dc,rc.left,rc.top,SRCCOPY);	//�Ѹ����ڱ���ͼƬ�Ȼ�����ť��

		ReleaseDC(dc);

		hbr = (HBRUSH) ::GetStockObject(NULL_BRUSH);
	}	
	return hbr;
}
