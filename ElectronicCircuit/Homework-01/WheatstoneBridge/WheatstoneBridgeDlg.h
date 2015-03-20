
// WheatstoneBridgeDlg.h : ���Y��
//

#pragma once
#include "afxwin.h"


// CWheatstoneBridgeDlg ��ܤ��
class CWheatstoneBridgeDlg : public CDialog
{
// �غc
public:
	CWheatstoneBridgeDlg(CWnd* pParent = NULL);	// �зǫغc�禡

// ��ܤ�����
	enum { IDD = IDD_WHEATSTONEBRIDGE_DIALOG };

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
	CScrollBar m_R1_Bar;
	CScrollBar m_R2_Bar;
	CScrollBar m_R3_Bar;
	CScrollBar m_R4_Bar;
	CScrollBar m_Vin_Bar;
	CEdit m_I1_Value;
	CEdit m_I2_Value;
	CEdit m_I3_Value;
	CEdit m_I4_Value;
	CEdit m_V1_Value;
	CEdit m_V2_Value;
	CEdit m_V3_Value;
	CEdit m_V4_Value;
	CEdit m_Vo_Value;
	CStatic m_R1_Value;
	CStatic m_R2_Value;
	CStatic m_R3_Value;
	CStatic m_R4_Value;
	CStatic m_Vin_Value;
	afx_msg void OnBnClickedCalculate();
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
};
