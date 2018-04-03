
// SM2_Sign_VerifyDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "SM2_Sign_Verify.h"
#include "SM2_Sign_VerifyDlg.h"
#include "afxdialogex.h"
#include "ec_param.h"
#include "ec_param.c"
#include "sm2_common.h"

#include "sm2_test_param.h"
#include "sm2_test_param.c"
#include "SM3.h"
#include "SM3.c"
#include "sm2_ec_key.h"
#include "sm2_ec_key.c"
#include "util.h"
#include "util.c"
#include "xy_ecpoint.h"
#include "xy_ecpoint.c"

#include"part2.h"
#include "part2.c"
#include "byteconverter.h"




#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CSM2_Sign_VerifyDlg 对话框




CSM2_Sign_VerifyDlg::CSM2_Sign_VerifyDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CSM2_Sign_VerifyDlg::IDD, pParent)
	, m_sign_file(_T(""))
	, m_Sign_r(_T(""))
	, m_Sign_e(_T(""))
	, m_22(_T(""))
	, m_23(_T(""))
	, m_24(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CSM2_Sign_VerifyDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, m_sign_file);
	DDX_Text(pDX, IDC_Sign_r, m_Sign_r);
	DDX_Text(pDX, IDC_EDIT4, m_Sign_e);
	DDX_Text(pDX, IDC_EDIT5, m_21);
	DDX_Text(pDX, IDC_EDIT6, m_22);
	DDX_Text(pDX, IDC_EDIT7, m_23);
	DDX_Text(pDX, IDC_EDIT8, m_24);
	//DDX_Text(pDX, IDC_Sign_s, m_sign_file);
}

BEGIN_MESSAGE_MAP(CSM2_Sign_VerifyDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_EN_CHANGE(IDC_EDIT1, &CSM2_Sign_VerifyDlg::OnEnChangeEdit1)
	ON_BN_CLICKED(IDC_sign_file, &CSM2_Sign_VerifyDlg::OnBnClickedsignfile)
	ON_BN_CLICKED(IDC_SIGN, &CSM2_Sign_VerifyDlg::OnBnClickedSign)
	ON_EN_CHANGE(IDC_Sign_r, &CSM2_Sign_VerifyDlg::OnEnChangeSignr)
	ON_EN_CHANGE(IDC_Sign_s, &CSM2_Sign_VerifyDlg::OnEnChangeSigns)
	ON_EN_CHANGE(IDC_EDIT4, &CSM2_Sign_VerifyDlg::OnEnChangeEdit4)
	ON_EN_CHANGE(IDC_EDIT5, &CSM2_Sign_VerifyDlg::OnEnChangeEdit5)
	ON_BN_CLICKED(IDC_BUTTON3, &CSM2_Sign_VerifyDlg::OnBnClickedButton3)
	ON_EN_CHANGE(IDC_EDIT6, &CSM2_Sign_VerifyDlg::OnEnChangeEdit6)
	ON_EN_CHANGE(IDC_EDIT7, &CSM2_Sign_VerifyDlg::OnEnChangeEdit7)
	ON_BN_CLICKED(IDC_BUTTON4, &CSM2_Sign_VerifyDlg::OnBnClickedButton4)
	ON_EN_CHANGE(IDC_EDIT8, &CSM2_Sign_VerifyDlg::OnEnChangeEdit8)
	ON_BN_CLICKED(IDC_BUTTON5, &CSM2_Sign_VerifyDlg::OnBnClickedButton5)
	ON_BN_CLICKED(IDC_Verify, &CSM2_Sign_VerifyDlg::OnBnClickedVerify)
END_MESSAGE_MAP()


// CSM2_Sign_VerifyDlg 消息处理程序

BOOL CSM2_Sign_VerifyDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 设置此对话框的图标。当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CSM2_Sign_VerifyDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CSM2_Sign_VerifyDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CSM2_Sign_VerifyDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CSM2_Sign_VerifyDlg::OnEnChangeEdit1()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialogEx::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
}


