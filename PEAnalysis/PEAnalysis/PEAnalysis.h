
// PEAnalysis.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CPEAnalysisApp:
// �йش����ʵ�֣������ PEAnalysis.cpp
//

class CPEAnalysisApp : public CWinApp
{
public:
	CPEAnalysisApp();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CPEAnalysisApp theApp;