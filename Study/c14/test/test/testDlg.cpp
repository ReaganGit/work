
// testDlg.cpp : implementation file
//

#include "stdafx.h"
#include "test.h"
#include "testDlg.h"
#include "afxdialogex.h"
#include <list>
#include <numeric>
#include <algorithm>
#include <iostream>
//#include <list>
//#include <numeric>
#include <random>
#include <vector>

#include <thread>
#include <mutex>
#include <regex>

#include<functional>
#include <bitset>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CAboutDlg dialog used for App About

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Implementation
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CtestDlg dialog



CtestDlg::CtestDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_TEST_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CtestDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CtestDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDOK, &CtestDlg::OnBnClickedOk)
	ON_BN_CLICKED(IDOK2, &CtestDlg::OnBnClickedSTDBind)
	ON_BN_CLICKED(IDOK3, &CtestDlg::OnBnClickedOk3)
END_MESSAGE_MAP()


// CtestDlg message handlers

BOOL CtestDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
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

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// TODO: Add extra initialization here

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CtestDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CtestDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CtestDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}









//////////////////////////////////////////////////////////////////////////////////////
//C++11 ��Ҫ�ڶ��̡߳����ͱ�̡�ͳһ��ʼ���Լ����ܱ��ּ�ǿ���˸���

//1�������� nullptr ���������ָ��
void fun(int a)
{
	TRACE0("come here��");

}
void fun(char *a)
{
	TRACE0("come here");

}

int incr(int & value)
{
	++value;
	return value;
}
//2����ֵ����  �ƶ�������Ҫ���߱����������׳��쳣���Դﵽ���׼�����
int incr(int && value)
{
	++value;
	return value;
}

//8�����߳�
void foo(int i)
{
	//�����������������ǽ��������ǰ�������⣬��������Դ����˷��գ����ǿ��Կ�����һ������ͨ��������������
	std::mutex m;
	m.lock();
	CString str;
	str.Format(_T("\n MutilThread str value:%d \n"), i);
	OutputDebugString(str);
	m.unlock();

	//ͨ��������������
	static std::mutex static_m;
	std::lock_guard<std::mutex> lock(static_m);
	OutputDebugString(str);
}

//10��costexper�����û���֤����������캯���Ǳ����ڳ���
constexpr int GetFive() { return 5; }
bool adjacent(long x, long y) { return true; }

struct Test
{
	bool operator()(short x, short y) { return true; };
};

//22��Ԫ��� ������Щ���д������޸ı������������ĳ��򣬳�֮ΪԪ��̣�������Ϊ���Է����ڱ����������
//����ָ��������   ģ����Ҫ�����涨��
template<int B, int N>
struct Pow
{
	//recursive call and recombination
	enum { value = B*Pow<B, N - 1>::value };
};
template<int B>
struct Pow<B, 0>
{
	//N==0 condition of termination
	enum { value = 1 };
};

//23����ʼ���б���ֵ
std::vector<std::string> test()
{
	return{"1","2","3"};
}