void CSM2_Sign_VerifyDlg::OnBnClickedsignfile()
{
	// TODO: 在此添加控件通知处理程序代码
	CString FilePathName;
	CFileDialog dlg(TRUE,
		NULL,
		NULL,
		OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,
		(LPCTSTR)_TEXT("ALL Files(*.*)|*.*||文本文件(*.txt)|*.txt|JPEG图片(*.jpg)|*.jpg|PNG图片(*.png)|*.png|BMP图片（*.bmp）|*.bmp"),
		NULL);
	if(dlg.DoModal() == IDOK)
	{
		FilePathName = dlg.GetPathName();
		SetDlgItemText(IDC_EDIT1,FilePathName);
	}
	else
	{
		return;
	}

}
int print_hex(char *pdst,unsigned char* psrc,int len)
{
	int i=0;
	for (i = 0;i<len;i++)
	{
		sprintf(pdst,"%02X",psrc[i]&0xff);
		pdst+=2;
	}
	return 0;
}

int AscToHex(unsigned char * AscBuf,int nLen,char cType,unsigned char * HexBuf)
{
	int i = 0;
	char cTmp,cTmp1;
	if(AscBuf == NULL)
		return -1; //-1代表失败
	if (nLen & 0x01 &cType)
		cTmp1 = 0;
	else 
		cTmp1 = 0x55;

	for (i = 0;i < nLen;AscBuf++,i++)
	{
		if (*AscBuf >= 'a')
			cTmp = *AscBuf - 'a' + 10;
		else if(*AscBuf >= 'A')
			cTmp = *AscBuf - 'A' +10;
		else if(*AscBuf >= '0')
			cTmp = *AscBuf - '0';
		else
		{
			cTmp = *AscBuf;
			cTmp &= 0x0f;
		}
		if(cTmp1 == 0x55)
			cTmp1 = cTmp;
		else
		{
			*HexBuf++ = cTmp1<<4|cTmp;
			cTmp1 = 0x55;
		}
	}
	if(cTmp1 != 0x55)
		*HexBuf = cTmp1 << 4;

	return 0;  //0代表成功
}



