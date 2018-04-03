
// SM2_Sign_VerifyDlg.h : 头文件
//

#pragma once


// CSM2_Sign_VerifyDlg 对话框
class CSM2_Sign_VerifyDlg : public CDialogEx
{
// 构造
public:
	CSM2_Sign_VerifyDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_SM2_SIGN_VERIFY_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnEnChangeEdit1();
	afx_msg void OnBnClickedsignfile();
	CString m_sign_file;
	afx_msg void OnBnClickedSign();
	afx_msg void OnEnChangeSignr();
	afx_msg void OnEnChangeSigns();
	CString m_Sign_r;
	afx_msg void OnEnChangeEdit4();
	CString m_Sign_e;
	afx_msg void OnEnChangeEdit5();
	afx_msg void OnBnClickedButton3();
	CString m_21;
	afx_msg void OnEnChangeEdit6();
	CString m_22;
	CString m_23;
	afx_msg void OnEnChangeEdit7();
	afx_msg void OnBnClickedButton4();
	afx_msg void OnEnChangeEdit8();
	CString m_24;
	afx_msg void OnBnClickedButton5();
	afx_msg void OnBnClickedVerify();
};
