
// SM2_Sign_VerifyDlg.cpp : ʵ���ļ�
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


// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// �Ի�������
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ʵ��
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


// CSM2_Sign_VerifyDlg �Ի���




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


// CSM2_Sign_VerifyDlg ��Ϣ�������

BOOL CSM2_Sign_VerifyDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ��������...���˵�����ӵ�ϵͳ�˵��С�

	// IDM_ABOUTBOX ������ϵͳ���Χ�ڡ�
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

	// ���ô˶Ի����ͼ�ꡣ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO: �ڴ���Ӷ���ĳ�ʼ������

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
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

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CSM2_Sign_VerifyDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR CSM2_Sign_VerifyDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CSM2_Sign_VerifyDlg::OnEnChangeEdit1()
{
	// TODO:  ����ÿؼ��� RICHEDIT �ؼ���������
	// ���ʹ�֪ͨ��������д CDialogEx::OnInitDialog()
	// ���������� CRichEditCtrl().SetEventMask()��
	// ͬʱ�� ENM_CHANGE ��־�������㵽�����С�

	// TODO:  �ڴ���ӿؼ�֪ͨ����������
}


void CSM2_Sign_VerifyDlg::OnBnClickedsignfile()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CString FilePathName;
	CFileDialog dlg(TRUE,
		NULL,
		NULL,
		OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,
		(LPCTSTR)_TEXT("ALL Files(*.*)|*.*||�ı��ļ�(*.txt)|*.txt|JPEGͼƬ(*.jpg)|*.jpg|PNGͼƬ(*.png)|*.png|BMPͼƬ��*.bmp��|*.bmp"),
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
		return -1; //-1����ʧ��
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

	return 0;  //0����ɹ�
}