//开始签名
void CSM2_Sign_VerifyDlg::OnBnClickedSign()
{
	UpdateData(TRUE);
	USES_CONVERSION;


	// TODO: 在此添加控件通知处理程序代码
	typedef struct 
	{
	BYTE *message;
	int message_byte_length;
	BYTE *ID;
	int ENTL;
	BYTE k[MAX_POINT_BYTE_LENGTH];  //签名中产生随机数

	BYTE private_key[MAX_POINT_BYTE_LENGTH];
	struct 
	{
		BYTE x[MAX_POINT_BYTE_LENGTH];
		BYTE y[MAX_POINT_BYTE_LENGTH];
	}public_key;
	BYTE Z[HASH_BYTE_LENGTH];
	BYTE r[MAX_POINT_BYTE_LENGTH];
	BYTE s[MAX_POINT_BYTE_LENGTH];
	BYTE R[MAX_POINT_BYTE_LENGTH];
	}sm2_sign_st1;


	sm2_hash Z_A;
	sm2_hash e;
	BIGNUM *e_bn;

	BIGNUM *r;
	BIGNUM *s;
	BIGNUM *tmp1;

	BIGNUM *P_x;
	BIGNUM *P_y;
	BIGNUM *d;
	BIGNUM *k;
	xy_ecpoint *xy1;

	char *sm2_param_fp_256[] = {
		//示例2：Fp-256曲线 
		//素数p： 
		"8542D69E" "4C044F18" "E8B92435" "BF6FF7DE" "45728391" "5C45517D" "722EDB8B" "08F1DFC3",
		//系数a： 
		"787968B4" "FA32C3FD" "2417842E" "73BBFEFF" "2F3C848B" "6831D7E0" "EC65228B" "3937E498",
		//系数b： 
		"63E4C6D3" "B23B0C84" "9CF84241" "484BFE48" "F61D59A5" "B16BA06E" "6E12D1DA" "27C5249A",
		//基点G = (x;y)，其阶记为n。 
		//坐标x： 
		"421DEBD6" "1B62EAB6" "746434EB" "C3CC315E" "32220B3B" "ADD50BDC" "4C4E6C14" "7FEDD43D",
		//坐标y： 
		"0680512B" "CBB42C07" "D47349D2" "153B70C4" "E5D7FDFC" "BFA36EA1" "A85841B9" "E46E09A2",
		//阶n： 
		"8542D69E" "4C044F18" "E8B92435" "BF6FF7DD" "29772063" "0485628D" "5AE74EE7" "C32E79B7",
	};

	ec_param *ecp;
	sm2_ec_key *key_A;
	sm2_sign_st1 sign;

	ecp = ec_param_new();
	ec_param_init(ecp, sm2_param_fp_256, 0, 256);

	key_A = sm2_ec_key_new(ecp);
	sm2_ec_key_init(key_A, sm2_param_digest_d_A[ecp->type], ecp);

	//memset(&sign, 0, sizeof(sign));
	sign.message = (BYTE *)message_digest;
	sign.message_byte_length = strlen(message_digest);
	sign.ID = (BYTE *)ID_A;
	sign.ENTL = strlen(ID_A);
	sm2_hex2bin((BYTE *)sm2_param_digest_k[ecp->type], sign.k, ecp->point_byte_length);
	sm2_bn2bin(key_A->d, sign.private_key, ecp->point_byte_length);
	sm2_bn2bin(key_A->P->x, sign.public_key.x, ecp->point_byte_length);
	sm2_bn2bin(key_A->P->y, sign.public_key.y, ecp->point_byte_length);
	

	e_bn = BN_new();
	r = BN_new();
	s = BN_new();
	tmp1 = BN_new();
	P_x = BN_new();
	P_y = BN_new();
	d = BN_new();
	k = BN_new();
	xy1 = xy_ecpoint_new(ecp);

	BN_bin2bn(sign.public_key.x, ecp->point_byte_length, P_x);
	BN_bin2bn(sign.public_key.y, ecp->point_byte_length, P_y);
	BN_bin2bn(sign.private_key, ecp->point_byte_length, d);
	BN_bin2bn(sign.k, ecp->point_byte_length, k);

	memset(&Z_A, 0, sizeof(Z_A));
	Z_A.buffer[0] = ((sign.ENTL * 8) >> 8) & 0xFF;
	Z_A.buffer[1] = (sign.ENTL * 8) & 0xFF;
	Z_A.position = Z_A.position + 2;
	BUFFER_APPEND_STRING(Z_A.buffer, Z_A.position, sign.ENTL, sign.ID);
	BUFFER_APPEND_BIGNUM(Z_A.buffer, Z_A.position, ecp->point_byte_length, ecp->a);
	BUFFER_APPEND_BIGNUM(Z_A.buffer, Z_A.position, ecp->point_byte_length, ecp->b);
	BUFFER_APPEND_BIGNUM(Z_A.buffer, Z_A.position, ecp->point_byte_length, ecp->G->x);
	BUFFER_APPEND_BIGNUM(Z_A.buffer, Z_A.position, ecp->point_byte_length, ecp->G->y);
	BUFFER_APPEND_BIGNUM(Z_A.buffer, Z_A.position, ecp->point_byte_length, P_x);
	BUFFER_APPEND_BIGNUM(Z_A.buffer, Z_A.position, ecp->point_byte_length, P_y);
	DEFINE_SHOW_STRING(Z_A.buffer, Z_A.position);
	SM3_Init();
	SM3_Update(Z_A.buffer, Z_A.position);
	SM3_Final_byte(Z_A.hash);
	memcpy(sign.Z, Z_A.hash, HASH_BYTE_LENGTH);

	//DEFINE_SHOW_STRING(Z_A.hash, HASH_BYTE_LENGTH);

	memset(&e, 0, sizeof(e));
	BUFFER_APPEND_STRING(e.buffer, e.position, HASH_BYTE_LENGTH, Z_A.hash);
	BUFFER_APPEND_STRING(e.buffer, e.position, strlen(message_digest), (BYTE *)message_digest);
	SM3_Init();
	SM3_Update(e.buffer, e.position);
	SM3_Final_byte(e.hash);
	//DEFINE_SHOW_STRING(e.hash, HASH_BYTE_LENGTH);
	//DEFINE_SHOW_STRING(sign.k, ecp->point_byte_length);
	/////////////////////////
	FILE *fp_e = NULL;
	if (NULL == (fp_e = fopen("C://sign_e.txt","w+")))
	{
		MessageBox(L"打开文件失败",L"提示",MB_OK);
		return;
	}
	char e_show[256] = {0};
	print_hex(e_show,e.hash,32);
	fwrite(e_show,1,64,fp_e);
	fclose(fp_e);
	SetDlgItemText(IDC_EDIT4,A2W(e_show));




	////////////////////////////
	BN_bin2bn(e.hash, HASH_BYTE_LENGTH, e_bn);

	xy_ecpoint_mul_bignum(xy1, ecp->G, k, ecp);
	BN_zero(r);
	BN_mod_add(r, e_bn, xy1->x, ecp->n, ecp->ctx);

	BN_one(s);
	BN_add(s, s, d);
	BN_mod_inverse(s, s, ecp->n, ecp->ctx);  //求模反

	BN_mul(tmp1, r, d, ecp->ctx);
	BN_sub(tmp1, k, tmp1);
	BN_mod_mul(s, s, tmp1, ecp->n, ecp->ctx);

	sm2_bn2bin(r, sign.r, ecp->point_byte_length);
	sm2_bn2bin(s, sign.s, ecp->point_byte_length);
	//////////////////////////
	FILE *fp_r = NULL;
	if (NULL == (fp_r = fopen("C://sign_r.txt","w+")))
	{
		MessageBox(L"打开文件失败",L"提示",MB_OK);
		return;
	}
	char r_show[256] = {0};
	print_hex(r_show,sign.r,32);
	fwrite(r_show,1,64,fp_r);
	fclose(fp_r);
	SetDlgItemText(IDC_Sign_r,A2W(r_show));

	//写入s值并 显示
	FILE *fp_s = NULL;
	if (NULL == (fp_s = fopen("C://sign_s.txt","w+")))
	{
		MessageBox(L"打开文件失败",L"提示",MB_OK);
		return;
	}
	char s_show[256] = {0};
	print_hex(s_show,sign.s,32);
	fwrite(s_show,1,64,fp_s);
	fclose(fp_s);
	SetDlgItemText(IDC_Sign_s,A2W(s_show));

	MessageBox(L"签名成功，签名值存放在sign_s.txt和sign_r.txt中",L"提示",MB_OK);







	/////////////////////////
	BN_free(e_bn);
	BN_free(r);
	BN_free(s);
	BN_free(tmp1);
	BN_free(P_x);
	BN_free(P_y);
	BN_free(d);
	BN_free(k);
	xy_ecpoint_free(xy1);
	sm2_ec_key_free(key_A);
	ec_param_free(ecp);
}


