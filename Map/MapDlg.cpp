
// MapDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "Map.h"
#include "MapDlg.h"
#include <afxdialogex.h>
#include<iostream>
#include<stdio.h>
#include<Windows.h>
#include <fstream>
#include<afx.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#define N 32//省的个数
#define Wide 660
#define High 500
int flag[High][Wide] = { 0 };
/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About

struct map
{
	char name[20];
	int x;
	int y;
}m[32] = { { "四川",322,327},
{"重庆",381,325},
{"陕西",389,281},
{"甘肃",333,261},
{"湖北",432,321},
{"河南",447,281},
{"山西",426,246},
{"内蒙",407,177},
{"河北",460,223},
{"安徽",491,307},
{"江西",474,366},
{"贵州",370,383},
{"青海",246,263},
{"北京",469,189},
{"天津",479,204},
{"湖南",424,378},
{"江苏",521,290},
{"山东",486,245},
{"辽宁",532,164},
{"吉林",564,138},
{"黑龙江",572,84},
{"宁夏",356,241},
{"上海",539,312},
{"浙江",523,345},
{"福建",507,384},
{"广东",455,424},
{"广西",395,422},
{"云南",307,412},
{"西藏",134,301},
{"新疆",143,191},
{"台湾",544,417},
{"海南",406,480}
};

using namespace std;

// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
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


// CMapDlg 对话框



CMapDlg::CMapDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_MAP_DIALOG, pParent)
	, m_prov(0)
	, m_color(0)
	, m_ColorReturn(0)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMapDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_PROV_EDIT, m_prov);
	DDV_MinMaxInt(pDX, m_prov, 1, 32);
	DDX_Text(pDX, IDC_COLOR_EDIT, m_color);
	DDV_MinMaxInt(pDX, m_color, 1, 4);
	DDX_Text(pDX, IDC_EDIT3, m_ColorReturn);
}

BEGIN_MESSAGE_MAP(CMapDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
/*	ON_EN_CHANGE(IDC_EDIT1, &CMapDlg::OnEnChangeEdit1)
	ON_EN_CHANGE(IDC_EDIT2, &CMapDlg::OnEnChangeEdit2)*/
	ON_EN_CHANGE(IDC_PROV_EDIT, &CMapDlg::OnEnChangeProvEdit)
	ON_BN_CLICKED(ID_CLOSE_BOTTON, &CMapDlg::OnBnClickedCloseBotton)
	ON_BN_CLICKED(IDC_BEGIN_COLOR_BUTTON, &CMapDlg::OnBnClickedBeginColorButton)
	ON_EN_CHANGE(IDC_EDIT3, &CMapDlg::OnEnChangeEdit3)
	ON_EN_CHANGE(IDC_COLOR_EDIT, &CMapDlg::OnEnChangeColorEdit)
END_MESSAGE_MAP()


// CMapDlg 消息处理程序

BOOL CMapDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		//BOOL bNameValid;
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);//copy
		//bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		//ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CMapDlg::OnSysCommand(UINT nID, LPARAM lParam)
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
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。



//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CMapDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CMapDlg::OnEnChangeEdit3()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialogEx::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
}

void CMapDlg::OnEnChangeColorEdit()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialogEx::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
}

void CMapDlg::OnEnChangeProvEdit()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialogEx::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
}

void CMapDlg::OnBnClickedCloseBotton()
{
		// TODO: 在此添加控件通知处理程序代码
		CDialogEx::OnCancel();
}
void CMapDlg::Color(int center_x, int center_y, int color)
{
	CClientDC dc(this);
	int adx[] = { -1,0,1,0 }, ady[] = { 0,1,0,-1 }; //交替选择坐标
	int *stakx = new int[High*Wide], *staky = new int[High*Wide];
	int xx, yy, x, y, mclr = 1, oldmclr = 0, begin = 0, end = 0;

	COLORREF colr; //定义使用颜色值的对象
	begin = end = 0;
	stakx[end] = center_x;
	staky[end] = center_y;

	switch (color)//选择颜色  rgb(red,green,blue)
	{
	case 1:
		colr = RGB(165, 208, 231);  //红色
		break;
	case 2: //绿
		colr = RGB(106, 158, 190);
		break;
	case 3: //黄
		colr = RGB(73, 170, 222);
		break;
	case 4:
		colr = RGB(26, 106, 173); //蓝
		break;
	default:
		colr = RGB(0, 0, 0);
		break;
	}

	while (begin <= end)//栈遍历
	{
		xx = stakx[begin];
		yy = staky[begin++]; //省份坐标

		for (int j = 0; j<4; j++)
		{
			x = xx + adx[j];  //?
			y = yy + ady[j]; //?

			if (flag[y][x] == 0)//没有染色的点进行染色
			{
				dc.SetPixel(x, y, colr);  //着色
				stakx[++end] = x;
				staky[end] = y;
				flag[y][x] = 1;
			}
		}
	}
	delete stakx;
	delete staky;
}

