
// RLC_CircuitDlg.h : ���Y��
//

#pragma once
#include "afxwin.h"


// CRLC_CircuitDlg ��ܤ��
class CRLC_CircuitDlg : public CDialog
{
// �غc
public:
	CRLC_CircuitDlg(CWnd* pParent = NULL);	// �зǫغc�禡

// ��ܤ�����
	enum { IDD = IDD_RLC_CIRCUIT_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV �䴩


// �{���X��@
protected:
	HICON m_hIcon;

	// ���ͪ��T�������禡
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	CScrollBar m_R_Bar;
	CScrollBar m_L_Bar;
	CScrollBar m_C_Bar;
	CScrollBar m_f_Bar;
	CEdit m_I_Value;
	CEdit m_Vo_Value;
	CEdit m_Z_Value;
	CStatic m_R_Value;
	CStatic m_L_Value;
	CStatic m_C_Value;
	CStatic m_f_Value;
	afx_msg void CalcAndDraw();
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
};