void CSM2_Sign_VerifyDlg::OnEnChangeSignr()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialogEx::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
}


void CSM2_Sign_VerifyDlg::OnEnChangeSigns()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialogEx::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
}


void CSM2_Sign_VerifyDlg::OnEnChangeEdit4()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialogEx::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
}


void CSM2_Sign_VerifyDlg::OnEnChangeEdit5()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialogEx::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
}

//选择验证文件
void CSM2_Sign_VerifyDlg::OnBnClickedButton3()
{
	// TODO: 在此添加控件通知处理程序代码
	CString FilePathName;
	CFileDialog dlg(TRUE,
		NULL,
		NULL,
		OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,
		(LPCTSTR)_TEXT("文本文件(*.txt)|*.txt|ALL Files(*.*)|*.*||"),
		NULL);
	if(dlg.DoModal() == IDOK)
	{
		FilePathName = dlg.GetPathName();
		SetDlgItemText(IDC_EDIT5,FilePathName);
	}
	else
	{
		return;
	}

}


void CSM2_Sign_VerifyDlg::OnEnChangeEdit6()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialogEx::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
}


void CSM2_Sign_VerifyDlg::OnEnChangeEdit7()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialogEx::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
}

//选择r
void CSM2_Sign_VerifyDlg::OnBnClickedButton4()
{
	// TODO: 在此添加控件通知处理程序代码
	CString FilePathName;
	CFileDialog dlg(TRUE,
		NULL,
		NULL,
		OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,
		(LPCTSTR)_TEXT("文本文件(*.txt)|*.txt|ALL Files(*.*)|*.*||"),
		NULL);
	if(dlg.DoModal() == IDOK)
	{
		FilePathName = dlg.GetPathName();
		SetDlgItemText(IDC_EDIT7,FilePathName);
	}
	else
	{
		return;
	}
}