void Coloring(int prov, int color, int ColorQueue[N], int relation[N][N], int ColorRecord[N][2])
{
	int colored(-1), top(0), i(0);//栈顶为数
	bool Yichu = false;
	while (top != colored)
	{
		if (top != -1 && (color == 0))//赋初值
			color = 1;
		/*else if(top==0)
		{
		//ColorRecord[prov - 1][1] = color;//第一个省入队
		colored++;
		}*/
		Yichu = false;
		i = 0;
		while (i <= colored)//检查有记录颜色的邻省的颜色重合
		{
			if (relation[prov - 1][(ColorQueue[i] - 1)] == 1)
			{
				if (ColorRecord[(ColorQueue[i] - 1)][1] == color)
				{
					color++;
					i = 0;
					continue;//赋值
				}
			}
			i++;
		}
		while (color > 4)//退栈：如果超出颜色则一直退栈
		{
			ColorRecord[prov - 1][1] = 0;
			//ColorRecord[prov - 1][0] = 0;
			prov = ColorQueue[colored];
			colored--;
			color = ColorRecord[prov - 1][1];
			color++;
			Yichu = true;
		}
		if (Yichu == true)//如果退栈则重新进行查色工作
			continue;
		ColorRecord[prov - 1][1] = color;
		colored++;
		for (i = 0; i < N; i++)
		{
			if (ColorRecord[i][0] == 0 && (relation[prov - 1][i] == 1))//未进队的进队
			{
				ColorQueue[top + 1] = i + 1;
				top++;
				ColorRecord[i][0] = 1;
			}
		}
		/*	for (int i = 0; i<N; i++)
		printf("%d\n", ColorQueue[i]);*/
		prov = ColorQueue[colored + 1];
		color = 0;
		
	}
}

void CMapDlg::OnPaint()
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

	BOOL first = false;
	if (first == false)
	{

		//读取位图
		
		CString strfile = _T("ChinaMap.bmp");  //*图片要是BMP格式*
		CFile file;
		if (!file.Open(strfile, CFile::modeRead))
		{
			MessageBox(strfile + "获取文件不存在");
			return;
		}
		BITMAPFILEHEADER bmpheader;
		if (file.Read((LPSTR)&bmpheader, sizeof(bmpheader)) != sizeof(bmpheader))
		{
			MessageBox(_T("获取文件头失败"),MB_OK);
			return;
		}
		if (bmpheader.bfType != ((WORD)('M' << 8) | 'B'))
		{
			MessageBox(_T("这不是BMP位图文件"), MB_OK);
			return;
		}

		BITMAPINFOHEADER bmphead; //位图信息头BITMAPINFOHEADER，也是一个结构
		if (file.Read((LPSTR)& bmphead, sizeof(bmphead)) != sizeof(bmphead))
		{
			MessageBox(_T("读取位图头信息失败"), MB_OK);
			return;
		}
		int   count = 3;//24位真彩  
		int   w = bmphead.biWidth; //图片宽度
		int   h = bmphead.biHeight; //图片高度
		char  str[4]; //读取文件
		POINT p;
		CClientDC dc(this);
		p.x = 0;
		p.y = h;
		int i, j;
		for (i = h - 1; i >= 0; i--) //循环遍历
		{
			for (j = 0; j<w; j++)
			{
				p.x = j;
				p.y = i;
				file.Read(str, count); //如果是BMP位图格式，则每次读取4个字节信息
				int i1 = str[0];
				int i2 = str[1];
				int i3 = str[2];
				if (i1 == -1 && i2 == -1 && i3 == -1)//空白部分
				{
					flag[p.y][p.x] = 0;
					continue;
				}
				flag[p.y][p.x] = 1;
				dc.SetPixel(p, RGB(i1, i2, i3));
			}
		}
		file.Close();

	}
	
}

