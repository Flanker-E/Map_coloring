
// MapDlg.cpp : ʵ���ļ�
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

#define N 32//ʡ�ĸ���
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
}m[32] = { { "�Ĵ�",322,327},
{"����",381,325},
{"����",389,281},
{"����",333,261},
{"����",432,321},
{"����",447,281},
{"ɽ��",426,246},
{"����",407,177},
{"�ӱ�",460,223},
{"����",491,307},
{"����",474,366},
{"����",370,383},
{"�ຣ",246,263},
{"����",469,189},
{"���",479,204},
{"����",424,378},
{"����",521,290},
{"ɽ��",486,245},
{"����",532,164},
{"����",564,138},
{"������",572,84},
{"����",356,241},
{"�Ϻ�",539,312},
{"�㽭",523,345},
{"����",507,384},
{"�㶫",455,424},
{"����",395,422},
{"����",307,412},
{"����",134,301},
{"�½�",143,191},
{"̨��",544,417},
{"����",406,480}
};

using namespace std;

// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ʵ��
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


// CMapDlg �Ի���



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


// CMapDlg ��Ϣ�������

BOOL CMapDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ��������...���˵�����ӵ�ϵͳ�˵��С�

	// IDM_ABOUTBOX ������ϵͳ���Χ�ڡ�
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

	// ���ô˶Ի����ͼ�ꡣ  ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO: �ڴ���Ӷ���ĳ�ʼ������

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
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

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ  ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�



//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR CMapDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CMapDlg::OnEnChangeEdit3()
{
	// TODO:  ����ÿؼ��� RICHEDIT �ؼ���������
	// ���ʹ�֪ͨ��������д CDialogEx::OnInitDialog()
	// ���������� CRichEditCtrl().SetEventMask()��
	// ͬʱ�� ENM_CHANGE ��־�������㵽�����С�

	// TODO:  �ڴ���ӿؼ�֪ͨ����������
}

void CMapDlg::OnEnChangeColorEdit()
{
	// TODO:  ����ÿؼ��� RICHEDIT �ؼ���������
	// ���ʹ�֪ͨ��������д CDialogEx::OnInitDialog()
	// ���������� CRichEditCtrl().SetEventMask()��
	// ͬʱ�� ENM_CHANGE ��־�������㵽�����С�

	// TODO:  �ڴ���ӿؼ�֪ͨ����������
}

void CMapDlg::OnEnChangeProvEdit()
{
	// TODO:  ����ÿؼ��� RICHEDIT �ؼ���������
	// ���ʹ�֪ͨ��������д CDialogEx::OnInitDialog()
	// ���������� CRichEditCtrl().SetEventMask()��
	// ͬʱ�� ENM_CHANGE ��־�������㵽�����С�

	// TODO:  �ڴ���ӿؼ�֪ͨ����������
}

