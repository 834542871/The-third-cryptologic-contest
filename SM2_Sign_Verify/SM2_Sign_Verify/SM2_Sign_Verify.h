
// SM2_Sign_Verify.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CSM2_Sign_VerifyApp:
// �йش����ʵ�֣������ SM2_Sign_Verify.cpp
//

class CSM2_Sign_VerifyApp : public CWinApp
{
public:
	CSM2_Sign_VerifyApp();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CSM2_Sign_VerifyApp theApp;