//4 lambda expression
int GetBiger(double first, double second)
{
	double result = (first > second) ? first : second;
	//�ֲ�����������ڲ����б�����������ᱨ��
	auto func = [result] {return result; };
	return func();
}
//lambda�������ֵ���񣨼��������÷��ϣ�ʱ���봫ֵ������Ϊһ�£���lambda���ʽ���ɵ��������еĳ�Ա�����ڹ���ʱ
//�´���������оֲ���ʱ�����ĸ���������������£�����lambda�ڵ�ֵ��Ӱ�츸��������ֵ��ͬ�����ĺ����ֲ�����ֵҲ��Ӱ��lambda�ڵĲ���ֵ
void func_lamabda()
{
	//�����ڵľֲ�����
	size_t v1 = 42;
	//�������б�Ϊֵ���񡿣��ڴ���lambdaʱ��������ʱ���ù��캯�������Ѿ�����
	auto f2 = [v1] {return v1; };
	v1 = 0;
	//��Ϊ��ֵ�����������޸ĸ������ľֲ�����������Ӱ��lambda������ĳ�Ա����������j��ֵ��Ȼ��42��
	auto j = f2();//j == 42

	auto f3 = [v1] {return v1; };
	auto j1 = f3();

	//�����ò��� �ڴ���lambdaʱ�������ͣ���ʽΪ���÷����ڲ������ǰ��
	auto f4 = [&v1] {return v1; };
	v1 = 2;
	//��Ϊ�����ó�ʼ�������Ը��ľֲ�����ֵ��lambda���ʽ���ɵ�δ�����������ݳ�ԱҲ���Ÿı䣬���j2=2;
	auto j2 = f4();

	//����ʽ���� �������ܶ಻��һ����д��ȥ ����ʽ�����ñ��������ݺ��������ƶ����ǽ�Ҫ�õ��ı�����
	//��ʽ���������ַ�ʽ��
	//1����ʽֵ���� ֵ���� ����=��������Ҫ����ı��� =��ʾ����ֵ����
	auto f5 = [=] {return v1; };
	v1 = 0;
	auto j3 = f5();
	//2����ʽ���ò��񣬲���&��������Ҫ����ı��� &��ʾ�������ò���ʽ
	auto f6 = [&] {return v1; };
	v1 = 42;
	auto j4 = f6();
	//3�����ʹ����ʽ�������ʾ���� ��ʽ�������ע�⣺
	//3.1�������б��е�һ��Ԫ�ر�����һ��&��=
	//3.2����ʾ�����б�����Ĳ���ʽ����ʽ����ʽ��ͬ���粶���б�д��auto f7=[&,&v2]�������ʽ���Ǵ���ġ�
	size_t v2 = 30;
	auto f7 = [&, v2] {return v1 + v2; };
	v1 = 0;
	auto j5 = f7();

	//���ɱ�lambda�� �����ʽ��һ��ֵ�����Ļ���lambda�ǲ���ı����ڵĳ�ʼ��ֵ
	//1��
	v1 = 42;
	auto f8 = [v1] {return v1; };//{return ++v1; }�������ᱨ����ʾ�����ǿ��޸ĵ���ֵ����ȷʵ��Ҫ�޸ģ�������mutable.
	v1 = 0;
	auto j6 = f8();
	//��mutable ����explicit ��explicit�ؼ��ֱ��������ڹ��캯����ʹ�ã������м�������������1�����캯������ֻ�������
	//һ���вΣ���Ȼ���������3������������Ĭ��ֵҲ�ǿ��Եġ�2��explicitֻ�������ڶ��� ��explicit A::A(int a)�������
	//��������explicit��ֹ������ʽת��
	//mutable ��ĳ���ݶ����mutableʱ�������κ�ʱ���������Ըı䣬����const�ࡪ��������ʵ��const��ֻ�ܵ���const��Ա����
	//�ͳ�Ա������mutableֻ�������ڷ�const �ı��������mutable const int a;���ǲ�������ġ�����ؼ����ƻ��˷�װ�ԣ������á�
	//volatile ���߱�������Ҫ�Ż��ñ���
	v1 = 42;
	auto f9 = [v1]()mutable {return ++v1; };//ֵ����,�����б�ʹΪ�� ҲҪ����()������벻����
	v1 = 0;
	auto j7 = f9();
	//2�������ǲ������ò��񣬱���һ���κ�ʱ�򶼿��Ըı䣬�ı�const�������⡣
	v1 = 42;
	auto f10 = [&v1]() {return ++v1; };
	v1 = 0;
	auto j8 = f10();
	const size_t v3 = 42;
//	auto f11 = [&v3]() {return ++v3; };//{return ++v3; };������� v3 const 
//	v2 = 0;
//	auto j9 = f11();

	//��ָ��lambda�������͡�һ��lambda���ݱ���ƶϷ������ͣ���û�з������ͷ���void ���磺
	auto f12 = [](int i) {i > 0 ? i : -i; };//�ⲻ����������ͼ
	auto f13 = [](int i)->int { if (i > 0) return i; else return -i; };
}