void CSM2_Sign_VerifyDlg::OnEnChangeEdit8()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialogEx::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
}


void CSM2_Sign_VerifyDlg::OnBnClickedButton5()
{
	// TODO: 在此添加控件通知处理程序代码】
	CString FilePathName;
	CFileDialog dlg(TRUE,
		NULL,
		NULL,
		OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,
		(LPCTSTR)_TEXT("文本文件(*.txt)|*.txt|ALL Files(*.*)|*.*||"),
		NULL);
	if(dlg.DoModal() == IDOK)
	{
		FilePathName = dlg.GetPathName();
		SetDlgItemText(IDC_EDIT8,FilePathName);
	}
	else
	{
		return;
	}

}

///y验证程序
void CSM2_Sign_VerifyDlg::OnBnClickedVerify()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);
	USES_CONVERSION;


	typedef struct 
	{
		BYTE *message;
		int message_byte_length;
		BYTE *ID;
		int ENTL;
		BYTE k[MAX_POINT_BYTE_LENGTH];  //签名中产生随机数

		BYTE private_key[MAX_POINT_BYTE_LENGTH];
		struct 
		{
			BYTE x[MAX_POINT_BYTE_LENGTH];
			BYTE y[MAX_POINT_BYTE_LENGTH];
		}public_key;
		BYTE Z[HASH_BYTE_LENGTH];
		BYTE r[MAX_POINT_BYTE_LENGTH];
		BYTE s[MAX_POINT_BYTE_LENGTH];
		BYTE R[MAX_POINT_BYTE_LENGTH];
		
	}sm2_sign_st2;


	//设置需要的参数
	////////////////////////////////////

	char *sm2_param_fp_256[] = {
		//示例2：Fp-256曲线 
		//素数p： 
		"8542D69E" "4C044F18" "E8B92435" "BF6FF7DE" "45728391" "5C45517D" "722EDB8B" "08F1DFC3",
		//系数a： 
		"787968B4" "FA32C3FD" "2417842E" "73BBFEFF" "2F3C848B" "6831D7E0" "EC65228B" "3937E498",
		//系数b： 
		"63E4C6D3" "B23B0C84" "9CF84241" "484BFE48" "F61D59A5" "B16BA06E" "6E12D1DA" "27C5249A",
		//基点G = (x;y)，其阶记为n。 
		//坐标x： 
		"421DEBD6" "1B62EAB6" "746434EB" "C3CC315E" "32220B3B" "ADD50BDC" "4C4E6C14" "7FEDD43D",
		//坐标y： 
		"0680512B" "CBB42C07" "D47349D2" "153B70C4" "E5D7FDFC" "BFA36EA1" "A85841B9" "E46E09A2",
		//阶n： 
		"8542D69E" "4C044F18" "E8B92435" "BF6FF7DD" "29772063" "0485628D" "5AE74EE7" "C32E79B7",
	};

	ec_param *ecp;
	sm2_ec_key *key_A;
	sm2_sign_st2 sign1;
	ecp = ec_param_new();
	ec_param_init(ecp, sm2_param_fp_256, 0, 256);

	key_A = sm2_ec_key_new(ecp);
	sm2_ec_key_init(key_A, sm2_param_digest_d_A[ecp->type], ecp);

	memset(&sign1, 0, sizeof(sign1));
	sign1.message = (BYTE *)message_digest;
	sign1.message_byte_length = strlen(message_digest);
	sign1.ID = (BYTE *)ID_A;
	sign1.ENTL = strlen(ID_A);
	sm2_hex2bin((BYTE *)sm2_param_digest_k[ecp->type], sign1.k, ecp->point_byte_length);
	sm2_bn2bin(key_A->d, sign1.private_key, ecp->point_byte_length);
	sm2_bn2bin(key_A->P->x, sign1.public_key.x, ecp->point_byte_length);
	sm2_bn2bin(key_A->P->y, sign1.public_key.y, ecp->point_byte_length);

	////////////////////////////////////
