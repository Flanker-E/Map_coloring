
// MapDlg.h : ͷ�ļ�
//

#pragma once


// CMapDlg �Ի���
class CMapDlg : public CDialogEx
{
// ����
public:
	CMapDlg(CWnd* pParent = NULL);	// ��׼���캯��
	void Color(int x, int y, int color);
// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MAP_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnEnChangeEdit1();
	afx_msg void OnEnChangeEdit2();
	// ����1~32������ʡ�ݣ�
	int m_prov;
	afx_msg void OnEnChangeProvEdit();
	// ������ɫ
	int m_color;
	// ����õ���ֵ
	int m_ColorReturn;
	afx_msg void OnBnClickedCloseBotton();
	afx_msg void OnBnClickedBeginColorButton();
	afx_msg void OnEnChangeEdit3();
	afx_msg void OnEnChangeColorEdit();
	afx_msg void OnBnClickedButton1();
};