void CMapDlg::OnBnClickedBeginColorButton()
{
	// TODO: 在此添加控件通知处理程序代码
	// 将各控件中的数据保存到相应的变量   
	UpdateData(TRUE);
	
	int prov, ColorQueue[N] = { 0 }, ColorRecord[N][2] = { 0 },i,j;//prov省号；ColorQueue填色的省的队；ColorRecord省号进队记录&省的颜色；relation邻接矩阵
	int relation[N][N] = { { 0,1,1,1,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,0,0,0 },
	{ 1,0,1,0,1,0,0,0,0,0,0,1,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
	{ 1,1,0,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0 },
	{ 1,0,1,0,0,0,0,1,0,0,0,0,1,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,1,0,0 },
	{ 0,1,1,0,0,1,0,0,0,1,1,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
	{ 0,0,1,0,1,0,1,0,1,1,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
	{ 0,0,1,0,0,1,0,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
	{ 0,0,1,1,0,0,1,0,1,0,0,0,0,0,0,0,0,0,1,1,1,1,0,0,0,0,0,0,0,0,0,0 },
	{ 0,0,0,0,0,1,1,1,0,0,0,0,0,1,1,0,0,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0 },
	{ 0,0,0,0,1,1,0,0,0,0,1,0,0,0,0,0,1,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0 },
	{ 0,0,0,0,1,0,0,0,0,1,0,0,0,0,0,1,0,0,0,0,0,0,0,1,1,1,0,0,0,0,0,0 },
	{ 1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,1,1,0,0,0,0 },
	{ 1,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,0,0 },
	{ 0,0,0,0,0,0,0,0,1,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
	{ 0,0,0,0,0,0,0,0,1,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
	{ 0,1,0,0,1,0,0,0,0,0,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,0,0,0,0,0 },
	{ 0,0,0,0,0,1,0,0,0,1,0,0,0,0,0,0,0,1,0,0,0,0,1,1,0,0,0,0,0,0,0,0 },
	{ 0,0,0,0,0,1,0,0,1,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
	{ 0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0 },
	{ 0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,1,0,1,0,0,0,0,0,0,0,0,0,0,0 },
	{ 0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0 },
	{ 0,0,1,1,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
	{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0 },
	{ 0,0,0,0,0,0,0,0,0,1,1,0,0,0,0,0,1,0,0,0,0,0,1,0,1,0,0,0,0,0,0,0 },
	{ 0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,1,0,1,0,0,0,0,1,0 },
	{ 0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,1,0,0,0,0,0,0,0,0,1,0,1,0,0,0,0,1 },
	{ 0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,1,0,0,0,0,0,0,0,0,0,1,0,1,0,0,0,0 },
	{ 1,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,1,0,0,0 },
	{ 1,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,1,0,0 },
	{ 0,0,0,1,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0 },
	{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0 },
	{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0 } };

	int color(0);
	//printf("请输入第一个开始的省以及颜色");
	//scanf("%d%d", &prov, &color);
	prov = m_prov; color = m_color;
	ColorRecord[prov - 1][1] = color;
	ColorRecord[prov - 1][0] = 1;
	ColorQueue[0] = prov;
	Coloring(prov, color, ColorQueue, relation, ColorRecord);
	for (int i = 0; i < N; i++)
		m_ColorReturn = 10 * m_ColorReturn + ColorRecord[i][1];
	//printf("%d,%d\n", ColorRecord[i][1], ColorRecord[i][0]);

	for (i = 0; i<32; i++)
	{
		j=ColorQueue[i]-1;
		int x = m[j].x;
		int y = m[j].y;
		Color(x, y, ColorRecord[j][1]);  //着色函数
	}
	int select;
	
		
		for (i = 0; i<High; i++)
		{
			for (j = 0; j<Wide; j++)
			{
				flag[i][j] = 0;
			}
		}
		OnPaint();
	// 根据各变量的值更新相应的控件。和的编辑框会显示m_editSum的值   
	UpdateData(FALSE);
}


