
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
	//Ĭ�Ϲ��캯��
	mystring() {};
	//�������캯��
	mystring(const mystring& str) {};
	//�ƶ����캯�� �ƶ�������Ҫnoexcept���߱����������׳��쳣���Դﵽ���׼�����
	mystring(mystring &&str) noexcept {};
	//��ֵ
	mystring & operator=(const mystring& str) { return /*static_cast<mystring>*/*this; };
	//�ƶ���ֵ
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