// 	FILE *fp = NULL;
// 	if(NULL == (fp = fopen(W2A(m_21),"r+")))
//  	{
//  		MessageBox(L"打开文件失败",L"提示",MB_OK);
//  		return;
//  	}
//  	fseek(fp,0,2);
//  	int file_len1 = ftell(fp);
//  	fseek(fp,0,0);
//  	 char *input = NULL;
//  	input= (char*)calloc(file_len1,sizeof(unsigned char));
//  	fread(input,1,file_len1,fp);
 //////////////////////////////////////////////////	
	sm2_hash Z_A;
	sm2_hash e;

	BIGNUM *e_bn;

	BIGNUM *r;
	BIGNUM *s;
	BIGNUM *tmp1;

	BIGNUM *P_x;
	BIGNUM *P_y;
	BIGNUM *d;
	BIGNUM *k;
	BIGNUM *t;
	BIGNUM *R;
	xy_ecpoint *xy1;

	xy_ecpoint *result;
	xy_ecpoint *result1;
	xy_ecpoint *result2;
	xy_ecpoint *P_A;

	t=BN_new();
	e_bn = BN_new();
	r = BN_new();
	s = BN_new();
	tmp1 = BN_new();
	P_x = BN_new();
	P_y = BN_new();
	d = BN_new();
	k = BN_new();
	xy1 = xy_ecpoint_new(ecp);
	P_A = xy_ecpoint_new(ecp);
	R = BN_new();
	result = xy_ecpoint_new(ecp);
	result1 = xy_ecpoint_new(ecp);
	result2 = xy_ecpoint_new(ecp);



	BN_bin2bn(sign1.public_key.x, ecp->point_byte_length, P_x);
	BN_bin2bn(sign1.public_key.y, ecp->point_byte_length, P_y);
	BN_bin2bn(sign1.private_key, ecp->point_byte_length, d);
	BN_bin2bn(sign1.k, ecp->point_byte_length, k);

	memset(&Z_A, 0, sizeof(Z_A));
	Z_A.buffer[0] = ((sign1.ENTL * 8) >> 8) & 0xFF;
	Z_A.buffer[1] = (sign1.ENTL * 8) & 0xFF;
	Z_A.position = Z_A.position + 2;
	BUFFER_APPEND_STRING(Z_A.buffer, Z_A.position, sign1.ENTL, sign1.ID);
	BUFFER_APPEND_BIGNUM(Z_A.buffer, Z_A.position, ecp->point_byte_length, ecp->a);
	BUFFER_APPEND_BIGNUM(Z_A.buffer, Z_A.position, ecp->point_byte_length, ecp->b);
	BUFFER_APPEND_BIGNUM(Z_A.buffer, Z_A.position, ecp->point_byte_length, ecp->G->x);
	BUFFER_APPEND_BIGNUM(Z_A.buffer, Z_A.position, ecp->point_byte_length, ecp->G->y);
	BUFFER_APPEND_BIGNUM(Z_A.buffer, Z_A.position, ecp->point_byte_length, P_x);
	BUFFER_APPEND_BIGNUM(Z_A.buffer, Z_A.position, ecp->point_byte_length, P_y);
	DEFINE_SHOW_STRING(Z_A.buffer, Z_A.position);
	SM3_Init();
	SM3_Update(Z_A.buffer, Z_A.position);
	SM3_Final_byte(Z_A.hash);
	memcpy(sign1.Z, Z_A.hash, HASH_BYTE_LENGTH);
	//读取r，s
	///////////////////////////////////////////////////
	FILE *fp_r = NULL;
	if (NULL == (fp_r = fopen(W2A(m_23),"r+")))
	{
		MessageBox(L"打开r文件失败",L"提示",MB_OK);
		return;
	}
	fseek(fp_r,0,2);
	int file_len11 = ftell(fp_r);
	fseek(fp_r,0,0);
	

	unsigned char r_tmp[64] = {0};
	///////////
 	char RR[256]={0};
	
	fread(r_tmp,64,1,fp_r);
	for (int aa=0;aa<file_len11;aa++)
	{
		RR[aa]=r_tmp[aa];
	}


	if (0 != AscToHex(r_tmp,64,0,sign1.r))  	//字符串转十六进制
	{
		MessageBox(L"字符转换失败！");
		return;
	}
	fclose(fp_r);

	FILE *fp_s = NULL;
	if (NULL == (fp_s = fopen(W2A(m_24),"r+")))
	{
		MessageBox(L"打开s文件失败",L"提示",MB_OK);
		return;
	}
	unsigned char s_tmp[64] = {0};
	fread(s_tmp,64,1,fp_s);
	if (0 != AscToHex(s_tmp,64,0,sign1.s))  	//字符串转十六进制
	{
		MessageBox(L"字符转换失败！");
		return;
	}
	fclose(fp_s);





	///////////////////////////////////////////////////////

	BN_bin2bn(sign1.r, ecp->point_byte_length, r);
	BN_bin2bn(sign1.s, ecp->point_byte_length, s);
	BN_bin2bn(sign1.public_key.x, ecp->point_byte_length, P_x);
	BN_bin2bn(sign1.public_key.y, ecp->point_byte_length, P_y);
	xy_ecpoint_init_xy(P_A, P_x, P_y, ecp);
