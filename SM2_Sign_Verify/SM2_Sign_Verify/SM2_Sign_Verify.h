
// SM2_Sign_Verify.h : PROJECT_NAME 应用程序的主头文件
//

#pragma once

#ifndef __AFXWIN_H__
	#error "在包含此文件之前包含“stdafx.h”以生成 PCH 文件"
#endif

#include "resource.h"		// 主符号


// CSM2_Sign_VerifyApp:
// 有关此类的实现，请参阅 SM2_Sign_Verify.cpp
//

class CSM2_Sign_VerifyApp : public CWinApp
{
public:
	CSM2_Sign_VerifyApp();

// 重写
public:
	virtual BOOL InitInstance();

// 实现

	DECLARE_MESSAGE_MAP()
};

extern CSM2_Sign_VerifyApp theApp;