
// MapDlg.h : 头文件
//

#pragma once


// CMapDlg 对话框
class CMapDlg : public CDialogEx
{
// 构造
public:
	CMapDlg(CWnd* pParent = NULL);	// 标准构造函数
	void Color(int x, int y, int color);
// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MAP_DIALOG };
#endif

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
	afx_msg void OnEnChangeEdit2();
	// 输入1~32（代表省份）
	int m_prov;
	afx_msg void OnEnChangeProvEdit();
	// 输入颜色
	int m_color;
	// 计算得到的值
	int m_ColorReturn;
	afx_msg void OnBnClickedCloseBotton();
	afx_msg void OnBnClickedBeginColorButton();
	afx_msg void OnEnChangeEdit3();
	afx_msg void OnEnChangeColorEdit();
	afx_msg void OnBnClickedButton1();
};