void CtestDlg::OnBnClickedOk()
{
	//1�������� nullptr ���������ָ��
	fun(0);
	char * pp = nullptr;
	fun(pp);

	//2����ֵ����  �ƶ�������Ҫ���߱����������׳��쳣���Դﵽ���׼�����
	int rightValue = 0;
	int &ri = rightValue;
	int &&rri = ri + 1;

	mystring mystr1;
	mystring mystr2;
	mystr1 = std::move(mystr2);

	std::string str = "Hello";
	std::vector<std::string> v;

	// uses the push_back(const T&) overload, which means
	// we'll incur the cost of copying str
	v.push_back(str);
	//std::cout << "After copy, str is \"" << str << "\"\n";

	// uses the rvalue reference push_back(T&&) overload,
	// which means no strings will copied; instead, the contents
	// of str will be moved into the vector.  This is less
	// expensive, but also means str might now be empty.
	v.push_back(std::move(str));
	//std::cout << "After move, str is \"" << str << "\"\n";
//	std::cout << "The contents of the vector are \"" << v[0]
	//	<< "\", \"" << v[1] << "\"\n";

	int a = 10, b = 20;
	int re1 = incr(a);
	int re2 = incr((a + b));
	int re3 = incr(3);

	//3���Զ��ƶ����� auto �� ���ͻ�ȡ decltype
	auto x = incr(10);
	decltype(x) y = x;

	//4��lambda���ʽ������������������ʽ��[captures](params)->ret{Statments;}
	//[]����ȡ�κα���
	//[&]��ȡ�ⲿ�����������б���������Ϊ�����ں�������ʹ��
	//[=]��ȡ�ⲿ�����������б�����������һ���ں�������ʹ��
	//[=,&foo]��ȡ�ⲿ�����������б�����������һ���ں�������ʹ�ã����Ƕ�foo����ʹ������
	//[bar]��ȡbar�������ҿ���һ���ں�������ʹ�ã�ͬʱ����ȡ��������
	//[&bar]��ȡ&bar����������Ϊ�����ں�������ʹ�ã�ͬʱ����ȡ��������
	//[this]��ȡ��ǰ���е�thisָ�룬����Ѿ�ʹ����&����=��Ĭ����Ӵ���
	//params���β�
	//���� []()->int{return 1;}
	auto retValue = []()->int {return 1; };
	auto  yy = incr(retValue());
	decltype(yy) yyy = incr(retValue());
	auto basiclambda = [] {TRACE0("come here"); };
	basiclambda();
	auto biger = GetBiger(2, 3);
	func_lamabda();

	//5��default and delete ���÷�
	class A
	{
		A() = default;//ָ��ʹ��Ĭ�Ϲ��캯��
		A(const A&) = delete;//ָ�������ÿ������캯��
		virtual ~A() = default;//ָ��ʹ��Ĭ����������
	};

	//6��override and final���η�
	//override ָ���鷽�������ض����Ƕ����µ�ͬ�������������η����±������ϸ��飬������Ϊ��������ͬ������ʧ��
	//final ������ͷ�������ʾ���ε��಻������Ϊ����������ء����η���ʱ��ʾ�˷���Ϊ����ʵ�֣����ܱ��κ�����������
	struct Base
	{
		virtual void some_func(float){}
	};
	struct Derived:Base
	{
		virtual void some_func(int)  {}
		virtual void some_func(float) override {}
	};


	//7���µ� for ���
	std::list<int> ls;
	for (int i=0;i<10;++i)
		ls.push_back(('a'+i));
	for (auto i : ls)
		TRACE1("\nls->i=%d", i);

	class ar
	{
		int *data, n;
	public:
		ar() :data(nullptr), n(0) {}
		ar(const ar& a) { n = a.n; data = new int[n]; for (int i = 0; i < n; ++i) data[i] = a.data[i]; }
		ar(ar&& a) :data(a.data), n(a.n) { a.data = nullptr; a.n = 0; }
		ar(int *a, int len) :n(n) { data = a; a = nullptr; }
		~ar() { delete[]data; data = nullptr; n = 0; }
		ar & operator= (const ar& a) { n = a.n; data = new int[n]; for (int i = 0; i < n; ++i)data[i] = a.data[i]; return *this; }
		ar & operator= (ar && a) { if (data)delete[]data; data = a.data; n = a.n; a.data = nullptr; a.n = 0; return *this; }
		const int *begin()const { return data; }
		int * begin() { return data; }
		const int *end()const { return nullptr; }
		int *end() { return data + n; }
	};

	int n = 5;
	int *an = new int[n];
	//for (int i = 0; i < n; i++)
	//	an[i] = i + 1;
	std::iota(an,an+n,0);
	ar arr(an, n);
	for each(int i in arr)
		TRACE1("arr[i]=%d\n",i);

	//�޸�������ֵ*2
	int my_array[5] = {1,2,3,4,5};
	for (int &x : my_array)
	{
		x *= 2;
	}


	//8�����߳�
	std::thread th(foo, 3);
	th.join();//�ȴ�th�߳�ִ�н���

	class threadAr
	{
	public:
		void foo(int i) 
		{
			CString str;
			str.Format(_T("\n MutilThread str value:%d \n"), i);
			OutputDebugString(str);
		}
	};

	threadAr arrr;
	//����ĳ������ĳ�Ա����������������
	std::thread th1(&threadAr::foo,&arrr, 6);
	th1.join();
	//
	std::thread th2([&arrr]() {arrr.foo(9); });//lambda ���ʽ
	th2.join();

	//9���߳���ʱ
	std::this_thread::sleep_for(std::chrono::seconds(1));
	std::this_thread::sleep_for(std::chrono::microseconds(10));
	std::this_thread::sleep_until(std::chrono::system_clock::now() + std::chrono::seconds(1));

	//10��costexper�����û���֤����������캯���Ǳ����ڳ���
	//constexpr int GetFive() { return 5; }
	int some_value[GetFive() + 5];//����10����������
	constexpr double  forceOfGravity = 9.8;
	constexpr double  moonGravity = forceOfGravity / 6.0;

	//11��ģ���ʵ����
	//template class std::vector<threadAr>;
	//ģ�岻Ҫ�ڸõ�Ԫʵ����
	//extern template class std::vector<MyClass>;
	//�����﷨���߱���������Ҫ�ڸñ��뵥Ԫ����ģ��ʵ����

	//12��ͳһ��ʼ�� 	std::initializer_list,���������ɱ����
	class SequenceClass
	{
	public:
		SequenceClass(std::initializer_list<int>list) 
		{
			CString str;
			for (auto beg = list.begin(); beg != list.end(); ++beg) 
			{
				str.Format(_T("list:%d "),*beg);
				OutputDebugString(str);
			}
			str = _T("\n");
			OutputDebugString(str);
		};
	};
	SequenceClass someValue = {1,2,3,4};
	SequenceClass someValue1 = { 1,2,3,4,5,6,7 };
	struct MyStruct
	{
		int x;
		float y;
	};
	MyStruct var1{5,3.2f};

	//13����������� ��β����
	//template<typename LHS,typename RHS>
	//Ret AddingFunc(const LHS &lhs,const RHS &rhs){return lhs+rhs;} //Ret�����ͱ����ǣ�lhs+rhs��
	//����ʹ��decltype ����������Ȼ���У���Ϊ�ڶ���ǰ�Ѿ�������lhs and rhs,����ֱ����������������벿��lhs\rhs��������
	//template<typename LHS,typename RHS>
	//decltype(lhs + rhs) AddingFunc(const LHS &lhs, const RHS &rhs) { return lhs + rhs; }
	//������β�������
	//template<typename LHS,typename RHS>
	//auto AddingFunc(const LHS &lhs, const RHS &rhs)->decltype(lhs + rhs) { return lhs + rhs; }

	//14��C++11�����캯�������������캯����������������ί�л�ת�ӣ�delegation��  
	class SomeType
	{
	private:
		int number;
		std::string name;
		SomeType(int i, const std::string&s) :number(i), name(s) {}
	public:
		SomeType() :SomeType(0, "invalid") {}
		SomeType(int i) :SomeType(i, "guest") {}
		SomeType(std::string &s) :SomeType(1, s) {}
	};

	//15������ͨ�������﷨��ɳ�ʼ��
	class MyClass
	{
	public:
		MyClass() {}
		explicit MyClass(int iNewValue) :iValue(iNewValue) {}
		~MyClass() {}

	private:
		int iValue = 5;

	};

	//16��ö���� ���ⲻ��ȷ
	enum class Enumeration
	{
		val1,
		val2,
		val3 = 100,
		val4 ,//val4= 101 ö���޷���˽ת�����޷��������Ƚ� Enumeration::Val4 == 101�ᴥ���������
	};

	//17���䳤ģ�����
	//template<typename ... Values> class tuple; ģ����tuple�����ܽ��ܲ��޸�����typename��Ϊ����ģ������β�

	//18��������ʽ
	const char *reg_esp = "[,.\\t\\n;:]";//�ָ���Ԫ�б�
	std::regex rgx(reg_esp);
	std::cmatch match;
	const char *target = ";Polytechnic,;:\t University of Turin";
	if (regex_search(target,match,rgx))
	{
		const size_t n = match.size();
		for (size_t a=0;a<n;a++)
		{
			std::string str(match[a].first,match[a].second);
			CString str1= L"CString Regex str  ";
			str1 += str.c_str();
			OutputDebugString(str1);
		}
	}

	//19������ָ��
	{
		std::shared_ptr<double> p_first(new double);
		{
			std::shared_ptr<double> p_copy = p_first;
			std::weak_ptr<double> p_weakPtr = p_copy;
			*p_copy = 21.2;
		}//��ʱ��p_copy�ᱻ���٣�
	}//��ʱ��p_firstҲ�ᱻ����

	//20�������uniform_int_distribution(��ɢ�Ծ��ȷֲ�)\bernoulli_distribution(��Ŭ���ֲ�)\geometric_distribution(���ηֲ�)
	//poisson_distribution(�����ɷֲ�)/binomial_distribution(����ֲ�)/uniform_real_distribution(��ɢ�Ծ��ȷֲ�)
	//exponential_distribution(ָ���ֲ�)/normal_distribution����̬�ֲ���/gamma_distribution��٤��ֲ���
	std::uniform_int_distribution<int> distrbution(0, 99);//����ɢ�;��ȷֲ�����int���������Χ��0-99
	std::mt19937 engine;//�����������������
	auto generator = std::bind(distrbution, engine);//����bind���������������ͷֲ���ϳ�һ��������������
	int random = generator();//���������


	//21����̬���������װ�� ���ƺ���ָ�뵫�ֲ�����ָ��������ֻҪ�ܱ����ã��������
	//���װ�����ݵĶ����Զ�̬���������װ����֮������ָ�롢��Ա����ָ���º�����
	std::function<int(int, int)>func;//����ģ����function������װ��
	std::plus<int>add;//plus������Ϊtemplete<class T>T plus(T,T) ���add���ͱ��� int add(int x,int y)
	func = add;//���У�add�βκͷ���������func���

	int a1 = func(1, 2);//ע�⣬����װ��funcû�вο����κκ������ᶪ��std::function_call����
	std::function<bool(short, short)>func2;
	//bool adjacent(long x, long y) { return true; }
	if (!func2)//��Ϊ��δ��ֵ��func2�κκ�����������Ϊ��
	{
		func2 = adjacent;//���У�adjacent���β��뷵������ͨ������ת����func2���
	}


	Test car;
	func = std::ref(car);//ģ����std::ref�ش�һ��struct car ���Ա����operator�İ�װ

	func = func2;//���У�func2 �β��뷵�����Ϳ�ͨ������ת������func���

	//22��Ԫ��� ������Щ���д������޸ı������������ĳ��򣬳�֮ΪԪ��̣�������Ϊ���Է����ڱ����������
	//����ָ��������   ģ����Ҫ�����涨��
	//template<int B,int N>
	//struct Pow
	//{
	//	//recursive call and recombination
	//	enum {value = B*Pow<B,N-1>::value};
	//};

	//template<int B>
	//struct Pow<B, 0>
	//{
	//	//N==0 condition of termination
	//	enum { value =1	};
	//};
	int quartic_of_three = Pow<3, 4>::value;


	//23����ʼ���б���ֵ
	{
		std::vector<std::string> temp;
		temp = test();
	}

	//24��bind() ����ʵ�֣�OnBnClickedSTDBind

	//25��mem_fn
	std::vector<std::string> svec;
	svec.push_back("abc");
	auto f = mem_fn(&std::string::empty);//f����һ��string����һ��string*
	f(*svec.begin());
	f(&svec[0]);

	//25��bitset���� #include <bitset>
	std::bitset<128> bitvec(1U);//128λ �����λ1 ����0

	CDialogEx::OnOK();
}