//��ʼǩ��
void CSM2_Sign_VerifyDlg::OnBnClickedSign()
{
	UpdateData(TRUE);
	USES_CONVERSION;


	// TODO: �ڴ���ӿؼ�֪ͨ����������
	typedef struct 
	{
	BYTE *message;
	int message_byte_length;
	BYTE *ID;
	int ENTL;
	BYTE k[MAX_POINT_BYTE_LENGTH];  //ǩ���в��������

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
		//ʾ��2��Fp-256���� 
		//����p�� 
		"8542D69E" "4C044F18" "E8B92435" "BF6FF7DE" "45728391" "5C45517D" "722EDB8B" "08F1DFC3",
		//ϵ��a�� 
		"787968B4" "FA32C3FD" "2417842E" "73BBFEFF" "2F3C848B" "6831D7E0" "EC65228B" "3937E498",
		//ϵ��b�� 
		"63E4C6D3" "B23B0C84" "9CF84241" "484BFE48" "F61D59A5" "B16BA06E" "6E12D1DA" "27C5249A",
		//����G = (x;y)����׼�Ϊn�� 
		//����x�� 
		"421DEBD6" "1B62EAB6" "746434EB" "C3CC315E" "32220B3B" "ADD50BDC" "4C4E6C14" "7FEDD43D",
		//����y�� 
		"0680512B" "CBB42C07" "D47349D2" "153B70C4" "E5D7FDFC" "BFA36EA1" "A85841B9" "E46E09A2",
		//��n�� 
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
		MessageBox(L"���ļ�ʧ��",L"��ʾ",MB_OK);
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
	BN_mod_inverse(s, s, ecp->n, ecp->ctx);  //��ģ��

	BN_mul(tmp1, r, d, ecp->ctx);
	BN_sub(tmp1, k, tmp1);
	BN_mod_mul(s, s, tmp1, ecp->n, ecp->ctx);

	sm2_bn2bin(r, sign.r, ecp->point_byte_length);
	sm2_bn2bin(s, sign.s, ecp->point_byte_length);
	//////////////////////////
	FILE *fp_r = NULL;
	if (NULL == (fp_r = fopen("C://sign_r.txt","w+")))
	{
		MessageBox(L"���ļ�ʧ��",L"��ʾ",MB_OK);
		return;
	}
	char r_show[256] = {0};
	print_hex(r_show,sign.r,32);
	fwrite(r_show,1,64,fp_r);
	fclose(fp_r);
	SetDlgItemText(IDC_Sign_r,A2W(r_show));

	//д��sֵ�� ��ʾ
	FILE *fp_s = NULL;
	if (NULL == (fp_s = fopen("C://sign_s.txt","w+")))
	{
		MessageBox(L"���ļ�ʧ��",L"��ʾ",MB_OK);
		return;
	}
	char s_show[256] = {0};
	print_hex(s_show,sign.s,32);
	fwrite(s_show,1,64,fp_s);
	fclose(fp_s);
	SetDlgItemText(IDC_Sign_s,A2W(s_show));

	MessageBox(L"ǩ���ɹ���ǩ��ֵ�����sign_s.txt��sign_r.txt��",L"��ʾ",MB_OK);







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
	// TODO:  ����ÿؼ��� RICHEDIT �ؼ���������
	// ���ʹ�֪ͨ��������д CDialogEx::OnInitDialog()
	// ���������� CRichEditCtrl().SetEventMask()��
	// ͬʱ�� ENM_CHANGE ��־�������㵽�����С�

	// TODO:  �ڴ���ӿؼ�֪ͨ����������
}


void CSM2_Sign_VerifyDlg::OnEnChangeSigns()
{
	// TODO:  ����ÿؼ��� RICHEDIT �ؼ���������
	// ���ʹ�֪ͨ��������д CDialogEx::OnInitDialog()
	// ���������� CRichEditCtrl().SetEventMask()��
	// ͬʱ�� ENM_CHANGE ��־�������㵽�����С�

	// TODO:  �ڴ���ӿؼ�֪ͨ����������
}


void CSM2_Sign_VerifyDlg::OnEnChangeEdit4()
{
	// TODO:  ����ÿؼ��� RICHEDIT �ؼ���������
	// ���ʹ�֪ͨ��������д CDialogEx::OnInitDialog()
	// ���������� CRichEditCtrl().SetEventMask()��
	// ͬʱ�� ENM_CHANGE ��־�������㵽�����С�

	// TODO:  �ڴ���ӿؼ�֪ͨ����������
}


void CSM2_Sign_VerifyDlg::OnEnChangeEdit5()
{
	// TODO:  ����ÿؼ��� RICHEDIT �ؼ���������
	// ���ʹ�֪ͨ��������д CDialogEx::OnInitDialog()
	// ���������� CRichEditCtrl().SetEventMask()��
	// ͬʱ�� ENM_CHANGE ��־�������㵽�����С�

	// TODO:  �ڴ���ӿؼ�֪ͨ����������
}

//ѡ����֤�ļ�
void CSM2_Sign_VerifyDlg::OnBnClickedButton3()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CString FilePathName;
	CFileDialog dlg(TRUE,
		NULL,
		NULL,
		OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,
		(LPCTSTR)_TEXT("�ı��ļ�(*.txt)|*.txt|ALL Files(*.*)|*.*||"),
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
	// TODO:  ����ÿؼ��� RICHEDIT �ؼ���������
	// ���ʹ�֪ͨ��������д CDialogEx::OnInitDialog()
	// ���������� CRichEditCtrl().SetEventMask()��
	// ͬʱ�� ENM_CHANGE ��־�������㵽�����С�

	// TODO:  �ڴ���ӿؼ�֪ͨ����������
}


void CSM2_Sign_VerifyDlg::OnEnChangeEdit7()
{
	// TODO:  ����ÿؼ��� RICHEDIT �ؼ���������
	// ���ʹ�֪ͨ��������д CDialogEx::OnInitDialog()
	// ���������� CRichEditCtrl().SetEventMask()��
	// ͬʱ�� ENM_CHANGE ��־�������㵽�����С�

	// TODO:  �ڴ���ӿؼ�֪ͨ����������
}

//ѡ��r
void CSM2_Sign_VerifyDlg::OnBnClickedButton4()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CString FilePathName;
	CFileDialog dlg(TRUE,
		NULL,
		NULL,
		OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,
		(LPCTSTR)_TEXT("�ı��ļ�(*.txt)|*.txt|ALL Files(*.*)|*.*||"),
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
	// TODO:  ����ÿؼ��� RICHEDIT �ؼ���������
	// ���ʹ�֪ͨ��������д CDialogEx::OnInitDialog()
	// ���������� CRichEditCtrl().SetEventMask()��
	// ͬʱ�� ENM_CHANGE ��־�������㵽�����С�

	// TODO:  �ڴ���ӿؼ�֪ͨ����������
}


void CSM2_Sign_VerifyDlg::OnBnClickedButton5()
{
	// TODO: �ڴ���ӿؼ�֪ͨ���������롿
	CString FilePathName;
	CFileDialog dlg(TRUE,
		NULL,
		NULL,
		OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,
		(LPCTSTR)_TEXT("�ı��ļ�(*.txt)|*.txt|ALL Files(*.*)|*.*||"),
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

///y��֤����
void CSM2_Sign_VerifyDlg::OnBnClickedVerify()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	UpdateData(TRUE);
	USES_CONVERSION;


	typedef struct 
	{
		BYTE *message;
		int message_byte_length;
		BYTE *ID;
		int ENTL;
		BYTE k[MAX_POINT_BYTE_LENGTH];  //ǩ���в��������

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


	//������Ҫ�Ĳ���
	////////////////////////////////////

	char *sm2_param_fp_256[] = {
		//ʾ��2��Fp-256���� 
		//����p�� 
		"8542D69E" "4C044F18" "E8B92435" "BF6FF7DE" "45728391" "5C45517D" "722EDB8B" "08F1DFC3",
		//ϵ��a�� 
		"787968B4" "FA32C3FD" "2417842E" "73BBFEFF" "2F3C848B" "6831D7E0" "EC65228B" "3937E498",
		//ϵ��b�� 
		"63E4C6D3" "B23B0C84" "9CF84241" "484BFE48" "F61D59A5" "B16BA06E" "6E12D1DA" "27C5249A",
		//����G = (x;y)����׼�Ϊn�� 
		//����x�� 
		"421DEBD6" "1B62EAB6" "746434EB" "C3CC315E" "32220B3B" "ADD50BDC" "4C4E6C14" "7FEDD43D",
		//����y�� 
		"0680512B" "CBB42C07" "D47349D2" "153B70C4" "E5D7FDFC" "BFA36EA1" "A85841B9" "E46E09A2",
		//��n�� 
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
//  		MessageBox(L"���ļ�ʧ��",L"��ʾ",MB_OK);
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
	//��ȡr��s
	///////////////////////////////////////////////////
	FILE *fp_r = NULL;
	if (NULL == (fp_r = fopen(W2A(m_23),"r+")))
	{
		MessageBox(L"��r�ļ�ʧ��",L"��ʾ",MB_OK);
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


	if (0 != AscToHex(r_tmp,64,0,sign1.r))  	//�ַ���תʮ������
	{
		MessageBox(L"�ַ�ת��ʧ�ܣ�");
		return;
	}
	fclose(fp_r);

	FILE *fp_s = NULL;
	if (NULL == (fp_s = fopen(W2A(m_24),"r+")))
	{
		MessageBox(L"��s�ļ�ʧ��",L"��ʾ",MB_OK);
		return;
	}
	unsigned char s_tmp[64] = {0};
	fread(s_tmp,64,1,fp_s);
	if (0 != AscToHex(s_tmp,64,0,sign1.s))  	//�ַ���תʮ������
	{
		MessageBox(L"�ַ�ת��ʧ�ܣ�");
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
		  MessageBox(L"��ϲ����֤�ɹ���",L"��ϲ",MB_OK);
	  else
		  MessageBox(L"���ź�����֤ʧ�ܣ������ԣ�",L"�ź�",MB_OK);

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