//////////////////////////////////////////////////////////////////
	memset(&e, 0, sizeof(e));
	BUFFER_APPEND_STRING(e.buffer, e.position, HASH_BYTE_LENGTH, sign1.Z);
	BUFFER_APPEND_STRING(e.buffer, e.position, sign1.message_byte_length, (BYTE*)sign1.message);
	SM3_Init();
	SM3_Update(e.buffer, e.position);
	SM3_Final_byte(e.hash);
	BN_bin2bn(e.hash, HASH_BYTE_LENGTH, e_bn);


	BN_mod_add(t, r, s, ecp->n, ecp->ctx);
	xy_ecpoint_mul_bignum(result1, ecp->G, s, ecp);
	xy_ecpoint_mul_bignum(result2, P_A, t, ecp);
	xy_ecpoint_add_xy_ecpoint(result, result1, result2, ecp);

	BN_mod_add(R, e_bn, result->x, ecp->n, ecp->ctx);

	sm2_bn2bin(R, sign1.R, ecp->point_byte_length);

	//////////////////////////////

	char R_show[256] = {0};
	print_hex(R_show,sign1.R,32);
	SetDlgItemText(IDC_EDIT6,A2W(R_show));
	/////////////////////////

 
// 	  //  StrCmp(A2W(R_show),A2W(RR));
	  if (0 == StrCmp(A2W(R_show),A2W(RR)))
		  MessageBox(L"恭喜，验证成功！",L"恭喜",MB_OK);
	  else
		  MessageBox(L"很遗憾，验证失败！请重试！",L"遗憾",MB_OK);

	////////////////////
	BN_free(e_bn);
	BN_free(t);
	BN_free(R);
	xy_ecpoint_free(result);
	xy_ecpoint_free(result1);
	xy_ecpoint_free(result2);
	xy_ecpoint_free(P_A);
	BN_free(r);
	BN_free(s);
	BN_free(P_x);
	BN_free(P_y);
	sm2_ec_key_free(key_A);
	ec_param_free(ecp);

}
