
// AddSectionOfPatch.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CAddSectionOfPatchApp:
// �йش����ʵ�֣������ AddSectionOfPatch.cpp
//

class CAddSectionOfPatchApp : public CWinApp
{
public:
	CAddSectionOfPatchApp();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CAddSectionOfPatchApp theApp;