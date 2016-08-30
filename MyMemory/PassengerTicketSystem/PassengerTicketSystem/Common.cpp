#include "StdAfx.h"
#include "Common.h"

int CCommon:: FlightCount = 0;  //�ܵĺ�����  �ɺ��๫˾�޸�
int CCommon:: PersonCount = 0;
int CCommon:: OrderCount = 0;
CCommon::CCommon(void)
{
	Flight = new FLIGHT[MAXNUM];
	memset(Flight,0,sizeof(_FLIGHT_)*MAXNUM);
	Passenger = new PASSENGER[MAXNUM];
	memset(Passenger,0,sizeof(_PASSENGER_)*MAXNUM);
	Order = new ORDER[MAXNUM];
	memset(Order,0,sizeof(_ORDER_)*MAXNUM);
}


CCommon::~CCommon(void)
{
	delete[] Flight;
	delete[] Passenger;
	delete[] Order;
}





void CCommon::read()//���ļ���ȡ��Ϣģ��   
{   int i =0;
FILE *fp,*fp1;//�����ļ�ָ��   
if((fp=fopen("������Ϣ.doc","rb"))==NULL)//���ļ������ж��Ƿ����   
{   
	MessageBox(NULL,L"���������ļ��Ƿ���ڣ���������������˵�",L"������ʾ",1);//��ӡ������ʾ   
	getchar();   
}   
if((fp1=fopen("������.doc","rb"))==NULL)//���ļ����ж��Ƿ����     
{   
	MessageBox(NULL,L"�����ļ�ʧ��!\n\n",L"������ʾ",1);//��ӡ������ʾ   
	getchar();   
	return;   
}   
fscanf(fp1,"%d",&FlightCount);   
fclose(fp1);//�ر��ļ�   

for(i=0;i<FlightCount;i++)    
{   
	fread(&Flight[i],sizeof(_FLIGHT_),1,fp);//���ļ��ж�ȡ��Ϣ   

}   
fclose(fp);//�ر��ļ�   
}   





void CCommon::save()//����ģ�����   
{   int i = 0;
FILE *fp,*fp1;//�����ļ�ָ��   
if((fp=fopen("������Ϣ.doc","wb"))==NULL)//���ļ����ж��Ƿ����     
{   
	MessageBox(NULL,L"�����ļ�ʧ��!\n\n",L"������",1);//��ӡ������ʾ   
	getchar();   
	return;   
}   
if((fp1=fopen("������.doc","wb"))==NULL)//���ļ����ж��Ƿ����     
{   
	MessageBox(NULL,L"�����ļ�ʧ��!\n\n",L"������",1);//��ӡ������ʾ  
	getchar();   
	return;   
}   
for(i=0;i<FlightCount;i++)   
	if(fwrite(&Flight[i],sizeof(_FLIGHT_),1,fp)==0)//���ļ�д�����ݣ����ж��Ƿ����   
		MessageBox(NULL,L"���ļ���������ʧ��!\n\n",L"������",1);   
fprintf(fp1,"%d",FlightCount);   
fclose(fp);//�ر��ļ�   
fclose(fp1);//�ر��ļ�   
}   



long CCommon::StringToInt( LPCTSTR str)
{
	TCHAR szBuff[ 20 ], *p;
	p = szBuff;

#ifdef _UNICODE
	return wcstol(  str, &p, 10 );   
#else
	return strtol(  str, &p, 10  );   
#endif
}






void CCommon::readPerson()//���ļ���ȡ��Ϣģ��   
{   int i =0;
FILE *fp,*fp1;//�����ļ�ָ��   
if((fp=fopen("�û���Ϣ.doc","rb"))==NULL)//���ļ������ж��Ƿ����   
{   
	MessageBox(NULL,L"���������ļ��Ƿ���ڣ���������������˵�",L"������ʾ",1);//��ӡ������ʾ   
	getchar();   
}   
if((fp1=fopen("�û���.doc","rb"))==NULL)//���ļ����ж��Ƿ����     
{   
	MessageBox(NULL,L"�����ļ�ʧ��!\n\n",L"������ʾ",1);//��ӡ������ʾ   
	getchar();   
	return;   
}   
fscanf(fp1,"%d",&PersonCount);   
fclose(fp1);//�ر��ļ�   

for(i=0;i<PersonCount;i++)    
{   
	fread(&Passenger[i],sizeof(_PASSENGER_),1,fp);//���ļ��ж�ȡ��Ϣ   

}   
fclose(fp);//�ر��ļ�   
}   





