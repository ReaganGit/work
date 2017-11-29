
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
//C++11 主要在多线程、泛型编程、统一初始化以及性能表现加强做了改善

//1、引入了 nullptr 用来代表空指针
void fun(int a)
{
	TRACE0("come here！");

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
//2、右值引用  移动语义需要告诉编译器不会抛出异常，以达到与标准库兼容
int incr(int && value)
{
	++value;
	return value;
}

//8、多线程
void foo(int i)
{
	//这个互斥锁，如果忘记解锁或解锁前出现问题，给其他资源造成了风险，与是可以看另外一个锁，通过析构函数解锁
	std::mutex m;
	m.lock();
	CString str;
	str.Format(_T("\n MutilThread str value:%d \n"), i);
	OutputDebugString(str);
	m.unlock();

	//通过析构函数解锁
	static std::mutex static_m;
	std::lock_guard<std::mutex> lock(static_m);
	OutputDebugString(str);
}

//10、costexper允许用户保证函数或对象构造函数是编译期常数
constexpr int GetFive() { return 5; }
bool adjacent(long x, long y) { return true; }

struct Test
{
	bool operator()(short x, short y) { return true; };
};

//22、元编程 对于那些自行创建或修改本身或其他程序的程序，称之为元编程，这种行为可以发生在编译或运行期
//计算指数的例子   模板需要在外面定义
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

//23、初始化列表返回值
std::vector<std::string> test()
{
	return{"1","2","3"};
}

//4 lambda expression
int GetBiger(double first, double second)
{
	double result = (first > second) ? first : second;
	//局部变量必须放在捕获列表，否则编译器会报错
	auto func = [result] {return result; };
	return func();
}
//lambda如果采用值捕获（即不带引用符合）时，与传值参数行为一致，由lambda表达式生成的新类型中的成员数据在构造时
//会拷贝父函数中局部临时变量的副本，在这种情况下，更改lambda内的值不影响父函数变量值，同样更改函数局部变量值也不影响lambda内的捕获值
void func_lamabda()
{
	//函数内的局部变量
	size_t v1 = 42;
	//【捕获列表为值捕获】，在创建lambda时（生成类时调用构造函数）就已经拷贝
	auto f2 = [v1] {return v1; };
	v1 = 0;
	//因为是值拷贝，所以修改父函数的局部变量，不会影响lambda生成类的成员变量，所以j的值仍然是42；
	auto j = f2();//j == 42

	auto f3 = [v1] {return v1; };
	auto j1 = f3();

	//【引用捕获】 在创建lambda时引用类型，格式为引用符号在捕获变量前面
	auto f4 = [&v1] {return v1; };
	v1 = 2;
	//因为是引用初始化，所以更改局部变量值，lambda表达式生成的未命名类内数据成员也跟着改变，结果j2=2;
	auto j2 = f4();

	//【隐式捕获】 当变量很多不想一个个写上去 用隐式捕获，让编译器根据函数体来推断我们将要用到的变量，
	//隐式捕获有三种方式：
	//1）隐式值捕获 值捕获 采用=代替我们要捕获的变量 =表示采用值捕获
	auto f5 = [=] {return v1; };
	v1 = 0;
	auto j3 = f5();
	//2）隐式引用捕获，采用&代替我们要捕获的变量 &表示采用引用捕获方式
	auto f6 = [&] {return v1; };
	v1 = 42;
	auto j4 = f6();
	//3）混合使用隐式捕获和显示捕获 隐式捕获必须注意：
	//3.1）捕获列表中第一个元素必须是一个&或=
	//3.2）显示捕获列表变量的捕获方式与隐式捕获方式不同，如捕获列表写成auto f7=[&,&v2]这个捕获方式就是错误的。
	size_t v2 = 30;
	auto f7 = [&, v2] {return v1 + v2; };
	v1 = 0;
	auto j5 = f7();

	//【可变lambda】 当表达式是一个值拷贝的话，lambda是不会改变其内的初始化值
	//1）
	v1 = 42;
	auto f8 = [v1] {return v1; };//{return ++v1; }编译器会报错，提示必须是可修改的左值，若确实需要修改，可以用mutable.
	v1 = 0;
	auto j6 = f8();
	//讲mutable 先提explicit ，explicit关键字必须在类内构造函数中使用，而且有几个限制条件：1、构造函数必须只允许接受
	//一个行参，当然，吗如果有3个，其他都带默认值也是可以的。2、explicit只能在类内定义 如explicit A::A(int a)这个定义
	//不被允许。explicit阻止数据隐式转换
	//mutable 当某数据定义成mutable时，无论任何时候他都可以改变，包括const类————事实上const类只能调用const成员变量
	//和成员函数。mutable只能作用于非const 的变量，如果mutable const int a;这是不被允许的。这个关键字破坏了分装性，很少用。
	//volatile 告诉编译器不要优化该变量
	v1 = 42;
	auto f9 = [v1]()mutable {return ++v1; };//值捕获,参数列表即使为空 也要带上()否则编译不过。
	v1 = 0;
	auto j7 = f9();
	//2）当我们采用引用捕获，变量一般任何时候都可以改变，改变const类型例外。
	v1 = 42;
	auto f10 = [&v1]() {return ++v1; };
	v1 = 0;
	auto j8 = f10();
	const size_t v3 = 42;
//	auto f11 = [&v3]() {return ++v3; };//{return ++v3; };编译错误 v3 const 
//	v2 = 0;
//	auto j9 = f11();

	//【指定lambda返回类型】一般lambda根据表达推断返回类型，如没有返回语句就返回void 但如：
	auto f12 = [](int i) {i > 0 ? i : -i; };//这不符合我们意图
	auto f13 = [](int i)->int { if (i > 0) return i; else return -i; };
}

void CtestDlg::OnBnClickedOk()
{
	//1、引入了 nullptr 用来代表空指针
	fun(0);
	char * pp = nullptr;
	fun(pp);

	//2、右值引用  移动语义需要告诉编译器不会抛出异常，以达到与标准库兼容
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

	//3、自动推断类型 auto 和 类型获取 decltype
	auto x = incr(10);
	decltype(x) y = x;

	//4、lambda表达式（匿名函数）完整格式：[captures](params)->ret{Statments;}
	//[]不截取任何变量
	//[&]截取外部作用域中所有变量，并作为引用在函数体中使用
	//[=]截取外部作用于中所有变量，并拷贝一份在函数体中使用
	//[=,&foo]截取外部作用域中所有变量，并拷贝一份在函数体中使用，但是对foo变量使用引用
	//[bar]截取bar变量并且拷贝一份在函数体中使用，同时不截取其他变量
	//[&bar]截取&bar变量并且作为引用在函数体中使用，同时不截取其他变量
	//[this]截取当前类中的this指针，如果已经使用了&或者=就默认添加此项
	//params是形参
	//举例 []()->int{return 1;}
	auto retValue = []()->int {return 1; };
	auto  yy = incr(retValue());
	decltype(yy) yyy = incr(retValue());
	auto basiclambda = [] {TRACE0("come here"); };
	basiclambda();
	auto biger = GetBiger(2, 3);
	func_lamabda();

	//5、default and delete 新用法
	class A
	{
		A() = default;//指定使用默认构造函数
		A(const A&) = delete;//指定不适用拷贝构造函数
		virtual ~A() = default;//指定使用默认析构函数
	};

	//6、override and final修饰符
	//override 指定虚方法的重载而不是定义新的同名函数，该修饰符导致编译器严格检查，避免因为函数名不同而重载失败
	//final 修饰类和方法，表示修饰的类不能再作为基类而被重载。修饰方法时表示此方法为最终实现，不能被任何派生类重载
	struct Base
	{
		virtual void some_func(float){}
	};
	struct Derived:Base
	{
		virtual void some_func(int)  {}
		virtual void some_func(float) override {}
	};


	//7、新的 for 语句
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

	//修改数组中值*2
	int my_array[5] = {1,2,3,4,5};
	for (int &x : my_array)
	{
		x *= 2;
	}


	//8、多线程
	std::thread th(foo, 3);
	th.join();//等待th线程执行结束

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
	//调用某个对象的成员函数，可以这样：
	std::thread th1(&threadAr::foo,&arrr, 6);
	th1.join();
	//
	std::thread th2([&arrr]() {arrr.foo(9); });//lambda 表达式
	th2.join();

	//9、线程延时
	std::this_thread::sleep_for(std::chrono::seconds(1));
	std::this_thread::sleep_for(std::chrono::microseconds(10));
	std::this_thread::sleep_until(std::chrono::system_clock::now() + std::chrono::seconds(1));

	//10、costexper允许用户保证函数或对象构造函数是编译期常数
	//constexpr int GetFive() { return 5; }
	int some_value[GetFive() + 5];//产生10个整数阵列
	constexpr double  forceOfGravity = 9.8;
	constexpr double  moonGravity = forceOfGravity / 6.0;

	//11、模板非实例化
	//template class std::vector<threadAr>;
	//模板不要在该单元实例化
	//extern template class std::vector<MyClass>;
	//上面语法告诉编译器，不要在该编译单元将该模板实例化

	//12、统一初始化 	std::initializer_list,参数个数可变情况
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

	//13、返回新类别 拖尾返回
	//template<typename LHS,typename RHS>
	//Ret AddingFunc(const LHS &lhs,const RHS &rhs){return lhs+rhs;} //Ret的类型必须是（lhs+rhs）
	//以下使用decltype 来声明，依然不行，因为在定义前已经出现了lhs and rhs,函数直到剖析器解析到后半部分lhs\rhs才有意义
	//template<typename LHS,typename RHS>
	//decltype(lhs + rhs) AddingFunc(const LHS &lhs, const RHS &rhs) { return lhs + rhs; }
	//采用拖尾方法解决
	//template<typename LHS,typename RHS>
	//auto AddingFunc(const LHS &lhs, const RHS &rhs)->decltype(lhs + rhs) { return lhs + rhs; }

	//14、C++11允许构造函数调用其它构造函数，这种做法称作委托或转接（delegation）  
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

	//15、可以通过以下语法完成初始化
	class MyClass
	{
	public:
		MyClass() {}
		explicit MyClass(int iNewValue) :iValue(iNewValue) {}
		~MyClass() {}

	private:
		int iValue = 5;

	};

	//16、枚举类 避免不明确
	enum class Enumeration
	{
		val1,
		val2,
		val3 = 100,
		val4 ,//val4= 101 枚举无法隐私转换，无法与整数比较 Enumeration::Val4 == 101会触发编译错误
	};

	//17、变长模板参数
	//template<typename ... Values> class tuple; 模板类tuple对象能接受不限个数的typename作为他的模板参数形参

	//18、正则表达式
	const char *reg_esp = "[,.\\t\\n;:]";//分割字元列表
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

	//19、智能指针
	{
		std::shared_ptr<double> p_first(new double);
		{
			std::shared_ptr<double> p_copy = p_first;
			std::weak_ptr<double> p_weakPtr = p_copy;
			*p_copy = 21.2;
		}//此时，p_copy会被销毁，
	}//此时，p_first也会被销毁

	//20、随机数uniform_int_distribution(离散性均匀分布)\bernoulli_distribution(伯努利分布)\geometric_distribution(几何分布)
	//poisson_distribution(卜瓦松分布)/binomial_distribution(二项分布)/uniform_real_distribution(离散性均匀分布)
	//exponential_distribution(指数分布)/normal_distribution（正态分布）/gamma_distribution（伽马分布）
	std::uniform_int_distribution<int> distrbution(0, 99);//以离散型均匀分布产生int随机数，范围在0-99
	std::mt19937 engine;//建立随机数生成引擎
	auto generator = std::bind(distrbution, engine);//利用bind将随机数生成引擎和分布组合成一个随机数生成物件
	int random = generator();//产生随机数


	//21、多态函数对象包装器 类似函数指针但又不像函数指针狭隘，只要能被调用，且其参数
	//与包装器兼容的都可以多态函数对象包装器称之（函数指针、成员函数指针或仿函数）
	std::function<int(int, int)>func;//利用模板类function建立包装器
	std::plus<int>add;//plus被宣告为templete<class T>T plus(T,T) 因此add的型别是 int add(int x,int y)
	func = add;//可行，add形参和返回类型与func相符

	int a1 = func(1, 2);//注意，若包装器func没有参考到任何函数，会丢出std::function_call例外
	std::function<bool(short, short)>func2;
	//bool adjacent(long x, long y) { return true; }
	if (!func2)//因为尚未赋值与func2任何函数，此条件为真
	{
		func2 = adjacent;//可行，adjacent的形参与返回类型通过类型转换与func2相符
	}


	Test car;
	func = std::ref(car);//模板类std::ref回传一个struct car 其成员函数operator的包装

	func = func2;//可行，func2 形参与返回类型可通过类型转换而与func相符

	//22、元编程 对于那些自行创建或修改本身或其他程序的程序，称之为元编程，这种行为可以发生在编译或运行期
	//计算指数的例子   模板需要在外面定义
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


	//23、初始化列表返回值
	{
		std::vector<std::string> temp;
		temp = test();
	}

	//24、bind() 见该实现：OnBnClickedSTDBind

	//25、mem_fn
	std::vector<std::string> svec;
	svec.push_back("abc");
	auto f = mem_fn(&std::string::empty);//f接受一个string或者一个string*
	f(*svec.begin());
	f(&svec[0]);

	//25、bitset类型 #include <bitset>
	std::bitset<128> bitvec(1U);//128位 ，最低位1 其他0

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
	//std::bind, bind 本身是一种延迟计算的思想，可以绑定普通函数、全局函数、静态函数、类静态函数甚至是类成员函数
	//#include <functional>
	//如下，bind能够在绑定时候就同时绑定一部分参数，未提供参数则使用占位符表示，然后在运行时传入实际的参数值。
	//绑定的参数将会以值传递方式传递给具体函数，占位符将会以引用传递
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

	//静态成员函数其实可以看作是全局函数，而非静态成员函数需要传递this指针作为第一个参数



}

//////////////////////////////////////////////////////////////////////////////////////////////////
//C++14 begin
//1、泛型的lambda函数
struct unnamed_lambda
{
	template<typename T, typename U> 
	auto operator()(T x, U y) const { return x + y; }
};

//3、函数返回类型推导
auto Correct(int i)
{
	if (i == 1)
		return i; //返回类型被推断为int
	else
		return Correct(i - 1) + i;//正确，可以调用
}
//auto Wrong(int i)
//{
//	if (i != 1)
//		return Wrong(i - 1) + i;//不能调用，之前没有return语句。
//	else
//		return i;//返回类型被推断为int
//}

int && f()
{
	return 0;
}

void CtestDlg::OnBnClickedOk3()
{
	//1、泛型的lambda函数
	//C++11 lambda函数形式需要被声明为具体类型，C++14放宽了这一要求，运行lambda函数形式参数申明中使用auto
	auto lambda = [](auto x, auto y) {return x + y; };
	auto f1 = lambda;
	auto j1 = f1(2,3);
	//泛型lambda函数遵循模板参数推导规则，以上代码的作用与下面代码相同
	/*struct unnamed_lambda
	{
		template<typename T,typename U>
		auto operator()(T x, U y) const { return x + y; }
	};//模板需要申明在外面
	*/
	auto lambda1 = unnamed_lambda();
	auto f2 = lambda1;
	auto j2 = f2(3, 4);

	//2、lambda捕获表达式
	//C++11 lambda函数他能够过值拷贝、引用、捕获已在外层作用域申明的变量，这意味着lambda的值成员不可以是move-only
	//的类型。C++14允许捕获成员任意表达式初始化。这即允许了capture by value-move，也允许了任意申明lambda成员，而不需要
	//外层作用域有一个具有相应名字的变量
	//
	//通过使用初始化表达式完成：
	//lambda函数lambda的返回值是1，说明value被初始化为1，被申明的捕获类型根据初始化表达式推断，推断方式与auto申明变量相同
	auto lambda2 = [value = 1]{ return value; };
	//
	//使用标准函数std::move可以使之被用以通过move捕获
	auto ptr = std::make_unique<int>(10);
	auto lambda3 = [ptr = std::move(ptr)]{ return *ptr; };
	//申明ptr = std::move(ptr)使用了两次ptr，第一次使用申明了一个新的变量，但在捕获部分这个变量还不在作用域内，所以
	//第二个ptr表示之前在lambda之外申明的变量。

	//3、函数返回类型推导
	//C++11运行lambda函数根据return语句表达式类型推断返回类型，C++14为一般函数也提供了这个能力，此外，还拓展了原有
	//规则，使得函数体并不是{return expression;}形式的函数也可以使用返回类型推导
	auto DeduceReturntype();//返回类型由编译器推断，如果有多个return语句，这些表达式必须可以推断为相同的类型
	//
	//使用返回类型推导的函数可以前向申明，但在定义之前不可以使用。
	//这样的函数可以存在递归，但递归调用必须在函数定义中的至少一个return语句之后：
	Correct(3);
	//auto Correct(int i)
	//{
	//	if (i == 1)
	//		return i; //返回类型被推断为int
	//	else
	//		return Correct(i - 1) + i;//正确，可以调用
	//}
	//
	//auto Wrong(int i)
	//{
	//	if (i != 1)
	//		return Wrong(i - 1) + i;//不能调用，之前没有return语句。
	//	else
	//		return i;//返回类型被推断为int
	//}

	//4、另一种类型推断
	//C++11有两种类型推断，auto根据给出表达式产生具有合适类型的变量，decltype可以计算给出表达式的类型。但，decltype
	//和auto推断类型的方式是不同的，特别地，auto总是推断出非引用类型，就好像使用了std::remove_reference一样，而
	//auto&&总是推断出引用类型。然而decltype可以根据表达式的值类别和表达式的性质推断出引用或非引用类型：
	int i=0;
	//int && f(); //外面定义
	auto x3a = i;//x3a类型是int
	decltype(i) x3d = i;//x3d类型是int
	auto x4a = (i);//x4a类型是int
	decltype((i)) x4d = (i);//x4d类型是 int&
	auto x5a = f(); //x5a类型是int
	decltype(f()) x5d = f();//x5d类型是int&&
	//
	//C++14增加了decltype(auto)语法，允许不必显示指定作为decltype参数的表达式，而使用decltype对于给定表达式的推断规则
	//decltype(auto)的语法也可以用于返回类型推导，只需要用decltype(auto)代替auto.

	//5、放松的constexpr限制
	//C++11引入了constexpr函数概念，这样的函数可以在编译期执行。他们返回值可以用于期望常量表达式的场合（如模板的非类型参数）
	//然而C++11要求constexpr函数只含有一个将被返回的表达式（也可以还含有static_assert声明等其他语句，但允许的语句类型很少）
	//C++14放松了这些限制，申明为constexpr的函数将可以含有一下内容：
	//任何申明，除了 
	//    static或thread_local变量
	//    没有初始化的变量声明
	//条件分支语句if和switch. goto是不允许的。
	//所有循环语句，包括基于范围的for循环。
	//表达式可以改变一个对象的值，只需该对象的生命期在常量表达式函数内开始。包括对有constexpt申明的任何非const非静态成员函数调用。
	//调用非cconstexpr函数仍然受限制。

	//6、变量模板
	//可以创建变量模板，包括特化在内，通常的模板规则都适用于变量模板申明和定义

	//7、聚合体成员初始化
	//C++14放宽了限制，如果花括号初始化列表不提供该参数初始化，member initializer会初始化它。

	//8、二进制字面量
	//使用前缀0b或0B 

	//9、数字分为符
	auto integer_literal = 100'0000;
	auto floating_point_literal = 1.797'693'134'862'315'7E+308;
	auto binary_literal = 0b0100'1100'0110;

	//10、共享的互斥体和锁
	//C++14增加了共享的互斥体和相应的共享锁，起初选择的名字是std::shared_mutex,但由于后来增加与std::timed_mutex相似的特性，
	//std::shared_timed_mutex成为更合适的名字
	
	//11、元函数的别名
	
	//12、关联容器中的异构查找
	//std::less<> 与 std::greater<>允许异构查找

	//13、标准自定义字面量
	//“s”,用于创建各种std::basic_string类型
	//“h”、“min”、"s"、“ms”、“us”、“ns”，用于创建相应的std::chrono::duration时间间隔
	using namespace std::literals;
	std::string str = "hello world"s;
	std::chrono::seconds dur = 60s;
	//俩个‘s’互不干扰，因为表示字符串的只能对字符串字面操作，表示秒的只针对数字

	//14、通过类型寻址多元组
	//c++11引入了std::tuple类型允许不同类型的值的聚合体用编译期常数索引。C++14还允许使用类型代替常数索引，从多元中
	//获取对象，若多元组含有多于一个这个类型的对象，将会产生编译错误
	std::tuple<std::string, std::string, int> t("foo","bar",7);
	int ii = std::get<int>(t); //i==7
	int j = std::get<2>(t);// same as before :j==7
//	std::string s = std::get<std::string>(t);//compiler error due to ambiguity 
	std::tuple<std::string, int> t1("one string",7);
	std::string s_oneString = std::get<std::string>(t1);

	//15、较小的标准库特性
	//std::make_unique 可以像 std::make_shared 一样使用，用于产生std::unique_ptr对象
	//std::is_final,用于识别一个class类型是否禁止被继承
	//std::integral_constant增加了一个返回常量值得operator().
	//全局std::begin/std::end函数除外，增加了std::cbegin/std::cend函数，他们总返回常量迭代器（constant iterators）

	//16、已被移除或不包含在c++14标准特性
	//16.1）关于数组的扩展
	//16.2）Optional值
	//16.3）Concepts Lite
}
//C++14 end
//////////////////////////////////////////////////////////////////////////////////////////////////
