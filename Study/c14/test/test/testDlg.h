
// testDlg.h : header file
//

#pragma once
#include <iostream>
#include <vector>
//#include <utility>
class mystring
{
	char *s;
	int len;
public:
	//默认构造函数
	mystring() {};
	//拷贝构造函数
	mystring(const mystring& str) {};
	//移动构造函数 移动语义需要noexcept告诉编译器不会抛出异常，以达到与标准库兼容
	mystring(mystring &&str) noexcept {};
	//赋值
	mystring & operator=(const mystring& str) { return /*static_cast<mystring>*/*this; };
	//移动赋值
	mystring & operator=(mystring && str) noexcept { return str; };
	~mystring() {};
};

// CtestDlg dialog
class CtestDlg : public CDialogEx
{
// Construction
public:
	CtestDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_TEST_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support


// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedSTDBind ();
	afx_msg void OnBnClickedOk3();
};