void CMapDlg::OnBnClickedCloseBotton()
{
		// TODO: �ڴ���ӿؼ�֪ͨ����������
		CDialogEx::OnCancel();
}
void CMapDlg::Color(int center_x, int center_y, int color)
{
	CClientDC dc(this);
	int adx[] = { -1,0,1,0 }, ady[] = { 0,1,0,-1 }; //����ѡ������
	int *stakx = new int[High*Wide], *staky = new int[High*Wide];
	int xx, yy, x, y, mclr = 1, oldmclr = 0, begin = 0, end = 0;

	COLORREF colr; //����ʹ����ɫֵ�Ķ���
	begin = end = 0;
	stakx[end] = center_x;
	staky[end] = center_y;

	switch (color)//ѡ����ɫ  rgb(red,green,blue)
	{
	case 1:
		colr = RGB(165, 208, 231);  //��ɫ
		break;
	case 2: //��
		colr = RGB(106, 158, 190);
		break;
	case 3: //��
		colr = RGB(73, 170, 222);
		break;
	case 4:
		colr = RGB(26, 106, 173); //��
		break;
	default:
		colr = RGB(0, 0, 0);
		break;
	}

	while (begin <= end)//ջ����
	{
		xx = stakx[begin];
		yy = staky[begin++]; //ʡ������

		for (int j = 0; j<4; j++)
		{
			x = xx + adx[j];  //?
			y = yy + ady[j]; //?

			if (flag[y][x] == 0)//û��Ⱦɫ�ĵ����Ⱦɫ
			{
				dc.SetPixel(x, y, colr);  //��ɫ
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
	int colored(-1), top(0), i(0);//ջ��Ϊ��
	bool Yichu = false;
	while (top != colored)
	{
		if (top != -1 && (color == 0))//����ֵ
			color = 1;
		/*else if(top==0)
		{
		//ColorRecord[prov - 1][1] = color;//��һ��ʡ���
		colored++;
		}*/
		Yichu = false;
		i = 0;
		while (i <= colored)//����м�¼��ɫ����ʡ����ɫ�غ�
		{
			if (relation[prov - 1][(ColorQueue[i] - 1)] == 1)
			{
				if (ColorRecord[(ColorQueue[i] - 1)][1] == color)
				{
					color++;
					i = 0;
					continue;//��ֵ
				}
			}
			i++;
		}
		while (color > 4)//��ջ�����������ɫ��һֱ��ջ
		{
			ColorRecord[prov - 1][1] = 0;
			//ColorRecord[prov - 1][0] = 0;
			prov = ColorQueue[colored];
			colored--;
			color = ColorRecord[prov - 1][1];
			color++;
			Yichu = true;
		}
		if (Yichu == true)//�����ջ�����½��в�ɫ����
			continue;
		ColorRecord[prov - 1][1] = color;
		colored++;
		for (i = 0; i < N; i++)
		{
			if (ColorRecord[i][0] == 0 && (relation[prov - 1][i] == 1))//δ���ӵĽ���
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

	BOOL first = false;
	if (first == false)
	{

		//��ȡλͼ
		
		CString strfile = _T("ChinaMap.bmp");  //*ͼƬҪ��BMP��ʽ*
		CFile file;
		if (!file.Open(strfile, CFile::modeRead))
		{
			MessageBox(strfile + "��ȡ�ļ�������");
			return;
		}
		BITMAPFILEHEADER bmpheader;
		if (file.Read((LPSTR)&bmpheader, sizeof(bmpheader)) != sizeof(bmpheader))
		{
			MessageBox(_T("��ȡ�ļ�ͷʧ��"),MB_OK);
			return;
		}
		if (bmpheader.bfType != ((WORD)('M' << 8) | 'B'))
		{
			MessageBox(_T("�ⲻ��BMPλͼ�ļ�"), MB_OK);
			return;
		}

		BITMAPINFOHEADER bmphead; //λͼ��ϢͷBITMAPINFOHEADER��Ҳ��һ���ṹ
		if (file.Read((LPSTR)& bmphead, sizeof(bmphead)) != sizeof(bmphead))
		{
			MessageBox(_T("��ȡλͼͷ��Ϣʧ��"), MB_OK);
			return;
		}
		int   count = 3;//24λ���  
		int   w = bmphead.biWidth; //ͼƬ���
		int   h = bmphead.biHeight; //ͼƬ�߶�
		char  str[4]; //��ȡ�ļ�
		POINT p;
		CClientDC dc(this);
		p.x = 0;
		p.y = h;
		int i, j;
		for (i = h - 1; i >= 0; i--) //ѭ������
		{
			for (j = 0; j<w; j++)
			{
				p.x = j;
				p.y = i;
				file.Read(str, count); //�����BMPλͼ��ʽ����ÿ�ζ�ȡ4���ֽ���Ϣ
				int i1 = str[0];
				int i2 = str[1];
				int i3 = str[2];
				if (i1 == -1 && i2 == -1 && i3 == -1)//�հײ���
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
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	// �����ؼ��е����ݱ��浽��Ӧ�ı���   
	UpdateData(TRUE);
	
	int prov, ColorQueue[N] = { 0 }, ColorRecord[N][2] = { 0 },i,j;//provʡ�ţ�ColorQueue��ɫ��ʡ�Ķӣ�ColorRecordʡ�Ž��Ӽ�¼&ʡ����ɫ��relation�ڽӾ���
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
	//printf("�������һ����ʼ��ʡ�Լ���ɫ");
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
		Color(x, y, ColorRecord[j][1]);  //��ɫ����
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
	// ���ݸ�������ֵ������Ӧ�Ŀؼ����͵ı༭�����ʾm_editSum��ֵ   
	UpdateData(FALSE);
}