int TestFunc(int a, char c, float f)
{
	CString str;
	str.Format(_T("%d,%d,%f\n"),a,c,f);
	OutputDebugString(str);
	return a;
}
void CtestDlg::OnBnClickedSTDBind()
{
	//std::bind, bind ������һ���ӳټ����˼�룬���԰���ͨ������ȫ�ֺ�������̬�������ྲ̬�������������Ա����
	//#include <functional>
	//���£�bind�ܹ��ڰ�ʱ���ͬʱ��һ���ֲ�����δ�ṩ������ʹ��ռλ����ʾ��Ȼ��������ʱ����ʵ�ʵĲ���ֵ��
	//�󶨵Ĳ���������ֵ���ݷ�ʽ���ݸ����庯����ռλ�����������ô���
	auto bindFun1 = bind(TestFunc,std::placeholders::_1,'A',100.1);
	bindFun1(10);

	auto bindFunc2 = bind(TestFunc, std::placeholders::_2, std::placeholders::_1, 100.1);
	bindFunc2('B',10);

	auto bindFunc3 = bind(TestFunc,std::placeholders::_2,std::placeholders::_3,std::placeholders::_1);
	bindFunc3(100.1,30,'C');

	auto bindFunc4 = std::bind(TestFunc,std::placeholders::_2,std::placeholders::_3,std::placeholders::_1);
	bindFunc4(100.1,30,'C');

	auto bindFunc5 = std::bind(TestFunc, std::placeholders::_3, std::placeholders::_2, std::placeholders::_1);
	bindFunc5(100.1, 30, 'C');

	//��̬��Ա������ʵ���Կ�����ȫ�ֺ��������Ǿ�̬��Ա������Ҫ����thisָ����Ϊ��һ������



}