void CCommon::savePerson()//����ģ�����   
{   int i = 0;
FILE *fp,*fp1;//�����ļ�ָ��   
if((fp=fopen("�û���Ϣ.doc","wb"))==NULL)//���ļ����ж��Ƿ����     
{   
	MessageBox(NULL,L"�����ļ�ʧ��!\n\n",L"������",1);//��ӡ������ʾ   
	getchar();   
	return;   
}   
if((fp1=fopen("�û���.doc","wb"))==NULL)//���ļ����ж��Ƿ����     
{   
	MessageBox(NULL,L"�����ļ�ʧ��!\n\n",L"������",1);//��ӡ������ʾ  
	getchar();   
	return;   
}   
for(i=0;i<PersonCount;i++)   
	if(fwrite(&Passenger[i],sizeof(_PASSENGER_),1,fp)==0)//���ļ�д�����ݣ����ж��Ƿ����   
		MessageBox(NULL,L"���ļ���������ʧ��!\n\n",L"������",1);   
fprintf(fp1,"%d",PersonCount);   
fclose(fp);//�ر��ļ�   
fclose(fp1);//�ر��ļ�   
}   




void CCommon::saveUser(WCHAR *Name)//����ģ�����   
{   int i = 0;


FILE *fp;//�����ļ�ָ��   
if((fp=fopen("��½����.doc","wb"))==NULL)//���ļ����ж��Ƿ����     
{   
	MessageBox(NULL,L"�����ļ�ʧ��!\n\n",L"������",1);//��ӡ������ʾ   
	getchar();   
	return;   
}   
	if(fwrite(Name,20,1,fp)==0)//���ļ�д�����ݣ����ж��Ƿ����   
		MessageBox(NULL,L"���ļ���������ʧ��!\n\n",L"������",1);   
  
fclose(fp);//�ر��ļ�   

}   



WCHAR* CCommon::readUser()//���ļ���ȡ��Ϣģ��   
{   int i =0;
FILE *fp;//�����ļ�ָ��   
if((fp=fopen("��½����.doc","rb"))==NULL)//���ļ������ж��Ƿ����   
{   
	MessageBox(NULL,L"���������ļ��Ƿ���ڣ���������������˵�",L"������ʾ",1);//��ӡ������ʾ   
	getchar();   
}   



WCHAR Name[20] = {0};
 
	fread(Name,20,1,fp);//���ļ��ж�ȡ��Ϣ   


   
fclose(fp);//�ر��ļ�   
return Name;
}   






void CCommon::readOrder()//���ļ���ȡ��Ϣģ��   
{   int i =0;
FILE *fp,*fp1;//�����ļ�ָ��   
if((fp=fopen("������Ϣ.doc","rb"))==NULL)//���ļ������ж��Ƿ����   
{   
	MessageBox(NULL,L"���������ļ��Ƿ���ڣ���������������˵�",L"������ʾ",1);//��ӡ������ʾ   
	getchar();   
}   
if((fp1=fopen("������.doc","rb"))==NULL)//���ļ����ж��Ƿ����     
{   
	MessageBox(NULL,L"�����ļ�ʧ��!\n\n",L"������ʾ",1);//��ӡ������ʾ   
	getchar();   
	return;   
}   
fscanf(fp1,"%d",&OrderCount);   
fclose(fp1);//�ر��ļ�   

for(i=0;i<OrderCount;i++)    
{   
	fread(&Order[i],sizeof(_ORDER_),1,fp);//���ļ��ж�ȡ��Ϣ   

}   
fclose(fp);//�ر��ļ�   
}   





void CCommon::saveOrder()//����ģ�����   
{   int i = 0;
FILE *fp,*fp1;//�����ļ�ָ��   
if((fp=fopen("������Ϣ.doc","wb"))==NULL)//���ļ����ж��Ƿ����     
{   
	MessageBox(NULL,L"�����ļ�ʧ��!\n\n",L"������",1);//��ӡ������ʾ   
	getchar();   
	return;   
}   
if((fp1=fopen("������.doc","wb"))==NULL)//���ļ����ж��Ƿ����     
{   
	MessageBox(NULL,L"�����ļ�ʧ��!\n\n",L"������",1);//��ӡ������ʾ  
	getchar();   
	return;   
}   
for(i=0;i<OrderCount;i++)   
	if(fwrite(&Order[i],sizeof(_ORDER_),1,fp)==0)//���ļ�д�����ݣ����ж��Ƿ����   
		MessageBox(NULL,L"���ļ���������ʧ��!\n\n",L"������",1);   
fprintf(fp1,"%d",OrderCount);   
fclose(fp);//�ر��ļ�   
fclose(fp1);//�ر��ļ�   
}   

