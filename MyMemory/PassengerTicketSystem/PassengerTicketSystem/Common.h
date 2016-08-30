#pragma once
#define MAXNUM 10000   //�趨���10000�˵���Ϣ
typedef struct _FLIGHT_
{
	WCHAR FightNum[8];  //�����
	WCHAR Start[20];     //��ʼվ
	WCHAR Arrive[20];    //�յ�վ
	WCHAR TimeStart[20];     //����ʱ��
	WCHAR TimeArrive[20];    //����ʱ��
	int nYear;
	int nMonth;
	int nDay;
	int    Price;        //�۸�
	int     SeatLeft;    //��Ʊ��
	int     SeatNum;     //��Ʊ��
}FLIGHT,*PFLIGHT;



typedef struct _PASSENGER_
{
	WCHAR OrderNum[28];
	WCHAR UserName[20];    //�û���
	WCHAR PassengerName[20];//����
	WCHAR Sex[4];           //�Ա�
	WCHAR WorkPlace[20];    //������λ
	WCHAR IDCard[20];       //���֤����
	WCHAR StartTime[20];             //����ʱ��
	WCHAR ArriveTime[20];
	WCHAR Start[20];		//ϵͳ��ѯ�ÿ͵�ʼ��վ ���亽��
	WCHAR Arrive[20];
	WCHAR Price[10];
	WCHAR Seat[20];         //�����λ
	WCHAR FightNum[8];     //��ϵͳ����ĺ����   
	BOOL IsGet;            //�Ƿ�ȡƱ
	int nDay;
}PASSENGER,*PPASSENGER;

typedef struct _ORDER_
{
	WCHAR FightNum[8];     //��ϵͳ����ĺ���� 
	WCHAR OrderNum[28];
	BOOL IsGet;            //�Ƿ�ȡƱ
}ORDER,*PORDER;


class CCommon
{
public:
	CCommon(void);
	~CCommon(void);
	void CCommon::read();
	void CCommon::save();
	PFLIGHT Flight;
	PPASSENGER Passenger;
	PORDER Order;
	static int FlightCount;
	static int PersonCount;
	static int OrderCount;
	long CCommon::StringToInt( LPCTSTR str);

	void CCommon::savePerson();
	void CCommon::readPerson();

	WCHAR* CCommon::readUser();
	void CCommon::saveUser(WCHAR *Name);


	void CCommon::saveOrder();
	void CCommon::readOrder();
};