//////////////////////////////////////////////////////////////////////////////////////////////////
//C++14 begin
//1�����͵�lambda����
struct unnamed_lambda
{
	template<typename T, typename U> 
	auto operator()(T x, U y) const { return x + y; }
};

//3���������������Ƶ�
auto Correct(int i)
{
	if (i == 1)
		return i; //�������ͱ��ƶ�Ϊint
	else
		return Correct(i - 1) + i;//��ȷ�����Ե���
}
//auto Wrong(int i)
//{
//	if (i != 1)
//		return Wrong(i - 1) + i;//���ܵ��ã�֮ǰû��return��䡣
//	else
//		return i;//�������ͱ��ƶ�Ϊint
//}

int && f()
{
	return 0;
}

void CtestDlg::OnBnClickedOk3()
{
	//1�����͵�lambda����
	//C++11 lambda������ʽ��Ҫ������Ϊ�������ͣ�C++14�ſ�����һҪ������lambda������ʽ����������ʹ��auto
	auto lambda = [](auto x, auto y) {return x + y; };
	auto f1 = lambda;
	auto j1 = f1(2,3);
	//����lambda������ѭģ������Ƶ��������ϴ�������������������ͬ
	/*struct unnamed_lambda
	{
		template<typename T,typename U>
		auto operator()(T x, U y) const { return x + y; }
	};//ģ����Ҫ����������
	*/
	auto lambda1 = unnamed_lambda();
	auto f2 = lambda1;
	auto j2 = f2(3, 4);

	//2��lambda������ʽ
	//C++11 lambda�������ܹ���ֵ���������á�����������������������ı���������ζ��lambda��ֵ��Ա��������move-only
	//�����͡�C++14�������Ա������ʽ��ʼ�����⼴������capture by value-move��Ҳ��������������lambda��Ա��������Ҫ
	//�����������һ��������Ӧ���ֵı���
	//
	//ͨ��ʹ�ó�ʼ�����ʽ��ɣ�
	//lambda����lambda�ķ���ֵ��1��˵��value����ʼ��Ϊ1���������Ĳ������͸��ݳ�ʼ�����ʽ�ƶϣ��ƶϷ�ʽ��auto����������ͬ
	auto lambda2 = [value = 1]{ return value; };
	//
	//ʹ�ñ�׼����std::move����ʹ֮������ͨ��move����
	auto ptr = std::make_unique<int>(10);
	auto lambda3 = [ptr = std::move(ptr)]{ return *ptr; };
	//����ptr = std::move(ptr)ʹ��������ptr����һ��ʹ��������һ���µı��������ڲ��񲿷���������������������ڣ�����
	//�ڶ���ptr��ʾ֮ǰ��lambda֮�������ı�����

	//3���������������Ƶ�
	//C++11����lambda��������return�����ʽ�����ƶϷ������ͣ�C++14Ϊһ�㺯��Ҳ�ṩ��������������⣬����չ��ԭ��
	//����ʹ�ú����岢����{return expression;}��ʽ�ĺ���Ҳ����ʹ�÷��������Ƶ�
	auto DeduceReturntype();//���������ɱ������ƶϣ�����ж��return��䣬��Щ���ʽ��������ƶ�Ϊ��ͬ������
	//
	//ʹ�÷��������Ƶ��ĺ�������ǰ�����������ڶ���֮ǰ������ʹ�á�
	//�����ĺ������Դ��ڵݹ飬���ݹ���ñ����ں��������е�����һ��return���֮��
	Correct(3);
	//auto Correct(int i)
	//{
	//	if (i == 1)
	//		return i; //�������ͱ��ƶ�Ϊint
	//	else
	//		return Correct(i - 1) + i;//��ȷ�����Ե���
	//}
	//
	//auto Wrong(int i)
	//{
	//	if (i != 1)
	//		return Wrong(i - 1) + i;//���ܵ��ã�֮ǰû��return��䡣
	//	else
	//		return i;//�������ͱ��ƶ�Ϊint
	//}

	//4����һ�������ƶ�
	//C++11�����������ƶϣ�auto���ݸ������ʽ�������к������͵ı�����decltype���Լ���������ʽ�����͡�����decltype
	//��auto�ƶ����͵ķ�ʽ�ǲ�ͬ�ģ��ر�أ�auto�����ƶϳ����������ͣ��ͺ���ʹ����std::remove_referenceһ������
	//auto&&�����ƶϳ��������͡�Ȼ��decltype���Ը��ݱ��ʽ��ֵ���ͱ��ʽ�������ƶϳ����û���������ͣ�
	int i=0;
	//int && f(); //���涨��
	auto x3a = i;//x3a������int
	decltype(i) x3d = i;//x3d������int
	auto x4a = (i);//x4a������int
	decltype((i)) x4d = (i);//x4d������ int&
	auto x5a = f(); //x5a������int
	decltype(f()) x5d = f();//x5d������int&&
	//
	//C++14������decltype(auto)�﷨����������ʾָ����Ϊdecltype�����ı��ʽ����ʹ��decltype���ڸ������ʽ���ƶϹ���
	//decltype(auto)���﷨Ҳ�������ڷ��������Ƶ���ֻ��Ҫ��decltype(auto)����auto.

	//5�����ɵ�constexpr����
	//C++11������constexpr������������ĺ��������ڱ�����ִ�С����Ƿ���ֵ�������������������ʽ�ĳ��ϣ���ģ��ķ����Ͳ�����
	//Ȼ��C++11Ҫ��constexpr����ֻ����һ���������صı��ʽ��Ҳ���Ի�����static_assert������������䣬�������������ͺ��٣�
	//C++14��������Щ���ƣ�����Ϊconstexpr�ĺ��������Ժ���һ�����ݣ�
	//�κ����������� 
	//    static��thread_local����
	//    û�г�ʼ���ı�������
	//������֧���if��switch. goto�ǲ�����ġ�
	//����ѭ����䣬�������ڷ�Χ��forѭ����
	//���ʽ���Ըı�һ�������ֵ��ֻ��ö�����������ڳ������ʽ�����ڿ�ʼ����������constexpt�������κη�const�Ǿ�̬��Ա�������á�
	//���÷�cconstexpr������Ȼ�����ơ�

	//6������ģ��
	//���Դ�������ģ�壬�����ػ����ڣ�ͨ����ģ����������ڱ���ģ�������Ͷ���

	//7���ۺ����Ա��ʼ��
	//C++14�ſ������ƣ���������ų�ʼ���б��ṩ�ò�����ʼ����member initializer���ʼ������

	//8��������������
	//ʹ��ǰ׺0b��0B 

	//9�����ַ�Ϊ��
	auto integer_literal = 100'0000;
	auto floating_point_literal = 1.797'693'134'862'315'7E+308;
	auto binary_literal = 0b0100'1100'0110;

	//10������Ļ��������
	//C++14�����˹���Ļ��������Ӧ�Ĺ����������ѡ���������std::shared_mutex,�����ں���������std::timed_mutex���Ƶ����ԣ�
	//std::shared_timed_mutex��Ϊ�����ʵ�����
	
	//11��Ԫ�����ı���
	
	//12�����������е��칹����
	//std::less<> �� std::greater<>�����칹����

	//13����׼�Զ���������
	//��s��,���ڴ�������std::basic_string����
	//��h������min����"s"����ms������us������ns�������ڴ�����Ӧ��std::chrono::durationʱ����
	using namespace std::literals;
	std::string str = "hello world"s;
	std::chrono::seconds dur = 60s;
	//������s���������ţ���Ϊ��ʾ�ַ�����ֻ�ܶ��ַ��������������ʾ���ֻ�������

	//14��ͨ������Ѱַ��Ԫ��
	//c++11������std::tuple��������ͬ���͵�ֵ�ľۺ����ñ����ڳ���������C++14������ʹ�����ʹ��泣���������Ӷ�Ԫ��
	//��ȡ��������Ԫ�麬�ж���һ��������͵Ķ��󣬽�������������
	std::tuple<std::string, std::string, int> t("foo","bar",7);
	int ii = std::get<int>(t); //i==7
	int j = std::get<2>(t);// same as before :j==7
//	std::string s = std::get<std::string>(t);//compiler error due to ambiguity 
	std::tuple<std::string, int> t1("one string",7);
	std::string s_oneString = std::get<std::string>(t1);

	//15����С�ı�׼������
	//std::make_unique ������ std::make_shared һ��ʹ�ã����ڲ���std::unique_ptr����
	//std::is_final,����ʶ��һ��class�����Ƿ��ֹ���̳�
	//std::integral_constant������һ�����س���ֵ��operator().
	//ȫ��std::begin/std::end�������⣬������std::cbegin/std::cend�����������ܷ��س�����������constant iterators��

	//16���ѱ��Ƴ��򲻰�����c++14��׼����
	//16.1�������������չ
	//16.2��Optionalֵ
	//16.3��Concepts Lite
}
//C++14 end
//////////////////////////////////////////////////////////////////////////////////////////////////
